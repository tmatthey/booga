/*
 * $RCSfile: RoofPoint.C,v $
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
 *  $Id: RoofPoint.C,v 1.4 1997/02/22 09:16:25 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Report.h"
#include "booga/base/RCString.h"
#include "booga/base/List.h"
#include "booga/base/Value.h"
#include "booga/base/Geometry3D.h"
#include "booga/object/Triangle3D.h"
#include "booga/object/Polygon3D.h"
#include "booga/object/Grid3D.h"
#include "booga/object/List3D.h"
#include "booga/building/RoofPoint.h"
#include "booga/building/Building.h"

// ____________________________________________________________________ RoofPoint

implementRTTI(RoofPoint, Roof);

RoofPoint::RoofPoint()
:Roof()
{}

RoofPoint::RoofPoint(Exemplar exemplar)
:Roof(exemplar)
{}

RoofPoint::RoofPoint(const RoofPoint& roofpoint) 
:Roof(roofpoint),myVertices(roofpoint.myVertices)
{
}

Object3D* RoofPoint::copy() const
{
  return new RoofPoint(*this);
}

RoofPoint::RoofPoint(Real ledge, const List<Vector3D>& vertices)
:myVertices(vertices)
{
  setLedge(ledge);
}

Makeable* RoofPoint::make(RCString& errMsg, const List<Value*>* parameters) const
{
  if ((!parameters ? 0 : parameters->count())>0) {
    List<Vector3D> vertices(parameters->count()-1);
    getParameter(1, Real, ledge);  
    
    for (int i=2; i<=parameters->count(); i++){
      getParameter(i, Vector3D, vertex);
      vertices.append(vertex);
    }
    RoofPoint* newRoofPoint = new RoofPoint(*this);
    newRoofPoint->removeVertices();
    newRoofPoint->setLedge(ledge);
    newRoofPoint->setVertices(vertices);
    return newRoofPoint;
  }
  else 
    return NULL;
}

List<Value*>* RoofPoint::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getLedge()));
  for(long i=0; i<myVertices.count();i++)
    parameters->append(new Value(myVertices.item(i)));
  return parameters;
}

static const RCString roofpointKeyword("roofpoint");

RCString RoofPoint::getKeyword() const {
  return roofpointKeyword;
}

Object3D* RoofPoint::doCreateSubject(Building* building) const
{
  //Grid3D* roof = new Grid3D(15,15,15);
  List3D* roof = new List3D();
  List<List<Vector3D> > holes;
  List<long> sum;
  List<Vector3D> temp;
  long i,max;
  
  sum.append(0);
  sum.append(computeLedge(building->getPolygonTop(0)).count());
  
  for(i=0;i < building->getHoles().count(); i++){
    temp = computeLedge(building->getPolygonTop(i+1));
    holes.append(temp);   
    sum.append(temp.count() + sum.item(sum.count()-1));
  }
  
  temp.removeAll();
  for(i=0;i<myVertices.count();i++)
    temp.append(myVertices.item(i) + Vector3D(0,0,building->getVertex(0,0).z() + building->getHeight()));
  
  Geometry3D::Triangulation* triangulation = 
    Geometry3D::createPolygonTriangulation(computeLedge(building->getPolygonTop(0)), holes, temp);

  if (triangulation){
    Geometry3D::Triangle triangle;
    long a,b,c,d,e,f;
    bool flag;
    long j,i1,i2,i3,j1,j2,j3;
    
    for(i=0;i<triangulation->myTriangleList.count();i++){
      triangle = triangulation->myTriangleList.item(i);
      
      flag = false;
      i1 = triangle.myIndex1;
      i2 = triangle.myIndex2;
      i3 = triangle.myIndex3;
      a = -1;
      b = -1;
      c = -1;
      max = sum.item(sum.count()-1);

      // no additonal points
      if (myVertices.count() == 0)
        flag = true;

      // triangle with 2 or 3 additonal
      if (i1 >= max){
        if (i2 >= max || i3 >= max)
          flag = true;
      }
      else{
        if (i2 >= max && i3 >= max)
          flag = true;
      }
      
      // triangle with only 1 additonal point
      if (!flag && (i1 >= max || i2 >= max || i3 >= max)){
        if (i1 >= max){
          a = i2;
          b = i3;
          c = i1;
        }
        else if (i2 >= max){
          a = i3;
          b = i1;
          c = i2;
        }
        else {
          a = i1;
          b = i2;
          c = i3;
        }
        // check if the 2 vertices are neighbours
        flag = isNeighbour(a,b,sum); 
      }

      // triangles with no additional points
      if (!flag){
        bool flag0 = isNeighbour(i1,i2,sum);
        bool flag1 = isNeighbour(i2,i3,sum);
        bool flag2 = isNeighbour(i3,i1,sum);
        
        if ((flag0 && !flag1 && !flag2) || (!flag0 && flag1 && flag2)){
          a = i1;
          b = i2;
          c = i3;
        }
        if ((!flag0 && flag1 && !flag2) || (flag0 && !flag1 && flag2)){
          a = i2;
          b = i3;
          c = i1;
        }
        if ((!flag0 && !flag1 && flag2) || (flag0 && flag1 && !flag2)){
          a = i3;
          b = i1;
          c = i2;
        }
        if (flag0 && flag1 && flag2)
          flag = true;
      }
      
      // find the neighbour triangle which has the same non-neighbour vertices
      if (!flag){
        for(j=0;j<triangulation->myTriangleList.count(); j++){
          // skip 
          if (j==i){
            j++;
            if (j == triangulation->myTriangleList.count())
              break;
          }
          
          triangle = triangulation->myTriangleList.item(j);

          j1 = triangle.myIndex1;
          j2 = triangle.myIndex2;
          j3 = triangle.myIndex3;
          
          d = -1;
          e = -1;
          f = -1;
          if (a == j1)
            d = j1;
          if (a == j2)
            d = j2;
          if (a == j3)
            d = j3;
          if (b == j1)
            e = j1;
          if (b == j2)
            e = j2;
          if (b == j3)
            e = j3;
          if (d >= 0 && e >= 0){
            if (j1 != d && j1 != e)
              f = j1;
            if (j2 != d && j2 != e)
              f = j2;
            if (j3 != d && j3 != e)
              f = j3;
            break;
          }
        }
        
        if (d >= 0 && e >= 0 && f >=0){
          triangulation->myTriangleList.remove(j);         
          triangulation->myTriangleList.insert(j, Geometry3D::Triangle(c,f,b));
          triangulation->myTriangleList.remove(i);         
          triangulation->myTriangleList.insert(i, Geometry3D::Triangle(c,a,f));
        }
        else
          Report::hint("[RoofPoint::doCreateSubject] gulp: cannot find the neighbour triangle");     
      }
    }

    for(i=0; i < triangulation->myTriangleList.count();i++){
      triangle = triangulation->myTriangleList.item(i);
      roof->adoptObject(new Triangle3D(triangulation->myPoints.item(triangle.myIndex1),
                                       triangulation->myPoints.item(triangle.myIndex2),
                                       triangulation->myPoints.item(triangle.myIndex3)));
    }

    delete triangulation;
    
    // add the ledges of the roof
    List<Vector3D> polygon;
    
    if (fabs(getLedge()) > EPSILON && isLedge()){
      for(i=0; i < building->countPolygon(); i++){
        temp = building->getPolygonTop(i);
        holes.removeAll();
        if (i==0) {
          holes.append(temp);
          polygon = Geometry3D::changeOrientation(computeLedge(temp));
        }
        else {
          holes.append(Geometry3D::changeOrientation(computeLedge(temp)));
          polygon = temp;
        }

        triangulation = Geometry3D::createPolygonTriangulation(polygon, holes);

        if (triangulation) {
          for(j=0; j < triangulation->myTriangleList.count();j++){
            triangle = triangulation->myTriangleList.item(j);
            roof->adoptObject(new Triangle3D(triangulation->myPoints.item(triangle.myIndex1),
                                             triangulation->myPoints.item(triangle.myIndex2),
                                             triangulation->myPoints.item(triangle.myIndex3)));
          }
          delete triangulation;
        }      
      }
    }
  }
  
  return roof;
}

bool RoofPoint::isNeighbour(long a, long b, const List<long>& sum) const
{
  bool flag = false;
  for(long j=1; j<sum.count();j++)
    if (sum.item(j-1)<= a && a<sum.item(j) && sum.item(j-1)<= b && b<sum.item(j))
      if (fabs(a-b) == 1 || fabs(a-b) == sum.item(j) - sum.item(j-1)- 1){
        flag = true;
        break;
      }        
  return flag;
}
