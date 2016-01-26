/*
 * ShaderArithExpNode.C
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
 *  $Id: ShaderArithExpNode.C,v 1.4 1996/04/18 14:30:47 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream.h>
#include "booga/texture/ShaderArithExpNode.h"
     
ShaderArithExpNode::ShaderArithExpNode(char theOperator,
                                       ShaderExpNode* theOp1,
                                       ShaderExpNode* theOp2)
{
  myOperator = theOperator;
  myOp1 = theOp1;
  myOp2 = theOp2;
  myBlockDepth = getCurrentBlockDepth();
}

ShaderArithExpNode::~ShaderArithExpNode()
{
  delete myOp1;
  myOp1 = NULL;
  delete myOp2;
  myOp2 = NULL;
}

void ShaderArithExpNode::print(bool indent)
{
  if (indent)
    printSpaces(2 *myBlockDepth);
  myOp1->print(false);
  cout << " " << myOperator << " ";
  myOp2->print(false);
}

void ShaderArithExpNode::execute(Texture3DContext&)
{}

Value* ShaderArithExpNode::evaluate(Texture3DContext& context)
{
  Value* temp1 = myOp1->evaluate(context);
  Value* temp2 = myOp2->evaluate(context);
  Value arg1 = *temp1;
  Value arg2 = *temp2;
  
  delete temp1;
  delete temp2;
  switch(myOperator) {
  case '+':
    return new Value(arg1 + arg2);
    break;
  case '-':
    return new Value(arg1 - arg2);  
    break;
  case '*':
    return new Value(arg1 * arg2);
    break;
  case '/':
    return new Value(arg1 / arg2);
    break;
  case '%':
    return new Value(arg1 % arg2);
    break;
  case '^':
    return new Value(arg1 ^ arg2);
    break;
  default:
    return NULL;
  }
  
  return NULL;
}
