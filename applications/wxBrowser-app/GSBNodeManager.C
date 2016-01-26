/*
 * GSBNodeManager.C 
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
 *  $Id: GSBNodeManager.C,v 1.4 1997/04/08 11:04:52 habegger Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Report.h"

#include "GSBNodeManager.h"

//_____________________________________________________________________ GSBNodeManager


implementRTTI(GSBNodeManager, Option);


GSBNodeManager::GSBNodeManager()
: myNodes(0), myMarkedFlag(false), myPrunedFlag(false)
{
}


GSBNodeManager::~GSBNodeManager()
{
  for (long i=0; i < myNodes.count(); i++)
    delete myNodes.item(i);
}


GSBNodeManager::GSBNodeManager(const GSBNodeManager&)
{}


Option* GSBNodeManager::copy() const
{
  return new GSBNodeManager(*this);
}


int GSBNodeManager::attachNode(GSBNode* aNode)
{
  long i = 0;
  for (; i < myNodes.count(); i++) {
    // already stored in the list?
    if (aNode->getViewID() == myNodes.item(i)->getViewID()) 
      return false;	// exists already!

    // insert element at the current position if the viewID is small than
    // the one stored in the list
    if (aNode->getViewID() < myNodes.item(i)->getViewID()) {
      myNodes.insert(i, aNode);
      break;
    }
  }
  if (i >= myNodes.count()) 
    myNodes.append(aNode);
  return true;
}


void GSBNodeManager::detachNode(long viewID)
{
  for (long i=0; i < myNodes.count(); i++) {
    if (myNodes.item(i)->getViewID() == viewID) {
      GSBNode* theNode = myNodes.item(i);
      myNodes.remove(i);
      delete theNode;
      break;
    }
  }
}


GSBNode* GSBNodeManager::getNode(long viewID) const
{
  for (long i=0; i < myNodes.count(); i++) {
    if (myNodes.item(i)->getViewID() == viewID) {
      return myNodes.item(i);
	}
  }
  return (GSBNode*) NULL;
}

