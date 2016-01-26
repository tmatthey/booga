/*
 * ShaderAssExpNode.h
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
 *  $Id: ShaderAssExpNode.h,v 1.4 1996/04/18 14:30:50 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShaderAssExpNode_H
#define _ShaderAssExpNode_H

#include "booga/texture/ShaderExpNode.h"
#include "booga/texture/ShaderIdExpNode.h"

class ShaderAssExpNode : public ShaderExpNode {
 
public:
  ShaderAssExpNode(ShaderIdExpNode* theOp1, ShaderExpNode* theOp2); 
  virtual ~ShaderAssExpNode();
  virtual void print(bool indent);
  virtual void execute(Texture3DContext& context);
  virtual Value* evaluate(Texture3DContext& context);

private:
  void evaluateTextureAttributes(const RCString& theName, Texture3DContext& context);

private:
  ShaderIdExpNode* myOp1;
  ShaderExpNode* myOp2;
  int myBlockDepth;
};

#endif



