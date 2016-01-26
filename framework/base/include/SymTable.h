/*
 * Copyright (c) 1987, 1988, 1989, 1990, 1991 Stanford University
 * Copyright (c) 1991 Silicon Graphics, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and 
 * its documentation for any purpose is hereby granted without fee, provided
 * that (i) the above copyright notices and this permission notice appear in
 * all copies of the software and related documentation, and (ii) the names of
 * Stanford and Silicon Graphics may not be used in any advertising or
 * publicity relating to the software without the specific, prior written
 * permission of Stanford and Silicon Graphics.
 * 
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY 
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  
 *
 * IN NO EVENT SHALL STANFORD OR SILICON GRAPHICS BE LIABLE FOR
 * ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF 
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE 
 * OF THIS SOFTWARE.
 *
 * Generic object association table.
 *
 * -----------------------------------------------------------------------------
 *  $Id: SymTable.h,v 1.11 1995/12/01 12:45:11 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _SymTable_H
#define  _SymTable_H

//_____________________________________________________________________ SymTable

template <class Key, class T> class SymTableEntry;
template <class Key, class T> class SymTableIterator;

template <class Key, class T>
class SymTable { 
public: 
  SymTable(int); 
  ~SymTable(); 

  int insert(const Key&, const T&); 
  int find(const Key&);
  int findAndReplace(const Key&, const T&); 
  int findAndRemove(const Key&, T&); 
  int lookup(const Key&, T&); 
  void remove(const Key&); 
  void removeAll(); 

private: 
  friend class SymTableIterator<Key, T>;

  int mySize; 
  SymTableEntry<Key, T>** myFirst; 
  SymTableEntry<Key, T>** myLast; 

  SymTableEntry<Key, T>*& probe(const Key&); 
}; 

//_____________________________________________________________ SymTableIterator

template <class Key, class T>
class SymTableIterator { 
public: 
  SymTableIterator(const SymTable<Key, T>&); 

  Key& curKey();
  T& curValue(); 
  int more();
  int next(); 

private: 
  SymTableEntry<Key, T>*  myCur; 
  SymTableEntry<Key, T>** myEntry; 
  SymTableEntry<Key, T>** myLast; 
}; 

//________________________________________________________________ SymTableEntry

template <class Key, class T>
class SymTableEntry { 
private: 
  friend class SymTable<Key, T>; 
  friend class SymTableIterator<Key, T>;

  Key myKey; 
  T myValue; 
  SymTableEntry<Key, T>* myChain; 
}; 

//_______________________________________________________________________INLINES

template <class Key, class T>
inline Key& SymTableIterator<Key, T>::curKey() 
{ 
  return myCur->myKey;      
}

template <class Key, class T>
inline T& SymTableIterator<Key, T>::curValue() 
{ 
  return myCur->myValue;    
}

template <class Key, class T>
inline int SymTableIterator<Key, T>::more()    
{ 
  return myEntry <= myLast; 
}

//____________________________________________________ Predefined hash functions

inline unsigned long _keyToHash(long key) 
{ 
  return (unsigned long) key; 
}
inline unsigned long _keyToHash(const void* k) 
{ 
  return (unsigned long) k; 
}

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
#define TEMPLATE_IS_INCLUDE_FROM_H
#include "../base/src/SymTable.C"
#endif // TEMPLATE_IN_HEADER

#endif // _SymTable_H

