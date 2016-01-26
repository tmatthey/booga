/*
 * $RCSfile: FaceItem.C,v $
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
 *  $Id: FaceItem.C,v 1.7 1997/04/21 13:38:30 matthey Exp $
 * -----------------------------------------------------------------------------
 */


#include "booga/base/mathutilities.h"
#include "booga/base/Report.h"
#include "booga/base/RCString.h"
#include "booga/base/List.h"
#include "booga/base/Value.h"
#include "booga/base/BoundingBox.h"
#include "booga/object/Transform3D.h"
#include "booga/object/Grid3D.h"
#include "booga/object/List3D.h"
#include "booga/object/Shared3D.h"
#include "booga/object/Polygon3D.h"
#include "booga/building/FaceItem.h"
#include "booga/building/FaceItemAttr.h"
#include "booga/building/Building.h"
#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"

const Real HOLE_EPSILON = 0.001; 

// ____________________________________________________________________ FaceItem

implementRTTI(FaceItem, Face);

FaceItem::FaceItem(Exemplar exemplar)
:Face(exemplar) 
{
  myObject = NULL;
  myDisplacement = Vector2D(0,0);
  myHoleFlag = false;
  myWallFlag = false;
  itemLeftCol();
  itemBottomRow();
}
FaceItem::FaceItem(const Vector2D& from,const Vector2D& to, long column, long row)
:Face()
{
  myObject = NULL;
  myDisplacement = Vector2D(0,0);
  myHoleFlag = false;
  myWallFlag = false;
  itemLeftCol();
  itemBottomRow();
  setFrom(from);
  setTo(to);
  setColumn(column);
  setRow(row);
}

FaceItem::FaceItem()
:Face()
{
  myObject = NULL;
  myDisplacement = Vector2D(0,0);
  myHoleFlag = false;
  myWallFlag = false;
  itemLeftCol();
  itemBottomRow();
}

FaceItem::FaceItem(const FaceItem& faceitem) 
:Face(faceitem),myDisplacement(faceitem.myDisplacement)
{
  if(faceitem.myObject != NULL)
    myObject = faceitem.myObject->copy();
  else
    myObject = NULL;
    
  myHoleFlag   = faceitem.myHoleFlag;
  myWallFlag   = faceitem.myWallFlag;
  myItemLeft   = faceitem.myItemLeft;     
  myItemRight  = faceitem.myItemRight;     
  myItemBottom = faceitem.myItemBottom;     
  myItemTop    = faceitem.myItemTop;     
}

Object3D* FaceItem::copy() const
{
  return new FaceItem(*this);
}

FaceItem::~FaceItem() 
{
  delete myObject;
}

