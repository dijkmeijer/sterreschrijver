/*
 * @file dxfbezier2lines.cpp
 */

/*****************************************************************************
**  $Id: dxfbezier2lines.cpp 8865 2008-02-04 18:54:02Z andrew $
**
**  This is part of the dxflib library
**  Copyright (C) 2001 Andrew Mustun
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU Library General Public License as
**  published by the Free Software Foundation.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Library General Public License for more details.
**
**  You should have received a copy of the GNU Library General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************/

#include "dxfbezierline.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>

#include "dxfbezierline.h"
/**
 * Default constructor.
 */

dxfbezier2linesClass::dxfbezier2linesClass(char *file_name, int st, double textLengte)
{
    n=0;
    res = 50000;
    min_X=1000000;
    max_X=-1000000;
    min_Y=1000000;
    max_Y=-1000000;
    text_lengte = textLengte;
    strcpy(file,file_name);
    aantal_punten = st;
    stepscale=80000.0; // stappen per mm op negatief

    DL_Dxf* dxf = new DL_Dxf();
    if (!dxf->in(file, this))   // if file open failed
    {
        std::cerr << file << " could not be opened.\n";
        exit(1);
    }
    delete dxf;
    calcLine();
    Scale();
    //  char* file="twee.dxf"

}


dxfbezier2linesClass::~dxfbezier2linesClass()
{
    delete Lijnen;
}


/**
 * Sample implementation of the method which handles layers.
 */
void dxfbezier2linesClass::addLayer(const DL_LayerData& data)
{
    // printf("LAYER: %s flags: %d\n", data.name.c_str(), data.flags);
//  printAttributes();
}

/**
 * Sample implementation of the method which handles point entities.
 */
void dxfbezier2linesClass::addPoint(const DL_PointData& data)
{
    printf("POINT    (%6.3f, %6.3f, %6.3f)\n",
           data.x, data.y, data.z);

    // printAttributes();
}

/**
 * Sample implementation of the method which handles line entities.
 */
void dxfbezier2linesClass::addLine(const DL_LineData& data)
{
    printf("LINE     (%6.3f, %6.3f, %6.3f) (%6.3f, %6.3f, %6.3f) \n",
           data.x1, data.y1, data.z1, data.x2, data.y2, data.z2);
    //  printAttributes();
}

/**
 * Sample implementation of the method which handles arc entities.
 */
void dxfbezier2linesClass::addArc(const DL_ArcData& data)
{
    printf("ARC      (%6.3f, %6.3f, %6.3f) %6.3f, %6.3f, %6.3f\n",
           data.cx, data.cy, data.cz,
           data.radius, data.angle1, data.angle2);
    // printAttributes();
}

/**
 * Sample implementation of the method which handles circle entities.
 */
void dxfbezier2linesClass::addCircle(const DL_CircleData& data)
{
    printf("CIRCLE   (%6.3f, %6.3f, %6.3f) %6.3f\n",
           data.cx, data.cy, data.cz,
           data.radius);
    // printAttributes();
}



/**
 * Sample implementation of the method which handles polyline entities.
 */
void dxfbezier2linesClass::addPolyline(const DL_PolylineData& data)
{
//    double Scale;
    // printf("POLYLINE \n");
    // printf("flags: %d\n", (int)data.flags);
    // printAttributes();
}


/**
 * Sample implementation of the method which handles vertices.
 */
void dxfbezier2linesClass::addVertex(const DL_VertexData& data)
{
    //printf("VERTEX   (%6.3f, %6.3f, %6.3f) %6.3f \n",
    //      data.x, data.y, data.z,
    //       data.bulge);
    // printf("%6.3f, %6.3f\n",
    //      data.x, data.y);
    Punten.push_back(data.x);
    Punten.push_back(data.y);
    // printAttributes();
}

void dxfbezier2linesClass::addSpline(const DL_SplineData& data)
{
    //printf("VERTEX   (%6.3f, %6.3f, %6.3f) %6.3f \n",
    //      data.x, data.y, data.z,
    //       data.bulge);
    // printf("%6.3f, %6.3f\n",
    //      data.x, data.y);
    //   printf("Spline %6d, %6d, %6d, %6d\n", data.degree, data.nKnots, data.flags, data.nControl);
    //Punten.push_back(data.x);
    //Punten.push_back(data.y);
    // printAttributes();
//    n=0;

}


