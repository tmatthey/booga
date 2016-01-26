/*
 * ShaderVecValueNode.C
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
 *  $Id: ShaderVecValueNode.C,v 1.3 1996/04/18 14:31:31 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream.h>
#include "booga/texture/ShaderVecValueNode.h"
     
ShaderVecValueNode::ShaderVecValueNode(ShaderExpNode* v1,
                                       ShaderExpNode* v2,
                                       ShaderExpNode* v3)
{
  myV1 = v1;
  myV2 = v2;
  myV3 = v3;
  myBlockDepth = getCurrentBlockDepth();
}

ShaderVecValueNode::~ShaderVecValueNode()
{
  delete myV1;
  delete myV2;
  delete myV3;
}

void ShaderVecValueNode::print(bool indent)
{
  if (indent)
    printSpaces(2 * myBlockDepth);
  cout << "[";
  myV1->print(false);
  cout << ", ";
  myV2->print(false);
  cout << ", ";
  myV3->print(false);
  cout << "]";
}

void ShaderVecValueNode::execute(Texture3DContext&)
{}

Value* ShaderVecValueNode::evaluate(Texture3DContext& context)
{
  Value* temp1 = myV1->evaluate(context);
  Value* temp2 = myV2->evaluate(context);
  Value* temp3 = myV3->evaluate(context);    

  Vector3D newVector = Vector3D((Real)*temp1,
                                (Real)*temp2,
                                (Real)*temp3);

  delete temp1;
  delete temp2;
  delete temp3;
  return new Value(newVector);
}
