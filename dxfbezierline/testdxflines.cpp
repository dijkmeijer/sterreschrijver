/*
 * @file main.cpp
 */

/*****************************************************************************
**  $Id: main.cpp 3591 2006-10-18 21:23:25Z andrew $
**
**  This is part of the dxflib library
**  Copyright (C) 2000-2001 Andrew Mustun
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU Library General Public License as
**  published by the Free Software Foundation.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Library General Public License for more details.
**
**  You should have received a copy of the GNU Library General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "dxfbezierline.h"

void usage();
void ConvertDXFBezier();

int steps=3600;
double textlength=10.;
string f_name="willekeurige_tekst.dxf";

/*
 * @brief Main function for DXFLib test program.
 *
 * @param argc Number of delimited items on command line,
 *		including program name.
 * @param argv Pointer to array of command line items
 *
 * @retval 0 if missing input file argument or
 *		file couldn't be opened
 * @retval 1 if file opened
 */

int main(int argc, char** argv) {


// Boost header +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int c;
while (1)
	{
		static struct option long_options[] =
		 {
				{"help",      no_argument, 0, 'h'},
				{"file",    required_argument, 0, 'f'},
				{"length", required_argument, 0, 'l'},
				{"steps",  required_argument, 0, 'p'},
				{0, 0, 0, 0}
			};
		/* getopt_long stores the option index here. */
		int option_index = 0;

		c = getopt_long (argc, argv, ":hf:l:p:",
										 long_options, &option_index);

		/* Detect the end of the options. */
		if (c == -1)
			break;

		switch (c)
			{
			case 'h': // output
				cout << "Usage: "<< argv[0] << " [-holmvayMdHisSpe]" << endl;
				cout << "\t-h --help: this info" << endl;
				cout << "\t-f --file: Filename of dxf file" << endl;
				cout << "\t-l --length: lengte van de trail" << endl;
				cout << "\t-p --steps: aantal punten in trail" << endl;

				exit(0);
				break;
			case 'f': // output
					 f_name = optarg;
				break;

			case 'l': // longitude
					textlength = atof(optarg);
				break;

			case 'p': // latitude
	 				steps = atoi(optarg);
				break;

	    }
 }
 cout << "output type = " << f_name << endl;
 cout << "length = " << textlength << endl;
 cout << "steps = " << steps << endl;


// end BOOST header   ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// main function   ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    ConvertDXFBezier();

    return 0;
}


/*
 * @brief Prints error message if file name not specified as command
 * line argument.
 */
void usage() {
    std::cout << "\nUsage: test <DXF file>\n\n";
}


void ConvertDXFBezier() {
    // Load DXF file into memory:
    //std::cout << "Reading file " << file << "...\n";

    dxfbezier2linesClass* creationClass = new dxfbezier2linesClass((string) f_name, steps, textlength);

    //    creationClass -> verschuif(file);
    cout.precision(12);
    for(int i =0; i < steps-1; i++)
    cout << creationClass->Lijnen[i].x << " " << creationClass->Lijnen[i].y << endl;
   // cout << creationClass -> min_X << " " << creationClass -> max_X << " " << creationClass -> min_Y << " " << creationClass -> max_Y << " " << endl;
//    delete dxf;
    delete creationClass;
}
