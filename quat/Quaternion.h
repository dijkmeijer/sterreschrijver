#ifndef _QUATERNION_H
#define _QUATERNION_H

#include <iostream>

#include <math.h>


using namespace std;

const double PI = 3.141592653589793238462 ;
template <class T = double>
class Sphere
{
public:
    T r, az, dec;
    Sphere(const T &r, const T &az, const T &dec): r(r), az(az), dec(dec) {};
    Sphere(const T &a, const T &d)
    {
        r=1.;
        az=a*PI/180.;
        dec=d*PI/180.;
    };
    int set(double faz, double fdec)
    {
        r=1.;
        az=faz*PI/180.;
        dec=fdec*PI/180.;

        return 0;
    };
};


template <class T = double>
class Quaternion
{
public:
    T w, x, y, z;

    // Numerical constructor
    Quaternion(const T &w, const T &x, const T &y, const T &z): w(w), x(x), y(y), z(z) {};
    Quaternion(const T &x, const T &y, const T &z): w(T()), x(x), y(y), z(z) {}; // For 3-rotations
    Quaternion(const T &r): w(r), x(T()), y(T()), z(T()) {};
    Quaternion(Sphere<> &s)
    {
        w=T();
        T d=T(M_PI_2-s.dec);
        x=T(s.r*sin(d)*cos(s.az));
        y=T(s.r*sin(d)*sin(s.az));
        z=T(s.r*cos(d));
    }


    int set(Sphere<> &s)
    {
        w=0.;
        T d = M_PI_2-s.dec;
        x=s.r*sin(d)*cos(s.az);
        y=s.r*sin(d)*sin(s.az);
        z=s.r*cos(d);
        return 0;
    }

    Quaternion(): w(T()), x(T()), y(T()), z(T()) {};
// Copy constructor and assignment
    Quaternion(const Quaternion &q): w(q.w), x(q.x), y(q.y), z(q.z) {};

    Quaternion& operator=(const Quaternion &q)
    {
        w=q.w;
        x=q.x;
        y=q.y;
        z=q.z;
        return *this;
    }

// Unary operators
    Quaternion operator-() const
    {
        return Quaternion(-w, -x, -y, -z);
    }
    Quaternion operator~() const
    {
        return Quaternion(w, -x, -y, -z);    // Conjugate
    }

// Norm-squared. SQRT would have to be made generic to be used here
    T normSquared() const
    {
        return w*w + x*x + y*y + z*z;
    }
// In-place operators
    Quaternion& operator+=(const T &r)
    {
        w += r;
        return *this;
    }
    Quaternion& operator+=(const Quaternion &q)
    {
        w += q.w;
        x += q.x;
        y += q.y;
        z += q.z;
        return *this;
    }

    Quaternion& operator-=(const T &r)
    {
        w -= r;
        return *this;
    }
    Quaternion& operator-=(const Quaternion &q)
    {
        w -= q.w;
        x -= q.x;
        y -= q.y;
        z -= q.z;
        return *this;
    }

    Quaternion& operator*=(const T &r)
    {
        w *= r;
        x *= r;
        y *= r;
        z *= r;
        return *this;
    }
    Quaternion& operator*=(const Quaternion &q)
    {
        T oldW(w), oldX(x), oldY(y), oldZ(z);
        w = oldW*q.w - oldX*q.x - oldY*q.y - oldZ*q.z;
        x = oldW*q.x + oldX*q.w + oldY*q.z - oldZ*q.y;
        y = oldW*q.y + oldY*q.w + oldZ*q.x - oldX*q.z;
        z = oldW*q.z + oldZ*q.w + oldX*q.y - oldY*q.x;
        return *this;
    }

