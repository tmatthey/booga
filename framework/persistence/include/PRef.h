/*
 * $RCSfile: PRef.h
 *
 * Copyright (C) 1996, Andrey Collison <collison@iam.unibe.ch>
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
 *  $Id: PRef.h,v 1.1 1996/12/11 13:59:31 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PRef_H
#define _PRef_H

#include "booga/persistence/POId.h"
#include "booga/persistence/Persistent.h"

class Marshal;

//_____________________________________________________________________ PRef

template <class T>
class PRef {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PRef();                         // Use default version.
  PRef(Persistent& p);
  PRef(Persistent* p);
  PRef(const POId& anId);
  PRef(const PRef<T>&);

public:
  virtual ~PRef();                // Use default version.
  PRef<T>& operator=(const PRef<T>&);
  PRef<T>& operator=(T& aPersistent);
  PRef<T>& operator=(T* aPersistent);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class PRef
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  T* operator->() const;                  // return pointer to object
  T* getPtr() const;
  T& getObj() const;
  
  POId getPOId();

  int operator==(const PRef<T>& aRef) const{ return (myPOId == aRef.myPOId);}
  int operator!=(const PRef<T>& aRef) const{ return (myPOId != aRef.myPOId);}
  int operator<(const PRef<T>& aRef) const { return (myPOId <  aRef.myPOId);}
  
  //  template <T>
  friend Marshal& operator<<(Marshal& m, const PRef& ref);
  //template <T>
  friend Marshal& operator>>(Marshal& m, PRef& ref);
   
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  POId myPOId;      // ObjectId of Persistent object
};

//______________________________________________________________________ INLINES

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
 #define TEMPLATE_IS_INCLUDE_FROM_H
 #include "../persistence/src/PRef.C"
#endif // TEMPLATE_IN_HEADER
 
#endif // _PRef_H

