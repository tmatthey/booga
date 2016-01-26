/*
 * $RCSfile: MProxy.C,v $
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
 *  $Id: MProxy.C,v 1.2 1996/08/07 16:15:03 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
/*
 * GNU compiler has a pretty bad handling of templates...
 */
#if defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
// Only compile this file if either not GNU compiler running,
// or, in case of GNU compiler, files is included from header.

#include <strstream.h>
#include "booga/base/Report.h" 
#include "booga/base/Exemplar.h" 

#ifdef TEMPLATE_IN_HEADER
# define INLINE inline
#else
# include "booga/object/MProxy.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER


//_____________________________________________________________________ MProxy

template <class TObject, class TProxy, class TPath, class TRay>
INLINE MProxy<TObject, TProxy, TPath, TRay>
::MProxy()
{
  mySubject = NULL;
}

template <class TObject, class TProxy, class TPath, class TRay>
INLINE MProxy<TObject, TProxy, TPath, TRay>
::MProxy(Exemplar exemplar) 
: TObject(exemplar)

{
  mySubject = NULL;
}

template <class TObject, class TProxy, class TPath, class TRay>
INLINE MProxy<TObject, TProxy, TPath, TRay>
::MProxy(const MProxy<TObject, TProxy, TPath, TRay>& proxy)
{
  mySubject = proxy.copy();
}

template <class TObject, class TProxy, class TPath, class TRay>
INLINE MProxy<TObject, TProxy, TPath, TRay>
::~MProxy()
{
  delete mySubject;
}

template <class TObject, class TProxy, class TPath, class TRay>
INLINE TObject* MProxy<TObject, TProxy, TPath, TRay>
::getSubject() const
{
  if (mySubject == NULL) {
    // Cache does not affect logical constness
    MProxy<TObject, TProxy, TPath, TRay>* This = 
      (MProxy<TObject, TProxy, TPath, TRay>*)this;
    This->mySubject = createSubject();
  }
  
  return mySubject;
}

template <class TObject, class TProxy, class TPath, class TRay>
INLINE void MProxy<TObject, TProxy, TPath, TRay>
::subjectChanged(const TPath* path)
{
  delete mySubject;
  mySubject = NULL;
  
  
  TPath newPath;                           // create new path which ends here
  for (path->first(); path->getObject() != this && !path->isDone(); path->next())
    newPath.append(path->getObject());
  
  computeBounds();                         // recompute bounds of this  
  TObject::recomputeBounds(newPath);       // recompute bounds along new path
}

template <class TObject, class TProxy, class TPath, class TRay>
INLINE TObject* MProxy<TObject, TProxy, TPath, TRay>
::makeUnique(TPath* path, bool shared)
{
  //
  // If we are at the end of the path or path == NULL, don't do anything.
  //
  if (path == NULL || path->isDone())
    return this;
  
  // !!!!! Test! Test!!
  if (shared == true) {
    MProxy<TObject, TProxy, TPath, TRay>* newProxy = 
      (MProxy<TObject, TProxy, TPath, TRay>*)copy();

    if (newProxy->mySubject != NULL) {
      delete mySubject;
      path->next();
      newProxy->mySubject = mySubject->makeUnique(path, true);
      path->prev();
    }
    path->replace(newProxy);
    return newProxy;
  }
  else {
    path->next();
    path->getObject()->makeUnique(path, false);
    path->prev();

    return this;
  }
}

template <class TObject, class TProxy, class TPath, class TRay>
INLINE long MProxy<TObject, TProxy, TPath, TRay>
::countSubobject() const
{
  return getSubject() ? 1 : 0;   // make sure, cache is initialized
}

template <class TObject, class TProxy, class TPath, class TRay>
INLINE TObject* MProxy<TObject, TProxy, TPath, TRay>
::getSubobject(long index)
{
  TObject* retval = getSubject();
  
  if (!retval || index != 0) {
    ostrstream os;
    os << "[MProxy::getSubobject] index out of range ";
    os << "(was " << index << ")";
    Report::error(os);
  }
  
  return retval;
}

template <class TObject, class TProxy, class TPath, class TRay>
INLINE void MProxy<TObject, TProxy, TPath, TRay>
::doComputeBounds()
{
  TObject* obj = getSubject();
  if (obj)
    myBounds.expand(obj->getBounds());  
}

template <class TObject, class TProxy, class TPath, class TRay>
INLINE bool MProxy<TObject, TProxy, TPath, TRay>
::doIntersect(TRay& ray)
{
  TObject* obj = getSubject();
  if (obj)
    return obj->intersect(ray);
  else
    return false;
}

#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
