/*
 * ShaderArithExpNode.h
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
 *  $Id: ShaderArithExpNode.h,v 1.3 1996/04/18 14:30:48 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShaderArithExpNode_H
#define _ShaderArithExpNode_H

#include "booga/texture/ShaderExpNode.h"

class ShaderArithExpNode : public ShaderExpNode {
 
public:
  ShaderArithExpNode(char theOperator, ShaderExpNode* theOp1, ShaderExpNode* theOp2); 
  virtual ~ShaderArithExpNode();
  virtual void print(bool indent);
  virtual void execute(Texture3DContext& context);

  virtual Value* evaluate(Texture3DContext& context);

private:
  char myOperator;
  ShaderExpNode* myOp1;
  ShaderExpNode* myOp2;
  int myBlockDepth;
};

#endif


