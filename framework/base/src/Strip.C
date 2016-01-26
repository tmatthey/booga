/*
 * $RCSfile: Strip.C,v $ 
 *
 * Copyright (C) 1996, Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: Strip.C,v 1.1 1996/12/19 16:14:53 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
/*
 * GNU compiler has a pretty bad handling of templates...
 */
#if defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
// Only compile this file if either not GNU compiler running,
// or, in case of GNU compiler, files is included from header.

#include "booga/base/Option.h"

#ifdef TEMPLATE_IN_HEADER
# define INLINE inline
#else
# include "booga/base/Strip.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER
//___________________________________________________________________ Strip

template <class T>
INLINE Strip<T>::Strip(const List<T>& vertices, int start, int end) : 
myVertices(vertices),
myStart(start),
myEnd(end)
{
  computeFarPoint();
}

template <class T>
INLINE void Strip<T>::computeFarPoint() {
  myFarPointDistance = 0.0;
  myFarPoint = myStart;
  int size = myVertices.count();
  int i;
  
  if (myStart != myEnd && myStart%size == myEnd % size) {
    for (i=myStart+1; i<myEnd; i++) {
      Real dist = (myVertices.item(0)-myVertices.item(i)).length();
      if (dist > myFarPointDistance){
          myFarPoint = i;
          myFarPointDistance = dist;
      }
    }
  }
  else {
    T a(myVertices.item(myStart%size));
    T b(myVertices.item(myEnd%size));
    T n = b-a;
    n = T(-n.y(),n.x()).normalized(); // rotate 90 degrees to get normal
    for (i=myStart+1; i<myEnd; i++) {
      Real dist = n^(myVertices.item(i%size)-a);
      if (dist < 0.0) dist = -dist;
      if (dist > myFarPointDistance) {
        myFarPoint = i;
        myFarPointDistance = dist;
      }
    }
  }
}

#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)


