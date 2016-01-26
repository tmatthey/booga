/*
 * ShaderCmpStmtNode.h
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
 *  $Id: ShaderCmpStmtNode.h,v 1.3 1996/04/18 14:30:51 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShaderCmpStmtNode_H
#define _ShaderCmpStmtNode_H

#include "booga/texture/ShaderNode.h"
#include "booga/base/List.h"

class ShaderCmpStmtNode : public ShaderNode {
public:
  ShaderCmpStmtNode(const ShaderCmpStmtNode& theCmpStmt);
  ShaderCmpStmtNode(List<ShaderNode*>* theDecls, List<ShaderNode*>* theStmts); 
  virtual ~ShaderCmpStmtNode();
  virtual void print(bool indent);
  virtual void execute(Texture3DContext& context);
  void printValues();

private:
  int myBlockDepth;  
  List<ShaderNode*>* myDecls;
  List<ShaderNode*>* myStmts;
  SymTable<RCString, Value>* myLocalScope;
};

#endif


