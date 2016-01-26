/*
 * Report.C
 *
 * Copyright (C) 1994, Christoph Streit <streit@iam.unibe.ch>
 *                     Stephan Amann <amann@iam.unibe.ch>
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
 * Adapted from Craig Kolbs rayshade.
 *
 * ---------------------------------------------------------------------
 *  $Id: Report.C,v 1.9 1998/01/05 09:50:02 buhlmann Exp $
 * ---------------------------------------------------------------------
 */

#include <stdlib.h>
#include <stdarg.h> // form
#include <sstream>

#include <iostream>

#include "booga/base/RCString.h"
#include "booga/base/Report.h"
#include "booga/base/Configuration.h"
#include "booga/base/StreamOption.h"


//___________________________________________________________________ Report

std::ostream* Report::ourErrorStream = NULL;
int Report::ourVerboseFlag = 1;
int Report::ourDebugFlag   = 1;

void Report::debug(const RCString& msg)
{
  if (ourErrorStream == NULL)
    setErrorStream();

  if (ourDebugFlag)
    *ourErrorStream << "Debug message: " << msg << ".\n" << std::flush;
}

void Report::hint(const RCString& msg)
{
  if (ourErrorStream == NULL)
    setErrorStream();

  if (ourVerboseFlag) 
    *ourErrorStream << "Hint: " << msg << ".\n" << std::flush;
}

void Report::warning(const RCString& msg)
{
  if (ourErrorStream == NULL)
    setErrorStream();

  if (ourDebugFlag)  
    *ourErrorStream << "Warning: " << msg << ".\n" << std::flush;
}

void Report::recoverable(const RCString& msg)
{ 
  if (ourErrorStream == NULL)
    setErrorStream();

  *ourErrorStream << "Recoverable Error: " << msg << "!\n" << std::flush;
}

void Report::error(const RCString& msg)
{
  if (ourErrorStream == NULL)
    setErrorStream();

  *ourErrorStream << "Fatal Error: " << msg << "!\n" << std::flush;
  exit(1);
}

void Report::setVerbose(int verboseFlag)
{
  ourVerboseFlag = verboseFlag;
}

void Report::setDebug(int debugFlag)
{
  ourDebugFlag = debugFlag;
}

void Report::setErrorStream()
{
  getConfigurationOption(StreamOption, strOption, "Report.ErrorStream");

  if (strOption != NULL)
    ourErrorStream = (std::ostream *)strOption->getStream();

  if (ourErrorStream == NULL)
    ourErrorStream = &(std::cerr);
}
