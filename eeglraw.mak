#  eeglraw.mak - Compile eeglraw.c Version 1.0.0
#  Copyright (C) 2016 aquila62 at github.com

#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License as
#  published by the Free Software Foundation; either version 2 of
#  the License, or (at your option) any later version.

#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to:

   #  Free Software Foundation, Inc.
   #  59 Temple Place - Suite 330
   #  Boston, MA 02111-1307, USA.

#--------------------------------------------------------
#  The LFSR in this generator comes from the following
#  website http://www.xilinx.com/support/documentation/
#  application_notes/xapp052.pdf
#--------------------------------------------------------

# this program feeds ranwlk.c
# use tstwlk.sh to test this program with ranwlk.c

OBJ=eeglraw.o \
	eeglinit.o \
	eegl.o \
	eeglpwr.o

CC=gcc

CFLAGS=-c -Wall -O2

LDFLAGS=-lgsl -lgslcblas -lm

eeglraw:			$(OBJ)
		$(CC) -Wall -O2 $(OBJ) -o eeglraw $(LDFLAGS)

eeglraw.o:			eeglraw.c
		$(CC) $(CFLAGS) eeglraw.c

eeglinit.o:			eeglinit.c
		$(CC) $(CFLAGS) eeglinit.c

eegl.o:				eegl.c
		$(CC) $(CFLAGS) eegl.c

eeglpwr.o:			eeglpwr.c
		$(CC) $(CFLAGS) eeglpwr.c

clean:
		rm -f $(OBJ) eeglraw
