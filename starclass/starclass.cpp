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

starclass::starclass()
{
    //ctor

    UCT_offset=1;
    UCT_offset=0;
    deltat = 61.0;
    setdate(2016, 05, 12, 04 , 12, 0);  // yyyy mm dd hh mm
    magnitude = 3.;    	// maximale magnitude v.d. ster
    bereik = 40.;       // hoek in graden tov zenith
    refstar=32349;		// referentie ster default
    refstar=24436;		// referentie ster default
    stappen=3600; 		// 3600 = 1 uur;
    focus=135;			//lens brandpunt
    motor_x=80.;   		// positie motor voor X beweging
    motor_y=80.; 		// positie motor voor X beweging
    Lijnen = new point[stappen];
    exposuretime=1.;    // 1 uur

    short int de_num;

    short int error = 0;

    double jd_beg, jd_end;



    // ********* Open the JPL ephemeris file.


		error = ephem_open ((char*)"JPLEPH", &jd_beg,&jd_end,&de_num);
    printf("error = %d\n", error);
    if (error==1) {
      printf("JPLEPH niet gevonden\n"); exit(1); }

    printf("JPLEPH gelezen\n");

    n_stars = read_cat();
    printf("cat gelezen\n");

    fixstar=11767;

    for(int i = 0; i < n_stars; i++)
        if (star[i].star.starnumber==fixstar)
            poolster=star[i];

    setref(refstar);

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

// ****************************************************************************
// read catalogus met sterren (is deel geselecteerd op naam en helderheid)
// ****************************************************************************

int starclass::read_cat()
{
  FILE *fp;
  printf("ḧierin?");
    fp=fopen("cat_entry.cat", "rb");
    if(fp==NULL)
      {printf("geen cat_entry.cat\n");
      exit(1);
    }
    fseek( fp, 0L, SEEK_END );
    n_stars=ftell(fp)/sizeof(star_rec);
    rewind(fp);
    star=(star_rec*)malloc(n_stars*sizeof(star_rec));
    fread(star, sizeof(star_rec), n_stars, fp);
    fclose(fp);
    return n_stars;
}

// ****************************************************************************
// set tijd en datum (sec toevoegen!)
// ****************************************************************************

int starclass::setdate(short int fy, short int fm, short int fd, short int fh, short int fmin, short int fsec)
{
	tjd=0;
    y=fy;
    m=fm;
    d=fd;
    h=fh;
    min=fmin;
    sec=fsec;
    tjd=julian_date(y,m,d, h+min/60.+sec/3600.)-UCT_offset*HOUR_PART;
    return 0;
}

int starclass::setdate(short int fy, short int fm, short int fd, float fh)
{
	tjd=0;
    y=fy;
    m=fm;
    d=fd;
    h=fh;
    tjd=julian_date(y,m,d,h)-UCT_offset*HOUR_PART;
    return 0;
}

// ****************************************************************************
// set huidige locatie
// ****************************************************************************

int starclass::setLocation(double latitude, double longitude)
{
	make_on_surface(latitude, longitude,0.,10,0.,&geo_loc);
	return 0;
}

int starclass::setMagnitude(float mag){
	magnitude = mag;
	return 0;
}

// ****************************************************************************
// set referentie ster voor startrail
// ****************************************************************************

int starclass::setref(int HIP)
{
    refstar=HIP;
    int error = 1;
    for(int i = 0; i < n_stars; i++)
        if (star[i].star.starnumber==refstar)
        { schrijfster=star[i];
		  error = 0;
	    }
    return error;
}

// ****************************************************************************
// set de belichtingstijd
// ****************************************************************************

int starclass::setExposure(double etime, int step)
{
	stappen = step;
	exposuretime=etime/3600.0;
	return 0;
}


// ****************************************************************************
// bereken alle sterren helderder dan "magnitude"
// ****************************************************************************

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

// ****************************************************************************
// ??
// ****************************************************************************

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

        // error=topo_star(t, deltat, &(schrijfster.star), &geo_loc, accuracy,&ra, &dec);
        // cout << ra << " " << dec << " " << error << endl;


        equ2hor(t,deltat,accuracy,0.0,0.0,&geo_loc, ra, dec,1,&d.zd,&d.azd,&rar,&decr);


        d.azh=d.azd*24./360.;

        // cout << "geoloc " << geo_loc.latitude << endl;
        // cout << d.azd << " " << d.zd << error << endl;
        // printf("az %9.4f, elev %6.4f\n", az, 90.0-zd);
        // printf("%f\n", t);
    }
    return d;
}

// ****************************************************************************
// ??
// ****************************************************************************

direction starclass::get_pool()
{
    direction d;
    short int error = 0;
    short int accuracy = 0;
    double ra, dec;
    double rar, decr;
    double pt=tjd+exposuretime/48.;
    error = app_star(pt, &(poolster.star), accuracy, &ra, &dec);
//	error=topo_star(pt, deltat, &(poolster.star), &geo_loc, accuracy,&ra, &dec);
    equ2hor(pt,deltat,accuracy,0.0,0.0,&geo_loc, ra, dec,1,&d.zd,&d.azd,&rar,&decr);
    d.azh=d.azd*24./360.;
    // cout << "poolster : "<< d.zd << ", " << d.azd << endl;


    // printf("az %9.4f, elev %6.4f\n", az, 90.0-zd);
    // printf("%f\n", t);
    return d;
}

// ****************************************************************************
// bereken beweging op sterpositie en dxf
// ****************************************************************************

int starclass::calc_trail()
{
    double t;
	double xmax=-10000;
	double ymax=-10000;
	double xmin=10000;
	double ymin=10000;
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
	    //cout << (ster_dir.azd+180.) - 360. << " " << 90.-ster_dir.zd << endl;
        s1.set(ster_dir.azd,90.-ster_dir.zd);

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
        cout << "c " << t*q2.x << " " << t*q2.y << endl;

    }
	cout << "t " << fabs(trailsize) << endl;
	cout << "r " << R.x << " " <<  R.y << " "  << R.z << " " <<  R.w << endl;
      //  cout << poolster.star.starnumber << endl;
      //  cout << schrijfster.star.starnumber << endl;
    return 0;
}

// ****************************************************************************
// bewegingsfactor x motorexcenter
// ****************************************************************************

double starclass::factor_x()
{
    return motor_x/focus;
}

// ****************************************************************************
// bewegingsfactor y motorexcenter)
// ****************************************************************************

double starclass::factor_y()
{
    return motor_y/focus;
}

// ****************************************************************************
// bereken verplaatsing camera ??
// ****************************************************************************

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
