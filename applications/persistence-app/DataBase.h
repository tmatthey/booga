/*
 * $RCSfile: DataBase.h
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
 *  $Id: DataBase.h,v 1.10 1996/12/06 16:43:57 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _DataBase_H
#define _DataBase_H
#include "POId.h"
#include "booga/base/RTTI.h"

#include "Persistent.h"
#include "PRef.h"

class Persistent;
class Marshal;

//_____________________________________________________________________ DataBase

class DataBase {
  declareRTTI(DataBase);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                
public:
  DataBase();
  
private:
  DataBase(const DataBase&);             // No copies.

public:
  virtual ~DataBase();                // Use default version.

private:
  DataBase& operator=(const DataBase&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class DataBase
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PDBId getPDBId();
  Marshal* getMarshal();

  virtual POId getUniquePOId()=0;

  virtual int write(Persistent* p)=0;
  virtual Persistent* load(const POId& id)=0;

  virtual int setObjectName(char* name, PRef<Persistent>& refAny)=0;
  virtual PRef<Persistent> lookupObject(char* name)=0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  PDBId myPDBId;
  Marshal* myMarshal;
};

//______________________________________________________________________ INLINES

#endif // _DataBase_H
