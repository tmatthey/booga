/*
 * $RCSfile: Geometry2D.C,v $ 
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
 *                        Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: Geometry2D.C,v 1.12 1997/01/30 08:51:37 matthey Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <sstream>
#include "tess-triangle.h"
#include "booga/base/Geometry2D.h"
#include "booga/base/List.h"
#include "booga/base/Strip.h"
#include "booga/base/Value.h"

//___________________________________________________________________ Geometry2D

Geometry2D::OrientType Geometry2D::orient(Real px1, Real py1,
                                          Real px2, Real py2,
                                          Real px3, Real py3)
{
  Real dx1 = px2 - px1;
  Real dy1 = py2 - py1;
  Real dx2 = px3 - px1; 
  Real dy2 = py3 - py1;
  Real dx1dy2 = dx1*dy2;
  Real dy1dx2 = dy1*dx2;
 
  if (dx1dy2 > dy1dx2) return CCW; // positive sign
  if (dx1dy2 < dy1dx2) return CW;  // negative sign
  if (dx1*dx2 < 0 || dy1*dy2 < 0) return CW; 
  if ((dx1*dx1 + dy1*dy1) >= (dx2*dx2 + dy2*dy2)) return ZERO; // area is 0
  
  return CCW;
}

bool Geometry2D::intersect(Real px1, Real py1,
                           Real px2, Real py2,
                           Real px3, Real py3,
                           Real px4, Real py4)
{
  if (orient(px1,py1, px2,py2, px3,py3)*orient(px1,py1, px2,py2, px4,py4) <= 0 &&
      orient(px3,py3, px4,py4, px1,py1)*orient(px3,py3, px4,py4, px2,py2) <= 0) {
    Real denom = (px3-px4)*py1 + (px4-px3)*py2 +
                 (px2-px1)*py3 + (px1-px2)*py4;
    
    // Better test overlap.
    if (fabs(denom) < EPSILON)
      return true;             
      
    // No intersection if the segments only touch.
    if ((equal(px1, px3) && equal(py1, py3)) || 
        (equal(px1, px4) && equal(py1, py4)) ||
        (equal(px2, px3) && equal(py2, py3)) ||
        (equal(px2, px4) && equal(py2, py4)))
      return false;             

    return true;
  }
  
  return false;
}
 
bool Geometry2D::pointInTriangle(Real px,  Real py,
                                 Real px1, Real py1,
                                 Real px2, Real py2,
                                 Real px3, Real py3)
{
  if (orient(px1,py1, px2,py2, px, py) == CCW &&
      orient(px2,py2, px3,py3, px, py) == CCW &&
      orient(px3,py3, px1,py1, px, py) == CCW)
    return true;
  return false;
}

List<Vector2D> Geometry2D::intersectSegmentSegment(const Vector2D& p0,const Vector2D& p1,const Vector2D& p2,const Vector2D& p3)
{
  List<Vector2D> result;
  
  // both segments are points
  if ((p0-p1).length() < EPSILON && (p2-p3).length() < EPSILON){
    if ((p0-p1).equal(p2-p3))
      result.append(p0);
    return result;
  }  
  
  if (orient(p0.x(),p0.y(), p1.x(),p1.y(), p2.x(),p2.y())*orient(p0.x(),p0.y(), p1.x(),p1.y(), p3.x(),p3.y()) <= 0 &&
      orient(p2.x(),p2.y(), p3.x(),p3.y(), p0.x(),p0.y())*orient(p2.x(),p2.y(), p3.x(),p3.y(), p1.x(),p1.y()) <= 0) {
    Real denom = (p2.x()-p3.x())*p0.y() + (p3.x()-p2.x())*p1.y() +
                 (p1.x()-p0.x())*p2.y() + (p0.x()-p1.x())*p3.y();
    

    if (fabs(denom) < EPSILON){
      // Better test overlap.
      long cmpIndex = 0;
      if (fabs((p2-p3).x()) <= fabs((p2-p3).y()))
        cmpIndex = 1;                      
      
      if ((p2[cmpIndex] < p3[cmpIndex] && p2[cmpIndex] < p0[cmpIndex] && p0[cmpIndex] < p3[cmpIndex]) ||
           p2[cmpIndex] > p3[cmpIndex] && p2[cmpIndex] > p0[cmpIndex] && p0[cmpIndex] > p3[cmpIndex])
        result.append(p0);
      if ((p2[cmpIndex] < p3[cmpIndex] && p2[cmpIndex] < p1[cmpIndex] && p1[cmpIndex] < p3[cmpIndex]) ||
           p2[cmpIndex] > p3[cmpIndex] && p2[cmpIndex] > p1[cmpIndex] && p1[cmpIndex] > p3[cmpIndex])
        result.append(p1);
        
      if (fabs((p0-p1).x()) <= fabs((p0-p1).y()))
        cmpIndex = 1;
      else
        cmpIndex = 0;                                      

      if ((p0[cmpIndex] < p1[cmpIndex] && p0[cmpIndex] < p2[cmpIndex] && p2[cmpIndex] < p1[cmpIndex]) ||
           p0[cmpIndex] > p1[cmpIndex] && p0[cmpIndex] > p2[cmpIndex] && p2[cmpIndex] > p1[cmpIndex])
        result.append(p2);
      if ((p0[cmpIndex] < p1[cmpIndex] && p0[cmpIndex] < p3[cmpIndex] && p3[cmpIndex] < p1[cmpIndex]) ||
           p0[cmpIndex] > p1[cmpIndex] && p0[cmpIndex] > p3[cmpIndex] && p3[cmpIndex] > p1[cmpIndex])
        result.append(p3);
    }
    
    // test if the endpoints are equal.
    if (p0.equal(p2) || p0.equal(p3))
      result.append(p0);

    if ((p1.equal(p2) || p1.equal(p3)) && !p0.equal(p1))
      result.append(p1);       
    
    // intersection inside the segments.
    if (result.count() == 0){
      Real t = ((p3-p2).y()*(p0-p2).x()-(p3-p2).x()*(p0-p2).y())/
               ((p3-p2).x()*(p1-p0).y()-(p3-p2).y()*(p1-p0).x());
      result.append(p0 + (p1-p0)*t);
    }
  }
  
  return result;  
}

Geometry2D::IntersectType Geometry2D::pointInPolygon(const Vector2D& point, const List<Vector2D>& vertices)
{
  Real area;
  Geometry2D::IntersectType result = OUTSIDE;
  Vector2D a,b,v;
  
  for(long i=0; i<vertices.count(); i++){
    a = vertices.item(i);
    b = vertices.item((i+1) % vertices.count());
    v = b - a;
    area = Geometry2D::area(a,b,point);
    if ((b.y() < point.y() && point.y() <= a.y() && area > 0) ||
        (a.y() < point.y() && point.y() <= b.y() && area < 0))
      result = (result == OUTSIDE) ? INSIDE : OUTSIDE;
    else if ((fabs(area) < EPSILON * EPSILON) &&
             ((b.y() <= point.y() && point.y() <= a.y()) || 
              (a.y() <= point.y() && point.y() <= b.y())))
      return ON_BOUND;              
  }
  
  return result;
}

Geometry2D::IntersectType Geometry2D::polygonInPolygon(const List<Vector2D>& polygonA,
                                        const List<Vector2D>& polygonB)
{
  long aInsideB  = 0;
  long aOutsideB = 0;
  long bInsideA  = 0;
  long bOutsideA = 0;

  long i;
  
  for(i = 0; i < polygonA.count();i++){
    switch (pointInPolygon(polygonA.item(i),polygonB)) {
    case OUTSIDE:
      aOutsideB++;
      break;    
//    case ON_BOUND:
    case INSIDE:
      aInsideB++;
      break;    
    default:
      break;
    }
    if (aOutsideB > 0 && aInsideB > 0) 
      return CROSSING;  
  }

  for(i = 0; i < polygonB.count();i++){
    switch (pointInPolygon(polygonB.item(i),polygonA)) {
//    case ON_BOUND:
    case OUTSIDE:
      bOutsideA++;
      break;    
    case INSIDE:
      bInsideA++;
      break;    
    default:
      break;
    }
    if (bOutsideA > 0 && bInsideA > 0) 
      return CROSSING;  
  }

  if (aOutsideB == 0 && bInsideA == 0)
    return INSIDE;
  else
    return OUTSIDE;  
}

Real Geometry2D::area(const List<Vector2D>& vertices)
{
  Real area = 0;
  Vector2D v1, v2;
  long count = vertices.count();

  if (count > 2) {
    for (long i=0; i< count ; i++) {
      v2 = vertices.item((i-1+count)%count) - vertices.item(i);
      v1 = vertices.item((i+1)%count) - vertices.item(i);
      area += v1.x()*v2.y()-v1.y()*v2.x();
   }
  }
  return area/2;
}

List<Vector2D> Geometry2D::removeCollinearPoints(const List<Vector2D>& vertices)
{
  List<Vector2D> tmp = vertices;
  
  long i=0;
  while (i < tmp.count()){
    if (Geometry2D::area(tmp.item((i-1+tmp.count())% tmp.count()),
                         tmp.item(i),
                         tmp.item((i+1) % tmp.count())) <= EPSILON * EPSILON){
      tmp.remove(i);
      i = 0;
    }
    else
      i++;
  }
  
  return tmp;
}



List<Geometry2D::Triangle>* 
Geometry2D::createPolygonTriangulation(const List<Vector2D>& vertices)
{
  long numVertices = vertices.count();
  register long i;
  triangulateio in,out;
  
  if (numVertices < 3) {
    std::stringstream os;
    os << "[Geometry2D::createPolygonTriangulation] only " << numVertices << " provided"
       << " , >= 3 required";
    Report::recoverable(os); 
    return NULL;
  }

  //
  // Check for degenerated polygon (straight line...)
  //
  Real area = 0;
  Vector2D v1, v2;

  for (i=1; i<numVertices-1; i++) {
    v1 = vertices.item(i-1) - vertices.item(i);
    v2 = vertices.item(i+1) - vertices.item(i);
    area += fabs(v1.x()*v2.y()-v1.y()*v2.x());
  }

  if (equal(area, 0))
    return NULL;

  //
  // Start tesselation.
  //
  List<Geometry2D::Triangle>* result = new List<Geometry2D::Triangle>;
  long a,b,c;
  
  in.numberofpoints = numVertices;
  in.pointlist = new REAL[numVertices * 2];
  in.numberofsegments = numVertices;
  in.segmentlist = new int[numVertices * 2];
  for(i = 0; i < numVertices; i++){
    in.pointlist[i*2    ] = (REAL)vertices.item(i).x();
    in.pointlist[i*2 + 1] = (REAL)vertices.item(i).y();
    in.segmentlist[i*2] = i;
    in.segmentlist[i*2 + 1] = (i+1) % numVertices;
  }
  in.numberofpointattributes = 0;
  in.pointattributelist = (REAL*) NULL;
  in.pointmarkerlist = (int *) NULL;
  in.segmentmarkerlist = (int *) NULL;
  in.numberofholes = 0;
  in.holelist = (REAL *) NULL;
  in.numberofregions = 0;
  in.regionlist = (REAL *) NULL;
  
  out.numberofpoints = 0;
  out.pointlist = (REAL *) NULL;
  out.numberofpointattributes = 0;
  out.pointattributelist = (REAL *) NULL;
  out.pointattributelist = (REAL *) NULL;
  
  out.numberoftriangles = 0;
  out.numberofcorners = 0;
  out.numberoftriangleattributes = 0;
  out.neighborlist = (int *) NULL;
  out.trianglearealist = (REAL *) NULL;
  out.trianglelist = (int *) NULL;
  out.triangleattributelist = (REAL *) NULL;
  
  out.segmentlist = (int *) NULL;
  out.segmentmarkerlist = (int *) NULL;
  out.numberofsegments = 0;
  
  triangulate("pzNQ",&in, &out, (triangulateio *)NULL);
  
  long count = out.numberoftriangles;
  long numDegenerate = 0;
  
  for (i = 0; i < count; i++){
    a = out.trianglelist[i *out.numberofcorners];
    b = out.trianglelist[i *out.numberofcorners + 1];
    c = out.trianglelist[i *out.numberofcorners + 2];
    if ((a<numVertices) && (b<numVertices) && (c<numVertices) && (a != b) && (a != c) && (b != c))
      result->append(Triangle(a,b,c));
    else
      numDegenerate++;
  }
      
  if (numDegenerate > 0){    
    std::stringstream os;
    os << "[Geometry2D::createPolygonTriangulation] polygon (" << vertices.item(0)
       << ") have lost " << numDegenerate << " strange triangles";
    Report::warning(os); 
  }
                        
  if (in.pointlist)              delete in.pointlist;
  if (in.segmentlist)            delete in.segmentlist;
  if (out.pointlist)             delete out.pointlist;
  if (out.segmentmarkerlist)     delete out.segmentmarkerlist;
  if (out.segmentlist)           delete out.segmentlist;
  if (out.trianglelist)          delete out.trianglelist;
  if (out.triangleattributelist) delete out.triangleattributelist;

  return result;
}


List<Geometry2D::Triangle>* 
Geometry2D::createPolygonTriangulation(const List<Vector2D>& points, const List<long>& segmentlength)
{
  register long i,j;
  triangulateio in,out;
  
  if (points.count() < 3) {
    std::stringstream os;
    os << "[Geometry2D::createPolygonTriangulation] only " << points.count() << " provided"
       << " , >= 3 required";
    Report::recoverable(os); 
    return NULL;
  }

  long numPoints = points.count();
     
  //  
  // Start tesselation.
  //
  List<Geometry2D::Triangle>* result = new List<Geometry2D::Triangle>;
  long a,b,c;
  
  in.numberofpoints = numPoints;
  in.pointlist = new REAL[in.numberofpoints * 2];
  in.numberofsegments = numPoints;
  in.segmentlist = new int[in.numberofpoints * 2];

  in.numberofholes = segmentlength.count() - 1;
  if (in.numberofholes>0) 
    in.holelist = new REAL[in.numberofholes * 2];
  else
   in.holelist = (REAL *) NULL;
      
  Vector2D v;  
  long index = 0;
  for(i = 0; i < segmentlength.count(); i++){
    if (i>0) {
      // Bad solution to find a point inside the hole
      v = points.item(index+1) - points.item(index);
      v = points.item(index) + Vector2D(v.y(),-v.x()) * 0.001 + v * 0.5;
      in.holelist[(i-1)*2   ] = (REAL)v.x();
      in.holelist[(i-1)*2 +1] = (REAL)v.y();
    }
    for(j = 0; j < segmentlength.item(i); j++){
      in.pointlist[index*2    ] = (REAL)points.item(index).x();
      in.pointlist[index*2 + 1] = (REAL)points.item(index).y();
      in.segmentlist[index*2] = index;
      in.segmentlist[index*2 + 1] = (j == segmentlength.item(i) -1) ? index + 1 - segmentlength.item(i) : index + 1;
      index++;
    }
  }
  
  in.numberofpointattributes = 0;
  in.pointattributelist = (REAL*) NULL;
  in.pointmarkerlist = (int *) NULL;
  in.segmentmarkerlist = (int *) NULL;
  
  in.numberofregions = 0;
  in.regionlist = (REAL *) NULL;
  
  out.numberofpoints = 0;
  out.pointlist = (REAL *) NULL;
  out.numberofpointattributes = 0;
  out.pointattributelist = (REAL *) NULL;
  out.pointattributelist = (REAL *) NULL;
  
  out.numberoftriangles = 0;
  out.numberofcorners = 0;
  out.numberoftriangleattributes = 0;
  out.neighborlist = (int *) NULL;
  out.trianglearealist = (REAL *) NULL;
  out.trianglelist = (int *) NULL;
  out.triangleattributelist = (REAL *) NULL;
  
  out.segmentlist = (int *) NULL;
  out.segmentmarkerlist = (int *) NULL;
  out.numberofsegments = 0;
  
  triangulate("pzNQ",&in, &out, (triangulateio *)NULL);
  
  long count = out.numberoftriangles;
  long numDegenerate = 0;
    
  for (i = 0; i < count; i++){
    a = out.trianglelist[i *out.numberofcorners];
    b = out.trianglelist[i *out.numberofcorners + 1];
    c = out.trianglelist[i *out.numberofcorners + 2];
    if ((a<numPoints) && (b<numPoints) && (c<numPoints) && (a != b) && (a != c) && (b != c))
      result->append(Triangle(a,b,c));
    else
      numDegenerate++;
  }
      
  if (numDegenerate > 0){    
    std::stringstream os;
    os << "[Geometry2D::createPolygonTriangulation] polygon (" << points.item(0)
       << ") have lost " << numDegenerate << " strange triangles";
    Report::warning(os); 
  }
  
  if (in.numberofpoints != out.numberofpoints){    
    std::stringstream os;
    os << "[Geometry2D::createPolygonTriangulation] polygon (" << points.item(0)
       << ") has more mesh points than input points";
    Report::warning(os); 
  }
                      
  if (in.pointlist)              delete in.pointlist;
  if (in.segmentlist)            delete in.segmentlist;
  if (in.holelist)               delete in.holelist;
  if (out.pointlist)             delete out.pointlist;
  if (out.segmentmarkerlist)     delete out.segmentmarkerlist;
  if (out.segmentlist)           delete out.segmentlist;
  if (out.trianglelist)          delete out.trianglelist;
  if (out.triangleattributelist) delete out.triangleattributelist;

  return result;
}

List<Vector2D> Geometry2D::approximatePolygon(const List<Vector2D>& vertices, int maxVertices, Real precision)
{
  //
  // nothing to fit?
  //
  if (vertices.count() <= maxVertices) return vertices;

  //
  // do fitting
  //
  List<Strip<Vector2D> > strips(maxVertices);

  // assume first point lies on convex hull
  // create initial strip
  strips.insert(0, Strip<Vector2D>(vertices, 0, vertices.count())); 
  int i;
  
  while (strips.count() < maxVertices) {
    Real worstDist = 0.0;
    int worstStrip = 0;
    for (i=0; i<strips.count(); i++) {
      if (strips.item(i).getFarPointDistance() > worstDist) {
        worstStrip = i;
        worstDist = strips.item(i).getFarPointDistance();
      }
    }
    if (worstDist < precision) break;
    Strip<Vector2D> splitA(vertices, 
                    strips.item(worstStrip).getStart(), 
                    strips.item(worstStrip).getFarPoint());
    Strip<Vector2D> splitB(vertices, 
                    strips.item(worstStrip).getFarPoint(), 
                    strips.item(worstStrip).getEnd());
    strips.remove(worstStrip);
    strips.insert(worstStrip, splitB);
    strips.insert(worstStrip, splitA);
  }

  List<Vector2D> newVertices(strips.count());

  for(i=0; i<strips.count(); i++) {
    newVertices.append(vertices.item(strips.item(i).getStart()));
  }
  return newVertices;
}


List<Vector2D> Geometry2D::changeOrientation(const List<Vector2D>& vertices)
{
  List<Vector2D> temp(vertices.count());
  
  // changes the order of the list: first becomes last ... last becomes first
  
  for(long i=0; i<vertices.count();i++)
    temp.prepend(vertices.item(i));  

  return temp;
}


