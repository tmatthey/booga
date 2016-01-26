/*
 * $RCSfile: FileBase.C 
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
 *  $Id: FileBase.C,v 1.10 1996/12/06 16:44:00 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Report.h"
#include "POId.h"
#include "Persistent.h"
#include "PersistentManager.h"
#include "FileBase.h"
#include "AsciiMarshal.h"
#include "Transaction.h"

//_____________________________________________________________________ FileBase

implementRTTI(FileBase, DataBase);
FileBase::FileBase(char *dirPath)
: myDirPath(dirPath),
myFilename("")
{
  myMarshal = new AsciiMarshal();
  std::stringstream filename;
  filename << myDirPath 
           << ".dbinfo";
  myInfoFilename = RCString(filename);

  readDBInfo();
  
  if (PersistentManager::getThePersistentManager() != NULL){
    PersistentManager::getThePersistentManager()->addDataBase(*this);
  }

  // load(POId(myPDBId,1));
}

FileBase::~FileBase() {
}

void FileBase::readDBInfo() {
  myInfoFile.open(myInfoFilename.chars(),std::ios::in);
  myInfoFile >> myPDBId;
  myInfoFile >> myOIdCount;
  myInfoFile.close();
}

void FileBase::writeDBInfo() {
  myInfoFile.open(myInfoFilename.chars(),std::ios::out);  
  myInfoFile << myPDBId << std::endl;
  myInfoFile << myOIdCount << std::endl;
  myInfoFile.close();
}

POId FileBase::getUniquePOId() {
  // get a unique POId;
  readDBInfo();
  myOIdCount++;
  writeDBInfo();
  
  return POId(myPDBId,myOIdCount);
}

int FileBase::write(Persistent* p) {
  if (p == NULL) {
    return 0;
  }
  myCurrPOId = p->getPOId();

  std::stringstream filename;
  filename << myDirPath 
           << myCurrPOId.getPObjectId();
  myFilename = RCString(filename);
  myFile.open(myFilename.chars(),std::ios::out);

  myFile << myCurrPOId.getPObjectId() << std::endl;
  myFile << typeid(p).name() << std::endl;
  myMarshal->marshal(p, myFile);
  myFile.close();
  return 1;
}

Persistent* FileBase::load(const POId& id) {
  if (Transaction::getTransactionLevel() <= 0) {
    std::stringstream os;
    os << "[FileBase::load] no active Transaction while loading " << id;
    Report::error(os);
  }
  std::stringstream filename;
  filename << myDirPath 
           << id.getPObjectId();
  myFilename = RCString(filename);
  myFile.open(myFilename.chars(),std::ios::in);
  
  PObjectId oid;
  myFile >> oid;
  char typeName[100];
  myFile >> typeName;

  Persistent *obj = PersistentManager::getThePersistentManager()->newInstance(typeName);
  if (obj == NULL) {
    myFile.close();
    std::stringstream os;
    os << "[FileBase::load] object type " << typeName 
       << " not registered. " << id << " not loaded";
    Report::recoverable(os);
    return NULL;
  }
  else {
    obj->setDataBase(*this);
    obj->setPOId(id);
    // myFile.open(myFilename.chars(),std::ios::in);
    myMarshal->unmarshal(obj, myFile);
    myFile.close();
  }
  return obj;
}

int FileBase::setObjectName(char* name, PRef<Persistent>& refAny) {
  return 0;
}

PRef<Persistent> FileBase::lookupObject(char* name) {
  return PRef<Persistent>(POID_NULL);
}

