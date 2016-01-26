/*
 * CTVariableDescription.h
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
 *  $Id: CTVariableDescription.h,v 1.5 1996/08/16 09:16:25 siebenth Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _CTVariableDescription_H
#define _CTVariableDescription_H

#include "booga/base/RCString.h"

//________________________________________________________ CTVariableDescription

class CTVariableDescription {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  CTVariableDescription(); 
  
private:
  // CTVariableDescription(const CTVariableDescription&);   
                                               // Use default version.
public:
  // virtual ~CTVariableDescription();         // Use default version.

private:
  // CTVariableDescription& operator=(const CTVariableDescription&);  
                                               // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class CTVariableDescription
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  const RCString& getName() const;
  void setName(const RCString& Name);

  const RCString& getType() const;
  void setType(const RCString& Type);
   
  const RCString& getInitValue() const;
  void setInitValue(const RCString& InitValue);
 
 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  RCString myName;
  RCString myType;
  RCString myInitValue;
  
};

//______________________________________________________________________ INLINES

#endif // _CTVariableDescription_H

