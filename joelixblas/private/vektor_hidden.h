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


#ifndef __JOELIX_VEKTOR_HIDDEN_H__
#define __JOELIX_VEKTOR_HIDDEN_H__

struct Joelix_Vektor_t
{
 int laenge;
 double * werte;
};

#endif
