/*
 *
 * CTVariableDescription.C
 *
 * Copyright (C) 1994-96, Thomas Wenger <wenger@iam.unibe.ch>
 *                        Thomas von Siebenthal <siebenth@iam.unibe.ch>
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
 *  $Id: CTVariableDescription.C,v 1.5 1996/08/16 09:16:24 siebenth Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "CTVariableDescription.h"

//________________________________________________________ CTVariableDescription


CTVariableDescription::CTVariableDescription () {
  myType = "";
  myInitValue = "";
  myName = "";
};

const RCString& CTVariableDescription::getName() const {
  return myName;
};

void CTVariableDescription::setName(const RCString& Name) {
  myName = Name;
};
  
const RCString& CTVariableDescription::getType() const {
  return myType;
};

void CTVariableDescription::setType(const RCString& Type) {
  myType = Type;
};
   
const RCString& CTVariableDescription::getInitValue() const {
  return myInitValue;
};

void CTVariableDescription::setInitValue(const RCString& InitValue) {
  myInitValue = InitValue;
};
 
