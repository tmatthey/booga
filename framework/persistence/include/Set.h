/*
 * $RCSfile: Set.h
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
 *  $Id: Set.h,v 1.2 1996/12/18 13:55:26 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Set_H
#define _Set_H

#include "booga/persistence/POId.h"
#include "booga/persistence/Persistent.h"
#include "booga/base/List.h"

class Marshal;

//_____________________________________________________________________ Set

template <class T>
class Set {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Set();                         // Use default version.
  Set(const Set<T>&);

public:
  virtual ~Set();                // Use default version.
  Set<T>& operator=(const Set<T>&);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Set
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void insertElement(const T& item);
  void removeElement(const T& item);
  void removeAll();
  int  isElement(const T& item) const;
  T&   getElement(const long i) const;
  long count() const;

  Set<T> unionOp(const Set<T>& aSet) const;
  Set<T> difference(const Set<T>& aSet) const;
  Set<T> intersection(const Set<T>& aSet) const;

  int operator==(const Set<T>& aSet) const;
  int operator!=(const Set<T>& aSet) const;
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  List<T> myElements;
};

template <class T>
Marshal& operator<<(Marshal& m, const Set<T>& aSet);

template <class T>
Marshal& operator>>(Marshal& m, Set<T>& aSet);

//______________________________________________________________________ INLINES

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
 #define TEMPLATE_IS_INCLUDE_FROM_H
 #include "../persistence/src/Set.C"
#endif // TEMPLATE_IN_HEADER
 
#endif // _Set_H

