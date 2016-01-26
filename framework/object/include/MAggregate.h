/*
 * $RCSfile: MAggregate.h,v $
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
 *  $Id: MAggregate.h,v 1.2 1996/08/09 12:54:03 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _MAggregate_H
#define _MAggregate_H

#include "booga/base/List.h"
#include "booga/object/BOOGAObject.h"

//___________________________________________________________________ MAggregate

template <class TObject, class TAggregate, class TPath>
class MAggregate : public TObject {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  MAggregate();
  MAggregate(Exemplar);
protected:
  MAggregate(const MAggregate<TObject, TAggregate, TPath>& aggregate);

public:
  virtual ~MAggregate();

private:
  MAggregate<TObject, TAggregate, TPath>& 
     operator=(const MAggregate<TObject, TAggregate, TPath>&);  
  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class MAggregate<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void adoptObject(TObject* newObject);
  // Add another object to the aggregate.
  virtual int orphanObject(const TObject* object);
  // Remove the indicated object from the list.
  // Returns 1 if OK, 0 if the object couldn't be removed.
  virtual int replaceObject(const TObject* from, TObject* to);
  // Replace the first occurence of 'from' by 'to'.
  // Returns 1 if OK, 0 if the object couldn't be replaced.

private:
  virtual TAggregate* makeEmpty() const = 0;
  // Create an empty exemplar of the corresponding object type.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class TObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual TObject* makeUnique(TPath* path = NULL, bool shared = false);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class BOOGAObject<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual long countSubobject() const;
  virtual TObject* getSubobject(long index);
protected:
  virtual void doComputeBounds();
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  List<TObject*> myElements;
};

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
#define TEMPLATE_IS_INCLUDE_FROM_H
#include "../object/src/MAggregate.C"
#endif // TEMPLATE_IN_HEADER

#endif // _MAggregate_H

