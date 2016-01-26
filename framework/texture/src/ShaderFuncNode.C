/*
 * ShaderFuncNode.C
 *
 * Copyright (C) 1995-96, Thomas Teuscher <teuscher@iam.unibe.ch>
 *                        University of Berne, Switzerland
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
 *  $Id: ShaderFuncNode.C,v 1.5 1996/06/06 11:49:39 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include "booga/texture/ShaderFuncNode.h"
#include "booga/texture/ShaderFunction.h"
#include "booga/base/AbstractPixmap.h"
     
ShaderFuncNode::ShaderFuncNode(RCString& errMsg, RCString* theName, List<ShaderExpNode*>* theArgs)
{
  myExeFlag = true;
  
  if (ourFunctions->lookup(*theName, myFunction) == 0) {
    errMsg = "Unknown function name: " + *theName + "()";
    setFatalError();
    myExeFlag = false;
  }  
  else {
    int rpn;
       rpn = myFunction->getRequiredParameterNumber();
    if (((theArgs != NULL) && (rpn != theArgs->count())) ||
        ((theArgs == NULL) && rpn != 0)) {
      std::stringstream temp;
      temp << "Function " << *theName << "() requires "
           << rpn << " argument";
      if (rpn > 1)
      temp << "s";
      errMsg = RCString(temp);
      setFatalError();
      myExeFlag = false;
    }
  }
  
  myName = theName;
  myArgList = theArgs;
  myBlockDepth = getCurrentBlockDepth();
}

ShaderFuncNode::~ShaderFuncNode()
{
  myFunction = NULL;
  delete myName;
  if (myArgList != NULL) {
    for (register long i = 0; i < myArgList->count(); i++)
      delete myArgList->item(i);
    delete myArgList;
  }
}

void ShaderFuncNode::print(bool indent)
{
  if (indent)
    printSpaces(2 * myBlockDepth);
  std::cout << *myName  << "(";
  if (myArgList != NULL) {
    for (register long i = 0; i < myArgList->count() - 1; i++) {
      myArgList->item(i)->print(0);
      std::cout << ", ";
    }
    myArgList->item(myArgList->count() - 1)->print(0);
  }
  std::cout << ")";
}

void ShaderFuncNode::execute(Texture3DContext& context)
{
  evaluate(context);
}

Value* ShaderFuncNode::evaluate(Texture3DContext& context)
{
  if(myExeFlag == true)
    return myFunction->evaluate(myArgList, context);
  else
    return new Value(0.);
}
