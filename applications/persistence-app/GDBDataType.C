/*
 * $RCSfile: GDBDataType.C,v $
 *
 * Copyright (C) 1996, Mister Nobody <nobody@iam.unibe.ch>
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
 *  $Id: GDBDataType.C,v 1.1 1996/12/06 16:44:11 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "GDBData.h"
#include "GDBDataType.h"

#include "PExtra.h"

//_____________________________________________________________________ GDBDataType

implementRTTI(GDBDataType, Persistent);

GDBDataType::GDBDataType(DataBase& aDB, const RCString& name) :
Persistent(aDB),
myName(name),
myBaseType(POID_NULL),
myExtent()
{
}

GDBDataType::GDBDataType(Prototype aPrototype) :
Persistent(aPrototype),
myName(""),
myBaseType(POID_NULL),
myExtent()
{
}

GDBDataType::~GDBDataType() {
}

RCString GDBDataType::getName() {
  return myName;
}

GDBDataType* GDBDataType::getBaseType() {
  return myBaseType.getPtr();
}

void GDBDataType::setBaseType(GDBDataType* theBaseType) {
  myBaseType = theBaseType;
  markChanged();
}

const SimpleIndex<RCString, PRef<GDBData> >& GDBDataType::getExtent() {
  return myExtent;
}

void GDBDataType::addToExtent(GDBData& obj) {
  myExtent.insert(obj.getName(), PRef<GDBData>(obj));
  markChanged();
}

void GDBDataType::removeFromExtent(GDBData& obj) {
  myExtent.remove(obj.getName());
  markChanged();
}

Persistent* GDBDataType::newInstance() {
  return new GDBDataType(aPrototype);
}

int GDBDataType::destroy() {
  return 0;
}

void GDBDataType::marshal(Marshal* aMarshal) {
  *aMarshal << *this;
}

void GDBDataType::unmarshal(Marshal* aMarshal) {
  *aMarshal >> *this;
}

Marshal& operator<<(Marshal& m, GDBDataType& obj) {
  m << obj.myName;
  m << obj.myBaseType;
  m << obj.myExtent;
  return m;
}

Marshal& operator>>(Marshal& m, GDBDataType& obj) {
  m >> obj.myName;
  m >> obj.myBaseType;
  m >> obj.myExtent;
  return m;
}

