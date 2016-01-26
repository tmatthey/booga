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
 *  $Id: GDBOperation.C,v 1.3 1997/02/20 09:30:34 collison Exp $
 * -----------------------------------------------------------------------------
 */
 


#include "booga/base/Report.h"
#include "booga/persistence/PRef.h"
#include "booga/persistence/PExtra.h"  // Marshal << RCString;
#include "booga/persistence/Transaction.h"
#include "booga/graphicsdb/GDBData.h"
#include "booga/graphicsdb/GDBOperation.h"
#include "booga/graphicsdb/GDBDataType.h"
#include "booga/graphicsdb/GDBRepType.h"

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
myDefaultConfig(),
myCurrentConfig(),
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
myDefaultConfig(),
myCurrentConfig(),
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
      ostrstream os;
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
        ostrstream os;
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
        ostrstream os;
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
      ostrstream os;
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
        ostrstream os;
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
    ostrstream os;
    os << "[GDBOperation::doExecute] " << myName << " failed";
    Report::recoverable(os);
    transaction.abort();
  } else {
    if (myTarget != NULL) {
      myTarget->setGenerator(this);
      myTarget->setGeneratorConfig(getCurrentConfiguration());
    }
    transaction.commit();
  }
  return POID_NULL;
}

bool GDBOperation::doExecute() {
  ostrstream os;
  os << "[GDBOperation::doExecute] dummy operation, nothing really happend!";
  Report::recoverable(os);
  return false;
}

GDBTraversal::Result GDBOperation::announceVisit(GDBData*) {
  ostrstream os;
  os << "[GDBOperation::announceVisit] dummy announceVisit called!";
  Report::recoverable(os);
  return GDBTraversal::EXIT;
}

GDBTraversal::Result GDBOperation::visit(GDBData*) {
  ostrstream os;
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

GDBConfiguration GDBOperation::getCurrentConfiguration() {
  return myCurrentConfig;
}

GDBConfiguration GDBOperation::getDefaultConfiguration() {
  return myDefaultConfig;
}

void GDBOperation::setCurrentConfiguration(GDBConfiguration& aConfig) {
  myCurrentConfig = aConfig;
}

void GDBOperation::setDefaultConfiguration(GDBConfiguration& aConfig) {
  myDefaultConfig = aConfig;
}

bool GDBOperation::getConfigValue(RCString name, Value& retValue) {
  if (myCurrentConfig.getValue(name, retValue)) return true;
  if (myDefaultConfig.getValue(name, retValue)) return true;
  return false;
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
  m << anOp.myDefaultConfig;
  return m;
}

Marshal& operator>>(Marshal& m, GDBOperation& anOp) {
  m >> anOp.myName;
  m >> anOp.mySourceType;
  m >> anOp.mySourceFormat;
  m >> anOp.myTargetType;
  m >> anOp.myTargetFormat;
  m >> anOp.myDefaultConfig;
  // anOp.myCurrentConfig = anOp.myDefaultConfig;
  return m;
}
