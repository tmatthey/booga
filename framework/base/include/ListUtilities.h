/*
 * ListUtilities.h
 *
 * Copyright (C) 1995, Christoph Streit <streit@iam.unibe.ch>
 *                     Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: ListUtilities.h,v 1.2 1996/03/02 12:23:38 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ListUtilities_H
#define _ListUtilities_H

#include <stdlib.h>
#include "booga/base/PrimitiveTypes.h"  // bool
#include "booga/base/List.h"

//___________________________________________________________________ deleteList
//
// delete all list elements in the list
// returns:  false, when NULL pointer passed
//           true   otherwise
//

template <class TList>
inline bool deleteList(TList*& theList)
{
  if (theList != NULL) {
    long count = theList->count();
    for (long i=0; i<count; i++)
      delete theList->item(i);
    delete theList;
    
    theList = NULL;
    return true;
  } else
    return false;
}

#endif // _ListUtilities_H

