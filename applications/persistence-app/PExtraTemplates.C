/*
 * $RCSfile: PExtraTemplates.C 
 *
 * Copyright (C) 1996, Andrey Collison <collison@iam.unibe.ch>
 *                     University of Berne, Switzerland
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
 *  $Id: PExtraTemplates.C,v 1.7 1996/12/06 16:46:34 collison Exp $
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
# include "PRef.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER
#include "PExtraTemplates.h"

#include "Marshal.h"

//_____________________________________________________________________ PExtraTemplates

template <class T>
INLINE Marshal& operator<<(Marshal& aDB, const List<T>& list) {
  aDB << list.count();
  for (long i=0; i<list.count(); i++) {
    aDB << list.item(i);
  }
  return aDB;
}

template <class T>
INLINE Marshal& operator>>(Marshal& aDB, List<T>& list) {
  long size;
  aDB >> size;
  for (long i=0; i<size; i++) {
    T* item = new T();
    aDB >> *item;
    list.append(*item);
  }
  return aDB;
}
 
#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
