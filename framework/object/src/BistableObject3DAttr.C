/*
 * $RCSfile: BistableObject3DAttr.C,v $ 
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
 *  $Id: BistableObject3DAttr.C,v 1.2 1996/08/07 09:20:16 amann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <sstream>

#include "booga/object/BistableObject3DAttr.h"

//______________________________________________________________ BistableObject3DAttrOn

implementRTTI(BistableObject3DAttrOn, Object3DAttr);

BistableObject3DAttrOn::BistableObject3DAttrOn(Exemplar exemplar)
: Object3DAttrObject(exemplar)
{}

Makeable* BistableObject3DAttrOn::make(RCString& errMsg, 
				const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new BistableObject3DAttrOn(anExemplar);
}

void BistableObject3DAttrOn::setAttribute(Object3D* object) const
{
  BistableObject3D* bistable = dynamic_cast<BistableObject3D*>(object);
  
  if (bistable == NULL) {
    std::stringstream os;
    os << "[BistableObject3DAttrOn::setAttribute] "
       << "Method applied to inapropriate type "
       << typeid(object).name();
    Report::recoverable(os);
    return;
  }
  
  bistable->adoptOn(myObject);
}

//_______________________________________________________________ BistableObject3DAttrOff

implementRTTI(BistableObject3DAttrOff, Object3DAttr);

BistableObject3DAttrOff::BistableObject3DAttrOff(Exemplar exemplar)
: Object3DAttrObject(exemplar)
{}

Makeable* BistableObject3DAttrOff::make(RCString& errMsg, 
			       const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new BistableObject3DAttrOff(anExemplar);
}

void BistableObject3DAttrOff::setAttribute(Object3D* object) const
{
  BistableObject3D* bistable = dynamic_cast<BistableObject3D*>(object);
  
  if (bistable == NULL) {
    std::stringstream os;
    os << "[BistableObject3DAttrOff::setAttribute] "
       << "Method applied to inapropriate type "
       << typeid(object).name();
    Report::recoverable(os);
    return;
  }
  
  bistable->adoptOff(myObject);
}
