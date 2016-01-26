/*
 * CTOperationDescription.C
 *
 * Copyright (C) 1994-96, Thomas Wenger <wenger@iam.unibe.ch>
 *                        Thomas von Siebenthal <siebenth@iam.unibe.ch>
 *                        University of Berne, Switzerland
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
 *  $Id: CTOperationDescription.C,v 1.10 1996/10/30 15:31:26 amann Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "CTOperationDescription.h"
#include "CTOperationDescriptionAttr.h"

//_______________________________________________________ CTOperationDescription

implementRTTI(CTOperationDescription, Makeable);

CTOperationDescription::CTOperationDescription () {
  myName = "";
  myReturnType = "";
  myIsAbstract = false;
};

CTOperationDescription::CTOperationDescription (Exemplar) {
  myName = "";
  myReturnType = "";
  myIsAbstract = false;
};

const RCString& CTOperationDescription::getName() const {
  return myName;
};

void CTOperationDescription::setName(const RCString& Name) {
  myName = Name;
};
  
const RCString& CTOperationDescription::getReturnType() const {
  return myReturnType;
};

void CTOperationDescription::setReturnType(const RCString& ReturnType) {
  myReturnType = ReturnType;
};
  
// Treatment of the private Parameter List by public methods
long CTOperationDescription::getParameterIndexMin() 
{ 
  return 0; 
};

long CTOperationDescription::getParameterIndexMax() 
{
  return (myParameters.count() - 1);
};

long CTOperationDescription::getParameterIndexFromName(const RCString& Name)
{
  long result = (getParameterIndexMin() - 1);
  for (long i = getParameterIndexMin(); i <= getParameterIndexMax() ; i++)
  {
    if (myParameters.item(i).getName() == Name)
    {
      result = i;
      break;
    };
  };
  return result;
};

const CTVariableDescription& CTOperationDescription::getParameterByIndex(long Index)
{
  return myParameters.item(Index);
};

const CTVariableDescription& CTOperationDescription::getParameterByName(const RCString& Name)
{
  long result;
  result = getParameterIndexFromName(Name);
  return getParameterByIndex(result); 
};

void CTOperationDescription::addParameter(const CTVariableDescription& Parameter)
{
  myParameters.append(Parameter);
};

void CTOperationDescription::delParameterByIndex(long Index)
{
  myParameters.remove(Index);
};

void CTOperationDescription::delParameterByName(const RCString& Name)
{
  long result;
  result = getParameterIndexFromName(Name);
  if ((result >= getParameterIndexMin()) || (result <= getParameterIndexMax())) {
    myParameters.remove(result);
    }; 
};

CTOperationDescription::CTEView CTOperationDescription::getView() {
  return myView;
};

void CTOperationDescription::setView(const CTEView& View) {
  myView = View;
};

void CTOperationDescription::emptyParameterList()
{
  myParameters.removeAll();
};

bool CTOperationDescription::getIsAbstract () {
  return myIsAbstract;
};

void CTOperationDescription::setIsAbstract(bool IsAbstract) {
  myIsAbstract = IsAbstract;
};

Makeable* CTOperationDescription::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(3);
  getParameter(1, RCString, view);
  if (view != "public" && view != "protected" && view != "private") {
    errMsg = "illegal view specified. Allowed views are: public, protected, private";
    return NULL;
  }
  
  getParameter(2, RCString, type);
  getParameter(3, RCString, name);
  if (name.isEmpty()) {
    errMsg = "empty name";
    return NULL;
  }

  CTOperationDescription* newOperation = new CTOperationDescription(*this);
  if (view == "public")
    newOperation->setView(CTOperationDescription::Public);
  else if (view == "protected")
    newOperation->setView(CTOperationDescription::Protected);
  else if (view == "private")
    newOperation->setView(CTOperationDescription::Private);
  else 
    newOperation->setView(CTOperationDescription::Unspecified);
  newOperation->setReturnType(type);
  newOperation->setName(name);

  return newOperation;
};

int CTOperationDescription::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  CTOperationDescriptionAttr* attr = dynamic_cast<CTOperationDescriptionAttr*>(specifier);
  if (attr != NULL) {
    // The CTClassDescription2DAttr object knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute(this);

    delete attr;
    return 1;  
  }

  // 
  // Let papa do the rest ...
  //
  return Makeable::setSpecifier(errMsg, specifier);
}
