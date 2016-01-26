/*
 * GSBConetreeNode.C 
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
 *  $Id: GSBConetreeNode.C,v 1.4 1997/04/08 11:04:35 habegger Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "GSBConetreeNode.h"
#include "GSBNodeTools.h"
#include "booga/object/Shared3D.h"
#include "booga/object/Text3D.h"

//_____________________________________________________________________ GSBConetreeNode

implementRTTI(GSBConetreeNode, GSBNode);

GSBConetreeNode::GSBConetreeNode(long viewID) 
: GSBNode(viewID)
{}


Option* GSBConetreeNode::copy() const
{
  return new GSBConetreeNode(*this);
}


void GSBConetreeNode::initNode(Object3D* obj)
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
  Text3D label(myLabel);
  label.setHeight(myHeight * .8);
  label.computeBounds();
  myWidth = (label.getBounds().getMax() - label.getBounds().getMin()).y() * 1.2;
}
