/*
 * $RCSfile: PExtra.C 
 *
 * Copyright (C) 1996, Andrey Collison <collison@iam.unibe.ch>
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
 * -----------------------------------------------------------------------------
 *  $Id: PExtra.C,v 1.7 1996/12/06 16:46:29 collison Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "PExtra.h"
#include "booga/base/RCString.h"
#include "Marshal.h"

Marshal& operator<<(Marshal& aDB, const RCString& s) {
  aDB << s.chars();
  return aDB;
}

Marshal& operator>>(Marshal& aDB, RCString& s) {
  char *str = NULL;
  aDB >> str;       // allocates memory for string beeing read
  s = RCString(str);
  delete str;       // don't forget to free the memory
  return aDB;
}
