/*
 * ShaderCompExpNode.h
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
 *  $Id: ShaderCompExpNode.h,v 1.4 1996/04/18 14:30:53 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShaderCompExpNode_H
#define _ShaderCompExpNode_H

#include "booga/texture/ShaderExpNode.h"

class ShaderCompExpNode : public ShaderExpNode {
 
public:
  ShaderCompExpNode(char* theOperator, ShaderExpNode* theOp1, ShaderExpNode* theOp2); 
  virtual ~ShaderCompExpNode();
  virtual void print(bool indent);
  virtual void execute(Texture3DContext& context);

  virtual Value* evaluate(Texture3DContext& context);

private:
  char* myOperator;
  ShaderExpNode* myOp1;
  ShaderExpNode* myOp2;
  int myBlockDepth;
};

#endif
