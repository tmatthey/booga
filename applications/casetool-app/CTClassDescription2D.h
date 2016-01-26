/*
 * CTClassDescription2D.h
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
 *  $Id: CTClassDescription2D.h,v 1.22 1996/10/30 15:31:21 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _CTClassDescription2D_H
#define _CTClassDescription2D_H

#include "booga/object/Primitive2D.h"
#include "booga/base/List.h"
#include "booga/base/PrimitiveTypes.h"
#include "booga/object/List2D.h"
#include "CTAttributeDescription.h"
#include "CTOperationDescription.h"
#include "CTBaseclassDescription.h"

//_________________________________________________________ CTClassDescription2D

class CTClassDescription2D : public Primitive2D {
declareRTTI(CTClassDescription2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  CTClassDescription2D();
  CTClassDescription2D(Exemplar);
  CTClassDescription2D(const CTClassDescription2D&);

public:
  ~CTClassDescription2D();
  
private:
  CTClassDescription2D& operator=(const CTClassDescription2D&);
                                                // use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class CTClassDescription2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  const RCString& getName() const;
  void setName(const RCString& Name);
  const Vector2D& getOrigin() const;
  void setOrigin(const Vector2D& Origin);
  Real getWidth();
  void setWidth(Real Width);
  bool getIsTemplate();
  void setIsTemplate(bool IsTemplate);
  const RCString& getTemplateParameters() const;
  void setTemplateParameters(const RCString& Parameter);
  bool getIsAbstract();
  void setIsAbstract(bool IsAbstract);
  Real getHeight();
  void setHeight(Real Height);

  // List Manipulators for Attribute - List
  long getAttributeIndexMin();
  long getAttributeIndexMax();
  long getAttributeIndexFromName(const RCString& Name);
  const CTAttributeDescription& getAttributeByIndex(long Index);
  const CTAttributeDescription& getAttributeByName(const RCString& Name);
  void addAttribute(const CTAttributeDescription& Attribute);
  void delAttributeByIndex(long Index);
  void delAttributeByName(const RCString& Name);
  void emptyAttributeList();

  // List Manipulators for Operation - List
  long getOperationIndexMin();
  long getOperationIndexMax();
  long getOperationIndexFromName(const RCString& Name);
  const CTOperationDescription& getOperationByIndex(long Index);
  const CTOperationDescription& getOperationByName(const RCString& Name);
  void addOperation(const CTOperationDescription& Operation);
  void delOperationByIndex(long Index);
  void delOperationByName(const RCString& Name);
  void emptyOperationList();

  // List Manipulators for Baseclass - List
  long getBaseclassIndexMin();
  long getBaseclassIndexMax();
  long getBaseclassIndexFromName(const RCString& Name);
  const CTBaseclassDescription& getBaseclassByIndex(long Index);
  const CTBaseclassDescription& getBaseclassByName(const RCString& Name);
  void addBaseclass(const CTBaseclassDescription& Baseclass);
  void delBaseclassByIndex(long Index);
  void delBaseclassByName(const RCString& Name);
  void emptyBaseclassList();

  // Methods to get/adpot Body and Connectors
  void adoptBody(List2D* Body);
  void adoptConnectors(List2D* Connectors);
  List2D* getBody();
  List2D* getConnectors();
  
  // Methods to manage the Dockingpoints:
  List<Vector2D>* getDockingPoints();
          
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Primitive2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object2D* createDecomposition() const;
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object2D* copy() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual void doComputeBounds();
private:
  virtual bool doIntersect(Ray2D& /* ray */);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual Makeable* make(RCString& /* errMsg */ , const List<Value*>* /* parameters */) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Real myWidth;
  Real myHeight;
  Vector2D myOrigin;
  RCString myName;
  bool myIsTemplate;
  RCString myTemplateParameters;
  bool myIsAbstract;
  List2D* myBody;
  List2D* myConnectors;
  List<CTAttributeDescription> myAttributes;
  List<CTOperationDescription> myOperations;
  List<CTBaseclassDescription> myBaseclasses;
  List<Vector2D> myDockingPoints;
};

//______________________________________________________________________ INLINES

#endif // _CTClassDescription2D_H
