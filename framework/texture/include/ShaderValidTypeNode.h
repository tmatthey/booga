/*
 * ShaderValidTypeNode.h
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
 *  $Id: ShaderValidTypeNode.h,v 1.3 1996/04/18 14:31:30 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShaderValidTypeNode_H
#define _ShaderValidTypeNode_H

#include "booga/texture/ShaderNode.h"
#include "booga/base/Name.h"

class ShaderValidTypeNode : public ShaderNode {
public:
  ShaderValidTypeNode(Name* theType);
  virtual void print();
  virtual void execute(Texture3DContext& context);

private:
  Name* myType;
};

#endif

