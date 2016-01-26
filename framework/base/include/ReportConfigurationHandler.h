/*
 * ReportConfigurationHandler.h
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

#ifndef _ReportConfigurationHandler_H
#define _ReportConfigurationHandler_H

#include <fstream.h>
#include "booga/base/StreamOption.h"
#include "booga/base/ValueOption.h"
#include "booga/base/ConfigurationHandler.h"
#include "booga/base/StaticInit.h"

//___________________________________________________ ReportConfigurationHandler

class ReportConfigurationHandler : public ConfigurationHandler {
public:
  virtual Option* handleOption(const Name& name, const Name& option);
  // Report sends warnings and error messages to a configurable output stream.

protected:
  virtual Option* handleOptionErrorStream(const Name& option);
  // Option ErrorStream declares to which output stream reports should be sent.
  virtual Option* handleOptionErrorStreamFilename(const Name& option);
  // Set filename for option/value pair 'Errorstream file'.

private:
  static const Name OPTIONErrorStream_;
  static const Name VALUEErrorStream_cerr_;
  static const Name VALUEErrorStream_cout_;
  static const Name VALUEErrorStream_file_;
  static const Name OPTIONErrorStreamFilename_;

public:
  static void initClass();
  // enable initialization of static members
};

//____________________ ensure initialization of class ReportConfigurationHandler

declareInitStatics(ReportConfigurationHandler);

#endif // _ReportConfigurationHandler_H
