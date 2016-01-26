/*
 * GSBTreeNode.C 
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
 *  $Id: GSBTreeNode.C,v 1.8 1997/04/08 11:05:04 habegger Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "GSBTreeNode.h"
#include "GSBNodeTools.h"
#include "booga/object/Shared3D.h"
#include "booga/object/Text2D.h"


//_____________________________________________________________________ GSBTreeNode

implementRTTI(GSBTreeNode, GSBNode);

GSBTreeNode::GSBTreeNode(long viewID) 
: GSBNode(viewID),
  myRepresentation(NULL)
{}


//GSBTreeNode::GSBTreeNode(const GSBTreeNode&)
//{}


Option* GSBTreeNode::copy() const
{
  return new GSBTreeNode(*this);
}


void GSBTreeNode::initNode(Object3D* obj)
{
  Shared3D* sharedObj = dynamic_cast(Shared3D, obj);
  if (sharedObj) {
    RCString name(sharedObj->getName());
    if (!name.isEmpty())
      myLabel = name.chars();
    else
      myLabel = typeid(sharedObj).name();
  } else
      myLabel = typeid(obj).name();
  Text2D label(myLabel);
  label.setHeight(myHeight * .8);
  label.computeBounds();
  myWidth = (label.getBounds().getMax() - label.getBounds().getMin()).x() * 1.2;
}


void GSBTreeNode::adoptRepresentation(Object2D* rep)
{
  if (rep == NULL) {
    Report::warning("[GSBTreeNode::adoptRepresentation] NULL representation passed!");
    return;
  }
  if (myRepresentation == rep)
    return;
  delete myRepresentation;  
  myRepresentation = rep;
}


Object2D* GSBTreeNode::orphanRepresentation()
{
  Object2D* rep = myRepresentation;
  myRepresentation = (Object2D*) NULL;
  return rep;
}
