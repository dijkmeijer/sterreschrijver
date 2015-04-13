#include <iostream>
#include "starclass.h"

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include "eph_manager.h"
#include "novas.h"
#include "../Novasextra/Novasextra.h"
}

using namespace std;

starclass::starclass(int stap)
{
    //ctor

    UCT_offset=1;
    deltat = 61.0;
    setdate(2013, 01, 07, 22 , 45);  // yyyy mm dd hh mm
    magnitude = 3.;    // maximale magnitude v.d. ster
    bereik = 40.;
    refstar=21421;
    stappen=stap; //3600;
    focus=135;
    motor_x=80.;    // positie motor voor X beweging
    motor_y=80.; // positie motor voor X beweging
    Lijnen = new point[stappen];
    exposuretime=1.;

    short int de_num;

    short int error = 0;

    double jd_beg, jd_end;
    /*
       Open the JPL ephemeris file.
    */

    try{
		error = ephem_open ((char*)"JPLEPH", &jd_beg,&jd_end,&de_num);}
	catch(int e)
    {
           printf ("Error %d from ephem_open\n", error);
    }

    // printf ("JPL Ephemeris DE%d open. jd_beg = %10.2f  jd_end = %10.2f\n",
     //             de_num, jd_beg, jd_end);
    // printf ("\n");
    
//    make_on_surface(51.43075, 5.48818,0.,22.65,1010.,&geo_loc);
    make_on_surface(51.43075, 5.48818,0.,10,0.,&geo_loc);

    n_stars=read_cat();

    fixstar=11767;
    for(int i = 0; i < n_stars; i++)
        if (star[i].star.starnumber==fixstar)
            poolster=star[i];


}


starclass::~starclass()
{
    ephem_close ();//dtor
    delete Lijnen;
	delete star;
	delete star_list;
}

int starclass::starlist(double start)
{
    return 0;
}

int starclass::read_cat()
{
    FILE *fp;
	try {
    fp=fopen("cat_entry.cat", "rb");
	}

	catch(int e){}
    fseek( fp, 0L, SEEK_END );
    n_stars=ftell(fp)/sizeof(star_rec);
    rewind(fp);
    star=(star_rec*)malloc(n_stars*sizeof(star_rec));
    fread(star, sizeof(star_rec), n_stars, fp);
    fclose(fp);
    return n_stars;
}


int starclass::setdate(short int fy, short int fm, short int fd, short int fh, short int fmin)
{
    y=fy;
    m=fm;
    d=fd;
    h=fh;
    min=fmin;
    tjd=julian_date(y,m,d, h+min/60.)-UCT_offset*HOUR_PART;
    return 0;
}

int starclass::get_starlist()
{
    short int error;
    short int accuracy = 0;
    double  ra, dec;
    double zd, az, rar, decr;
	char s[100];
	int count = 0;
    for(int i = 0; i < n_stars; i++)
    {
		error = app_star(tjd, &(star[i].star), accuracy, &ra, &dec);
        equ2hor(tjd,deltat,accuracy,0.0,0.0,&geo_loc, ra, dec,1,&zd,&az,&rar,&decr);
        if((zd < bereik) && star[i].Vmag < magnitude)
			count++;
	}
	star_list=(star_list_rec*)malloc(count*sizeof(star_list_rec)); // reserveer ruimte voor alle sterren binnen specificatie
	count=0;
        
	for(int i = 0; i < n_stars; i++)
    {
		/*cout << star[i].star.starnumber << " " <<
         		star[i].star.starname  << " " <<  
         		star[i].star.ra  << " " <<  
         		star[i].star.dec  << " " <<  
         		star[i].star.promora  << " " <<  
         		star[i].star.promodec  << " " << 
         		star[i].star.parallax  << " " <<  
				star[i].Vmag << endl;
		*/
        error = app_star(tjd, &(star[i].star), accuracy, &ra, &dec);
        equ2hor(tjd,deltat,accuracy,0.0,0.0,&geo_loc, ra, dec,1,&zd,&az,&rar,&decr);
        if((zd < bereik) && star[i].Vmag < magnitude)
        {
				star_list[count].az = az;
				star_list[count].zd = zd;
				star_list[count].hd = 90.-zd;
				strcpy(star_list[count].starname, star[i].star.starname);
				star_list[count].starnumber = star[i].star.starnumber;
				
				/*cout << star_list[count].az << "\t"
				     << star_list[count].zd << "\t"
				     << star_list[count].hd << "\t"
				     << star_list[count].starname <<"\t"
				     << star_list[count].starnumber << endl;
				*/
				count++;
				
							
        }
    }
    return count;
}

