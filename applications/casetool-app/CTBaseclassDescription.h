/*
 * CTBaseclassDescription.h
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
 *  $Id: CTBaseclassDescription.h,v 1.7 1996/10/30 15:31:17 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _CTBaseclassDescription_H
#define _CTBaseclassDescription_H

#include "booga/base/RCString.h"

class CTClassDescription2D;

//_______________________________________________________ CTBaseclassDescription

class CTBaseclassDescription {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  CTBaseclassDescription();
private:
  // CTBaseclassDescription(const CTBaseclassDescription&);
                                               // Use default version.
public:
  // virtual CTBaseclassDescription();         // Use default version.

private:
  // CTBaseclassDescription& operator=(const CTBaseclassDescription&);
                                               // Use default version.

// Enumeration
public:
  enum CTEView { Private, Public, Protected, Unspecified};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class CTBaseclassDescription
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  CTEView getView();
  void setView(CTEView View);

  CTClassDescription2D* getBaseclass();
  void setBaseclass(CTClassDescription2D* baseclass);  
  RCString getName() const;
  void setName(const RCString& baseclass);  


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  CTEView myView;
  CTClassDescription2D* myBaseclass;
  RCString myName;
};

//______________________________________________________________________ INLINES

#endif // _CTBaseclassDescription_H
