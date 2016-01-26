/*
 * ShaderIfNode.h
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
 *  $Id: ShaderIfNode.h,v 1.4 1996/04/18 14:31:05 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShaderIfNode_H
#define _ShaderIfNode_H

#include "booga/texture/ShaderNode.h"
#include "booga/texture/ShaderExpNode.h"

class ShaderIfNode : public ShaderNode {

public:
  ShaderIfNode(ShaderExpNode* theExp, ShaderNode* theStmt);
  virtual ~ShaderIfNode();
  virtual void print(bool indent);
  virtual void execute(Texture3DContext& context);

private:
  ShaderExpNode* myExp;
  ShaderNode* myStmt;
  int myBlockDepth;
};

#endif

