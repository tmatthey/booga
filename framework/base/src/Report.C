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
#ifdef WIN32
#include <stdarg.h> // form
#include <strstream.h>
#endif

#include <iostream.h>

#include "booga/base/RCString.h"
#include "booga/base/Report.h"
#include "booga/base/Configuration.h"
#include "booga/base/StreamOption.h"

//___________________________________________________________________ Report

ostream* Report::ourErrorStream = NULL;
int Report::ourVerboseFlag = 1;
int Report::ourDebugFlag   = 1;

void Report::debug(const RCString& msg)
{
  if (ourErrorStream == NULL)
    setErrorStream();

  if (ourDebugFlag)
    *ourErrorStream << "Debug message: " << msg << ".\n" << flush;
}

void Report::hint(const RCString& msg)
{
  if (ourErrorStream == NULL)
    setErrorStream();

  if (ourVerboseFlag) 
    *ourErrorStream << "Hint: " << msg << ".\n" << flush;
}

void Report::warning(const RCString& msg)
{
  if (ourErrorStream == NULL)
    setErrorStream();

  if (ourDebugFlag)  
    *ourErrorStream << "Warning: " << msg << ".\n" << flush;
}

void Report::recoverable(const RCString& msg)
{ 
  if (ourErrorStream == NULL)
    setErrorStream();

  *ourErrorStream << "Recoverable Error: " << msg << "!\n" << flush;
}

void Report::error(const RCString& msg)
{
  if (ourErrorStream == NULL)
    setErrorStream();

  *ourErrorStream << "Fatal Error: " << msg << "!\n" << flush;
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
    ourErrorStream = (ostream *)strOption->getStream();

  if (ourErrorStream == NULL)
    ourErrorStream = &cerr;
}

#ifdef WIN32
#include <string.h>
static int pos = 0;
char* form(const char* format...)
{
  static const int count = 4096;
  static char buffer[count];
  
  va_list ap;
  va_start(ap, format);
  _vsnprintf(&buffer[pos], 4096-pos, format, ap);

//  vsprintf (&buffer[pos], format, ap);
  char *retval = &buffer[pos];
  pos += strlen(&buffer[pos]) + 1;
  if (pos > 4000)
  pos = 0;
  va_end(ap);
  return retval;
}
#endif
