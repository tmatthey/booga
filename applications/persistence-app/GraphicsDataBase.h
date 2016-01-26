/*
 * $RCSfile: GraphicsDataBase.h,v $
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
 *  $Id: GraphicsDataBase.h,v 1.1 1996/12/06 16:44:45 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GraphicsDataBase_H
#define _GraphicsDataBase_H

#include "Persistent.h"
#include "PRef.h"
#include "DataBase.h"
#include "GDBDataType.h"
#include "GDBRepType.h"
#include "GDBOperation.h"

class Marshal;
class GDBData;

//_____________________________________________________________________ GraphicsDataBase

class GraphicsDataBase : public Persistent {
declareRTTI(GraphicsDataBase);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GraphicsDataBase(DataBase& aDB);
  GraphicsDataBase(Prototype aPrototype);
  ~GraphicsDataBase();
  
private:
  GraphicsDataBase(const GraphicsDataBase&);             // No copies.

public:
  // virtual ~GraphicsDataBase();                // Use default version.

private:
  GraphicsDataBase& operator=(const GraphicsDataBase&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GraphicsDataBase
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void registerDataType(GDBDataType* aDataType);
  void registerRepType(GDBRepType* aRepType);
  void registerOperation(GDBOperation* anOp);

  GDBDataType* getDataType(const RCString& typeName) const;
  GDBRepType* getRepType(const RCString& repName) const;
  GDBOperation* getOperation(const RCString& opName);
  static GraphicsDataBase* getTheGraphicsDataBase();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Persistent
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Persistent* newInstance();
  virtual int destroy();  // destroyes persistent object in database

  virtual void marshal(Marshal* aMarshal);
  virtual void unmarshal(Marshal* aMarshal);

  friend Marshal& operator<<(Marshal& m, GraphicsDataBase& obj);
  friend Marshal& operator>>(Marshal& m, GraphicsDataBase& obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  DataBase* myPoolDB;

  // DataBase* myUserDB;
  Set<PRef<GDBDataType> > myGDBDataTypes;
  Set<PRef<GDBRepType> > myGDBRepTypes;
  Set<PRef<GDBOperation> > myGDBOperations;
  static GraphicsDataBase* theGraphicsDataBase;
};

//______________________________________________________________________ INLINES

#endif // _GraphicsDataBase_H

