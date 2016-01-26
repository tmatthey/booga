/*
 * $RCSfile: CollectBuilding.h,v $
 *
 * Copyright (C) 1994-96, Andrey Collison <collison@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: CollectBuilding.h,v 1.4 1996/09/13 08:03:49 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _CollectBuilding_H
#define _CollectBuilding_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/MIterator.h"
#include "booga/component/Operation3D.h"

class Building;

//______________________________________________________________ CollectBuilding

class CollectBuilding : public Operation3D, 
                           public MIterator<Building*, List<Building*> > {
declareRTTI(CollectBuilding);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  CollectBuilding();
private:
  // CollectBuilding(const CollectBuilding&);          // No copies.

public:
  // virtual ~CollectBuilding();                       // Use default version.

private:
  CollectBuilding& operator=(const CollectBuilding&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class CollectBuilding
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setSortCollection(bool sort);
  bool getSortCollection() const;
  // Switch between sorted collection and order of appearence.
  // Set this flag before applying this component!
  
  Building* getCurrent() const;
  // Iteration over the found Building objects is done using these 
  // member functions:
  //
  // for (collector.first(); !collector.isDone(); collector.next()) { 
  //    collector.getCurrent();

private:
  Traversal::Result visit(Building* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool preprocessing();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class MIterator
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  virtual List<Building*>* getContainer();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Visitor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Traversal::Result dispatch(Makeable* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  List<Building*> myBuilding;
  long myCurrent;
  bool mySortList;
};

//______________________________________________________________________ INLINES

#endif // _CollectBuilding_H
