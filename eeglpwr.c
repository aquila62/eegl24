/* eeglpwr.c - random number generator Version 1.0.0                 */
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

/* this subroutine generates a random unsigned integer    */
/* from 1 to 32 bits                                      */
/* For performance reasons the parameter is not validated */
/* See eeglint.c for generating a random signed integer   */

#include <gsl/gsl_rng.h>
#include "eegl.h"

unsigned int eeglpwr(eefmt *ee, int bits)
   {
   int i;                   /* loop counter */
   unsigned int intgr;      /* output UINT */
   intgr = 0;               /* initialize the output UINT */
   i = bits;                /* set the loop counter */
   /* to produce the UINT, shift the UINT one bit to the left */
   /* and add a zero or one to the low order bit              */
   while (i--)              /* UINT loop */
      {
      intgr = (intgr << 1) | eegl(ee);   /* see above comment */
      } /* for each bit in intgr */
   return(intgr);           /* return random unsigned integer */
   } /* eeglpwr */
