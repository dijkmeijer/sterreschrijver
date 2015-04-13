/**
 * @file dxfbezier2lines.h
 */

/*****************************************************************************
**  $Id: dxfbezier2lines.h 8865 2008-02-04 18:54:02Z andrew $
**
**  This is part of the dxflib library
**  Copyright (C) 2001 Andrew Mustun
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU Library General Public License as
**  published by the Free Software Foundation.
**    TekenLijst = new dxfbezier2linesClass("willekeurige_tekst.dxf", 3600,1.);
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Library General Public License for more details.
**
**  You should have received a copy of the GNU Library General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************/

#ifndef DXFBEZIER2LINES
#define DXFBEZIER2LINES

#include "dl_creationadapter.h"
#include "dl_dxf.h"
#include <list>
#include "point.h"

using namespace std;


#define DAYSECS 86400.0


/**
 * This class takes care of the entities read from the file.
 * Usually such a class would probably store the entities.
 * this one just prints some information about them to stdout.
 *
 * @author Andrew Mustun
 */

class dxfbezier2linesClass : public DL_CreationAdapter {
public:
    dxfbezier2linesClass(char *file_name, int st, double textLengte);
    ~dxfbezier2linesClass(); // constructor opent dxf file

    list<double> Punten;
    list<double> controlPunten;
    point *Lijnen;
    double stepscale; // stappen per mm negatief

    double BG;  // breedtegraad
// interne rekengrootheden.
    double max_X;  //
    double min_X;
    double max_Y;
    double min_Y;
    double length;
    int interval; //Interval waarmee de camera fotos maakt.
    int res;  //aantal punten in een beziercurve
    int aantal_punten;  // aantal punten in de berekende lijn
    double stepsize;  // lengte van een lijnstuk berekend uit bezierlengte / aantalpunten
    int n;
    double X_prev;      // begin coordinaten afzonderlijke lijnstukken
    double Y_prev;
    double text_lengte;
    char file[256];
    int Normalize();
    int Scale();
    double getlength();
    int Print();
    int subdivide();
    virtual void addLayer(const DL_LayerData& data);
    virtual void addPoint(const DL_PointData& data);
    virtual void addLine(const DL_LineData& data);
    virtual void addArc(const DL_ArcData& data);
    virtual void addCircle(const DL_CircleData& data);
    virtual void addPolyline(const DL_PolylineData& data);
    virtual void addVertex(const DL_VertexData& data);
    virtual void add3dFace(const DL_3dFaceData& data);
    virtual void addSpline(const DL_SplineData& data);
    virtual void addControlPoint (const DL_ControlPointData& data);
    virtual void addKnot (const DL_KnotData& data);
    double bezier_seglen(double t, double *x, double *y);
    double bezlen();
    double calcLine();
    point get_Lijn_punt(int n);
    void printAttributes();
};


#endif
