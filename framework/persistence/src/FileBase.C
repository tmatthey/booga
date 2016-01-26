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
 *  $Id: FileBase.C,v 1.2 1996/12/23 10:57:22 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <typeinfo>
#include <streambuf>
#include "booga/base/Report.h"
#include "booga/persistence/POId.h"
#include "booga/persistence/Persistent.h"
#include "booga/persistence/PersistentManager.h"
#include "booga/persistence/FileBase.h"
#include "booga/persistence/PExtra.h"
#include "booga/persistence/AsciiMarshal.h"
#include "booga/persistence/Transaction.h"

//const int FILEBASE_OPENPROT = 0664;
//_____________________________________________________________________ FileBase

implementRTTI(FileBase, DataBase);
FileBase::FileBase(char *dirPath)
: myDirPath(dirPath),
myFilename("")
{
  myMarshal = new AsciiMarshal();
  std::stringstream filename;
  filename << myDirPath 
           << ".dbCounter";
  myOIdCounterFilename = RCString(filename);
  std::stringstream filename2;
  filename2 << myDirPath 
           << ".dbObjectNames";
  myObjectNamesFilename = RCString(filename2);
 
  readOIdCounter();
  
  if (PersistentManager::getThePersistentManager() != NULL){
    PersistentManager::getThePersistentManager()->addDataBase(*this);
  }

  // load(POId(myPDBId,1));
}

FileBase::~FileBase() {
}

void FileBase::readOIdCounter() {
  myCounterFile.open(myOIdCounterFilename.chars(),std::ios::in);
  myCounterFile >> myPDBId;
  myCounterFile >> myOIdCount;
  myCounterFile.close();
}

void FileBase::writeOIdCounter() {
  myCounterFile.open(myOIdCounterFilename.chars(),std::ios::out);//,FILEBASE_OPENPROT);
  //  fchmod(myCounterFile.rdbuf()->fd(),FILEBASE_OPENPROT);
  myCounterFile << myPDBId << std::endl;
  myCounterFile << myOIdCount << std::endl;
  myCounterFile.close();
}

void FileBase::readObjectNames() {
  std::fstream fin;
  fin.open(myObjectNamesFilename.chars(),std::ios::in);
  myMarshal->useInputStream(fin);
  *myMarshal >> myObjectNames;
  myMarshal->useInputStream(std::cin);
  fin.close();
}

void FileBase::writeObjectNames() {
  std::fstream fout;
  fout.open(myObjectNamesFilename.chars(),std::ios::out);//,FILEBASE_OPENPROT);
  //  fchmod(fout.rdbuf()->fd());//,FILEBASE_OPENPROT);
  myMarshal->useOutputStream(fout);
  *myMarshal << myObjectNames;
  myMarshal->useOutputStream(std::cout);
  fout.close();
}

POId FileBase::getUniquePOId() {
  // get a unique POId;
  readOIdCounter();
  myOIdCount++;
  writeOIdCounter();
  
  return POId(myPDBId,myOIdCount);
}

int FileBase::setObjectName(char* name, const POId& oid) {
  readObjectNames();
  RCString key(name);
  POId dummy;
  if (myObjectNames.lookup(key,dummy)) {
    std::stringstream os;
    os << "[FileBase::setObjectName] name allready used " 
       << key << " " << oid;
    Report::warning(os);
    return 0;
  }
  myObjectNames.insert(key,oid);
  writeObjectNames();
  return 1;
}

POId FileBase::lookupObject(char* name) {
  readObjectNames();
  RCString key = RCString(name);
  POId oid(POID_NULL);
  myObjectNames.lookup(key, oid);
  return oid;
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
  myFile.open(myFilename.chars(),std::ios::out);//,FILEBASE_OPENPROT);
  //  fchmod(myFile.rdbuf()->fd());//,FILEBASE_OPENPROT);

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



