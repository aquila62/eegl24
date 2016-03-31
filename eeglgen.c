/* eeglgen.c - random bit stream generator Version 1.0.0             */
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
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <time.h>
#include <sys/times.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include "eegl.h"

/* number of LFSR registers in the eegl generator */
#define STATES 2000

/* print syntax */
void putstx(char *pgm)
   {
   fprintf(stderr,"Usage: %s #states\n", pgm);
   fprintf(stderr,"Example: %s 2000\n", pgm);
   fprintf(stderr,"In this example, %s has 2000 states\n", pgm);
   exit(1);
   } /* putstx */

/* print one million bits to stdout */
void putblk(char *blk, int len)
   {
   int rslt;
   rslt = write(1,blk,len);
   if (rslt != len)
      {
      fprintf(stderr,"putblk: write error\n");
      exit(1);
      } /* write error */
   } /* putblk */

int main(int argc, char **argv)
   {
   int states;          /* number of LFSR registers in the eegl generator */
   unsigned int i;      /* output block length counter */
   char *p;             /* pointer to the output block */
   char *blk;           /* output bit stream */
   eefmt *ee;           /* eegl structure */
   if (argc != 2) putstx(*argv);      /* must have one parameter */
   states = atoi(*(argv+1));          /* convert parameter to integer */
   /* validate input parameter */
   if (states < 1)
      {
      fprintf(stderr,"main: parameter #states %s "
         "is too small\n", *(argv+1));
      putstx(*argv);
      } /* states is too small */
   if (states > STATES)
      {
      fprintf(stderr,"main: parameter #states %s "
         "is too large\n", *(argv+1));
      putstx(*argv);
      } /* states is too large */
   ee = (eefmt *) eeglinit(states);    /* initialize eegl generator */
   /***************************************/
   /* allocate memory for the output      */
   /* bit stream                          */
   /***************************************/
   blk = (char *) malloc(1048576 + 100);
   if (blk == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating blk\n");
      exit(1);
      } /* out of mem */
   /***************************************/
   /* point to the beginning of the output bit stream block */
   p = (char *) blk;
   i = 0;            /* initialize the length of the output block */
   /* the output bit stream is piped into a following program */
   /* when the down stream program ends, this program ends */
   while (1)         /* infinite loop */
      {
      i++;           /* counter for block length */
      /* append a random ASCII bit to the end of the output block */
      *p++ = eegl(ee) + 0x30;
      if (i >= 1048576)       /* if output block is filled */
         {
         putblk(blk,i);       /* write output block to stdout */
         i = 0;               /* reset block length to zero */
         p = (char *) blk;    /* point to beginning of output block */
         } /* output filled block */
      } /* for each random bit produced */
   /* the compiler requires a return statement */
   return(0);                 /* normal end of job */
   } /* main */
