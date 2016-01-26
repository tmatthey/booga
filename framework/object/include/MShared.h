/*
 * $RCSfile: MShared.h,v $
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
 *  $Id: MShared.h,v 1.12 1996/10/11 14:27:56 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _MShared_H
#define _MShared_H

#include "booga/base/ReferenceCounting.h"

//___________________________________________________________________ MShared<>

template <class TObject, class TShared, class TPath, class TRay>
class MShared : public TObject, public RCEnvelope {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  MShared(TObject* adoptObject);
  // MShared(Exemplar);                  // No exemplar constructor!
  MShared(TObject* adoptObject, const Name defName);
  // MShared(const MShared<TObject, TShared, TPath, TRay>&);  
  // Use default version.

public:
  // virtual ~MShared();                 // Use default version.

private:
  MShared<TObject, TShared, TPath, TRay>& 
    operator=(const MShared<TObject, TShared, TPath, TRay>& );  
  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class MShared<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void setTypeName(const Name& name);
  virtual const Name& getTypeName() const;
  void adoptObject(TObject* object);
  
private:
  static Name generateUniqueName();  // Internal use only.
  // If there's no name provided with the constructor, we have to 
  // generate a unique name by ourself. The static variable is a 
  // counter that allows the creation of these names.

  TObject* getObject();              // Internal use only.

 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class TObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual TObject* copy() const;
  virtual TObject* makeUnique(TPath* path = NULL, bool shared = false);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class BOOGAObject<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual long countSubobject() const;
  virtual TObject* getSubobject(long index);
protected:
  virtual void doComputeBounds();
private:
  virtual bool doIntersect(TRay& ray);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual RCString getKeyword() const;
  virtual void iterateAttributes(MakeableHandler* handler);
};

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
#define TEMPLATE_IS_INCLUDE_FROM_H
#include "../object/src/MShared.C"
#endif // TEMPLATE_IN_HEADER

#endif // _MShared_H

