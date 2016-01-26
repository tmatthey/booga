/*
 * $RCSfile: PRef.C 
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
 *  $Id: PRef.C,v 1.10 1996/12/06 16:46:53 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
/*
 * GNU compiler has a pretty bad handling of templates...
 */
#if defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
// Only compile this file if either not GNU compiler running,
// or, in case of GNU compiler, files is included from header.


#include "PersistentManager.h"
#include "Marshal.h"
 
#ifdef TEMPLATE_IN_HEADER
# define INLINE inline
#else
# include "PRef.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER

//_____________________________________________________________________ PRef

template <class T>
INLINE PRef<T>::PRef() 
: myPOId(POID_NULL)
{}

template <class T>
INLINE PRef<T>::PRef(Persistent& p) 
: myPOId(p.getPOId())
{
}

template <class T>
INLINE PRef<T>::PRef(Persistent* p) 
: myPOId(POID_NULL)
{  
  if (p != NULL) {
    myPOId = p->getPOId(); // may only reference a Persistent
  }
}

template<class T>
INLINE PRef<T>::PRef(const POId& anId) :
myPOId(anId) 
{
}

template <class T>
INLINE PRef<T>::~PRef() 
{}

template <class T>
INLINE PRef<T>::PRef(const PRef<T>& ref) :
myPOId(ref.myPOId) {
}

template <class T>
INLINE PRef<T>& PRef<T>::operator=(const PRef<T>& ref) {
  myPOId = ref.myPOId;
  return *this;
}

template <class T>
INLINE PRef<T>& PRef<T>::operator=(T& aPersistent) {
  myPOId = aPersistent.getPOId(); // may only reference a Persistent
  return *this;
}

template <class T>
INLINE PRef<T>& PRef<T>::operator=(T* aPersistent) {
  if (aPersistent == NULL) {
    myPOId = POID_NULL;
  } else {
    myPOId = aPersistent->getPOId(); // may only reference a Persistent
  }
  return *this;
}

template <class T>
INLINE T* PRef<T>::operator->() const {
   return getPtr();
}

template <class T>
INLINE T* PRef<T>::getPtr() const {

  if (myPOId == POID_NULL) {
     return NULL;                   // no object asigned to PRef
  }
  else {
     // get the object
     Persistent *obj = PersistentManager::getThePersistentManager()->load(myPOId);
     if (obj == NULL) return NULL;
     T* memObj = dynamic_cast<T*>(obj);
     return memObj;
  }
  return NULL;
}

template <class T>
INLINE T& PRef<T>::getObj() const {
  return *(getPtr());
}

template <class T>
INLINE POId PRef<T>::getPOId() { 
  return myPOId; 
}

template <class T>
INLINE Marshal& operator<<(Marshal& m, const PRef<T>& ref) {
  m << ref.myPOId;
  return m;
}

template <class T>
INLINE Marshal& operator>>(Marshal& m, PRef<T>& ref) {
  m >> ref.myPOId;
  return m;
}
 
#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
