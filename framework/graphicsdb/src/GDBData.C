/*
 * $RCSfile: GDBData.C 
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
 *  $Id: GDBData.C,v 1.4 1997/03/21 13:09:06 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/RCString.h"
#include "booga/persistence/DataBase.h"
#include "booga/persistence/FileBase.h"
#include "booga/persistence/PExtra.h"
#include "booga/persistence/Prototype.h"
#include "booga/persistence/Marshal.h"
#include "booga/graphicsdb/GDBData.h"
#include "booga/graphicsdb/GDBDataType.h"
#include "booga/graphicsdb/GDBRepType.h"
#include "booga/graphicsdb/GraphicsDataBase.h"

//_____________________________________________________________________ GDBData

implementRTTI(GDBData, Persistent);

GDBData::GDBData(DataBase& aDB, const RCString& name) 
: Persistent(aDB),
myStatus(UPDATE_REQUIERED),
myName(name),
myType(POID_NULL),
myFormat(POID_NULL),
myKeywords(""),
myDescription(""),
myIcon(POID_NULL),
myParts(),
myPartOf(),
myPreviousVersion(POID_NULL),
myNextVersion(),
mySource(POID_NULL),
myGenerator(POID_NULL),
myTarget(),
myData(""),
myBinaryData(POID_NULL)
{
}

GDBData::GDBData(Prototype aPrototype) 
: Persistent(aPrototype),
myStatus(0),
myName(""),
myType(POID_NULL),
myFormat(POID_NULL),
myKeywords(""),
myDescription(""),
myIcon(POID_NULL),
myParts(),
myPartOf(),
myPreviousVersion(POID_NULL),
myNextVersion(),
mySource(POID_NULL),
myGenerator(POID_NULL),
myTarget(),
myData(),
myBinaryData(POID_NULL)
{
}

//
// deleting representation in memory leaves object in database unaffected
//
GDBData::~GDBData()
{
}

Persistent* GDBData::newInstance()
{
  return new GDBData(aPrototype);
}

int GDBData::destroy() {
  return 0;
}

void GDBData::setName(const RCString& name) {
  myName = name;
  markChanged();
}

RCString GDBData::getName() const {
  return myName;
}

RCString GDBData::getNameId() const {
  ostrstream os;
  os << myName << "." << getPOId();
  return RCString(os);
}

RCString GDBData::getNameIdFormat() const {
  ostrstream os;
  os << myName << "." << getPOId() << ".";
  if (myFormat.getPtr() != NULL) {
    os << myFormat->getExtension();
  } else {
    os << "NOFORMAT";
  }
  return RCString(os);
}

void GDBData::setType(const PRef<GDBDataType>& aGDBDataType) {
  if (myType.getPOId() != POID_NULL)
    myType->removeFromExtent(*this);
  myType = aGDBDataType;
  myType->addToExtent(*this);
  markChanged();
}

GDBDataType* GDBData::getType() const {
  return myType.getPtr();
}

void GDBData::setFormat(const PRef<GDBRepType>& aGDBRepType) {
  if (myFormat.getPOId() != POID_NULL)
    myFormat->removeFromExtent(*this);
  myFormat = aGDBRepType;
  myFormat->addToExtent(*this);
  markChanged();
}

GDBRepType* GDBData::getFormat() const {
  return myFormat.getPtr();
}

void GDBData::setType(const RCString& typeName) {
  if (myType.getPOId() != POID_NULL)
    myType->removeFromExtent(*this);
  myType = GraphicsDataBase::getTheGraphicsDataBase()->getDataType(typeName);
  myType->addToExtent(*this);
  markChanged();
}

void GDBData::setFormat(const RCString& formatname) {
  if (myFormat.getPOId() != POID_NULL)
    myFormat->removeFromExtent(*this);
  myFormat = GraphicsDataBase::getTheGraphicsDataBase()->getRepType(formatname);
  myFormat->addToExtent(*this);
  markChanged();
}

void GDBData::setStatus(long setFlags) { 
  myStatus |= setFlags;
  markChanged();
}

long GDBData::getStatus() const { 
  return myStatus; 
}

void GDBData::setIcon(GDBData* icon) {
  if (myIcon.getPOId() != POID_NULL && myIcon.getPOId() != icon->getPOId()) {
    ostrstream os;
    os << "[GDBData::setIcon] set new icon failed (icon allready exists)";
    Report::recoverable(os);
  } 
  else {
    myIcon = icon;
    markChanged();
  }
}

GDBData* GDBData::getIcon() {
  return myIcon.getPtr();
}

void GDBData::setParts(Set<PRef<GDBData> > parts) {
  Set<PRef<GDBData> > removeSet = myParts.difference(parts);
  Set<PRef<GDBData> > insertSet = parts.difference(myParts);
  long i;
  for(i=0; i<removeSet.count(); i++) {
    removeSet.getElement(i)->myPartOf.removeElement(PRef<GDBData>(*this));
    removeSet.getElement(i)->markChanged();
    markChanged();
  }
  for(i=0; i<insertSet.count(); i++) {
    insertSet.getElement(i)->myPartOf.insertElement(PRef<GDBData>(*this));
    insertSet.getElement(i)->markChanged();
    markChanged();
  }
  myParts = parts;
  markChanged();
}

const Set<PRef<GDBData> >& GDBData::getParts() const {
  return myParts;
}

const Set<PRef<GDBData> >& GDBData::getPartOf() const {
  return myPartOf;
}

const Set<PRef<GDBData> >& GDBData::getNextVersion() const {
  return myNextVersion;
}

//void GDBData::setPartOf(GDBData* obj){
//  PRef<GDBData> aRef(*obj);
//  if (myPartOf.isElement(aRef)) return;
//  myPartOf.insertElement(aRef);
//}

void GDBData::setPreviousVersion(GDBData* obj) {
  myPreviousVersion = PRef<GDBData>(*obj);
  markChanged();
}

//void GDBData::setNextVersion(GDBData* obj) {
//  PRef<GDBData> aRef(*obj);
//  if (myNextVersion.isElement(aRef)) return;
//  myNextVersion.insertElement(aRef);
//}

PRef<GDBData> GDBData::getPreviousVersion() const {
  return myPreviousVersion;
}

GDBData* GDBData::newVersion() {
  GDBData* gdbData = new GDBData(this->getDataBase(), this->getName());
  gdbData->setType(this->getType());
  gdbData->setFormat(this->getFormat());
  myNextVersion.insertElement(PRef<GDBData>(*gdbData));
  gdbData->setPreviousVersion(this);
  markChanged();
  return gdbData;
}

PRef<GDBData> GDBData::getSource() const {
  return mySource;
}

const Set<PRef<GDBData> >& GDBData::getTarget() const {
  return myTarget;
}
 
GDBOperation* GDBData::getGenerator() const {
  return myGenerator.getPtr();
}

GDBConfiguration GDBData::getGeneratorConfig() const {
  return myGeneratorConfig;
} 

void GDBData::setGenerator(GDBOperation* op) { 
  myGenerator = op;
  markChanged();
}

void GDBData::setGeneratorConfig(const GDBConfiguration& genConfig) {
  myGeneratorConfig = genConfig;
  markChanged();
}
 
void GDBData::setSource(GDBData* source) {
  mySource = source;
  markChanged();
}

void GDBData::addTarget(GDBData* target) {
  myTarget.insertElement(PRef<GDBData>(target));
}

void GDBData::setData(const RCString& newData) {
  if (myData != newData) {  // has the data really changed?
    if (myStatus & FROZEN) {
      ostrstream os;
      os << "[GDBData::setData] set failed (data is frozen)";
      Report::recoverable(os);
      return;
    }
    else {
        myData = newData;
        myStatus |= CHANGED;
        markChanged();
    }
    for (long i=0; i<myPartOf.count(); i++) {
        myPartOf.getElement(i)->setStatus(UPDATE_REQUIERED);
    }
  }
}

RCString GDBData::getData() const {
  return myData;
}

void GDBData::setBinaryData(PBinary* pbinary) {
  if (myBinaryData.getPOId() != POID_NULL && myBinaryData.getPOId() != pbinary->getPOId()) {
    ostrstream os;
    os << "[GDBData::setBinaryData] set new BinaryData failed (BinaryData allready exists)";
    Report::recoverable(os);
  } 
  else {
    myBinaryData = *pbinary;
    markChanged();
  }
}

PBinary* GDBData::getBinaryData() {
  return myBinaryData.getPtr();
}

void GDBData::marshal(Marshal* aMarshal) {
  *aMarshal << *this;
}

void GDBData::unmarshal(Marshal* aMarshal) {
  *aMarshal >> *this;
}

Marshal& operator<<(Marshal& m, GDBData& obj) {
  m << (unsigned int) obj.myStatus;
  m << obj.myName;
  m << obj.myKeywords;
  m << obj.myType;
  m << obj.myFormat;
  m << obj.myDescription;
  m << obj.myIcon;
  m << obj.myParts;
  m << obj.myPartOf;
  m << obj.myPreviousVersion;
  m << obj.myNextVersion;
  m << obj.mySource;
  m << obj.myGenerator;
  m << obj.myGeneratorConfig;
  m << obj.myTarget;
  m << obj.myData;
  m << obj.myBinaryData;
  return m;
}

Marshal& operator>>(Marshal& m, GDBData& obj) {
  unsigned int dummy;
  m  >> dummy;
  obj.myStatus = dummy;
  m  >> obj.myName;
  m  >> obj.myKeywords;
  m  >> obj.myType;
  m  >> obj.myFormat;
  m  >> obj.myDescription;
  m  >> obj.myIcon;
  m  >> obj.myParts;
  m  >> obj.myPartOf;
  m  >> obj.myPreviousVersion;
  m  >> obj.myNextVersion;
  m  >> obj.mySource;
  m  >> obj.myGenerator;
  m  >> obj.myGeneratorConfig;
  m  >> obj.myTarget;
  m  >> obj.myData;
  m  >> obj.myBinaryData;
  return m;
}
