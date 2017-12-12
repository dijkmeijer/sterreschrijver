#include "starclass.h"
#include <iostream>
#include <math.h>
extern "C" {
#include "../Novasextra/Novasextra.h"
#include "eph_manager.h"
#include "novas.h"
#include <stdio.h>
#include <stdlib.h>
}

using namespace std;

// position position::convert(direction star)
// {
//     position sterPos;
//     x=sterPos.x=50.-sin(star.azd*PI/180.) * star.zd;
//     y=sterPos.y=50.-cos(star.azd*PI/180.) * star.zd;
//     return sterPos;
// }

starclass::starclass() {
  // ctor

  UCT_offset = 1;
  UCT_offset = 0;
  deltat = 61.0;
  setdate(2016, 05, 12, 04, 12, 0); // yyyy mm dd hh mm
  magnitude = 3.;                   // maximale magnitude v.d. ster
  bereik = 40.;                     // hoek in graden tov zenith
  refstar = 32349;                  // referentie ster default
  refstar = 24436;                  // referentie ster default
  stappen = 3600;                   // 3600 = 1 uur;
  focus = 135;                      // lens brandpunt
  motor_x = 80.;                    // positie motor voor X beweging
  motor_y = 80.;                    // positie motor voor X beweging
  Lijnen = new point[stappen];
  exposuretime = 1.; // 1 uur

  short int de_num;

  short int error = 0;

  double jd_beg, jd_end;

  // ********* Open the JPL ephemeris file.

  error = ephem_open((char *)"JPLEPH", &jd_beg, &jd_end, &de_num);
  printf("error = %d\n", error);
  if (error == 1) {
    printf("JPLEPH niet gevonden\n");
    exit(1);
  }

  printf("JPLEPH geladen\n");

  n_stars = read_cat();

  printf("cat geladen\n");

  fixstar = 11767;

  for (int i = 0; i < n_stars; i++)
    if (star[i].star.starnumber == fixstar)
      poolster = star[i];

  setref(refstar);
}

starclass::~starclass() {
  ephem_close(); // dtor
  delete Lijnen;
  delete star;
  delete star_list;
}

int starclass::starlist(double start) { return 0; }

// ****************************************************************************
// read catalogus met sterren (is deel geselecteerd op naam en helderheid)
// ****************************************************************************

int starclass::read_cat() {
  FILE *fp;
  fp = fopen("cat_entry.cat", "rb");
  if (fp == NULL) {
    printf("cat_entry.cat  niet gevonden\n");
    exit(1);
  }
  fseek(fp, 0L, SEEK_END);
  n_stars = ftell(fp) / sizeof(star_rec);
  rewind(fp);
  star = (star_rec *)malloc(n_stars * sizeof(star_rec));
  fread(star, sizeof(star_rec), n_stars, fp);
  fclose(fp);
  printf("%d\n", n_stars);
  return n_stars;
}

// ****************************************************************************
// set tijd en datum (sec toevoegen!)
// ****************************************************************************

int starclass::setdate(short int fy, short int fm, short int fd, short int fh,
                       short int fmin, short int fsec) {
  tjd = 0;
  y = fy;
  m = fm;
  d = fd;
  h = fh;
  min = fmin;
  sec = fsec;
  tjd = julian_date(y, m, d, h + min / 60. + sec / 3600.) -
        UCT_offset * HOUR_PART;
  return 0;
}

int starclass::setdate(short int fy, short int fm, short int fd, float fh) {
  tjd = 0;
  y = fy;
  m = fm;
  d = fd;
  h = fh;
  tjd = julian_date(y, m, d, h) - UCT_offset * HOUR_PART;
  return 0;
}

int starclass::setdate(double utc) {
  cout << "utc = " << utc << endl;

  return 0;
}

// ****************************************************************************
// set huidige locatie
// ****************************************************************************

int starclass::setLocation(double latitude, double longitude) {
  make_on_surface(latitude, longitude, 0., 10, 0., &geo_loc);
  return 0;
}

int starclass::setMagnitude(float mag) {
  magnitude = mag;
  return 0;
}

// ****************************************************************************
// set referentie ster voor startrail
// ****************************************************************************

int starclass::setref(int HIP) {
  refstar = HIP;
  int error = 1;
  for (int i = 0; i < n_stars; i++)
    if (star[i].star.starnumber == refstar) {
      schrijfster = star[i];
      error = 0;
    }
  return error;
}

// ****************************************************************************
// set de belichtingstijd
// ****************************************************************************

int starclass::setExposure(double etime, int step) {
  stappen = step;
  exposuretime = etime / 3600.0;
  return 0;
}