    Quaternion& operator/=(const T &r)
    {
        w /= r;
        x /= r;
        y /= r;
        z /= r;
        return *this;
    }
    Quaternion& operator/=(const Quaternion &q)
    {
        T oldW(w), oldX(x), oldY(y), oldZ(z), n(q.normSquared());
        w = (oldW*q.w + oldX*q.x + oldY*q.y + oldZ*q.z) / n;
        x = (oldX*q.w - oldW*q.x + oldY*q.z - oldZ*q.y) / n;
        y = (oldY*q.w - oldW*q.y + oldZ*q.x - oldX*q.z) / n;
        z = (oldZ*q.w - oldW*q.z + oldX*q.y - oldY*q.x) / n;
        return *this;
    }

// Binary operators based on in-place operators
    Quaternion operator+(const T &r) const
    {
        return Quaternion(*this) += r;
    }
    Quaternion operator+(const Quaternion &q) const
    {
        return Quaternion(*this) += q;
    }
    Quaternion operator-(const T &r) const
    {
        return Quaternion(*this) -= r;
    }
    Quaternion operator-(const Quaternion &q) const
    {
        return Quaternion(*this) -= q;
    }
    Quaternion operator*(const T &r) const
    {
        return Quaternion(*this) *= r;
    }
    Quaternion operator*(const Quaternion &q) const
    {
        return Quaternion(*this) *= q;
    }
    Quaternion operator/(const T &r) const
    {
        return Quaternion(*this) /= r;
    }
    Quaternion operator/(const Quaternion &q) const
    {
        return Quaternion(*this) /= q;
    }

// Comparison operators, as much as they make sense
    bool operator==(const Quaternion &q) const
    {
        return (w == q.w) && (x == q.x) && (y == q.y) && (z == q.z);
    }
    bool operator!=(const Quaternion &q) const
    {
        return !operator==(q);
    }

// The operators above allow quaternion op real. These allow real op quaternion.
// Uses the above where appropriate.
    template<class T1> friend Quaternion<T1> operator+(const T1 &r, const Quaternion<T1> &q);
    template<class T1> friend Quaternion<T1> operator-(const T1 &r, const Quaternion<T1> &q);
    template<class T1> friend Quaternion<T1> operator*(const T1 &r, const Quaternion<T1> &q);
    template<class T1> friend Quaternion<T1> operator/(const T1 &r, const Quaternion<T1> &q);

// Allows cout << q
    template<class T1> friend ostream& operator<<(ostream &io, const Quaternion<T1> &q);


    Quaternion normalize()
    {
        T a = sqrt(normSquared());
        if(a > 0.001)
        {
            w/=a;
            x/=a;
            y/=a;
            z/=a;
        }
        else
        {
            w=1.;
            x=0.;
            y=0.;
            z=0.;


        }
        return Quaternion(*this);
    }

    Quaternion rotate()
    {
        T w1=acos(w)/2.;
        w=0.;
        normalize();
        x*=sin(w1);
        y*=sin(w1);
        z*=sin(w1);
        w=cos(w1);
        //normalize();
        return Quaternion(*this);
    }

    /* Quaternion rotate()
     {
         if (w > 1) normalize(); // if w>1 acos and sqrt will produce errors, this cant happen if quaternion is normalised
         T angle = 2 * acos(w);
         T s = sqrt(1-w*w); // assuming quaternion normalised then w is less than 1, so term always positive.
         w=angle;
         if (s > 0.001)   // test to avoid divide by zero, s is always positive due to sqrt
         {
             x = x / s; // normalise axis
             y = y / s;
             z = z / s;
         }
     return Quaternion(*this);
     }
     */

    Quaternion vec()
    {
        w=0;
        return Quaternion(*this);
    }
    
    Sphere<> toSphere()
    {
        Sphere<> s(0.,0.);
        w=0.;
        normalize();

        s.az=atan(y/x)*180./M_PI;
        if(x*x<.00001)s.az=0.;
        s.dec=acos(z)*180./M_PI;
        return s;
    }
};

// Friend functions need to be outside the actual class definition
template<class T1>
Quaternion<T1> operator+(const T1 &r, const Quaternion<T1> &q)
{
    return q+r;
}

template<class T1>
Quaternion<T1> operator-(const T1 &r, const Quaternion<T1> &q)
{
    return Quaternion<T1>(r-q.w, q.x, q.y, q.z);
}

