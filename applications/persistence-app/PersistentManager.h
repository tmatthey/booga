/*
 * $RCSfile: PersistentManager.h
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
 *  $Id: PersistentManager.h,v 1.10 1996/12/06 16:46:26 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PersistentManager_H
#define _PersistentManager_H

#include "booga/base/SymTable.h"
#include "booga/base/RCString.h"
#include "POId.h"

class Persistent;
class DataBase;

//_____________________________________________________________________ PersistentManager

class PersistentManager {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PersistentManager(long size);
  
private:
  PersistentManager(const PersistentManager&);             // No copies.

public:
  virtual ~PersistentManager();
  
private:
  PersistentManager& operator=(const PersistentManager&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class PersistentManager
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void registerPrototype(Persistent* p);
  Persistent *newInstance(char *typeName);
  void addDataBase(DataBase& aDB);
  void addPersistent(Persistent *p);
  void removePersistent(Persistent *p);
  Persistent* load(const POId &id);
  static PersistentManager* getThePersistentManager();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  SymTable<POId,Persistent*> *myMemTable;
  SymTable<PDBId,DataBase*> *myDataBaseTable;
  SymTable<RCString,Persistent*> *myPrototypeTable;
  static PersistentManager* thePersistentManager;
};

//______________________________________________________________________ INLINES


#endif // _PersistentManager_H

