/*
 * ShaderIdExpNode.C
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
 *  $Id: ShaderIdExpNode.C,v 1.4 1996/04/18 14:31:02 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream.h>
#include "booga/texture/ShaderIdExpNode.h"
#include "booga/object/Ray3D.h"

ShaderIdExpNode::ShaderIdExpNode(ShaderIdExpNode* theIdNode)
{
  myValue = new Value(*theIdNode->myValue);
  myId = new RCString(*theIdNode->myId);
  myBlockDepth = theIdNode->myBlockDepth;
}     

ShaderIdExpNode::ShaderIdExpNode(RCString& errMsg, RCString* theId)
{
  // the Identifier must have been declared somewhere.
  // So let's look for it to assign the correct value to myValue.
  myValue = new Value(0.);
  int i = 0;
  while((i < ourScopes->count()) &&
        (!ourScopes->item(i)->lookup(*theId, *myValue)))
    i++;
    
  // we can't find it in neither scope --> it's a texture attribute. 
  if (i == ourScopes->count()) {
    if (!lookupTextureAttributes(theId)) {
      errMsg = "Unknown Name: " + *theId;
     // although an unknown name is provided we give myId a value
     // to enable the parse tree to be executed anyway.
     // The evaluate() member function will return a 0 Value.
      myId =  new RCString("Unknown");
      delete theId;
    }
    else
      myId = theId;
  }
  else
    myId = theId;
  myBlockDepth = getCurrentBlockDepth();    
}

ShaderIdExpNode::~ShaderIdExpNode()
{
  delete myValue;
  delete myId;
}

bool ShaderIdExpNode::lookupTextureAttributes(RCString* theId)
{
  // we are in the parsing pass. So no Texture3DContext is known yet,
  // and we can not give myValue an "existing" texture attribute value.
  // But of course, we have to accept the name. We will give
  // a pro forma 0 value to myValue.
  
  if (*theId == "LDist") {
    *myValue = Value(0.0);
    return true;
  }
  else
  if ((*theId == "Col") || (*theId == "Illum") || (*theId == "LDir") ||
      (*theId == "Eye") || (*theId == "RDir") || (*theId == "WPos") ||
      (*theId == "WNorm") || (*theId == "OPos") ||(*theId == "ONorm") ||
      (*theId == "TPos") || (*theId == "TNorm")) {
    *myValue = Value(Vector3D(0,0,0)); // pro forma;
    return true;
  }
  else
    return false;
}

void ShaderIdExpNode::print(bool indent)
{
  if (indent)
    printSpaces(2 * myBlockDepth);
  cout << *myId;
}

void ShaderIdExpNode::execute(Texture3DContext&)
{}

Value* ShaderIdExpNode::evaluate(Texture3DContext& context)
{
  // since an identifier's value could have been changed during execution,
  // we first have to update myValue from the SymbolTable.
  int i = 0;
  while((i < ourScopes->count()) &&
        (!ourScopes->item(i)->lookup(*myId, *myValue)))
    i++;
    
  // we can't find it in neither scope --> it's a texture attribute. 
  if (i == ourScopes->count())
    if (context.getWorld() != NULL)       // that means, we are in the
      evaluateTextureAttributes(context);  // execution pass.

  // if it is neither a declared identifier nor a texture attribute
  // we leave the value as it is, namely 0.
  
  return new Value(*myValue);
}

void ShaderIdExpNode::evaluateTextureAttributes(Texture3DContext& context)
{
  if (*myId == "Col")
    *myValue = Value(context.getColor());
  else
  if (*myId == "Illum")
    *myValue = Value(context.getIllumination());
  else
  if (*myId == "LDir")
    *myValue = Value(context.getLightDirection());
  else
  if (*myId == "LDist")
    *myValue = Value(context.getLightDistance());
  else
  if (*myId == "Eye")
    *myValue = Value(context.getIncidencePosition());
  else
  if (*myId == "RDir")
    *myValue = Value(context.getIncidenceRay()->getDirection());
  else
  if (*myId == "WPos")
    *myValue = Value(context.getPositionWCS());
  else
  if (*myId == "WNorm")
    *myValue = Value(context.getNormalWCS());
  else
  if (*myId == "OPos")
    *myValue = Value(context.getPositionOCS());
  else
  if (*myId == "ONorm")
    *myValue = Value(context.getNormalOCS());
  else
  if (*myId == "TPos")
    *myValue = Value(context.getPositionTCS());
  else
  if (*myId == "TNorm")
    *myValue = Value(context.getNormalTCS());
}

RCString* ShaderIdExpNode::getName()
{
  return myId;
}
