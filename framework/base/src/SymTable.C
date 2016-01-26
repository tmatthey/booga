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
 *  $Id: SymTable.C,v 1.5 1995/12/01 12:45:10 streit Exp $
 * -----------------------------------------------------------------------------
 */

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#if defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
// Only compile this file if either not GNU compiler running,
// or, in case of GNU compiler, files is included from header.

#include <stdlib.h>  

#ifdef TEMPLATE_IN_HEADER
# define INLINE inline
#else
# include "booga/base/SymTable.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER


//______________________________________________ Implementation of class SymTable

template <class Key, class T>
INLINE SymTable<Key, T>::SymTable(int n) 
{ 
  for (mySize=32; mySize<n; mySize<<=1) ; 
  myFirst = new SymTableEntry<Key, T>*[mySize]; 
  --mySize; 
  myLast = &myFirst[mySize]; 
  for (register SymTableEntry<Key, T>** e=myFirst; e<=myLast; e++) { 
    *e = NULL; 
  } 
} 

template <class Key, class T>
INLINE SymTable<Key, T>::~SymTable() 
{ 
  removeAll();  
  delete myFirst; 
} 

template <class Key, class T>
INLINE SymTableEntry<Key, T>*& SymTable<Key, T>::probe(const Key &i) 
{ 
  return myFirst[_keyToHash(i) & mySize]; 
} 

template <class Key, class T>
INLINE int SymTable<Key, T>::insert(const Key& k, const T &v) 
{ 
  if (find(k)) return 0; 

  register SymTableEntry<Key, T>* e = new SymTableEntry<Key, T>; 
  e->myKey = k; 
  e->myValue = v; 
  register SymTableEntry<Key, T>** a = &probe(k); 
  e->myChain = *a; 
  *a = e; 
  return 1;
} 

template <class Key, class T>
INLINE int SymTable<Key, T>::lookup(const Key &k, T &v) 
{ 
  for (register SymTableEntry<Key, T>* e=probe(k); e!=NULL; e=e->myChain) { 
    if (e->myKey == k) { 
      v = e->myValue; 
      return 1; 
    } 
  } 
  return 0; 
} 

template <class Key, class T>
INLINE int SymTable<Key, T>::find(const Key &k) 
{ 
  for (register SymTableEntry<Key, T>* e=probe(k); e!=NULL; e=e->myChain) { 
    if (e->myKey == k) { 
      return 1; 
    } 
  } 
  return 0; 
} 

template <class Key, class T>
INLINE int SymTable<Key, T>::findAndReplace(const Key& k, const T& v) 
{ 
  for (register SymTableEntry<Key, T>* e=probe(k); e!=NULL; e=e->myChain) { 
    if (e->myKey == k) { 
      e->myValue = v; 
      return 1; 
    } 
  } 
  return 0; 
} 

template <class Key, class T>
INLINE int SymTable<Key, T>::findAndRemove(const Key& k, T& v) 
{ 
  SymTableEntry<Key, T>** a = &probe(k); 
  register SymTableEntry<Key, T>* e = *a; 
  if (e != NULL) { 
    if (e->myKey == k) { 
      v = e->myValue; 
      *a = e->myChain; 
      delete e; 
      return 1; 
    } else { 
      register SymTableEntry<Key, T>* prev; 
      do { 
	prev = e; 
	e = e->myChain; 
      } while (e != NULL && e->myKey != k); 
      if (e != NULL) { 
	v = e->myValue; 
	prev->myChain = e->myChain; 
	delete e; 
	return 1; 
      } 
    } 
  } 
  return 0; 
} 

template <class Key, class T>
INLINE void SymTable<Key, T>::remove(const Key &k) 
{ 
  SymTableEntry<Key, T>** a = &probe(k); 
  register SymTableEntry<Key, T>* e = *a; 
  if (e != NULL) { 
    if (e->myKey == k) { 
      *a = e->myChain; 
      delete e; 
    } else { 
      register SymTableEntry<Key, T>* prev; 
      do { 
	prev = e; 
	e = e->myChain; 
      } while (e!=NULL && e->myKey!=k); 
      if (e != NULL) { 
	prev->myChain = e->myChain; 
	delete e; 
      } 
    } 
  } 
} 

template <class Key, class T>
INLINE void SymTable<Key, T>::removeAll() 
{ 
  SymTableEntry<Key, T>* cur, * next;
  for  (register SymTableEntry<Key, T>** e=myFirst; e<=myLast; e++) {
    cur = *e;
    *e = NULL;
    
    while (cur != NULL) {
      next = cur->myChain;
      delete cur;
      cur = next;
    }
  }
} 


//______________________________________ Implementation of class SymTableIterator

template <class Key, class T>
INLINE SymTableIterator<Key, T>::SymTableIterator(const SymTable<Key, T>& t) 
{ 
  myLast = t.myLast; 
  for (myEntry = t.myFirst; myEntry <= myLast; myEntry++) { 
    myCur = *myEntry; 
    if (myCur != NULL) { 
      break; 
    } 
  } 
} 

template <class Key, class T>
INLINE int SymTableIterator<Key, T>::next() 
{ 
  myCur = myCur->myChain; 
  if (myCur != NULL) { 
    return 1; 
  } 
  for (++myEntry; myEntry <= myLast; myEntry++) { 
    myCur = *myEntry; 
    if (myCur != NULL) { 
      return 1; 
    } 
  } 
  return 0; 
}

#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)

