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
 *  $Id: PExtra.C,v 1.3 1997/02/20 09:31:25 collison Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/persistence/PExtra.h"
#include "booga/base/RCString.h"
#include "booga/base/Value.h"
#include "booga/persistence/Marshal.h"

Marshal& operator<<(Marshal& m, const RCString& s) {
  m << s.chars();
  return m;
}

Marshal& operator>>(Marshal& m, RCString& s) {
  char *str = NULL;
  m >> str;       // allocates memory for string beeing read
  s = RCString(str);
  delete str;       // don't forget to free the memory
  return m;
}

Marshal& operator<<(Marshal& m, const Value& v) {
  m << (RCString) v;
  return m;
}

Marshal& operator>>(Marshal& m, Value& v) {
  char *str = NULL;
  m >> str;
  RCString s = RCString(str);
  v = s;
  return m;
}
