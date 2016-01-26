/*
 * $RCSfile: POId.C 
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
 *  $Id: POId.C,v 1.1 1996/12/11 13:59:25 collison Exp $
 * -----------------------------------------------------------------------------
 */
 

#include <iostream.h>
#include "booga/persistence/DataBase.h"
#include "booga/persistence/POId.h"
#include "booga/persistence/Marshal.h"

const POId POID_NULL;

//_____________________________________________________________________ POId

POId::POId() 
: myPDBId(PDBID_NULL), 
myPObjectId(POBJECTID_NULL)
{
}

POId::POId(PDBId a, PObjectId b) 
: myPDBId(a), 
myPObjectId(b)
{
}

POId::POId(const POId& anId) 
: myPDBId(anId.myPDBId),
myPObjectId(anId.myPObjectId)
{
}

POId& POId::operator=(const POId& anId) {
  myPDBId = anId.myPDBId;
  myPObjectId = anId.myPObjectId;
  return *this;
}

int POId::operator==(const POId& anId) const
{
  return (myPDBId == anId.myPDBId && 
          myPObjectId == anId.myPObjectId);
}

int POId::operator!=(const POId& anId) const 
{
  return (myPDBId != anId.myPDBId ||
          myPObjectId != anId.myPObjectId);
}

int POId::operator<(const POId& anId) const 
{
  return ((myPDBId < anId.myPDBId) || 
  ((myPDBId == anId.myPDBId) && (myPObjectId < anId.myPObjectId)));
}

PDBId POId::getPDBId() const { return myPDBId; }

PObjectId POId::getPObjectId() const { return myPObjectId; }

Marshal& operator<<(Marshal& m, const POId& id) {
  m << id.myPDBId;
  m << id.myPObjectId;
  return m;
}

Marshal& operator>>(Marshal& m, POId& id) {
  m >> id.myPDBId;
  m >> id.myPObjectId;
  return m;
}
 
ostream& operator<<(ostream& out, const POId& anId) {
  out << anId.myPDBId  << "." << anId.myPObjectId; 
  return out;
}
