/*
 * $RCSfile: MShared.C,v $
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
 *  $Id: MShared.C,v 1.9 1996/10/11 14:27:50 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
/*
 * GNU compiler has a pretty bad handling of templates...
 */
#if defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
// Only compile this file if either not GNU compiler running,
// or, in case of GNU compiler, files is included from header.

#include <sstream>
#include "booga/base/Report.h"
#include "booga/object/MakeableHandler.h"

#ifdef TEMPLATE_IN_HEADER
# define INLINE inline
#else
# include "booga/object/MShared.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER

//_____________________________________________________________________ TShared

/*_________________________________________________________________ Shared3DImpl
 *
 * The class Shared3DImpl supports the additional degree of 
 * indirection necessary to handle reference counting. The class
 * basically just a place holder for an Object3D pointer.
 *
 */

template <class TObject>
class SharedImpl : public RCLetter {
public:
  SharedImpl(TObject* object);
  virtual ~SharedImpl();

  virtual RCLetter* rcCopy() const; 
  // abstract method in base class RCLetter

  void setTypeName(const Name& name);
  const Name& getTypeName() const;

  TObject* myObject;
  Name myTypeName; // Shared's type name is stored in letter!
};

template <class TObject>
INLINE SharedImpl<TObject>::SharedImpl(TObject* object)
{
  myObject = object;
}

template <class TObject>
INLINE SharedImpl<TObject>::~SharedImpl()
{
  if (myObject) 
    delete myObject;
}

template <class TObject>
INLINE RCLetter* SharedImpl<TObject>::rcCopy() const 
{
  return new SharedImpl<TObject>(myObject->copy());
}


template <class TObject>
INLINE void SharedImpl<TObject>::setTypeName(const Name& name) {
  myTypeName = name;
}

template <class TObject>
INLINE const Name& SharedImpl<TObject>::getTypeName() const {
  return myTypeName;
}

//_____________________________________________________________________ Shared3D

template <class TObject, class TShared, class TPath, class TRay>
INLINE void MShared<TObject, TShared, TPath, TRay>::adoptObject(TObject* newObject)
{
  if (newObject == NULL)
    return;
    
  if (((SharedImpl<TObject>*) myLetter)->myObject)
    delete ((SharedImpl<TObject>*) myLetter)->myObject;
    
  ((SharedImpl<TObject>*) myLetter)->myObject = newObject;
}

template <class TObject, class TShared, class TPath, class TRay>
INLINE TObject* MShared<TObject, TShared, TPath, TRay>
::getObject()
{
  return ((SharedImpl<TObject>*) myLetter)->myObject;
}

template <class TObject, class TShared, class TPath, class TRay>
INLINE MShared<TObject, TShared, TPath, TRay>
::MShared(TObject* adoptObject)
: RCEnvelope(new SharedImpl<TObject>(adoptObject))
{
  setName(generateUniqueName());
}

template <class TObject, class TShared, class TPath, class TRay>
INLINE MShared<TObject, TShared, TPath, TRay>
::MShared(TObject* adoptObject, const Name defName)
: RCEnvelope(new SharedImpl<TObject>(adoptObject))
{
  setTypeName(defName);
}

template <class TObject, class TShared, class TPath, class TRay>
INLINE Name MShared<TObject, TShared, TPath, TRay>
::generateUniqueName()
{
  static long ourCurrentNameNumber;   // implicit initialisation to 0

  std::stringstream os;
  os << "_MShared" << ourCurrentNameNumber;
  ourCurrentNameNumber++;
  return Name(os); 
}

template <class TObject, class TShared, class TPath, class TRay>
INLINE TObject* MShared<TObject, TShared, TPath, TRay>
::copy() const
{
  // Reference counting is handled by the copy constructor of 
  // class RCEnvelope.
  return new TShared(*((TShared*)this));  // need instantiated type!
}

template <class TObject, class TShared, class TPath, class TRay>
INLINE long MShared<TObject, TShared, TPath, TRay>
::countSubobject() const
{
  return 1;
}

template <class TObject, class TShared, class TPath, class TRay>
INLINE TObject* MShared<TObject, TShared, TPath, TRay>
::getSubobject(long index)
{
  if (index != 0)
    Report::error("[MShared::getSubobject] index out of range");

  return getObject();
}

template <class TObject, class TShared, class TPath, class TRay>
INLINE TObject* MShared<TObject, TShared, TPath, TRay>
::makeUnique(TPath* path, bool shared)
{
  //
  // If we are at the end of the path or path == NULL, don't do anything.
  //
  if (path == NULL || path->isDone())
    return this;
  
  if (shared == false && rcIsShared()) {
    path->next();
    TObject* obj = getObject()->makeUnique(path, true);
    path->prev();

    rcDeref(); // release the old implementation
    myLetter = new SharedImpl<TObject>(obj);
    return this;
  }
  else if (shared) {
    path->next();
    TObject* obj = getObject()->makeUnique(path, true);
    path->prev();

    TShared* newShared = new TShared(obj);
    path->replace(newShared);
    return newShared;
  }
  else {
    path->next();
    getObject()->makeUnique(path, false);
    path->prev();
    return this;
  }
}

template <class TObject, class TShared, class TPath, class TRay>
INLINE void MShared<TObject, TShared, TPath, TRay>
::doComputeBounds()
{
  myBounds = getObject()->getBounds();
}

template <class TObject, class TShared, class TPath, class TRay>
INLINE bool MShared<TObject, TShared, TPath, TRay>
::doIntersect(TRay& ray)
{
  return getObject()->intersect(ray);
}

template <class TObject, class TShared, class TPath, class TRay>
INLINE Makeable* MShared<TObject, TShared, TPath, TRay>
::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return copy();
}

template <class TObject, class TShared, class TPath, class TRay>
INLINE void MShared<TObject, TShared, TPath, TRay>
::setTypeName(const Name& name)
{
  ((SharedImpl<TObject>*) myLetter)->setTypeName(name);
}

template <class TObject, class TShared, class TPath, class TRay>
INLINE const Name& MShared<TObject, TShared, TPath, TRay>
::getTypeName() const
{
  return ((SharedImpl<TObject>*) myLetter)->getTypeName();
}

template <class TObject, class TShared, class TPath, class TRay>
INLINE RCString MShared<TObject, TShared, TPath, TRay>
::getKeyword() const 
{
  return RCString(((SharedImpl<TObject>*) myLetter)->getTypeName());
}

template <class TObject, class TShared, class TPath, class TRay>
INLINE void MShared<TObject, TShared, TPath, TRay>
::iterateAttributes(MakeableHandler* handler)
{
  handler->handle(getObject());
}

#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)


