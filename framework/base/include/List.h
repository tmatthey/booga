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
 * Generic list implemented as dynamic array
 *
 * ----------------------------------------------------------------------
 *  $Id: List.h,v 1.18 1996/02/16 12:52:43 streit Exp $
 * ----------------------------------------------------------------------
 */

#ifndef _List_H
#define _List_H

extern long ListImpl_best_new_count(long count, long size);

//___________________________________________________________________ List<T>

template <class T>
class List { 
public: 
  List();
  List(long size);
  List(const List<T>& list);
  ~List();

  List<T>& operator=(const List<T>& list);

  long count() const  { return myCount; } 
  long size()  const  { return mySize; } 
  T& item(long index) const;
 
  void prepend(const T& item) { insert(0, item); } 
  void append(const T& item)  { insert(myCount, item); } 
  void insert(long index, const T&); 
  void remove(long index); 
  void removeAll();
  
private:
  T* myItems; 
  long mySize; 
  long myCount; 
  long myFree; 
}; 


//________________________________________________________________ ListItr<T>
//
// Non robust Iterator over List
//
template <class T>
class ListItr { 
public: 
  ListItr(const List<T>& list); 

  void first();
  void next(); 
  int isDone() const; 
  T& curItem() const; 
  
private: 
  const List<T>* myList; 
  long myCurItem; 
  long myListCount; 
};

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
#define TEMPLATE_IS_INCLUDE_FROM_H
#include "../base/src/List.C"
#endif // TEMPLATE_IN_HEADER
 
#endif // _List_H
