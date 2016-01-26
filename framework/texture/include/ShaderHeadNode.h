/*
 * ShaderHeadNode.h
 *
 * Copyright (C) 1996 Thomas Teuscher <teuscher@iam.unibe.ch>
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
 *  $Id: ShaderHeadNode.h,v 1.3 1996/04/18 14:39:58 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShaderHeadNode_H
#define _ShaderHeadNode_H

#include "booga/texture/ShaderNode.h"
#include "booga/base/List.h"

class ShaderHeadNode : public ShaderNode {
public:
  ShaderHeadNode(RCString* theShaderType, RCString* theName, List<ShaderNode*>* theParamDecls); 
  virtual ~ShaderHeadNode();
  virtual void print(bool indent);
  virtual void execute(Texture3DContext& context);
  void overwriteDefaults(const List<Value*>* theArguments);
  
  void printValues();
  List<Value*>* createParameters();
  
private:
  void setWarningFlag(bool val);
  bool isWarningFlagTrue();
  
private:
  RCString* myShaderType;
  RCString* myName;
  RCString* myFileName;
  List<ShaderNode*>* myParamDecls;
  bool myWarningFlag;
};

inline void ShaderHeadNode::setWarningFlag(bool val)
{
  myWarningFlag = val;
}

inline bool ShaderHeadNode::isWarningFlagTrue()
{
  return myWarningFlag;
}
#endif

