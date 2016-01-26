/*
 * $RCSfile: PrintWorld3D.C,v $
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: PrintWorld3D.C,v 1.11 1996/09/13 08:05:58 streit Exp $
 * -----------------------------------------------------------------------------
 */
  
#include "booga/base/RCString.h"
#include "booga/base/List.h"
#include "booga/object/Object3D.h"
#include "booga/object/Shared3D.h"
#include "booga/object/Aggregate3D.h"
#include "booga/component/CollectShared3D.h"
#include "booga/component/PrintWorld3D.h"

//_________________________________________________________________ PrintWorld3D

implementRTTI(PrintWorld3D, Operation3D);

PrintWorld3D::PrintWorld3D(ostream& os)
: myStream(os)
{}

bool PrintWorld3D::doExecute()
{
  myLevel = 0;
  
  myStream << "\n-------  The World ----------------------------------------\n\n";

  traverse(getWorld());

  World3D dummyWorld;
  CollectShared3D collector;
 
  collector.execute(getWorld());
  myLevel = 1;
  
  if (collector.count() == 0) {
    // No shared objects.
    return true;
  }
  
  myStream << "\n-------  Shared Objects -----------------------------------\n";

  for (collector.first(); !collector.isDone(); collector.next()) {
    myStream << endl 
	    << collector.getCurrent()->getName()
	    << "  (refs: " << collector.getCurrent()->rcCountReferences() 
	    << " addr: " << (void*)collector.getCurrent() << ")\n";

    dummyWorld.getObjects()->adoptObject(collector.getCurrent()->getSubobject(0));
    traverse(&dummyWorld);
    dummyWorld.getObjects()->orphanObject(collector.getCurrent()->getSubobject(0));
  }

  return true;
}

Traversal::Result PrintWorld3D::visit(Object3D* obj)
{
  myStream << RCString(' ', myLevel*4) << typeid(obj).name() << endl;

  if (obj->getTransform().getTransMatrix() != TransMatrix3D::getIdentity())
    myStream << RCString(' ', myLevel*4+2) 
	    << obj->getTransform().getTransMatrix() << endl;

   return Traversal::CONTINUE;
}

Traversal::Result PrintWorld3D::visit(Shared3D* obj)
{
  myStream << RCString(' ', myLevel*4) << obj->getName()
	  << " (Shared3D refs: " << obj->rcCountReferences() << ")"
	  << endl;
  
  if (obj->getTransform().getTransMatrix() != TransMatrix3D::getIdentity())
    myStream << RCString(' ', myLevel*4+2) 
	    << obj->getTransform().getTransMatrix() << endl;

  return Traversal::PRUNE;
}

Traversal::Result PrintWorld3D::dispatch(Makeable* obj)
{
  tryConcrete(Shared3D, obj);
  tryAbstract(Object3D, obj);

  return Traversal::CONTINUE;
}

void PrintWorld3D::incLevel()
{
  myLevel++;
}

void PrintWorld3D::decLevel()
{
  myLevel--;
}
