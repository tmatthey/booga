/*
 * $RCSfile: ParserUtilities.h,v $
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
 *                        University of Berne, Switzerland
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
 *  $Id: ParserUtilities.h,v 1.2 1996/08/09 14:53:15 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ParserUtilities_H
#define _ParserUtilities_H

#include <stdio.h> // FILE
#include "booga/base/RCString.h"

//______________________________________________________________ ParserUtilities

class ParserUtilities {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  ParserUtilities();                                   // No instances.
  ParserUtilities(const ParserUtilities&);             // No copies.

private:
  ~ParserUtilities();                                  // No destruction.

private:
  ParserUtilities& operator=(const ParserUtilities&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class ParserUtilities
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  static FILE* cppopen(FILE* fp, const RCString& cppParameters);
  static int cppclose(FILE* fp);
  //
  // Filter the provided FILE* with the C preprocessor.
  //
  // cppopen() expects a FILE* as its argument, created with fopen(), popen(), etc.
  // Important: The FILE* has to be openend using the read only mode!
  //
  // cppopen() return a new FILE* handle opened in read only mode. When reading
  // from this FILE* the stream is atomatically filtered with the C preprocessor.
  //
  // Overview (Deeeep UNIX!!)
  //
  // parameter ----> | ----> cpp ----> | ----> return value
  //                1 0               1 0
  //         filedescPipe2[2]   filedescPipe1[2]
  //

  friend class _dummy;
  // Avoid warning about private ctor/dtor and no friends.
};

#endif // _ParserUtilities_H