int starclass::setBereik(double _bereik) {
  bereik = _bereik;
  return bereik;
}
// ****************************************************************************
// bereken alle sterren helderder dan "magnitude"
// ****************************************************************************

int starclass::get_starlist() {
  short int error;
  short int accuracy = 0;
  double ra, dec;
  double zd, az, rar, decr;
  char s[100];
  int count = 0;
  for (int i = 0; i < n_stars; i++) {
    error = app_star(tjd, &(star[i].star), accuracy, &ra, &dec);
    equ2hor(tjd, deltat, accuracy, 0.0, 0.0, &geo_loc, ra, dec, 1, &zd, &az,
            &rar, &decr);
    if ((zd < bereik) && star[i].Vmag < magnitude)
      count++;
  }
  star_list = (star_list_rec *)malloc(
      count * sizeof(star_list_rec)); // reserveer ruimte voor alle sterren
                                      // binnen specificatie
  count = 0;

  for (int i = 0; i < n_stars; i++) {

    error = app_star(tjd, &(star[i].star), accuracy, &ra, &dec);
    equ2hor(tjd, deltat, accuracy, 0.0, 0.0, &geo_loc, ra, dec, 1, &zd, &az,
            &rar, &decr);
    if ((zd < bereik) && star[i].Vmag < magnitude) {
      star_list[count].az = az;
      star_list[count].zd = zd;
      star_list[count].hd = 90. - zd;
      star_list[count].x = 50. - sin(az * PI / 180.) * zd;
      star_list[count].y = 50. - cos(az * PI / 180.) * zd;
      strcpy(star_list[count].starname, star[i].star.starname);
      star_list[count].starnumber = star[i].star.starnumber;

      count++;
    }
  }
  return count;
}

// ****************************************************************************
// ??
// ****************************************************************************

direction starclass::get_postionlist() {
  direction d;
  short int error = 0;
  short int accuracy = 0;
  double ra, dec;
  double rar, decr;
  double stepsize = exposuretime / stappen / 24.;
  double t = tjd - exposuretime / 48.;
  for (int i = 0; i < n_stars; i++)
    if (star[i].star.starnumber == refstar) {
      for (int j = 0; j < stappen; j++) {
        error = app_star(t, &(star[i].star), accuracy, &ra, &dec);
        equ2hor(t, deltat, accuracy, 0.0, 0.0, &geo_loc, ra, dec, 1, &d.zd,
                &d.azh, &rar, &decr);
        printf("az %9.4f, elev %6.4f\n", d.azh, 90.0 - d.zd);
        printf("%f\n", t);
        t += stepsize;
      }
    }
  return d;
}

direction starclass::get_position(int it) {
  direction d;
  short int error = 0;
  short int accuracy = 0;
  double ra, dec;
  double rar, decr;
  double stepsize = exposuretime / stappen / 24.;
  double t = tjd + it * stepsize;

  if (it < stappen) {
    // error = app_star(t, &(schrijfster.star), accuracy, &ra, &dec);

    error = topo_star(t, deltat, &(schrijfster.star), &geo_loc, accuracy, &ra,
                      &dec);

    equ2hor(t, deltat, accuracy, 0.0, 0.0, &geo_loc, ra, dec, 1, &d.zd, &d.azd,
            &rar, &decr);
    d.x = sin(d.azd * PI / 180.) *
          d.zd; // recalc polair to rectanglular coordinates
    d.y = cos(d.azd * PI / 180.) *
          d.zd;                 // recalc polair to rectanglular coordinates
    d.azh = d.azd * 24. / 360.; // recalc degrees to hour notation
  }
  return d;
}

// ****************************************************************************
// ??
// ****************************************************************************

direction starclass::get_pool() {
  direction d;
  short int error = 0;
  short int accuracy = 0;
  double ra, dec;
  double rar, decr;
  double pt = tjd + exposuretime / 48.;
  // error = app_star(pt, &(poolster.star), accuracy, &ra, &dec);
  error =
      topo_star(pt, deltat, &(poolster.star), &geo_loc, accuracy, &ra, &dec);
  equ2hor(pt, deltat, accuracy, 0.0, 0.0, &geo_loc, ra, dec, 1, &d.zd, &d.azd,
          &rar, &decr);
  d.azh = d.azd * 24. / 360.;
  // cout << "poolster : "<< d.zd << ", " << d.azd << endl;

  // printf("az %9.4f, elev %6.4f\n", az, 90.0-zd);
  // printf("%f\n", t);
  return d;
}

// ****************************************************************************
// bereken beweging op sterpositie en dxf
// ****************************************************************************

