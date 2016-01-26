/*
 * $RCSfile: Front.C,v $
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
 *  $Id: Front.C,v 1.6 1997/04/10 12:41:58 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/building/Building.h"
#include "booga/building/Front.h"
#include "booga/building/FrontAttr.h"
#include "booga/building/Face.h"
#include "booga/object/MakeableHandler.h"

// ____________________________________________________________________ Front

implementRTTI(Front, BuildingObject);

Front::Front(Exemplar exemplar)
:BuildingObject(exemplar)
{
  myFrontIndex = 0;
  myPolygonIndex = 0;
  myWallFlag = true;
  
  if (myObjectList.count() > 0) {
    for (long i = 0; i < myObjectList.count(); i++)
      delete myObjectList.item(i);
    myObjectList.removeAll();
  }  

}

Front::Front()
{
  myFrontIndex = 0;
  myPolygonIndex = 0;
  myWallFlag = true;
  
  if (myObjectList.count() > 0) {
    for (long i = 0; i < myObjectList.count(); i++)
      delete myObjectList.item(i);
    myObjectList.removeAll();
  }  
}

Front::~Front()
{
  if (myObjectList.count() > 0) {
    for (long i = 0; i < myObjectList.count(); i++)
      delete myObjectList.item(i);
    myObjectList.removeAll();
  }
}

Front::Front(const Front& front) : BuildingObject(front)
{
  myFrontIndex = front.myFrontIndex;
  myPolygonIndex = front.myPolygonIndex;
  myWallFlag = front.myWallFlag;
    
  for (long i=0; i<front.myObjectList.count(); i++)
    this->adoptObject(front.myObjectList.item(i)->copy());

}

int Front::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  // Check for Front attributes
  FrontAttr* attr = dynamic_cast<FrontAttr*>(specifier);
  if (attr != NULL) {
    // The Front object knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute(this);

    delete attr;
    return 1;  
  }

  // Check for objects
  Object3D* object = dynamic_cast<Object3D*>(specifier);
  if (object != NULL){
    adoptObject(object);
    return 1;    
  }

  // 
  // Let papa do the rest ...
  //
  return BuildingObject::setSpecifier(errMsg, specifier);
}


Object3D* Front::createSubject(Building* building) const
{
  
  if (!building->testIndex(getFrontIndex(),getPolygonIndex())){
    std::stringstream os;
    os << "[Front::createSubject] front ("
       <<  getFrontIndex() << ","
       <<  getPolygonIndex() << ") is out of bounds";
    Report::recoverable(os);     
    return new NullObject3D();  
  }  

 
  if (building->getHeight() < EPSILON || ! isOn())
    return new NullObject3D();

  
  List<Vector3D> vertices = building->getPolygon(getPolygonIndex());
  TransMatrix3D transform;
  Vector3D a(vertices.item((myFrontIndex+1) % vertices.count()) - vertices.item(myFrontIndex));

  transform.rotateX(0.5*M_PI);
  transform.rotateZ(atan2(a.y(),a.x()));
  transform.translate(vertices.item(myFrontIndex));

  Front* This = (Front*)this;
  This->setTransform(transform);
  
  return doCreateSubject(building);
}

void Front::adoptObject(Object3D* object)
{
  if (object == NULL){
    Report::recoverable("[Front::adoptObject] NULL pointer");
    return;
  }
  
  Face* face = dynamic_cast<Face*>(object);

  if (face) {
    face->setFrontIndex(myFrontIndex);
    face->setPolygonIndex(myPolygonIndex);
    face->setParentFront(this);
    face->subjectChanged();
    myObjectList.append(face);
  }
  else
    myObjectList.append(object);
}

Object3D* Front::getObject(long index) const
{
  if ((index < 0) || (index >= myObjectList.count())){
    Report::recoverable("[Front::getObject] index out of range");
    return NULL;
  }
  
  return myObjectList.item(index);
}

Object3D* Front::orphanObject(long index)
{
  if ((index < 0) || (index >= myObjectList.count())){
    Report::warning("[Front::removeObject] index out of range");
    return NULL;
  }
  
  Object3D* tmp = myObjectList.item(index);
  myObjectList.remove(index);
  return tmp;
}

long Front::countSubobject() const
{
  if (isOn())
    return 1 + myObjectList.count();   
  else
    return 1;
}

Object3D* Front::getSubobject(long index)
{
  Object3D* retval = NULL;
  
  if (index == 0)
    retval = getSubject();
  else if (index >0 && index <= myObjectList.count() && isOn())
    retval = myObjectList.item(index-1);
    
  if (!retval) {
    std::stringstream os;
    os << "[Front::getSubobject] index out of range ";
    os << "(was " << index << ")";
    Report::error(os);
  }
      
  return retval;
}

void Front::iterateAttributes(MakeableHandler* handler) {
  this->BuildingObject::iterateAttributes(handler);
  for(long i=0; i<myObjectList.count(); i++)
    handler->handle(myObjectList.item(i));
}

void Front::subjectChanged() const
{
  BuildingObject::subjectChanged();
    
  for(long i=0; i<myObjectList.count();i++){
    BuildingObject* object = dynamic_cast<BuildingObject*>(myObjectList.item(i));
    if (object)
      object->subjectChanged();
  }
}

void Front::doComputeBounds()
{
  for(long i=0;i<countSubobject();i++)
    myBounds.expand(getSubobject(i)->getBounds());
}

long Front::numberOfFaces() const
{
  long l=0;
  for(long i=0; i<myObjectList.count();i++)
   if (dynamic_cast<Face*>(myObjectList.item(i)))
     l++;

  return l;
}

List<Vector2D> Front::getFrontPolygon() const
{
  List<Vector2D> polygon = getPointsBottom();
  List<Vector2D> temp = getPointsTop();
  for(long i = temp.count()-1; i >= 0 ; i--)
    polygon.append(temp.item(i));
    
  return polygon;
}

void Front::getIndirectFaceObjects(long frontindex, long polygonindex, List<Face*>* facelist) const
{
  Face* face = NULL;
  
  for(long i=0; i < myObjectList.count();i++){
    face = dynamic_cast<Face*>(myObjectList.item(i));
    if (face) 
      face->getIndirectFaceObjects(frontindex, polygonindex, facelist);          
  }
}

void Front::setFrontIndex(long frontindex)
{
  myFrontIndex = frontindex;
  for(long i=0; i<myObjectList.count();i++){
    Face* face = dynamic_cast<Face*>(myObjectList.item(i));
    if(face)
      face->setFrontIndex(frontindex);
  }
}


void Front::setPolygonIndex(long polygonindex)
{
  myPolygonIndex = polygonindex;
  for(long i=0; i<myObjectList.count();i++){
    Face* face = dynamic_cast<Face*>(myObjectList.item(i));
    if(face)
      face->setPolygonIndex(polygonindex);
  }
}
