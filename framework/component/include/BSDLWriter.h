/*
 * $RCSfile: BSDLWriter.h,v $
 *
 * Copyright (C) 1996, Andrey Collison <collison@iam.unibe.ch>
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
 *  $Id: BSDLWriter.h,v 1.9 1996/10/04 09:45:58 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _BSDLWriter_H
#define _BSDLWriter_H

#include <fstream.h>
#include "booga/base/Value.h"
#include "booga/base/RCString.h"
#include "booga/base/List.h"
#include "booga/base/SymTable.h"
#include "booga/component/DocumentStore.h"
#include "booga/object/MakeableHandler.h"

class World3D;
class World2D;
class Shared3D;
class Shared2D;
class Texture3D;
class Texture2D;

//_____________________________________________________________________ BSDLWriter

class BSDLWriter : public MakeableHandler {
declareRTTI(BSDLWriter);
// enable RTTI support

private:
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  BSDLWriter(DocumentStore& docuStore);
  virtual ~BSDLWriter();

private:
  BSDLWriter(const BSDLWriter&);             // No copies.

public:
  // virtual ~BSDLWriter();                // Use default version.

private:
  BSDLWriter& operator=(const BSDLWriter&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class BSDLWriter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void execute(Makeable* rootMakeable);
private:
  void printParameters(List<Value*>* parameters);
  void incIndent();
  void decIndent();
  void newLineIndent();
  void incBracketLevel();
  void openingBracket();
  void closingBracket();
  
  void dispatch(Makeable* obj);

  void visit(Makeable* obj);
  void visit(World3D* obj);
  void visit(World2D* obj);
  void visit(Shared3D* obj);
  void visit(Shared2D* obj);
  void visit(Texture3D* obj);
  void visit(Texture2D* obj);
    
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class MakeableHandler
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  virtual void handle(Makeable* makeable);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  int myIndent;         // indent levels in text output
  bool myDoDefinitionsMode;
  DocumentStore *myDS;
  List<int> myNeedBracket;
  SymTable<RCString,RCString> myDefinedNames;
};

//______________________________________________________________________ INLINES

#endif // _BSDLWriter_H

