/*
 * $RCSfile: MBistableObject.h,v $
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
 *  $Id: MBistableObject.h,v 1.6 1996/09/13 08:04:52 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _MBistableObject_H
#define _MBistableObject_H

#include "booga/base/Exemplar.h"
#include "booga/base/RCString.h"
#include "booga/object/BOOGAObject.h"

//____________________________________________________________ MBistableObject

template <class TInteractionObject, class TBistableObject, class TObject,
          class TObjectAttr, class TShared, class TWorld, class TPath>
class MBistableObject : public TInteractionObject {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  MBistableObject(Exemplar);
  MBistableObject(TObject* on, TObject* off, Switch state);
  MBistableObject(const MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>&); 

public:
  virtual ~MBistableObject(); 

private:
  MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>& 
    operator=(const MBistableObject<TInteractionObject, TBistableObject, TObject, TObjectAttr, TShared, TWorld, TPath>&);  
  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class MBistableObject<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void adoptOn(TObject* object);
  const TObject* getOn() const;
  void adoptOff(TObject* object);
  const TObject* getOff() const;
  
  void setOn();
  void setOff();
  void toggle();
  void setState(Switch state);
  Switch getState();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class TInteractionObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual int activate(TWorld* world, const TPath* path, int x, int y);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class TProxy
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  virtual TObject* createSubject() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class TObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual TObject* copy() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  TShared* myOn;
  TShared* myOff;
  Switch myCurState;
};

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
#define TEMPLATE_IS_INCLUDE_FROM_H
#include "../object/src/MBistableObject.C"
#endif // TEMPLATE_IN_HEADER

#endif // _MBistableObject_H

