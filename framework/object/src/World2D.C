/*
 * $RCSfile: World2D.C,v $
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
 *  $Id: World2D.C,v 1.11 1996/10/30 08:34:21 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Exemplar.h"
#include "booga/object/List2D.h"
#include "booga/object/World2D.h"
#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"

//______________________________________________________________________ World2D

implementRTTI(World2D, World);

World2D::World2D()
{
  myRootAggregatePrototype = new List2D(anExemplar);
  myObjects = (Aggregate2D*)(myRootAggregatePrototype->copy());
}

World2D::World2D(const World2D& world)
{
  myObjects = (Aggregate2D*)(world.myObjects->copy());
  myRootAggregatePrototype = 
    (Aggregate2D*)(world.myRootAggregatePrototype->copy());
}
 
World2D::~World2D()
{
  delete myObjects;
  delete myRootAggregatePrototype;
}

void World2D::adoptRootAggregate(Aggregate2D* prototype)
{
  if (myRootAggregatePrototype != prototype) {
    delete myRootAggregatePrototype;
    myRootAggregatePrototype = prototype;
  }
}

Aggregate2D* World2D::getObjects() const
{
  return myObjects;
}

Aggregate2D* World2D::orphanObjects()
{
  Aggregate2D* retval = myObjects;
  myObjects = (Aggregate2D*)(myRootAggregatePrototype->copy());

  return retval;
}

int World2D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  //
  // There are not so many different valid specifier types:
  // First lets try, if it is a Object2D ...
  //
  Object2D* object = dynamic_cast<Object2D*>(specifier);
  if (object != NULL) {
    myObjects->adoptObject(object);
    return 1;
  } 

  // 
  // Let papa do the rest ...
  //
  return World::setSpecifier(errMsg, specifier);
}

Makeable* World2D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new World2D();
}

World* World2D::copy() const
{
  return new World2D(*this);
}

bool World2D::isEmpty() const
{
  if (myObjects != NULL && myObjects->countSubobject() > 0)
    return false;
  else
    return true;
}

void World2D::iterateAttributes(MakeableHandler *handler) {
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
