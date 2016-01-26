/*
 * $RCSfile: TransientBase.h
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
 *  $Id: TransientBase.h,v 1.2 1996/12/23 10:58:14 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _TransientBase_H
#define _TransientBase_H

#include <fstream>
#include "booga/persistence/DataBase.h"
#include "booga/persistence/POId.h"
#include "booga/base/RCString.h"

class Persistent;
//_____________________________________________________________________ TransientBase

class TransientBase : public DataBase {
  declareRTTI(TransientBase);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  TransientBase();
private:
  TransientBase(const TransientBase&);             // No copies.

public:
  virtual ~TransientBase();

private:
  TransientBase& operator=(const TransientBase&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class DataBase
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual POId getUniquePOId();

  virtual int write(Persistent* p);
  virtual Persistent* load(const POId& id);
  
  virtual int setObjectName(char* name, const POId& oid);
  virtual POId lookupObject(char* name);
  static TransientBase* getTheTransientBase();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

private:
  static TransientBase* theTransientBase;
  PObjectId myOIdCount;
  POId myCurrPOId;
};

//______________________________________________________________________ INLINES

#endif // _TransientBase_H