void dxfbezier2linesClass::addControlPoint (const DL_ControlPointData &data)
{
    //printf("VERTEX   (%6.3f, %6.3f, %6.3f) %6.3f \n",
    //      data.x, data.y, data.z,
    //       data.bulge);
    // printf("%6.3f, %6.3f\n",
    //      data.x, data.y);

    // printf("%d  ", n);

    if((n >= 3) && (n%3==1))
    {
        controlPunten.push_back(X_prev);
        controlPunten.push_back(Y_prev);
    }
    n++;

    X_prev=data.x;
    Y_prev=data.y;
    controlPunten.push_back(X_prev);
    controlPunten.push_back(Y_prev);


    //Punten.push_back(data.x);
    //Punten.push_back(data.y);
    // printAttributes();
}

void dxfbezier2linesClass::addKnot (const DL_KnotData& data)

{
    //printf("VERTEX   (%6.3f, %6.3f, %6.3f) %6.3f \n",
    //      data.x, data.y, data.z,
    //       data.bulge);
    // printf("%6.3f, %6.3f\n",
    //      data.x, data.y);
    //  printf("Knot  (%6.3f\n",
    //       data.k);
    //Punten.push_back(data.x);
    //Punten.push_back(data.y);
    // printAttributes();
}


void dxfbezier2linesClass::add3dFace(const DL_3dFaceData& data)
{
    printf("3DFACE\n");
    for (int i=0; i<4; i++)
    {
        printf("   corner %d: %6.3f %6.3f %6.3f\n",
               i, data.x[i], data.y[i], data.z[i]);
    }
    //  printAttributes();
}

void dxfbezier2linesClass::printAttributes()
{
    printf("  Attributes: Layer: %s, ", attributes.getLayer().c_str());
    printf(" Color: ");
    if (attributes.getColor()==256)
    {
        printf("BYLAYER");
    }
    else if (attributes.getColor()==0)
    {
        printf("BYBLOCK");
    }
    else
    {
        printf("%d", attributes.getColor());
    }
    printf(" Width: ");
    if (attributes.getWidth()==-1)
    {
        printf("BYLAYER");
    }
    else if (attributes.getWidth()==-2)
    {
        printf("BYBLOCK");
    }
    else if (attributes.getWidth()==-3)
    {
        printf("DEFAULT");
    }
    else
    {
        printf("%d", attributes.getWidth());
    }
    printf(" Type: %s\n", attributes.getLineType().c_str());
}



int dxfbezier2linesClass::Normalize()
{
    double GX;
    double GY;
    double Scale;

    int i=0;
    GX = (max_X + min_X)/2.0;
    GY = (max_Y + min_Y)/2.0;
    if((max_X-min_X)>(max_Y-min_Y))
        Scale=1.0/(max_X-min_X);
    else
        Scale=1.0/(max_Y-min_Y);

    for(i=0; i<aantal_punten; i++)
    {
        Lijnen[i].x=(Lijnen[i].x-GX)*Scale;
        Lijnen[i].y=(Lijnen[i].y-GY)*Scale;
#ifdef DEBUG
        cout << Lijnen[i].x << ", " << Lijnen[i].y << endl ;
#endif
    }

    return 0;
}

point dxfbezier2linesClass::get_Lijn_punt(int n)
{
    return Lijnen[n];
}


int dxfbezier2linesClass::Scale()
{
    double GX;
    double GY;
    double Scale;
    int i=0;
    GX = (max_X + min_X)/2.0;
    GY = (max_Y + min_Y)/2.0;
    if((max_X-min_X)>(max_Y-min_Y))
        Scale=text_lengte/(max_X-min_X);
    else
        Scale=text_lengte/(max_Y-min_Y);


    for(i=0; i<aantal_punten; i++)
    {
        Lijnen[i].x=(Lijnen[i].x-GX)*Scale;
        Lijnen[i].y=(Lijnen[i].y-GY)*Scale;
#ifdef DEBUG
        cout << Lijnen[i].x << ", " << Lijnen[i].y << endl ;
#endif
    }

    return 0;
}

int dxfbezier2linesClass::Print()
{
    list<double>::iterator it;
    int i=0;
    for (it = Punten.begin(); it != Punten.end(); it++)
        if(i++%2==0)
            cout << *it << ", ";
        else
            cout << *it << "\n";
    return 0;
}


