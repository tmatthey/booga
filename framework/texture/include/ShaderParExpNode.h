/*
 * ShaderParExpNode.h
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
 *  $Id: ShaderParExpNode.h,v 1.3 1996/04/18 14:31:18 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShaderParExpNode_H
#define _ShaderParExpNode_H

#include "booga/texture/ShaderExpNode.h"

class ShaderParExpNode : public ShaderExpNode {

public:
  ShaderParExpNode(ShaderExpNode* theExp);
  virtual ~ShaderParExpNode();
  virtual void print(bool indent);
  virtual void execute(Texture3DContext& context);
  virtual Value* evaluate(Texture3DContext& context);

private:
  ShaderExpNode* myExp;
  int myBlockDepth;
};

#endif

