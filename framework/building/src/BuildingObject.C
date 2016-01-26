/*
 * $RCSfile: BuildingObject.C,v $
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
 *  $Id: BuildingObject.C,v 1.4 1997/02/22 09:16:11 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"
#include "booga/object/NullObject3D.h"
#include "booga/building/Building.h"
#include "booga/building/BuildingObject.h"
#include "booga/building/BuildingObjectAttr.h"

// ____________________________________________________________________ BuildingObject

implementRTTI(BuildingObject, Object3D);

BuildingObject::BuildingObject(Exemplar exemplar)
:Object3D(exemplar)
{
  mySubject = NULL;
  myIsOn = true;
  myParentBuilding = NULL;
}

BuildingObject::BuildingObject()
{
  mySubject = NULL;
  myIsOn = true;
  myParentBuilding = NULL;  
}

BuildingObject::BuildingObject(const BuildingObject& buildingobject)
  : Object3D(buildingobject)
{
  if (buildingobject.mySubject != NULL)
    mySubject = buildingobject.mySubject->copy();
  else
    mySubject = NULL;

  if (buildingobject.myParentBuilding)
    myParentBuilding = buildingobject.myParentBuilding;
  else
    myParentBuilding = NULL;
        
  myIsOn = buildingobject.myIsOn;
}

int BuildingObject::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  // Check for Building attributes
  BuildingObjectAttr* attr = dynamic_cast<BuildingObjectAttr*>(specifier);
  if (attr != NULL) {
    // The BuildingObject object knows best which method has to be called.
    // So let the object do the job.

    attr->setAttribute(this);
     
    delete attr;
    return 1;  
  }

  // 
  // Let papa do the rest ...
  //
  return Object3D::setSpecifier(errMsg, specifier);  
}

void BuildingObject::doComputeBounds()
{
  for(long i=0;i<countSubobject();i++)
    myBounds.expand(getSubobject(i)->getBounds());
}

bool BuildingObject::doIntersect(Ray3D& ray)
{
  if (!isOn())
    return false;
    
  bool hit = false;
  for(long i=0; i<countSubobject(); i++)
    if (getSubobject(i)->intersect(ray))
      hit = true;
     
  return hit;
}
 
Object3D* BuildingObject::getSubobject(long index)
{
  Object3D* retval = getSubject();
  
  if (!retval || index != 0) {
    std::stringstream os;
    os << "[BuildingObject::getSubobject] index out of range ";
    os << "(was " << index << ")";
    Report::error(os);
  }
  
  return retval;
}

Object3D* BuildingObject::getSubject() const
{
  BuildingObject* This = (BuildingObject*)this;
  
  if (mySubject == NULL) {
    // Cache does not affect logical constness
    if (getParentBuilding())
      This->mySubject = createSubject(getParentBuilding());
    else {
      Report::warning("[BuildingObject::getSubject] no parent building");
      This->mySubject = new NullObject3D();
    }
    This->mySubject->computeBounds();
  } 
  return mySubject;
}

void BuildingObject::subjectChanged() const
{
  if (mySubject != NULL) {
    // Cache does not affect logical constness
    BuildingObject* This = (BuildingObject*)this;
    delete This->mySubject;
    This->mySubject = NULL;
  } 
}

long BuildingObject::countSubobject() const
{
  return getSubject() ? 1 : 0;   // make sure, cache is initialized
}

Object3D* BuildingObject::makeUnique(Path3D*, bool)
{
  return NULL;
}

void BuildingObject::iterateAttributes(MakeableHandler *handler) {
// buildingobject has no transformation, only textures
  if (getTexture() != NULL) {
    handler->handle((Makeable*)getTexture());
  }
  if (!isOn()) {
    DummyMakeable m("off");
    handler->handle(&m);
  } 
}
