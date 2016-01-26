/*
 * $RCSfile: BSDLParser.C,v $
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
 *  $Id: BSDLParser.C,v 1.6 1997/09/19 07:13:52 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Report.h"
#include "booga/base/ParserUtilities.h"
#include "booga/component/BSDLParser.h"
#include "BSDLLex.h"
#include "BSDLYacc.h"

/*_______________________________________________________________ BSDLParserImpl
 *
 * Private implementation of the BSDLParser data. Doing it this way,
 * we do not have do make the BSDLLex.h and BSDLYacc.h files 
 * publicly available. 
 */

class BSDLParserImpl : public BSDLYacc {
public:
  BSDLParserImpl() {};
  // ~BSDLParserImpl();   // Use default version.

  int parse(World* world, FILE* input = stdin, 
                          const RCString& cppParameters = RCString());
  // Return 1, if parsing was not successful, 0 otherwise.

  void debugScanner(bool enable = true);
  void debugParser(bool enable = true);

protected:
  virtual int scan();
  virtual void fatalError(char* errorMsg);
  virtual void recoverableError(const RCString& errorMsg);

private:
  BSDLLex myScanner;
  
private:
  RCString createErrorMsg(const RCString& errorMsg);
  
private:
  BSDLParserImpl(const BSDLParserImpl&);            // No copies.
  BSDLParserImpl& operator=(const BSDLParserImpl&); // No assignments.
};

int BSDLParserImpl::parse(World* world, FILE* input, const RCString& cppParameters) 
{
  if (world == NULL) {
    Report::error("[Error 1, line 0] empty world  provided");
    return 0;
  }
 
  if ((myScanner.inputFile = ParserUtilities::cppopen(input, cppParameters)) == NULL) {
    Report::error("[Error 1, line 0] could not spawn preprocessor");
    return 0;
  }

  setWorldObject(world);
  int retval = !(BSDLYacc::parse() || myErrorCount);

  ParserUtilities::cppclose(myScanner.inputFile);
 
  return retval;
}

void BSDLParserImpl::debugScanner(bool enable)
{
  myScanner.myScannerDebugFlag = enable;
}

void BSDLParserImpl::debugParser(bool enable)
{
  myParserDebugFlag = enable;
}

int BSDLParserImpl::scan()
{
  return myScanner.scan(myTokenValue);
}

void BSDLParserImpl::fatalError(char* errorMsg)
{
  Report::recoverable(createErrorMsg(errorMsg));
}

void BSDLParserImpl::recoverableError(const RCString& errorMsg)
{
  Report::recoverable(createErrorMsg(errorMsg));
}

RCString BSDLParserImpl::createErrorMsg(const RCString& errorMsg)
{
  RCString file; 
  if (myScanner.getCurrentFilename() != "\"\"")
    file = ", file " + myScanner.getCurrentFilename();

  std::stringstream str;
  str <<"[Error " << (++myErrorCount) << file
      << ", line " <<myScanner.getCurrentLine()
      << ", near \""  << myScanner.getCurrentToken() << "\"] "
      << errorMsg;
    return  RCString(str.str().c_str());
}

/*___________________________________________________________________ BSDLParser
 *
 * The BSDLParser class serves as an envelope using the functionality 
 * of the letter class BSDLParserImpl. Requests are forwarded to the 
 * letter instance.
 */

BSDLParser::BSDLParser()
{
  myParser = new BSDLParserImpl;
}

BSDLParser::~BSDLParser() 
{
  delete myParser;
}

int BSDLParser::parse(World* world, FILE* input, const RCString& cppParameters)
{
  return myParser->parse(world, input, cppParameters);
}

void BSDLParser::debugScanner(bool enable)
{
  myParser->debugScanner(enable);
}

void BSDLParser::debugParser(bool enable)
{
  myParser->debugParser(enable);
}
