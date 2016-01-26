/*
 * GSBConetreeLayouter.C
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: GSBConetreeLayouter.C,v 1.8 1997/04/08 11:04:32 habegger Exp $
 * -----------------------------------------------------------------------------
 */
   

#include "GSBFastTraversal3D.h"
#include "GSBConetreeLayouter.h"
#include "GSBConetreeNode3D.h"
#include "GSBConetreeNode.h"
#include "GSBNodeTools.h"

#include "booga/object/List3D.h"
#include "booga/object/Cylinder3D.h"
#include "booga/object/Shared3D.h"


//__________________________________________________________________ GSBConetreeLayouter

implementRTTI(GSBConetreeLayouter, Operation3D);


GSBConetreeLayouter::GSBConetreeLayouter()
: myViewID(-1), myBorder(20), myDistanceToParents(80)
{
}


bool GSBConetreeLayouter::doExecute()
{
  if (myViewID < 0) {
    Report::error("[GSBConetreeLayouter::generate] ID of view not specified");
  }
  adoptTraversal(new GSBFastTraversal3D);
  traverse(getWorld());

  // get the built world representation:
  GSBConetreeNode* headNode = dynamic_cast(GSBConetreeNode,  
    (GSBNodeTools::getNode(getWorld()->getObjects(), myViewID)));
  if (headNode->getRepresentation() == NULL) {
    Report::error("[GSBTreeLayouter::generate] Something's buggy...");
  }
  Object3D* worldRep = headNode->getRepresentation();
  World3D* result = new World3D;
  result->getObjects()->adoptObject(worldRep);
  adoptResult(result);
  return true;
}


Traversal::Result GSBConetreeLayouter::visit(Object3D* obj)
{
  if (GSBNodeTools::getNodeManager(obj)->isPruned() || (obj->countSubobject() == 0) ) {
    visitLeafNode(obj);
    return Traversal::PRUNE;
  }
  else {  
    visitAggregateNode(obj);
    return Traversal::CONTINUE;
  }
}


void GSBConetreeLayouter::visitLeafNode(Object3D* obj)
{
  GSBConetreeNode *node = dynamic_cast(GSBConetreeNode, 
        GSBNodeTools::getNode(obj, myViewID));
  GSBConetreeNode3D *theRep = new GSBConetreeNode3D(node->getLabel(),
        node->getWidth(), node->getHeight());
  theRep->setRepresentWho(obj);
  theRep->computeBounds();
  node->adoptRepresentation(theRep);
}


void GSBConetreeLayouter::visitAggregateNode(Object3D* obj)
{
  GSBConetreeNode* node = dynamic_cast(GSBConetreeNode, 
        GSBNodeTools::getNode(obj, myViewID));
  GSBConetreeNode3D* thisNodeRep = new GSBConetreeNode3D(node->getLabel(), 
        node->getWidth(), node->getHeight());
        
  thisNodeRep->setRepresentWho(obj);
  
  List3D* theRep = new List3D;
  theRep->adoptObject(thisNodeRep);
  
  List3D* childList = new List3D;
  Real radius = 0.0;
  long i;
  for(i = 0; i < obj->countSubobject(); i++) {
    GSBConetreeNode* child = dynamic_cast(GSBConetreeNode, 
    GSBNodeTools::getNode(obj->getSubobject(i), myViewID));
    Object3D* childRep = child->getRepresentation();
    childList->adoptObject(childRep);
    radius = max(radius, (childRep->getBounds().getMax() -
                          childRep->getBounds().getMin()).z() + myBorder);
  }
  if (childList->countSubobject() == 1) {
    radius = 0.0;
  }
  radius /= 1.2;
  float angle = 2 * M_PI / childList->countSubobject();
  for(i = 0; i < childList->countSubobject(); i++) {
    TransMatrix3D tm = TransMatrix3D::makeRotateY(-angle * i);
    tm.translate(0,0,radius);
    tm.rotateY(angle * i);
    childList->getSubobject(i)->addTransform(tm);
		
    Cylinder3D* connect = new Cylinder3D(2, 
      Vector3D(0,0,0), Vector3D(0, myDistanceToParents,radius));
    connect->addTransform(TransMatrix3D::makeRotateY(angle * i));		
    connect->addTransform(TransMatrix3D::makeTranslate(0,node->getWidth(),0));
    theRep->adoptObject(connect);
  }
  TransMatrix3D tm = TransMatrix3D::makeTranslate(0, 
										  myDistanceToParents + node->getWidth(),0);
  childList->addTransform(tm);
  
  theRep->adoptObject(childList);
  theRep->computeBounds();
  node->adoptRepresentation(theRep);
}
