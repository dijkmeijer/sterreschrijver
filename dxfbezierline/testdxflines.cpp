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
#include <boost/program_options.hpp>

#include "dxfbezierline.h"

void usage();
void ConvertDXFBezier();

int steps;
double textlength;
string f_name;

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
	char Mes[125];
	sprintf(Mes, "Allowed options for %s", argv[0]);
	boost::program_options::options_description d(Mes);
    d.add_options()
      ("help,h",
        "produce this help message")
      ("file,f",
	     boost::program_options::value<string>()->required(),
         "Set name of DXF file to be converted  ")
      ("textlength,l",
         boost::program_options::value<float>(),
         "Set length of text")
	  ("steps,s",
         boost::program_options::value<int>(),
         "Set number of steps in text");

  boost::program_options::variables_map m;
  boost::program_options::store(
  boost::program_options::parse_command_line(
   argc, argv, d), m);
  boost::program_options::notify(m);

  //If one of the options is set to 'help'...
  if (m.count("help"))
  {
    //Display the options_description
    std::cout << "option" << d << "\n";
	return 0;
  }

  if (m.count("file"))
  {
      f_name = m["file"].as<string> ();
  }

  if (m.count("textlength"))
  {
     textlength = m["textlength"].as<float>();

  }
  else textlength = 10.;

   if (m.count("steps"))
  {
      steps = m["steps"].as<int>();
  }
  else steps = 3600;


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
