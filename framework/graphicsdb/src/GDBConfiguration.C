/*
 * $RCSfile: GDBConfiguration.C,v $
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
 *  $Id: GDBConfiguration.C,v 1.2 1997/02/20 09:30:26 collison Exp $
 * -----------------------------------------------------------------------------
 */

//
// global configuration: name, value 
// component default configuration (component default values overriding global)
// component current configuration (values overiding default config)
// component specific configuration (values used by component for last execute)
//
// look for values in the following order: current, default, global config 
//

#include "booga/persistence/PExtra.h"
#include "booga/graphicsdb/GDBConfiguration.h"

//_____________________________________________________________________ GDBConfiguration

//implementRTTI(GDBConfiguration, Persistent);

GDBConfiguration::GDBConfiguration() :
myConfigValues()
{
}

GDBConfiguration::~GDBConfiguration()
{
}
  
GDBConfiguration::GDBConfiguration(const GDBConfiguration& aConfig) :
myConfigValues(aConfig.myConfigValues)
{
}

GDBConfiguration& GDBConfiguration::operator=(const GDBConfiguration& aConfig) {
  if (this == &aConfig) {
    return *this;
  }
  myConfigValues = aConfig.myConfigValues;
  return *this;
}

void GDBConfiguration::setValue(const RCString& name, const Value& value) {
  if (isDefined(name)) {
    myConfigValues.remove(name);
  }
  myConfigValues.insert(name,value);
}

bool GDBConfiguration::getValue(const RCString& name, Value& value) const {
  return myConfigValues.lookup(name, value);
}

bool GDBConfiguration::isDefined(const RCString& name) {
  Value dummy;
  return myConfigValues.lookup(name, dummy);
}

Marshal& operator<<(Marshal& m, GDBConfiguration& obj) {
  m << obj.myConfigValues;
  return m;
}

Marshal& operator>>(Marshal& m, GDBConfiguration& obj) {
  m >> obj.myConfigValues;
  return m;
}

