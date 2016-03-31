/* eeglunif.c - uniform random number generator 0-1 Version 1.0.0    */
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

/* this subroutine produces a uniform random number     */
/* from zero to one                                     */

#define BITS 53

#include <gsl/gsl_rng.h>
#include "eegl.h"

double eeglunif(eefmt *ee)
   {
   int i;                  /* loop counter for # of bits */
   double num;             /* random number from 0-1     */
   num = 0.0;              /* initialize output          */
   i = BITS;               /* set loop counter           */
   /* the uniform random number is shifted 1 bit to the right */
   /* then a zero or one bit is added as the high order bit   */
   /* in the mantissa.                                        */
   /* This is repeated 53 times for a 53 bit mantissa         */
   while (i--)             /* mantissa loop              */
      {
      if (eegl(ee)) num = (num * 0.5) + 0.5;    /* if one bit */
      else num *= 0.5;                          /* else zero bit */
      } /* for each bit in mantissa */
   return(num);            /* return uniform random number */
   } /* eeglunif */
