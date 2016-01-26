/*
 * $RCSfile: StringUtilities.C,v $ 
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
 *  $Id: StringUtilities.C,v 1.2 1996/08/09 14:53:24 streit Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/base/StringUtilities.h"

//______________________________________________________________ StringUtilities

RCString StringUtilities::extractPath(const RCString& file)
{
  if (!file.isEmpty()) {
    //
    // Search backward for a backward or forward slash
    //
    for (int i=file.length()-1; i>-1; i--) {
      if (file[i] == '/' || file[i] == '\\')
        return RCString(file(0, i));
    }
  }
 
  return RCString();
}
