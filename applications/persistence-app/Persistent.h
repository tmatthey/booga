/*
 * $RCSfile: Persistent.h
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
 *  $Id: Persistent.h,v 1.10 1996/12/06 16:46:21 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Persistent_H
#define _Persistent_H

#include "Prototype.h"
#include "booga/base/RTTI.h"
#include "POId.h"

class DataBase;
class PersistentManager;

//_____________________________________________________________________ Persistent

class Persistent {
declareRTTI(Persistent);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Persistent(DataBase& aDB);
  Persistent(Prototype);

private:
  Persistent(const Persistent&);

public:
  virtual ~Persistent();

private:
  Persistent& operator=(const Persistent&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Persistent
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Persistent* newInstance()=0;
  void markChanged();      // mark that object has changed
  int hasChanged() const;  // returns Transaction level of last change
  virtual int destroy();   // destroyes persistent object in database
  
  POId getPOId() const;
  DataBase& getDataBase();

public: 
  void setPOId(const POId& id);
  void setDataBase(DataBase& aDB);
  
  virtual void marshal(Marshal* aMarshal) = 0;
  virtual void unmarshal(Marshal* aMarshal) = 0;

//  friend Persistent* PersistentManager::load(POId& id);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  POId myPOId;
  DataBase *myDB;
  int myChanged; // transaction level on which object had last change (0=unchanged)
};

//______________________________________________________________________ INLINES

#endif // _Persistent_H
