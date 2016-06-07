#include <iostream>
#include <stdio.h>
#include "starclass.h"
#include <ctime>
#include <boost/program_options.hpp>


#define NO_OUTPUT 0
#define LIST 1
#define TRAIL 2
#define SETYEAR 8
#define SETMONTH 4
#define SETDAY 2
#define SETHOUR 1

using namespace std;
starclass *star;	
double exposuretime;
int step;
int refstar;
float utime;
struct tm itime;
int timeset;

int outputtype;

int main(int argc, char **argv){
	float latitude, longitude, magnitude;
	outputtype = NO_OUTPUT;  // default value, change to list or trail;
	timeset=0;
// Boost header +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	char Mes[125];
	sprintf(Mes, "Allowed options for %s", argv[0]);
	boost::program_options::options_description d(Mes);
    d.add_options()
      ("help,h",
        "produce this help message")
      ("output,o",       
	     boost::program_options::value<string>(),
         "Output of program \n'list' starlist or \n'trail' for startrail")
      ("latitude,m",
         boost::program_options::value<float>(),
         "Latitude of location (meridian) in gg.dddddd \nnorth positive, south negative")      
	  ("longitude,l",
         boost::program_options::value<float>(),
         "Longitude of location in gg.dddddd\n0.0 < Lon < 360.0")
      ("magnitude,v", 
		boost::program_options::value<float>(),
         "minimal magnitude of the stars")
      ("time,t", 
		boost::program_options::value<float>(),
         "set time and date in Julian UTC")
      ("year,Y", 
		boost::program_options::value<int>(),
         "set year")
      ("month,M", 
		boost::program_options::value<int>(),
         "set month")
      ("day,D", 
		boost::program_options::value<int>(),
         "set day")
      ("hour,H", 
		boost::program_options::value<float>(),
         "set hour; minutes en seconds as decimals")
      ("utc,u", 
		boost::program_options::value<float>(),
         "set UTC time")
      ("angle,a",         
		boost::program_options::value<float>(),
         "angle from zenith for list of visible stars")
      ("star,s", 
		boost::program_options::value<int>(),
         "set star for startrail")
      ("step,p",         
	     boost::program_options::value<int>(),
         "set number of steps")
      ("exposure,e",         
	     boost::program_options::value<double>(),
         "set exposuretime in seconds")      
      ;

  boost::program_options::variables_map m;
  boost::program_options::store(
  boost::program_options::parse_command_line(
      argc, argv, d), m);
  boost::program_options::notify(m);

  //If one of the options is set to 'help'...
  if (m.count("help"))
  {
    //Display the options_description
    std::cout << d << "\n";
	return 0;
  }

 if (m.count("output"))
  {
      string SO = m["output"].as<string>();
      
      if (SO == "list") outputtype = LIST;
      if (SO == "trail") outputtype = TRAIL;
  }
  else outputtype = TRAIL;

  if (m.count("latitude"))
  {
      latitude = m["latitude"].as<float>();
      
  } 
  else latitude = 51.43075;
  
   if (m.count("longitude"))
  {
      longitude = m["longitude"].as<float>();     
  }
  else longitude = 5.48818;
  
   if (m.count("utc"))
  {
      utime = m["utc"].as<float>();
  }
  else{
   time_t now = time(0);
   tm *ltm = localtime(&now);
	}
	
   if (m.count("year"))
  {
      itime.tm_year = m["year"].as<int>();
      timeset = timeset | SETYEAR;
  }
  else itime.tm_year=2016;
   if (m.count("month"))
  {
      itime.tm_mon = m["month"].as<int>();
      timeset = timeset | SETMONTH;
  }
  else itime.tm_mon=1;
   if (m.count("day"))
  {
      itime.tm_mday = m["day"].as<int>();
      timeset = timeset | SETDAY;
  }   
  else itime.tm_mday=1;
   if (m.count("hour"))
  {
      itime.tm_hour= m["hour"].as<float>();
      timeset = timeset | SETHOUR;
  }
  else itime.tm_hour=0;
  
  if (m.count("magnitude"))
  {
      magnitude = m["magnitude"].as<float>();
  }
  else magnitude = 3;
    
  if (m.count("star"))
  {
     refstar = m["star"].as<int>();
  }
  else refstar = 24436;  
  
  if (m.count("exposure"))
  {
      exposuretime = m["exposure"].as<double>();
  }
  else exposuretime =3600.0;  
  
  if (m.count("step"))
  {
       step = m["step"].as<int>();
  }
  else  step = 3600;
  
// end BOOST header   +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
  
  if (outputtype != NO_OUTPUT){
	
  
	int count;
	char s_az[20], s_hd[20];
	star = new starclass();
	time_t now = time(0);
	/* star->setdate(ltm->tm_year+1900, 
				  (short int)ltm->tm_mon+1, 
				  (short int)ltm->tm_mday,
				  (short int)ltm->tm_hour, 
				  (short int)ltm->tm_min,
				  (short int)ltm->tm_sec);
	*/
	cout << "timeset = " << timeset << endl;
	if(timeset > 0) {
	if (timeset == SETYEAR | SETMONTH | SETDAY | SETHOUR) {
//		cout << "OK" << endl;
		star->setdate(itime.tm_year, itime.tm_mon, itime.tm_mday, itime.tm_hour);
	} 
	else {
		cout << "year, month, day and hour" << endl;
		return 1;
	}
}
  
  
 
 
 	star->setLocation(latitude, longitude);
	star->setMagnitude(magnitude);
	star->setExposure(exposuretime, step);		
	if	(star->setref(refstar)){
		cout << "Geen ster in de catalogus" << endl;
		return 1;
	}
	//  cout << ltm->tm_year+1900 << " " << ltm->tm_mon+1 << " " << ltm->tm_mday << " " <<  ltm->tm_hour << " " << ltm->tm_min << endl;
	
	
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
		cout << "\t<option value = " << star->star_list[i].starnumber << " > " << star->star_list[i].starname << " </option>" << endl;
	}
	cout << "<select>" << endl;
    */
// ++++++++++++++++++++  output list +++++++++++++++++++++++++++++++++++++++
    if (outputtype == LIST){
	count = star->get_starlist();
	for(int i =0; i < count; i++) {
		double x, y;
		//cout << star->star_list[i].az << " " << star->star_list[i].zd << endl;
		x=50.-sin((star->star_list[i].az)*3.14/180.) * star->star_list[i].zd ;
		y=50.-cos((star->star_list[i].az)*3.14/180.) * star->star_list[i].zd;
		cout << "<div style=\"position: absolute; top: " <<y << "%;  left: " << x << "%; \">" << star->star_list[i].starname << " </div>" << endl;
		//cout << "<a href=\"info.php?x="<<x-50<<"&y="<<y-50<<"\"><img src=\"ster.png\" height=4% width=4% style=\"position: absolute; top: " << y-2 << "%;  left: " << x-2 << "%; \"></a>"<< endl;
		cout << "<img id=\"star\" x="<<x-50<<" y="<<y-50<<" src=\"ster.png\" height=4% width=4% style=\"position: absolute; top: " << y-2 << "%;  left: " << x-2 << "%; \">"<< endl;
	}
	
	cout << "</div>";
	}
// ++++++++++++++++++++  output trail +++++++++++++++++++++++++++++++++++++++
	if (outputtype == TRAIL)
	{
			star->calc_trail();
    }

    }
	return 0;
}
