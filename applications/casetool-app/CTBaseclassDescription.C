/*
 * CTBaseclassDescription.C
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
 *  $Id: CTBaseclassDescription.C,v 1.6 1996/10/30 15:31:17 amann Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "CTBaseclassDescription.h"

//_______________________________________________________ CTBaseclassDescription


CTBaseclassDescription::CTBaseclassDescription () {
  myView = Unspecified;
  // myBaseclass = NULL;
};

CTBaseclassDescription::CTEView CTBaseclassDescription::getView() {
  return myView;
};

void CTBaseclassDescription::setView(CTBaseclassDescription::CTEView View) {
  myView = View;
};

CTClassDescription2D* CTBaseclassDescription::getBaseclass() {
  return myBaseclass;
};

void CTBaseclassDescription::setBaseclass(CTClassDescription2D* baseclass) {
  myBaseclass = baseclass;
};  

RCString CTBaseclassDescription::getName() const 
{
  return myName;
}

void CTBaseclassDescription::setName(const RCString& name)
{
  myName = name;
}
