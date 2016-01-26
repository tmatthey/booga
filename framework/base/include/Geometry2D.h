/*
 * $RCSfile: Geometry2D.h,v $
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
 *                        University of Berne, Switzerland
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
 *  $Id: Geometry2D.h,v 1.7 1997/01/30 08:51:42 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Geometry2D_H
#define _Geometry2D_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/Vector2D.h"
#include "booga/base/List.h"

//___________________________________________________________________ Geometry2D

class Geometry2D {
public:
  enum OrientType { CW=-1, CCW=1, ZERO=0 };
  enum IntersectType { OUTSIDE =0, INSIDE=1, ON_BOUND=2, CROSSING=3 };
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Geometry2D();                                 // No instances.
  // Geometry2D(const Geometry2D&);             // Use default version.

public:
  // ~Geometry2D();                             // Use default version.

private:
  // Geometry2D& operator=(const Geometry2D&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class Geometry2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  static OrientType orient(Real px1, Real py1,
                           Real px2, Real py2,
                           Real px3, Real py3);

  static bool intersect(Real px1, Real py1,
                        Real px2, Real py2,
                        Real px3, Real py3,
                        Real px4, Real py4);

  static bool pointInTriangle(Real px,  Real py,
                              Real px1, Real py1,
                              Real px2, Real py2,
                              Real px3, Real py3);
                              
  // computes the intersection of two segments
  static List<Vector2D> intersectSegmentSegment(const Vector2D& p0,const Vector2D& p1,const Vector2D& p2,const Vector2D& p3);
  // computes a point onto a cubic-Bezier-line 
  static Vector2D bezierPoint(const Vector2D& a, const Vector2D& b, 
                       const Vector2D& c, const Vector2D& d, Real t);   		       
  // computes the area of the polygon (signed !!!)
  static Real area(const List<Vector2D>& vertices);
  // computes the area of the triangle (signed !!!)
  static Real area(const Vector2D& a, const Vector2D& b, const Vector2D& c);  
  // test if a point is in, ouside or on a polygon
  static IntersectType pointInPolygon(const Vector2D& point, const List<Vector2D>& vertices);
  // test if a polygon is in, ouside or on an other polygon
  static IntersectType polygonInPolygon(const List<Vector2D>& polygonA,
                                        const List<Vector2D>& polygonB);
  // returns an approximating polygon with [maxVertices] vertices or
  // less (if [precision] can be achieved with less vertices)
  static List<Vector2D> approximatePolygon(const List<Vector2D>& vertices, int maxVertices=16, Real precision=0.5);
  // removes collinear points of a polygon
  static List<Vector2D> removeCollinearPoints(const List<Vector2D>& vertices); 
  // changes the orienatation of the polygon
  static List<Vector2D> changeOrientation(const List<Vector2D>& vertices);
                              
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

  // computes triangulation of polygon with help of Triangle Version 1.3, 1996
  static List<Triangle>* createPolygonTriangulation(const List<Vector2D>& vertices);
  static List<Triangle>* createPolygonTriangulation(const List<Vector2D>& points, const List<long>& segmentlength); 

  /*****************************************************************************/
  /*                                                                           */ 
  /*  triangle                                                                 */
  /*                                                                           */
  /*  Accompanies Triangle Version 1.3                                         */
  /*  July 19, 1996                                                            */
  /*                                                                           */
  /*  Copyright 1996                                                           */
  /*  Jonathan Richard Shewchuk                                                */
  /*  School of Computer Science                                               */
  /*  Carnegie Mellon University                                               */
  /*  5000 Forbes Avenue                                                       */
  /*  Pittsburgh, Pennsylvania  15213-3891                                     */
  /*  jrs@cs.cmu.edu                                                           */
  /*                                                                           */
  /*  Hypertext instructions for Triangle are available on the Web at          */
  /*                                                                           */
  /*      http://www.cs.cmu.edu/~quake/triangle.html                           */
  /*                                                                           */
  /*  Some of the references listed below are marked [*].  These are available */
  /*    for downloading from the Web page                                      */
  /*                                                                           */
  /*      http://www.cs.cmu.edu/~quake/triangle.research.html                  */
  /*****************************************************************************/

};

//________________________________________________________________INLINE

inline Real Geometry2D::area(const Vector2D& a, const Vector2D& b, const Vector2D& c)
{
  return ((b-a).x()*(c-b).y()-(b-a).y()*(c-b).x())/2;
}  

inline Vector2D Geometry2D::bezierPoint(const Vector2D& a, const Vector2D& b, const Vector2D& c, const Vector2D& d, Real t)
{
  return a*(1-t)*(1-t)*(1-t) + 3*b*t*(1-t)*(1-t) + 3*c*t*t*(1-t) + d*t*t*t;
}


#endif // _Geometry2D_H

