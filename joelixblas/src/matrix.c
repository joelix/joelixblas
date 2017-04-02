/*  
  This file is part of joelixblas.
  joelixblas is a C library for some basic linear algebra routines, which
  was created as supplementary material to the advanced C programming course
  given by the authors in April 2017 at the univerity of Bonn.
 
  Copyright (C) 2017 the developers
 
  joelixblas is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.
 
  joelixblas is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "joelix_error.h"
#include "vektor_hidden.h"
#include "vektor.h"
#include "matrix_hidden.h"
#include "matrix.h"

/* Gebe Speicher von Matrix frei. Wird intern benutzt, weil wir es mehr
   als einer Stelle brauchen.
 */
static void joelix_smatrix_befreien (Joelix_sMatrix M)
{
  if (M == NULL) return;
  free (M->werte);
  free (M->zeilen_akk);
  free (M->spalten_ind);
  free (M);
}

/* Initialisiere sparse Matrix mit gegebener Anzahl an nicht-null Elementen */
Joelix_Fehler joelix_smatrix_init (Joelix_sMatrix *pMatrix, int nzeilen, int nspalten,
                                   int nnichtnull)
{
  Joelix_sMatrix M;
  int i;
  
  if (pMatrix == NULL || nzeilen < 0 || nspalten < 0 || nnichtnull < 0) {
   /* Ungueltige Parameter */
   return (joelix_fehler_code = F_FALSCHE_PARAMETER);
  }
  
  M = malloc (sizeof (*M));
  if (M == NULL) return (joelix_fehler_code = F_KEIN_SPEICHER); /* Speicherfehler */
  
  /* Setze Parameter von M */
  M->n = nzeilen;
  M->m = nspalten;
  M->nnE = nnichtnull;
  /* Alloziiere Speicher */
  /* Speicher fuer die nich-null Eintraege */
  M->werte = calloc (M->nnE, sizeof (*M->werte));
  /* Ein Index pro Zeile plus ein zusaetzlicher Index */
  M->zeilen_akk = malloc ( (M->n + 1)*sizeof (*M->zeilen_akk) );
  /* Fuer jeden nich-null Eintrag ein Spaltenindex */
  M->spalten_ind = calloc (M->nnE, sizeof (*M->spalten_ind));
  /* Abfrage, ob wir den Speicher bekommen haben */
  if (M->werte == NULL || M->zeilen_akk == NULL || M->spalten_ind == NULL) {
    /* Speicherfehler, also geben wir allen Speicher, den wir geholt haben frei.
       Dies geht so, da free(NULL) laut Standard nichts tut. */
    joelix_smatrix_befreien (M);
    return (joelix_fehler_code = F_KEIN_SPEICHER);
  }
  /* Wir initialisieren die zeilen_akk (ausser den 0ten) Werte mit -1 vor,
   * um beim fuellen mit joelix_smatrix_fuelleZeile checken zu
   * koennen, ob die Zeilen in der richtigen Reihenfolge befuellt werden. */
  if (M->n > 0) M->zeilen_akk[0] = 0;
  for (i = 1;i < M->n + 1;i++) M->zeilen_akk[i] = -1;
  *pMatrix = M;
  return (joelix_fehler_code = F_ERFOLG);
}

/* Eine neue Zeile einer smatrix befuellen. Wir gehen davon aus, dass die Zeilen
   in aufsteigender Reihenfolge befuellt werden. Nullzeilen koennen dabei ueber-
   sprungen werden.
 */
