/*
 * GSBNode.h
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
 *  $Id: GSBNode.h,v 1.4 1997/04/08 11:04:48 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBNode_H
#define _GSBNode_H

#include "booga/base/Option.h"
#include "booga/object/Object3D.h"

//_____________________________________________________________________ GSBNode
// abstract base class GSBNode:

class GSBNode : public Option {
declareRTTI(GSBNode);                          // enable RTTI support
		  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBNode(long viewID);

public:
//  virtual ~GSBNode();                  // Use default version.

private:
//  GSBNode& operator=(const GSBNode&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBNode
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  long getViewID() const { return myViewID; };
  virtual void initNode(Object3D* obj) = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  long myViewID;
};

//______________________________________________________________________ INLINES

#endif // _GSBNode_H
