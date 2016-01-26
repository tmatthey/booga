/*
 * $RCSfile: MAggregate.C,v $
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: MAggregate.C,v 1.1 1996/08/07 09:20:33 amann Exp $
 * -----------------------------------------------------------------------------
 */

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#if defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
// Only compile this file if either not GNU compiler running,
// or, in case of GNU compiler, files is included from header.

#include "booga/base/Report.h"

#ifdef TEMPLATE_IN_HEADER
# define INLINE inline
#else
# include "booga/object/MAggregate.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER

//___________________________________________________________________ MAggregate

template <class TObject, class TAggregate, class TPath>
INLINE MAggregate<TObject, TAggregate, TPath>
::MAggregate() {}

template <class TObject, class TAggregate, class TPath>
INLINE MAggregate<TObject, TAggregate, TPath>
::MAggregate(Exemplar exemplar)
: TObject(exemplar)
{}

template <class TObject, class TAggregate, class TPath>
INLINE MAggregate<TObject, TAggregate, TPath>
::MAggregate(const MAggregate<TObject, TAggregate, TPath>& aggregate)
: TObject(aggregate),
  myElements(aggregate.myElements.count())  
{
  for (register long i=0; i<aggregate.myElements.count(); i++)
    myElements.append(aggregate.myElements.item(i)->copy());
}
 
template <class TObject, class TAggregate, class TPath>
INLINE MAggregate<TObject, TAggregate, TPath>
::~MAggregate()
{  
  for (register long i=0; i<myElements.count(); i++)
    delete myElements.item(i);
}

template <class TObject, class TAggregate, class TPath>
INLINE void MAggregate<TObject, TAggregate, TPath>
::adoptObject(TObject* newObject)
{
  if (newObject == NULL)
    return;
    
  myElements.append(newObject);
  myBounds.expand(newObject->getBounds());
}

template <class TObject, class TAggregate, class TPath>
INLINE int MAggregate<TObject, TAggregate, TPath>
::orphanObject(const TObject* object)
{
  for (register long i=0; i<myElements.count(); i++)
    if (myElements.item(i) == object) {
      myElements.remove(i);
      return 1;
    }

  return 0;
}

template <class TObject, class TAggregate, class TPath>
INLINE int MAggregate<TObject, TAggregate, TPath>
::replaceObject(const TObject* from, TObject* to)
{
  for (register long i=0; i<myElements.count(); i++)
    if (myElements.item(i) == from) {
      myElements.item(i) = to;
      return 1;
    }

  return 0;
}

template <class TObject, class TAggregate, class TPath>
INLINE long MAggregate<TObject, TAggregate, TPath>
::countSubobject() const
{
  return myElements.count();
}

template <class TObject, class TAggregate, class TPath>
INLINE TObject* MAggregate<TObject, TAggregate, TPath>
::getSubobject(long index)
{
  if (index < 0 || index >= myElements.count())
    Report::error("[Aggregate3D::getSubobject] index out of range");

  return myElements.item(index);
}
 
template <class TObject, class TAggregate, class TPath>
INLINE TObject* MAggregate<TObject, TAggregate, TPath>
::makeUnique(TPath* path, bool shared)
{
  //
  // If we are at the end of the path or path == NULL, don't do anything.
  //
  if (path == NULL || path->isDone())
    return this;
  
  if (shared == true) {
    TAggregate* newAgg = makeEmpty();
    for (register long i=0; i<myElements.count(); i++) {
      if (myElements.item(i) != path->getObject())
	newAgg->adoptObject(myElements.item(i)->copy());
      else {
	path->next();
	myElements.item(i)->makeUnique(path, true);
	path->prev();
      }
    }
    path->replace(newAgg);
    return newAgg;
  }
  else {
    path->next();
    path->getObject()->makeUnique(path, false);
    path->prev();

    return this;
  }
}

template <class TObject, class TAggregate, class TPath>
INLINE void MAggregate<TObject, TAggregate, TPath>
::doComputeBounds()
{
  long count = countSubobject();
  for (long i=0; i< count; i++)
    myBounds.expand(getSubobject(i)->getBounds());
}

template <class TObject, class TAggregate, class TPath>
INLINE int MAggregate<TObject, TAggregate, TPath>
::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  //
  // There might be an object passed, so lets try to cast
  // specifier to Object3D* :
  //
  TObject* object = dynamic_cast<TObject*>(specifier);
  if (object != NULL) {
    adoptObject(object);
    return 1;
  }

  // 
  // Let papa do the rest ...
  //
  return TObject::setSpecifier(errMsg, specifier);
}

#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
