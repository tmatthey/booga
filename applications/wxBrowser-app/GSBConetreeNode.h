/*
 * GSBConetreeNode.h
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
 *  $Id: GSBConetreeNode.h,v 1.4 1997/04/08 11:04:36 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBConetreeNode_H
#define _GSBConetreeNode_H

#include "booga/object/World2D.h"
#include "GSBNode.h"
#include "GSBPolygon.h"

//_____________________________________________________________________ GSBConetreeNode

class GSBConetreeNode : public GSBNode {
declareRTTI(GSBConetreeNode);                          // enable RTTI support
 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBConetreeNode(long viewID);
//  GSBConetreeNode(const GSBConetreeNode&);

public:
//  virtual ~GSBConetreeNode();

private:
//  GSBConetreeNode& operator=(const GSBConetreeNode&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBConetreeNode
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void		setWidth(Real width) { myWidth = width; };
  Real		getWidth() const { return myWidth; };
  
  void		setHeight(Real height) { myHeight = height; };
  Real		getHeight() const { return myHeight; };
  
  void		setLabel(RCString& newLabel) { myLabel = newLabel; };
  RCString	getLabel() const { return myLabel; }

  void		adoptRepresentation(Object3D* rep) { myRep = rep; };
  Object3D* getRepresentation() { return myRep; };


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class GSBNode
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  virtual void initNode(Object3D* obj);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Option
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Option* copy() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  // layout algorithm:
  Real			myWidth;
  Real			myHeight;
  
  // miscellaneous:
  RCString	myLabel;
  Object3D*	myRep;
};

//______________________________________________________________________ INLINES

#endif // _GSBConetreeNode_H

