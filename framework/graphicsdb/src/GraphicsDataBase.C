/*
 * $RCSfile: GraphicsDataBase.C,v $
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
 *  $Id: GraphicsDataBase.C,v 1.1 1996/12/11 13:58:23 collison Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/persistence/Marshal.h"
#include "booga/graphicsdb/GraphicsDataBase.h"

//_____________________________________________________________________ GraphicsDataBase

implementRTTI(GraphicsDataBase, Persistent);

GraphicsDataBase* GraphicsDataBase::theGraphicsDataBase = NULL;

//_____________________________________________________________________ PersistentManager


GraphicsDataBase::GraphicsDataBase(DataBase& aDB) :
Persistent(aDB)
{
  if (theGraphicsDataBase != NULL) {
    ostrstream os;
    os << "[GraphicsDatabase::GraphicsDataBase(DataBase&)] ";
    os << "Only one instance of class GraphicsDataBase allowed!";
    Report::warning(os);
    // exit(1);
  }
  theGraphicsDataBase = this;
}

GraphicsDataBase::GraphicsDataBase(Prototype aPrototype) :
Persistent(aPrototype)
{
  if (theGraphicsDataBase != NULL) {
    ostrstream os;
    os << "[GraphicsDatabase::GraphicsDataBase(Prototype)] ";
    os << "Only one instance of class GraphicsDataBase allowed!";
    Report::warning(os);
    // exit(1);
  }
  theGraphicsDataBase = this;
}

GraphicsDataBase::~GraphicsDataBase() {
  if (theGraphicsDataBase == this) theGraphicsDataBase = NULL;
}

GraphicsDataBase* GraphicsDataBase::getTheGraphicsDataBase() {
  return theGraphicsDataBase;
}

void GraphicsDataBase::registerDataType(GDBDataType* aDataType) {
  // here we should check for dublicates...
  myGDBDataTypes.insertElement(PRef<GDBDataType>(aDataType));
}

void GraphicsDataBase::registerRepType(GDBRepType* aRepType) {
  myGDBRepTypes.insertElement(PRef<GDBRepType>(aRepType));
}
 
void GraphicsDataBase::registerOperation(GDBOperation* anOp) {
  myGDBOperations.insertElement(PRef<GDBOperation>(anOp));
}

GDBDataType* GraphicsDataBase::getDataType(const RCString& typeName) const {
  for(int i=0; i<myGDBDataTypes.count(); i++) {
    if (myGDBDataTypes.getElement(i)->getName() == typeName) {
      return myGDBDataTypes.getElement(i).getPtr();
    }
  }
  return NULL;
}

GDBRepType* GraphicsDataBase::getRepType(const RCString& repName) const {
  for(int i=0; i<myGDBRepTypes.count(); i++) {
    if (myGDBRepTypes.getElement(i)->getName() == repName) {
      return myGDBRepTypes.getElement(i).getPtr();
    }
  }
  return NULL;
}

GDBOperation* GraphicsDataBase::getOperation(const RCString& opName) {
  for(int i=0; i<myGDBOperations.count(); i++) {
    if (myGDBOperations.getElement(i)->getName() == opName) {
      return myGDBOperations.getElement(i).getPtr();
    }
  }
  return NULL;
}

Persistent* GraphicsDataBase::newInstance() {
  return new GraphicsDataBase(aPrototype);
}

int GraphicsDataBase::destroy() {
  // destroyes persistent object in database
  return 0;
}

void GraphicsDataBase::marshal(Marshal* aMarshal) {
  *aMarshal << *this;
}

void GraphicsDataBase::unmarshal(Marshal* aMarshal) {
  *aMarshal >> *this;
}

Marshal& operator<<(Marshal& m, GraphicsDataBase& obj) {
  // m << obj.myName;
  m << obj.myGDBDataTypes;
  m << obj.myGDBRepTypes;
  m << obj.myGDBOperations;
  return m;
}

Marshal& operator>>(Marshal& m, GraphicsDataBase& obj) {
  // m >> obj.myName;
  m >> obj.myGDBDataTypes;
  m >> obj.myGDBRepTypes;
  m >> obj.myGDBOperations;
  return m;
}
