/*
 * $RCSfile: TransientBase.C 
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
 *  $Id: TransientBase.C,v 1.2 1996/12/23 10:58:12 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/persistence/POId.h"
#include "booga/persistence/Persistent.h"
#include "booga/persistence/PersistentManager.h"
#include "booga/persistence/TransientBase.h"
#include "booga/base/Report.h"

TransientBase* TransientBase::theTransientBase = NULL;

//_____________________________________________________________________ TransientBase

implementRTTI(TransientBase, DataBase);

TransientBase::TransientBase() :
myOIdCount(1)
{
  myPDBId = 0;
  if (theTransientBase != NULL) {
    Report::error("[TransientBase::TransientBase] only one instance of TransientBase allowed");
  } else {
    theTransientBase = this;
  }
}

TransientBase::~TransientBase() {
  if (theTransientBase == this) theTransientBase = NULL;
}

TransientBase* TransientBase::getTheTransientBase() {
  return theTransientBase;
}
POId TransientBase::getUniquePOId() {
  // get a unique POId;
  myOIdCount++;
  return POId(myPDBId,myOIdCount);
}

Persistent* TransientBase::load(const POId& id) {
  std::stringstream os;
  os << "[TransientBase::load] can't load " << id << " from a TransientBase";
  Report::recoverable(os);
  return NULL;
}

int TransientBase::write(Persistent* p) {
  std::stringstream os;
  os << "[TransientBase::write] can't write to a TransientBase " << p->getPOId();
  Report::recoverable(os);
  return 0;
}

int TransientBase::setObjectName(char*, const POId&) {
  return 0;
}

POId TransientBase::lookupObject(char*) {
  return POID_NULL;
}
