/*
 * $RCSfile: BistableObject3DAttr.h,v $
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
 *  $Id: BistableObject3DAttr.h,v 1.2 1996/08/07 09:20:17 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _BistableObject3DAttr_H
#define _BistableObject3DAttr_H

#include "booga/object/BistableObject3D.h"
#include "booga/object/Object3DAttr.h"

class Object3D;


//_______________________________________________________ BistableObject3DAttrOn

class BistableObject3DAttrOn : public Object3DAttrObject {
declareRTTI(BistableObject3DAttrOn);
// enable RTTI support

public:
  BistableObject3DAttrOn(Exemplar);

  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Object3D* object) const;
};

//______________________________________________________ BistableObject3DAttrOff

class BistableObject3DAttrOff : public Object3DAttrObject {
declareRTTI(BistableObject3DAttrOff);
// enable RTTI support

public:
  BistableObject3DAttrOff(Exemplar);

  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Object3D* object) const;
};

#endif // _BistableObject3DAttr_H