double dxfbezier2linesClass::getlength()
{
    list<double>::iterator it;
    list<double>::iterator itstart;
    int i=0;
    double X;
    double Y;
    double SX;
    double SY;

    length=0;
    SX=0;
    if(Punten.size()>2)
    {
        itstart=Punten.begin();
        X=*itstart++;
        Y=*itstart++;
        for (it = itstart; it != Punten.end(); it++)
            if(i++%2==0)
            {
                SX=X-(*it);
                X=*it;
            }
            else
            {
                SY=Y-(*it);
                Y=*it;
                length+=sqrt(SX*SX+SY*SY);
            }

    }
    return length;
}

double lengte(double x1, double x2, double y1, double y2)
{
    double dx;
    double dy;
    dx=x2-x1;
    dy=y2-y1;
    return sqrt(dx*dx+dy*dy);
}


double _bezier_point (double t, double *x)
{
    /* Formula from Wikipedia article on Bezier curves. */
    return      x[0] * (1.0 - t)  * (1.0 - t) * (1.0 - t)
                + 3.0 *  x[1] * (1.0 - t) * (1.0 - t)  * t
                + 3.0 *  x[2] * (1.0 - t) * t          * t
                +        x[3] * t         * t          * t;
}


double Line_length(double x1, double y1, double x2, double y2)
{
    return (sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1))));
}

double dxfbezier2linesClass::bezier_seglen(double t, double *x, double *y)
{
    double x0=x[0];
    double y0=y[0];
    double x1;
    double y1;
    double result=0.0;
    int a;
    int m;
    m=(int)(res*t);
    double d;
    double dx;
    double dy;
    for(a=0; a<m; a++)
    {

        x1= _bezier_point(double(a)/res, x);
        y1= _bezier_point(double(a)/res, y);
        dx=x1-x0;
        dy=y1-y0;
        d = sqrt((dx*dx)+(dy*dy));
        result += d;
        x0=x1;
        y0=y1;

    }
    return result;

}


double dxfbezier2linesClass::bezlen()
{
    list<double>::iterator it;
    double x[4];
    double y[4];
    double result=0.0;
    int i=0;
    it = controlPunten.begin();
    while(it != controlPunten.end())
    {
        //printf("%6.3f, %6.3f  ", *it++, *it++);
        x[i]=*it++;
        y[i]=*it++;

        i++;

        if (i==4)
        {
            i=0;
            result+=bezier_seglen(1, x, y);

        }
    }
    stepsize=result/ aantal_punten;
    return result;
}




double dxfbezier2linesClass::calcLine()
{
    bezlen();
    list<double>::iterator it;
    double x[4];
    double y[4];
    double L;
    L=stepsize;
    double result=0.0;
    int i=0;
    int Lijnen_it=0;
    double x1;
    double y1;
    int a;
    double d;
    double dx;
    double dy;
    Lijnen = new point[aantal_punten];
    it = controlPunten.begin();
    while(it != controlPunten.end())
    {
        //printf("%6.3f, %6.3f  ", *it++, *it++);
        x[i]=*it++;
        y[i]=*it++;

        i++;

        if (i==4)
        {
            i=0;
            double x0=x[0];
            double y0=y[0];
            for(a=0; a<res; a++)
            {
                x1= _bezier_point(double(a)/res, x);
                y1= _bezier_point(double(a)/res, y);
                dx=x1-x0;
                dy=y1-y0;
                d = sqrt((dx*dx)+(dy*dy));
                result += d;
                if(result > L)
                {
                    L+=stepsize;
                    //printf("%6d, %6d\n", int(x1*1000), int(y1*1000));
                    if(x1 < min_X) min_X = x1;
                    if(x1 > max_X) max_X = x1;
                    if(y1 < min_Y) min_Y = y1;
                    if(y1 > max_Y) max_Y = y1;
                    Lijnen[Lijnen_it].x=x1;
                    Lijnen[Lijnen_it].y=y1;
                    Lijnen_it++;
                }
                x0=x1;
                y0=y1;

            }
            Lijnen[aantal_punten-1].x=x1;
            Lijnen[aantal_punten-1].y=y1;
        }
        // cout << L << endl;
    }

//  Normalize();
return result;

}




// EOF
