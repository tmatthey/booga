/*
 * $RCSfile: MBistableObject.C,v $ 
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
 *  $Id: MBistableObject.C,v 1.4 1996/09/13 08:04:51 streit Exp $
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
# include "booga/object/MBistableObject.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER


//________________________________________________________________ BistableObject3D

template <class TInteractionObject, class TBistableObject, class TObject, class TObjectAttr, class TShared, class TWorld, class TPath>
INLINE MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>
::MBistableObject(Exemplar exemplar)
: TInteractionObject(exemplar) 
{
  myCurState = ON;
  myOn = NULL;
  myOff = NULL;
}

template <class TInteractionObject, class TBistableObject, class TObject, class TObjectAttr, class TShared, class TWorld, class TPath>
INLINE MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>
::MBistableObject(TObject* on, TObject* off, Switch state)
{
  myCurState = state;
  myOn = new TShared(on);
  myOff = new TShared(off);
}

template <class TInteractionObject, class TBistableObject, class TObject, class TObjectAttr, class TShared, class TWorld, class TPath>
INLINE MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>
::MBistableObject(const MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>& obj)
{
  myCurState = obj.myCurState;
  myOn  = (TShared*)(obj.myOn  ? obj.myOn->copy()  : NULL);
  myOff = (TShared*)(obj.myOff ? obj.myOff->copy() : NULL);
}

template <class TInteractionObject, class TBistableObject, class TObject, class TObjectAttr, class TShared, class TWorld, class TPath>
INLINE MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>
::~MBistableObject()
{
  delete myOn;
  delete myOff;
}

template <class TInteractionObject, class TBistableObject, class TObject, class TObjectAttr, class TShared, class TWorld, class TPath>
INLINE void MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>
::adoptOn(TObject* on)
{
  if (on == NULL) {
    Report::warning("[MBistableObject::adoptOn] NULL pointer passed");
    return;
  }

  delete myOn;
  myOn = new TShared(on);
}

template <class TInteractionObject, class TBistableObject, class TObject, class TObjectAttr, class TShared, class TWorld, class TPath>
INLINE const TObject* MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>
::getOn() const
{
  return (TObject*)(myOn ? myOn->getSubobject(0) : NULL);
}

template <class TInteractionObject, class TBistableObject, class TObject, class TObjectAttr, class TShared, class TWorld, class TPath>
INLINE void MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>
::adoptOff(TObject* off)
{
  if (off == NULL) {
    Report::warning("[MBistableObject::adoptOff] NULL pointer passed");
    return;
  }

  delete myOff;
  myOff = new TShared(off);
}

template <class TInteractionObject, class TBistableObject, class TObject, class TObjectAttr, class TShared, class TWorld, class TPath>
INLINE const TObject* MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>
::getOff() const
{
  return (TObject*)(myOff ? myOff->getSubobject(0) : NULL);
}

template <class TInteractionObject, class TBistableObject, class TObject, class TObjectAttr, class TShared, class TWorld, class TPath>
INLINE void MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>
::setOn()
{
  myCurState = ON;
}

template <class TInteractionObject, class TBistableObject, class TObject, class TObjectAttr, class TShared, class TWorld, class TPath>
INLINE void MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>
::setOff()
{
  myCurState = OFF;
}

template <class TInteractionObject, class TBistableObject, class TObject, class TObjectAttr, class TShared, class TWorld, class TPath>
INLINE void MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>
::toggle()
{
  myCurState = (myCurState == ON) ? OFF : ON;
}

template <class TInteractionObject, class TBistableObject, class TObject, class TObjectAttr, class TShared, class TWorld, class TPath>
INLINE void MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>
::setState(Switch state)
{
  myCurState = state;
}

template <class TInteractionObject, class TBistableObject, class TObject, class TObjectAttr, class TShared, class TWorld, class TPath>
INLINE Switch MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>
::getState()
{
  return myCurState;
}

template <class TInteractionObject, class TBistableObject, class TObject, class TObjectAttr, class TShared, class TWorld, class TPath>
INLINE int MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>
::activate(TWorld*, const TPath* path, int , int )
{
  toggle();                                // switch to other state
  subjectChanged(path);                    // send message to proxy
  
  return 0;
}

template <class TInteractionObject, class TBistableObject, class TObject, class TObjectAttr, class TShared, class TWorld, class TPath>
INLINE TObject* MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>
::createSubject() const
{
  if (myCurState == ON)
    return (TObject*)(myOn ? myOn->copy() : NULL);
  else
    return (TObject*)(myOff ? myOff->copy() : NULL);
}

template <class TInteractionObject, class TBistableObject, class TObject, class TObjectAttr, class TShared, class TWorld, class TPath>
INLINE TObject* MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>
::copy() const
{
  return new TBistableObject(*((TBistableObject*)this));
}

template <class TInteractionObject, class TBistableObject, class TObject, class TObjectAttr, class TShared, class TWorld, class TPath>
INLINE int MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>
::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  TObjectAttr* attr = dynamic_cast(TObjectAttr, specifier);
  if (attr != NULL) {
    // The Object3DAttr object knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute(this);

    delete attr;
    return 1;  
  }

  // 
  // Let papa do the rest ...
  //
  return TInteractionObject::setSpecifier(errMsg, specifier);
}

template <class TInteractionObject, class TBistableObject, class TObject, class TObjectAttr, class TShared, class TWorld, class TPath>
INLINE Makeable* MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>
::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return copy();
}

#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)

