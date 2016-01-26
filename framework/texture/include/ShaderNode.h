/*
 * ShaderNode.h
 *
 * Base class for interpreting the SL's parse tree
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
 *  $Id: ShaderNode.h,v 1.6 1996/06/06 11:49:48 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShaderNode_H
#define _ShaderNode_H

#include "booga/base/Value.h"
#include "booga/base/SymTable.h"
#include "booga/base/RCString.h"
#include "booga/base/List.h"
#include "booga/object/Texture3DContext.h"
#include "booga/base/StaticInit.h"
#include "booga/base/AbstractPixmap.h"

class ShaderFunction;

class ShaderNode {
public:
  virtual ~ShaderNode();
  virtual void print(bool indent = true) = 0;
  virtual void execute(Texture3DContext& context) = 0;
  virtual void printValues();
  void printSpaces(int times);

  static void init();
  static void initFunctionScope();
  static int getCurrentBlockDepth();
  static SymTable<RCString, Value>* getCurrentScope();
  static List<SymTable<RCString, Value>*>* getScopes();
  static SymTable<RCString, AbstractPixmap*>* getPixmaps();
  static void enterBlock();
  static void leaveBlock();
  static bool isFatalError();
  static void setFatalError(bool enable = true);

  // do proper initialisation of static members.
  static void initClass();
  
protected:
  static bool ourFatalErrorFlag;
  static int ourBlockDepth;
  static int ourLineNumber;
  static List<SymTable<RCString, Value>*>* ourScopes;
  static SymTable<RCString, ShaderFunction*>* ourFunctions;
  static SymTable<RCString, AbstractPixmap*>* ourPixmaps;
};

//_______________________________________________________________INLINES

inline int ShaderNode::getCurrentBlockDepth()
{
  return ourBlockDepth;
}

inline SymTable<RCString, Value>* ShaderNode::getCurrentScope()
{
  return ourScopes->item(0);
}

inline List<SymTable<RCString, Value>*>* ShaderNode::getScopes()
{
  return ourScopes;
}

inline SymTable<RCString, AbstractPixmap*>* ShaderNode::getPixmaps()
{
  return ourPixmaps;
}

//_______________________________ ensure initialisation of class ShaderNode

  declareInitStatics(ShaderNode);

#endif
