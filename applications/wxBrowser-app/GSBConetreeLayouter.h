/*
 * GSBConetreeLayouter.h
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
 *  $Id: GSBConetreeLayouter.h,v 1.5 1997/04/08 11:04:34 habegger Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _GSBConetreeLayouter_H
#define _GSBConetreeLayouter_H

#include "booga/component/Operation3D.h"

//__________________________________________________________________ GSBConetreeLayouter

class GSBConetreeLayouter : public Operation3D {
declareRTTI(GSBConetreeLayouter);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBConetreeLayouter();
  // GSBConetreeLayouter(const GSBConetreeLayouter&);          // Use default version.

public:
  // virtual GSBConetreeLayouter();                   // Use default version.

private:
  GSBConetreeLayouter& operator=(const GSBConetreeLayouter&);  // No assignments.  

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBConetreeLayouter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void	 setViewID(long viewID) { myViewID = viewID; };

  void   setBorder(long border) { myBorder = border; };
  void   setDistanceToParents(long dist) { myDistanceToParents = dist; };
  
  long   getBorder() const { return myBorder; };
  long   getDistanceToParents() const { return myDistanceToParents; };

private:
  void   visitAggregateNode(Object3D* obj);
  void   visitLeafNode(Object3D* obj);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Visitor3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
virtual Traversal::Result visit(Object3D* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Generator3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool doExecute();
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  long        myViewID;
  int         myBorder;
  int         myDistanceToParents;
};

#endif // _GSBConetreeLayouter_H
