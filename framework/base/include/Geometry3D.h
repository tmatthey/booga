/*
 * Geometry3D.h
 *
 * Copyright (C) 1996, Thierry Matthey <matthey@iam.unibe.ch>
 *                     University of Berne, Switzerland
 *
 * All rights reserved.
 *
 * This software may be freely copied, modified, and redistributed
 * provided that this copyright notice is preserved on all copies.
 *
 * You may not distribute this software, in whole or in part, as part of
 * any commercial product without the express consent of the authors.
 *
 * There is no warranty or other guarantee of fitness of this software
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: Geometry3D.h,v 1.6 1998/02/04 12:54:17 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Geometry3D_H
#define _Geometry3D_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/Vector3D.h"
#include "booga/base/List.h"

//___________________________________________________________________ Geometry3D

class Geometry3D {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Geometry3D();                                 // No instances.
  // Geometry3D(const Geometry3D&);             // Use default version.

public:
  // ~Geometry3D();                             // Use default version.

private:
  // Geometry3D& operator=(const Geometry3D&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class Geometry3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // interpolates 
  static Vector3D bilinearInterpolation(const Vector3D& u00, const Vector3D& u10, 
                                      const Vector3D& u01, const Vector3D& u11, 
                                      Real u, Real v);
  // computes the normal of the polygon
  static Vector3D normal(const List<Vector3D>& vertices);
  // computes the normal of the triangle
  static Vector3D normal(const Vector3D& a,const Vector3D& b,const Vector3D& c);
  // computes the area of the polygon
  static Real area(const List<Vector3D>& vertices);
  // computes the area of the triangle
  static Real area(const Vector3D& a,const Vector3D& b,const Vector3D& c);
  // computes a point onto a cubic-Bezier-line 
  static Vector3D bezierPoint(const Vector3D& a, const Vector3D& b, 
                       const Vector3D& c, const Vector3D& d, Real t);   		       
  // rotates the polygon planar to the xy-plane
  static List<Vector3D> projectionToPlane(const List<Vector3D>& vertices,
                                          const Vector3D& normal);
  // changes the orienatation of the polygon
  static List<Vector3D> changeOrientation(const List<Vector3D>& vertices);

public:
  struct Triangle {
    Triangle() {}
    Triangle(long index1, long index2, long index3)
    : myIndex1(index1), 
      myIndex2(index2), 
      myIndex3(index3)
    {}
    
    long myIndex1, myIndex2, myIndex3;
  };

public:
  struct Triangulation {
    Triangulation() {}
    Triangulation(List<Vector3D> points)
    :myPoints(points)
    {}
   
    List<Vector3D> myPoints;
    List<Triangle> myTriangleList;
  };
  
  // computes the triangulation of a polygon and returns a set of triangles
  static Triangulation* createPolygonTriangulation(const List<Vector3D>& vertices,
                                              const List<List<Vector3D> > &holes = List<List<Vector3D> >(0),
                                              const List<Vector3D>& meshpoints = List<Vector3D>(0));
  // computes the layer with delta of the polygon 
  static List<Vector3D> computeLayer(Real delta,const List<Vector3D>& vertices);  
  // computes the layer with delta of the polygon
  static List<Vector3D> computeLayerXYPlane(Real delta,const List<Vector3D>& vertices);  
  // removes collinear points of a polygon
  static List<Vector3D> removeCollinearPoints(const List<Vector3D>& vertices); 
  // computes the intersection of two segments
  static List<Vector3D> intersectSegmentSegment(const Vector3D& p0,const Vector3D& p1,const Vector3D& p2,const Vector3D& p3);
  // intersection between to planes
  // p0,p1,p2 points of plane 1 and  q0,q1,q2 points of plane 2
  // ro the translation and r the direction of the line
  static bool intersectPlanePlane(Vector3D p0, Vector3D p1, Vector3D p2,
                                  Vector3D q0, Vector3D q1, Vector3D q2,
                                  Vector3D& ro, Vector3D& r);
  // intersection between a segment and a plane
  // p0,p1,p2 points of the plane
  // ro the translation and r the segment
  // intersection point = ro + t*r, with t in [0,1]
  static bool intersectPlaneSegment(Vector3D p0, Vector3D p1, Vector3D p2,
                                    Vector3D ro, Vector3D r,  Real &t);

  // structures for intersections
  // line segment
public:
  struct Segment3D {
    Segment3D() {}
    Segment3D(Vector3D start, Vector3D end)
    : myStart(start), 
      myEnd(end)
    {}
    
    Vector3D myStart, myEnd;
  };
  // intersection (only convex) between two polygons
  static Segment3D* intersectCPolygonCPolygon(const List<Vector3D> &polygonA, const List<Vector3D> &polygonB);
  
};

//______________________________________________________________________ INLINES

inline Vector3D Geometry3D::bezierPoint(const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d, Real t)
{
  return a*(1-t)*(1-t)*(1-t) + 3*b*t*(1-t)*(1-t) + 3*c*t*t*(1-t) + d*t*t*t;
}

inline Real Geometry3D::area(const Vector3D& a,const Vector3D& b,const Vector3D& c)
{
  return fabs(((c-b)*(a-b)).length()/2);
}

#endif // _Geometry3D_H
