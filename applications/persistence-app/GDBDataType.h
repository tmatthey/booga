/*
 * $RCSfile: GDBDataType.h,v $
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
 *  $Id: GDBDataType.h,v 1.1 1996/12/06 16:44:12 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GDBDataType_H
#define _GDBDataType_H

#include "booga/base/RCString.h"
#include "Persistent.h"
#include "PRef.h"
#include "SimpleIndex.h"
#include "GDBData.h"

class GDBData;
class GDBDataType;
typedef PRef<GDBDataType> GDBDataTypeRef;

//_____________________________________________________________________ GDBDataType

class GDBDataType : public Persistent {
declareRTTI(GDBDataType);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GDBDataType(DataBase& aDB, const RCString& name);
  GDBDataType(Prototype aPrototype);
  ~GDBDataType();

private:
  GDBDataType(const GDBDataType&);             // No copies.
  
private:
  GDBDataType& operator=(const GDBDataType&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GDBDataType
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  RCString getName();
  GDBDataType* getBaseType();
  void setBaseType(GDBDataType* theBaseType);
  const SimpleIndex<RCString, PRef<GDBData> >& getExtent();
  void addToExtent(GDBData& obj);
  void removeFromExtent(GDBData& obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Persistent
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Persistent* newInstance();
  virtual int destroy();

  virtual void marshal(Marshal *aMarshal);
  virtual void unmarshal(Marshal *aMarshal);

  friend Marshal& operator<<(Marshal& m, GDBDataType& obj);
  friend Marshal& operator>>(Marshal& m, GDBDataType& obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typedef PRef<GDBDataType> GDBDataTypeRef;

private:
  RCString myName;
  PRef<GDBDataType> myBaseType;
  SimpleIndex<RCString, PRef<GDBData> > myExtent;
};

//______________________________________________________________________ INLINES

#endif // _GDBDataType_H

