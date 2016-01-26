/*
 * $RCSfile: PixmapTransformerWrapper.h,v $
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
 *  $Id: PixmapTransformerWrapper.h,v 1.1 1996/08/01 12:00:45 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _PixmapTransformerWrapper_H
#define _PixmapTransformerWrapper_H

#include "booga/base/RCString.h"
#include "booga/component/AbstractPixmapOperation.h"

class ofstream;
class PixmapTransformer;

//_____________________________________________________ PixmapTransformerWrapper

class PixmapTransformerWrapper : public AbstractPixmapOperation {
declareRTTI(PixmapTransformerWrapper);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PixmapTransformerWrapper(PixmapTransformer* adoptOperation, 
                           Type traversalType=FIRST);
private:
  PixmapTransformerWrapper(const PixmapTransformerWrapper&);           
  // No copies.

public:
  virtual ~PixmapTransformerWrapper();
  
private:
  PixmapTransformerWrapper& operator=(const PixmapTransformerWrapper&); 
  // No assignment.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class PixmapTransformerWrapper
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void adoptOperation(PixmapTransformer* adoptOperation);
  const PixmapTransformer* getOperation() const;
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class AbstractPixmapOperation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  virtual bool operateOnPixmap2D(Pixmap2D* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  PixmapTransformer* myOperation;
};

#endif // _PixmapTransformerWrapper_H
