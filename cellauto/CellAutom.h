/*
* Copyright (C) 2002, 2003 Kevin McDermott <kevin@kidojo.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307, USA.
*/

#ifndef CELL_AUTO
#define CELL_AUTO 1

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

class CellAutom {

	public:

	CellAutom( char caColors[9], int iWidth, int iHeight, int iPixel);
	~CellAutom();

	// Print the image out in pgm format
	void vPrintImage(FILE *fOut, char cRandom);

	private:

	// given an upper scanline, return the corresponding current one
	char *cpCalcCurrSL(char *cpUpperSL, char *cpCurrSL);

    char caColors[9];      // Bitmask representing colors of the 8 
                           // possible color combinations of upper pixels

	char caaCombos[8][4];  // All the possible upper color combinations

    int iWidth;            // Width for Calculation Purposes
    int iHeight;           // Image Height
	int iImageWidth;       // Image Width

	int iPixel;            // Pixel size (actual pixels wide/high)
   
};

#endif
