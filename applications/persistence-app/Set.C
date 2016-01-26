/*
 * $RCSfile: Set.C 
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
 *  $Id: Set.C,v 1.6 1996/12/06 16:47:01 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
/*
 * GNU compiler has a pretty bad handling of templates...
 */
#if defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
// Only compile this file if either not GNU compiler running,
// or, in case of GNU compiler, files is included from header.

#ifdef TEMPLATE_IN_HEADER
# define INLINE inline
#else
# include "Set.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER

#include "Marshal.h"

//_____________________________________________________________________ Set

template <class T>
INLINE Set<T>::Set() 
: myElements(10)
{}

template <class T>
INLINE Set<T>::~Set() 
{
  if (myElements.count() > 0) myElements.removeAll();
}

template <class T>
INLINE Set<T>::Set(const Set<T>& aSet) :
myElements(aSet.myElements){
}

template <class T>
INLINE Set<T>& Set<T>::operator=(const Set<T>& aSet) {
  if (this != &aSet) {
    myElements = aSet.myElements;
  }
  return *this;
}

template <class T>
INLINE int Set<T>::operator==(const Set<T>& aSet) const {
  if (myElements.count() != aSet.count()) return 0;
  for (long i=0; i<myElements.count(); i++) {
    if (!aSet.isElement(myElements.item(i))) return 0;
  }
  return 1;
}

template <class T>
INLINE int Set<T>::operator!=(const Set<T>& aSet) const {
  return !(*this == aSet);
}

template <class T>
INLINE void Set<T>::insertElement(const T& item) { 
  for (long i=0; i<myElements.count(); i++) {
    if (item == myElements.item(i)) return;
  }
  myElements.append(item);
}

template <class T>
INLINE void Set<T>::removeElement(const T& item) {
  for (long i=0; i<myElements.count(); i++) {
    if (item == myElements.item(i)) {
      myElements.remove(i);
    }
  }
}

template <class T>
INLINE void Set<T>::removeAll() {
  myElements.removeAll();
}

template <class T>
INLINE int Set<T>::isElement(const T& item) const {
  for (long i=0; i<myElements.count(); i++) {
    if (item == myElements.item(i)) {
      return 1;
    }
  }
  return 0;
}

template <class T>
INLINE T& Set<T>::getElement(const long i) const {  
  return myElements.item(i);
}

template <class T>
INLINE long Set<T>::count() const {
  return myElements.count();
}

template <class T>
INLINE Set<T> Set<T>::unionOp(const Set<T>& aSet) const {
  Set<T> retSet(aSet);
  for(long i=0; i<myElements.count(); i++) {
    retSet.insertElement(myElements.item(i));
  }
  return retSet;
}

template <class T>
INLINE Set<T> Set<T>::intersection(const Set<T>& aSet) const {
  Set<T> retSet;
  for(long i=0; i<myElements.count(); i++) {
    if(aSet.isElement(myElements.item(i))) {
      retSet.insertElement(myElements.item(i));
    }
  }
  return retSet;
}

template <class T>
INLINE Set<T> Set<T>::difference(const Set<T>& aSet) const {
  Set<T> retSet(*this);
  for(long i=0; i<aSet.myElements.count(); i++) {
    if(retSet.isElement(aSet.myElements.item(i))) {
      retSet.removeElement(aSet.myElements.item(i));
    }
  }
  return retSet;
}
 
template <class T>
INLINE Marshal& operator<<(Marshal& m, const Set<T>& aSet) {
  m << aSet.myElements;
  return m;
}

template <class T>
INLINE Marshal& operator>>(Marshal& m, Set<T>& aSet) {
  m >> aSet.myElements;
  return m;
}
 
#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
