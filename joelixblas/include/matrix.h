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


#ifndef __JOELIX_MATRIX_H__
#define __JOELIX_MATRIX_H__

#include "joelix_error.h"
#include "vektor.h"

/** \file matrix.h Hier werden die Funktionen fuer das Matrix-Interface
 * festgelegt */

/** Der Datentyp fuer Matrizen. */
typedef struct Joelix_sparse_Matrix_t *Joelix_sMatrix;

/** Initialisiert eine sparse Matrix mit einer gegebenen Anzahl an nicht-null Eintraegen.
  \param [in] pMatrix    Pointer auf die Matrix (vom Typ Joelix_sMatrix) die
                         initialisiert werden soll.
  \param [in] nzeilen    Die Anzahl an Zeilen der Matrix.
  \param [in] nspalten   Die Anzahl an Spalten der Matrix.
  \param [in] nnichtnull Die Anzahl an nicht-null Eintraegen der Matrix.
  \return                F_ERFOLG bei Erfolg, sonst ein anderer Fehlercode.
 */
Joelix_Fehler joelix_smatrix_init (Joelix_sMatrix *pMatrix, int nzeilen, int nspalten,
                                   int nnichtnull);

/** Befuelle eine Zeile einer sparse Matrix mit Eintraegen.
   Nachdem die Matrix mit joelix_smatrix_init initialisiert wurde, muss diese Funktion
   fuer jede Zeile mit nicht-null Eintraegen aufgerufen werden. Die Aufrufe muessen in
   aufsteigender Reihenfolge des Zeilenindex erfolgen.
   \param [in] M          Eine mit joelix_sMatrix_init initialisierte Matrix.
   \param [in] zeile      Der Index der zu befuellenden Zeile.
   \param [in] znichtnull Die Anzahl der nicht-null Eintraege in dieser Zeile.
   \param [in] werte      Ein Array der Laenge znichtnull mit den Werten der nicht-null Eintraege.
   \param [in] spalten    Ein Array der Laenge ynichtnull mit den Spaltenindices der
                       nicht-null Eintraege.
   \return             F_ERFOLG bei Erfolg, sonst ein anderer Fehlercode.
   Warnung:            Es wird nicht ueberprueft, ob die Spaltenindices alle
                       innerhalb der zulaessigen Grenzen liegen (0 <= j <
                       Anzahl_Spalten).
 */
Joelix_Fehler joelix_smatrix_fuelleZeile (Joelix_sMatrix M, int zeile, int znichtnull,
                                          double * werte, int * spalten);
/** Fordere die Anzahl der Zeilen an.
 * \param [in] M          Eine mit joelix_sMatrix_init initialisierte Matrix.
 * \return            Anzahl der Zeilen oder -1 bei Fehler.
 */
int joelix_smatrix_get_zeilen(Joelix_sMatrix M);

/** Fordere die Anzahl der Spalten an.
 * \param [in] M          Eine mit joelix_sMatrix_init initialisierte Matrix.
 * \return            Anzahl der Spalten oder -1 bei Fehler.
 */
int joelix_smatrix_get_spalten(Joelix_sMatrix M);

/** Ermoeglicht es einen nichtnull Eintrag, der mit 
 * joelix_smatrix_fuelleZeile gesetzt wurde, zu veraendern.
 *  \param [in] M          Eine mit joelix_sMatrix_init initialisierte Matrix.
 *  \param [in] zeile      Der Zeilenindex des zu aendernden Eintrags.
 *  \param [in] spalte     Der Spaltenindex des zu aendernden Eintrags.
 *  \param [in] wert       Der neue Wert.
 *  \return                F_ERFOLG bei Erfolg, sonst ein anderer Fehlercode.
 *  Diese Funktion darf nur aufgerufen werden, wenn vorher ein Aufruf
 *  von joelix_smatrix_fuelleZeile geschehen ist, bei deim zeile und spalte
 *  mit den Werten hier uebereinstimmen.
 */
  
Joelix_Fehler joelix_smatrix_aendernneintrag (Joelix_sMatrix M, int zeile,
                                              int spalte, double wert);

/** Berechnet b = Mx als Matrix-Vektor Multiplikation.
   \param [in]  M    Eine mit joelix_smatrix_neu erstellte Matrix.
   \param [in]  x    Ein mit joelix_vektor_neu erstellter Vektor. (input)
   \param [in,out]  b    Ein mit joelix_vektor_neu erstellter Vektor. (output)
   \return           b   b = Mx wird inplace berechnet.
   Warnung: b und x muessen verschiedene Vektoren sein.
 */
Joelix_Fehler joelix_smatvec (Joelix_Vektor b, Joelix_sMatrix M, Joelix_Vektor x);

/** Gebe eine sparse matrix auf der Konsole aus.
 *  \param [in] M    Eine mit joelix_smatrix_neu erstellte Matrix.
 *  \return          F_ERFOLG bei Erfolg, sonst ein anderer Fehlercode.
 */
Joelix_Fehler joelix_smatrix_print (const Joelix_sMatrix M);

/** Gibt den Speicher, der von einer Matrix benutzt wird, wieder frei.
 * \param [in,out] pM       Pointer auf eine von smatrix_neu erzeugte Matrix.
 *                          Ist nach Ausführen der Funktion NULL.
 *  \return          F_ERFOLG bei Erfolg, sonst ein anderer Fehlercode.
 */
Joelix_Fehler joelix_smatrix_loeschen (Joelix_sMatrix *pM);

#endif
