/*
 * ShaderValidTypeNode.C
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
 *  $Id: ShaderValidTypeNode.C,v 1.3 1996/04/18 14:31:29 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream.h>
#include "booga/texture/ShaderValidTypeNode.h"

ShaderValidTypeNode::ShaderValidTypeNode(Name* theType)
{
  myType = theType;
}

void ShaderValidTypeNode::print()
{
  cout << *myType;
}

void ShaderValidTypeNode::execute(Texture3DContext&)
{}



