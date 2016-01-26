/*
 * $RCSfile: GDBConfiguration.h,v $
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
 *  $Id: GDBConfiguration.h,v 1.2 1997/02/20 09:30:27 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GDBConfiguration_H
#define _GDBConfiguration_H

#include "booga/base/RCString.h"
#include "booga/base/Value.h"
#include "booga/base/PrimitiveTypes.h"
#include "booga/persistence/SimpleIndex.h"
#include "booga/persistence/PRef.h"

//_____________________________________________________________________ GDBConfiguration

class GDBConfiguration {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GDBConfiguration();
  ~GDBConfiguration();
  GDBConfiguration(const GDBConfiguration&);
  GDBConfiguration& operator=(const GDBConfiguration&);

private:
  

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GDBConfiguration
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setValue(const RCString& name, const Value& value);
  bool getValue(const RCString& name, Value& value) const;
  bool isDefined(const RCString& name);
  
  friend Marshal& operator<<(Marshal& m, GDBConfiguration& obj);
  friend Marshal& operator>>(Marshal& m, GDBConfiguration& obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

private:

  SimpleIndex<RCString,Value> myConfigValues;
};

//______________________________________________________________________ INLINES

#endif // _GDBConfiguration_H

