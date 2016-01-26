/*
 * CTAttributeDescription.h
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
 *  $Id: CTAttributeDescription.h,v 1.7 1996/09/10 13:27:25 siebenth Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _CTAttributeDescription_H
#define _CTAttributeDescription_H

#include "CTVariableDescription.h"
#include "booga/base/PrimitiveTypes.h"

class CTClassDescription2D;
 

//_______________________________________________________ CTAttributeDescription

class CTAttributeDescription : public CTVariableDescription {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  CTAttributeDescription();
private:
  // CTAttributeDescription(const CTAttributeDescription&);
                                               // Use default version.
public:
  // virtual ~CTAttributeDescription();        // Use default version.

private:
  // CTAttributeDescription& operator=(const CTAttributeDescription&);
                                               // Use default version.

// Enumeration
public:
  enum CTEView { Private, Public, Protected, Unspecified};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class CTAttributeDescription
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  CTEView getView();
  void setView(CTEView View);

  CTClassDescription2D*  getAssociation();
  void setAssociation(CTClassDescription2D* Association); 
  
  bool getIsTemplate();
  void setIsTemplate(const bool IsTemplate);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class CTVariableDescription
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
//  const RCString& getName() const;
//  void setName(const RCString& Name);
//  const RCString& getType() const;
//  void setType(const RCString& Type);
//  const RCString& getInitValue() const;
//  void setInitValue(const RCString& InitValue);


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  CTEView myView;
  CTClassDescription2D* myAssociation;
  bool myIsTemplate;
};

//______________________________________________________________________ INLINES

#endif // _AttributeDescription_H

