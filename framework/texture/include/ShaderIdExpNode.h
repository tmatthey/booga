/*
 * ShaderIdExpNode.h
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
 *  $Id: ShaderIdExpNode.h,v 1.4 1996/04/18 14:31:03 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShaderIdExpNode_H
#define _ShaderIdExpNode_H

#include "booga/texture/ShaderExpNode.h"

#include "booga/base/Value.h"
#include "booga/base/SymTable.h"
#include "booga/base/List.h"
#include "booga/base/RCString.h"

class ShaderIdExpNode : public ShaderExpNode {

public:
  ShaderIdExpNode(ShaderIdExpNode* theIdNode);
  ShaderIdExpNode(RCString& errMsg, RCString* theId);
  virtual ~ShaderIdExpNode();
  bool lookupTextureAttributes(RCString* theId);
  virtual void print(bool indent);
  virtual void execute(Texture3DContext& context);
  virtual Value* evaluate(Texture3DContext& context);
  void evaluateTextureAttributes(Texture3DContext& context);
  
  RCString* getName();

private:
  RCString* myId;
  Value* myValue;
  int myBlockDepth;
};

#endif
