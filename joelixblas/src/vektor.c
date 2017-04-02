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
#include "vektor_hidden.h"
#include "vektor.h"
#include "joelix_error.h"

extern Joelix_Fehler joelix_fehler_code;

/* Einen Vektor erstellen */
Joelix_Fehler joelix_vektor_init (Joelix_Vektor * px, int n)
{
  Joelix_Vektor V;

  if (px == NULL || n < 0) {
   /* Ungueltige Parameter */
   return (joelix_fehler_code = F_FALSCHE_PARAMETER);
  }
  /* Speicher für V selber alloziieren */
  V = malloc (sizeof (*V));
  if (V == NULL) {
    /* Speicherfehler */
    return (joelix_fehler_code = F_KEIN_SPEICHER);
  }
  /* Speicher für n Werte alloziieren */
  V->werte = calloc (n, sizeof (*V->werte));
  if (V->werte == NULL) {
    /* Speicherfehler */
    free (V); 
    return (joelix_fehler_code = F_KEIN_SPEICHER);
  }
  V->laenge = n;
  *px = V;
  return (joelix_fehler_code = F_ERFOLG);
}

/* setze x = 0 */
Joelix_Fehler joelix_vektor_null (Joelix_Vektor x)
{
  int i;
  
  if (x == NULL) return (joelix_fehler_code = F_FALSCHE_PARAMETER);

  for (i = 0;i < x->laenge;i++) {
    x->werte[i] = 0;
  }
  return (joelix_fehler_code = F_ERFOLG);
}

/* gibt Laenge zurueck */
int joelix_vektor_laenge (Joelix_Vektor x)
{
  if (x == NULL) {
    joelix_fehler_code = F_FALSCHE_PARAMETER;
    return -1;
  } else {
    return x->laenge;
  }
}

/* setze x_i = wert */
Joelix_Fehler joelix_vektor_seti (Joelix_Vektor x, int i, double wert)
{
  if (x == NULL) return (joelix_fehler_code = F_FALSCHE_PARAMETER); /* Check ob x gueltig ist */
  /* Check ob i im Indexbereich ist. */
  if (i < 0 || i >= x->laenge) return (joelix_fehler_code = F_FALSCHER_INDEX);
  /* setze neuen Wert */
  x->werte[i] = wert;
  return (joelix_fehler_code = F_ERFOLG);
}

/* Setze wert = x_i */
Joelix_Fehler joelix_vektor_geti (Joelix_Vektor x, int i, double *wert)
{
  if (x == NULL) return (joelix_fehler_code = F_FALSCHE_PARAMETER); /* Check ob x gueltig ist */
  /* Check ob i im Indexbereich ist. */
  if (i < 0 || i >= x->laenge) return (joelix_fehler_code = F_FALSCHER_INDEX);
  /* setze Wert */
  *wert = x->werte[i];
  return (joelix_fehler_code = F_ERFOLG);
}

/* setze y = x */
Joelix_Fehler joelix_vektor_copy (Joelix_Vektor y, Joelix_Vektor x)
{
  if (x == NULL || y == NULL) return (joelix_fehler_code = F_FALSCHE_PARAMETER); /* ungueltige Eingabe */
  /* Check ob die Vektoren gleich gross sind */
  if (x->laenge != y->laenge) {
    return (joelix_fehler_code = F_FALSCHE_DIMENSIONEN_VEKTOR_KOPIE);
  }
  /* kopiere x */
  memcpy (y->werte, x->werte, y->laenge * sizeof (*y->werte));
  return (joelix_fehler_code = F_ERFOLG);
}

/* Berechne x = alpha * x */
Joelix_Fehler joelix_vektor_ax (Joelix_Vektor x, double alpha)
{
  int i;
  
  if (x == NULL) return (joelix_fehler_code = F_FALSCHE_PARAMETER); /* Check ob x gueltig ist */
  /* Setze jeden Eintrag von x auf x*alpha */
  for (i = 0;i < x->laenge;i++) x->werte[i] *= alpha;
  return (joelix_fehler_code = F_ERFOLG);
}

/* Berechen y = alpha * x + y */
Joelix_Fehler joelix_vektor_axpy (Joelix_Vektor y, Joelix_Vektor x, double alpha)
{
  int i;

  if (x == NULL || y == NULL) return (joelix_fehler_code = F_FALSCHE_PARAMETER); /* ungueltige Eingabe */
  /* Check ob die Vektoren gleich gross sind */
  if (x->laenge != y->laenge) {
    return (joelix_fehler_code = F_FALSCHE_DIMENSIONEN_VEKTOR_VEKTOR);
  }
  /* Modifiziere jeden Eintrag von y */

  for (i = 0;i < y->laenge;i++){
    y->werte[i] += alpha * x->werte[i];
  }
  return (joelix_fehler_code = F_ERFOLG);
}

/* Berechne das Skalarprodukt von x und y */
Joelix_Fehler joelix_vektor_dot (double * produkt, Joelix_Vektor x, Joelix_Vektor y)
{
  int i;

  if (produkt == NULL || x == NULL || y == NULL) {
    /* ungueltige Eingabe */
    return (joelix_fehler_code = F_FALSCHE_PARAMETER); 
  }
  /* Check ob die Vektoren gleich gross sind */
  if (x->laenge != y->laenge) {
    return (joelix_fehler_code = F_FALSCHE_DIMENSIONEN_VEKTOR_VEKTOR);
  }
  /* Berechne das Skalarprodukt */
  *produkt = 0;
  for (i = 0;i < x->laenge;i++) *produkt += x->werte[i] * y->werte[i];
  return (joelix_fehler_code = F_ERFOLG);  
}

Joelix_Fehler joelix_vektor_print (Joelix_Vektor x)
{
  int i;

  if (x == NULL) return (joelix_fehler_code = F_FALSCHE_PARAMETER); /* ungueltige Eingabe */
  /* Print Vektor */
  printf("(");
  for (i = 0;i < x->laenge;i++) printf ("%f%s", x->werte[i], (i == x->laenge-1 ? "" : ", ") );
  printf(")\n");
  return (joelix_fehler_code = F_ERFOLG);
}

Joelix_Fehler joelix_vektor_print_tofile (Joelix_Vektor x, char *filename)
{
  FILE * file;
  int i, ret;

  file = fopen (filename, "w");
  if (file == NULL) return F_FALSCHE_PARAMETER;
  /* schreibe Eintraege des Vektors Zeile fuer Zeile ins File */
  for (i = 0;i < x->laenge;i++) {
    ret = fprintf (file, "%e %e\n", ((double) i) / (x->laenge - 1), x->werte[i]);
    if (ret <= 0) {
      fclose (file);
      return F_FILEIO_FEHLER;
    }
  }
  fclose (file);
  return F_ERFOLG;
}

/* Speicher eine Vektors freigeben */
Joelix_Fehler joelix_vektor_loeschen (Joelix_Vektor *pVektor)
{
  Joelix_Vektor V;
   
  /* Check ob Argument falsch benutzt wird */
  if (pVektor == NULL || *pVektor == NULL) {
    return (joelix_fehler_code = F_FALSCHE_PARAMETER);
  }
  /* Speicher freigeben und pVektor auf NULL setzen */
  V = *pVektor;
  free (V->werte);
  free (V);
  pVektor = NULL;
  return (joelix_fehler_code = F_ERFOLG);
}
