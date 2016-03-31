/* eeglint.c - generate a random number integer Version 1.0.0        */
/* Copyright (C) 2016 aquila62 at github.com                         */

/* This program is free software; you can redistribute it and/or     */
/* modify it under the terms of the GNU General Public License as    */
/* published by the Free Software Foundation; either version 2 of    */
/* the License, or (at your option) any later version.               */

/* This program is distributed in the hope that it will be useful,   */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of    */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the      */
/* GNU General Public License for more details.                      */

/* You should have received a copy of the GNU General Public License */
/* along with this program; if not, write to:                        */

   /* Free Software Foundation, Inc.                                 */
   /* 59 Temple Place - Suite 330                                    */
   /* Boston, MA 02111-1307, USA.                                    */

/********************************************************/
/* The LFSR in this generator comes from the following  */
/* website http://www.xilinx.com/support/documentation/ */
/* application_notes/xapp052.pdf                        */
/********************************************************/

/* this subroutine generates a random integer from zero */
/* up to a limit                                        */
/* the limit may be positive or negative                */
/* For performance reasons, the input parameter is not  */
/* validated                                            */
/* See eeglpwr.c for generating an unsigned integer     */

#include <gsl/gsl_rng.h>
#include "eegl.h"

int eeglint(eefmt *ee, int limit)
   {
   int intgr;                        /* output integer */
   double num;                       /* uniform random number */
   num = eeglunif(ee);      /* generate uniform random number */
   /* multiply num by the limit and truncate */ 
   /* this produces an integer from zero up to the limit */
   intgr = (int) floor(num * (double) limit);
   return(intgr);           /* return the integer */
   } /* eeglint */
