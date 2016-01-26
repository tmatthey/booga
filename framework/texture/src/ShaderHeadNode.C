/*
 * ShaderHeadNode.C
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
 *  $Id: ShaderHeadNode.C,v 1.4 1996/06/06 11:49:44 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include "booga/texture/ShaderHeadNode.h"
#include "booga/texture/ShaderDeclNode.h"

ShaderHeadNode::ShaderHeadNode(RCString* theShaderType,
                               RCString* theName,
                               List<ShaderNode*>* theParamDecls)
{
  myShaderType = theShaderType;
  myName = theName;
  myFileName = NULL;
  myParamDecls = theParamDecls;
  setWarningFlag(true);
}

ShaderHeadNode::~ShaderHeadNode()
{
  delete myShaderType;
  delete myName;
  delete myFileName;
  if (myParamDecls != NULL) {
    for(register long i = 0; i < myParamDecls->count(); i++)
      delete myParamDecls->item(i);
    delete myParamDecls;
  }
}

void ShaderHeadNode::print(bool)
{
  std::cout << *myShaderType << " " << *myName << "(";
  if(myParamDecls) {
    int PDC = myParamDecls->count();
    for(register long i = 0; i < PDC - 1; i++) {
      ((ShaderDeclNode*)myParamDecls->item(i))->printParamDecls();
      std::cout << ", ";
      if ((i%3 == 0) && (i != 0))
        std::cout << std::endl << "\t\t";
    }
    if (PDC > 0) 
      ((ShaderDeclNode*)myParamDecls->item(PDC - 1))->printParamDecls(); 
  } 
   std::cout << ")" << std::endl;
}  
 
void ShaderHeadNode::execute(Texture3DContext& context)
{
  if (myParamDecls)
    for (register long i = 0; i < myParamDecls->count(); i++) {
      myParamDecls->item(i)->execute(context);
    }
}

void ShaderHeadNode::overwriteDefaults(const List<Value*>* theArguments)
{
  // If the number of provided arguments is smaller than the number
  // of declared parameters, we will overwrite only the "first"
  // parameters of the list. If vice versa, we will ignore the
  // arguments that can not be mapped onto a parameter.
  
  int argNumber = (theArguments != NULL) ? theArguments->count() : 0;
  int paramNumber = (myParamDecls != NULL) ? myParamDecls->count() : 0;
  Value* temp = theArguments->item(0);
  if (myFileName != NULL)
    delete myFileName;
  myFileName = new RCString((RCString)*temp);
  if(argNumber > 1) {
    if(argNumber - 1 <= paramNumber)
      for (int i = 1; i < argNumber; i++) {
        Value* theIthItem = theArguments->item(i);
        ((ShaderDeclNode*)myParamDecls->item(i-1))->overwriteDefaults(*theIthItem);
      } 
    else {
      std::stringstream temp;
      temp << "[ShaderHeadNode::execute()] ";
      temp << "Too many arguments in call to shader \"" << myFileName
           << "\"! Ignoring last";
      int diff = argNumber - paramNumber - 1;
      if (diff > 1)
        temp << " " << diff;
      temp << " argument";
      if (diff > 1)
        temp << "s";
      if (isWarningFlagTrue()) {
        Report::warning(RCString(temp));
        setWarningFlag(false);
      }        
      for (int i = 0; i < paramNumber; i++) {
        Value* theIthItem = theArguments->item(i+1);
        ((ShaderDeclNode*)myParamDecls->item(i))->overwriteDefaults(*theIthItem);
      }
    }
  }
}
void ShaderHeadNode::printValues()
{
  std::cout << std::endl << "Shader Instance Variables:" << std::endl;
  if (myParamDecls)
    for (register long i = 0; i < myParamDecls->count(); i++)
      myParamDecls->item(i)->printValues();
  std::cout << std::endl;
}

List<Value*>* ShaderHeadNode::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  RCString temp =  RCString('\"',1) + RCString(*myFileName) + RCString('\"',1);
  parameters->append(new Value(temp));
  if(myParamDecls) {
    for(register long i = 0; i < myParamDecls->count(); i++) {
      parameters->append(((ShaderDeclNode*)myParamDecls->item(i))->createValue());
    } 
  }
  return parameters;
}
