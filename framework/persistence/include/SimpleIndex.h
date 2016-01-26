/*
 * $RCSfile: SimpleIndex.h,v $
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
 *  $Id: SimpleIndex.h,v 1.5 1997/01/15 13:48:20 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _SimpleIndex_H
#define _SimpleIndex_H

#include "booga/base/List.h"

//_____________________________________________________________________SimpleIndex

template <class TKey, class TData> class SimpleIndexEntry;
template <class TKey, class TData> class SimpleIndex;

template<class TKey, class TData> 
class SimpleIndexEntry {
public:
  SimpleIndexEntry();
  SimpleIndexEntry(const TKey& key, const TData& data);
  friend class SimpleIndex<TKey,TData>;
  
private:
  TKey myKey;
  TData myData;
};

template <class TKey, class TData>
class SimpleIndex {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  SimpleIndex(int n=20);
  ~SimpleIndex();
  SimpleIndex(const SimpleIndex<TKey, TData>&);

public:
  // virtual ~SimpleIndex();                // Use default version.

  SimpleIndex<TKey,TData>& operator=(const SimpleIndex<TKey, TData>&);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class SimpleIndex
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void insert(const TKey& key, const TData& data);
  int lookup(const TKey& key, TData& retVal) const;
  void remove(const TKey& key);
  void removeAll();
  long find(const TKey& key) const;
  long count() const;
  TKey getKey(long i) const;
  TData getData(long i) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  List<SimpleIndexEntry<TKey, TData> > myEntries;
};

template <class TKey, class TData>
inline Marshal& operator<<(Marshal& m, const SimpleIndex<TKey,TData>& aSI);

template <class TKey, class TData>
inline Marshal& operator>>(Marshal& m, SimpleIndex<TKey,TData>& aSI);

//______________________________________________________________________ INLINES

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
#define TEMPLATE_IS_INCLUDE_FROM_H
#include "../persistence/src/SimpleIndex.C"
#endif // TEMPLATE_IN_HEADER


#endif // _SimpleIndex_H

