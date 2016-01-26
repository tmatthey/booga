/*
 * $RCSfile: PixmapGeneratorWrapper.C,v $
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
 *  $Id: PixmapGeneratorWrapper.C,v 1.2 1996/08/30 13:53:33 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/pixmapOp/PixmapGenerator.h"
#include "booga/object/Aggregate2D.h"
#include "booga/object/Pixmap2D.h"
#include "booga/component/PixmapGeneratorWrapper.h"

//_______________________________________________________ PixmapGeneratorWrapper

implementRTTI(PixmapGeneratorWrapper, AbstractPixmapOperation);

PixmapGeneratorWrapper::PixmapGeneratorWrapper(PixmapGenerator* adoptOperation, 
                                               Type traversalType)
: AbstractPixmapOperation(traversalType)
{
  myOperation = adoptOperation;
}

PixmapGeneratorWrapper::~PixmapGeneratorWrapper()
{
  delete myOperation;
}

void PixmapGeneratorWrapper::adoptOperation(PixmapGenerator* operation)
{
  //
  // Self assignment?
  //
  if (myOperation == operation)
    return;
    
  delete myOperation;
  myOperation = operation;
}

const PixmapGenerator* PixmapGeneratorWrapper::getOperation() const
{
  return myOperation;
}

bool PixmapGeneratorWrapper::operateOnPixmap2D(Pixmap2D* obj)
{
  if (myOperation == NULL) {
    Report::warning("[PixmapGeneratorWrapper::operateOnPixmap2D] called without pixmap operation assigned");
    return false;
  }

  AbstractPixmap* newPixi = NULL;
  //
  // Terminate Traversal, if operation went wrong
  //
  if ((newPixi = myOperation->generate(obj->getPixmap())) == NULL) {
    Report::warning("[PixmapGeneratorWrapper::operateOnPixmap2D] operation failed");
    return false;
  }

  getResult()->getObjects()->adoptObject(new Pixmap2D(newPixi));

  return true;
}
