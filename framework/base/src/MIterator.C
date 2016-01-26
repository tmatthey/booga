/*
 * MIterator.C 
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
 *  $Id: MIterator.C,v 1.10 1996/01/19 17:05:20 amann Exp $
 * -----------------------------------------------------------------------------
 */
 
//_____________________________________________________________________ MIterator

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#if defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
// Only compile this file if either not GNU compiler running,
// or, in case of GNU compiler, files is included from header.

#include "booga/base/Report.h"

#ifdef TEMPLATE_IN_HEADER
# define INLINE inline
#else
# include "booga/base/MIterator.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER

template<class TObject, class TContainer>
INLINE MIterator<TObject, TContainer>::MIterator()
{
  myContainer      = NULL;
  myCurItem        = 0;
  myContainerCount = 0;
}

template<class TObject, class TContainer>
INLINE void MIterator<TObject, TContainer>::first()
{
  myContainer      = getContainer();
  myCurItem        = 0;
  myContainerCount = myContainer->count();
}

template<class TObject, class TContainer>
INLINE void MIterator<TObject, TContainer>::next()
{
  ++myCurItem;  
}

template<class TObject, class TContainer>
INLINE bool MIterator<TObject, TContainer>::isDone() const
{
  return !(myCurItem < myContainerCount); 
}

template<class TObject, class TContainer>
INLINE int MIterator<TObject, TContainer>::count() const
{
  // 
  // getContainer is not const, but we will call a const 
  // function (count) on the result.
  // Let's cast away the constness here.
  //
  MIterator<TObject, TContainer>* This = (MIterator<TObject, TContainer>*)this;
  return This->getContainer()->count(); 
}

template<class TObject, class TContainer>
INLINE TObject& MIterator<TObject, TContainer>::curItem() const
{
  if (myCurItem >= myContainerCount)
    Report::error("[MIterator::curItem] empty container");
    
  return myContainer->item(myCurItem);
}

#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)

