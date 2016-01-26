/*
 * CTClassDescription2D.C
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
 *  $Id: CTClassDescription2D.C,v 1.26 1996/10/30 15:31:19 amann Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "CTClassDescription2D.h"
#include "CTClassDescription2DAttributes.h"
#include "booga/object/Visitor2D.h"


//_________________________________________________________ CTClassDescription2D

implementRTTI(CTClassDescription2D, Primitive2D);


CTClassDescription2D::CTClassDescription2D () {
  myName = "";
  myWidth = 1;
  myHeight = 0;
  myOrigin = Vector2D(0,0);
  myIsTemplate = false;
  myTemplateParameters = "";
  myIsAbstract = false;
  myBody = new List2D;
  myConnectors = new List2D;
};

CTClassDescription2D::CTClassDescription2D (Exemplar) {
  myName = "";
  myWidth = 1;
  myHeight = 0;
  myOrigin = Vector2D(0,0);
  myIsTemplate = false;
  myTemplateParameters = "";
  myIsAbstract = false;
  myBody = new List2D;
  myConnectors = new List2D;
};

CTClassDescription2D::CTClassDescription2D(const CTClassDescription2D& desc)
: myOrigin(desc.myOrigin), myName(desc.myName), 
  myAttributes(desc.myAttributes),
  myOperations(desc.myOperations),
  myBaseclasses(desc.myBaseclasses)
{
  myWidth = desc.myWidth;
  myHeight = desc.myHeight;
  myIsTemplate = desc.myIsTemplate;
  myTemplateParameters = desc.myTemplateParameters;
  myIsAbstract = desc.myIsAbstract;
  myBody = dynamic_cast(List2D, desc.myBody->copy());
  myConnectors = dynamic_cast(List2D, desc.myConnectors->copy());
};

CTClassDescription2D::~CTClassDescription2D() {
  delete myBody;
  delete myConnectors;
};

const RCString& CTClassDescription2D::getName() const {
  return myName;
};

void CTClassDescription2D::setName(const RCString& Name) {
  myName = Name;
};
 
const Vector2D& CTClassDescription2D::getOrigin() const {
  return myOrigin;
};

void CTClassDescription2D::setOrigin(const Vector2D& Origin) {
  myOrigin = Origin;
};

Real CTClassDescription2D::getWidth() {
  return myWidth;
};

void CTClassDescription2D::setWidth(Real Width) {
  myWidth = Width;
};

Real CTClassDescription2D::getHeight() {
  return myHeight;
};

void CTClassDescription2D::setHeight(Real Height) {
  myHeight = Height;
};

bool CTClassDescription2D::getIsTemplate () {
  return myIsTemplate;
};

void CTClassDescription2D::setIsTemplate (bool IsTemplate) {
  myIsTemplate = IsTemplate;
};

const RCString& CTClassDescription2D::getTemplateParameters() const {
  return myTemplateParameters;
};

void CTClassDescription2D::setTemplateParameters(const RCString& Parameter) {
  myTemplateParameters = Parameter;
  if (Parameter.length() > 0) { 
    myIsTemplate = true;
    };
};

bool CTClassDescription2D::getIsAbstract () {
  return myIsAbstract;
};

void CTClassDescription2D::setIsAbstract(bool IsAbstract) {
  myIsAbstract = IsAbstract;
};

Object2D* CTClassDescription2D::createDecomposition() const
{
  List2D* myDecomposition = new List2D;
  
  myDecomposition->adoptObject(new List2D(*myBody));
  myDecomposition->adoptObject(new List2D(*myConnectors));
   
  return myDecomposition;
};

Object2D* CTClassDescription2D::copy() const
{
  return new CTClassDescription2D(*this);
};

void CTClassDescription2D::doComputeBounds()
{
  // myBounds.expand(0,0);
  myBounds.expand(myOrigin[0], myOrigin[1]);
  myBounds.expand(myOrigin[0] + myWidth, myOrigin[1] + myHeight);
};

bool CTClassDescription2D::doIntersect(Ray2D& /* ray */)
{
  return false;
};

Makeable* CTClassDescription2D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, RCString, name);

  if (name.isEmpty()) {
    errMsg = "empty name";
    return NULL;
  }

  CTClassDescription2D* newClass = new CTClassDescription2D(*this);
  newClass->setName(name);
  
  return newClass;
};


// Treatment of the private Attribute List by public methods
long CTClassDescription2D::getAttributeIndexMin() 
{ 
  return 0; 
};

long CTClassDescription2D::getAttributeIndexMax() 
{
  return (myAttributes.count() - 1);
};

long CTClassDescription2D::getAttributeIndexFromName(const RCString& Name)
{
  long result = (getAttributeIndexMin() - 1);
  for (long i = getAttributeIndexMin(); i <= getAttributeIndexMax() ; i++)
  {
    if (myAttributes.item(i).getName() == Name)
    {
      result = i;
      break;
    };
  };
  return result;
};

const CTAttributeDescription& CTClassDescription2D::getAttributeByIndex(long Index)
{
  return myAttributes.item(Index);
};

