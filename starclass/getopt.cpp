#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <iostream>

using namespace std;

/* Flag set by ‘--verbose’. */
static int verbose_flag;

string output="list";
float longitude = 5.48818;
float latitude = 51.43075;
float magnitude=3.;
float angle = 40.;
int year = 2017;
int month = 12;
int day = 11;
int hour = 22;
int minute = 47;
int second = 0;
int star = 24436;
int step = 3600;
float exposure = 3600.;

int main (int argc, char **argv)
{
  int c;

  while (1)
    {
      static struct option long_options[] =
       {
          {"help",      no_argument, 0, 'h'},	
          {"output",    required_argument, 0, 'o'},
          {"longitude", required_argument, 0, 'l'},
          {"latitude",  required_argument, 0, 'm'},
          {"magnitude", required_argument, 0, 'v'},
          {"angle",     required_argument, 0, 'a'},
          {"year",      required_argument, 0, 'y'},
          {"month",     required_argument, 0, 'M'},
          {"day",       required_argument, 0, 'd'},
          {"hour",      required_argument, 0, 'H'},
          {"min",       required_argument, 0, 'i'},
          {"sec",       required_argument, 0, 's'},
          {"star",      required_argument, 0, 'S'},
          {"step",      required_argument, 0, 'p'},
          {"exposure",  required_argument, 0, 'e'},
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      c = getopt_long (argc, argv, "ho:l:m:v:a:y:M:d:H:i:s:S:p:e:",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;


      switch (c)
        {
        case 'h': // output
          cout << "Usage: "<< argv[0] << " [-holmvayMdHisSpe]" << endl;
          cout << "\t-h --help: this info" << endl;
          cout << "\t-o --output: output-type [list, trail, sim]" << endl;
          cout << "\t-l --longitude: longitude of location" << endl;
          cout << "\t-m --latitude: latitude of location" << endl;
          cout << "\t-v --magnitude: minimum magnitude of stars in list" << endl;
          cout << "\t-a --angle: angle from zenith " << endl;
          cout << "\t-y --year    : set date," << endl;
          cout << "\t-M --month   : " << endl;
          cout << "\t-d --day     : " << endl;
          cout << "\t-H --hour    : use offset for" << endl;
          cout << "\t-i --minute  : setup of equipment." << endl;
          cout << "\t-s --second  :" << endl;
          cout << "\t-S --star: star of interest for writing" << endl;
          cout << "\t-p --step: number of steps in startrail" << endl;
          cout << "\t-e --exposure: exposuretime" << endl;
          exit(0);		
          break;
        case 'o': // output
	  output = optarg;	
          break;

        case 'l': // longitude
	  longitude = atof(optarg);
          break;

        case 'm': // latitude
	  latitude = atof(optarg);
          break;

        case 'a': // angle
	  angle = atof(optarg);
          break;

        case 'v': //magnitude
	  magnitude = atof(optarg);
          break;

        case 'y': // year
	  year = atoi(optarg);	
          break;

        case 'M': // month
	  month = atoi(optarg);
          break;

        case 'd': // day
	  day = atoi(optarg);
		
          break;

        case 'H': // hour
	  hour = atoi(optarg);
          break;

        case 'i': // minute
          minute = atoi(optarg);
          break;

        case 's': // second
	  second = atoi(optarg);
          break;

        case 'S': // star
	  star=atoi(optarg);
          break;

        case 'p': // steps
	  step = atoi(optarg);
          break;

        case 'e': // exposure time
	  exposure =  atof(optarg);
          break;

        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          abort ();
        }
    }

   cout << "output type = " << output << endl;
   cout << "longitude = " << longitude << endl;
   cout << "latitude = " << latitude << endl;
   cout << "zenith angle = " << angle << endl;
   cout << "magnitude = " << magnitude << endl;
   cout << "year = " << year << endl;
   cout << "month = " << month << endl;
   cout << "day = " << day << endl;
   cout << "hour = " << hour << endl;
   cout << "minute = " << minute << endl;
   cout << "second = " << second << endl;
   cout << "star of interrest = " << star << endl;
   cout << "number of steps = " << step << endl;
   cout << "exposure time = " <<exposure << endl;
  exit (0);
}
