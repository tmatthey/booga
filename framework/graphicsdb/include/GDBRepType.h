/*
 * $RCSfile: GDBRepType.h,v $
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
 *  $Id: GDBRepType.h,v 1.2 1997/01/15 13:46:11 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GDBRepType_H
#define _GDBRepType_H

#include "booga/base/RCString.h"
#include "booga/persistence/Persistent.h"
#include "booga/persistence/PRef.h"
#include "booga/persistence/SimpleIndex.h"
#include "booga/graphicsdb/GDBData.h"

class GDBData;
class GDBRepType;

//_____________________________________________________________________ GDBRepType

class GDBRepType : public Persistent {
declareRTTI(GDBRepType);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GDBRepType(DataBase& aDB, const RCString& name);
  GDBRepType(DataBase& aDB, const RCString& name, const RCString& extension);
  GDBRepType(Prototype aPrototype);
  ~GDBRepType();

private:
  GDBRepType(const GDBRepType&);             // No copies.
  
private:
  GDBRepType& operator=(const GDBRepType&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GDBRepType
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  RCString getName() const;
  RCString getExtension() const;
  GDBRepType* getSuperRepType() const;
  void setSuperRepType(GDBRepType* theSuperRep);
  const SimpleIndex<RCString,PRef<GDBData> >& getExtent();
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

  friend Marshal& operator<<(Marshal& m, GDBRepType& obj);
  friend Marshal& operator>>(Marshal& m, GDBRepType& obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

private:
  RCString myName;
  RCString myExtension;
  PRef<GDBRepType> mySuperRep;
  SimpleIndex<RCString,PRef<GDBData> > myExtent;
};

//______________________________________________________________________ INLINES

#endif // _GDBRepType_H