Joelix_Fehler joelix_smatrix_fuelleZeile (Joelix_sMatrix M, int zeile, 
                                           int znichtnull,
                                           double * werte, int * spalten)
{
  int j;
  int fruehere_zeile; /* Speichert den index der vorherigen nicht-null Zeile */
  int frueherer_index; /* Speichert den letzten eingetragenen index in zeilen_akk */

  if ( M == NULL ) return (joelix_fehler_code = F_FALSCHE_PARAMETER);
#if 0
  if (M->zeilen_akk[zeile+1] >= 0) {
    /* Diese Zeile wurde schon befuellt. Neue Werte werden nicht eingefuellt. */
    fprintf (stderr, "Warnung: Zeile %i in Matrix wurde schon befuellt.\n"
             " Neue Werte werden ignoriert.\n", zeile);
    return M;
  }
#endif
  /* Falls zeile eine Nullzeile ist, ist nichts zu tuen */
  if (znichtnull > 0) {
    /* Wir benutzen den letzten Werte des zeilen_akk arrays als
     * temporaeren Speicher, um uns zu merken welche Zeile wir
     * als letztes befuellt haben. Der Wert ist -1, wenn noch
     * keine Zeile befuellt wurde. */
    fruehere_zeile = M->zeilen_akk[M->n];
    frueherer_index = M->zeilen_akk[fruehere_zeile+1];

    /* Fehlercheck */
    if (frueherer_index + znichtnull > M->nnE) {
      /* Zu viele nicht Null Werte */
      return (joelix_fehler_code = F_FALSCHE_ANZAHL_NICHT_NULL_WERTE);
    }
    
    /* Wir fuellen alle Zeilen zwischen der letzten gefuellten und der
     * neuen gefuellten mit dem neuen Index, naemlich frueherer_index + znichtnull.
     * Da wir davon ausgehen, dass die Zeilen in aufsteigender Reihenfolge gefuellt
     * werden, sind alle Zeilen zwischen dem letzten Index und i Nullzeilen. */
    for (j = fruehere_zeile+2;j < zeile+1; j++) {
      M->zeilen_akk[j] = frueherer_index;
    }
    /* Schreibe den neuen index fuer die naechste Zeile nach zeile */
    M->zeilen_akk[zeile + 1] = frueherer_index + znichtnull;
    /* zeile ist jetzt die neue als letzte befuellte Zeile */
    M->zeilen_akk[M->n] = zeile;

    /* Uebertrage die werte und Spaltenindices in die Arrays von M */
    memcpy (M->werte + frueherer_index,
            werte, znichtnull * sizeof (*werte));
    memcpy (M->spalten_ind + frueherer_index,
            spalten, znichtnull * sizeof (*spalten));
    /* Wenn wir die letzte moegliche Zeile fuellen,
     * werden alle kommenden Werte aufgefuellt. */
    if (frueherer_index + znichtnull == M->nnE) {
      for (j = zeile + 1;j < M->n+1;j++) M->zeilen_akk[j] = M->nnE;
    }
  }
  return (joelix_fehler_code = F_ERFOLG);
}

/* Fordere die Anzahl der Zeilen an. */
int joelix_smatrix_get_zeilen(Joelix_sMatrix M)
{
  if (M == NULL){
    joelix_fehler_code = F_FALSCHE_PARAMETER;
    return -1;
  }
  else
  {
    return M->n;
  }
}

/* Fordere die Anzahl der Spalten an. */
int joelix_smatrix_get_spalten(Joelix_sMatrix M)
{
  if (M == NULL){
    joelix_fehler_code = F_FALSCHE_PARAMETER;
    return -1;
  }
  else
  {
    return M->m;
  }
}

/* Aendere einen nicht-null Eintrag, der vorher mit fuelleZeile gesetzt wurde */
Joelix_Fehler joelix_smatrix_aendernneintrag (Joelix_sMatrix M, int zeile,
                                              int spalte, double wert)
{
  int j;
  int found = 0;

  if (M == NULL || zeile < 0 || zeile >= M->n
      || spalte < 0 || spalte >= M->m) return F_FALSCHE_PARAMETER;

  /* Wir suchen in den nicht-null Eintraegen zu der Zeile nach dem passenden
   * Spalteneintrag */
  j = M->zeilen_akk[zeile];
  while (!found) {
    if (M->spalten_ind[j] == spalte) {
      found = 1;
    }
    else {
      /* Der Spaltenindex existiert nicht */
      if (j >= M->zeilen_akk[zeile+1]) found = -1;
      j++;
    }
  }
  /* Falls der Eintrag nicht gefunden wurde */
  if (found < 0) return F_FALSCHE_PARAMETER;
  /* Der Eintrag wurde gefunden und ist an Stelle j im Array werte */
  M->werte[j] = wert;
  return F_ERFOLG;
}

