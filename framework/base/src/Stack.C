/*
 * Stack.C 
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: Stack.C,v 1.5 1996/02/16 14:01:03 streit Exp $
 * -----------------------------------------------------------------------------
 */

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#if defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
// Only compile this file if either not GNU compiler running,
// or, in case of GNU compiler, files is included from header.

#include <stdlib.h>
#include "booga/base/Report.h"

#ifdef TEMPLATE_IN_HEADER
# define INLINE inline
#else
# include "booga/base/Stack.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER

//________________________________________________________________________ Stack

template <class T>
INLINE void Stack<T>::push(const T& item)
{
  myRep.append(item);
}


template <class T>
INLINE void Stack<T>::removeAll()
{
  myRep.removeAll();
}

template <class T>
INLINE bool Stack<T>::isEmpty() const
{
  return myRep.count() == 0;
}

template <class T>
INLINE long Stack<T>::count() const
{
  return myRep.count();
}

//_______________________________________________________________________ Stack

template <class T>
INLINE T& Stack<T>::top() const
{
  if (myRep.count() <= 0)
    Report::error("[Stack<T>::top] no element on the stack");

  return myRep.item(myRep.count()-1);
}

template <class T>
INLINE T& Stack<T>::pop()
{
  if (myRep.count() <= 0) 
    Report::error("[Stack<T>::pop] no element on the stack");

  T& saveElement = myRep.item(myRep.count()-1);
  myRep.remove(myRep.count()-1);
  return saveElement;
}

#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)

