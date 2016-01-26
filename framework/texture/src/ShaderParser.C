/*
 * ShaderParser.C
 *
 * Copyright (C) 1995 Thomas Teuscher <teuscher@iam.unibe.ch>
 *                    University of Berne Switzerland
 *
 * All rights reserved.
 *
 * This software may be freely copied, modified and redistributed
 * provided that this copyright note be preserved on all copies.
 * 
 * You may not distribute this software, in whole or in part, as part
 * of any commercial product without the express consent of the author.
 *
 * There is no warranty or other guarantee of fitness of this software
 * for any purpose. It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: ShaderParser.C,v 1.7 1997/09/19 07:14:48 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
#ifdef SVR4
#include <stream.h>
#endif
#include "ShaderLex.h"
#include "ShaderYacc.h"
#include "booga/base/Report.h"
#include "booga/texture/ShaderParser.h"

/*__________________________________________________________ ShaderParserImpl
 *
 * Private implementation of the ShaderParser data. Doing it this way,
 * we do not have do make the ShaderLex.h and ShaderYacc.h files 
 * publicly available. 
 */

class ShaderParserImpl : public ShaderYacc {
public:
  ShaderParserImpl() {};
  // ~ShaderParserImpl();   // Use default version
  
  int parse(RCString inputFile);
  void setParseFile(FILE* parseFile);

protected:
  virtual int scan();
  virtual void fatalError(char* msg);
  virtual void recoverableError(const RCString& msg);
  virtual void warning(const RCString& msg);

private:
  ShaderLex myScanner;
  RCString myFileName;
  
private:
  RCString createErrorMsg(const RCString& errorMsg);
  RCString createWarnMsg(const RCString& warnMsg);  
  ShaderParserImpl(const ShaderParserImpl&);              // no copies
  ShaderParserImpl& operator=(const ShaderParserImpl&);   // no assignment
};
  
int ShaderParserImpl::parse(RCString fileName)
{
  myFileName = fileName;
  // HACK !!! to delete the last "
  if (myFileName.length() > 1 && myFileName[myFileName.length()-1] == '\"')
    myFileName = myFileName(0,myFileName.length()-2);


  // check if file exists and assign to parser

  FILE* parseFile = fopen(myFileName.chars(), "r");
  if (parseFile == NULL) {
    Report::recoverable("[ShaderParserImpl::parse] could not open file " + myFileName);
    return false;
  }
    
  setParseFile(parseFile);
  int retval = ShaderYacc::parse();
  fclose(parseFile);
  return retval;
}

void ShaderParserImpl::setParseFile(FILE* parseFile)
{
  myScanner.setParseFile(parseFile);
}

int ShaderParserImpl::scan()
{
  return myScanner.scan(myTokenValue);
}

void ShaderParserImpl::fatalError(char* errorMsg)
{
  Report::recoverable(createErrorMsg(errorMsg));
}

void ShaderParserImpl::recoverableError(const RCString& errorMsg)
{
  myErrorCount++;
  Report::recoverable(createErrorMsg(errorMsg));
}

RCString ShaderParserImpl::createErrorMsg(const RCString& errorMsg)
{
  RCString file; 
  if (myFileName != "\"\"")
    file = ", file " + myFileName;

  return  RCString("[Error ") + form("%d", myErrorCount) 
		   + file
		   + ", line " + form("%d", myScanner.getLineNo())
 		   + ", near \"" + myScanner.getToken() + "\"] "
                     + errorMsg;
}

void ShaderParserImpl::warning(const RCString& warnMsg)
{
  Report::warning(createWarnMsg(warnMsg));
}

RCString ShaderParserImpl::createWarnMsg(const RCString& warnMsg)
{
  RCString file; 
  if (myFileName != "\"\"")
    file = ", file " + myFileName;

  return  RCString(file + ", line " + form("%d", myScanner.getLineNo())
 		   + ", near \"" + myScanner.getToken() + "\"] "
                   + warnMsg);
}



/*___________________________________________________________________ ShaderParser
 *
 * The ShaderParser class serves as an envelope using the functionality 
 * of the letter class ShaderParserImpl. Requests are forwarded to the 
 * letter instance.
 */

ShaderParser::ShaderParser()
{
  myParser = new ShaderParserImpl();
}

ShaderParser::~ShaderParser() 
{
  delete myParser;
}

int ShaderParser::parse(RCString fileName)
{
  return myParser->parse(fileName);
}

ShaderProgNode* ShaderParser::getParseTree()
{
  return myParser->getParseTree();
}
