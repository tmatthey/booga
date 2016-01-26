/*
 * $RCSfile: DummyMakeable.C,v $
 *
 * Copyright (C) 1996, Andrey Collison <collison@iam.unibe.ch>
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
 *  $Id: DummyMakeable.C,v 1.3 1996/10/04 09:46:34 collison Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/base/Report.h"
#include "booga/object/DummyMakeable.h"
#include "booga/object/MakeableHandler.h"

//_____________________________________________________________________ DummyMakeable

implementRTTI(DummyMakeable, Makeable);

DummyMakeable::DummyMakeable(const RCString& keyword) :
myKeyword(keyword) 
{
}

DummyMakeable::DummyMakeable(const RCString& keyword, const Value& value) :
myKeyword(keyword)
{
  myParameters.append(value);
}

Makeable* DummyMakeable::make(RCString&, 
                         const List<Value*>* ) const {
  //
  // Absolutly dummy! Never use this method!
  //
  Report::recoverable("[DummyMakeable::make] this method never should be called. How did that happen?");
  return new DummyMakeable("errorDummy");
}
 
void DummyMakeable::addParameter(const Value& value) {
  myParameters.append(value);
}

void DummyMakeable::addAttribute(Makeable* attribute) {
  myAttributes.append(attribute);
}

RCString DummyMakeable::getKeyword() const {
  return myKeyword;
}

List<Value*>* DummyMakeable::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  for (int i=0; i<myParameters.count(); i++) {
    parameters->append(new Value(myParameters.item(i)));
  }
  return parameters;
}

void DummyMakeable::iterateAttributes(MakeableHandler* handler) {
  for (int i=0; i<myAttributes.count(); i++) {
    handler->handle(myAttributes.item(i));
  }
}
