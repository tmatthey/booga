/*
 * $RCSfile: Persistent.C 
 *
 * Copyright (C) 1996, Andrey Collison <collisona@iam.unibe.ch>
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
 *  $Id: Persistent.C,v 1.1 1996/12/11 13:59:14 collison Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/persistence/Persistent.h"
#include "booga/persistence/DataBase.h"
#include "booga/persistence/PersistentManager.h"
#include "booga/persistence/Transaction.h"

//_____________________________________________________________________ Persistent

implementRTTIBase(Persistent);

Persistent::Persistent(DataBase& aDB) :
myPOId(aDB.getUniquePOId()),
myDB(&aDB)
{
  PersistentManager::getThePersistentManager()->addPersistent(this);
  markChanged(); // make sure that new persistent objects will be stored
}

Persistent::Persistent(Prototype) 
: myPOId(PDBID_NULL,POBJECTID_NULL),
myDB(NULL), myChanged(0)
{
}

//
// deleting representation in memory leaves object in database unaffected
//
Persistent::~Persistent() {
  PersistentManager::getThePersistentManager()->removePersistent(this);
  // Warning: Don't delete persistence objects during active rransactions!
}

POId Persistent::getPOId() const {
  return myPOId;
}

DataBase& Persistent::getDataBase() {
  return *myDB;
}

void Persistent::setPOId(const POId& id) {
  myPOId = id;
}

void Persistent::setDataBase(DataBase& aDB) {
  myDB = &aDB;
}

void Persistent::markChanged() {
  int level = Transaction::getTransactionLevel();
  if (level != myChanged) {
    myChanged = level;
    Transaction::changed(this); // inform the current Transaction about changes
  }
}

int Persistent::hasChanged() const {
  return myChanged;
}

int Persistent::destroy() {
  return 0;
}

