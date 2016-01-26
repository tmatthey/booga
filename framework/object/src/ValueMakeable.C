/*
 * ValueMakeable.C
 *
 * Copyright (C) 1994, Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: ValueMakeable.C,v 1.2 1995/04/21 12:37:00 amann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/ValueMakeable.h"

implementRTTI(ValueMakeable, Makeable);

ValueMakeable::ValueMakeable(const Value& value)
: myValue(value)     
{}

Makeable* ValueMakeable::make(RCString& errMsg, 
                              const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new ValueMakeable(*this);
}
