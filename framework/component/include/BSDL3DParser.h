/*
 * $RCSfile: BSDL3DParser.h,v $
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: BSDL3DParser.h,v 1.6 1996/08/01 11:59:01 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _BSDL3DParser_H
#define _BSDL3DParser_H

#include <stdio.h> // FILE*
#include "booga/base/RCString.h"
#include "booga/component/Operation3D.h"
#include "booga/component/BSDLParser.h"

//_________________________________________________________________ BSDL3DParser

class BSDL3DParser : public Operation3D {
declareRTTI(BSDL3DParser);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  BSDL3DParser();
private:
  BSDL3DParser(const BSDL3DParser&);            // No copies.

public:
  virtual ~BSDL3DParser();

private:
  BSDL3DParser& operator=(const BSDL3DParser&); // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class BSDL3DParser
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setFilename(const RCString& filename);
  void adoptFile(FILE* input);
  // Set the input stream to use by the parser.

  void setCppParameters(const RCString& cppParameters);
  void addCppParameters(const RCString& cppParameters);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool doExecute();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  FILE* myInput;
  RCString myCppParameters;
};

//______________________________________________________________________ INLINES

inline void BSDL3DParser::setCppParameters(const RCString& cppParameters)
{
  myCppParameters = cppParameters;
}

inline void BSDL3DParser::addCppParameters(const RCString& cppParameters)
{
  myCppParameters += " " + cppParameters;
}

#endif // _BSDL3DParser_H
