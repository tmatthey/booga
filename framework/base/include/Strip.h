/*
 * $RCSfile: Strip.h,v $
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
 *  $Id: Strip.h,v 1.1 1996/12/19 16:14:54 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Strip_H
#define _Strip_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/List.h"
#include "booga/base/Value.h"

//___________________________________________________________________ Strip

template <class T>
class Strip {
public:
  Strip() {}
  // Strip(Strip &); use default
  Strip(const List<T>& vertices, int start, int end);
  void computeFarPoint();
  int getStart() { return myStart; }
  int getEnd() { return myEnd; }
  int getFarPoint() { return myFarPoint; }
  Real getFarPointDistance() { return myFarPointDistance; }

private: 
  List<T> myVertices;
  int myStart;
  int myEnd;
  int myFarPoint;
  Real myFarPointDistance;
};

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
#define TEMPLATE_IS_INCLUDE_FROM_H
#include "../base/src/Strip.C"
#endif // TEMPLATE_IN_HEADER

#endif // _Strip_H


