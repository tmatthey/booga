/*
 * $RCSfile: VRMLParser.C,v $
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
 *  $Id: VRMLParser.C,v 1.3 1997/09/19 07:15:19 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
#include <sstream>
#include "booga/base/Report.h"
#include "booga/component/VRMLParser.h"
#include "VRMLLex.h"
#include "VRMLYacc.h"

/*_______________________________________________________________ VRMLParserImpl
 *
 * Private implementation of the VRMLParser data. Doing it this way,
 * we do not have do make the VRMLLex.h and VRMLYacc.h files 
 * publicly available. 
 */

class VRMLParserImpl : public VRMLYacc {
public:
  VRMLParserImpl() {};
  virtual ~VRMLParserImpl(){}   // Use default version.

  int parse(World3D* world3D, FILE* input = stdin); 
  // Return 1, if parsing was not successful, 0 otherwise.

  void debugScanner(bool enable = true);
  void debugParser(bool enable = true);

protected:
  virtual int scan();
  virtual void fatalError(char* errorMsg);
  virtual void recoverableError(const RCString& errorMsg);

private:
  VRMLLex myScanner;
  
private:
  RCString createErrorMsg(const RCString& errorMsg);
  
private:
  VRMLParserImpl(const VRMLParserImpl&);            // No copies.
  VRMLParserImpl& operator=(const VRMLParserImpl&); // No assignments.
};

int VRMLParserImpl::parse(World3D* world3D, FILE* input) 
{
  if (world3D == NULL) {
    Report::error("[Error 1, line 0] empty world  provided");
    return 0;
  }
  
  myScanner.inputFile = input;

  setWorldObject(world3D);
  int retval = !(VRMLYacc::parse() || myErrorCount);

  return retval;
}

void VRMLParserImpl::debugScanner(bool enable)
{
  myScanner.myScannerDebugFlag = enable;
}

void VRMLParserImpl::debugParser(bool enable)
{
  myParserDebugFlag = enable;
}

int VRMLParserImpl::scan()
{
  return myScanner.scan(myTokenValue);
}

void VRMLParserImpl::fatalError(char* errorMsg)
{
  Report::error(createErrorMsg(errorMsg) + ", aborting");
}

void VRMLParserImpl::recoverableError(const RCString& errorMsg)
{
  Report::recoverable(createErrorMsg(errorMsg));
}

RCString VRMLParserImpl::createErrorMsg(const RCString& errorMsg)
{
  RCString file; 
  if (myScanner.getCurrentFilename() != "\"\"")
    file = ", file " + myScanner.getCurrentFilename();

  std::stringstream str;
  str <<"[Error " << (++myErrorCount) << file
      << ", line " << myScanner.getCurrentLine()
      << ", near \"" << myScanner.getCurrentToken() << "\"] "
      << errorMsg;
  return  RCString(str);
}

/*___________________________________________________________________ VRMLParser
 *
 * The VRMLParser class serves as an envelope using the functionality 
 * of the letter class VRMLParserImpl. Requests are forwarded to the 
 * letter instance.
 */

implementRTTI(VRMLParser, Operation3D);
// enable RTTI support

VRMLParser::VRMLParser()
: myInput(stdin)
{
  myParser = new VRMLParserImpl;
}

VRMLParser::~VRMLParser() 
{
  delete myParser;
  if (myInput != stdin)
    fclose(myInput);
}

int VRMLParser::parse(World3D* world3D, FILE* input)
{
  return myParser->parse(world3D, input);
}

void VRMLParser::debugScanner(bool enable)
{
  myParser->debugScanner(enable);
}

void VRMLParser::debugParser(bool enable)
{
  myParser->debugParser(enable);
}

bool VRMLParser::doExecute()
{
  if (!parse(getWorld(), myInput)) {
    Report::recoverable("[VRMLParser::doExecute] parser failed");
    return false;
  }

  if (myInput != stdin) {
    fclose(myInput);
    myInput = stdin;
  }
  
  getWorld()->getObjects()->computeBounds();

  return true;
}

void VRMLParser::setFilename(const RCString& filename)
{
  if (myInput != stdin) {
    fclose(myInput);
    myInput = stdin;
  }

  if (!(myInput = fopen(filename.chars(), "r")))
    Report::error("[VRMLParser::setFilename] could not open file " + filename);
}

