/*
 * ShaderShaderNode.C 
 *
 * Copyright (C) 1996, Thomas Teuscher <teuscher@iam.unibe.ch>
 *                     University of Berne, Switzerland
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
 *  $Id: ShaderShaderNode.C,v 1.3 1996/06/06 11:49:50 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/texture/ShaderShaderNode.h"
#include "booga/texture/ShaderParser.h"
#include "booga/texture/ShaderExpNode.h"

ShaderShaderNode::ShaderShaderNode(List<ShaderExpNode*>* arguments)
{
  myBlockDepth = getCurrentBlockDepth();
  myArguments = arguments;
  setFirstPass(true);
}

ShaderShaderNode::~ShaderShaderNode()
{
  delete myParseTree;
  if (myArguments != NULL) {
    for (register long i = 0; i < myArguments->count(); i++)
      delete myArguments->item(i);
    delete myArguments;
  }
}

void ShaderShaderNode::print(bool indent)
{
  if (indent)
    printSpaces(2 * myBlockDepth);
  std::cout << "shader(";
  if(myArguments) {
    for(register long i = 0; i < myArguments->count() - 1; i++) {
      myArguments->item(i)->print(0);
      std::cout << ", ";
    }
    if (myArguments->count() > 0) 
      myArguments->item(myArguments->count() - 1)->print(0);
  } 
   std::cout << ")";
}  

void ShaderShaderNode::execute(Texture3DContext& context)
{
  // because the arguments that we pass to the shader can change
  // during execution, e.g. an argument being the current position,
  // we have to overwrite the defaults before we can continue
  // interpreting the shader's parsetree.

  List<Value*>* theArguments = new List<Value*>(myArguments->count());
  for (int i = 0; i < myArguments->count(); i++)
    theArguments->append(myArguments->item(i)->evaluate(context));  

  if (isFirstPass()) {
    Value* temp = myArguments->item(0)->evaluate(context);
    RCString fileToParse = (RCString)*temp;
    ShaderParser parser;
    parser.parse(fileToParse);
    parser.getParseTree()->overwriteDefaults(theArguments, context);
    myParseTree = parser.getParseTree();
    setFirstPass(false);
  }

  for (int j = 0; j < theArguments->count(); j++)
  delete theArguments->item(j);
  delete theArguments;
  myParseTree->execute(context);
}
