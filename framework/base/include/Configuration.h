/*
 * Configuration.h
 *
 * Unique pool for options. A option is set as a RCString pair. The first
 * String specifies the name of the option, the second String defines the
 * value of the option. The option String gets translated into an Option
 * by a Chain of Responsability Pattern (Design Patterns, 223). The Chain
 * can be extended by adding ConfigurationHandlers to the Configuration.
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
 *  $Id: Configuration.h,v 1.7 1997/09/19 07:14:02 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _Configuration_H
#define _Configuration_H

#include "booga/base/StaticInit.h"
#include "booga/base/SymTable.h"
#include "booga/base/List.h"
#include "booga/base/RCString.h"
#include "booga/base/Name.h"

class ConfigurationHandler;
class Option;

//________________________________________________________________ Configuration

class Configuration {
public:
  static void addHandler(ConfigurationHandler* handler);
  // Prepend a new ConfigurationHandler. Last come, first serve!

  static int setOption(const RCString& name, const RCString& option);
  static int setOption(const Name& name, const Name& option);
  static const Option* getOption(const RCString& name);
  static const Option* getOption(const Name& name);
  // set/get Options. Option* is built by ConfigurationHandler's from 
  // RCString option.

private:
  static SymTable<Name, Option*>* ourOptions;
  static List<ConfigurationHandler*>* ourHandlers;

public:
  static void initClass();

private:
  Configuration();
  // Make constructor private --> no instance may be created
};

declareInitStatics(Configuration);

#define getConfigurationOption(type,varName,option)                 \
  type* varName = NULL;                                             \
  {                                                                 \
    Option* _option = const_cast(Option, Configuration::getOption(Name(option))); \
    if (_option != NULL)                                            \
      varName = dynamic_cast(type, _option);                        \
  }

#endif // _Configuration_H
