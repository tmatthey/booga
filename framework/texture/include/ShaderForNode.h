/*
 * ShaderForNode.h
 *
 * Copyright (C) 1995 Thomas Teuscher <teuscher@iam.unibe.ch>
 *                    University of Berne Switzerland
 *
 * All rights reserved.
 *
 * This software may be freely copied, modForied and redistributed
 * provided that this copyright note be preserved on all copies.
 * 
 * You may not distribute this software, in whole or in part, as part
 * of any commercial product without the express consent of the author.
 *
 * There is no warranty or other guarantee of fitness of this software
 * for any purpose. It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: ShaderForNode.h,v 1.4 1996/04/18 14:30:56 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShaderForNode_H
#define _ShaderForNode_H

#include "booga/texture/ShaderNode.h"
#include "booga/texture/ShaderExpNode.h"

class ShaderForNode : public ShaderNode {

public:
  ShaderForNode(ShaderExpNode* theBaseExp, ShaderExpNode* theIterExp,
                ShaderExpNode* theCancelExp, ShaderNode* theStmt);
  virtual ~ShaderForNode();
  virtual void print(bool indent);
  virtual void execute(Texture3DContext& context);

private:
  ShaderExpNode* myBaseExp;
  ShaderExpNode* myIterExp;
  ShaderExpNode* myCancelExp;
  ShaderNode* myStmt;
  int myBlockDepth;
};

#endif

