/*
 * $RCSfile: FrontTriangle.C,v $
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
 *  $Id: FrontTriangle.C,v 1.7 1997/04/21 13:29:35 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Value.h"
#include "booga/base/Geometry3D.h"
#include "booga/base/Geometry2D.h"
#include "booga/object/Polygon3D.h"
#include "booga/building/FrontTriangle.h"
#include "booga/building/Building.h"

const Real HOLE_EPSILON = 0.001; 

// ____________________________________________________________________ FrontTriangle

implementRTTI(FrontTriangle, Front);

FrontTriangle::FrontTriangle()
{}

FrontTriangle::FrontTriangle(long frontindex, long polygonindex, const List<Vector2D>& vertices)
{
  setFrontIndex(frontindex);
  setPolygonIndex(polygonindex);
  for(long i=0;i<vertices.count();i++)
    addVertex(vertices.item(i));
}

FrontTriangle::FrontTriangle(Exemplar exemplar)
:Front(exemplar)
{
}

Object3D* FrontTriangle::copy() const
{
  return new FrontTriangle(*this);
}

Makeable* FrontTriangle::make(RCString& errMsg, const List<Value*>* parameters) const
{
  FrontTriangle* newFrontTriangle = NULL;

  if ((parameters == NULL) || (parameters->count() < 1))
    errMsg = "Wrong number of parameters.";   
  else {
    newFrontTriangle = new FrontTriangle(*this);
    newFrontTriangle->removeVertices();
    getParameter(1, Real, frontindex);
    newFrontTriangle->setFrontIndex((long)frontindex);
    if (parameters->count() >1){
      getParameter(2, Real, polygonindex);
      newFrontTriangle->setPolygonIndex((long)polygonindex);
    }
    if (parameters->count() >2){
      for(long i = 3;i <= parameters->count(); i++){
        getParameter(i, Vector2D, vertex);
        newFrontTriangle->addVertex(vertex);
      }
    }
  }

  return newFrontTriangle;
}

List<Value*>* FrontTriangle::createParameters() {
  List<Value*>* parameters = new List<Value*>;

  parameters->append(new Value(getFrontIndex()));
  parameters->append(new Value(getPolygonIndex()));
  for(long i=0; i<myVertices.count(); i++)
    parameters->append(new Value(myVertices.item(i)));
  
  return parameters;
}

void FrontTriangle::iterateAttributes(MakeableHandler* handler) {
  this->Front::iterateAttributes(handler);
}

static const RCString fronttriangleKeyword("fronttri");

RCString FrontTriangle::getKeyword() const {
  return fronttriangleKeyword;
}

Object3D* FrontTriangle::doCreateSubject(Building* building)  const
{  
  if (!isWall())
    return new NullObject3D();

  long i,j,k;
  List<Vector3D> vertices = building->getPolygon(getPolygonIndex());
  Vector3D a(vertices.item((getFrontIndex()+1) % vertices.count()) - vertices.item(getFrontIndex()));
  Real x = a.length();
  Real y = building->getHeight();

  List<Vector3D> temp;
  List<Vector2D> frontpolygon = getFrontPolygon();
  
  for(i=0; i<frontpolygon.count();i++)
    temp.append(Vector3D(x*frontpolygon.item(i).x(),y*frontpolygon.item(i).y(),0));  

  Polygon3D* polygon = new Polygon3D(temp);
  Real x0,x1,y0,y1,dx,dy;
  
  if (polygon){
    List<Face*>* facelist = new List<Face*>;

    building->getIndirectFaceObjects(getFrontIndex(),getPolygonIndex(),facelist);
    for(i=0;i<countSubobject()-1;i++){
      Face* face = dynamic_cast(Face,getObject(i));
      if (face)
        facelist->append(face);
    }
    
    // compute the holes for the faces
    for(i=0;i<facelist->count();i++){
      Face* face = facelist->item(i);
        
      if (face->isFilled()){
        temp.removeAll();
        
        if (face->isFaceInFront((Front*)this)){
          // face is inside the front
          
          // compute a hole which is a bit smaller than the face
          // which is inside the front
        
          x0 = face->getFrom().x() * x;
          y0 = face->getFrom().y() * y;
          x1 = face->getTo().x() * x;
          y1 = face->getTo().y() *y;

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
        else {
          // look for alternative holes for the face
          List<List<Vector3D> > holes = face->getAlternativeHoles(building); 
          for(j=0; j<holes.count();j++){
            List<Vector2D> temp;
            List<Vector3D> poly = holes.item(j);
            for(k=0;k < poly.count();k++)
              temp.append(Vector2D(poly.item(k).x()/x,poly.item(k).y()/y));
            if (Geometry2D::polygonInPolygon(temp,getFrontPolygon()) == Geometry2D::INSIDE)
              polygon->addHole(poly);           
          }
        }
      }
    }
    delete facelist;
  }  
  else
    return new NullObject3D();
  
  return polygon;
}

List<Vector2D> FrontTriangle::getPointsTop() const
{
  List<Vector2D> temp;
  temp.append(Vector2D(0,1));
  for(long i=0;i < myVertices.count();i++)
    if (myVertices.item(i).y() > 0.5)
      temp.append(myVertices.item(i));
  temp.append(Vector2D(1,1));
  return temp;
}

List<Vector2D> FrontTriangle::getPointsBottom() const
{
  List<Vector2D> temp;
  temp.append(Vector2D(0,0));
  for(long i=0;i < myVertices.count();i++)
    if (myVertices.item(i).y() < 0.5)
      temp.append(myVertices.item(i));
  temp.append(Vector2D(1,0));
  
  return temp;
}

void FrontTriangle::addVertex(const Vector2D& vertex)
{
  if (vertex.x() <= -EPSILON || vertex.x() >= 1+EPSILON || (vertex.y() <= 1-EPSILON && vertex.y() >= EPSILON)) {
    ostrstream os;
    os << "[FrontTriangle::addVertex] the ("
       << vertex << ") is out of bounds";
    Report::recoverable(os);
    return;
  }

  if (vertex.equal(Vector2D(0,0)) || 
      vertex.equal(Vector2D(1,0)) || 
      vertex.equal(Vector2D(1,1)) || 
      vertex.equal(Vector2D(0,1))) {
    ostrstream os;
    os << "[FrontTriangle::addVertex] the vertex ("
       << vertex << ") is a corner of the front";
    Report::recoverable(os);
    return;
  }
  
  
  long i;
  for (i = 0; i < myVertices.count(); i++)
    if ((myVertices.item(i).x() > vertex.x() && 
        ((myVertices.item(i).y() > 0.5 && vertex.y() > 0.5) ||
         (myVertices.item(i).y() < 0.5 && vertex.y() < 0.5))) ||
        myVertices.item(i).y() > 0.5 && vertex.y() < 0.5)
      break;

  if (i > 0 && vertex.equal(myVertices.item(i-1))){
    ostrstream os;
    os << "[FrontTriangle::addVertex] two consecutive vertices ("
       << vertex << ")";
    Report::recoverable(os);
    return;
  }
  myVertices.insert(i, vertex);
}

bool FrontTriangle::isFaceInFront(Face* face) const
{
  List<Vector2D> rect;

  rect.append(face->getFrom());
  rect.append(Vector2D(face->getTo().x(),face->getFrom().y()));
  rect.append(face->getTo());
  rect.append(Vector2D(face->getFrom().x(),face->getTo().y()));
  if (Geometry2D::polygonInPolygon(rect,getFrontPolygon()) == Geometry2D::INSIDE)
    return true;
  else
    return false;
}