/* b = Mx matrix-vektor Produkt */
Joelix_Fehler joelix_smatvec (Joelix_Vektor b, Joelix_sMatrix M, Joelix_Vektor x)
{
  int i, k;
 
  if (b == NULL || M == NULL || x == NULL) return (joelix_fehler_code = F_FALSCHE_PARAMETER);
  
  if (x->laenge != b->laenge) {
    return (joelix_fehler_code = F_FALSCHE_DIMENSIONEN_MATRIX_VEKTOR);
  }

  for (i = 0;i < M->n;i++) {
    /* Schleife ueber alle Zeilen der Matrix */
    b->werte[i] = 0;
    for (k = M->zeilen_akk[i];k < M->zeilen_akk[i+1];k++) {
      /* Schleife ueber alle nicht-null Eintraege dieser Zeile */
      /* Der wert an Stelle k steht in Spalte spalten_ind[k] und muss dehalb
         mit dem Wert in Zeile spalten_ind[k] von x multipliziert werden. */
      b->werte[i] += M->werte[k] * x->werte[M->spalten_ind[k]];
    }
  }
  return (joelix_fehler_code = F_ERFOLG);
}


/* Gebe Matrix auf Konsole aus */
Joelix_Fehler joelix_smatrix_print (const Joelix_sMatrix M)
{
  int row, i, j;

  if (M == NULL) return (joelix_fehler_code = F_FALSCHE_PARAMETER);
  
  for (row = 0;row < M->n;row++) {
    /* Gehe jede Zeile durch */
    j = 0;
    for (i = M->zeilen_akk[row];i < M->zeilen_akk[row+1];i++) {
      /* Nulleintraege for dem Eintrag */
      for (;j < M->spalten_ind[i];j++) printf (" 0");
      printf (" %f", M->werte[i]);
      j++;
    }
    /* Nulleintraege nach letztem Eintrag der Zeile */
    for (;j < M->m;j++) printf (" 0");
    printf ("\n");
  }
  
  return (joelix_fehler_code = F_ERFOLG);
}

/* detailierter output */
Joelix_Fehler joelix_smatrix_print_debug (Joelix_sMatrix M)
{
  int i;

  if (M == NULL) return (joelix_fehler_code = F_FALSCHE_PARAMETER);
  
  printf ("%i x %i Matrix mit %i nicht-null Eintraegen.\n", M->n, M->m, M->nnE);
  printf ("Werte:  \t");
  for (i = 0;i < M->nnE;i++) printf ("%f ", M->werte[i]);
  printf ("\nZeilen: \t");
  for (i = 0;i < M->n + 1;i++) printf ("%i ", M->zeilen_akk[i]);
  printf ("\nSpalten:\t");
  for (i = 0;i < M->nnE;i++) printf ("%i ", M->spalten_ind[i]);
  printf ("\n");
  joelix_smatrix_print (M);
  
  return (joelix_fehler_code = F_ERFOLG);
}


/* Gebe allen Speicher eine sparse Matrix wieder frei */
Joelix_Fehler joelix_smatrix_loeschen (Joelix_sMatrix *pM)
{
  if (pM == NULL || *pM == NULL) (joelix_fehler_code = F_FALSCHE_PARAMETER);
  joelix_smatrix_befreien (*pM);
  
  return (joelix_fehler_code = F_ERFOLG);
}

