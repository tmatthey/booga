/*
 * $RCSfile: GDBOperation.h,v $
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
 *  $Id: GDBOperation.h,v 1.2 1997/01/15 13:46:08 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GDBOperation_H
#define _GDBOperation_H

#include "booga/base/RTTI.h"
#include "booga/base/PrimitiveTypes.h"
#include "booga/base/Value.h"
#include "booga/persistence/Persistent.h"
#include "booga/persistence/POId.h"
#include "booga/persistence/PRef.h"
#include "booga/graphicsdb/GDBTraversal.h"
#include "booga/graphicsdb/GDBConfiguration.h"

class GDBDataType;
class GDBRepType;
class GDBData;

//_____________________________________________________________________ GDBOperation

class GDBOperation : public Persistent {
declareRTTI(GDBOperation);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GDBOperation(DataBase& aDB, const RCString& name, 
               GDBDataType* sourceType, GDBRepType* sourceFormat,
               GDBDataType* targetType, GDBRepType* targetFormat);
  GDBOperation(Prototype aPrototype);
private:
  GDBOperation(const GDBOperation&);             // No copies.

public:
  virtual ~GDBOperation();

private:
  GDBOperation& operator=(const GDBOperation&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GDBOperation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  POId execute(const POId& source, const POId& target);
  virtual bool doExecute();
  virtual GDBTraversal::Result announceVisit(GDBData* object);
  virtual GDBTraversal::Result visit(GDBData* object);
  RCString getName();

  GDBConfiguration getCurrentConfiguration();
  GDBConfiguration getDefaultConfiguration();
  void setCurrentConfiguration(GDBConfiguration& aConfig);
  void setDefaultConfiguration(GDBConfiguration& aConfig);
  bool getConfigValue(RCString name, Value& retValue);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Persistent
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Persistent* newInstance();
  virtual int destroy();  // destroyes persistent object in database

  virtual void marshal(Marshal* aMarshal);
  virtual void unmarshal(Marshal* aMarshal);

  friend Marshal& operator<<(Marshal& m, GDBOperation& anOp);
  friend Marshal& operator>>(Marshal& m, GDBOperation& anOp);
 
protected:
  void reset();
  // Reset the failure flag.
  void failed();
  // To be called if the operation failed.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  RCString myName;
  PRef<GDBDataType> mySourceType;
  PRef<GDBRepType> mySourceFormat;
  PRef<GDBDataType> myTargetType;
  PRef<GDBRepType> myTargetFormat;
  GDBConfiguration myDefaultConfig;
  GDBConfiguration myCurrentConfig; // not saved on database
  GDBData* mySource;
  GDBData* myTarget;
  bool myFailedFlag;
  GDBTraversal* myTraversal;

};

//______________________________________________________________________ INLINES

#endif // _GDBOperation_H

