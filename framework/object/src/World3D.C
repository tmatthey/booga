/*
 * $RCSfile: World3D.C,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: World3D.C,v 1.12 1996/10/30 08:34:22 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Exemplar.h"
#include "booga/object/List3D.h"
#include "booga/object/World3D.h"
#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"

//______________________________________________________________________ World3D

implementRTTI(World3D, World);

World3D::World3D()
{
  myRootAggregatePrototype = new List3D(anExemplar);
  myObjects = (Aggregate3D*)myRootAggregatePrototype->copy();
}

World3D::World3D(const World3D& world)
{
  myObjects = (Aggregate3D*)(world.myObjects->copy());
  myRootAggregatePrototype = 
    (Aggregate3D*)(world.myRootAggregatePrototype->copy());
}
 
World3D::~World3D()
{
  delete myObjects;
  delete myRootAggregatePrototype;
}

void World3D::adoptRootAggregate(Aggregate3D* prototype)
{
  if (myRootAggregatePrototype != prototype) {
    delete myRootAggregatePrototype;
    myRootAggregatePrototype = prototype;
  }
}

Aggregate3D* World3D::getObjects() const
{
  return myObjects;
}

Aggregate3D* World3D::orphanObjects() 
{
  Aggregate3D* retval = myObjects;
  myObjects = (Aggregate3D*)(myRootAggregatePrototype->copy());

  return retval;
}

int World3D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  //
  // There are not so many different valid specifier types:
  // First lets try, if it is a Object3D ...
  //
  Object3D* object = dynamic_cast(Object3D, specifier);
  if (object != NULL) {
    myObjects->adoptObject(object);
    return 1;
  } 

  // 
  // Let papa do the rest ...
  //
  return World::setSpecifier(errMsg, specifier);
}

Makeable* World3D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new World3D();
}

World* World3D::copy() const
{
  return new World3D(*this);
}

bool World3D::isEmpty() const
{
  if (myObjects != NULL && myObjects->countSubobject() > 0)
    return false;
  else
    return true;
}

void World3D::iterateAttributes(MakeableHandler *handler) {
  RCString name(getName());
  if (!name.isEmpty()) {
    RCString quoteName(RCString("\"") + name + RCString("\""));
    DummyMakeable name("name", quoteName);
    handler->handle(&name);
  }
  if (myObjects == NULL) return;
  for (int i=0; i<myObjects->countSubobject(); i++) {
    handler->handle(myObjects->getSubobject(i));
  }
}
