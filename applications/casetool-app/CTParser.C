/*
 * CTParser.C
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
 *  $Id: CTParser.C,v 1.13 1996/10/30 08:30:20 siebenth Exp $
 * -----------------------------------------------------------------------------
 */

#include <stream.h>
#include "booga/base/Report.h"
#include "booga/base/ParserUtilities.h"
#include "booga/base/StringUtilities.h"
#include "CTParser.h"
#include "CTLex.h"
#include "CTYacc.h"

/*_______________________________________________________________ CTParserImpl
 *
 * Private implementation of the CTParser data. Doing it this way,
 * we do not have do make the CTLex.h and CTYacc.h files 
 * publicly available. 
 */

class CTParserImpl : public CTYacc {
public:
  CTParserImpl() {};
  // ~CTParserImpl();   // Use default version.

  bool parse(World2D* world, FILE* input = stdin, 
                             const RCString& cppParameters = RCString());
  // Return false, if parsing was not successful, true otherwise.

  void debugScanner(bool enable = true);
  void debugParser(bool enable = true);
  void verboseOutput(bool enable = true);

protected:
  virtual int scan();
  virtual void fatalError(char* errorMsg);
  virtual void recoverableError(const RCString& errorMsg);

private:
  CTLex myScanner;
  
private:
  RCString createErrorMsg(const RCString& errorMsg);
  
private:
  CTParserImpl(const CTParserImpl&);            // No copies.
  CTParserImpl& operator=(const CTParserImpl&); // No assignments.
};

bool CTParserImpl::parse(World2D* world, FILE* input, const RCString& cppParameters) 
{
  if (world == NULL) {
    Report::error("[Error 1, line 0] empty world  provided");
    return false;
  }
 
  if ((myScanner.inputFile = ParserUtilities::cppopen(input, cppParameters)) == NULL) {
    Report::error("[Error 1, line 0] could not spawn preprocessor");
    return false;
  }

  setWorldObject(world);
  bool retval = !(CTYacc::parse() || myErrorCount);

  ParserUtilities::cppclose(myScanner.inputFile);
 
  return retval;
}

void CTParserImpl::debugScanner(bool enable)
{
  myScanner.myScannerDebugFlag = enable;
}

void CTParserImpl::debugParser(bool enable)
{
  myParserDebugFlag = enable;
}

void CTParserImpl::verboseOutput(bool enable)
{
  setVerboseFlag(enable);
}

int CTParserImpl::scan()
{
  return myScanner.scan(myTokenValue);
}

void CTParserImpl::fatalError(char* errorMsg)
{
  Report::recoverable(createErrorMsg(errorMsg));
}

void CTParserImpl::recoverableError(const RCString& errorMsg)
{
  Report::recoverable(createErrorMsg(errorMsg));
}

RCString CTParserImpl::createErrorMsg(const RCString& errorMsg)
{
  RCString file; 
  if (myScanner.getCurrentFilename() != "\"\"")
    file = ", file " + myScanner.getCurrentFilename();

  return  RCString("[Error ") + form("%d", ++myErrorCount) 
		   + file
		   + ", line " + form("%d", myScanner.getCurrentLine())
 		   + ", near \"" + myScanner.getCurrentToken() + "\"] "
                     + errorMsg;
}

/*___________________________________________________________________ CTParser
 *
 * The CTParser class serves as an envelope using the functionality 
 * of the letter class CTParserImpl. Requests are forwarded to the 
 * letter instance.
 */

implementRTTI(CTParser, Operation2D);

CTParser::CTParser()
: myInput(stdin)
{
  myParser = new CTParserImpl;
}

CTParser::~CTParser() 
{
  if (myInput != stdin && myInput != NULL)
    fclose(myInput);
  delete myParser;
}

void CTParser::setFilename(const RCString& filename)
{
  if (filename.isEmpty())
    return;

  if (myInput != stdin && myInput != NULL) {
    fclose(myInput);
    myInput = NULL;
  }

  if (!(myInput = fopen(filename.chars(), "r"))) {
    myInput = NULL;
    Report::error("[CTParser::setFilename] could not open file " + filename);
    return;
  }

  RCString directory = StringUtilities::extractPath(filename);
  if (!directory.isEmpty())
    addCppParameters("-I" + directory);
}

void CTParser::adoptFile(FILE* input)
{ 
  if (myInput != stdin && myInput != NULL)
    fclose(myInput);

  myInput = input;
}

bool CTParser::parse(World2D* world)
{

  if (myInput == NULL) {
    Report::warning("[CTParser::parse] no input file");
    return false;
  }
  
  if (!myParser->parse(world, myInput, myCppParameters)) {
    Report::recoverable("[CTParser::parse] parsing failed");
    return false;
  }

  if (myInput != stdin) {
    fclose(myInput);
    myInput = NULL;
  }

  return true;
}

bool CTParser::doExecute()
{
  if (!parse(getWorld())) {
    Report::recoverable("[CTParser::doExecute] parser failed");
    return false;
  }

  getWorld()->getObjects()->computeBounds();
  
  return true;
}

void CTParser::debugScanner(bool enable)
{
  myParser->debugScanner(enable);
}

void CTParser::debugParser(bool enable)
{
  myParser->debugParser(enable);
}

void CTParser::verboseOutput(bool enable)
{
  myParser->verboseOutput(enable);
}
