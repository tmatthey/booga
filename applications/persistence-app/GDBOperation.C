/*
 * $RCSfile: GDBOperation.C,v $
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
 *  $Id: GDBOperation.C,v 1.5 1996/12/06 16:44:21 collison Exp $
 * -----------------------------------------------------------------------------
 */
 


#include "booga/base/Report.h"
#include "PRef.h"
#include "GDBData.h"
#include "GDBOperation.h"
#include "Transaction.h"
#include "GDBDataType.h"
#include "GDBRepType.h"
#include "PExtra.h"  // Marshal << RCString;

//_____________________________________________________________________ GDBOperation

implementRTTI(GDBOperation, Persistent);

GDBOperation::GDBOperation(DataBase& aDB, const RCString& name, 
                           GDBDataType* sourceType, 
                           GDBRepType* sourceFormat,
                           GDBDataType* targetType, 
                           GDBRepType* targetFormat) :
Persistent(aDB),
myName(name),
mySourceType(sourceType),
mySourceFormat(sourceFormat),
myTargetType(targetType),
myTargetFormat(targetFormat),
myTraversal(NULL)
{
}

GDBOperation::GDBOperation(Prototype aPrototype) 
: Persistent(aPrototype),
myName(""),
mySourceType(NULL),
mySourceFormat(NULL),
myTargetType(NULL),
myTargetFormat(NULL),
myTraversal(NULL)
{
}

GDBOperation::~GDBOperation()
{
  delete myTraversal;
}

Persistent* GDBOperation::newInstance()
{
  return new GDBOperation(aPrototype);
}

int GDBOperation::destroy() {
  return 0;
}

RCString GDBOperation::getName() {
  return myName;
}

POId GDBOperation::execute(const POId& source, const POId& target) {
  Transaction transaction;
  
  transaction.begin();
  reset();
  
  if (source == POID_NULL) {
    mySource = NULL; 
  } 
  else {
    mySource = PRef<GDBData>(source).getPtr();
    if (mySource == NULL) {
      std::stringstream os;
      os << "[GDBOperation::execute] ";
      os << "source object " << source << " is of wrong class";
      Report::recoverable(os);
      return POID_NULL; // aborts transaction
    }

    if (mySourceType.getPtr() != NULL) {
      GDBDataType *srcDataType = mySource->getType();
      while (srcDataType != NULL && srcDataType != mySourceType.getPtr()) {
        srcDataType = srcDataType->getBaseType();
      }
      if (srcDataType == NULL) {
        std::stringstream os;
        os << "[GDBOperation::execute] ";
        os << "wrong source type of " << source << ", " << mySourceType->getName() << " expected";
        Report::recoverable(os);
        return POID_NULL; // aborts transaction
      }
    }

    if (mySourceFormat.getPtr() != NULL) {
      GDBRepType *srcRepType = mySource->getFormat();
      while (srcRepType != NULL && srcRepType == mySourceFormat.getPtr()) {
        srcRepType = srcRepType->getSuperRepType();
      }
      if (srcRepType == NULL) {
        std::stringstream os;
        os << "[GDBOperation::execute] ";
        os << "wrong source format of " << source << ", " << mySourceFormat->getName() << " expected";
        Report::recoverable(os);
        return POID_NULL; // aborts transaction
      }
    }
  }
 
  if (target == POID_NULL) {
    myTarget = NULL;
  }
  else {
    myTarget = PRef<GDBData>(target).getPtr();
    if (myTarget == NULL) {
      std::stringstream os;
      os << "[GDBOperation::execute] ";
      os << "target object " << target << " is of wrong class";
      Report::recoverable(os);
      return POID_NULL; // aborts transaction
    }
    if (myTargetType.getPtr() != NULL) {
      GDBDataType* targetDataType = myTargetType.getPtr();
      while (targetDataType != NULL && targetDataType == myTarget->getType()) {
        targetDataType = targetDataType->getBaseType();
      }
      if (targetDataType == NULL) {
        std::stringstream os;
        os << "[GDBOperation::execute] ";
        os << "wrong target type of " << target << ", " << myTargetType->getName() << " expected";
        Report::recoverable(os);
        return POID_NULL; // aborts transaction
      }
    }
    myTarget->setType(myTargetType.getPtr());
    myTarget->setFormat(myTargetFormat.getPtr());
  }
 
  if (doExecute() == false) {
    std::stringstream os;
    os << "[GDBOperation::doExecute] " << myName << " failed";
    Report::recoverable(os);
    transaction.abort();
  } else {
    transaction.commit();
  }
  return POID_NULL;
}

bool GDBOperation::doExecute() {
  std::stringstream os;
  os << "[GDBOperation::doExecute] dummy operation, nothing really happend!";
  Report::recoverable(os);
  return false;
}

GDBTraversal::Result GDBOperation::announceVisit(GDBData*) {
  std::stringstream os;
  os << "[GDBOperation::announceVisit] dummy announceVisit called!";
  Report::recoverable(os);
  return GDBTraversal::EXIT;
}

GDBTraversal::Result GDBOperation::visit(GDBData*) {
  std::stringstream os;
  os << "[GDBOperation::visit] dummy visit called!";
  Report::recoverable(os);
  return GDBTraversal::EXIT;
}

void GDBOperation::reset() {
  myFailedFlag = false; // Reset the failure flag.
}

void GDBOperation::failed() {
  myFailedFlag = true;
}

void GDBOperation::marshal(Marshal* aMarshal) {
  *aMarshal << *this;
}

void GDBOperation::unmarshal(Marshal* aMarshal) {
  *aMarshal >> *this;
}

Marshal& operator<<(Marshal& m, GDBOperation& anOp) {
  m << anOp.myName;
  m << anOp.mySourceType;
  m << anOp.mySourceFormat;
  m << anOp.myTargetType;
  m << anOp.myTargetFormat;
  return m;
}

Marshal& operator>>(Marshal& m, GDBOperation& anOp) {
  m >> anOp.myName;
  m >> anOp.mySourceType;
  m >> anOp.mySourceFormat;
  m >> anOp.myTargetType;
  m >> anOp.myTargetFormat;
  return m;
}
