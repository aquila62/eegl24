/* eegl.h - random number generator header file Version 1.0.0 */
/* Copyright (C) 2016 aquila62 at github.com */

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

/* the following includes are used especially by the    */
/* initialization routine                               */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>
#include <math.h>
#include <gsl/gsl_rng.h>

typedef struct eeglstruct {
   int states;               /* number of states */
   int ofst;                 /* offset into state array */
   int out;                  /* output from the state */
   unsigned int *state;      /* state array */
   gsl_rng *r;               /* GSL RNG eg taus */
   } eefmt;

eefmt *eeglinit(int states);           /* initialization routine */
int eegl(eefmt *ee);                   /* random bit generator */
double eeglunif(eefmt *ee);            /* random number 0-1 */
int eeglint(eefmt *ee, int limit);     /* random integer 0-limit */
unsigned int eeglpwr(eefmt *ee, int bits); /* random # 0-32 bits */
