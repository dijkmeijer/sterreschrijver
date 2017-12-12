#include "starclass.h"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <getopt.h>


#define NO_OUTPUT 0
#define LIST 1
#define TRAIL 2
#define SIM 3
#define SETUTC 64
#define SETYEAR 32
#define SETMONTH 16
#define SETDAY 8
#define SETHOUR 4
#define SETMIN 2
#define SETSEC 1

using namespace std;
starclass *star;
int refstar;
double utime;
struct tm itime;
int timeset;

float bereik;
direction tmpstar;
int outputtype;
tm ltm;

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
int starnr = 24436;
int step = 3600;
float exposure = 3600.;


int main(int argc, char **argv) {
  outputtype = TRAIL  ; // default value, change to list or trail;
  // getopt header +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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
             if (output == "list")
               outputtype = LIST;
             if (output == "trail")
               outputtype = TRAIL;
             if (output == "sim")
               outputtype = SIM;
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
	  starnr=atoi(optarg);
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

  // end getopt header
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  if (outputtype != NO_OUTPUT) {

    int count;
    char s_az[20], s_hd[20];
    star = new starclass();
    // time_t ltm = ;

    //	time_t now = time(0);
    //	ltm = *localtime(&now);

    // star->setdate(ltm.tm_year + 1900, (short int)ltm.tm_mon,
    //               (short int)ltm.tm_mday,
    //               (short int)ltm.tm_hour + (short int)ltm.tm_min / 60. +
    //                   (short int)ltm.tm_sec / 3600.);
    //
    // //
    // //  cout << "timeset = " << timeset << endl;
    // if (timeset > 0) {
    //   if (timeset == SETYEAR | SETMONTH | SETDAY | SETHOUR | SETMIN | SETSEC) {
    //     //		cout << "OK" << endl;
    //     star->setdate(itime.tm_year, itime.tm_mon, itime.tm_mday, itime.tm_hour,
    //                   itime.tm_min, itime.tm_sec);
    //   } else {
    //     cout << "year, month, day and hour" << endl;
    //     return 1;
    //   }
    //   if (timeset == SETUTC) {
    //     star->setdate(utime);
    //   }
    // }
    star->setdate(year, month, day, hour, minute, second);
    star->setLocation(latitude, longitude);
    star->setMagnitude(magnitude);
    star->setExposure(exposure, step);
    star->setBereik(angle);
    if (star->setref(starnr)) {
      cout << "Geen ster in de catalogus" << endl;
      return 1;
    }
    //  cout << ltm->tm_year+1900 << " " << ltm->tm_mon+1 << " " << ltm->tm_mday
    //  << " " <<  ltm->tm_hour << " " << ltm->tm_min << endl;

    /*
       for(int i =0; i < count; i++) {

       printf("%f\t%f\t%d\t%s\n",star->star_list[i].az,
             star->star_list[i].hd,
             star->star_list[i].starnumber,
             star->star_list[i].starname);
       }
     */
    /*
       cout << "<select name=starlist>" << endl;
       for(int i =0; i < count; i++) {
       cout << "\t<option value = " << star->star_list[i].starnumber << " > " <<
       star->star_list[i].starname << " </option>" << endl;
       }
       cout << "<select>" << endl;
     */
    // ++++++++++++++++++++  output list +++++++++++++++++++++++++++++++++++++++
    if (outputtype == LIST) {
      printf("time %d %f\n", ltm.tm_sec, star->tjd);
      count = star->get_starlist();
      for (int i = 0; i < count; i++) {
        double x, y;
        // x=50.-sin((star->star_list[i].az)*PI/180.) * star->star_list[i].zd;
        // y=50.-cos((star->star_list[i].az)*PI/180.) * star->star_list[i].zd;
        x = star->star_list[i].x;
        y = star->star_list[i].y;
        cout << "<div class=StarLabel number=" << star->star_list[i].starnumber
             << " id=\"star\" x=" << x - 50 << " y=" << y - 50
             << " style=\"position: absolute; top: " << y << "%;  left: " << x
             << "%; \">" << star->star_list[i].starname << "<br>"
             << star->star_list[i].starnumber << "</div>" << endl;
        cout << "<img id=\"star\" x=" << x - 50 << " y=" << y - 50
             << " src=\"ster.png\" class=StarImg style=\"position: absolute; "
                "top: "
             << y - 3 << "%;  left: " << x - 3 << "%; \">" << endl;
      }
    }

    // ++++++++++++++++++++  output trail
    // +++++++++++++++++++++++++++++++++++++++
    if (outputtype == TRAIL) {
      star->calc_norm_trail();
    }
    // ++++++++++++++++++++  output sim +++++++++++++++++++++++++++++++++++++++
    if (outputtype == SIM) {
      // star->setExposure(3600.,star->stappen/2.);

      count = star->get_starlist();
      for (int i = 0; i < count; i++) {
        star->setref(star->star_list[i].starnumber);
        cout << star->schrijfster.star.starnumber << "  "
             << star->schrijfster.star.starname << endl;
        star->calc_norm_trail();

        // cout << "Time: " <<  setprecision(15) << star->tjd << endl;
      }
    }
    cout << "tjd = " << std::setprecision(12) << star->tjd << endl;
    time_t result = time(0);
    return 0; // input != NO_OUTPUT
  }
} // main
