/*
 * GSBTreeNode.h
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
 *  $Id: GSBTreeNode.h,v 1.6 1997/04/08 11:05:05 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBTreeNode_H
#define _GSBTreeNode_H

#include "booga/object/Object2D.h"
#include "booga/object/World2D.h"

#include "GSBNode.h"
#include "GSBPolygon.h"

//_____________________________________________________________________ GSBTreeNode

class GSBTreeNode : public GSBNode {
declareRTTI(GSBTreeNode);                          // enable RTTI support
 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBTreeNode(long viewID);
//  GSBTreeNode(const GSBTreeNode&);

public:
//  virtual ~GSBTreeNode();

private:
//  GSBTreeNode& operator=(const GSBTreeNode&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBTreeNode
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
//  Vector2D& connectOfs() { return connectOfs_; };
  
  void        setWidth(Real w) { myWidth = w; };
  void        setHeight(Real h) { myHeight = h; };
  void        setBorder(Real b) { myBorder = b; };
  void        setLabel(RCString& newLabel) { myLabel = newLabel; };
  void        setRelPos(Vector2D pos) { myRelPos = pos; };
  void        setAbsPos(Vector2D pos) { myAbsPos = pos; };
  GSBPolygon& contour() { return myContour; }

  Real        getWidth() const { return myWidth; };
  Real        getHeight() const { return myHeight; };
  Real        getBorder() const { return myBorder; };
  RCString    getLabel() const { return myLabel; }
  Vector2D    getRelPos() const { return myRelPos; };
  Vector2D    getAbsPos() const { return myAbsPos; };
  
  const Object2D* getRepresentation() const;
  void	       adoptRepresentation(Object2D* rep);
  Object2D*   orphanRepresentation();

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
  Real		   myBorder;
  Real		   myHeight;
  Real		   myWidth;
  GSBPolygon	   myContour;
  Vector2D       myRelPos;
  Vector2D       myAbsPos;
  Vector2D       myConnectOffset;
  
  // miscellaneous:
  RCString       myLabel;
  Object2D*      myRepresentation;
};

//______________________________________________________________________ INLINES

inline
const Object2D* GSBTreeNode::getRepresentation() const
{
  return myRepresentation;
};

#endif // _GSBTreeNode_H

