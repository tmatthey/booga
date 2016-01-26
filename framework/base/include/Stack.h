/*
 * Stack.h
 *
 * A general implementation of the ADT Stack based on templates.
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
 *                        University of Berne, Switzerland
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
 *  $Id: Stack.h,v 1.7 1996/02/16 14:01:04 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Stack_H
#define _Stack_H

#include "booga/base/PrimitiveTypes.h"  // bool
#include "booga/base/List.h"

//_____________________________________________________________________ Stack<T>

template <class T>
class Stack {
public:
  T& top() const;
  T& pop();
  void push(const T& item);
  void removeAll();
  bool isEmpty() const;
  long count() const;

private:
  List<T> myRep;
};

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
#define TEMPLATE_IS_INCLUDE_FROM_H
#include "../base/src/Stack.C"
#endif // TEMPLATE_IN_HEADER

#endif // _Stack_H
