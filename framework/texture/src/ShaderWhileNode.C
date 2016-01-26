/*
 * ShaderWhileNode.C
 *
 * Copyright (C) 1995 Thomas Teuscher <teuscher@iam.unibe.ch>
 *                    University of Berne Switzerland
 *
 * All rights reserved.
 *
 * This software may be freely copied, modForied and redistributed
 * provided that this copyright note be preserved on all copies.
 * 
 * You may not distribute this software, in whole or in part, as part
 * of any commercial product without the express consent of the author.
 *
 * There is no warranty or other guarantee of fitness of this software
 * for any purpose. It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: ShaderWhileNode.C,v 1.5 1996/04/18 14:31:33 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include "booga/texture/ShaderWhileNode.h"

ShaderWhileNode::ShaderWhileNode(ShaderExpNode* theExp, ShaderNode* theStmt)
{ 
  myExp = theExp;
  myStmt = theStmt;
  myBlockDepth = getCurrentBlockDepth();
}

ShaderWhileNode::~ShaderWhileNode()
{
  delete myExp;
  delete myStmt;
}
     
void ShaderWhileNode::print(bool indent)
{
  if (indent)
    printSpaces(2 * myBlockDepth);
  std::cout << "while (";
  myExp->print(false);
  std::cout << ")" << std::endl;
  myStmt->print();
}

void ShaderWhileNode::execute(Texture3DContext& context)
{
  Value* temp = myExp->evaluate(context);
  int condition = (int)*temp;
  delete temp;
  
  while(condition != 0) {
    myStmt->execute(context);
    temp = myExp->evaluate(context);
    condition = (int)*temp;
    delete temp;
  }
}
