/*
 * $RCSfile: BSDL2DParser.C,v $
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
 *  $Id: BSDL2DParser.C,v 1.12 1996/08/01 11:58:56 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#include "booga/base/StringUtilities.h"
#include "booga/object/Object2D.h"
#include "booga/object/Aggregate2D.h"
#include "booga/component/BSDL2DParser.h"

//_________________________________________________________________ BSDL2DParser

implementRTTI(BSDL2DParser, Operation2D);

BSDL2DParser::BSDL2DParser()
: myInput(stdin)
{}

BSDL2DParser::~BSDL2DParser()
{
  if (myInput != stdin && myInput != NULL)
    fclose(myInput);
}

void BSDL2DParser::setFilename(const RCString& filename)
{
  if (filename.isEmpty())
    return;

  if (myInput != stdin && myInput != NULL) {
    fclose(myInput);
    myInput = NULL;
  }

  if (!(myInput = fopen(filename.chars(), "r"))) {
    myInput = NULL;
    Report::recoverable("[BSDL2DParser::setFilename] could not open file " + filename);
    return;
  }

  RCString directory = StringUtilities::extractPath(filename);
  if (!directory.isEmpty())
    addCppParameters("-I" + directory);
}

void BSDL2DParser::adoptFile(FILE* input)
{ 
  if (myInput != stdin && myInput != NULL)
    fclose(myInput);

  myInput = input;
}

bool BSDL2DParser::doExecute()
{
  BSDLParser parser;

  if (myInput == NULL) {
    Report::warning("[BSDL2DParser::doExecute] no input file");
    return false;
  }
  
  if (!parser.parse(getWorld(), myInput, myCppParameters)) {
    Report::recoverable("[BSDL2DParser::doExecute] parsing failed");
    return false;
  }

  if (myInput != stdin) {
    fclose(myInput);
    myInput = NULL;
  }

  getWorld()->getObjects()->computeBoundsLazy();
  
  return true;
}
