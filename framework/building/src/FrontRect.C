/*
 * $RCSfile: FrontRect.C,v $
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
 *  $Id: FrontRect.C,v 1.5 1997/02/22 09:16:17 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Value.h"
#include "booga/base/Geometry3D.h"
#include "booga/base/Geometry2D.h"
#include "booga/object/Polygon3D.h"
#include "booga/object/NullObject3D.h"
#include "booga/building/FrontRect.h"
#include "booga/building/Building.h"
#include "booga/building/Face.h"

const Real HOLE_EPSILON = 0.001; 

// ____________________________________________________________________ FrontRect

implementRTTI(FrontRect, Front);

FrontRect::FrontRect()
{
  myTop    = 1;
  myBottom = 0;
}

FrontRect::FrontRect(long frontindex, long polygonindex, Real bottom, Real top)
{
  setFrontIndex(frontindex);
  setPolygonIndex(polygonindex);
  setBottom(bottom);
  setTop(top);
}

FrontRect::FrontRect(Exemplar exemplar)
:Front(exemplar)
{
  myTop    = 1;
  myBottom = 0;
}

Object3D* FrontRect::copy() const
{
  return new FrontRect(*this);
}

Makeable* FrontRect::make(RCString& errMsg, const List<Value*>* parameters) const
{
  FrontRect* newFrontRect = NULL;

  if (parameters == NULL || (parameters->count() < 1) || (parameters->count() > 4))
    errMsg = "Wrong number of parameters.";   
  else {
    newFrontRect = new FrontRect(*this);
    getParameter(1, Real, frontindex);
    newFrontRect->setFrontIndex((long)frontindex);
    if (parameters->count() >1){
      getParameter(2, Real, polygonindex);
      newFrontRect->setPolygonIndex((long)polygonindex);
    }
    if (parameters->count() >2){
      getParameter(3, Real, bottom);
      newFrontRect->setBottom(bottom);
    }
    if (parameters->count() >3){
      getParameter(4, Real, top);
      newFrontRect->setTop(top);
    }
  }

  return newFrontRect;
}

List<Value*>* FrontRect::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getFrontIndex()));
  parameters->append(new Value(getPolygonIndex()));
  parameters->append(new Value(getBottom()));
  parameters->append(new Value(getTop()));
  return parameters;
}

void FrontRect::iterateAttributes(MakeableHandler* handler) {
  this->Front::iterateAttributes(handler);
}

static const RCString frontrectKeyword("frontrect");

RCString FrontRect::getKeyword() const {
  return frontrectKeyword;
}

Object3D* FrontRect::doCreateSubject(Building* building)  const
{ 
  if (!isWall())
    return new NullObject3D();
  
  long i;
  List<Vector3D> vertices = building->getPolygon(getPolygonIndex());
  Vector3D a(vertices.item((getFrontIndex()+1) % vertices.count()) - vertices.item(getFrontIndex()));
  Real x = a.length();
  Real y = building->getHeight();
  bool flag;
  
  List<Vector3D> temp(4);
  List<Vector2D> frontpolygon = getFrontPolygon();
  
  for(i=0; i<frontpolygon.count();i++)
    temp.append(Vector3D(x*frontpolygon.item(i).x(),y*frontpolygon.item(i).y(),0));  

  Polygon3D* polygon = new Polygon3D(temp);
  Real x0,x1,y0,y1,dx,dy;
  
  if (polygon){
    List<Face*>* facelist = new List<Face*>;

    building->getIndirectFaceObjects(getFrontIndex(),getPolygonIndex(),facelist);
    for(i=0;i<countSubobject()-1;i++){
      Face* face = dynamic_cast<Face*>(getObject(i));
      if (face)
        facelist->append(face);
    }
    
    for(i=0;i<facelist->count();i++){
      Face* face = facelist->item(i);
      if (face->isFilled()){
        temp.removeAll();
        flag = true;  

        x0 = face->getFrom().x();
        y0 = face->getFrom().y();
        x1 = face->getTo().x();
        y1 = face->getTo().y();
        
        // test if face inside front
        if (x0 < 0 || x0 > 1 || 
            y0 < myBottom || y0 > myTop ||
            x1 < 0 || x1 > 1 || 
            y1 < myBottom || y1 > myTop){
          
          // try alternative holes if possible
          List<List<Vector3D> > holes = face->getAlternativeHoles(building); 
          for(long j=0; j<holes.count();j++){
            flag = false;           
            List<Vector2D> temp;
            List<Vector3D> poly = holes.item(j);
            for(long k=0;k < poly.count();k++)
              temp.append(Vector2D(poly.item(k).x()/x,poly.item(k).y()/y));
            if (Geometry2D::polygonInPolygon(temp,getFrontPolygon()) == Geometry2D::INSIDE){
              polygon->addHole(poly);
            }
          }
        }
        
        // test if alternative holes added  
        if (flag){
          // compute a hole which is a bit smaller than the face
          // which is inside the front
        
          x0 = (x0 < 0) ? 0 : x0;
          x0 = (x0 > 1) ? 1 : x0;
          x0 *= x;      
        
          y0 = (y0 < myBottom) ? myBottom : y0;
          y0 = (y0 > myTop)    ? myTop    : y0;
          y0 *= y;      
        
          x1 = (x1 < 0) ? 0 : x1;
          x1 = (x1 > 1) ? 1 : x1;
          x1 *= x;      

          y1 = (y1 < myBottom) ? myBottom : y1;
          y1 = (y1 > myTop)    ? myTop    : y1;
          y1 *= y;      

          dx = (x1 - x0) * HOLE_EPSILON;
          dy = (y1 - y0) * HOLE_EPSILON;
            
          temp.append(Vector3D(x0+dx,y0+dy,0));
          temp.append(Vector3D(x1-dx,y0+dy,0));
          temp.append(Vector3D(x1-dx,y1-dy,0));
          temp.append(Vector3D(x0+dx,y1-dy,0));
 
          temp = Geometry3D::removeCollinearPoints(temp);
          if (Geometry3D::normal(temp).z() > 0)
            polygon->addHole(temp);
        }
      }
    }
    delete facelist;
  }  
  else
    return new NullObject3D();
  
  return polygon;
}

List<Vector2D> FrontRect::getPointsTop() const
{
  List<Vector2D> temp;
  temp.append(Vector2D(0,myTop));
  temp.append(Vector2D(1,myTop));
  return temp;
}

List<Vector2D> FrontRect::getPointsBottom() const
{
  List<Vector2D> temp;
  temp.append(Vector2D(0,myBottom));
  temp.append(Vector2D(1,myBottom));
  return temp;
}

bool FrontRect::isFaceInFront(Face* face) const
{
  if (face->getFrom().x() < 0 ||
      face->getTo().x()   > 1 ||
      face->getFrom().y() < getBottom() ||
      face->getTo().y()   > getTop())
    return false;
  else
    return true;
}
