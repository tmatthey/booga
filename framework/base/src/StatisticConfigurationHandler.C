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

#include "booga/base/StatisticConfigurationHandler.h"

//________________________________________________ StatisticConfigurationHandler

implementInitStatics(StatisticConfigurationHandler);

const Name StatisticConfigurationHandler::OPTIONOutputStream_("Statistic.OutputStream");
const Name StatisticConfigurationHandler::VALUEOutputStream_cerr_("cerr");
const Name StatisticConfigurationHandler::VALUEOutputStream_cout_("cout");
const Name StatisticConfigurationHandler::VALUEOutputStream_file_("file");
const Name StatisticConfigurationHandler::OPTIONOutputStreamFilename_("Statistic.OutputStream.Filename");

/*
 * Report sends warnings and error messages to a configurable output stream.
 */
Option* StatisticConfigurationHandler::handleOption(const Name& name, const Name& option)
{
  if (name == OPTIONOutputStream_)
    return handleOptionOutputStream(option);
  else if (name == OPTIONOutputStreamFilename_)
    return handleOptionOutputStreamFilename(option);
  else
    return NULL;
}

/*
 * Option OutputStream declares to which output stream reports should be sent.
 */
Option* StatisticConfigurationHandler::handleOptionOutputStream(const Name& option)
{
  if (option == VALUEOutputStream_cerr_) {
    return new StreamOption(&cerr);
  } else if (option == VALUEOutputStream_cout_) {
    return new StreamOption(&cout);
  } else if (option == VALUEOutputStream_file_) {
    // 
    // Get file name using option ErrorStream.Filename. 
    //
    getConfigurationOption(ValueOption,valueOption,"Report.OutputStream.Filename");
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
 * Set filename for option/value pair 'OutputStream file'.
 */
Option* StatisticConfigurationHandler::handleOptionOutputStreamFilename(const Name& option)
{
  return new ValueOption(Value(((const RCString&)option)));
}

void StatisticConfigurationHandler::initClass()
{
  Configuration::addHandler(new StatisticConfigurationHandler);
}
