/*
 * $RCSfile: VRMLParser.h,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
 *                        University of Berne, Switzerland
 *
 * Adapted to VRML by  Beat M. Liechti <liechti@isbe.ch>
 *                     Ingenieurschule Bern, Switzerland
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
 *  $Id: VRMLParser.h,v 1.2 1996/08/01 12:01:36 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _VRMLParser_H
#define _VRMLParser_H

#include <stdio.h>
#include "booga/base/PrimitiveTypes.h"
#include "booga/base/RCString.h"
#include "booga/object/World3D.h"
#include "booga/component/Operation3D.h"

//___________________________________________________________________ VRMLParser

class VRMLParserImpl;

class VRMLParser : public Operation3D {
declareRTTI(VRMLParser);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  VRMLParser();

private:
  VRMLParser(const VRMLParser&);            // No copies.

public:
  ~VRMLParser();
  
private:
  VRMLParser& operator=(const VRMLParser&); // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLParser
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setFilename(const RCString& filename);
  void adoptFile(FILE* input);
  // Set the input stream to use by the parser.
private:
  int parse(World3D* world3D, FILE* input = stdin); 
  void debugScanner(bool enable = true);
  void debugParser(bool enable = true);
  // Enable/disable debugging output for the Scanner 
  // (lexical analyzer) or the parser, repectively.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool doExecute();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  VRMLParserImpl* myParser;
  FILE* myInput;
};

#endif // _VRMLParser_H
