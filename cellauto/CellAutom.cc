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
*
*
* -- Thanks to Ray Whitmer for his bug fixes --
*/


#include "CellAutom.h"

/* 
 * Constructor
 */
CellAutom::CellAutom(char caColors[9], int iWidth, int iHeight, int iPixel) {

	strcpy(this->caColors, caColors);
	this->iPixel = iPixel;
	this->iHeight = (int)(iHeight / iPixel);
	this->iWidth = iWidth + this->iHeight * 2;

	this->iImageWidth = (int)(iWidth / iPixel);


	// Set all 8 possible color combinations of above three pixels in UpperSL
	strcpy(this->caaCombos[0], "000");
	strcpy(this->caaCombos[1], "001");
	strcpy(this->caaCombos[2], "010");
	strcpy(this->caaCombos[3], "011");
	strcpy(this->caaCombos[4], "100");
	strcpy(this->caaCombos[5], "101");
	strcpy(this->caaCombos[6], "110");
	strcpy(this->caaCombos[7], "111");

}

/* 
 * Destructor
 */
CellAutom::~CellAutom() {

}

// Calculate current scanline, given the previous (upper) scanline
char *CellAutom::cpCalcCurrSL( char *cpUpperSL, char *cpCurrSL) {

	for (int i = 1; i < (this->iWidth - 1); i++) {
		char caUpper[4];
		caUpper[0] = ((cpUpperSL[i - 1] == 0) ? '0' : '1');
		caUpper[1] = ((cpUpperSL[i] == 0)     ? '0' : '1');
		caUpper[2] = ((cpUpperSL[i + 1] == 0) ? '0' : '1');
		caUpper[3] = '\0';
		for (char cRule = 0; cRule < 8; cRule++) {
			if (!strcmp(caUpper, this->caaCombos[cRule])) {
				// in rules, 1 is black
				cpCurrSL[i] = ((this->caColors[cRule] == '1') ? 0 : 255);
			}	
		}
	}

	return(cpCurrSL);
}


// Print image to File Descriptor
void CellAutom::vPrintImage(FILE *fOut, char cRandom) {

	// Offset within calculative width to begin showing Image Width
	int iOffset = (int)(iWidth / 2) - (int)(iImageWidth / 2);

	// Create the upper scanline the specified width, with a black dot in
	// the middle of the line
	char *cpUpperSL = new char[this->iWidth];
	memset(cpUpperSL, 255, this->iWidth);

	// Make the first scanline either randomly black and white, or 
	// a single black pixel in the middle
	if (cRandom) {
		srand(time(NULL));
		for (int i = iOffset; 
		     i < (iOffset + this->iImageWidth); i++) {
			cpUpperSL[i] = (int)((rand() / (RAND_MAX + 1.0)) + .5);
		}
	}
	else {
		cpUpperSL[(int)(this->iWidth / 2)] = 0;
	}

	char *cpCurrSL = new char[this->iWidth];
	memset(cpCurrSL, 255, this->iWidth);

	// Print out Image Header
	fprintf( fOut, "P5\n%d %d\n255\n", (this->iImageWidth * iPixel), 
	         (this->iHeight * iPixel) );


	for (int i = 0; i < this->iHeight; i++) {
		char *cpGen;

		cpCurrSL = cpCalcCurrSL(cpUpperSL, cpCurrSL);

		if (iPixel == 1) {
			fwrite(cpUpperSL + iOffset, this->iImageWidth, 1, fOut);
		}
		else {
			for (int pY = 0; pY < iPixel; pY++) {
				for (int j = 0; j < iImageWidth; j++) {
					for (int pX = 0; pX < iPixel; pX++) {
						fwrite(cpUpperSL + iOffset + j, sizeof(char), 1, fOut);
					}
				}
			}
		}
		
		// Swap Current to Upper
		cpGen = cpUpperSL;
		cpUpperSL = cpCurrSL;
		cpCurrSL = cpGen;
	}

	delete(cpUpperSL);
	delete(cpCurrSL);
}
