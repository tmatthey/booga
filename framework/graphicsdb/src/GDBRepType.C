/*
 * $RCSfile: GDBRepType.C,v $
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
 *  $Id: GDBRepType.C,v 1.3 1997/01/15 13:46:10 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/persistence/PExtra.h"
#include "booga/graphicsdb/GDBData.h"
#include "booga/graphicsdb/GDBDataType.h"
#include "booga/graphicsdb/GDBRepType.h"


//_____________________________________________________________________ GDBRepType

implementRTTI(GDBRepType, Persistent);

GDBRepType::GDBRepType(DataBase& aDB, const RCString& name) :
Persistent(aDB),
myName(name),
myExtension(""),
mySuperRep(POID_NULL),
myExtent()
{
}

GDBRepType::GDBRepType(DataBase& aDB, const RCString& name, const RCString& extension) :
Persistent(aDB),
myName(name),
myExtension(extension),
mySuperRep(POID_NULL),
myExtent()
{
}
GDBRepType::GDBRepType(Prototype aPrototype) :
Persistent(aPrototype),
myName(""),
myExtension(""),
mySuperRep(POID_NULL),
myExtent()
{
}

GDBRepType::~GDBRepType() {
}

RCString GDBRepType::getName() const {
  return myName;
}

RCString GDBRepType::getExtension() const {
  return myExtension;
}

void GDBRepType::setSuperRepType(GDBRepType* theSuperRep) {
  mySuperRep = theSuperRep;
  markChanged();
}

GDBRepType* GDBRepType::getSuperRepType() const {
  return mySuperRep.getPtr();
}

const SimpleIndex<RCString, PRef<GDBData> >& GDBRepType::getExtent() {
  return myExtent;
}

void GDBRepType::addToExtent(GDBData& obj) {
  myExtent.insert(obj.getName(), PRef<GDBData>(obj));
  markChanged();
}

void GDBRepType::removeFromExtent(GDBData& obj) {
  myExtent.remove(obj.getName()); // Warning: assumes key is unique!!! 
  markChanged();
}

Persistent* GDBRepType::newInstance() {
  return new GDBRepType(aPrototype);
}

int GDBRepType::destroy() {
  return 0;
}

void GDBRepType::marshal(Marshal* aMarshal) {
  *aMarshal << *this;
}

void GDBRepType::unmarshal(Marshal* aMarshal) {
  *aMarshal >> *this;
}

Marshal& operator<<(Marshal& m, GDBRepType& obj) {
  m << obj.myName;
  m << obj.myExtension;
  m << obj.mySuperRep;
  m << obj.myExtent;
  return m;
}

Marshal& operator>>(Marshal& m, GDBRepType& obj) {
  m >> obj.myName;
  m >> obj.myExtension;
  m >> obj.mySuperRep;
  m >> obj.myExtent;
  return m;
}

