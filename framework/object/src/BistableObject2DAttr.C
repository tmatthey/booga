/*
 * $RCSfile: BistableObject2DAttr.C,v $ 
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
 *  $Id: BistableObject2DAttr.C,v 1.1 1996/08/07 09:20:13 amann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <sstream>

#include "booga/object/BistableObject2DAttr.h"

//______________________________________________________________ BistableObject2DAttrOn

implementRTTI(BistableObject2DAttrOn, Object2DAttr);

BistableObject2DAttrOn::BistableObject2DAttrOn(Exemplar exemplar)
: Object2DAttrObject(exemplar)
{}

Makeable* BistableObject2DAttrOn::make(RCString& errMsg, 
				const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new BistableObject2DAttrOn(anExemplar);
}

void BistableObject2DAttrOn::setAttribute(Object2D* object) const
{
  BistableObject2D* bistable = dynamic_cast<BistableObject2D*>(object);
  
  if (bistable == NULL) {
    std::stringstream os;
    os << "[BistableObject2DAttrOn::setAttribute] "
       << "Method applied to inapropriate type "
       << typeid(object).name();
    Report::recoverable(os);
    return;
  }
  
  bistable->adoptOn(myObject);
}

//_______________________________________________________________ BistableObject2DAttrOff

implementRTTI(BistableObject2DAttrOff, Object2DAttr);

BistableObject2DAttrOff::BistableObject2DAttrOff(Exemplar exemplar)
: Object2DAttrObject(exemplar)
{}

Makeable* BistableObject2DAttrOff::make(RCString& errMsg, 
			       const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new BistableObject2DAttrOff(anExemplar);
}

void BistableObject2DAttrOff::setAttribute(Object2D* object) const
{
  BistableObject2D* bistable = dynamic_cast<BistableObject2D*>(object);
  
  if (bistable == NULL) {
    std::stringstream os;
    os << "[BistableObject2DAttrOff::setAttribute] "
       << "Method applied to inapropriate type "
       << typeid(object).name();
    Report::recoverable(os);
    return;
  }
  
  bistable->adoptOff(myObject);
}
