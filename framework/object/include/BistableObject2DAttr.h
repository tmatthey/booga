/*
 * $RCSfile: BistableObject2DAttr.h,v $
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
 *  $Id: BistableObject2DAttr.h,v 1.1 1996/08/07 09:20:14 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _BistableObject2DAttr_H
#define _BistableObject2DAttr_H

#include "booga/object/BistableObject2D.h"
#include "booga/object/Object2DAttr.h"

class Object2D;


//_______________________________________________________ BistableObject2DAttrOn

class BistableObject2DAttrOn : public Object2DAttrObject {
declareRTTI(BistableObject2DAttrOn);
// enable RTTI support

public:
  BistableObject2DAttrOn(Exemplar);

  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Object2D* object) const;
};

//______________________________________________________ BistableObject2DAttrOff

class BistableObject2DAttrOff : public Object2DAttrObject {
declareRTTI(BistableObject2DAttrOff);
// enable RTTI support

public:
  BistableObject2DAttrOff(Exemplar);

  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Object2D* object) const;
};

#endif // _BistableObject2DAttr_H

