#include <iostream>
#include "starclass.h"
#include <ctime>


using namespace std;
starclass *star;
int main(int argc, char **argv){
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
		cout << "<a href ><img src=\"ster.png\" height=4% width=4% style=\"position: absolute; top: " << y-2 << "%;  left: " << x-2 << "%; \"></a>"<< endl;
	}
	//cout << "</div>";
	return 0;
}
