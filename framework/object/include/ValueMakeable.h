/*
 * ValueMakeable.h 
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
 *  $Id: ValueMakeable.h,v 1.2 1995/04/21 12:37:02 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ValueMakeable_H
#define _ValueMakeable_H

#include "booga/base/Value.h"
#include "booga/object/Makeable.h"

class ValueMakeable : public Makeable {
  declareRTTI(ValueMakeable);
// enable RTTI support

public:
  ValueMakeable(const Value& value);

  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;

  const Value& getValue() const;

private:
  Value myValue;
};

inline const Value& ValueMakeable::getValue() const
{
  return myValue;
}

#endif // _ValueMakeable_H
