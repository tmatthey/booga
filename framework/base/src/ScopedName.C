/*
 * ScopedName.C
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: ScopedName.C,v 1.6 1996/04/01 12:54:50 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include "booga/base/ScopedName.h"

//___________________________________________________________________ ScopedName

implementInitStatics(ScopedName);

Name* ScopedName::ourGlobalNS;

ScopedName& ScopedName::operator=(const ScopedName& scopedName)
{
  if (&scopedName == this)
    return *this;

  myNamespace = scopedName.myNamespace;
  myId = scopedName.myId;

  return *this;
}

RCString ScopedName::getScopedName() const
{
  if (myNamespace == *ourGlobalNS)
    return RCString(myId);
  else
    return RCString((RCString)myNamespace + "::" + (RCString)myId);
}

void ScopedName::initClass()
{
  ourGlobalNS = new Name("GLOBAL_NS");
}

std::ostream& operator<<(std::ostream& os, const ScopedName& scopedName)
{
  return os << scopedName.getScopedName();
}
