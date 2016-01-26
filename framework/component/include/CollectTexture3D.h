/*
 * $RCSfile: CollectTexture3D.h,v $
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
 *  $Id: CollectTexture3D.h,v 1.4 1996/09/13 08:03:49 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _CollectTexture3D_H
#define _CollectTexture3D_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/MIterator.h"
#include "booga/component/Operation3D.h"

//______________________________________________________________ CollectTexture3D

class CollectTexture3D : public Operation3D, 
                           public MIterator<Texture3D*, List<Texture3D*> > {
declareRTTI(CollectTexture3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  CollectTexture3D();
private:
  // CollectTexture3D(const CollectTexture3D&);          // No copies.

public:
  // virtual ~CollectTexture3D();                       // Use default version.

private:
  CollectTexture3D& operator=(const CollectTexture3D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class CollectTexture3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setSortCollection(bool sort);
  bool getSortCollection() const;
  // Switch between sorted collection and order of appearence.
  // Set this flag before applying this component!
  
  Texture3D* getCurrent() const;
  // Iteration over the found Texture objects is done using these 
  // member functions:
  //
  // for (collector.first(); !collector.isDone(); collector.next()) { 
  //    collector.getCurrent();

private:
  Traversal::Result visit(Object3D* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool preprocessing();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class MIterator
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  virtual List<Texture3D*>* getContainer();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Visitor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Traversal::Result dispatch(Makeable* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  List<Texture3D*> myTexture;
  long myCurrent;
  bool mySortList;
};

//______________________________________________________________________ INLINES

#endif // _CollectTexture3D_H
