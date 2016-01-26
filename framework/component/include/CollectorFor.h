/*
 * $RCSfile: CollectorFor.h,v $
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
 *  $Id: CollectorFor.h,v 1.18 1996/09/13 08:03:36 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _CollectorFor_H
#define _CollectorFor_H

#include "booga/base/List.h"
#include "booga/base/SymTable.h"
#include "booga/base/MIterator.h"
#include "booga/object/PathOf.h"

//________________________________________________________________  CollectorFor

template <class TSearchObject, // Object class we are looking for
          class TObjectBase,   // Object2D or Object3D
          class TOperation,    // Operation2D or Operation3D
          class TPathOf,       // Path2D or Path3D
          class TWorld,        // World2D or World3D
          class TShared>       // Shared2D or World3D
class CollectorFor : public TOperation, 
		     public MIterator<TPathOf*,List<TPathOf*> > {
#ifndef __GNUC__
  //declareRTTI(CollectorFor);
// enable RTTI support
#endif // __GNUC__

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  CollectorFor(int size=30);

private:
  CollectorFor(const CollectorFor<TSearchObject,TObjectBase,
			       TOperation,TPathOf,TWorld,TShared>&);
  // No copies.			       

public:
  virtual ~CollectorFor();

private:
  CollectorFor<TSearchObject,TObjectBase,TOperation,TPathOf,TWorld,TShared>&
	operator=(const CollectorFor<TSearchObject,TObjectBase,
				  TOperation,TPathOf,TWorld,TShared>&); 
  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class CollectorFor<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  TSearchObject* getObject() const;
  TPathOf* getPath() const;
  TSearchObject* createTransformedObject() const;
  // 
  // Usage:
  //
  //   CollectorFor<XXX> collector.
  //   collector.execute(world);
  //
  //   for (collector.first(); !collector.isDone(); collector.next()) {
  //      .. = collector.getObject();  // or
  //      .. = collector.getPath();    // or
  //      Object* ocopy = collector.createTransformedObject();
  //   }
  
private:
  Traversal::Result visit(TShared* obj);
  Traversal::Result visit(TSearchObject* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool preprocessing();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Visitor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Traversal::Result dispatch(Makeable* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class MIterator<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  virtual List<TPathOf*>* getContainer();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  SymTable<void*,char> myVisitedShareds;
  List<TPathOf*> myCollection;
};

//_____________________________________________________________________  INLINES

template <class TSearchObject, class TObjectBase,
          class TOperation,
          class TPathOf, class TWorld, class TShared>
inline TSearchObject*
CollectorFor<TSearchObject,TObjectBase,TOperation,TPathOf,TWorld,TShared>::getObject() const
{
  return (TSearchObject*)curItem()->getLastObject();
}

template <class TSearchObject, class TObjectBase,
          class TOperation,
          class TPathOf, class TWorld, class TShared>
inline TPathOf* 
CollectorFor<TSearchObject,TObjectBase,TOperation,TPathOf,TWorld,TShared>::getPath() const
{
  return curItem();
}

template <class TSearchObject, class TObjectBase,
          class TOperation,
          class TPathOf, class TWorld, class TShared>
inline TSearchObject*
CollectorFor<TSearchObject,TObjectBase,TOperation,TPathOf,TWorld,TShared>::createTransformedObject() const
{
  return (TSearchObject*)curItem()->createLastTransformedObject();
}

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
#define TEMPLATE_IS_INCLUDE_FROM_H
#include "../component/src/CollectorFor.C"
#endif // TEMPLATE_IN_HEADER

#endif // _CollectorFor_H

