/*
 * $RCSfile: PersistenceFor.h
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
 *  $Id: PersistenceFor.h,v 1.1 1996/12/11 13:59:09 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PersistenceFor_H
#define _PersistenceFor_H

#include "booga/persistence/Persistent.h"
#include "booga/persistence/DataBase.h"
#include "booga/persistence/Prototype.h"

class Marshal;
//_____________________________________________________________________ PersistenceFor

template <class T>
class PersistenceFor : public Persistent, public T {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PersistenceFor(DataBase& aDB);                 
  PersistenceFor(Prototype aPrototype);

private:
//  PersistenceFor(const PersistenceFor<T>&);

public:
  virtual ~PersistenceFor();
private:
//  PersistenceFor<T>& operator=(const PersistenceFor<T>&);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class PersistenceFor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // virtual PersistenceFor<T>* newInstance();
  virtual Persistent* newInstance();
  virtual int destroy();

  virtual void marshal(Marshal* aMarshal);
  virtual void unmarshal(Marshal* aMarshal);

  friend Marshal& operator<<(Marshal& aDB, const PersistenceFor& aPF);
  friend Marshal& operator>>(Marshal& aDB, PersistenceFor& aPF);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
};

//______________________________________________________________________ INLINES

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
#define TEMPLATE_IS_INCLUDE_FROM_H
#include "../persistence/src/PersistenceFor.C"
#endif // TEMPLATE_IN_HEADER
 
#endif // _PersistenceFor_H

