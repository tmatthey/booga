/*
 * ShaderVecValueNode.h
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
 *  $Id: ShaderVecValueNode.h,v 1.3 1996/04/18 14:31:32 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShaderVecValueNode_H
#define _ShaderVecValueNode_H

#include "booga/texture/ShaderExpNode.h"

class ShaderVecValueNode : public ShaderExpNode {

public:
  ShaderVecValueNode(ShaderExpNode* v1, ShaderExpNode* v2, ShaderExpNode* v3);
  ~ShaderVecValueNode();
  virtual void print(bool indent);
  virtual void execute(Texture3DContext& context);
  virtual Value* evaluate(Texture3DContext& context);

private:
  ShaderExpNode* myV1;
  ShaderExpNode* myV2;
  ShaderExpNode* myV3;
  int myBlockDepth;
};

#endif


