/*
 * ShaderForNode.C
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
 *  $Id: ShaderForNode.C,v 1.4 1996/04/18 14:30:56 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream.h>
#include "booga/base/Value.h"
#include "booga/texture/ShaderForNode.h"

ShaderForNode::ShaderForNode(ShaderExpNode* theBaseExp,
                             ShaderExpNode* theIterExp,
                             ShaderExpNode* theCancelExp,
                             ShaderNode* theStmt)
{
  myBaseExp = theBaseExp;
  myIterExp = theIterExp;
  myCancelExp = theCancelExp;
  myStmt = theStmt;
  myBlockDepth = getCurrentBlockDepth();
}

ShaderForNode::~ShaderForNode()
{
  delete myBaseExp;
  delete myIterExp;
  delete myCancelExp;
  delete myStmt;
}
     
void ShaderForNode::print(bool indent)
{
  if (indent)
    printSpaces(2 * myBlockDepth);
  cout << "for (";
  myBaseExp->print(false);
  cout << "; ";
  myIterExp->print(false);
  cout << "; ";
  myCancelExp->print(false);
  cout << ")" << endl;
  myStmt->print();
}

void ShaderForNode::execute(Texture3DContext& context)
{
  Value* temp1;
  Value* temp2;
  Value* temp3;
  
  temp1 = myBaseExp->evaluate(context);        // we need this return value
  delete temp1;                         // just to be able to clean up!
  
  temp2 = myIterExp->evaluate(context);
  int condition = (int)*temp2;
  delete temp2;
  
  while (condition != 0) {
    myStmt->execute(context);
    temp3 = myCancelExp->evaluate(context);    // we need this return value
    delete temp3;                       // just to be able to clean up!
    temp2 = myIterExp->evaluate(context);
    condition = (int)*temp2;
    delete temp2;
  }    
}
