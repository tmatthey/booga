/*
 * Copyright (c) 1991 Stanford University
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
 * ---------------------------------------------------------------------
 *  $Id: List.C,v 1.8 1996/02/16 12:52:42 streit Exp $
 * ---------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>

//_______________________________________________ Support routines for lists

#ifndef TEMPLATE_IS_INCLUDE_FROM_H
static long ListImpl_best_new_sizes[] = {
    48, 112, 240, 496, 1008, 2032, 4080, 8176,
    16368, 32752, 65520, 131056, 262128, 524272, 1048560,
    2097136, 4194288, 8388592, 16777200, 33554416, 67108848
};

long ListImpl_best_new_count(long count, long size) 
{
  for (int i = 0; i < int(sizeof(ListImpl_best_new_sizes)/sizeof(long)); i++) {
    if (count * size < ListImpl_best_new_sizes[i]) {
      return ListImpl_best_new_sizes[i] / size;
    }
  }
  return count;
}
#endif // TEMPLATE_IS_INCLUDE_FROM_H

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#if defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
// Only compile this file if either not GNU compiler running,
// or, in case of GNU compiler, files is included from header.

#include <strstream.h>
#include "booga/base/Report.h"

#ifdef TEMPLATE_IN_HEADER
# define INLINE inline
#else
# include "booga/base/List.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER

//___________________________________________________________________ List<T>

template <class T>
INLINE List<T>::List()
: myItems(0), mySize(0), myCount(0), myFree(0) 
{}

template <class T>
INLINE List<T>::List(long size)
{ 
  if (size > 0) { 
    mySize = ListImpl_best_new_count(size, sizeof(T)); 
    myItems = new T[mySize]; 
  } 
  else { 
    mySize = 0; 
    myItems = 0; 
  } 
  myCount = 0; 
  myFree = 0; 
}

template <class T>
INLINE List<T>::List(const List<T>& list)
: myItems(0), mySize(0), myCount(0), myFree(0) 
{
  long count = list.count();
  for (long i=0; i<count; i++)
    append(list.item(i));
}

template <class T>
INLINE List<T>::~List()
{
  delete [] myItems;
}

template <class T>
INLINE List<T>& List<T>::operator=(const List<T>& list)
{
  if (this == &list)
    return *this;
  
  removeAll();
  for (register long i=0; i<list.count(); i++)
    append(list.item(i));

  return *this;
}

template <class T>
INLINE T& List<T>::item(long index) const
{
  //
  // index out of range?
  //
  if (index < 0 || index >= myCount) {
    ostrstream os;
    os << "[List<T>::item] index " << index << " out of range";
    Report::error(os);
  }
     
  long i = index < myFree ? index : index + mySize - myCount; 
  return myItems[i]; 
}

template <class T>
INLINE void List<T>::insert(long index, const T& item) 
{ 
  if (myCount == mySize) { 
    long size = ListImpl_best_new_count(mySize + 1, sizeof(T)); 
    T* items = new T[size]; 
    if (myItems != 0) { 
      register long i; 
      for (i = 0; i < myFree; ++i) { 
	items[i] = myItems[i]; 
      } 
      for (i = 0; i < myCount - myFree; ++i) { 
	items[myFree + size - myCount + i] = 
	  myItems[myFree + mySize - myCount + i]; 
      } 
      delete [] myItems;
    } 
    myItems = items; 
    mySize = size; 
  } 
  if (index >= 0 && index <= myCount) { 
    if (index < myFree) { 
      for (register long i = myFree - index - 1; i >= 0; --i) { 
	myItems[index + mySize - myCount + i] = myItems[index + i]; 
      } 
    } else if (index > myFree) { 
      for (register long i = 0; i < index - myFree; ++i) { 
	myItems[myFree + i] = myItems[myFree + mySize - myCount + i]; 
      } 
    } 
    myFree = index + 1; 
    myCount += 1; 
    myItems[index] = item; 
  } 
} 

template <class T>
INLINE void List<T>::remove(long index) 
{ 
  if (index >= 0 && index <= myCount) { 
    if (index < myFree) { 
      for (register long i = myFree - index - 2; i >= 0; --i) { 
	myItems[mySize - myCount + index + 1 + i] = 
	  myItems[index + 1 + i]; 
      } 
    } else if (index > myFree) { 
      for (register long i = 0; i < index - myFree; ++i) { 
	myItems[myFree + i] = myItems[myFree + mySize - myCount + i]; 
      } 
    } 
    myFree = index; 
    myCount -= 1; 
  } 
} 

template <class T>
INLINE void List<T>::removeAll()
{
  myCount = 0; 
  myFree = 0; 
}

//________________________________________________________________ ListItr<T>

template <class T>
INLINE void ListItr<T>::first() 
{ 
  myCurItem = 0;
  myListCount = myList->count(); 
} 

template <class T>
INLINE void ListItr<T>::next() 
{ 
  ++myCurItem;
} 

template <class T>
INLINE int ListItr<T>::isDone() const 
{ 
  return !(myCurItem < myListCount); 
}
 
template <class T>
INLINE T& ListItr<T>::curItem() const 
{ 
  return myList->item(myCurItem);
} 

template <class T>
INLINE ListItr<T>::ListItr(const List<T>& list) 
{ 
  myList = &list; 
  myCurItem = 0; 
  myListCount = myList->count(); 
}

#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
