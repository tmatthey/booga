/*
 * $RCSfile: Parser3D.h,v $
 *
 * This component parses 3D scene description in BSDL or VRML 1.0 format.
 * You may specify a filename (setFilename()) to indicate the file to read 
 * from, otherwise the parser will read from stdin. If the filename is of 
 * the form:
 *
 *   directory/.../directory/name.bsdl
 * 
 * the path (directory/.../directory) is automatically extracted and used
 * as a cpp argument (-Idirectory/.../directory) to correctly handle
 * #include's!
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
 *  $Id: Parser3D.h,v 1.2 1996/08/01 12:00:23 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _Parser3D_H
#define _Parser3D_H

#include "booga/base/RCString.h"
#include "booga/component/Operation3D.h"

//_____________________________________________________________________ Parser3D

class Parser3D : public Operation3D {
declareRTTI(Parser3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // Parser3D();                        // Use default version.
private:
  // Parser3D(const Parser3D&);         // Use default version.

public:
  // virtual ~Parser3D();               // Use default version.

private:
  Parser3D& operator=(const Parser3D&); // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Parser3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setFilename(const RCString& filename);
  // Set the input file to be use by the parser.

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
  RCString myFilename;
  RCString myCppParameters;
};

//______________________________________________________________________ INLINES

inline void Parser3D::setCppParameters(const RCString& cppParameters)
{
  myCppParameters = cppParameters;
}

inline void Parser3D::addCppParameters(const RCString& cppParameters)
{
  myCppParameters += cppParameters;
}

#endif // _Parser3D_H
