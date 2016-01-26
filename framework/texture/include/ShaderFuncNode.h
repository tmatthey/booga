/*
 * ShaderFuncNode.h
 *
 * Copyright (C) 1995-96, Thomas Teuscher <teuscher@iam.unibe.ch>
 *                        University of Berne, Switzerland
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
 *  $Id: ShaderFuncNode.h,v 1.5 1996/06/06 11:49:40 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShaderFuncNode_H
#define _ShaderFuncNode_H

#include "booga/texture/ShaderExpNode.h"

class ShaderFunction;

class ShaderFuncNode : public ShaderExpNode {

public:
  ShaderFuncNode(RCString& errMsg, RCString* theName, List<ShaderExpNode*>* theArgs);
  ~ShaderFuncNode();
  virtual void print(bool indent);
  virtual void execute(Texture3DContext& context);
  virtual Value* evaluate(Texture3DContext& context);

private:
  ShaderFunction* myFunction;
  RCString* myName;
  List<ShaderExpNode*>* myArgList;
  int myBlockDepth;
  bool myExeFlag;
};

#endif
