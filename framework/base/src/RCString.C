/*
 * $RCSfile: RCString.C,v $
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
 * -----------------------------------------------------------------------------
 *  $Id: RCString.C,v 1.13 1996/08/30 13:53:45 streit Exp $
 * -----------------------------------------------------------------------------
 */


#include <string.h>
#include <iostream>
#include <sstream>
#include "booga/base/RCString.h"
#include "booga/base/Report.h"

/*__________________________________________________________________ RCStringRep
 *  Representation (shared implementation) for reference counted 
 *  string class
 */

class RCStringRep : public RCLetter {
friend class RCString;

private:
  RCStringRep(char c);
  RCStringRep(const char* s);
  RCStringRep(char** r);  // Coplien, Advanced C++, p. 64

  virtual ~RCStringRep();

  virtual RCLetter* rcCopy() const; 
  // abstract method in base class RCLetter
  
private:
  char* myStr;
  int   myLen;
};

inline RCStringRep::RCStringRep(char c) 
{
  myStr = new char[2]; myStr[0] = c; myStr[1] = '\0'; 
  myLen = 1;
}

inline RCStringRep::RCStringRep(const char* s) 
{
  if (s == NULL) {
    // NULL pointer provided ...
    myLen = 0;
    myStr = new char[1];
    myStr[0] = '\0';
  }
  else {
    myLen = strlen(s);
    myStr = new char[myLen+1];
    strcpy(myStr, s);
  }
}

inline RCStringRep::RCStringRep(char** r) 
{ 
  myStr = *r; myLen = strlen(myStr); 
}

inline RCStringRep::~RCStringRep() 
{
  delete [] myStr; 
}

RCLetter* RCStringRep::rcCopy() const
{
  return new RCStringRep(myStr);
}

//_____________________________________________________________________ RCString

implementInitStatics(RCString);

RCString* RCString::ourEmptyString;

void RCString::initClass()
{
  RCString::ourEmptyString = new RCString("");
}

inline RCStringRep* RCString::getLetter()
{
  return (RCStringRep*)myLetter;
}

inline const RCStringRep* RCString::getLetter() const
{
  return (RCStringRep*)myLetter;
}

/*
 * Constructors and destructors
 * ----------------------------
 */

RCString::RCString() 
: RCEnvelope(*ourEmptyString)
{}

RCString::RCString(char c, int num)
: RCEnvelope(*ourEmptyString)
{
  if (num < 0) 
    Report::error("[RCString::RCString(char c, int num)] num <= 0");

  if (num > 0) {
    // remove emptyString
    rcDeref(); 

    char* buf = new char[num + 1];
    memset(buf, c, num);
    buf[num] = '\0';
    
    // call the private constructor
    myLetter = new RCStringRep(&buf); 
  }
}

RCString::RCString(const char* s) 
: RCEnvelope(new RCStringRep(s))
{}

RCString::RCString(std::stringstream& stream) 
: RCEnvelope(*ourEmptyString)
{
  rcDeref();                          // Remove empty string.

  stream << std::ends;                    // Terminate the string
  char* buf = (char *)stream.str().c_str();
  myLetter = new RCStringRep(&buf);   // Call the private constructor.
}

RCString::RCString(char** r) 
: RCEnvelope(new RCStringRep(r))
{}

/*
 * Element extraction 
 * ----------------------------
 */

char& RCString::operator[](int i)
{
  if (i<0 || i>=getLetter()->myLen) {
    std::stringstream os;
    os << "[RCString::operator[] ] index (" << i << ") out of range. "
       << "Valid range is [0, " << getLetter()->myLen << "]";
    Report::recoverable(os);

    static char dummy = ' ';
    return dummy;
  }

  rcMakeUnique(); // Copy on write!
  return getLetter()->myStr[i];
}

char RCString::operator[](int i) const
{
  if (i<0 || i>=getLetter()->myLen) {
    std::stringstream os;
    os << "[RCString::operator[] const] index (" << i << ") out of range. "
       << "Valid range is [0, " << getLetter()->myLen << "]";
    Report::recoverable(os);
    return ' ';
  }

  return getLetter()->myStr[i];
}

/*
 * Substring extraction
 * ----------------------------
 */

RCString RCString::operator()(int fromIndex, int toIndex) const
{
  if (toIndex   <  fromIndex || 
      fromIndex < 0 || fromIndex >= getLetter()->myLen   || 
      toIndex   < 0 || toIndex   >= getLetter()->myLen) {
    std::stringstream os;
    os << "[RCString::operator(unsigned, unsigned)] index (" 
       << fromIndex << " or " << toIndex << " ) out of range";
    Report::recoverable(os);
    return *ourEmptyString;
  }

  char* buf = new char[toIndex - fromIndex + 2];
  strncpy(buf, getLetter()->myStr+fromIndex, toIndex - fromIndex + 1);
  buf[toIndex - fromIndex + 1] = '\0';

  return RCString(&buf);  // call the private constructor
}

/*
 * Assignment
 * ----------------------------
 */

