/*
 * GSBNodeTools.C 
 *
 * Copyright (C) 1996, Pascal Habegger <habegger@iam.unibe.ch>
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
 *  $Id: GSBNodeTools.C,v 1.9 1997/04/17 09:38:20 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Report.h"

#include "GSBNodeTools.h"
#include "GSBTreeNode.h"
#include "GSBNodeManager.h"

#include "booga/object/Shared3D.h"
#include "booga/component/CollectShared3D.h"

//_____________________________________________________________________ GSBNodeTools

implementRTTI(GSBNodeTools, Operation3D);


bool GSBNodeTools::doExecute()
{
  if ((myToDo == INSTALL_NODES) && (myNodePrototype == NULL)) {
    Report::error("[GSBNodeTools::execute] No node prototype specified.");
  }
  traverse(getWorld());

  World3D* dummyWorld = new World3D;
  
  CollectShared3D sharedCollector;
  sharedCollector.execute(getWorld());
  
  for (sharedCollector.first(); !sharedCollector.isDone(); sharedCollector.next()) {
    dummyWorld->getObjects()->adoptObject(sharedCollector.getCurrent()->getSubobject(0));
  }
  
  traverse(dummyWorld);

  for (sharedCollector.first(); !sharedCollector.isDone(); sharedCollector.next()) {
    dummyWorld->getObjects()->orphanObject(sharedCollector.getCurrent()->getSubobject(0));
  }
  delete dummyWorld;

  return true;
}

Traversal::Result GSBNodeTools::dispatch(Makeable* obj)
{
  tryAbstract(Object3D, obj);
  return Traversal::UNKNOWN;
}

Traversal::Result GSBNodeTools::visit(Object3D* obj)
{
  switch(myToDo) {
    case INSTALL_MANAGERS :
      {
        attachNodeManager(obj);
        break;
      }
    case INSTALL_NODES :
      {
        GSBNode* theCopy = (GSBNode*) myNodePrototype->copy();
        if (attachNode(obj, theCopy)) {
          theCopy->initNode(obj);
        }
        break;
      }
    case REMOVE_NODES : 
      {
        GSBNodeManager* theManager;
        if ((theManager = hasNodeManager(obj))) {
           theManager->detachNode(myViewID);
        }
        break;
      }
    case REMOVE_ALL : 
      obj->adoptUserData((Option*) NULL);
  }
  if (dynamic_cast(Shared3D, obj) == NULL)
    return Traversal::CONTINUE;
  else
    return Traversal::PRUNE;
}


GSBNodeManager* GSBNodeTools::getNodeManager(const Object3D* obj)
{
  GSBNodeManager* isManager = hasNodeManager(obj);
  if (isManager == NULL) {
    Report::error("[GSBNodeTools::getNodeManager] No node manager found.");
  }
  return isManager;
}


GSBNodeManager* GSBNodeTools::attachNodeManager(Object3D* obj)
{
  // check if there's already a NodeManager attached to the object:
  if (hasNodeManager(obj) != NULL) {
    Report::error("[GSBNodeTools::attachNodeManager] Tried to attach \
        NodeManager twice.");
  }
  GSBNodeManager* newManager = new GSBNodeManager;
  obj->adoptUserData(newManager);
  if (dynamic_cast(Shared3D, obj))
    newManager->setPruned(true);
  return newManager;
}


int GSBNodeTools::attachNode(Object3D* obj, GSBNode* theNode)
{
  GSBNodeManager* theManager;
  if ((theManager = hasNodeManager(obj)) == NULL) {
    theManager = attachNodeManager(obj);
  }
  return theManager->attachNode(theNode);
}


GSBNodeManager* GSBNodeTools::hasNodeManager(const Object3D* obj)
{
  return dynamic_cast(GSBNodeManager, obj->getUserData());
}


GSBNode* GSBNodeTools::getNode(Object3D* obj, long viewID)
{
  GSBNode* aNode = getNodeManager(obj)->getNode(viewID);
  if (aNode == NULL) {
    Report::error("[GSBNodeTools::getNode] Didn't get requested node.");
  }
  return aNode;
}


GSBNode* GSBNodeTools::findNode(Object3D* obj, long viewID)
{
  return getNodeManager(obj)->getNode(viewID);
}
