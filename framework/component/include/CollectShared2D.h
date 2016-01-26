/*
 * $RCSfile: CollectShared2D.h,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
 *                        University of Berne, Switzerland
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
 *  $Id: CollectShared2D.h,v 1.7 1996/09/13 08:03:39 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _CollectShared2D_H
#define _CollectShared2D_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/MIterator.h"
#include "booga/component/Operation2D.h"

//______________________________________________________________ CollectShared2D

class CollectShared2D : public Operation2D, 
                          public MIterator<Shared2D*, List<Shared2D*> > {
declareRTTI(CollectShared2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  CollectShared2D();
private:
  // CollectShared2D(const CollectShared2D&);          // No copies.

public:
  // virtual ~CollectShared2D();                       // Use default version.

private:
  CollectShared2D& operator=(const CollectShared2D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class CollectShared2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setSortCollection(bool sort);
  bool getSortCollection() const;
  // Switch between sorted collection and order of appearence.
  // Set this flag before applying this component!
  
  Shared2D* getCurrent() const;
  // Iteration over the found shared objects is done using these 
  // member functions:
  //
  // for (collector.first(); !collector.isDone(); collector.next()) { 
  //    collector.getCurrent();

private:
  Traversal::Result visit(Shared2D* obj);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool preprocessing();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class MIterator
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  virtual List<Shared2D*>* getContainer();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Visitor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Traversal::Result dispatch(Makeable* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  List<Shared2D*> myShared;
  long myCurrent;
  bool mySortList;
};

//______________________________________________________________________ INLINES

#endif // _CollectShared2D_H

