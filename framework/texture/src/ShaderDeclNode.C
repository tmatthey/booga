/*
 * ShaderDeclNode.C
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
 *  $Id: ShaderDeclNode.C,v 1.5 1996/06/06 11:49:38 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/texture/ShaderDeclNode.h"

NVPair::NVPair(RCString* theName, ShaderExpNode* theExpr)
: name(theName), expr(theExpr)
{}

NVPair::~NVPair()
{
  delete name;
  delete expr;
}

ShaderDeclNode::ShaderDeclNode()
{
  myValidType = NULL;
  myDeclList = NULL;
}

ShaderDeclNode::ShaderDeclNode(RCString& warnMsg, RCString* theValidType, List<NVPair*>* theDeclList)
{
  myValidType = theValidType;
  myDeclList = theDeclList;
  myBlockDepth = getCurrentBlockDepth();
  insertValues(warnMsg);
};

ShaderDeclNode::~ShaderDeclNode()
{
  delete myValidType;
  if (myDeclList != NULL) {
    for (register long i = 0; i < myDeclList->count(); i++)
      delete myDeclList->item(i);
  delete myDeclList;
  }
}

void ShaderDeclNode::print(bool)
{
  if (myDeclList->count() > 0) {
    printSpaces(2 * myBlockDepth);
    std::cout << *myValidType;
    std::cout << " ";
    for (register long i = 0; i < myDeclList->count() - 1; i++) {
      std::cout << *myDeclList->item(i)->name;
      if (myDeclList->item(i)->expr) {
        std::cout << " = "; 
        myDeclList->item(i)->expr->print(0);
      }
      std::cout << ", ";
    }
     std::cout << *myDeclList->item(myDeclList->count() - 1)->name;
    if (myDeclList->item(myDeclList->count() - 1)->expr) {
      std::cout << " = ";
      myDeclList->item(myDeclList->count() - 1)->expr->print(0);
    }
    std::cout << ";" << std::endl;
  }
}

void ShaderDeclNode::execute(Texture3DContext& context)
{
  //
  // since the variables could have been changed during the previous
  // execution, they must be re-initialized before the new execution!
  //

  Value temp = Value(0.0);
  for (register long i = 0; i < myDeclList->count(); i++) {
    RCString name = *myDeclList->item(i)->name;
    // no optional init -> multiplicate with zero (unless type is string!)
    if (myDeclList->item(i)->expr == NULL) {
      if(*myValidType != "string") {
        Value oldValue;
        getCurrentScope()->lookup(name, oldValue);
        Value newValue = temp * oldValue;
        getCurrentScope()->findAndReplace(name, newValue);
      }
    }
    else {        // assign the value of the optional init
      Value* temp = myDeclList->item(i)->expr->evaluate(context);
      Value newValue = *temp;
      getCurrentScope()->findAndReplace(name, newValue);
      delete temp;
    }
  }
}

void ShaderDeclNode::overwriteDefaults(const Value& theParameterValue)
{
  // there is just one element in myDeclList, so no need 
  // to iterate over it.
  // a declarator list could theoretically be empty, if a parameter
  // was declared twice. So we must check if it is not.
  if (myDeclList->count() > 0) {
    RCString* name = myDeclList->item(0)->name;
    getCurrentScope()->findAndReplace(*name, theParameterValue);
  }
}

void ShaderDeclNode::printParamDecls()
{
  // if a parameter was declared twice (mistake!), it was removed
  // from the list. So let's check if the list really contains something
  if (myDeclList->count() > 0) {
    std::cout << *myValidType;
    std::cout << " ";
    std::cout << *myDeclList->item(0)->name;
    if (myDeclList->item(0)->expr) {
      std::cout << " = "; 
      myDeclList->item(0)->expr->print(0);
    }
  }
}
void ShaderDeclNode::insertValues(RCString& warnMsg)
{
  Texture3DContext context; // dummy context for evaluate()-function!
  
  for (register long i = 0; i < myDeclList->count(); i++) {
    Value* temp;
    
    if (*myValidType == "real") {
      if (myDeclList->item(i)->expr == NULL)
        temp = new Value((Real) 0.0);
      else
        temp = myDeclList->item(i)->expr->evaluate(context);
    }  
    else if (*myValidType == "string") {
      if (myDeclList->item(i)->expr == NULL)
        temp = new Value(" ");
      else
        temp = myDeclList->item(i)->expr->evaluate(context);
    }  
    else if (*myValidType == "color") {
      if(myDeclList->item(i)->expr == NULL) {
        Vector3D newVector =  Vector3D();
        temp = new Value(newVector);          // color handled as vector!
      }
      else
        temp = myDeclList->item(i)->expr->evaluate(context);
    }
    else if (*myValidType == "vector") {
      if(myDeclList->item(i)->expr == NULL) {
        Vector3D newVector = Vector3D();
        temp = new Value(newVector);
      }
      else
        temp = myDeclList->item(i)->expr->evaluate(context);
    }
    
    if(!getCurrentScope()->lookup(*myDeclList->item(i)->name, *temp)) {
      getCurrentScope()->insert(*myDeclList->item(i)->name, *temp);
      delete temp;
    }
    else {
      warnMsg = RCString("One or more variables are already declared ")
              + "in this scope. Ignoring last declaration";
      myDeclList->remove(i);
      i--;
    }
  }
}

void ShaderDeclNode::printValues()
{
  for (register long i = 0; i < myDeclList->count(); i++) {
    Value* temp = new Value();
    if (getCurrentScope()->lookup(*myDeclList->item(i)->name, *temp))
      std::cout << *myDeclList->item(i)->name << " = " << *temp << std::endl;
    delete temp;
  }
}
      
Value* ShaderDeclNode::createValue()
{
  Value* value = NULL;
  Texture3DContext context; // dummy context for evaluate()-function!

  if ((myDeclList->count() > 0) && (myDeclList->item(0)->expr != NULL))
      value = myDeclList->item(0)->expr->evaluate(context);

  return value;
}
