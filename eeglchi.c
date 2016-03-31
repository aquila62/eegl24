/* eeglchi.c - eegl chi square test Version 1.0.0                    */
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

/* this is the 24-bit version of the eegl generator */

#include <stdio.h>
#include "eegl.h"

/* number of LFSR states */
#define STATES 2000

int main()
   {
   int i;                         /* loop counter */
   double *p,*q;                  /* pointers to tally array */
   double tally[32];              /* chi square counts */
   double expected = 1024.0;      /* expected chi square count */
   double diff;                   /* expected - actual count */
   double diffsq;                 /* difference squared */
   double chisq = 0.0;            /* chi square total */
   eefmt *ee;                     /* Eegl structure */
   ee = (eefmt *) eeglinit(STATES);
   /**********************************/
   /* initialize tally array to zero */
   /**********************************/
   p = (double *) tally;
   q = (double *) tally + 32;
   while (p < q) *p++ = 0.0;
   /********************************************/
   /* tally 16384 4-bit samples in 16 counters */
   /********************************************/
   i = 16384;
   while (i--)
      {
      int indx;
      indx = eeglpwr(ee,4);      /* 4 bit sample 0-15 */
      tally[indx] += 1.0;        /* tally the sample */
      } /* for each sample */
   /******************************************/
   /* add up the chi square from 16 counters */
   /******************************************/
   p = (double *) tally;
   q = (double *) tally + 16;
   i = 16;
   while (i--)
      {
      diff = expected - *p;             /* expected - actual */
      diffsq = diff * diff;             /* square the difference */
      chisq += (diffsq / expected);     /* add to chi square total */
      printf("i %d actual %.0f expected %.0f diff %.0f\n",
         16-i, *p, expected, diff);
      p++;
      } /* for each tally */
   /****************/
   /* print report */
   /****************/
   printf("Total samples 16384\n");
   printf("Chi square %f\n", chisq);
   printf("15 degrees of freedom\n");
   printf("Chi square at  5%c is  7.261\n", '%');
   printf("Chi square at 95%c is 24.996\n", '%');
   free(ee->state);
   free(ee);
   return(0);            /* normal eoj */
   } /* main */
