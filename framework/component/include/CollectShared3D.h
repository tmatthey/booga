/*
 * $RCSfile: CollectShared3D.h,v $
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
 *  $Id: CollectShared3D.h,v 1.7 1996/09/13 08:03:46 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _CollectShared3D_H
#define _CollectShared3D_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/MIterator.h"
#include "booga/component/Operation3D.h"

//______________________________________________________________ CollectShared3D

class CollectShared3D : public Operation3D, 
                          public MIterator<Shared3D*, List<Shared3D*> > {
declareRTTI(CollectShared3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  CollectShared3D();
private:
  // CollectShared3D(const CollectShared3D&);          // No copies.

public:
  // virtual ~CollectShared3D();                       // Use default version.

private:
  CollectShared3D& operator=(const CollectShared3D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class CollectShared3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setSortCollection(bool sort);
  bool getSortCollection() const;
  // Switch between sorted collection and order of appearence.
  // Set this flag before applying this component!
  
  Shared3D* getCurrent() const;
  // Iteration over the found shared objects is done using these 
  // member functions:
  //
  // for (collector.first(); !collector.isDone(); collector.next()) { 
  //    collector.getCurrent();

private:
  Traversal::Result visit(Shared3D* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool preprocessing();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class MIterator
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  virtual List<Shared3D*>* getContainer();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Visitor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Traversal::Result dispatch(Makeable* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  List<Shared3D*> myShared;
  long myCurrent;
  bool mySortList;
};

//______________________________________________________________________ INLINES

#endif // _CollectShared3D_H
