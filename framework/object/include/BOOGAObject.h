/*
 * $RCSfile: BOOGAObject.h,v $
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
 *  $Id: BOOGAObject.h,v 1.4 1996/08/07 16:13:38 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _BOOGAObject_H
#define _BOOGAObject_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/object/BoundsUtilities.h"
#include "booga/object/Makeable.h"
#include "booga/object/PathOf.h"

class Option;

//________________________________________________________________ BOOGAObject<>

template <class TObject, class TTransform, class TVector, class TBounds, class TRay>
class BOOGAObject : public Makeable {
  //declareRTTI(BOOGAObject);
  // enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  BOOGAObject();
protected:
  BOOGAObject(const BOOGAObject<TObject,TTransform,TVector,TBounds,TRay>& obj);
  
public:
  virtual ~BOOGAObject();

private:
  BOOGAObject<TObject,TTransform,TVector,TBounds,TRay>& 
        operator=(const BOOGAObject<TObject,TTransform,TVector,TBounds,TRay>&);
  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class BOOGAObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

public:
  virtual long countSubobject() const = 0;
  virtual TObject* getSubobject(long index) = 0;
  
// handle transformation :
public:
  void addTransform(const TTransform& transform);
  void setTransform(const TTransform& transform);
  const TTransform& getTransform() const;
  // Add (concat), set, get local transformation of object. 

// handle intersection :
public:
  bool intersect(TRay& ray);
  // ... in object coordinate system with local transformation applied
private:
  virtual bool doIntersect(TRay& ray) = 0;
  // ... in local object coordinate system
  
// handle bounding box
public:
  const TBounds& getBounds() const;
  void computeBounds();
  void computeBoundsLazy();
  // ... in object coordinate system with local transformation applied
protected:  
  virtual void doComputeBounds() = 0;
  // ... in local object coordinate system
  
// handle user data :
public:
  const Option* getUserData() const;
  void adoptUserData(Option* data);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  TTransform myTransform;  // Local transformation
  TBounds myBounds;   // Axis aligned rectangular box enclosing object. 
  Option* myUserData;
};

//_____________________________________________________________________ inline's

template <class TObject,class TTransform, class TVector, class TBounds, class TRay>
inline void BOOGAObject<TObject,TTransform,TVector,TBounds,TRay>::addTransform(const TTransform& transform)
{
  myTransform.addTransform(transform);
}

template <class TObject, class TTransform, class TVector, class TBounds, class TRay>
inline void BOOGAObject<TObject,TTransform,TVector,TBounds,TRay>::setTransform(const TTransform& transform)
{
  myTransform = transform;
}

template <class TObject, class TTransform, class TVector, class TBounds, class TRay>
inline const TTransform& BOOGAObject<TObject,TTransform,TVector,TBounds,TRay>::getTransform() const
{
  return myTransform;
}

template <class TObject, class TTransform, class TVector, class TBounds, class TRay>
inline const TBounds& BOOGAObject<TObject,TTransform,TVector,TBounds,TRay>::getBounds() const
{
  return myBounds;
}

template <class TObject, class TTransform, class TVector, class TBounds, class TRay>
inline const Option* BOOGAObject<TObject,TTransform,TVector,TBounds,TRay>::getUserData() const
{
  return myUserData;
}

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
#define TEMPLATE_IS_INCLUDE_FROM_H
#include "../object/src/BOOGAObject.C"
#endif // TEMPLATE_IN_HEADER

#endif // _BOOGAObject_H
