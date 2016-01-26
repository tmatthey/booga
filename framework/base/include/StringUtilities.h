/*
 * $RCSfile: StringUtilities.h,v $
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
 *  $Id: StringUtilities.h,v 1.2 1996/08/09 14:53:25 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _StringUtilities_H
#define _StringUtilities_H

#include "booga/base/RCString.h"

//______________________________________________________________ StringUtilities

class StringUtilities {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  StringUtilities();                                   // No instances.
  StringUtilities(const StringUtilities&);             // No copies.

private:
  ~StringUtilities();                                  // No destruction.

private:
  StringUtilities& operator=(const StringUtilities&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class StringUtilities
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  static RCString extractPath(const RCString& file);

  friend class _dummy;
  // Avoid warning about private ctor/dtor and no friends.
};

#endif // _StringUtilities_H

