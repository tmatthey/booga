/*
 * $RCSfile: AbstractPixmapOperation.C,v $
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
 *  $Id: AbstractPixmapOperation.C,v 1.3 1996/09/13 08:03:03 streit Exp $
 * -----------------------------------------------------------------------------
 */
    
#include "booga/object/Pixmap2D.h"
#include "booga/component/AbstractPixmapOperation.h"

//______________________________________________________ AbstractPixmapOperation

implementRTTI(AbstractPixmapOperation, Operation2D);

AbstractPixmapOperation::AbstractPixmapOperation(Type traversalType)
{
  myTraversalType = traversalType;
}

Traversal::Result AbstractPixmapOperation::visit(Pixmap2D* obj)
{
  //
  // Terminate Traversal, if operation went wrong
  //
  if (!operateOnPixmap2D(obj))
    return Traversal::EXIT;

  //
  // Traversal::Result depends on traversal type of Pixmap
  //
  if (myTraversalType == FIRST)
    return Traversal::EXIT;
  else
    return Traversal::CONTINUE;
}

Traversal::Result AbstractPixmapOperation::dispatch(Makeable* obj)
{
  tryConcrete(Pixmap2D, obj);
  
  return Traversal::CONTINUE;
}
