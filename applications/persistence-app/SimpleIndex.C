/*
 * $RCSfile: SimpleIndex.C,v $
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
 *  $Id: SimpleIndex.C,v 1.1 1996/12/06 16:47:17 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
/*
 * GNU compiler has a pretty bad handling of templates...
 */
#if defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
// Only compile this file if either not GNU compiler running,
// or, in case of GNU compiler, files is included from header.

#include <stdlib.h> 
#include <iostream> 
#include "PExtraTemplates.h"
#include "Marshal.h"

#ifdef TEMPLATE_IN_HEADER
# define INLINE 
#else
# include "SimpleIndex.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER


//______________________________________________ Implementation of class SimpleIndex

template <class TKey, class TData>
INLINE SimpleIndex<TKey, TData>::SimpleIndex(int n) :
myEntries(n)
{
}

template <class TKey, class TData>
INLINE SimpleIndex<TKey,TData>::~SimpleIndex() 
{
}

template <class TKey, class TData>
INLINE void SimpleIndex<TKey,TData>::insert(const TKey& key, const TData& data)
{
  long pos;
  pos = find(key);
  myEntries.insert(pos, SimpleIndexEntry<TKey,TData>(key,data));
}

template <class TKey, class TData>
INLINE int SimpleIndex<TKey,TData>::lookup(const TKey& key, TData& retVal) const
{
  long pos;
  pos = find(key);
  if (pos >= myEntries.count()) return 0;
  if (myEntries.item(pos).myKey == key) {
    retVal = myEntries.item(pos).myData;
    return 1;
  }
  return 0;
}

//
// Warning: assumes key is unique
//
template <class TKey, class TData>
INLINE void SimpleIndex<TKey,TData>::remove(const TKey& key) 
{
  long pos;
  pos = find(key);
  if (pos >= myEntries.count()) return;
  if (myEntries.item(pos).myKey == key) {
    myEntries.remove(pos);
  }
}

//
// if the key is not found the insert position is returned
//
template <class TKey, class TData>
INLINE long SimpleIndex<TKey,TData>::find(const TKey& key) const
{
  long bottom = 0;
  long top = myEntries.count();
  while (top > bottom) {
    long mid = (top + bottom)/2;
    if (myEntries.item(mid).myKey < key) {
      bottom = mid+1;
    }
    else {
      top = mid;
    }
  }
  return bottom;
}

template <class TKey, class TData>
INLINE long SimpleIndex<TKey,TData>::count() const {
  return myEntries.count();
}

template <class TKey, class TData>
INLINE TKey SimpleIndex<TKey,TData>::getKey(long i) const {
  if (i < 0 || i >= myEntries.count()) {
    Report::error("[SimpleIndex::getKey] index out of range");
    exit(1);
  }
  return myEntries.item(i).myKey;
}

template <class TKey, class TData>
INLINE TData SimpleIndex<TKey,TData>::getData(long i) const {
  if (i < 0 || i >= myEntries.count()) {
    Report::error("[SimpleIndex::getData] index out of range");
    exit(1);
  }
  return myEntries.item(i).myData;
}

template <class TKey, class TData>
INLINE Marshal& operator<<(Marshal& m, const SimpleIndex<TKey,TData>& aSI) {
  m << aSI.myEntries;
  return m;
}

template <class TKey, class TData>
INLINE Marshal& operator>>(Marshal& m, SimpleIndex<TKey,TData>& aSI) {
  m >> aSI.myEntries;
  return m;
}
  

template <class TKey, class TData>
INLINE SimpleIndexEntry<TKey,TData>::SimpleIndexEntry() 
{
}

template <class TKey, class TData>
INLINE SimpleIndexEntry<TKey,TData>::SimpleIndexEntry(const TKey& key, const TData& data) 
: myKey(key), myData(data)
{
}

template <class TKey, class TData>
INLINE Marshal& operator<<(Marshal& m, const SimpleIndexEntry<TKey,TData>& aSIE) {
  m << aSIE.myKey;
  m << aSIE.myData;
  return m;
}

template <class TKey, class TData>
INLINE Marshal& operator>>(Marshal& m, SimpleIndexEntry<TKey,TData>& aSIE) {
  m >> aSIE.myKey;
  m >> aSIE.myData;
 return m;
}
  
#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
