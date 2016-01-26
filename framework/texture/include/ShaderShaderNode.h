/*
 * ShaderShaderNode.h
 *
 * Copyright (C) 1996, Thomas Teuscher <teuscher@iam.unibe.ch>
 *                     University of Berne, Switzerland
 *
 * All rights reserved.
 *
 * This software may be freely copied, modified, and redistributed
 * provided that this copyright notice is preserved on all copies.
 *
 * You may not distribute this software, in whole or in part, as part of
 * any commercial product without the express consent of the authors.
 *
 * There is no warranty or other guarantee of fitness of this software
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: ShaderShaderNode.h,v 1.2 1996/06/06 11:49:50 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShaderShaderNode_H
#define _ShaderShaderNode_H

#include "booga/texture/ShaderNode.h"
#include "booga/texture/ShaderProgNode.h"
#include "booga/texture/ShaderExpNode.h"

class ShaderShaderNode : public ShaderNode {
public:
  ShaderShaderNode(List<ShaderExpNode*>* arguments);
  virtual ~ShaderShaderNode();
  virtual void print(bool indent);
  virtual void execute(Texture3DContext& context);

private:
  bool isFirstPass() const;
  void setFirstPass(bool flag);
  
private:
  int myBlockDepth;
  ShaderProgNode* myParseTree;
  List<ShaderExpNode*>* myArguments;
  bool myIsFirstPass;
};

//______________________________________________________________________ INLINES

inline bool ShaderShaderNode::isFirstPass() const
{
  return myIsFirstPass;
}

inline void ShaderShaderNode::setFirstPass(bool flag)
{
   myIsFirstPass = flag;
}


#endif

