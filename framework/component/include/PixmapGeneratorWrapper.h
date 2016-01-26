/*
 * $RCSfile: PixmapGeneratorWrapper.h,v $
 *
 * Wrapper component for PixmapGenerator operation from the pixmapOp library.
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: PixmapGeneratorWrapper.h,v 1.1 1996/08/01 12:00:38 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _PixmapGeneratorWrapper_H
#define _PixmapGeneratorWrapper_H

#include "booga/component/AbstractPixmapOperation.h"

class PixmapGenerator;

//_______________________________________________________ PixmapGeneratorWrapper

class PixmapGeneratorWrapper : public AbstractPixmapOperation {
declareRTTI(PixmapGeneratorWrapper);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PixmapGeneratorWrapper(PixmapGenerator* adoptOperation, 
                         Type traversalType=FIRST);
private:
  PixmapGeneratorWrapper(const PixmapGeneratorWrapper&);            
  // No copies.

public:
  virtual ~PixmapGeneratorWrapper();
  
private:
  PixmapGeneratorWrapper& operator=(const PixmapGeneratorWrapper&); 
  // No assignment.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class PixmapGeneratorWrapper
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void adoptOperation(PixmapGenerator* adoptOperation);
  const PixmapGenerator* getOperation() const;
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class AbstractPixmapOperation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  virtual bool operateOnPixmap2D(Pixmap2D* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  PixmapGenerator* myOperation;
};

#endif // _PixmapGeneratorWrapper_H