template<class T1>
Quaternion<T1> operator*(const T1 &r, const Quaternion<T1> &q)
{
    return q*r;
}

template<class T1>
Quaternion<T1> operator/(const T1 &r, const Quaternion<T1> &q)
{
    T1 n(q.normSquared());
    return Quaternion<T1>(r*q.w/n, -r*q.x/n, -r*q.y/n, -r*q.z/n);
}

template<class T1>
ostream& operator<<(ostream &io, const Quaternion<T1> &q)
{
    io << q.w;
    (q.x < T1()) ? (io << " - " << (-q.x) << "i") : (io << " + " << q.x << "i");
    (q.y < T1()) ? (io << " - " << (-q.y) << "j") : (io << " + " << q.y << "j");
    (q.z < T1()) ? (io << " - " << (-q.z) << "k") : (io << " + " << q.z << "k");
    return io;
}



inline int print(Quaternion<> t, const char *naam)
{
    cout << naam << " " << t.w << " " << t.x << " " << t.y << " " << t.z << endl;
    return 0;
}

typedef struct
{
    double rc;  // hoek basisplaat tov noorden
    double hy;  // Kanteling camera om y as (parallel aan RC);
    double hx;  // Kanteling camera om x as (loodrecht op RC);
} orientatie;

inline Quaternion<> calc_orientatie(Quaternion<> q1, Quaternion<> q2, orientatie *O)
{

    /*
    de sterreschrijver heeft 3 instelbare basis assen:
    rc: rc is 0 wanneer de sterreschrijver is uitgelijnd op het noorden.
    hx &  hy
    hy is een scharnieras die parallel loop taan RC
    hy = 0 in vertikale positie van de sterreschrijver (hx=0)
    hx is de tweede scharnieras staat loodrecht op hy
    hx is 0 in vertikale positie van de sterreschrijver (hy=0)

    De orientatie van de sterreschrijver moet met
    de hoofdas parallel aan twee sterren worden uitgelijnd
    NB de poolster en de "schrijf ster".
    de hoek hy wordt bepaald door de verdraaiing die nodig is om de verbindingslijn
    tussen de sterren midden in beeld te krijgen.
    De hoek hx wordt bepaald door de verdraaiing die nodig is om de "schrijfster"
    midden in beeld te krijgen.

    q1 en q2 zijn vectoren (quaternion met W=0) voor de twee sterren.
    RC:
    het vlak tussen de sterren en het nulpunt wordt bepaald door:
    ~q2*q1

    */

    Quaternion<> x(0,1,0,0);
    Quaternion<> y(0,0,1,0);
    Quaternion<> z(0,0,0,1);
    q1.normalize();
    q2.normalize();

    Quaternion<> n=(~q2*q1).vec();     // normaal op vlak Q1, q1, 0
    n.normalize();

    Quaternion<> nz(0., n.x, n.y, 0.); // projectie van n op het vlak Z=0;
    nz.normalize();

    Quaternion<> rx=(~n*nz);           // rx op vlak z = 0;
    // rotatie van n naar nz
    //rx.normalize();
    Quaternion<> rc=rx;                // werkkopie voor rc (= genormaliseerde vector van rx)
    rc.vec();
    rc.normalize();



    Quaternion<> r=(~rc*y).rotate();   // rotatie van y-as naar rc
    rx.rotate();

    Quaternion<> nx=rx*z*~rx;          // roteer z over rx om de rotatie hoek te
    // bepalen voor ry
    Quaternion<> ry=(~q1*nx).rotate(); // bepaal hoek tussen q1 en nx ((NB rotatieas
    // is gelijk aan rc

    O->rc = acos(r.w)*360./PI;
    if(O->rc >=90.) O->rc-=180.;
    O->hx = acos(rx.w)*360./PI;
    if(O->hx >=90.) O->hx-=180.;
    O->hy = acos(ry.w)*360./PI;
    if(O->hy >=90.) O->hy-=180.;

    return (ry*rx*r);

};

#endif
