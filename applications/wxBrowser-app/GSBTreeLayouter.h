/*
 * GSBTreeLayouter.h
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
 *  $Id: GSBTreeLayouter.h,v 1.9 1997/04/08 11:05:02 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBTreeLayouter_H
#define _GSBTreeLayouter_H

#include "booga/base/List.h"
#include "booga/base/Vector2D.h"
#include "booga/object/World2D.h"
#include "booga/object/Shared3D.h"
#include "booga/component/Operation3DTo2D.h"

#include "GSBTreeNode.h"
#include "GSBNode2D.h"

//_____________________________________________________________________ GSBLayout

class GSBTreeLayouter : public Operation3DTo2D {
declareRTTI(GSBTreeLayouter);
// enable RTTI support

public:
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBTreeLayouter();
private:
  GSBTreeLayouter(const GSBTreeLayouter&);             // No copies.

public:
//  virtual ~GSBTreeLayouter();                        // Use default version

private:
  GSBTreeLayouter& operator=(const GSBTreeLayouter&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBTreeLayouter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void   setViewID(long viewID) { myViewID = viewID; };

  void   setBorder(long border) { myBorder = border; };
  void   setDistanceToParents(long dist) { myDistanceToParents = dist; };
  void   setVertical(bool vertical) { myVertical = vertical; };
  
  long   getBorder() const { return myBorder; };
  long   getDistanceToParents() const { return myDistanceToParents; };
  bool   getVertical() const { return myVertical; };
  
  void   markRep(Object3D* obj, GSBNode2D* rep);

private:
  // layouting methods:
  void   layoutLeaf(Object3D* obj);
  Real   join(Object3D* obj);
  void   attachParent(Object3D* obj, Real vHeight);
  Real   merge(GSBPolygon* c1, GSBPolygon* c2);
  Real   offset(const Vector2D& pos, const Vector2D& a, const Vector2D& b);
  GSBPolyline* bridge(GSBPolyline* line1, Vector2D ofs1, 
                      GSBPolyline* line2, Vector2D ofs2);
  GSBPolyline* createPolyline(Real dx, Real dy, GSBPolyline* link);
  
  // auxiliary methods:
  GSBTreeNode* getChildNode(Object3D* obj, long i);
  void         garbageCollection();
  Object2D*    createRep(Object3D* obj, GSBTreeNode* node);
    
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual bool doExecute();
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Visitor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Traversal::Result dispatch(Makeable* obj);
  
private:
  virtual Traversal::Result visit(Object3D* obj);
  virtual Traversal::Result visit(Shared3D* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  long                myViewID;
  GSBTreeNode*        myNode;
  
  // layouting algorithm:
  long                myBorder;
  long                myDistanceToParents;
  bool                myVertical;
  List<GSBPolyline*>  myMemory;
  GSBPolygon          myContour;
};

//______________________________________________________________________ INLINES

#endif // _GSBTreeLayouter_H
