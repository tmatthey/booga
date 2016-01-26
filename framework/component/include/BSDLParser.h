/*
 * $RCSfile: BSDLParser.h,v $
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
 *  $Id: BSDLParser.h,v 1.3 1996/08/01 11:59:03 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _BSDLParser_H
#define _BSDLParser_H

#include <stdio.h>
#include "booga/base/PrimitiveTypes.h"
#include "booga/object/World.h"

//___________________________________________________________________ BSDLParser

class BSDLParserImpl;

class BSDLParser  {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  BSDLParser();
private:
  BSDLParser(const BSDLParser&);            // No copies.

public:
  ~BSDLParser();
  
private:
  BSDLParser& operator=(const BSDLParser&); // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class BSDLParser
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  int parse(World* world, FILE* input = stdin, 
                          const RCString& cppParameter = RCString());

  void debugScanner(bool enable = true);
  void debugParser(bool enable = true);
  // Enable/disable debugging output for the Scanner 
  // (lexical analyzer) or the parser, repectively.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  BSDLParserImpl* myParser;
};

// -----------------------------------------------------------------------------
// Macros to simplify registration of parseable objects ...

// eg. registerParserNamespace("3D");
#define registerParserNamespace(ns)                        \
  if (!Makeable::createNamespace(Name(ns)))	              \
    Report::error("namespace creation failed: " +(RCString)ns)
// eg. unregisterParserNamespace("3D");
#define unregisterParserNamespace(ns)                   \
  if (!Makeable::removeNamespace(Name(ns)))	           \
    Report::error("namespace deletion failed: " +(RCString)ns)

// eg. registerParserExemplar("3D", transform, Transform);
#define registerParserExemplar(ns, specName, specType)                  \
{					                           \
  registerParserNamespace((RCString)ns + "::" #specName);               \
  RCString errMsg;			                           \
  if (!Makeable::registerExemplar(errMsg,                               \
				  ScopedName(Name(ns), #specName),  \
				  new specType(anExemplar)))        \
    Report::error("prototype registration failed: " + errMsg);          \
}
// eg. unregisterParserExemplar("3D", transform);
#define unregisterParserExemplar(ns, specName)                          \
{					                           \
  Makeable* anExemplar;                                                 \
  if (!Makeable::removeNamespace(Name((RCString)ns + "::" #specName)))  \
    Report::error("namespace deletion failed: " +(RCString)ns);         \
  RCString errMsg;			                           \
  if (!Makeable::unregisterExemplar(errMsg,                             \
				  ScopedName(Name(ns), #specName),  \
				  anExemplar))                      \
    Report::error("prototype deletion failed: " + errMsg);              \
  else			                                             \
    delete anExemplar;	                                             \
}

// eg. registerParserAttribute("3D", scale, transform, TransformAttrScale);
#define registerParserAttribute(ns, attrName, specName, attrType)       \
{						                  \
  RCString errMsg;				                  \
  if (!Makeable::registerExemplar(errMsg, 	                           \
                    ScopedName(Name((RCString)ns + "::" #specName),     \
                               #attrName),                              \
                    new attrType(anExemplar)))                          \
    Report::error("prototype registration failed: " + errMsg);          \
}
// eg. unregisterParserAttribute("3D", scale, transform);
#define unregisterParserAttribute(ns, attrName, specName)               \
{						                  \
  Makeable* anExemplar;                                                 \
  RCString errMsg;				                  \
  if (!Makeable::unregisterExemplar(errMsg, 	                           \
                      ScopedName(Name((RCString)ns + "::" #specName),   \
                                 #attrName),                            \
                      anExemplar))                                      \
    Report::error("prototype deletion failed: " + errMsg);              \
  else			                                             \
    delete anExemplar;	                                             \
}

#endif // _BSDLParser_H