Object3D* FaceItem::doCreateSubject(Building* building) const
{
  if ((getColumn() > 0) && (getRow() > 0)){
    Real x = getWidth(building);
    Real y = building->getHeight();

    //Grid3D* faceitem = new Grid3D(15,15,15);
    List3D* faceitem = new List3D();
    Object3D* object = NULL;     
    Shared3D* polygon = NULL; 
      
    Vector2D d =  getTo() - getFrom();
    d = Vector2D(x*d.x()/(Real)getColumn(), y*d.y()/(Real)getRow());
    Vector3D displacement = Vector3D(x/(Real)getColumn() * getDisplacement().x() * (getTo() - getFrom()).x(),
                                     y/(Real)getRow() * getDisplacement().y() * (getTo() - getFrom()).y(),
                                     0);
    Vector3D v;
    Vector3D from(getFromReal(x,y));
    
    // compute the hole for the object/item 
    if (isHole() && isFaceInFront()){
      List<Vector3D> hole = getObjectHole(building);
      if (hole.count() > 0){   
        List<Vector3D> element;
        element.append(Vector3D(0,0,0));
        element.append(Vector3D(d.x(),0,0));
        element.append(Vector3D(d.x(),d.y(),0));
        element.append(Vector3D(0,d.y(),0));
        polygon = new Shared3D(new Polygon3D(element, hole));
      }      
    }
    // Put together all elements
    for(long i=0; i <= getColumn(); i++)
      for(long j=0; j <= getRow(); j++) {
        v = Vector3D (d.x()*i, d.y()*j,0) + from;
        if ((myObject != NULL) &&        
             (((i==0           && myItemLeft) ||
               (i > 0          && i < getColumn()) ||
               (i==getColumn() && myItemRight)) &&
              ((j==0           && myItemBottom) ||
               (j > 0          && j < getRow()) ||
               (j==getRow()    && myItemTop)))){
          object = myObject->copy();
          object->addTransform(TransMatrix3D::makeTranslate(v + displacement));
          faceitem->adoptObject(object);
        }
        if (polygon != NULL && i < getColumn() && j < getRow()) {
          object = polygon->copy();
          object->addTransform(TransMatrix3D::makeTranslate(v));
          faceitem->adoptObject(object);
        }
      }
    
    
    // one big wall for holeless walls
    if (isWall() && isFaceInFront()) {
      if(polygon == NULL) {
        List<Vector3D> tmp(4);
        tmp.append(Vector3D(x*getFrom().x(),y*getFrom().y(),0));
        tmp.append(Vector3D(x*getTo().x(),  y*getFrom().y(),0));
        tmp.append(Vector3D(x*getTo().x(),  y*getTo().y(),0));
        tmp.append(Vector3D(x*getFrom().x(),y*getTo().y(),0));
        faceitem->adoptObject(new Polygon3D(tmp));
      }
    }
    
    if (polygon != NULL)
      delete polygon;
    
    return faceitem;
  }
  else
    return new NullObject3D();
}


int FaceItem::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  // Check for FaceItem attributes
  FaceItemAttr* attr = dynamic_cast<FaceItemAttr*>(specifier);
  if (attr != NULL) {
    // The FaceItem object knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute(this);

    delete attr;
    return 1;  
  }

  Object3D* object = dynamic_cast<Object3D*>(specifier);
  if (object != NULL) {
    if (myObject != NULL)
      delete myObject;
    myObject = object;
    myObject->computeBounds();
         
    return 1;
  } 
  
  // 
  // Let papa do the rest ...
  //
  return Face::setSpecifier(errMsg, specifier);
}

Object3D* FaceItem::orphanObject()
{
  Object3D* tmp = myObject;
  myObject = NULL;
  
  return tmp;
}

void FaceItem::addVertex(const Vector3D& vertex)
{
  long count = myVertices.count();

  //
  // Check for vaild vertex.
  //
  if (count > 0) {
    if (myVertices.item(count-1) == vertex) {
      std::stringstream os;
      os << "[FaceItem::addVertex] two consecutive vertices ("
         << vertex << ") must not have the same value";
      Report::recoverable(os);
      return;
    }
  }
  myVertices.append(Vector3D(vertex.x(),vertex.y(),0));
}

void FaceItem::setVertices(const List<Vector3D>& vertices)
{
  myVertices = vertices;
}

List<Vector3D> FaceItem::orphanVertices()
{
  List<Vector3D> tmp = myVertices;
  myVertices.removeAll();
  
  return tmp;
}

Makeable* FaceItem::make(RCString& errMsg, const List<Value*>* parameters) const
{
  FaceItem* newFaceItem = NULL;

  if ((parameters == NULL) || (parameters->count() != 4))
    errMsg = "Wrong number of parameters.";   
  else {
    newFaceItem = new FaceItem(*this);
    getParameter(1, Vector2D, from);   
    getParameter(2, Vector2D, to);
    getParameter(3, Real    , column)   
    getParameter(4, Real    , row)   
    newFaceItem->setFrom(from);
    newFaceItem->setTo(to);
    newFaceItem->setColumn((long)column);
    newFaceItem->setRow((long)row);
  }
  return newFaceItem;
}
List<Value*>* FaceItem::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getFrom()));
  parameters->append(new Value(getTo()));
  parameters->append(new Value(getColumn()));
  parameters->append(new Value(getRow()));
  return parameters;
}

