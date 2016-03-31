/* eeglinit.c - random number generator initialization Version 1.0.0 */
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

/* This version of the eegl generator uses 24-bit LFSR     */
/* This initialization routine is based on date/time/ticks */

#include <gsl/gsl_rng.h>
#include "eegl.h"

eefmt *eeglinit(int states)
   {
   int sixteenmeg;             /* 2^24 */
   unsigned int dttk;          /* combined date and #ticks */
   unsigned int *stp,*stq;     /* pointer into state array */
   time_t now;                 /* current date and time */
   clock_t clk;                /* current number of ticks */
   struct tms t;               /* structure used by times() */
   eefmt *ee;                  /* eegl structure */

   /***************************************************/
   /* allocate memory for eegl structure */
   /***************************************************/
   ee = (eefmt *) malloc(sizeof(eefmt));
   if (ee == NULL)
      {
      fprintf(stderr,"eeglinit: out of memory "
      "allocating ee\n");
      exit(1);
      } /* out of memory */
   if (states < 1)
      {
      fprintf(stderr,"eeglinit: input parameter states %d "
         "is too small\n", states);
      exit(1);
      } /* states too small */
   if (states > 2000)
      {
      fprintf(stderr,"eeglinit: input parameter states %d "
         "is too large\n", states);
      exit(1);
      } /* states too large */
   ee->states = states; /* save the number of LFSR registers */

   /***************************************************/
   /* allocate memory for eegl state array */
   /***************************************************/
   ee->state = (unsigned int *)
   malloc(sizeof(unsigned int)*ee->states);
   if (ee->state == NULL)
      {
      fprintf(stderr,"initeegl: out of memory "
      "allocating ee->state\n");
      exit(1);
      } /* out of memory */

   /* declare the GSL random number generator as taus  */
   ee->r = (gsl_rng *) gsl_rng_alloc(gsl_rng_taus);
   /* get clock ticks since boot                       */
   clk = times(&t);
   /* get date & time                                  */
   time(&now);
   /* combine date, time, and ticks into a single UINT */
   dttk = (unsigned int) (now ^ (clk << 16));
   /* allocate the GSL taus random number generator    */
   ee->r = (gsl_rng *) gsl_rng_alloc(gsl_rng_taus);
   /* initialize the GSL taus random number generator  */
   /* to date,time,#ticks                              */
   gsl_rng_set(ee->r, dttk);

   /***************************************************/
   /* initialize the state array to random values     */
   /***************************************************/
   sixteenmeg = 65536 * 256;       /* sixteen meg 16+8=24 */
   stp = (unsigned int *) ee->state;
   stq = (unsigned int *) ee->state + ee->states;
   while (stp < stq)
      {
      /* set to random 24-bit UINT */
      *stp++ = gsl_rng_uniform_int(ee->r, sixteenmeg);
      } /* for each element in ee->state */

   /***************************************************/
   /* after this subroutine you may initialize the    */
   /* state array to your own values, if you wish     */
   /* to do regression testing.                       */
   /* Use the above 6 lines as an example of how to   */
   /* initialize the array                            */
   /***************************************************/
   /* return the eegl structure                       */
   /***************************************************/
   return(ee);
   } /* eeglinit subroutine */
