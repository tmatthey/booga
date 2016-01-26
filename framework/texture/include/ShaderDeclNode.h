/*
 * ShaderDeclNode.h
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
 *  $Id: ShaderDeclNode.h,v 1.4 1996/04/18 14:30:54 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShaderDeclNode_H
#define _ShaderDeclNode_H

#include "booga/base/Value.h"
#include "booga/base/Color.h"
#include "booga/base/RCString.h"
//#include "booga/base/Name.h"
#include "booga/base/Report.h"
#include "booga/texture/ShaderNode.h"
#include "booga/texture/ShaderExpNode.h"

struct NVPair {
  NVPair(RCString* theName, ShaderExpNode* theExpr);
  ~NVPair();
  RCString* name;
  ShaderExpNode* expr;
};


class ShaderDeclNode : public ShaderNode {
public:
  ShaderDeclNode(); 
  ShaderDeclNode(RCString& warnMsg, RCString* theValidType, List<NVPair*>* theDeclList);
  virtual ~ShaderDeclNode();
  virtual void print(bool indent);
  virtual void execute(Texture3DContext& context);
  void overwriteDefaults(const Value& theParameterValue);
  void printParamDecls();
  void printValues();
  Value* createValue();

private:
  void insertValues(RCString& warnMsg);

private:
  int myBlockDepth;  
  RCString* myValidType;
  List<NVPair*>* myDeclList;
};

#endif
