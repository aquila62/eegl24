/*
tstnc.c Version 1.0.0 - Generate Random Data Pattern in Curses
Copyright (C) 2016   aquila62 at github.com

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to:

	Free Software Foundation, Inc.
	59 Temple Place - Suite 330
	Boston, MA  02111-1307, USA.
*/

/* This program uses the 24-bit version of the eegl generator */

/* this program tests eeglint() and eeglunif() */
/* by producing a random pattern of ASCII characters */
/* on a curses screen */

/* press 'r' to reset */
/* press 'q' to exit */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <gsl/gsl_rng.h>
#include "eegl.h"

#define SCRW 80.0
#define SCRH 24.0

/* number of LFSR registers */
#define STATES 2000

/* print syntax */
void putstx(char *pgm)
   {
   fprintf(stderr,"Usage: %s #states\n", pgm);
   fprintf(stderr,"Example: %s 2000\n", pgm);
   fprintf(stderr,"In this example, %s has 2000 states\n", pgm);
   exit(1);
   } /* putstx */

/* initialize curses */
void initcrss()
   {
   initscr();
   cbreak();
   noecho();
   nonl();
   intrflush(stdscr,FALSE);
   nodelay(stdscr,TRUE);
   } /* initcrss */

int main(int argc, char **argv)
   {
   int states;             /* number of states in eegl generator */
   int ch;                 /* ASCII character to display */
   int x;                  /* column coordinate 0-79 */
   int y;                  /* row    coordinate 0-23 */
   eefmt *ee;              /* eegl structure */
   if (argc != 2) putstx(*argv);    /* must have one parameter  */
   states = atoi(*(argv+1));    /* convert parameter to integer */
   /* valid parameter range is 1-2000 */
   if (states < 1)
      {
      fprintf(stderr,"main: parameter #states %s "
         "is too small\n", *(argv+1));
      putstx(*argv);
      } /* states is too small */
   if (states > 2000)
      {
      fprintf(stderr,"main: parameter #states %s "
         "is too large\n", *(argv+1));
      putstx(*argv);
      } /* states is too large */
   ee = (eefmt *) eeglinit(states);    /* initialize eegl   */
   initcrss();                         /* initialize curses mode */
   /* terminate loop with 'q' or 'escape'                   */
   while(1)                            /* infinite loop     */
      {
      y = eeglint(ee,SCRH);       /* set row coordinate to 0-23 */
      /* do not use row 23 column 79 */
      /* set column coordinate to 0-79 */
      if (y == 23)
         x = eeglint(ee,SCRW-1);
      else
         x = eeglint(ee,SCRW);
      /* position cursor at x,y coordinate */
      move(y,x);
      /* generate a random ASCII character */
      ch = eeglint(ee,95) + 33;
      /* display random ASCII character at position x,y */
      addch(ch);
      refresh();         /* display the new screen */
      ch = getch();      /* test keyboard for interrupt */
      /* quit if 'escape' or 'q' */
      if (ch == 0x1b) /* ESCAPE */
         break;
      if (ch == 'q') /* quit */
         break;
      /* reset screen to blank if 'r' */
      if (ch == 'r') /* reset */
         {
         clear();
         refresh();
         } /* reset */
      }
   endwin();           /* de-activate curses mode */
   free(ee->state);    /* free state array */
   free(ee);           /* free eegl structure */
   return(0);          /* normal eoj */
   } /* main */
