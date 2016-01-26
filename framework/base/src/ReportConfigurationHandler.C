/*
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

#include "booga/base/ReportConfigurationHandler.h"

//___________________________________________________ ReportConfigurationHandler

implementInitStatics(ReportConfigurationHandler);

const Name ReportConfigurationHandler::OPTIONErrorStream_("Report.ErrorStream");
const Name ReportConfigurationHandler::VALUEErrorStream_cerr_("cerr");
const Name ReportConfigurationHandler::VALUEErrorStream_cout_("cout");
const Name ReportConfigurationHandler::VALUEErrorStream_file_("file");
const Name ReportConfigurationHandler::OPTIONErrorStreamFilename_("Report.ErrorStream.Filename");

/*
 * Report sends warnings and error messages to a configurable output stream.
 */
Option* ReportConfigurationHandler::handleOption(const Name& name, const Name& option)
{
  if (name == OPTIONErrorStream_)
    return handleOptionErrorStream(option);
  else if (name == OPTIONErrorStreamFilename_)
    return handleOptionErrorStreamFilename(option);
  else
    return NULL;
}

/*
 * Option ErrorStream declares to which output stream reports should be sent.
 */
Option* ReportConfigurationHandler::handleOptionErrorStream(const Name& option)
{
  if (option == VALUEErrorStream_cerr_) {
    return new StreamOption(&cerr);
  } else if (option == VALUEErrorStream_cout_) {
    return new StreamOption(&cout);
  } else if (option == VALUEErrorStream_file_) {
    // 
    // Get file name using option ErrorStream.Filename. 
    //
    getConfigurationOption(ValueOption,valueOption,"Report.ErrorStream.Filename");
    if (valueOption == NULL)
      return NULL;
    
    //
    // Build return value. 
    //
    RCString filename;
    if (valueOption->getValue().toRCString(filename))
      return new StreamOption(new ofstream(filename.chars()));
    else
      return NULL;
  } else
    return NULL;
}

/*
 * Set filename for option/value pair 'Errorstream file'.
 */
Option* ReportConfigurationHandler::handleOptionErrorStreamFilename(const Name& option)
{
  return new ValueOption(Value(((const RCString&)option)));
}

void ReportConfigurationHandler::initClass()
{
  Configuration::addHandler(new ReportConfigurationHandler);
}