RCString& RCString::operator=(char c)
{
  rcDeref();
  myLetter = new RCStringRep(c);

  return *this;
}

RCString& RCString::operator=(const char* s)
{
  if (getLetter()->myStr == s)
    return *this;

  rcDeref();
  myLetter = new RCStringRep(s);

  return *this;
}

RCString& RCString::operator=(const RCString& s)
{
  rcAssign(s);

  return *this;
}

void RCString::operator+=(const char* s)
{
  char* buf = new char[getLetter()->myLen + strlen(s) + 1];
  strcpy(buf, getLetter()->myStr);
  strcat(buf, s);

  rcDeref();
  myLetter = new RCStringRep(&buf);  // call the private constructor
}

void RCString::operator+=(const RCString& s)
{
  char* buf = new char[getLetter()->myLen + s.getLetter()->myLen + 1];
  strcpy(buf, getLetter()->myStr);
  strcat(buf, s.getLetter()->myStr);

  rcDeref();
  myLetter = new RCStringRep(&buf);  // call the private constructor
}

/*
 * Comparison operators
 * ----------------------------
 */

int RCString::operator==(const RCString& s) const 
{ 
  return strcmp(getLetter()->myStr, s.getLetter()->myStr) == 0; 
}

int RCString::operator==(const char* s) const 
{ 
  return strcmp(getLetter()->myStr, s) == 0; 
}

int RCString::operator!=(const RCString& s) const 
{ 
  return strcmp(getLetter()->myStr, s.getLetter()->myStr) != 0; 
}

int RCString::operator!=(const char* s) const 
{ 
  return strcmp(getLetter()->myStr, s) != 0; 
}

int RCString::operator<(const RCString& s) const 
{ 
  return strcmp(getLetter()->myStr, s.getLetter()->myStr) < 0; 
}

int RCString::operator<=(const RCString& s) const 
{ 
  return strcmp(getLetter()->myStr, s.getLetter()->myStr) <= 0; 
}

int RCString::operator>(const RCString& s) const 
{ 
  return strcmp(getLetter()->myStr, s.getLetter()->myStr) > 0; 
}

int RCString::operator>=(const RCString& s) const 
{ 
  return strcmp(getLetter()->myStr, s.getLetter()->myStr) >= 0; 
}

/*
 * Conversion
 * ----------------------------
 */

const char* RCString::chars() const 
{
  return getLetter()->myStr; 
}

/*
 * State reports
 * ----------------------------
 */

int RCString::length() const 
{
  return getLetter()->myLen; 
}

bool RCString::isEmpty() const 
{ 
  return (getLetter()->myLen == 0); 
}

int RCString::find(const RCString& subString) const 
{
  char* string = getLetter()->myStr;
  char* search = subString.getLetter()->myStr;
  int len1 = getLetter()->myLen;
  int len2 = subString.getLetter()->myLen;
  for(int i=0; i<len1-len2; i++) {
    int j=0;
    while(j<len2 && search[j] == string[i+j]) j++;
    if (j == len2) {
      return i;
    }
    else {
      i+=j;
    }
  }
  return -1;
}

List<RCString>* RCString::createTokens(const RCString& delimiters) const
{
  List<RCString>* retval = new List<RCString>;
  int length; char* token;
  
  char* string = getLetter()->myStr; 
  while (*string!='\0') {
    // skip trailing delimiters
    string += strspn(string, delimiters.chars()); 
    // find end of next token
    length = strcspn(string, delimiters.chars());
    // create new token
    token = new char[length+1];
    strncpy(token, string, length);
    token[length] = '\0';
    // append new token to list of tokens
    retval->append(RCString(&token));
    // skip processed token
    string += length;
  }

  return retval;
}

/*
 * Misc
 * ----------------------------
 */

unsigned int RCString::computeHashCode() const
{
  //
  // string hashing after P.J. Weinberger
  //
  unsigned int h = 0;
  unsigned int g;

  for (register char* s = getLetter()->myStr; *s; s++) {
    h = (h<<4) + *s;
    if ((g = h & 0xf0000000)) {
      h = h^(g>>24);
      h = h^g;
    }
  }

  return h;
}

/*
 * Concatenation
 * ----------------------------
 */

RCString operator+(const RCString& x, const char* y)
{
  char* buf = new char[x.length() + strlen(y) + 1];
  strcpy(buf, x.chars());
  strcat(buf, y);

  return RCString(&buf); // call the private constructor
}  

RCString operator+(const char* x, const RCString& y)
{
  char* buf = new char[strlen(x) + y.length() + 1];
  strcpy(buf, x);
  strcat(buf, y.chars());

  return RCString(&buf); // call the private constructor
}  

RCString operator+(const RCString& x, const RCString& y)
{
  char* buf = new char[x.length() + y.length() + 1];
  strcpy(buf, x.chars());
  strcat(buf, y.chars());

  return RCString(&buf); // call the private constructor
}  
  
/*
 * Stream operator
 * ----------------------------
 */

std::ostream& operator<<(std::ostream& os, const RCString& s)
{ 
  return os << s.chars();
}

