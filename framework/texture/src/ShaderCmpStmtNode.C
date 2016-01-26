/*
 * ShaderCmpStmtNode.C
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
 *  $Id: ShaderCmpStmtNode.C,v 1.3 1996/04/18 14:30:50 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <iostream.h>
#include "booga/texture/ShaderCmpStmtNode.h"

ShaderCmpStmtNode::ShaderCmpStmtNode(const ShaderCmpStmtNode& theCmpStmt)
{
  myDecls = theCmpStmt.myDecls;
  myStmts = theCmpStmt.myStmts;
  myBlockDepth = theCmpStmt.myBlockDepth;
  myLocalScope = theCmpStmt.myLocalScope;
}

ShaderCmpStmtNode::ShaderCmpStmtNode(List<ShaderNode*>* theDecls,
                                     List<ShaderNode*>* theStmts)
{
  myDecls = theDecls;
  myStmts = theStmts;
  myBlockDepth = getCurrentBlockDepth();
  myLocalScope = getCurrentScope();
}


ShaderCmpStmtNode::~ShaderCmpStmtNode()
{
  if (myDecls != NULL) {
    for (register long i = 0; i < myDecls->count(); i++)
      delete myDecls->item(i);
    delete myDecls;
  }
  
  if (myStmts != NULL) {
    for (register long i = 0; i < myStmts->count(); i++)
      delete myStmts->item(i);
    delete myStmts;
  }
    
  delete myLocalScope;
}

void ShaderCmpStmtNode::print(bool indent)
{
  if (indent)
    printSpaces(2 * myBlockDepth - 2);
  cout << "{" << endl;
  if (myDecls)
    for (register long i = 0; i < myDecls->count(); i++) {
      myDecls->item(i)->print();
    }
  if (myStmts)
    for (register long i = 0; i < myStmts->count(); i++) {
      myStmts->item(i)->print();
      cout << ";" << endl;
    }
  if (indent)  
    printSpaces(2 * myBlockDepth - 2);
  cout << "}";
}

void ShaderCmpStmtNode::execute(Texture3DContext& context)
{
  ourScopes->prepend(myLocalScope);

  if (myDecls != NULL)
    for (register long i = 0; i < myDecls->count(); i++)
      myDecls->item(i)->execute(context);

  if (myStmts != NULL)
    for (register long i = 0; i < myStmts->count(); i++)
      myStmts->item(i)->execute(context);

  ourScopes->remove(0);
}

void ShaderCmpStmtNode::printValues()
{
  ourScopes->prepend(myLocalScope);
  cout << "Variables in first Scope:" << endl;
  if (myDecls)
    for (register long i = 0; i < myDecls->count(); i++)
      myDecls->item(i)->printValues();
  ourScopes->remove(0);
}
