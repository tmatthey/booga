/*
 * CTOperationDescription.h
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
 *  $Id: CTOperationDescription.h,v 1.9 1996/10/30 15:31:28 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _CTOperationDescription_H
#define _CTOperationDescription_H

#include "booga/base/List.h"
#include "booga/base/RCString.h"
#include "booga/object/ObjectSpecifier.h"
#include "CTVariableDescription.h"

//_______________________________________________________ CTOperationDescription

class CTOperationDescription : public Makeable {
declareRTTI(CTOperationDescription);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  CTOperationDescription();
  CTOperationDescription(Exemplar);
private:
  //  CTOperationDescription(const CTOperationDescription&);
                                               // Use default version.
public:
  // virtual ~CTOperationDescription();          // Use default version.

private:
  // CTOperationDescription& operator=(const CTOperationDescription&);
                                               // Use default version.

// Enumeration
public:
  enum CTEView { Private, Public, Protected, Unspecified};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class CTOperationDescription
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  const RCString& getName() const;
  void setName(const RCString& Name);

  const RCString& getReturnType() const;
  void setReturnType(const RCString& ReturnType);
 
  // List Manipulators for Parameter - List
  long getParameterIndexMin();
  long getParameterIndexMax();
  long getParameterIndexFromName(const RCString& Name);
  const CTVariableDescription& getParameterByIndex(long Index);
  const CTVariableDescription& getParameterByName(const RCString& Name);
  void addParameter(const CTVariableDescription& Parameter);
  void delParameterByIndex(long Index);
  void delParameterByName(const RCString& Name);
  void emptyParameterList();
  CTEView getView();
  void setView(const CTEView& View);
  bool getIsAbstract();
  void setIsAbstract(bool IsAbstract);

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
  RCString myReturnType;
  RCString myName;
  List<CTVariableDescription> myParameters;
  CTEView myView;
  bool myIsAbstract;

};

//______________________________________________________________________ INLINES

#endif // _CTOperationDescription_H

