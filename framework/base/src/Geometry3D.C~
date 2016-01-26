/*
 * Geometry3D.C 
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
 *  $Id: Geometry3D.C,v 1.5 1997/09/19 07:14:03 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include "tess-triangle.h"
#include "booga/base/Geometry3D.h"
#include <stdio.h> // NULL
//___________________________________________________________________ Geometry3D

Geometry3D::Triangulation* Geometry3D::createPolygonTriangulation(
                  const List<Vector3D>& vertices,
                  const List<List<Vector3D> >& holes,
                  const List<Vector3D>& meshpoints)
{
  register long i,j;
  List<Vector3D> temp;
  long count;
  
  if ((vertices.count() < 3) || (Geometry3D::area(vertices)< EPSILON * EPSILON)) {
    Report::warning("[Geometry3D::createPolygonTriangulation] degenerate polygon");
    return NULL;
  }

  // Create the NICE datastructur for triangle 
  
  Vector3D normal(Geometry3D::normal(vertices));

  long numPoints = vertices.count() + meshpoints.count();
  for(i=0;i<holes.count();i++)
    numPoints += holes.item(i).count(); 

  List<Vector3D> points(numPoints);

  triangulateio in,out;
  in.numberofpoints = numPoints;
  in.pointlist = new REAL[in.numberofpoints * 2];
  in.numberofsegments = numPoints - meshpoints.count();
  in.segmentlist = new int[in.numberofsegments * 2];

  in.numberofholes = holes.count();
  if (in.numberofholes>0) 
    in.holelist = new REAL[in.numberofholes * 2];
  else
    in.holelist = (REAL *) NULL;
    
  //  
  // collect all points of the polygon, holes and the addional meshpoints 
  //
  long index = 0;

  // add vertices to the pointlist
    
  temp = projectionToPlane(vertices,normal);
  Real zDistance = temp.item(0).z();    // only for new points needed
  count = vertices.count();
  for(i = 0; i < count; i++){
    points.append(vertices.item(i));
    in.pointlist[index*2    ] = (REAL)temp.item(i).x();
    in.pointlist[index*2 + 1] = (REAL)temp.item(i).y();
    in.segmentlist[index*2] = index;
    in.segmentlist[index*2 + 1] = (i == count -1) ? index + 1 - count : index + 1;
    index++;
  } 
  // add holes to the pointlist
 
  Vector3D v;
  for(i = 0; i < holes.count(); i++){
    temp = projectionToPlane(holes.item(i),normal);
    count = temp.count();
    for(j = 0; j < count; j++){
      points.append(holes.item(i).item(j));
      in.pointlist[index*2    ] = (REAL)temp.item(j).x();
      in.pointlist[index*2 + 1] = (REAL)temp.item(j).y();
      in.segmentlist[index*2] = index;
      in.segmentlist[index*2 + 1] = (j == count -1) ? index + 1 - count : index + 1;
      index++;
    }
    // compute a point inside the hole
    if (Geometry3D::normal(temp).z()<= 0){    // hole is CCW
      v = temp.item(1) - temp.item(0);
      v = temp.item(0) + Vector3D(v.y(),-v.x(),0) * 0.001 + v * 0.5;
      in.holelist[i*2   ] = (REAL)v.x();
      in.holelist[i*2 +1] = (REAL)v.y();    
    }
    else{                         // hole is CW
      v = temp.item(0) - temp.item(1);
      v = temp.item(1) + Vector3D(v.y(),-v.x(),0) * 0.001 + v * 0.5;
      in.holelist[i*2   ] = (REAL)v.x();
      in.holelist[i*2 +1] = (REAL)v.y();    
    }
  }
  
  // add meshpoints to the pointlist
 
  temp = projectionToPlane(meshpoints,normal);
  count = temp.count();
  for(i = 0; i < count; i++){    
    points.append(meshpoints.item(i));
    in.pointlist[index*2    ] = (REAL)temp.item(i).x();
    in.pointlist[index*2 + 1] = (REAL)temp.item(i).y();
    index++;
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
  
  // add the new points
  
  if (in.numberofpoints < out.numberofpoints){    
    temp.removeAll();
    count = out.numberofpoints - in.numberofpoints;
    for(i = in.numberofpoints; i <  out.numberofpoints; i++)
      temp.append(Vector3D(out.pointlist[i*2],out.pointlist[i*2+1],zDistance));
    temp = projectionToPlane(temp, Vector3D(-normal.x(),-normal.y(),normal.z()));
    for(i = 0; i<temp.count();i++)
      points.append(temp.item(i));
  }
  
  long a,b,c;
  
  Geometry3D::Triangulation* triangulation = new Geometry3D::Triangulation(points);
  for (i = 0; i < out.numberoftriangles; i++){
    a = out.trianglelist[i *out.numberofcorners];
    b = out.trianglelist[i *out.numberofcorners + 1];
    c = out.trianglelist[i *out.numberofcorners + 2];
    if ((a != b) && (a != c) && (b != c))
      triangulation->myTriangleList.append(Geometry3D::Triangle(a,b,c));
  }
  
  if (in.numberofpoints > 0)     delete in.pointlist;
  if (in.segmentlist)            delete in.segmentlist;
  if (in.holelist)               delete in.holelist;
  if (out.pointlist)             delete out.pointlist;
  if (out.segmentmarkerlist)     delete out.segmentmarkerlist;
  if (out.segmentlist)           delete out.segmentlist;
  if (out.trianglelist)          delete out.trianglelist;
  if (out.triangleattributelist) delete out.triangleattributelist;
  
  return triangulation;

}

List<Vector3D> Geometry3D::removeCollinearPoints(const List<Vector3D>& vertices)
{
  List<Vector3D> tmp = vertices;
  
  long i=0;
  while (i < tmp.count()){
    if (Geometry3D::area(tmp.item((i-1+tmp.count())% tmp.count()),
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

List<Vector3D> Geometry3D::computeLayer(Real delta, const List<Vector3D>& vertices)
{
  if (equal(delta,0))
    return vertices;
  else {
    //
    // Calculates layer of the polygon 
    //
    List<Vector3D> temp;
    long count = vertices.count();
    Vector3D a, b, c, d;
    for(long i=0; i < count; i++) {
      a = (vertices.item(i) - vertices.item((i+count-1) % count)). normalized();
      c = Vector3D(a.y(),-a.x(),a.z()) * delta;
      b = (vertices.item((i+1) % count) - vertices.item(i)). normalized();
      d = Vector3D(b.y(),-b.x(),b.z()) * delta;
      if (equal(b.x(),-a.x()))
        temp.append(vertices.item(i) + d + b * (c.y()-d.y())/(b.y() + a.y()));
      else        
        temp.append(vertices.item(i) + d + b * (c.x()-d.x())/(b.x() + a.x()));
    }
    return temp;
  }
}

List<Vector3D> Geometry3D::computeLayerXYPlane(Real delta, const List<Vector3D>& vertices)
{
  if (equal(delta,0))
    return vertices;
  else {
    //
    // Calculates layer of the polygon 
    //
    long j;
    List<Vector3D> temp;
    long count = vertices.count();
    Vector3D a, b, c, d;
    for(long i=0; i < count; i++) {

      // find the next edges a and b with 
      // length > 0 in the xy-plane
      j = i;
      do {
        j = (j + count -1) % count;
        a = vertices.item((j+1) % count) - vertices.item(j);          
        a = Vector3D(a.x(),a.y(),0);      
      }
      while (i != j && a.length() < EPSILON);

      j = i;
      do {
        b = vertices.item((j+1) % count) - vertices.item(j);          
        b = Vector3D(b.x(),b.y(),0);
        j = (j + 1) % count;
      }
      while (i != j && b.length() < EPSILON);
      
      a.normalize();
      b.normalize();
      
      c = Vector3D(a.y(),-a.x(),0) * delta;
      d = Vector3D(b.y(),-b.x(),0) * delta;

      if (equal(b.x(),-a.x()))
        temp.append(vertices.item(i) + d + b * (c.y()-d.y())/(b.y() + a.y()));
      else        
        temp.append(vertices.item(i) + d + b * (c.x()-d.x())/(b.x() + a.x()));
    }

    return temp;
  }
}

Vector3D Geometry3D::normal(const Vector3D& a,const Vector3D& b,const Vector3D& c)
{
  Vector3D n = (c-b)*(a-b);
  
  if (n.equal(Vector3D(0,0,0)))
    return Vector3D(0,0,0);
  else
    return n.normalized();
}

Vector3D Geometry3D::normal(const List<Vector3D>& vertices)
{
  Vector3D normal(0,0,0);
  Vector3D m(0,0,0);
  long i;
  
  if (vertices.count() > 2) {
    for (i=0 ; i < vertices.count(); i++)
      m += vertices.item(i);
    m = m / vertices.count();
    
    for (i=0 ; i < vertices.count(); i++)
      normal  +=   (vertices.item(i) - m) * (vertices.item((i+1) % vertices.count()) - m) ;
  }
  if (normal.length() > 0)
    return normal.normalized();
  else
    return Vector3D(0,0,1);
}

Real Geometry3D::area(const List<Vector3D>& vertices)
{
  Vector3D normal(0,0,0);
  
  if (vertices.count() > 2) {
    for (long i=0 ; i < vertices.count(); i++)
      normal  +=   vertices.item(i) * (vertices.item((i+1) % vertices.count()) - vertices.item(i)) ;
    return fabs(0.5 * normal.length());
  }
  else
    return 0;
}

List<Vector3D> Geometry3D::changeOrientation(const List<Vector3D>& vertices)
{
  List<Vector3D> temp(vertices.count());
  
  // changes the order of the list: first becomes last ... last becomes first
  
  for(long i=0; i<vertices.count();i++)
    temp.prepend(vertices.item(i));  

  return temp;
}

List<Vector3D> Geometry3D::projectionToPlane(const List<Vector3D>& vertices, const Vector3D& normal)
{
  List<Vector3D> result(vertices.count());
  Vector3D w(normal.y(),-normal.x(),0);        // the rotation axis
  Real x,y, z;

  Real cosAlpha = normal.z();                  // values of the rotation angle
  Real sinAlpha = sin(acos (normal.z()));

  if (equal(w.length(),0))                     // normalize rotation axis !!!
    w = Vector3D(1,0,0);
  else
    w = w.normalized();

  // 3D-rotation of the normal vector into the plane which is parallel to the xy-plane
  for(long i=0; i < vertices.count(); i++)
  {
    x = Vector3D(w.x()*w.x() + cosAlpha*(1- w.x()*w.x()), w.x()*w.y()*(1 - cosAlpha),w.y()*sinAlpha) ^ vertices.item(i);
    y = Vector3D(w.x()*w.y()*(1 - cosAlpha), w.y()*w.y() + cosAlpha*(1 - w.y()*w.y()), - w.x()*sinAlpha) ^ vertices.item(i);
    z = Vector3D(-w.y()*sinAlpha, w.x()*sinAlpha, cosAlpha) ^ vertices.item(i);
    result.append(Vector3D(x,y,z));  
  }
  
  return result;
}
bool Geometry3D::intersectPlanePlane(Vector3D p0, Vector3D p1, Vector3D p2,
                                     Vector3D q0, Vector3D q1, Vector3D q2,
                                     Vector3D& ro, Vector3D& r)
{
  Vector3D n1((p2 - p1)*(p0 - p1));
  Vector3D n2((q2 - q1)*(q0 - q1));
  Real d1(-n1 ^ p1);
  Real d2(-n2 ^ q1);

  r = n1 * n2;

  Real x = fabs(r.x());
  Real y = fabs(r.y());
  Real z = fabs(r.z());


  if ((z > 0) && (z > y) && (z > x)){
    r.normalize();
    ro = Vector3D(n1.y()*d2 - n2.y()*d1,n2.x()*d1 - n1.x()*d2,0);
    return true;
  }
  else if ((y > 0) && (y > x)){
    r.normalize();
    ro = Vector3D(n1.z()*d2 - n2.z()*d1,0,n2.x()*d1 - n1.x()*d2);
    return true;
  }
  else if (x > 0){
    r.normalize();
    ro = Vector3D(0,n1.z()*d2 - n2.z()*d1,n2.y()*d1 - n1.y()*d2);
    return true;
  }
  else {
    r  = Vector3D(0,0,0);
    ro = Vector3D(0,0,0);
    return false;
  }
}
List<Vector3D> Geometry3D::intersectSegmentSegment(const Vector3D& p0,const Vector3D& p1,
                                                   const Vector3D& p2,const Vector3D& p3)
{
  List<Vector3D> result;
  
  Vector3D n0 = Geometry3D::normal(p0,p1,p2);
  Vector3D n1 = Geometry3D::normal(p1,p0,p3);
  Vector3D n2 = Geometry3D::normal(p2,p3,p1);
  Vector3D n3 = Geometry3D::normal(p3,p2,p0);
  Real     d0 = n0.length();
  Real     d1 = n1.length();
  Real     d2 = n2.length();
  Real     d3 = n3.length();
  Real     l0 = (p0-p1).length();
  Real     l1 = (p2-p3).length();
  
  if (d0 > EPSILON)
    n0.normalize();
  if (d1 > EPSILON)
    n1.normalize();
  if (d2 > EPSILON)
    n2.normalize();
  if (d3 > EPSILON)
    n3.normalize();

  // both segments are points
  if (l0 < EPSILON && l1 < EPSILON){
    if ((p0-p1).equal(p2-p3))
      result.append(p0);
    return result;
  }
  
  // first segment is a point
  if (l0 < EPSILON){  
    if (d2 < EPSILON)
      result.append(p0);
    return result;
  }

  // second segment is a point
  if (l1 < EPSILON){  
    if (d0 < EPSILON)
      result.append(p2);
    return result;
  }
  
  // no intersection when at least two normals not equal
  if (d0 >= EPSILON && d1 >= EPSILON && !n0.equal(n1))
    return result;
  if (d0 >= EPSILON && d2 >= EPSILON && !n0.equal(n2))
    return result;
  if (d0 >= EPSILON && d3 >= EPSILON && !n0.equal(n3))
    return result;
  if (d1 >= EPSILON && d2 >= EPSILON && !n1.equal(n2))
    return result;
  if (d1 >= EPSILON && d3 >= EPSILON && !n1.equal(n3))
    return result;
  if (d2 >= EPSILON && d3 >= EPSILON && !n2.equal(n3))
    return result;
    
  // intersection inside the segments.
  if (d0 >= EPSILON  && d1 >= EPSILON && d2 >= EPSILON  && d3 >= EPSILON &&
      n0.equal(n1) && n1.equal(n2) && n2.equal(n3)){
    long i0,i1;
    Real t;
            
    if ((p1-p0).y()*(p3-p2).x() - (p1-p0).x()*(p3-p2).y() >= EPSILON){
      i0 = 0;
      i1 = 1;
    }
    else if ((p1-p0).z()*(p3-p2).x() - (p1-p0).x()*(p3-p2).z() >= EPSILON){
      i0 = 0;
      i1 = 2;
    }
    else{
      i0 = 1;
      i1 = 2; 
    }
    
    t = ((p3-p2)[i1]*(p0-p2)[i0] - (p3-p2)[i0]*(p0-p2)[i1])/
        ((p1-p0)[i1]*(p3-p2)[i0] - (p1-p0)[i0]*(p3-p2)[i1]);
    
    result.append(p0 + t*(p1-p0));
        
    return result;
  }                                              

  // segments touch, p2 on p1-p0
  if (d0 < EPSILON  && d1 >= EPSILON && d3 >= EPSILON  && n1.equal(n3) && (d2 < EPSILON || n2.equal(n1))){
    result.append(p2);
    return result;
  }                                              

  // segments touch, p3 on p1-p0
  if (d1 < EPSILON  && d0 >= EPSILON && d2 >= EPSILON  && n0.equal(n2) && (d3 < EPSILON || n3.equal(n0))){
    result.append(p3);
    return result;
  }                                              

  // segments touch, p1 on p3-p2
  if (d2 < EPSILON  && d0 >= EPSILON && d3 >= EPSILON  && n0.equal(n3) && (d1 < EPSILON || n1.equal(n0))){
    result.append(p1);
    return result;
  }                                              

  // segments touch, p0 on p3-p2
  if (d3 < EPSILON  && d1 >= EPSILON && d2 >= EPSILON  && n1.equal(n2) && (d0 < EPSILON || n0.equal(n1))){
    result.append(p0);
    return result;
  }                                              

  // overlap
  if (d0 < EPSILON && d1 < EPSILON && d2 < EPSILON && d3 < EPSILON){
    long cmpIndex;
    Vector3D u = (p0 - p1).normalized();
    Vector3D a,b,c,d;

    if (fabs(u.x()) >= fabs(u.y()) && fabs(u.x()) >= fabs(u.z()))
      cmpIndex = 0;
    else if (fabs(u.y()) >= fabs(u.z()))  
      cmpIndex = 1;
    else
      cmpIndex = 2;

    if (p0[cmpIndex] < p1[cmpIndex]){
      a = p0;
      b = p1;
    }
    else {
      a = p1;
      b = p2;
    }

    if (p2[cmpIndex] < p3[cmpIndex]){
      c = p2;
      d = p3;
    }
    else {
      c = p3;
      d = p2;
    }
    // test if segments not overlap
    if (b[cmpIndex] < c[cmpIndex] || d[cmpIndex] < a[cmpIndex])
      return result;
      
    // find the the common segment 
    if (a[cmpIndex] >= c[cmpIndex])
      result.append(a);
    else
      result.append(c);

    if (b[cmpIndex] <= d[cmpIndex]){
      if (!b.equal(result.item(0)))
        result.append(b);
    }
    else{
      if (!d.equal(result.item(0)))
        result.append(d);
    }
  }  
    
  return result;
}

bool Geometry3D::intersectPlaneSegment(Vector3D p0, Vector3D p1, Vector3D p2,
                                       Vector3D ro, Vector3D r,  Real &t)
{

  Vector3D n((p2 - p1)*(p0 -p1));
  Real d =- n^p1;
  Real a =- d - (n^ro);
  Real b =  n^r;

  if (b != 0){
    t = a/b;
    if ((t >= 0) && (t <= 1))
      return true;
    else
      return false;
  }
  else {
    if (a != 0){
      t = 0;
      return false;
    }
    else {
      t = 1;
      return false;
    }
  }
}

Geometry3D::Segment3D* Geometry3D::intersectCPolygonCPolygon(const List<Vector3D> &polygonA, const List<Vector3D> &polygonB)
{
  // the intersection must be convex !!
  Vector3D r, ro;
  Real t;
  long i;
  long cmpIndex;
  Geometry3D::Segment3D a,b;
  bool firstpoint = true;
  bool intersection = false;
  
  if(polygonA.count() < 3 || polygonB.count() < 3)
    return NULL;
    
  for(i=0;i<polygonB.count();i++){
    r  = polygonB.item((i+1)%polygonB.count()) - polygonB.item(i);
    ro = polygonB.item(i);
    
    if(Geometry3D::intersectPlaneSegment(polygonA.item(0),polygonA.item(1),polygonA.item(2),
                                             ro,r,t)){                                             
      
      // cerr << "point: " << ro + r*t << endl;
      if (firstpoint){
        a.myStart = ro + r*t;
        firstpoint = false;
      }
      else{      
        a.myEnd = ro + r*t;
        if (!a.myStart.equal(a.myEnd)){
          // cerr << a.myStart << ", " << a.myEnd << endl;
          intersection= true;
          break;
        }
      }  
    }            
  }   
  
  if (!intersection || (a.myEnd-a.myStart).length() < EPSILON)
    return NULL;
    
  intersection = false;
  firstpoint = true;
  
  for(i=0;i<polygonA.count();i++){
    r  = polygonA.item((i+1)%polygonA.count()) - polygonA.item(i);
    ro = polygonA.item(i);
    
    if(Geometry3D::intersectPlaneSegment(polygonB.item(0),polygonB.item(1),polygonB.item(2),
                                             ro,r,t)){
      
      if (firstpoint){
        b.myStart = ro + r*t;
        firstpoint = false;
      }
      else{      
        b.myEnd = ro + r*t;
        if (!b.myStart.equal(b.myEnd)){
          // cerr << b.myStart << ", " << b.myEnd << endl;
          intersection = true;
          break;
        }
      }
    }
  }   

  if (!intersection || (b.myEnd-b.myStart).length() < EPSILON)
    return NULL;

  Vector3D u = (a.myEnd - a.myStart).normalized();

  if (fabs(u.x()) >= fabs(u.y()) && fabs(u.x()) >= fabs(u.z()))
    cmpIndex = 0;
  else if (fabs(u.y()) >= fabs(u.z()))  
    cmpIndex = 1;
  else
    cmpIndex = 2;

  if (a.myStart[cmpIndex] > a.myEnd[cmpIndex]){
    Vector3D temp = a.myEnd;
    a.myEnd = a.myStart;
    a.myStart = temp;
  }  

  if (b.myStart[cmpIndex] > b.myEnd[cmpIndex]){
    Vector3D temp = b.myEnd;
    b.myEnd = b.myStart;
    b.myStart = temp;
  }  

  // test if intersection lines overlap
  if (a.myEnd[cmpIndex] <= b.myStart[cmpIndex] || b.myEnd[cmpIndex] <= a.myStart[cmpIndex])
    return NULL; 

  Geometry3D::Segment3D* result = new Segment3D();
  
  if (a.myStart[cmpIndex] >= b.myStart[cmpIndex])
    result->myStart = a.myStart;
  else
    result->myStart = b.myStart;

  if (a.myEnd[cmpIndex] <= b.myEnd[cmpIndex])
    result->myEnd = a.myEnd;
  else
    result->myEnd = b.myEnd;
    
  return result;
  
}

Vector3D Geometry3D::bilinearInterpolation(const Vector3D& u00, const Vector3D& u10, 
                                         const Vector3D& u01, const Vector3D& u11, 
                                         Real u, Real v)
{
  Vector3D a = u00 + (u10 - u00) * u;
  Vector3D b = u01 + (u11 - u01) * u;
  return a + (b - a) * v;
}
