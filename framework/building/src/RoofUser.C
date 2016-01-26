/*
 * $RCSfile: RoofUser.C,v $
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
 *  $Id: RoofUser.C,v 1.4 1997/04/21 13:29:35 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/TransMatrix3D.h"
#include "booga/object/NullObject3D.h"
#include "booga/building/RoofUser.h"
#include "booga/building/Building.h"
#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"

// ____________________________________________________________________ RoofUser

implementRTTI(RoofUser, Roof);

RoofUser::RoofUser(Exemplar exemplar)
:Roof(exemplar)
{
  myObject = NULL;
  setLedge(0);
}

RoofUser::RoofUser()
:Roof()
{
  myObject = NULL;
  setLedge(0);
}

RoofUser::RoofUser(const RoofUser& roofuser)
:Roof(roofuser)
{
  if(roofuser.myObject != NULL)
    myObject = roofuser.myObject->copy();
  else
    myObject = NULL;
  setLedge(0);
}

RoofUser::~RoofUser()
{
  if (myObject)
    delete myObject;
}

Object3D* RoofUser::copy() const
{
  return new RoofUser(*this);
}

Makeable* RoofUser::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new RoofUser(*this);
}

Object3D* RoofUser::orphanObject()
{
  Object3D* tmp = myObject;
  myObject = NULL;
  
  return tmp;
}

int RoofUser::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  Object3D* object = dynamic_cast(Object3D, specifier);
  if (object != NULL) {
    if (myObject != NULL)
      delete myObject;
    myObject = object;

    return 1;
  } 
  
  // 
  // Let papa do the rest ...
  //
  return Roof::setSpecifier(errMsg, specifier);
}

Object3D* RoofUser::doCreateSubject(Building* building) const
{
 if (myObject){
   Object3D* object = myObject->copy();
   object->addTransform(TransMatrix3D::makeTranslate(
     Vector3D(0,0,building->getVertex(0,0).z() + building->getHeight())));
   return object;
 }
 else
   return new NullObject3D;
}

void RoofUser::iterateAttributes(MakeableHandler *handler) {
  this->Roof::iterateAttributes(handler);
  if (myObject)
    handler->handle(myObject);
}

static const RCString roofuserKeyword("roofuser");

RCString RoofUser::getKeyword() const {
  return roofuserKeyword;
}