direction starclass::get_postionlist()
{
    direction d;
    short int error = 0;
    short int accuracy = 0;
    double  ra, dec;
    double rar, decr;
    double stepsize=exposuretime/stappen/24.;
    double t=tjd-exposuretime/48.;
    for(int i = 0; i < n_stars; i++)
        if (star[i].star.starnumber==refstar)
        {
            for(int j=0; j<stappen; j++)
            {
                error = app_star(t, &(star[i].star), accuracy, &ra, &dec);
                equ2hor(t,deltat,accuracy,0.0,0.0,&geo_loc, ra, dec,1,&d.zd,&d.azh,&rar,&decr);
                printf("az %9.4f, elev %6.4f\n", d.azh, 90.0-d.zd);
                 printf("%f\n", t);
                t+=stepsize;
            }
        }
    return d;
}

int starclass::setref(int HIP)
{
    refstar=HIP;
    for(int i = 0; i < n_stars; i++)
        if (star[i].star.starnumber==refstar)
            schrijfster=star[i];
    return 0;
}

direction starclass::get_position(int it)
{
    direction d;
    short int error = 0;
    short int accuracy = 0;
    double  ra, dec;
    double rar, decr;
    double stepsize=exposuretime/stappen/24.;
    double t=tjd+it*stepsize;

    if(it < stappen)
    {
        error = app_star(t, &(schrijfster.star), accuracy, &ra, &dec);
        equ2hor(t,deltat,accuracy,0.0,0.0,&geo_loc, ra, dec,1,&d.zd,&d.azd,&rar,&decr);
        d.azh=d.azd*24./360.;
        // printf("az %9.4f, elev %6.4f\n", az, 90.0-zd);
        // printf("%f\n", t);
    }
    return d;
}

direction starclass::get_pool()
{
    direction d;
    short int error = 0;
    short int accuracy = 0;
    double ra, dec;
    double rar, decr;
    double pt=tjd+exposuretime/48.;
    error = app_star(pt, &(poolster.star), accuracy, &ra, &dec);
    equ2hor(pt,deltat,accuracy,0.0,0.0,&geo_loc, ra, dec,1,&d.zd,&d.azd,&rar,&decr);
    d.azh=d.azd*24./360.;
// cout << "poolster : "<< d.zd << ", " << d.azd << endl;


    // printf("az %9.4f, elev %6.4f\n", az, 90.0-zd);
    // printf("%f\n", t);
    return d;
}

int starclass::calc_trail()
{
    double t;

    Quaternion<> x(0,1,0,0);
    Quaternion<> y(0,0,1,0);
    Quaternion<> z(0,0,0,1);
    direction ster_dir = get_position(stappen/2.);
    direction pool_dir=get_pool();
    Sphere<> s1(ster_dir.azd,90.-ster_dir.zd);
    Sphere<> s2(pool_dir.azd,90.-pool_dir.zd);
    Quaternion<> q1(s1);
    Quaternion<> q2(s2);
    R=calc_orientatie(q1, q2, &schrijverstand);

    for(int i=0; i<stappen; i++)
    {
        ster_dir=get_position(i);

        s1.set(ster_dir.azd,90.-ster_dir.zd);
        //  cout << ster.azd << "," << 90.-ster.zd << endl;
        q1.set(s1);
        // cout << "q1 " << q1 << endl;
        q2=~R*q1*R;
        //   printf("%9.6f %9.6f %9.6f %9.6f\n", (double)q2.w, (double)q2.x,(double)q2.y,(double)q2.z);
        //cout << "q2 " << q2 << endl;
        t=focus/q2.z;
        Lijnen[i].x=t*q2.x;
        Lijnen[i].y=t*q2.y;
        if(i==0)
        {
            trailsize=-t*q2.x;
        }
        if(i == stappen-1)
        {
            trailsize+=t*q2.x;
        }
        // cout << t*q2.x << "," << t*q2.y << endl;
    }

    return 0;
}

double starclass::factor_x()
{
    return motor_x/focus;
}


double starclass::factor_y()
{
    return motor_y/focus;
}

int angle_desc(char *s, double d){
	double dec;
	int angle,min, sec;
	angle = floor(d);
	d-=angle;
	min=floor(60*d);
	d*=60;
	d-=min;
	sec=floor(60*d);
	sprintf(s, "%d°%d\'%d\" ", angle, min, sec);
	return 1;

}
