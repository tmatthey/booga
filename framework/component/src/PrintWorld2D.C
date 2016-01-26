/*
 * $RCSfile: PrintWorld2D.C,v $
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
 *  $Id: PrintWorld2D.C,v 1.11 1996/09/13 08:05:56 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#include "booga/base/RCString.h"
#include "booga/base/List.h"
#include "booga/object/Object2D.h"
#include "booga/object/Shared2D.h"
#include "booga/object/Aggregate2D.h"
#include "booga/component/CollectShared2D.h"
#include "booga/component/PrintWorld2D.h"

//_________________________________________________________________ PrintWorld2D

implementRTTI(PrintWorld2D, Operation2D);

PrintWorld2D::PrintWorld2D(std::ostream& os)
: myStream(os)
{}

bool PrintWorld2D::doExecute()
{
  myLevel = 0;
  
  myStream << "\n-------  The World ----------------------------------------\n\n";

  traverse(getWorld());

  World2D dummyWorld;
  CollectShared2D collector;
 
  collector.execute(getWorld());
  myLevel = 1;
  
  if (collector.count() == 0) {
    // No shared objects.
    return true;
  }
    
  myStream << "\n-------  Shared Objects -----------------------------------\n";

  for (collector.first(); !collector.isDone(); collector.next()) {
    myStream << std::endl 
	    << collector.getCurrent()->getName()
	    << "  (refs: " << collector.getCurrent()->rcCountReferences() 
	    << " addr: " << (void*)collector.getCurrent() << ")\n";

    dummyWorld.getObjects()->adoptObject(collector.getCurrent()->getSubobject(0));
    traverse(&dummyWorld);
    dummyWorld.getObjects()->orphanObject(collector.getCurrent()->getSubobject(0));
  }

  return true;
}

Traversal::Result PrintWorld2D::visit(Object2D* obj)
{
  myStream << RCString(' ', myLevel*4) << typeid(obj).name() << std::endl;

  if (obj->getTransform().getTransMatrix() != TransMatrix2D::getIdentity())
    myStream << RCString(' ', myLevel*4+2) 
	    << obj->getTransform().getTransMatrix() << std::endl;

   return Traversal::CONTINUE;
}

Traversal::Result PrintWorld2D::visit(Shared2D* obj)
{
  myStream << RCString(' ', myLevel*4) << obj->getName()
	  << " (Shared2D refs: " << obj->rcCountReferences() << ")"
	  << std::endl;
  
  if (obj->getTransform().getTransMatrix() != TransMatrix2D::getIdentity())
    myStream << RCString(' ', myLevel*4+2) 
	    << obj->getTransform().getTransMatrix() << std::endl;

  return Traversal::PRUNE;
}

Traversal::Result PrintWorld2D::dispatch(Makeable* obj)
{
  tryConcrete(Shared2D, obj);
  tryAbstract(Object2D, obj);

  return Traversal::CONTINUE;
}

void PrintWorld2D::incLevel()
{
  myLevel++;
}

void PrintWorld2D::decLevel()
{
  myLevel--;
}
