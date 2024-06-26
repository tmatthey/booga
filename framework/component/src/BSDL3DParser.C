/*
 * $RCSfile: BSDL3DParser.C,v $
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
 *  $Id: BSDL3DParser.C,v 1.12 1996/08/01 11:58:59 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/StringUtilities.h"
#include "booga/object/Object3D.h"
#include "booga/object/Aggregate3D.h"
#include "booga/component/BSDL3DParser.h"

//_________________________________________________________________ BSDL3DParser

implementRTTI(BSDL3DParser, Operation3D);

BSDL3DParser::BSDL3DParser()
: myInput(stdin)
{}

BSDL3DParser::~BSDL3DParser()
{
  if (myInput != stdin && myInput != NULL)
    fclose(myInput);
}

void BSDL3DParser::setFilename(const RCString& filename)
{
  if (filename.isEmpty())
    return;
    
  if (myInput != stdin && myInput != NULL) {
    fclose(myInput);
    myInput = NULL;
  }

  if (!(myInput = fopen(filename.chars(), "r"))) {
    myInput = NULL;
    Report::recoverable("[BSDL3DParser::setFilename] could not open file " + filename);
    return;
  }
  
  RCString directory = StringUtilities::extractPath(filename);
  if (!directory.isEmpty())
    addCppParameters("-I" + directory);
}

void BSDL3DParser::adoptFile(FILE* input)
{ 
  if (myInput != stdin && myInput != NULL)
    fclose(myInput);

  myInput = input;
}


bool BSDL3DParser::doExecute()
{
  BSDLParser parser;

  if (myInput == NULL) {
    Report::warning("[BSDL3DParser::doExecute] no input file");
    return false;
  }
  
  if (!parser.parse(getWorld(), myInput, myCppParameters)) {
    Report::recoverable("[BSDL3DParser::doExecute] parsing failed");
    return false;
  }

  if (myInput != stdin) {
    fclose(myInput);
    myInput = NULL;
  }

  getWorld()->getObjects()->computeBoundsLazy();
  
  return true;
}

