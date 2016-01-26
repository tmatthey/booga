/*
 * ShaderIfThenElseNode.h
 *
 * Copyright (C) 1995-96, Thomas Teuscher <teuscher@iam.unibe.ch>
 *                        University of Berne, Switzerland
 *
 * All rights reserved.
 *
 * This software may be freely copied, modIfThenElseied and redistributed
 * provided that this copyright note be preserved on all copies.
 * 
 * You may not distribute this software, in whole or in part, as part
 * of any commercial product without the express consent of the author.
 *
 * There is no warranty or other guarantee of fitness of this software
 * for any purpose. It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: ShaderIfThenElseNode.h,v 1.5 1996/06/06 11:49:45 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShaderIfThenElseNode_H
#define _ShaderIfThenElseNode_H

#include "booga/texture/ShaderNode.h"
#include "booga/texture/ShaderExpNode.h"

class ShaderIfThenElseNode : public ShaderNode {

public:
  ShaderIfThenElseNode(ShaderExpNode* theExp, ShaderNode* theThenStmt,
                       ShaderNode* theElseStmt);
  virtual ~ShaderIfThenElseNode();
  virtual void print(bool indent);
  virtual void execute(Texture3DContext& context);

private:
  ShaderExpNode* myExp;
  ShaderNode* myThenStmt;
  ShaderNode* myElseStmt;
  int myBlockDepth;
};

#endif

