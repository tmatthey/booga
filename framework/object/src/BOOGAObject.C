/*
 * $RCSfile: BOOGAObject.C,v $
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
 *  $Id: BOOGAObject.C,v 1.5 1996/10/30 08:34:16 streit Exp $
 * -----------------------------------------------------------------------------
 */

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#if defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
// Only compile this file if either not GNU compiler running,
// or, in case of GNU compiler, files is included from header.

#include "booga/base/Option.h"

#ifdef TEMPLATE_IN_HEADER
# define INLINE inline
#else
# include "booga/object/BOOGAObject.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER

//implementRTTI(BOOGAObject, Makeable);

//________________________________________________________________ BOOGAObject<>

template <class TObject, class TTransform, class TVector, class TBounds, class TRay>
INLINE BOOGAObject<TObject,TTransform,TVector,TBounds,TRay>::BOOGAObject()
{
  myUserData = NULL;
}

template <class TObject, class TTransform, class TVector, class TBounds, class TRay>
INLINE BOOGAObject<TObject,TTransform,TVector,TBounds,TRay>::BOOGAObject(const BOOGAObject<TObject,TTransform,TVector,TBounds,TRay>& obj)
: Makeable(obj) 
{
  myBounds = obj.myBounds;
  myTransform = obj.myTransform;
  if (obj.myUserData != NULL)
    myUserData = obj.myUserData->copy();
  else
    myUserData = NULL;
}

template <class TObject, class TTransform, class TVector, class TBounds, class TRay>
INLINE BOOGAObject<TObject,TTransform,TVector,TBounds,TRay>::~BOOGAObject()
{
  delete myUserData;
}

template <class TObject, class TTransform, class TVector, class TBounds, class TRay>
INLINE bool BOOGAObject<TObject,TTransform,TVector,TBounds,TRay>::intersect(TRay& ray)
{
  bool hit = false;
  
  //
  // Check bounds of the object first.
  //
  if (BoundsUtilities::intersect(myBounds, ray)) {
    ray.incLevel();
    //
    // The ray has to be transformed, if a local transformation is 
    // attached to the object.
    //
    if (myTransform.isIdentity())
      hit = doIntersect(ray);
    else {
      //
      // Transform the ray.
      //
      TVector origin = ray.getOrigin();
      TVector direction = ray.getDirection();
      Real rescale = 1. / ray.transform(myTransform);

      hit = doIntersect(ray);

      //
      // 'Untransform' the ray.
      //
      ray.setOrigin(origin);
      ray.setDirection(direction);
      ray.setBestHitDistance(ray.getBestHitDistance() * rescale);
      ray.setBoundsHitDistance(ray.getBoundsHitDistance() * rescale);
      ray.setTolerance(ray.getTolerance() * rescale);
    }
    ray.decLevel();
  }
  
  if (hit)
    ray.addToPath((TObject*)this);

  return hit;
}

template <class TObject, class TTransform, class TVector, class TBounds, class TRay>
INLINE void BOOGAObject<TObject,TTransform,TVector,TBounds,TRay>::computeBoundsLazy()
{
  if (!myBounds.isEmpty())
    return;


  long count = countSubobject();
  for (long i=0; i<count; i++)
    getSubobject(i)->computeBoundsLazy();
    
  doComputeBounds(); // call of template method.

  //
  // Apply local transformation.
  //
  if (!myTransform.isIdentity())
    myBounds.transform(myTransform.getTransMatrix());

  //
  // Ensure that the bound of the object is valid:
  //    Empty bound or 
  //    Extension in any dimension does not equal zero.
  //
  myBounds.inflate(); 
}

template <class TObject, class TTransform, class TVector, class TBounds, class TRay>
INLINE void BOOGAObject<TObject,TTransform,TVector,TBounds,TRay>::computeBounds()
{
  myBounds.reset();   // Start with empty bounds.
  
  long count = countSubobject();
  for (long i=0; i<count; i++)
    getSubobject(i)->computeBounds();
    
  doComputeBounds(); // call of template method.

  //
  // Apply local transformation.
  //
  if (!myTransform.isIdentity())
    myBounds.transform(myTransform.getTransMatrix());

  //
  // Ensure that the bound of the object is valid:
  //    Empty bound or 
  //    Extension in any dimension does not equal zero.
  //
  myBounds.inflate(); 
}

template <class TObject, class TTransform, class TVector, class TBounds, class TRay>
INLINE void BOOGAObject<TObject,TTransform,TVector,TBounds,TRay>::adoptUserData(Option* data)
{
  //
  // Self assignment?
  //
  if (myUserData == data)
    return;
    
  delete myUserData;
  myUserData = data;
}

#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)

