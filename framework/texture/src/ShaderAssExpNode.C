/*
 * ShaderAssExpNode.C
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
 *  $Id: ShaderAssExpNode.C,v 1.5 1996/04/18 14:39:55 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include "booga/texture/ShaderAssExpNode.h"
#include "booga/object/Ray3D.h"
     
ShaderAssExpNode::ShaderAssExpNode(ShaderIdExpNode* theOp1,
                                   ShaderExpNode* theOp2)
{
  myOp1 = theOp1;
  myOp2 = theOp2;
  myBlockDepth = getCurrentBlockDepth();
}

ShaderAssExpNode::~ShaderAssExpNode()
{
  delete myOp1;
  myOp1 = NULL;
  delete myOp2;
  myOp1 = NULL;
}

void ShaderAssExpNode::print(bool indent)
{
  if (indent)
    printSpaces(2 * myBlockDepth);
  myOp1->print(false);
  std::cout << " = ";
  myOp2->print(false);
}

void ShaderAssExpNode::execute(Texture3DContext& context)
{
  Value* dummyValue = evaluate(context);
  delete dummyValue;
}

Value* ShaderAssExpNode::evaluate(Texture3DContext& context)
{
  RCString theName = *myOp1->getName();
  Value* tempVal = myOp2->evaluate(context);
  int i = 0;  
  while((i < ourScopes->count()) &&
        (!ourScopes->item(i)->findAndReplace(theName, *tempVal)))
    i++;
  delete tempVal;

  // we can't find it in neither scope --> it's a texture attribute.
  if (i == ourScopes->count()) 
    evaluateTextureAttributes(theName, context);
    
  return new Value(1);  // pro forma
}

void ShaderAssExpNode::evaluateTextureAttributes(const RCString& theName,
                                                 Texture3DContext& context)
{
  if (theName == "Col") {
    Value* temp = myOp2->evaluate(context);
    Vector3D vec = (Vector3D)*temp;
    context.setColor(vec);
    delete temp;
  }
  else
  if (theName == "Illum") {
    Value* temp = myOp2->evaluate(context);
    Vector3D vec = (Vector3D)*temp;   
    context.setIllumination(vec);
    delete temp;
  }
  else
  if (theName == "LDir") {
    Value* temp = myOp2->evaluate(context);
    Vector3D vec = (Vector3D)*temp;
    context.setLightDirection(vec);
    delete temp;
  }
  else
  if (theName == "LDist") {
    Value* temp = myOp2->evaluate(context);
    Real val = (Real)*temp;
    context.setLightDistance(val);
    delete temp;
  }
  else
  if (theName == "Eye") {
    Value* temp = myOp2->evaluate(context);
    Vector3D vec = (Vector3D)*temp;
    context.setIncidencePosition(vec);
    delete temp;
  }
  else
//  if (theName == "RDir")  // not allowed!!!
  if (theName == "WPos") {
    Value* temp = myOp2->evaluate(context);
    Vector3D vec = (Vector3D)*temp;
    context.setPositionWCS(vec);
    delete temp;
  }
  else
  if (theName == "WNorm") {
    Value* temp = myOp2->evaluate(context);
    Vector3D vec = (Vector3D)*temp;
    context.setNormalWCS(vec);
    delete temp;
  }
  else
  if (theName == "OPos") {
    Value* temp = myOp2->evaluate(context);
    Vector3D vec = (Vector3D)*temp;
    context.setPositionOCS(vec);
    delete temp;
  }
  else
  if (theName == "ONorm") {
    Value* temp = myOp2->evaluate(context);
    Vector3D vec = (Vector3D)*temp;
    context.setNormalOCS(vec);
    delete temp;
  }
  else
  if (theName == "TPos") {
    Value* temp = myOp2->evaluate(context);
    Vector3D vec = (Vector3D)*temp;
    context.setPositionTCS(vec);
    delete temp;
  }
  else
  if (theName == "TNorm") {
    Value* temp = myOp2->evaluate(context);
    Vector3D vec = (Vector3D)*temp;
    context.setNormalTCS(vec);
    delete temp;
  }
}
