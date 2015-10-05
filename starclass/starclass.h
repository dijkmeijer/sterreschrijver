#ifndef STARCLASS_H
#define STARCLASS_H

extern "C" {
#include "Novasextra.h"
}

#include "point.h"
#include "Quaternion.h"
#define N_STARS 3
#define N_TIMES 4


#define HOUR_PART 0.041666666
class direction
{
    public:
    direction(){dir_type=0;};
    double azh;
    double azd;
    double zd;
    int dir_type;
};

class star_list_rec {
	public:
	double az;
	double zd;
	double hd;
	char starname[SIZE_OF_OBJ_NAME];
	int starnumber;
};

class starclass
{
public:
    /** Default constructor */
    starclass(int stap);
    /** Default destructor */
    virtual ~starclass();
    int starlist(double start); 
    double exposuretime; // belichtingstijd
    int stappen;         // aantalpunten in trail
	char *starcat_file;
	char *ephemeris_file; 
    star_rec *star;      // lijst van alle benoemde sterren
	star_list_rec *star_list;  // lijst van sterre binnen zichtbare deel van de hemel.
    star_rec schrijfster; // ster om te schrijven
    star_rec poolster;   // "vaste" referentie naar noorden

    point *Lijnen;       // lijst met punten voor baan ster op negatief
    double trailsize;
    int n_stars;         // aantal sterren in star - lijst
    int read_cat();      // lees catalog sla records op in stars
    on_surface geo_loc;
    Quaternion<> R;
    orientatie schrijverstand;
    double tjd;          // tijd in "Julian date"
    short int m, d, y;   // tijd variabelen: year month, day, hour, minute
    int h, min;
    int setdate(short int fy, short int fm, short int fd, short int fh, short int fmin);
	int setLocation(double latitude, double longitude);
    double UCT_offset;   // offset i.v.m. locale tijd
    double deltat;       // delta t offset i.v.m. verschil UTC julian Date
    double magnitude;    // maximale magnitude v.d. ster
    double bereik;       // bereik waarin de sterren worden weergeven in  graden vanaf zenith
    int get_starlist();
    int refstar;
    int fixstar;
    int setref(int HIP);
    double focus;
    double motor_x;       // positie motor voor X beweging
    double motor_y;       // positie motor voor X beweging
    double factor_x();
    double factor_y();
    direction get_postionlist();
    direction get_position(int it);
    direction get_pool();
    int calc_trail();

protected:
private:
};



int angle_desc( char *s, double d);


#endif // STARCLASS_H
