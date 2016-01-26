/*
 * Name.h 
 *
 * Class for space efficient name storage.
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
 *  $Id: Name.h,v 1.4 1996/02/29 09:58:51 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Name_H
# define _Name_H

#include <iostream>
#include "booga/base/StaticInit.h"
#include "booga/base/RCString.h"
#include "booga/base/SymTable.h"
#include "booga/base/List.h"

//_________________________________________________________________________ Name

class Name {
public:
  Name(const char* name = "");
  Name(const RCString& name);
  Name(const std::stringstream& os);

  Name& operator=(const char* name);
  Name& operator=(const RCString& name);
  Name& operator=(const Name& name);

  int operator==(const Name& anotherName) const;
  int operator!=(const Name& anotherName) const;

  long getIndex() const;
  operator RCString() const;

  friend std::ostream& operator<<(std::ostream& os, const Name& name);

public:
  static long addName(const RCString& newName);
  // Add a name to the global name space, i.e. associate an index with the
  // string 'newName' and insert it in the name space (if it is not already
  // known).

  static long count();
  // Return the number of names stored in the global name space.

  static void printNames(std::ostream& os = std::cout);
  // Print the names in the global name space to 'os'

protected:
  long myIndex;  // The index associated with the name.

public:
  static void initClass(); 
  // do proper initialisation of static members

private:
  static List<RCString>* ourGlobalNameSpace; 
  // List of the all the names known to the application, i.e. the strings 
  // used as an argument to one of the constructors, assignment operators or 
  // to the addName method.

  static SymTable<RCString, long>* ourIndexTable;
  // Hashtable for fast lookup of the index value associated with a string.

  static long ourNextIndex;
  // The index to be used for a new (unknown) string value.
};

//__________________________________________ ensure initialization of class Name

declareInitStatics(Name);

//________________________________________________________ Inlines of class Name

inline Name& Name::operator=(const Name& name)
{
  myIndex = name.myIndex;
  return *this;  
}

inline int Name::operator==(const Name& anotherName) const 
{
  return (myIndex == anotherName.myIndex);
}

inline int Name::operator!=(const Name& anotherName) const 
{
  return (myIndex != anotherName.myIndex);
}

inline long Name::getIndex() const 
{ 
  return myIndex; 
}

/*________________________________________________________ Interface to SymTable
 * ... make Name hashable
 */
  
inline unsigned long _keyToHash(const Name& key)
{ 
  return (unsigned long)key.getIndex();
}

#endif // _Name_H
