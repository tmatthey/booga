/*
 * $RCSfile: DataBase.C 
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
 *  $Id: DataBase.C,v 1.2 1996/12/23 10:57:19 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Report.h"
#include "booga/persistence/DataBase.h"
#include "booga/persistence/PersistentManager.h"
#include "booga/persistence/Marshal.h"

//_____________________________________________________________________ DataBase

implementRTTIBase(DataBase);
DataBase::DataBase() :
myMarshal(NULL)
{  
  if (PersistentManager::getThePersistentManager() == NULL) {
    ostrstream os;
    os << "[DataBase::DataBase] Create the PersistentManager before creating a DataBase instance";
    Report::error(os);
    exit(0);
  }
}

DataBase::~DataBase() {
  delete myMarshal;
}

PDBId DataBase::getPDBId() {
  return myPDBId;
}

Marshal* DataBase::getMarshal() {
  return myMarshal;
}
