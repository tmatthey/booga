/*
 * ScopedName.h
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
 *  $Id: ScopedName.h,v 1.6 1996/04/01 12:54:51 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ScopedName_H
#define _ScopedName_H

#include "booga/base/Name.h"
#include "booga/base/StaticInit.h"

class ostream;

//___________________________________________________________________ ScopedName
 
class ScopedName {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  ScopedName(const RCString& id);
  ScopedName(const Name& id);
  ScopedName(const Name& theNamespace, const Name& id);

public:
  // ~ScopedName();  // Use default version.

public:
  ScopedName& operator=(const ScopedName& scopedName);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class ScopedName
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  RCString getScopedName() const;
  const Name& getNamespace() const;
  const Name& getIdentifier() const;

  static const Name& getGlobalNS();

  friend ostream& operator<<(ostream& os, const ScopedName& scopedName);

public:
  static void initClass();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  static Name* ourGlobalNS;
  // The name of the global namespace.

private:
  Name myNamespace;
  Name myId;
};

declareInitStatics(ScopedName);

//______________________________________________________________________ INLINES

inline ScopedName::ScopedName(const Name& theNamespace, const Name& id)
: myNamespace(theNamespace), myId(id)
{}

inline ScopedName::ScopedName(const RCString& id)
: myNamespace(*ourGlobalNS), myId(id)
{}

inline ScopedName::ScopedName(const Name& id)
: myNamespace(*ourGlobalNS), myId(id)
{}

inline const Name& ScopedName::getNamespace() const
{
  return myNamespace;
}

inline const Name& ScopedName::getIdentifier() const
{
  return myId;
}

inline const Name& ScopedName::getGlobalNS()
{
  return *ourGlobalNS;
}

#endif // _ScopedName_H
