/*
 * $RCSfile: GDBTraversal.C,v $
 *
 * Copyright (C) 1996, Andrey Collison <collison@iam.unibe.ch>
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
 *  $Id: GDBTraversal.C,v 1.3 1996/12/06 16:44:36 collison Exp $
 * -----------------------------------------------------------------------------
 */


#include "GDBTraversal.h"
#include "GDBData.h"
#include "GDBOperation.h"

//_____________________________________________________________________ GDBTraversal


GDBTraversal::GDBTraversal() :
myTraverseRelation(GDBTraversal::NONE),
myPreorder(true),
myMultiVisit(false),
myVisited(256),
myOperation(NULL)
{}

GDBTraversal::~GDBTraversal() {}

bool GDBTraversal::traverse(GDBData *object) {
  myVisited.removeAll(); // reinitialize symbol table

  if (object == NULL) return true;

  return doTraverse(object);
}

bool GDBTraversal::doTraverse(GDBData *object) {
  if (object == NULL) return true;

  RCString currentObject(object->getNameId());
  int dummy;
    
  if (!myMultiVisit) {
    // has the object allready been visited?)
    if (myVisited.lookup(currentObject,dummy)) return true; // prune current branch
  }

  GDBTraversal::Result state = CONTINUE;
  if (myPreorder) {
    state = myOperation->visit(object);
  } 
  else {
    state = myOperation->announceVisit(object);
  }
  
  if (!myMultiVisit) {
    // add object the ones that have allready been visited
    myVisited.insert(currentObject,dummy);
  }
   
  switch(state) {
    case GDBTraversal::EXIT:
      return false;
    case GDBTraversal::PRUNE:
    case GDBTraversal::CONTINUE:
    case GDBTraversal::UNKNOWN:
      break;
    default: 
      Report::recoverable("[GDBTraversal::doTraverse] unknown tag (Result)");
      return false;
  }
  // 
  // Visit the subobjects...
  //
  long i=0; // to be left here for AIX Compiler
  if (state == CONTINUE) {
    switch(myTraverseRelation) {
      case GDBTraversal::PARTS:
        for(i=0; i<object->getParts().count(); i++) {
          GDBData* nextObject = object->getParts().getElement(i).getPtr();
          if (!doTraverse(nextObject)) return false;
        }
        break;
      case GDBTraversal::PARTOF:
        break;
      case GDBTraversal::NONE:
        break;
      default:      
        Report::recoverable("[GDBTraversal::doTraverse] unknown tag (TraverseRelation)");
        return false;
    }
  }
  
  if (!myPreorder) { // i.e. if postorder traversal
    state = myOperation->visit(object); 

    switch(state) {
      case GDBTraversal::EXIT:
        return false;
      case GDBTraversal::PRUNE:
      case GDBTraversal::CONTINUE:
      case GDBTraversal::UNKNOWN:
        break;
      default: 
        Report::recoverable("[GDBTraversal::doTraverse] unknown tag (Result)");
        return false;  
    }
  }
  return true;
}
