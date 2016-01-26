/*
 * ShaderCompExpNode.C
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
 *  $Id: ShaderCompExpNode.C,v 1.4 1996/04/18 14:30:52 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream.h>
#include <string.h>
#include "booga/texture/ShaderCompExpNode.h"
     
ShaderCompExpNode::ShaderCompExpNode(char* theOperator,
                                     ShaderExpNode* theOp1,
                                     ShaderExpNode* theOp2)
{
  myOperator = theOperator;
  myOp1 = theOp1;
  myOp2 = theOp2;
  myBlockDepth = getCurrentBlockDepth();
}

ShaderCompExpNode::~ShaderCompExpNode()
{
  delete myOp1;
  delete myOp2;
}

void ShaderCompExpNode::print(bool indent)
{
  if (indent)
    printSpaces(2 *myBlockDepth);
  myOp1->print(false);
  cout << " " << myOperator << " ";
  myOp2->print(false);
}

void ShaderCompExpNode::execute(Texture3DContext&)
{}

Value* ShaderCompExpNode::evaluate(Texture3DContext& context)
{
  Value* temp1 = myOp1->evaluate(context);
  Value* temp2 = myOp2->evaluate(context);
  Value arg1 = *temp1;
  Value arg2 = *temp2;
  
  delete temp1;
  delete temp2;
  if (!strcmp(myOperator, ">"))
    return new Value(arg1 > arg2);
  else if (!strcmp(myOperator, "<"))
    return new Value(arg1 < arg2);
  else if (!strcmp(myOperator, ">="))
    return new Value(arg1 >= arg2);
  else if (!strcmp(myOperator, "<="))
    return new Value(arg1 <= arg2);
  else if (!strcmp(myOperator, "=="))
    return new Value(arg1 == arg2);
  else if (!strcmp(myOperator, "!="))
    return new Value(arg1 != arg2);

  else return NULL;
}

