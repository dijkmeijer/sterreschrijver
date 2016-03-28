#include <iostream>
#include <stdio.h>
#include "starclass.h"
#include <ctime>
#include <boost/program_options.hpp>

using namespace std;
starclass *star;
int main(int argc, char **argv){
	float latitude, longitude;
	char Mes[125];
	sprintf(Mes, "Allowed options for %s", argv[0]);
	boost::program_options::options_description d(Mes);
    d.add_options()
      ("help,h",
        "produce this help message")
      ("latitude,m",
         boost::program_options::value<float>(),
         "Latitude of location (meridian) in gg.dddddd north positive, south negative")      
	  ("longitude,l",
         boost::program_options::value<float>(),
         "Longitude of location in gg.dddddd; 0.0 < L < 360.0")
      ("date,d",         
	     boost::program_options::value<float>(),
         "Date and time of this moment in  UTC");
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

  if (m.count("latitude"))
  {
      latitude = m["latitude"].as<float>();
  }
  
   if (m.count("longitude"))
  {
      longitude = m["longitude"].as<float>();
  }
	int count;
	char s_az[20], s_hd[20];
	star = new starclass(365);
	time_t now = time(0);
	tm *ltm = localtime(&now);
	
	star->setdate(ltm->tm_year+1900, 
				  (short int)ltm->tm_mon+1, 
				  (short int)ltm->tm_mday,
				  (short int)ltm->tm_hour, 
				  (short int)ltm->tm_min);
	star->setLocation(latitude, longitude);
				  
	//  cout << ltm->tm_year+1900 << " " << ltm->tm_mon+1 << " " << ltm->tm_mday << " " <<  ltm->tm_hour << " " << ltm->tm_min << endl;
	count = star->get_starlist();
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
	for(int i =0; i < count; i++) {
		double x, y;
		//cout << star->star_list[i].az << " " << star->star_list[i].zd << endl;
		x=50.-sin((star->star_list[i].az)*3.14/180.) * star->star_list[i].zd ;
		y=50.-cos((star->star_list[i].az)*3.14/180.) * star->star_list[i].zd;
		cout << "<div style=\"position: absolute; top: " <<y << "%;  left: " << x << "%; \">" << star->star_list[i].starname << " </div>" << endl;
		//cout << "<a href=\"info.php?x="<<x-50<<"&y="<<y-50<<"\"><img src=\"ster.png\" height=4% width=4% style=\"position: absolute; top: " << y-2 << "%;  left: " << x-2 << "%; \"></a>"<< endl;
		cout << "<img id=\"star\" x="<<x-50<<" y="<<y-50<<" src=\"ster.png\" height=4% width=4% style=\"position: absolute; top: " << y-2 << "%;  left: " << x-2 << "%; \">"<< endl;
	}
	//cout << "</div>";
	return 0;
}
