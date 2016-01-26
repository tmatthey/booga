/*
 * $RCSfile: SnatchRoof.C,v $
 *
 * Copyright (C) 1997, Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: SnatchRoof.C,v 1.8 1997/04/21 13:29:36 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/TransMatrix3D.h"
#include "booga/base/mathutilities.h"
#include "booga/object/NullObject3D.h"
#include "booga/object/List3D.h"
#include "booga/building/SnatchRoof.h"
#include "booga/building/Building.h"
#include "booga/building/Roof.h"
#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"

// ____________________________________________________________________ SnatchRoof

implementRTTI(SnatchRoof, Snatch);

SnatchRoof::SnatchRoof(Exemplar exemplar)
:Snatch(exemplar)
{
  myObject = NULL;
  myPosition = Vector2D(0,0);
}

SnatchRoof::SnatchRoof()
{
  myPosition = Vector2D(0,0);
  myObject = NULL;
}

SnatchRoof::SnatchRoof(const Vector2D& position)
:myPosition(position)
{
  myObject = NULL;
}

SnatchRoof::SnatchRoof(const SnatchRoof& snatchroof) 
:Snatch(snatchroof),myPosition(snatchroof.myPosition)
{
  if(snatchroof.myObject != NULL)
    myObject = snatchroof.myObject->copy();
  else
    myObject = NULL;
}

SnatchRoof::~SnatchRoof()
{
  if (myObject)
    delete myObject;
}

Object3D* SnatchRoof::copy() const
{
  return new SnatchRoof(*this);
}

Makeable* SnatchRoof::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  SnatchRoof* newSnatch =  new SnatchRoof(*this);
  getParameter(1, Vector2D, position);  
  newSnatch->setPosition(position);
  return newSnatch;
}

Object3D* SnatchRoof::orphanObject()
{
  Object3D* tmp = myObject;
  myObject = NULL;
  
  return tmp;
}

int SnatchRoof::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  Object3D* object = dynamic_cast<Object3D*>(specifier);
  if (object != NULL) {
    if (myObject != NULL)
      delete myObject;
    myObject = object;

    return 1;
  } 
  
  // 
  // Let papa do the rest ...
  //
  return Snatch::setSpecifier(errMsg, specifier);
}

Object3D* SnatchRoof::getSnatchObjects(Building* building) const
{
  List<Roof*> objects = building->getRoofObjects();
  List3D* snatch = NULL;
  if (objects.count() > 0){
    snatch = new List3D;
    for(long i=0; i<objects.count();i++)
      snatch->adoptObject(objects.item(i));
  }
  return snatch;    
}

void SnatchRoof::getRaySegment(Vector3D &from, Vector3D &to) const
{
  from = Vector3D(myPosition.x(),myPosition.y(),0);
  to   = from - Vector3D(0,0,1);  
}

Object3D* SnatchRoof::doCreateSubject(Building*) const
{
 if (myObject)
   return myObject->copy();
 else
   return new NullObject3D;
}

void SnatchRoof::iterateAttributes(MakeableHandler *handler) {
  this->Snatch::iterateAttributes(handler);
  if (myObject)
    handler->handle(myObject);
}

static const RCString snatchroofKeyword("snatch");

RCString SnatchRoof::getKeyword() const {
  return snatchroofKeyword;
}

List<Value*>* SnatchRoof::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getPosition()));
  return parameters;
}

TransMatrix3D SnatchRoof::getRotation(const Vector3D&, const Vector3D &normal) const
{
  TransMatrix3D transform;
  if (normal.length() < EPSILON)
    return transform;

  Vector3D a = Vector3D(normal.x(),normal.y(),0).normalized(); 
  Vector3D b(1,0,0);
  Vector3D n(b * a);
    
  Real alpha = asin(n.z() > 0 ? n.length() : - n.length());
  alpha = (a-b).length() > sqrt(2) ? M_PI - alpha : 2*M_PI + alpha;
  alpha = alpha >= 2*M_PI ? alpha - 2*M_PI : alpha;
  transform.rotateZ(alpha);
  
  return transform;
  
}
