/*
 * ShaderIfThenElseNode.C
 *
 * Copyright (C) 1995 Thomas Teuscher <teuscher@iam.unibe.ch>
 *                    University of Berne Switzerland
 *
 * All rights reserved.
 *
 * This software may be freely copied, modIfThenElseied and redistributed
 * provided that this copyright note be preserved on all copies.
 * 
 * You may not distribute this software, in whole or in part, as part
 * of any commercial product without the express consent of the author.
 *
 * There is no warranty or other guarantee of fitness of this software
 * for any purpose. It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: ShaderIfThenElseNode.C,v 1.4 1996/04/18 14:31:05 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream.h>
#include "booga/texture/ShaderIfThenElseNode.h"

ShaderIfThenElseNode::ShaderIfThenElseNode(ShaderExpNode* theExp,
                                           ShaderNode* theThenStmt,
                                           ShaderNode* theElseStmt)
{
  myExp = theExp;
  myThenStmt = theThenStmt;
  myElseStmt = theElseStmt;
  myBlockDepth = getCurrentBlockDepth();
}
     
ShaderIfThenElseNode::~ShaderIfThenElseNode()
{
  delete myExp;
  delete myThenStmt;
  delete myElseStmt;
}

void ShaderIfThenElseNode::print(bool indent)
{
  if (indent)
    printSpaces(2 * myBlockDepth);
  cout << "if (";
  myExp->print(false);
  cout << ") " << endl;
  myThenStmt->print();
  cout << ";" << endl;
  if (indent)
    printSpaces(2 * myBlockDepth);
  cout << "else" << endl;
  myElseStmt->print();
}

void ShaderIfThenElseNode::execute(Texture3DContext& context)
{
  Value* temp = myExp->evaluate(context); 
  if((int)*temp != 0)
    myThenStmt->execute(context);
  else
    myElseStmt->execute(context);
    
  delete temp;
}
