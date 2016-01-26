/*
 * 
 * $RCSfile: PersistentManager.C 
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
 *  $Id: PersistentManager.C,v 1.10 1996/12/06 16:46:24 collison Exp $
 * -----------------------------------------------------------------------------
 */
 

#include <iostream.h>
#include "booga/base/RCString.h"
#include "booga/base/Report.h"
#include "POId.h"
#include "Persistent.h"
#include "DataBase.h"
#include "Transaction.h"
#include "PersistentManager.h"

PersistentManager* PersistentManager::thePersistentManager = NULL;

//_____________________________________________________________________ PersistentManager

PersistentManager::PersistentManager(long size) 
: myMemTable(NULL),
myDataBaseTable(NULL),
myPrototypeTable(NULL)
{
  if (thePersistentManager != NULL) {
    ostrstream os;
    os << "[PersistentManager::Persistentmanager] ";
    os << "Only one instance of class PersistantManager allowed!";
    Report::error(os);
    exit(1);
  }
  myMemTable = new SymTable<POId, Persistent*>(size);
  myDataBaseTable = new SymTable<PDBId, DataBase*>(256);
  myPrototypeTable = new SymTable<RCString, Persistent*>(1024);
  thePersistentManager = this;
}

PersistentManager::~PersistentManager() {
  delete myMemTable;
  delete myDataBaseTable;
  delete myPrototypeTable;
  thePersistentManager = NULL;
}

PersistentManager* PersistentManager::getThePersistentManager() {
  return thePersistentManager;
}

void PersistentManager::registerPrototype(Persistent* p) {
  myPrototypeTable->insert(typeid(p).name(),p);
}

Persistent* PersistentManager::newInstance(char* typeName) {
  Persistent* prot = NULL;
  if (myPrototypeTable->lookup(RCString(typeName),prot)) {
    return prot->newInstance();
  }
  return NULL;
}

void PersistentManager::addDataBase(DataBase& aDB) {
  myDataBaseTable->insert(aDB.getPDBId(),&aDB);
}

void PersistentManager::addPersistent(Persistent *p) {
  if (Transaction::getTransactionLevel() > 1) {
    Transaction::loaded(p);
    myMemTable->insert(p->getPOId(),p);
  }
  else {
    ostrstream os;
    os << "[PersistentManager::addPersistent] no active transaction "
       << p->getPOId();
    Report::error(os);
  }
}

void PersistentManager::removePersistent(Persistent *p) {
  myMemTable->remove(p->getPOId());
  // Warning: does not remove object from Transaction.myLoaded unless explicitly done
}

Persistent* PersistentManager::load(const POId& id) {
  // check if object is allready loaded into memory
  Persistent* obj=NULL;
  if (!myMemTable->lookup(id, obj)){  // no, try to load object
    if (id == POID_NULL) {            // check for NULL ObjectId
      ostrstream os;
      os << "[PersistentManager::load()] ridiculous try "
         << "to load a POID_NULL object";
      Report::recoverable(os);
      return NULL;
    }
    // get database on which the object is stored
    DataBase *db;
    if (!myDataBaseTable->lookup(id.getPDBId(), db)) {
      ostrstream os;
      os << "[PersistentManager::load()] can't find database on which ";
      os << id << "is supposed to live";
      Report::recoverable(os);
      return NULL;
    }
    // try to load object from database
    obj = db->load(id);
    if (obj != NULL) addPersistent(obj);
  }
  return obj;
}
  
