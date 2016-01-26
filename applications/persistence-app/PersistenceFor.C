/*
 * $RCSfile: PersistenceFor.C 
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
 *  $Id: PersistenceFor.C,v 1.5 1996/12/06 16:46:13 collison Exp $
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
# include "PersistenceFor.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER

#include "Marshal.h"

//_____________________________________________________________________ PersistenceFor

template <class T>
INLINE PersistenceFor<T>::PersistenceFor(DataBase& aDB) :
Persistent(aDB), 
T()
{}

template <class T>
INLINE PersistenceFor<T>::PersistenceFor(Prototype aPrototype) :
Persistent(aPrototype),
T()
{}

template <class T>
INLINE PersistenceFor<T>::~PersistenceFor()
{}

template <class T>
INLINE Persistent* PersistenceFor<T>::newInstance() {
  return new PersistenceFor<T>(aPrototype);
}

template <class T>
INLINE int PersistenceFor<T>::destroy() {
  return 0;
}

template <class T>
INLINE void PersistenceFor<T>::marshal(Marshal* aMarshal) {
  *aMarshal << *this;
}

template <class T>
INLINE void PersistenceFor<T>::unmarshal(Marshal* aMarshal) {
  *aMarshal >> *this;
}

template <class T>
INLINE Marshal& operator<<(Marshal& aDB, const PersistenceFor<T>& aPF) {
  aDB << (T&) aPF;
  return aDB;
}

template <class T>
INLINE Marshal& operator>>(Marshal& aDB, PersistenceFor<T>& aPF) {
  aDB >> (T&) aPF;
  return aDB;
}
 
#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
