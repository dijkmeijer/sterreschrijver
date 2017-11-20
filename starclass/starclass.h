#ifndef STARCLASS_H
#define STARCLASS_H

extern "C" {
#include "Novasextra.h"
}

#include "Quaternion.h"
#include "point.h"
#define N_STARS 3
#define N_TIMES 4

#define HOUR_PART 0.041666666

class direction {
public:
  direction() { dir_type = 0; };
  double azh;
  double azd;
  double zd;
  double x;
  double y;
  int dir_type;
};

class camera_dir {
public:
  double pan;  // rotatie om z zenith as
  double roll; // kanteling opzij camera (eerste laag)
  double tilt; // kanteling naar voren (tweede laag)
  camera_dir calc_camera(double latitude, direction *ster_dir);
  camera_dir calc_camera(double x1, double y1, double x2, double y2,
                         double latitude);
};
// class position
// {
//     public:
//     double x;
//     double y;
//     position convert(direction star);
// };

class star_list_rec {
public:
  double az;
  double zd;
  double hd;
  double x;
  double y;
  char starname[SIZE_OF_OBJ_NAME];
  int starnumber;
};

class starclass {
public:
  /** Default constructor */
  starclass();
  /** Default destructor */
  virtual ~starclass();
  int starlist(double start);
  double exposuretime; // belichtingstijd
  int stappen;         // aantalpunten in trail
  char *starcat_file;
  char *ephemeris_file;
  star_rec *star; // lijst van alle benoemde sterren
  star_list_rec
      *star_list;       // lijst van sterre binnen zichtbare deel van de hemel.
  star_rec schrijfster; // ster om te schrijven
  star_rec poolster;    // "vaste" referentie naar noorden

  point *Lijnen; // lijst met punten voor baan ster op negatief
  double trailsize;
  int n_stars;        // aantal sterren in star - lijst
  int read_cat();     // lees catalog sla records op in stars
  on_surface geo_loc; // positie op aarde
  Quaternion<> R;     // Quaternion.h
  orientatie
      schrijverstand; // Quaternion.h verdraaing van de schrijver over 3 assen
  double tjd;         // tijd in "Julian date"
  short int m, d, y;  // tijd variabelen: year month, day, hour, minute
  short int h, min, sec;
  int setdate(short int fy, short int fm, short int fd, short int fh,
              short int fmin, short int fsec);
  int setdate(short int fy, short int fm, short int fd, float fh);
  int setdate(double utc);
  int setLocation(double latitude, double longitude);
  int setMagnitude(float mag);
  int setExposure(double etime, int step);
  int setBereik(double _bereik);
  double UCT_offset; // offset i.v.m. locale tijd
  double deltat;     // delta t offset i.v.m. verschil UTC julian Date
  double magnitude;  // maximale magnitude v.d. ster
  double bereik; // bereik waarin de sterren worden weergeven in  graden vanaf
                 // zenith
  int get_starlist();
  int refstar;
  int fixstar; // vaste ster aan firnament = poolsters
  int setref(int HIP);
  double focus;
  double motor_x; // positie motor voor X beweging
  double motor_y; // positie motor voor X beweging
  double factor_x();
  double factor_y();
  direction get_postionlist();
  direction get_position(int it);
  direction get_pool();
  int calc_trail();
  int calc_norm_trail();

protected:
private:
};

int angle_desc(char *s, double d);

#endif // STARCLASS_H
