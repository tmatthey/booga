/*
 * ShaderProgNode.C
 *
 * Copyright (C) 1996 Thomas Teuscher <teuscher@iam.unibe.ch>
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
 *  $Id: ShaderProgNode.C,v 1.5 1996/04/18 14:40:00 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream.h>
#include "booga/texture/ShaderProgNode.h"
#include "booga/texture/ShaderHeadNode.h"

ShaderProgNode::ShaderProgNode(ShaderProgNode* theProg)
{
 if (theProg) {
   myHead = theProg->myHead;
   myCmpStmt = theProg->myCmpStmt;
   myLocalScope = theProg->myLocalScope;
 }   
}

ShaderProgNode::ShaderProgNode(ShaderNode* theHead, ShaderNode* theCmpStmt)
{
  myHead = theHead;
  myCmpStmt = theCmpStmt;
  myLocalScope = getCurrentScope();
}

ShaderProgNode::~ShaderProgNode()
{
  delete myHead;
  delete myCmpStmt;
  delete myLocalScope;
}

void ShaderProgNode::print(bool)
{
  myHead->print(false);
  myCmpStmt->print(false);
  cout << endl;
}  
 
void ShaderProgNode::overwriteDefaults(const List<Value*>* theParameters,
                                       Texture3DContext& context)
{
  // myHead->exeute() will reset the head's parameters to their
  // default values (they could have been changed during execution!).
  // But if we want to overwrite them with the arguments of
  // a shader call, we have to reset them  b e f o r e
  // we can overwrite them, otherwise we
  // would reset the overwritten values to their defaults again!
  // That's why we call myHead->execute() here already.
  ourScopes->prepend(myLocalScope);
  myHead->execute(context);
  ((ShaderHeadNode*)myHead)->overwriteDefaults(theParameters);
  ourScopes->remove(0);
}

void ShaderProgNode::execute(Texture3DContext& context)
{
  ourScopes->prepend(myLocalScope);
  // we will not call myHead->execute() here because this would
  // reset the already overwritten parameters back to their defaults!
  myCmpStmt->execute(context);
  ourScopes->remove(0);
}

void ShaderProgNode::printValues()
{
  ourScopes->prepend(myLocalScope);
  myHead->printValues();
  myCmpStmt->printValues();
  ourScopes->remove(0);  
}

List<Value*>* ShaderProgNode::createParameters() {
  return ((ShaderHeadNode*)myHead)->createParameters();
}
