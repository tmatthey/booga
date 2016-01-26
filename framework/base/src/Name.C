/*
 * Name.C
 *
 * Copyright (C) 1994, Christoph Streit <streit@iam.unibe.ch>
 *                     Stephan Amann <amann@iam.unibe.ch>
 *                     University of Berne, Switzerland
 * Portions Copyright (C) 1990, Jonathan P. Leech
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
 *  $Id: Name.C,v 1.4 1996/02/29 09:58:50 amann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Name.h"
#include <cstring>

//_________________________________________________________________________ Name

implementInitStatics(Name);

List<RCString>* Name::ourGlobalNameSpace = NULL;
SymTable<RCString, long>* Name::ourIndexTable = NULL;
long Name::ourNextIndex;

void Name::initClass()
{
  if (Name::ourGlobalNameSpace == NULL)
  {
    Name::ourGlobalNameSpace = new List<RCString>(1000);
    Name::ourIndexTable = new SymTable<RCString, long>(503);
    Name::ourNextIndex = 0;
  }
}

Name::Name(const char* name)
{
  myIndex = addName(RCString(name));
}

Name::Name(const RCString& name)
{
  myIndex = addName(name.chars());
}

Name::Name(const std::stringstream& os)
{
  myIndex = addName(RCString(const_cast<const char*>(os.str().c_str())));
}

Name& Name::operator=(const char* name)
{
  myIndex = addName(RCString(name));
  return *this;
}

Name& Name::operator=(const RCString& name)
{
  myIndex = addName(name);
  return *this;
}

Name::operator RCString() const
{
  return ourGlobalNameSpace->item(myIndex);
}

long Name::addName(const RCString& newName)
{
  long index = -1;
  
  //
  // If the string 'newName' is already stored in the global name space,
  // just return the index of the stored string. Otherwise add 'newName' to
  // our name space and associate it with the current value of ourNextIndex.
  //
  if (ourIndexTable ==  NULL)
    Name::initClass();
    
  if (!ourIndexTable->lookup(newName, index)) {
    index = ourNextIndex++;
    ourGlobalNameSpace->append(newName);
    ourIndexTable->insert(newName, index);
  }

  return index;
}

long Name::count() 
{ 
  //
  // Alternative: return ourGlobalNameSpace->count();
  //
  return ourNextIndex;
}

void Name::printNames(std::ostream& os)
{
  for (register long i=0; i<ourGlobalNameSpace->count(); i++)
    os << "[" << i << "]\t\"" << ourGlobalNameSpace->item(i) << "\"\n";
}

std::ostream& operator<<(std::ostream& os, const Name& name)
{
  return os << (RCString) name;
}

