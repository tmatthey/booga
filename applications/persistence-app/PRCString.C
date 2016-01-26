/*
 * $RCSfile: PRCString.C,v $
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
 *  $Id: PRCString.C,v 1.5 1996/12/06 16:46:48 collison Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "PRCString.h"

//_____________________________________________________________________ PRCString

implementRTTI(PRCString, Persistent);

PRCString::PRCString(DataBase& aDB) : 
PersistenceFor<RCString>(aDB)
{}

PRCString::PRCString(Prototype aPrototype) :
PersistenceFor<RCString>(aPrototype)
{}

RCString& PRCString::operator=(char c) {
  return ((RCString&) *this) = c;
}
RCString& PRCString::operator=(const char* s) {
  return ((RCString&) *this) = s;
}

RCString& PRCString::operator=(const RCString& s) {
  return ((RCString&) *this) = s;
}
