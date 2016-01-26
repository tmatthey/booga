/*
 * MIterator.h
 *
 * Copyright (C) 1995, Stephan Amann <amann@iam.unibe.ch>
 *                     Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: MIterator.h,v 1.7 1996/01/19 15:39:37 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _MIterator_H
#define _MIterator_H

#include <stddef.h>
#include "booga/base/PrimitiveTypes.h"

//____________________________________________________________________ MIterator

template<class TObject, class TContainer>
class MIterator {
public:
  MIterator();
  // virtual ~MIterator();                     // Use default version.

  void first();
  void next();
  bool isDone() const;
  
  int count() const;

protected:
  TObject& curItem() const;

private:
  virtual TContainer* getContainer() = 0;

private:
  TContainer* myContainer;
  long myCurItem;
  long myContainerCount;
  
private:
  MIterator(MIterator<TObject, TContainer>&); 		           
  // No copy constructor.
  MIterator<TObject, TContainer>& operator=(const MIterator<TObject, TContainer>&);	  
  // No assignment.
};

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
#define TEMPLATE_IS_INCLUDE_FROM_H
#include "../base/src/MIterator.C"
#endif // TEMPLATE_IN_HEADER

#endif // _MIterator_H