void FaceItem::iterateAttributes(MakeableHandler *handler) {
  this->Face::iterateAttributes(handler);
  if (myObject)
    handler->handle(myObject);
  if (isHole()) {
    DummyMakeable hole("hole");
    if (myVertices.count() > 0)
      for(long i=0;i<myVertices.count();i++)
        hole.addParameter(Value(Vector2D(myVertices.item(i).x(),myVertices.item(i).y())));
    handler->handle(&hole);
  }
  if (!isHole() && isWall()){
    DummyMakeable wall("wallon");
    handler->handle(&wall);
  }
  if (!myDisplacement.equal(Vector2D(0,0))){
    DummyMakeable displacement("displacement");
    displacement.addParameter(Value(myDisplacement));
    handler->handle(&displacement);
  }  
  if (isItemRightCol()) {
    DummyMakeable rightcolumn("rightcolumn");
    handler->handle(&rightcolumn);
  }
  if (isItemBothCol()) {
    DummyMakeable bothcolumn("bothcolumn");
    handler->handle(&bothcolumn);
  }
  if (isItemInsideCol()) {
    DummyMakeable insidecolumn("insidecolumn");
    handler->handle(&insidecolumn);
  }
  if (isItemTopRow()) {
    DummyMakeable toprow("toprow");
    handler->handle(&toprow);
  }
  if (isItemBothRow()) {
    DummyMakeable bothrow("bothrow");
    handler->handle(&bothrow);
  }
  if (isItemInsideRow()) {
    DummyMakeable insiderow("insiderow");
    handler->handle(&insiderow);
  }
}

static const RCString faceitemKeyword("faceitem");

RCString FaceItem::getKeyword() const {
  return faceitemKeyword;
}

List<List<Vector3D> > FaceItem::getAlternativeHoles(Building* building) const
{
  List<List<Vector3D> > holes;
  List<Vector3D> temp;
  List<Vector3D> objecthole = getObjectHole(building);

  if (objecthole.count() < 3)
    return holes;

  Real x = getWidth(building);
  Real y = building->getHeight();
  Vector2D d =  getTo() - getFrom();
  d = Vector2D(x*d.x()/(Real)getColumn(), y*d.y()/(Real)getRow());
  Vector3D v;
  Vector3D from(getFromReal(x,y));
    
  for(long i=0; i < getColumn(); i++)
    for(long j=0; j < getRow(); j++) {
      v = Vector3D (d.x()*i, d.y()*j,0) + from;
      temp.removeAll();
      for(long k=0; k < objecthole.count(); k++)
        temp.append(objecthole.item(k) + v);
      holes.append(temp);        
    }
  return holes;
}

List<Vector3D> FaceItem::getObjectHole(Building* building) const
{
  List<Vector3D> hole,tmp;
  Real x = getWidth(building);
  Real y = building->getHeight();
  Vector3D displacement = Vector3D(x/(Real)getColumn() * getDisplacement().x() * (getTo() - getFrom()).x(),
                                   y/(Real)getRow() * getDisplacement().y() * (getTo() - getFrom()).y(),
                                   0);
    
  if (myVertices.count() > 0)
    tmp = myVertices;
  else {
    if (myObject != NULL) {              
      // a simple solution to finde the hole 
      Vector3D min(myObject->getBounds().getMin());
      Vector3D max(myObject->getBounds().getMax());
      Vector3D delta(max - min);
          
      min += delta * HOLE_EPSILON;
      max -= delta * HOLE_EPSILON;
          
      tmp.append(Vector3D(min.x(),min.y(),0));
      tmp.append(Vector3D(max.x(),min.y(),0));
      tmp.append(Vector3D(max.x(),max.y(),0));
      tmp.append(Vector3D(min.x(),max.y(),0));
  
          //
          // World3D* world = new World3D;
          // world->adoptObject(myObject);
          // Triangulator triang;
          // bla blabla ...
          // ConvexHull2D
          // bla blabla ...
    }
  }
  
  // Displacement of the hole
  for(long i=0;i <tmp.count(); i++)
    hole.append(tmp.item(i) + displacement);

  return hole;
}
