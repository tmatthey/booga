/*
 * $RCSfile: MTraversal.C,v $
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
 *  $Id: MTraversal.C,v 1.1 1996/09/13 08:05:00 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
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
# include "booga/component/MTraversal.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER


//_________________________________________________________________ MTraversal<>

template <class TWorld, class TObject, class TPath>
INLINE MTraversal<TWorld,TObject,TPath>::MTraversal()
{
  myWorld = NULL;
  myVisitor = NULL;
  myPath = new TPath;
}

template <class TWorld, class TObject, class TPath>
INLINE MTraversal<TWorld,TObject,TPath>::~MTraversal()
{
  delete myPath;
}

template <class TWorld, class TObject, class TPath>
INLINE bool MTraversal<TWorld,TObject,TPath>::apply(TWorld* world, Visitor* visitor)
{
  if ((myWorld = world) == NULL) {
    Report::recoverable("[MTraversal::apply] world object == NULL");
    return false;
  }

  if ((myVisitor = visitor) == NULL) {
    Report::recoverable("[MTraversal::apply] visitor object == NULL");
    return false;
  }

  myPath->reset();
  reset();
  traverse(myWorld->getObjects());
  
  return true;
}

template <class TWorld, class TObject, class TPath>
INLINE void MTraversal<TWorld,TObject,TPath>::reset()
{
}

#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
