/*
 * $RCSfile: RCString.h,v $
 *
 * Reference counted string class.
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
 *                        Igor Metz <metz@iam.unibe.ch>
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
 * ----------------------------------------------------------------------
 *  $Id: RCString.h,v 1.11 1996/08/30 12:52:10 streit Exp $
 * ----------------------------------------------------------------------
 */

#ifndef _RCString_H
#define _RCString_H

#include "booga/base/PrimitiveTypes.h"  // bool
#include "booga/base/StaticInit.h"
#include "booga/base/ReferenceCounting.h"
#include "booga/base/List.h"

//_____________________________________________________________________ RCString

#include <ostream>
class RCStringRep;

class RCString : public RCEnvelope {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  RCString();
  RCString(char c, int num);
  RCString(const char* s);
  RCString(std::stringstream& stream);
private:
  RCString(char** r); // Coplien, Advanced C++, p. 64

public:
  // virtual ~RCString();  // Use default version.

public:
  RCString& operator=(char c);
  RCString& operator=(const char* s);
  RCString& operator=(const RCString& s);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class RCString
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  char& operator[](int i);
  char  operator[](int i) const;
  // Element extraction

  RCString operator()(int fromIndex, int toIndex) const;
  // Substring extraction

  void operator+=(const char* s);
  void operator+=(const RCString& s);

  int operator==(const RCString& s) const;
  int operator==(const char* s)     const;
  int operator!=(const RCString& s) const;
  int operator!=(const char* s)     const;
  int operator< (const RCString& s) const;
  int operator<=(const RCString& s) const;
  int operator> (const RCString& s) const;
  int operator>=(const RCString& s) const;
  
  const char* chars() const;
  // Conversion to const char*
  //
  // This method should not be used for temporary objects as shown in the 
  // following example:
  //
  //    extern foo(const char* s);
  //    String s1, s2;
  //    foo((s1+s2).chars());
  //
  // The temporary object (s1+s2) may be delete before function foo() is 
  // called (see ARM p. 267ff).

  int length() const;
  bool isEmpty() const;
  // State information

  int find(const RCString& subString) const;
  // Search the string 'subString' in the current string.
  // Returns position (>= 0) of first character, if the sub string 
  //             could be found, 
  //         -1 otherwise.

  List<RCString>* createTokens(const RCString& delimiters) const;
  // Create list of tokens delimted by delimiters
  
  unsigned int computeHashCode() const;
  // Compute hash codes for string values

  friend RCString operator+(const RCString& x, const char* y);
  friend RCString operator+(const char* x, const RCString& y);
  friend RCString operator+(const RCString& x, const RCString& y);
  // Concatenation

  friend std::ostream& operator<<(std::ostream& os, const RCString& s);

public:
  static void initClass();
  // do proper initialisation of static members

private:
  RCStringRep* getLetter();
  const RCStringRep* getLetter() const;
  // internal use only!
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  static RCString* ourEmptyString;
};

//______________________________________ ensure initialization of class RCString

declareInitStatics(RCString);

/*________________________________________________________ Interface to SymTable
 * ... make RCString hashable
 */
  
inline unsigned long _keyToHash(const RCString& key)
{ 
  return (unsigned long)key.computeHashCode();
}

#endif  // _RCString_H 


