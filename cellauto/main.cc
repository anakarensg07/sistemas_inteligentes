/*
* Copyright (C) 2002 Kevin McDermott <kevin@kidojo.com>
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

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "CellAutom.h"
using namespace std;

char *cpDec2Bin(int iNumber, char *cpBinStr) {
    int iQuotient = iNumber, iOldQuotient = 0;;
    int iRemainder = 0;
	char caBinary[64] = "";

    do {
        char caTmp[64];
        strcpy(caTmp, caBinary);
        iOldQuotient = iQuotient;
        iQuotient = (int)(iQuotient / 2);
        iRemainder = iOldQuotient - (iQuotient * 2);
        sprintf(caBinary, "%d%s", iRemainder, caTmp);
    } while (iQuotient);

	// Ensure we always return "one byte" (8 chars)
	memset (cpBinStr, '0', 8);
	char cPos = ( (strlen(caBinary) > 8) ? 0 : (8 - strlen(caBinary)) );
	strcpy(cpBinStr + cPos, caBinary); 

    return(cpBinStr);
}

void vUsage() {
	cerr << "Usage: cellatom <rule-set> <width> <height> <pixel-size> <rand>\n" <<
	        "	where\n" <<
	        "	<rule-set> is a number between 0 and 255\n" <<
	        "	  which coresponds to a bitmask which represents\n" <<
	        "	  white or black (0 or 1 respectivly) for each of\n" <<
	        "	  the 8 possible combinations of three upper colors\n" <<
	        "	  in a two color cellular atomata\n" <<
	        "	<width> the width in pixels the resulting image\n" <<
	        "	  (defaults to 800)\n" <<
	        "	<height> the height of the resulting image\n" <<
	        "	  (defaults to 600)\n" <<
	        "	<pixel-size> the width and height of each pixel\n" <<
			"	<rand> (value 0 or 1) indicates the first line will be random\n\n";
	exit(0);
}

int main(int argc, char **argv) {

    int iWidth = 800, iHeight = 600;    // Default image to 800x600
	int iPixel = 1;                     // Default pixel size is 1
    unsigned char cRule;                // User Entered rule
    char caBinRule[9];                  // Bitmask of rule
	CellAutom *Automata;
	char *cpGen;
	char cRandom = 0;

	if (argc < 2) {
		vUsage();
	}

	// Ensure the rule is a number
	for (cpGen = argv[1]; cpGen < (argv[1] + strlen(argv[1])); cpGen++) {
		if (!isdigit(*cpGen)) {
			vUsage();
		}	
	}
	
	cRule = atoi(argv[1]);

	if (argc > 2) {
		// Ensure the width is a number	
		for (cpGen = argv[2]; cpGen < (argv[2] + strlen(argv[2])); cpGen++) {
			if (!isdigit(*cpGen)) {
				vUsage();
			}	
		}
		iWidth = atoi(argv[2]);
	}
	if (argc > 3) {
		// Ensure the height is a number	
		for (cpGen = argv[3]; cpGen < (argv[3] + strlen(argv[3])); cpGen++) {
			if (!isdigit(*cpGen)) {
				vUsage();
			}	
		}
		iHeight = atoi(argv[3]);
	}
	if (argc > 4) {
		// Ensure the pixel width is a number	
		for (cpGen = argv[4]; cpGen < (argv[4] + strlen(argv[4])); cpGen++) {
			if (!isdigit(*cpGen)) {
				vUsage();
			}	
		}
		iPixel = atoi(argv[4]);
	}
	if (argc > 5) {
		if ( (strlen(argv[5]) != 1) || ((argv[5][0] != '0') &&
		     (argv[5][0] != '1')) ) {
			vUsage();
		}	
		else {
			if (argv[5][0] == '1') {
				cRandom = 1;	
			}
			else if (argv[5][0] == '0') {
				cRandom = 0;	
			}
		}
	}
	Automata = new CellAutom(cpDec2Bin(cRule, caBinRule),iWidth,iHeight,iPixel);

	Automata->vPrintImage(stdout, cRandom);

	return(0);
}
