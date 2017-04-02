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


#include "joelix_error.h"

const char* joelix_fehler_beschreibung_hidden [] = {
    "Erfolg.",
    "Nicht genuegend Speicher vorhanden.",
    "Ungueltige Parameter an Funktion uebergeben.",
    "Index nicht im zulaessigen Bereich.",
    "Falsche Dimensionen beim Vektor-Vektor Produkt.",
    "Falsche Dimensionen bei Vekto Kopie.",
    "Falsche Dimensionen beim Matrix-Vektor-Produkt.",
    "Falsche Dimensionen beim Matrix-Matrix-Produkt.",
    "Falsche Dimensionen: Matrix nicht quadratisch.",
    "Falsche Anzahl von nicht-Null Werten.",
    "Fehler beim schreiben oder lesen von Datei.",
    "Das CG-Verfahren terminiert nicht."
};

Joelix_Fehler joelix_fehler_code = 0;

const char* joelix_fehler_beschreibung( const Joelix_Fehler fehler_code )
{
    return joelix_fehler_beschreibung_hidden[(int)fehler_code];
}
