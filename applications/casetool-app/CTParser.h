
/*
 * CTParser.h
 *
 * Copyright (C) 1994-96, Thomas Wenger <wenger@iam.unibe.ch>
 *                        Thomas von Siebenthal <siebenth@iam.unibe.ch>
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
 *  $Id: CTParser.h,v 1.11 1996/10/30 08:30:23 siebenth Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _CTParser_H
# define _CTParser_H

#include <stdio.h>
#include "booga/base/PrimitiveTypes.h"
#include "booga/object/World2D.h"
#include "booga/component/Operation2D.h"

//___________________________________________________________________ CTParser

class CTParserImpl;

class CTParser : public Operation2D {
declareRTTI(CTParser);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  CTParser();
private:
  CTParser(const CTParser&);            // No copies.

public:
  ~CTParser();
  
private:
  CTParser& operator=(const CTParser&); // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class CTParser
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void debugScanner(bool enable = true);
  void debugParser(bool enable = true);
  // Enable/disable debugging output for the Scanner 
  // (lexical analyzer) or the parser, repectively.
  void verboseOutput(bool enable = true);

  void setFilename(const RCString& filename);
  void adoptFile(FILE* input);
  // Set the input stream to use by the parser.

  void setCppParameters(const RCString& cppParameters);
  void addCppParameters(const RCString& cppParameters);

private:
  bool parse(World2D* world);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool doExecute();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  CTParserImpl* myParser;
  FILE* myInput;
  RCString myCppParameters;
};

// INLINES

inline void CTParser::setCppParameters(const RCString& cppParameters)
{
  myCppParameters = cppParameters;
}

inline void CTParser::addCppParameters(const RCString& cppParameters)
{
  myCppParameters += " " + cppParameters;
}

#endif // _CTParser_H
