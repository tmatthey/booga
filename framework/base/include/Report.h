/*
 * Report.h 
 *
 * General message (error, warning, debug) reporting methods.
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
 * ----------------------------------------------------------------------
 *  $Id: Report.h,v 1.7 1998/01/05 09:50:03 buhlmann Exp $
 * ----------------------------------------------------------------------
 */

#ifndef _Report_H
# define _Report_H

class RCString;
#include <ostream>

//___________________________________________________________________ Report

class Report {
public:
  static void debug       (const RCString& msg);
  static void hint        (const RCString& msg);
  static void warning     (const RCString& msg);
  static void recoverable (const RCString& msg);
  static void error       (const RCString& msg);

  static void setVerbose (int verboseFlag = 1);
  static void setDebug   (int debugFlag = 1);

private:
  static std::ostream* ourErrorStream;
  static int ourVerboseFlag;
  static int ourDebugFlag;

private:
  static void setErrorStream();

  Report();  
  // make constructor private -> no instance may be created
};

// This include has to stay here !
#include "booga/base/RCString.h"

#endif // _Report_H
