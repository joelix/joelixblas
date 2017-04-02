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


#ifndef __JOELIX_MATRIX_HIDDEN_H__
#define __JOELIX_MATRIX_HIDDEN_H__

#include "joelix_error.h"

struct Joelix_sparse_Matrix_t
{
  int n, m; /* Zeilen und Spaltenanzahl */
  int nnE;  /* Anzahl der nicht-null Eintraege */
  double * werte; /* Hat Laenge nnE. Speichert die nicht-null Eintraege */
  int * zeilen_akk; /* Hat Laenge n+1. An Stelle i steht die gesamt Anzahl an nicht-null
                       Eintraegen bis zu Zeile i-1. 
                       D.h. werte[zeilen_akk[i]] ist der erste nicht-null Eintrag
                       in Zeile i. */
  int * spalten_ind; /* Hat Laenge nnE. An Stelle i steht der Spaltenindex des i-ten
                        Elementes in werte, also des i-ten nicht-null Elements. */
};

/* Ein detailierter Output auf der Konsole zum debuggen */
Joelix_Fehler joelix_smatrix_print_debug (struct Joelix_sparse_Matrix_t * M);

#endif
