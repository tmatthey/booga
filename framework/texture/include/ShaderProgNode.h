/*
 * ShaderProgNode.h
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
 *  $Id: ShaderProgNode.h,v 1.5 1996/04/18 14:40:00 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShaderProgNode_H
#define _ShaderProgNode_H

#include "booga/base/Color.h"
#include "booga/base/List.h"
#include "booga/texture/ShaderNode.h"

class ShaderProgNode : public ShaderNode {
public:
  ShaderProgNode(ShaderProgNode* theProg);
  ShaderProgNode(ShaderNode* theHead, ShaderNode* theCmpStmt); 
  virtual ~ShaderProgNode();
  virtual void print(bool indent);
  virtual void execute(Texture3DContext& context);
  void overwriteDefaults(const List<Value*>* theParams, Texture3DContext& context);
  void printValues();
  List<Value*>* createParameters();
  
private:
  ShaderNode* myHead;
  ShaderNode* myCmpStmt;
  SymTable<RCString, Value>* myLocalScope;
};

#endif

