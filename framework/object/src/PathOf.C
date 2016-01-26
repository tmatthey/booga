/*
 * $RCSfile: PathOf.C,v $ 
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
 *  $Id: PathOf.C,v 1.8 1996/08/16 08:38:40 streit Exp $
 * -----------------------------------------------------------------------------
 */

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#if defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
// Only compile this file if either not GNU compiler running,
// or, in case of GNU compiler, files is included from header.

#include <stddef.h>
#include "booga/base/Report.h"

#ifdef TEMPLATE_IN_HEADER
# define INLINE inline
#else
# include "booga/object/PathOf.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER

//_____________________________________________________________________ PathOf<>

template <class TObject, class TTransform>
INLINE PathOf<TObject,TTransform>::PathOf()
{
  myPosition = -1;
}

template <class TObject, class TTransform>
INLINE int PathOf<TObject,TTransform>::operator==(const PathOf<TObject,TTransform>& p) const
{
  long count = myObjects.count();
  if (myObjects.count() != p.myObjects.count())
    return 0;  
  
  for (register int i=0; i<count; i++)
    if (myObjects.item(i) != p.myObjects.item(i))
      return 0;

  return 1;
}

template <class TObject, class TTransform>
INLINE int PathOf<TObject,TTransform>::operator!=(const PathOf<TObject,TTransform>& p) const
{
  return !(this->operator==(p));
}

template <class TObject, class TTransform>
INLINE void PathOf<TObject,TTransform>::append(TObject* object)
{
  if (object == NULL)
    Report::error("[PathOf<>::append] NULL pointer passed");
  else {
    myObjects.append(object);

    if (myTransforms.count() <= 0)
      myTransforms.append(object->getTransform());
    else {
      myTransforms.append(object->getTransform());
      myTransforms.item(myTransforms.count()-1).addTransform(
			 myTransforms.item(myTransforms.count()-2));
    }
  }
}

template <class TObject, class TTransform>
INLINE void PathOf<TObject,TTransform>::removeLast()
{
  if (myObjects.count() > 0) {
    myObjects.remove(myObjects.count()-1);
    myTransforms.remove(myTransforms.count()-1);
  }
  else
    Report::warning("[PathOf<>::removeLast} no elements in path");
}

template <class TObject, class TTransform>
INLINE void PathOf<TObject,TTransform>::replace(TObject* object)
{
  if (!isDone() && object != NULL)
    myObjects.item(myPosition) = object;
  else
    Report::warning("[PathOf<>::replace] illegal replacement");
}

template <class TObject, class TTransform>
INLINE void PathOf<TObject,TTransform>::reset()
{
  myObjects.removeAll();
  myTransforms.removeAll();
  myPosition = -1;
}

template <class TObject, class TTransform>
INLINE void PathOf<TObject,TTransform>::first() const
{
  if (myObjects.count() > 0)
    ((PathOf<TObject,TTransform>*)this)->myPosition = 0;	
  else
    ((PathOf<TObject,TTransform>*)this)->myPosition = -1;	
}

template <class TObject, class TTransform>
INLINE void PathOf<TObject,TTransform>::last() const
{
  ((PathOf<TObject,TTransform>*)this)->myPosition = myObjects.count()-1;
}

template <class TObject, class TTransform>
INLINE void PathOf<TObject,TTransform>::next() const
{
  ((PathOf<TObject,TTransform>*)this)->myPosition++;
  if (myPosition >= myObjects.count())
      ((PathOf<TObject,TTransform>*)this)->myPosition = -1;
}

template <class TObject, class TTransform>
INLINE void PathOf<TObject,TTransform>::prev() const
{
  ((PathOf<TObject,TTransform>*)this)->myPosition--;
}

template <class TObject, class TTransform>
INLINE bool PathOf<TObject,TTransform>::isDone() const
{
  if (myPosition < 0 || myPosition >= myObjects.count())
    return true;
  else
    return false;
}

template <class TObject, class TTransform>
INLINE TObject* PathOf<TObject,TTransform>::getObject() const
{
  if (!isDone())
    return myObjects.item(myPosition);
  else {
    Report::warning("[PathOf<>::getObject] no valid position");
    return NULL;
  }
}

template <class TObject, class TTransform>
INLINE TObject* PathOf<TObject,TTransform>::createTransformedObject() const
{
  if (!isDone()) {
    TObject* newObject = myObjects.item(myPosition)->copy();
    newObject->setTransform(myTransforms.item(myPosition));
    return newObject;
  }
  else {
    Report::warning("[PathOf<>::createTransformedObject] no valid position");
    return NULL;
  }
}

template <class TObject, class TTransform>
INLINE const TTransform& PathOf<TObject,TTransform>::getTransform() const
{
  if (!isDone())
    return myTransforms.item(myPosition);
  else 
    Report::error("[PathOf<>::getTransform] no valid position");

  //
  // Avoid warning message.
  //
  static TTransform transform;
  return transform;
}

template <class TObject, class TTransform>
INLINE TObject* PathOf<TObject,TTransform>::getLastObject() const
{
  if (myObjects.count() > 0)
    return myObjects.item(myObjects.count()-1);
  else {
    Report::warning("[PathOf<>::getLastObject] empty path");
    return NULL;
  }
}

template <class TObject, class TTransform>
INLINE TObject* PathOf<TObject,TTransform>::createLastTransformedObject() const
{
  if (myObjects.count() > 0) {
    TObject* newObject = myObjects.item(myObjects.count()-1)->copy();
    newObject->setTransform(myTransforms.item(myObjects.count()-1));
    return newObject;
  }
  else {
    Report::warning("[PathOf<>::createLastTransformedObject] empty path");
    return NULL;
  }
}

template <class TObject, class TTransform>
INLINE const TTransform& PathOf<TObject,TTransform>::getLastTransform() const
{
  if (myTransforms.count() > 0)
    return myTransforms.item(myTransforms.count()-1);
  else
    Report::warning("[PathOf<>::getLastTransform] empty path");

  //
  // Avoid warning message.
  //
  static TTransform transform;
  return transform;
}

template <class TObject, class TTransform>
INLINE const List<TObject*>& PathOf<TObject,TTransform>::getObjects() const
{
  return myObjects;
}

#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
