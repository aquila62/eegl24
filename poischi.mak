# poischi.mak Version 1.0.0 - Compile Poisson Chi Square
# Copyright (C) 2016   aquila62 at github.com

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

# this version of poischi.c is for 24-bit LFSR registers

OBJ=poischi.o \
	eeglinit.o \
	eegl.o \
	eeglunif.o

CC=gcc

CFLAGS=-c -Wall -O2

LDFLAGS=-lgsl -lgslcblas -lm

poischi:		$(OBJ)
	$(CC) -Wall -O2 $(OBJ) -o poischi $(LDFLAGS)

poischi.o:		poischi.c
	$(CC) $(CFLAGS) poischi.c

eeglinit.o:		eeglinit.c
	$(CC) $(CFLAGS) eeglinit.c

eegl.o:			eegl.c
	$(CC) $(CFLAGS) eegl.c

eeglunif.o:		eeglunif.c
	$(CC) $(CFLAGS) eeglunif.c

clean:
	rm -f $(OBJ) poischi
