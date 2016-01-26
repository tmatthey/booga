/*
 * $RCSfile: PixmapTransformerWrapper.C,v $
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
 *  $Id: PixmapTransformerWrapper.C,v 1.2 1996/08/30 13:53:38 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/pixmapOp/PixmapTransformer.h"
#include "booga/object/Pixmap2D.h"
#include "booga/component/PixmapTransformerWrapper.h"

//_____________________________________________________ PixmapTransformerWrapper

implementRTTI(PixmapTransformerWrapper, AbstractPixmapOperation);

PixmapTransformerWrapper::PixmapTransformerWrapper(PixmapTransformer* adoptOperation, 
                                                   Type traversalType)
: AbstractPixmapOperation(traversalType)
{
  myOperation = adoptOperation;
}

PixmapTransformerWrapper::~PixmapTransformerWrapper()
{
  delete myOperation;
}

void PixmapTransformerWrapper::adoptOperation(PixmapTransformer* operation)
{
  //
  // Self assignment?
  //
  if (myOperation == operation)
    return;
    
  delete myOperation;
  myOperation = operation;
}

const PixmapTransformer* PixmapTransformerWrapper::getOperation() const
{
  return myOperation;
}

bool PixmapTransformerWrapper::operateOnPixmap2D(Pixmap2D* obj)
{
  if (myOperation == NULL) {
    Report::warning("[PixmapTransformerWrapper::operateOnPixmap2D] called without pixmap operation assigned");
    return false;
  }
  
  myOperation->apply(obj->getPixmap());

  return true;
}

