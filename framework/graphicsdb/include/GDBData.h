/*
 * $RCSfile: GDBData.h
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
 *  $Id: GDBData.h,v 1.3 1997/02/20 09:30:31 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GDBData_H
#define _GDBData_H

#include <iostream.h>
#include "booga/base/List.h"
#include "booga/persistence/Set.h"
#include "booga/persistence/PRef.h"
#include "booga/persistence/Persistent.h"
#include "booga/persistence/PExtraTemplates.h"
#include "booga/persistence/PBinary.h"
#include "booga/graphicsdb/GDBConfiguration.h"
#include "booga/graphicsdb/GDBOperation.h"

class RCString;
class Marshal;
class GDBData;
class GDBDataType;
class GDBRepType;


//_____________________________________________________________________ GDBData

class GDBData : public Persistent {
declareRTTI(GDBData);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Local types/enums
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  enum Status { 
    FROZEN=1,
    CHANGED=2,
    UPDATE_REQUIERED=4
  };

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GDBData(DataBase& aDB, const RCString& name);
  GDBData(Prototype);
  // GDBData(const GDBData&); 

public:
  virtual ~GDBData();
  
private:
  GDBData& operator=(const GDBData&);  // No assignments.

public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GDBData
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setName(const RCString& name);
  void setType(const PRef<GDBDataType>& aGDBDataType);
  void setFormat(const PRef<GDBRepType>& aGDBRepType);
  void setType(const RCString& typeName);
  void setFormat(const RCString& formatname);
  void setStatus(long setFlags);
  void setIcon(GDBData* icon);
  
  RCString getName() const;
  GDBDataType* getType() const;
  GDBRepType* getFormat() const;
  RCString getNameId() const;
  RCString getNameIdFormat() const;
  GDBData* getIcon();
  long getStatus() const;

  void setParts(Set<PRef<GDBData> > parts);
//  void setPartOf(GDBData* obj);
//  void setNextVersion(GDBData* obj);
  void setPreviousVersion(GDBData* obj);
  
  const Set<PRef<GDBData> >& getParts() const;
  const Set<PRef<GDBData> >& getPartOf() const;
  PRef<GDBData> getPreviousVersion() const;
  const Set<PRef<GDBData> >& getNextVersion() const;
  PRef<GDBData> getSource() const;
  GDBOperation* getGenerator() const;
  GDBConfiguration getGeneratorConfig() const;
  const Set<PRef<GDBData> >& getTarget() const;

  void setSource(GDBData* source);
  void setGenerator(GDBOperation* op);
  void setGeneratorConfig(const GDBConfiguration& genConfig);
  void addTarget(GDBData* target);

  GDBData* newVersion();
 
  void setData(const RCString& newData);
  RCString getData() const;
  void setBinaryData(PBinary* pbinary);
  PBinary* getBinaryData();

//  GDBOperationInfo getSource(long i);
//  GDBOperationInfo getTarget(long i); // Or get the whole List ?

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Persistent
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Persistent* newInstance();
  virtual int destroy();  // destroyes persistent object in database

  virtual void marshal(Marshal* aMarshal);
  virtual void unmarshal(Marshal* aMarshal);

  friend Marshal& operator<<(Marshal& aDB, GDBData& obj);
  friend Marshal& operator>>(Marshal& aDB, GDBData& obj);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

private:
   long myStatus;     // frozen, changed
   RCString myName;
   PRef<GDBDataType> myType;
   PRef<GDBRepType> myFormat; // Format of object representation
   RCString myKeywords; // ??? may be better as a Feature
   RCString myDescription;

   PRef<GDBData> myIcon; // GDBData object holding the icon
   // PRef<GDBOwner> myOwner;
   Set<PRef<GDBData> > myParts;
   Set<PRef<GDBData> > myPartOf;
   PRef<GDBData>   myPreviousVersion;
   Set<PRef<GDBData> > myNextVersion; //saved under same name after editing (Prev & Next of same Type)
   PRef<GDBData> mySource;
   PRef<GDBOperation> myGenerator;
   GDBConfiguration myGeneratorConfig;
   Set<PRef<GDBData> > myTarget;
   RCString myData;
   PRef<PBinary> myBinaryData;  // binary data is stored in an external object
};

//______________________________________________________________________ INLINES

#endif // _GDBData_H
