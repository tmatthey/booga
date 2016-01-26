/*
 * ShaderRealValueNode.C
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
 *  $Id: ShaderRealValueNode.C,v 1.4 1996/04/18 14:31:22 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include "booga/texture/ShaderRealValueNode.h"
     
ShaderRealValueNode::ShaderRealValueNode(Real theValue)
{
  myValue = theValue;
  myBlockDepth = getCurrentBlockDepth();
}

void ShaderRealValueNode::print(bool indent)
{
  if (indent)
    printSpaces(2 * myBlockDepth);
  std::cout << myValue;
}

void ShaderRealValueNode::execute(Texture3DContext&)
{}

Value* ShaderRealValueNode::evaluate(Texture3DContext&)
{
  return new Value(myValue);
}



