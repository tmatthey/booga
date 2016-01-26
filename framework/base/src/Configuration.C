/*
 * Configuration.C
 *
 * Copyright (C) 1995, Stephan Amann <amann@iam.unibe.ch>
 *                     Christoph Streit <streit@iam.unibe.ch>
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: Configuration.C,v 1.8 1996/03/02 12:23:27 amann Exp $
 * -----------------------------------------------------------------------------
 */

#include <stdlib.h>  // NULL  

#include "booga/base/Report.h" 
#include "booga/base/Configuration.h"
#include "booga/base/ConfigurationHandler.h"

//________________________________________________________________ Configuration

implementInitStatics(Configuration);

const int MAX_CONFIGURATION_ENTRIES = 100;

SymTable<Name, Option*>* Configuration::ourOptions;
List<ConfigurationHandler*>* Configuration::ourHandlers;

void Configuration::addHandler(ConfigurationHandler* handler)
{
  ourHandlers->prepend(handler);
}

int Configuration::setOption(const RCString& name, const RCString& option)
{
  return setOption(Name(name), Name(option));
}

int Configuration::setOption(const Name& name, const Name& option)
{
  Option* resultingOption;
  for (long i=0; i<ourHandlers->count(); i++)
    if ((resultingOption = ourHandlers->item(i)->handleOption(name,option)) != NULL)
      return ourOptions->insert(name,resultingOption);

  Report::warning("[Configuration::setOption] Unknown option \"" + (const RCString)name + "\"");
  return 0;
}

const Option* Configuration::getOption(const Name& name)
{
  Option* option;
  if (!ourOptions->lookup(name, option)) {
    return NULL;
  }

  return option;
}

const Option* Configuration::getOption(const RCString& name)
{
  return getOption(Name(name));
}

void Configuration::initClass()
{
  ourOptions = new SymTable<Name, Option*>(MAX_CONFIGURATION_ENTRIES);
  ourHandlers = new List<ConfigurationHandler*>;
}