int starclass::calc_trail() {
  camera_dir cd;
  double t;

  double x, y;
  double mx, my; // midden coordinaten van de trail op int(step/2)

  direction ster_dir = get_position(stappen / 2.);
  direction pool_dir = get_pool();

  for (int i = 0; i < stappen; i++) {
    ster_dir = get_position(i);
    cout << "xy " << ster_dir.x << " " << ster_dir.y << endl;
  }
  ster_dir = get_position(int(stappen / 2));
  cd.calc_camera(geo_loc.latitude, &ster_dir);
  cout << "mid " << ster_dir.x << " " << ster_dir.y << " " << cd.pan * 180. / PI
       << " " << cd.roll << endl;
  ster_dir = get_position(0);
  x = ster_dir.x;
  y = ster_dir.y;
  ster_dir = get_position(stappen - 1);
  mx = ster_dir.x;
  my = ster_dir.y;

  cout << "top " << x << " " << y << " " << mx << " " << my << endl;

  return 0;
}

int rotate_point(double cx, double cy, double angle, double *x, double *y) {
  double s = sin(angle);
  double c = cos(angle);

  // translate point back to origin:
  *x -= cx;
  *y -= cy;

  // rotate point
  double xnew = *x * c - *y * s;
  double ynew = *x * s + *y * c;

  // translate point back:
  *x = xnew + cx;
  *y = ynew + cy;
  return 0;
}

int starclass::calc_norm_trail() // trail rotated with middle south.
{
  camera_dir cd;
  double t;

  double x1, y1, x2, y2;
  double dx, dy, zd;
  double mx, my;

  direction ster_dir = get_position(stappen / 2.);
  cd.calc_camera(geo_loc.latitude, &ster_dir);
  zd = (90. - geo_loc.latitude);
  dx = ster_dir.x;
  // idx=0;
  my = ster_dir.y;
  dy = zd - my;
  double R = sqrt((dx * dx) + (dy * dy));
  cout << "R " << R << endl;
  dy = R - zd;

  // ********* calc line from start to end of trail.
  ster_dir = get_position(0);
  x1 = ster_dir.x;
  y1 = ster_dir.y;
  ster_dir = get_position(stappen - 1);
  x2 = ster_dir.x;
  y2 = ster_dir.y;
  cout << "top " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
  // calc rotation angle
  double a = atan2(y2 - y1, x2 - x1) + PI;

  // **** calc midpoint of trail
  ster_dir = get_position(stappen / 2.);
  mx = ster_dir.x;
  my = ster_dir.y;

  cout << "mid " << ster_dir.x << " " << ster_dir.y << " " << mx << " " << my
       << " " << a * 180. / PI << " " << cd.roll << endl;
  double cx, cy;

  // ***** calc points on the trail
  for (int i = 0; i < stappen; i++) {

    ster_dir = get_position(i);
    x1 = ster_dir.x - dx;
    y1 = ster_dir.y - dy - my;

    rotate_point(0., -dy, -a, &x1, &y1);
    cout << "xy " << x1 << " " << y1 << endl;
  }
  return 0;
}

// ****************************************************************************
// bewegingsfactor x motorexcenter
// ****************************************************************************

double starclass::factor_x() { return motor_x / focus; }

// ****************************************************************************
// bewegingsfactor y motorexcenter)
// ****************************************************************************

double starclass::factor_y() { return motor_y / focus; }

// ****************************************************************************
// bereken verplaatsing camera ??
// ****************************************************************************

int angle_desc(char *s, double d) {
  double dec;
  int angle, min, sec;
  angle = floor(d);
  d -= angle;
  min = floor(60 * d);
  d *= 60;
  d -= min;
  sec = floor(60 * d);
  sprintf(s, "%d°%d\'%d\" ", angle, min, sec);
  return 1;
}

camera_dir camera_dir::calc_camera(double latitude, direction *ster_dir) {
  double zd = 90. - latitude;
  pan = atan2(ster_dir->x, (-ster_dir->y + 90. - latitude));

  roll = sin(pan) * zd;
  //  cout << latitude << "  " << ster_dir->x << "  "  << ster_dir->y << "  " <<
  //  pan*180/PI << " " << roll*180/PI << endl;

  tilt = ster_dir->x;
  return *this;
}

camera_dir camera_dir::calc_camera(double x1, double y1, double x2, double y2,
                                   double latitude) {
  double mx, my;

  double zd = 90. - latitude;
  mx = (x1 + x2) / 2.;
  my = (y1 + y2) / 2.;
  pan = atan2(x2 - x1, y2 - y1);

  roll = sin(pan);
  //  cout << latitude << "  " << ster_dir->x << "  "  << ster_dir->y << "  " <<
  //  pan*180/PI << " " << roll*180/PI << endl;

  tilt = mx;
  return *this;
}
