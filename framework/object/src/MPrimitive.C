/*
 * $RCSfile: MPrimitive.C,v $
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
 *  $Id: MPrimitive.C,v 1.1 1996/08/07 09:20:41 amann Exp $
 * -----------------------------------------------------------------------------
 */

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#if defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
// Only compile this file if either not GNU compiler running,
// or, in case of GNU compiler, files is included from header.

#ifdef TEMPLATE_IN_HEADER
# define INLINE inline
#else
# include "booga/object/MPrimitive.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER

static const float DEFAULT_PRECISON = 0.5;

template <class TObject, class TPrimitive, class TPath, class TRay, class TPrimitiveAttr>
INLINE MPrimitive<TObject, TPrimitive, TPath, TRay, TPrimitiveAttr>
::MPrimitive()
{
  myPrecision = DEFAULT_PRECISON;
}

template <class TObject, class TPrimitive, class TPath, class TRay, class TPrimitiveAttr>
INLINE MPrimitive<TObject, TPrimitive, TPath, TRay, TPrimitiveAttr>
::MPrimitive(Exemplar exemplar)
: TObject(exemplar)
{
  myPrecision = DEFAULT_PRECISON;
}

template <class TObject, class TPrimitive, class TPath, class TRay, class TPrimitiveAttr>
INLINE void MPrimitive<TObject, TPrimitive, TPath, TRay, TPrimitiveAttr>
::setPrecision(float precision)
{
  myPrecision = precision;
}

template <class TObject, class TPrimitive, class TPath, class TRay, class TPrimitiveAttr>
INLINE float MPrimitive<TObject, TPrimitive, TPath, TRay, TPrimitiveAttr>
::getPrecision() const
{
  return myPrecision;
}

template <class TObject, class TPrimitive, class TPath, class TRay, class TPrimitiveAttr>
INLINE long MPrimitive<TObject, TPrimitive, TPath, TRay, TPrimitiveAttr>
::countSubobject() const
{
  return 0;
}

template <class TObject, class TPrimitive, class TPath, class TRay, class TPrimitiveAttr>
INLINE TObject* MPrimitive<TObject, TPrimitive, TPath, TRay, TPrimitiveAttr>
::getSubobject(long)
{
  Report::error("[MPrimitive::getSubobject] index out of range");

  return NULL;
}

template <class TObject, class TPrimitive, class TPath, class TRay, class TPrimitiveAttr>
INLINE TObject* MPrimitive<TObject, TPrimitive, TPath, TRay, TPrimitiveAttr>
::makeUnique(TPath* path, bool shared)
{
  //
  // If we are at the end of the path or path == NULL, don't do anything.
  //
  if (path == NULL || path->isDone())
    return this;

  //
  // If a predecessor is shared more than once, we have to provide a copy
  // of ourself.
  //
  if (shared == true) {
    TObject* newPrimitive = copy();
    path->replace(newPrimitive);
    return newPrimitive;
  }
  else
    return this;
}

template <class TObject, class TPrimitive, class TPath, class TRay, class TPrimitiveAttr>
INLINE int MPrimitive<TObject, TPrimitive, TPath, TRay, TPrimitiveAttr>
::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  TPrimitiveAttr* attr = dynamic_cast<TPrimitiveAttr*>(specifier);
  if (attr != NULL) {
    // The PrimitiveAttr object knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute((TPrimitive*)this);  // need instantiated type

    delete attr;
    return 1;  
  }

  // 
  // Let papa do the rest ...
  //
  return TObject::setSpecifier(errMsg, specifier);
}

/*
 * Default implementation for all the primitives:
 *   Create decomposition of the primitive.
 *   Intersect with the decomposition.
 *   If we have a hit, add "this" as the new bestHitObject.
 */
template <class TObject, class TPrimitive, class TPath, class TRay, class TPrimitiveAttr>
INLINE bool MPrimitive<TObject, TPrimitive, TPath, TRay, TPrimitiveAttr>
::doIntersect(TRay& ray)
{
  bool hit = false;
  TObject* decomposition = createDecomposition();
      
  if (decomposition != NULL) {
    if (hit = decomposition->intersect(ray))
      ray.setBestHitObject((TPrimitive*)this);  // need instantiated type!
    delete decomposition;
  }  

  return hit;
}

#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)

