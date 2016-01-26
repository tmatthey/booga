/*
 * StatisticConfigurationHandler.h
 *
 * Copyright (C) 1995, Stephan Amann <amann@iam.unibe.ch>
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
 */

#ifndef _StatisticConfigurationHandler_H
#define _StatisticConfigurationHandler_H

#include <fstream.h>
#include "booga/base/StreamOption.h"
#include "booga/base/ValueOption.h"
#include "booga/base/ConfigurationHandler.h"
#include "booga/base/StaticInit.h"

//________________________________________________ StatisticConfigurationHandler

class StatisticConfigurationHandler : public ConfigurationHandler {
public:
  virtual Option* handleOption(const Name& name, const Name& option);
  // Report sends warnings and error messages to a configurable output stream.

protected:
  virtual Option* handleOptionOutputStream(const Name& option);
  // Option OutputStream declares to which output stream reports should be sent.
  virtual Option* handleOptionOutputStreamFilename(const Name& option);
  // Set filename for option/value pair 'OutputStream file'.

private:
  static const Name OPTIONOutputStream_;
  static const Name VALUEOutputStream_cerr_;
  static const Name VALUEOutputStream_cout_;
  static const Name VALUEOutputStream_file_;
  static const Name OPTIONOutputStreamFilename_;

public:
  static void initClass();
  // enable initialization of static members
};

//_________________ ensure initialization of class StatisticConfigurationHandler

declareInitStatics(StatisticConfigurationHandler);

#endif // _StatisticConfigurationHandler_H
