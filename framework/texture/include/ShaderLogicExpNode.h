/*
 * ShaderLogicExpNode.h
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
 *  $Id: ShaderLogicExpNode.h,v 1.4 1996/04/18 14:31:15 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShaderLogicExpNode_H
#define _ShaderLogicExpNode_H

#include "booga/texture/ShaderExpNode.h"

class ShaderLogicExpNode : public ShaderExpNode {
 
public:
  ShaderLogicExpNode(char* theOperator, ShaderExpNode* theOp1, ShaderExpNode* theOp2); 
  ShaderLogicExpNode(char* theOperator, ShaderExpNode* theOp);
  virtual ~ShaderLogicExpNode();
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
