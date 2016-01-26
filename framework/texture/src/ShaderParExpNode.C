/*
 * ShaderParExpNode.C
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
 *  $Id: ShaderParExpNode.C,v 1.3 1996/04/18 14:31:18 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include "booga/texture/ShaderParExpNode.h"
     
ShaderParExpNode::ShaderParExpNode(ShaderExpNode* theExp )
{
  myExp = theExp;
  myBlockDepth = getCurrentBlockDepth();
}

ShaderParExpNode::~ShaderParExpNode()
{
  delete myExp;
}

void ShaderParExpNode::print(bool indent)
{
  if (indent)
    printSpaces(2 * myBlockDepth);
  std::cout << "(";
  myExp->print(false);
  std::cout << ")";
}

void ShaderParExpNode::execute(Texture3DContext&)
{}

Value* ShaderParExpNode::evaluate(Texture3DContext& context)
{
  return myExp->evaluate(context);
}
