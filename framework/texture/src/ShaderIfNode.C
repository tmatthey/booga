/*
 * ShaderIfNode.C
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
 *  $Id: ShaderIfNode.C,v 1.4 1996/04/18 14:31:04 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream.h>
#include "booga/texture/ShaderIfNode.h"

ShaderIfNode::ShaderIfNode(ShaderExpNode* theExp, ShaderNode* theStmt)
{
  myExp = theExp;
  myStmt = theStmt;
  myBlockDepth = getCurrentBlockDepth();
}
     
ShaderIfNode::~ShaderIfNode()
{
  delete myExp;
  delete myStmt;
}

void ShaderIfNode::print(bool indent)
{
  if (indent)
  printSpaces(2 * myBlockDepth);
  cout << "if (";
  myExp->print(false);
  cout << ") " << endl;
  myStmt->print();
}

void ShaderIfNode::execute(Texture3DContext& context)
{
  Value* temp = myExp->evaluate(context);
  int val = (int)*temp;

  delete temp;
  if(val)
    myStmt->execute(context);
}
