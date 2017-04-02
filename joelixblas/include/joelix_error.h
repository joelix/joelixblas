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


#ifndef __JOELIX_ERROR_H__
#define __JOELIX_ERROR_H__

/** \file joelix_error.h Definiert den Rueckgabetyp \a Joelix_Fehler. */

/** Der Fehlertyp, welcher als Rueckgabewert fast aller Funktionen dient. */
typedef enum {
    F_ERFOLG = 0, /**< Alles it gut, kein Fehler. */
    F_KEIN_SPEICHER, /**< Speicherfehler */
    F_FALSCHE_PARAMETER, /**< Parameterfehler */
    F_FALSCHER_INDEX,
    F_FALSCHE_DIMENSIONEN_VEKTOR_VEKTOR,
    F_FALSCHE_DIMENSIONEN_VEKTOR_KOPIE,
    F_FALSCHE_DIMENSIONEN_MATRIX_VEKTOR,
    F_FALSCHE_DIMENSIONEN_MATRIX_MATRIX,
    F_FALSCHE_DIMENSIONEN_MATRIX_NICHT_QUADRATISCH,
    F_FALSCHE_ANZAHL_NICHT_NULL_WERTE,
    F_FILEIO_FEHLER,
    F_CG_TERMINIERT_NICHT
} Joelix_Fehler;

/** Variable, welche immer den zuletzt erzeugten Fehlercode speicher. */
extern Joelix_Fehler joelix_fehler_code;

/** Gebe eine kurze Beschreibung einen Fehlers als string zurueck.
   \param [in] Fehler   Der Fehler.
   \return              Ein String, welcher eine Beschreibung des Fehlers
                        enthaelt.
 */
const char* joelix_fehler_beschreibung( const Joelix_Fehler Fehler);

#endif