const CTAttributeDescription& CTClassDescription2D::getAttributeByName(const RCString& Name)
{
  long result;
  result = getAttributeIndexFromName(Name);
  return getAttributeByIndex(result); 
};

void CTClassDescription2D::addAttribute(const CTAttributeDescription& Attribute)
{
  myAttributes.append(Attribute);
};

void CTClassDescription2D::delAttributeByIndex(long Index)
{
  myAttributes.remove(Index);
};

void CTClassDescription2D::delAttributeByName(const RCString& Name)
{
  long result;
  result = getAttributeIndexFromName(Name);
  if ((result >= getAttributeIndexMin()) || (result <= getAttributeIndexMax())) {
    myAttributes.remove(result);
    }; 
};

void CTClassDescription2D::emptyAttributeList()
{
  myAttributes.removeAll();
};


// Treatment of the private Operation List by public methods
long CTClassDescription2D::getOperationIndexMin() 
{ 
  return 0; 
};

long CTClassDescription2D::getOperationIndexMax() 
{
  return (myOperations.count() - 1);
};

long CTClassDescription2D::getOperationIndexFromName(const RCString& Name)
{
  long result = (getOperationIndexMin() - 1);
  for (long i = getOperationIndexMin(); i <= getOperationIndexMax() ; i++)
  {
    if (myOperations.item(i).getName() == Name)
    {
      result = i;
      break;
    };
  };
  return result;
};

const CTOperationDescription& CTClassDescription2D::getOperationByIndex(long Index)
{
  return myOperations.item(Index);
};

const CTOperationDescription& CTClassDescription2D::getOperationByName(const RCString& Name)
{
  long result;
  result = getOperationIndexFromName(Name);
  return getOperationByIndex(result); 
};

void CTClassDescription2D::addOperation(const CTOperationDescription& Operation)
{
  myOperations.append(Operation);
};

void CTClassDescription2D::delOperationByIndex(long Index)
{
  myOperations.remove(Index);
};

void CTClassDescription2D::delOperationByName(const RCString& Name)
{
  long result;
  result = getOperationIndexFromName(Name);
  if ((result >= getOperationIndexMin()) || (result <= getOperationIndexMax())) {
    myOperations.remove(result);
    }; 
};

void CTClassDescription2D::emptyOperationList()
{
  myOperations.removeAll();
};


// Treatment of the private Baseclass List by public methods
long CTClassDescription2D::getBaseclassIndexMin() 
{ 
  return 0; 
};

long CTClassDescription2D::getBaseclassIndexMax() 
{
  return (myBaseclasses.count() - 1);
};

long CTClassDescription2D::getBaseclassIndexFromName(const RCString& Name)
{
  long result = (getBaseclassIndexMin() - 1);
  for (long i = getBaseclassIndexMin(); i <= getBaseclassIndexMax() ; i++)
  {
    if (myBaseclasses.item(i).getBaseclass()->getName() == Name)
    {
      result = i;
      break;
    };
  };
  return result;
};

const CTBaseclassDescription& CTClassDescription2D::getBaseclassByIndex(long Index)
{
  return myBaseclasses.item(Index);
};

const CTBaseclassDescription& CTClassDescription2D::getBaseclassByName(const RCString& Name)
{
  long result;
  result = getBaseclassIndexFromName(Name);
  return getBaseclassByIndex(result); 
};

void CTClassDescription2D::addBaseclass(const CTBaseclassDescription& Baseclass)
{
  myBaseclasses.append(Baseclass);
};

void CTClassDescription2D::delBaseclassByIndex(long Index)
{
  myBaseclasses.remove(Index);
};

void CTClassDescription2D::delBaseclassByName(const RCString& Name)
{
  long result;
  result = getBaseclassIndexFromName(Name);
  if ((result >= getBaseclassIndexMin()) || (result <= getBaseclassIndexMax())) {
    myBaseclasses.remove(result);
    }; 
};

void CTClassDescription2D::emptyBaseclassList()
{
  myBaseclasses.removeAll();
};

void CTClassDescription2D::adoptBody(List2D* Body)
{
  myBody = Body;
};

void CTClassDescription2D::adoptConnectors(List2D* Connectors)
{
  myConnectors = Connectors;
};

List2D* CTClassDescription2D::getBody()
{
  return myBody;
}
  
List2D* CTClassDescription2D::getConnectors()
{
  return myConnectors;
}

// Methods to manage the Dockingpoints:
List<Vector2D>* CTClassDescription2D::getDockingPoints()
{
  return &myDockingPoints;
}

int CTClassDescription2D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  // Special treatment of CTOperationDescriptions...
  CTOperationDescription* opDesc = dynamic_cast(CTOperationDescription, specifier);
  if (opDesc != NULL) {
    addOperation(*opDesc);
    delete opDesc;
    return 1;  
  }

  CTClassDescription2DAttr* attr = dynamic_cast(CTClassDescription2DAttr, specifier);
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
  return Object2D::setSpecifier(errMsg, specifier);
}
