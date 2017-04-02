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


#ifndef __JOELIX_VEKTOR_H__
#define __JOELIX_VEKTOR_H__

#include "joelix_error.h"

/** \file vektor.h Hier werden die Funktionen fuer das Vektor-Interface
  festgelegt. */ 


/* TODO: Ergebniss nach links */

/** Der Datentyp fuer Vektoren. */
typedef struct Joelix_Vektor_t * Joelix_Vektor;

/** Initialisiert einen Vektor der Laenge n und fuellt diesen mit Nullen auf.
   \param [in,out] pVektor Pointer auf den Vektor (vom Typ Joelix_Vektor) der
                    initialisiert werden soll.
   \param [in] n       Laenge des zu erstellenden Vektors.
   \return         F_ERFOLG bei Erfolg, sonst ein anderer Fehlercode.
 */
Joelix_Fehler joelix_vektor_init (Joelix_Vektor *pVektor, int n);

/** Setze alle Eintraege eines Vektor auf den Wert 0.
   \param [in] x      Ein mit joelix_vektor_init initialisierter Vektor.
   \return F_ERFOLG bei Erfolg, sonst ein anderer Fehlercode.
 */
Joelix_Fehler joelix_vektor_null (Joelix_Vektor x);

/** Gebe die Laenge eines Vektors aus.
   \param [in] x      Ein mit joelix_vektor_init initialisierter Vektor.
   \return        Die Laenge des Vektors x oder -1, bei nicht
                   initialisiertem Vektor.
 */
int joelix_vektor_laenge (Joelix_Vektor x);

/** Setze den i-ten Eintrag eines Vektors auf einen gegebenen
   Wert.
   \param [in,out] x      Ein mit joelix_vektor_init initialisierter Vektor.
   \param [in] i      Ein index innerhalb des Vektors, 0 <= i < n.
   \param [in] wert   Der Wert auf den der i-te Eintrag von x gesetzt
                   werden soll.
   \return        F_ERFOLG bei Erfolg, sonst ein anderer Fehlercode.
 */
Joelix_Fehler joelix_vektor_seti (Joelix_Vektor x, int i, double wert);

/** Lese den i-ten Eintrag eines Vektors aus.
   \param [in] x      Ein mit joelix_vektor_init initialisierter Vektor.
   \param [in] i      Ein index innerhalb des Vektors, 0 <= i < n.
   \param [in] wert   Pointer auf einen allokierten double.
                   Dieser double wird auf den i-ten Eintrag von x gesetzt.
   \return         F_ERFOLG bei Erfolg, sonst ein anderer Fehlercode.
 */
Joelix_Fehler joelix_vektor_geti (Joelix_Vektor x, int i, double *wert);

/** Berechnet y = x.
  \param [in] x          Ein mit joelix_vektor_init initialisierter Vektor.
  \param [in,out] y      Ein mit joelix_vektor_init initialisierter Vektor mit gleicher Laenge wie x.
  \return        F_ERFOLG bei Erfolg, sonst ein anderer Fehlercode.
*/
Joelix_Fehler joelix_vektor_copy (Joelix_Vektor y, Joelix_Vektor x);

/** Berechne x = alpha * x fuer einen Vektor x und einen Skalar alpha.
   \param [in] alpha  Skalar.
   \param [in,out]  x      Ein mit joelix_vektor_init initialisierter Vektor.
   \return        F_ERFOLG bei Erfolg, sonst ein anderer Fehlercode.
 */
Joelix_Fehler joelix_vektor_ax (Joelix_Vektor x, double alpha);

/** Berechnet y = alpha * x + y fuer Vektoren x und y und einen 
   reellen Skalar alpha.
   \param [in] alpha  Skalar.
   \param [in] x      Ein mit joelix_vektor_init initialisierter Vektor.
   \param [in,out] y      Ein mit joelix_vektor_init initialisierter Vektor mit gleicher Laenge wie x.
   \return        F_ERFOLG bei Erfolg, sonst ein anderer Fehlercode.
 */
Joelix_Fehler joelix_vektor_axpy (Joelix_Vektor y, Joelix_Vektor x, double alpha);

/** Berechnet das Skalarprodukt zweier Vektoren.
   \param [out] produkt Ein Pointer auf eine initialisierte Double Variable.
   \param [in] x      Ein mit joelix_vektor_init initialisierter Vektor.
   \param [in] y      Ein mit joelix_vektor_init initialisierter Vektor mit gleicher Laenge wie x.
   \return        F_ERFOLG bei Erfolg, sonst ein anderer Fehlercode.
 */
Joelix_Fehler joelix_vektor_dot (double * produkt, Joelix_Vektor x, Joelix_Vektor y);

/** Gebe einen Vektor auf der Konsole aus.
   \param [in] x      Ein mit joelix_vektor_init initialisierter Vektor.
   \return       F_ERFOLG bei Erfolg, sonst ein anderer Fehlercode.
 */
Joelix_Fehler joelix_vektor_print (Joelix_Vektor x);

/** Gebe einen Vektor in eine Datei aus.
   \param [in] x      Ein mit joelix_vektor_init initialisierter Vektor.
   \param [in] filename Der Name der Outputdatei. Die Datei wird ueberschrieben,
                   falls sie existiert.
   \return        F_ERFOLG bei Erfolg, sonst ein anderer Fehlercode.
 */
Joelix_Fehler joelix_vektor_print_tofile (Joelix_Vektor x, char * filename);

/** Gibt den Speicher, der von einem Vektor benutzt wird, wieder frei.
   \param [in,out] pVektor  Pointer auf einen von joelix_vektor_init initialiserter Vektor.
                     Ist nach Ausführen der Funktion NULL.
   \return        F_ERFOLG bei Erfolg, sonst ein anderer Fehlercode.
 */
Joelix_Fehler joelix_vektor_loeschen (Joelix_Vektor * pVektor);

#endif
