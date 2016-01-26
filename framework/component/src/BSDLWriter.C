/*
 * $RCSfile: BSDLWriter.C,v $
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
 *  $Id: BSDLWriter.C,v 1.16 1997/09/19 07:13:55 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
//_____________________________________________________________________ BSDLWriter


#include <sstream>  // STDOUT_FILENO

#include "booga/object/World3D.h"
#include "booga/object/Shared3D.h"
#include "booga/object/Texture3D.h"
#include "booga/object/Shared2D.h"
#include "booga/object/World2D.h"
#include "booga/object/Texture2D.h"
#include "booga/component/BSDLWriter.h"

//_____________________________________________________________ BSDLWriter

implementRTTI(BSDLWriter, MakeableHandler);

BSDLWriter::BSDLWriter(DocumentStore& docuStore) 
: myIndent(0), myDS(&docuStore), myDefinedNames(1000)
{}

BSDLWriter::~BSDLWriter() {
}

//
// Warning: Consumes (deletes) the List given to the function
//
void BSDLWriter::printParameters(List<Value*>* parameters) {
  int count = parameters->count();
  if (count > 0) {
    myDS->os() << " ";
    if (count > 1) myDS->os() << "(";
    for(long i=0; i < parameters->count(); i++) {
      if (i!=0) myDS->os() << ", ";
      myDS->os() << *parameters->item(i);
      delete parameters->item(i);
    }
    if (count > 1) myDS->os() << ")";
  }
  //
  // destroy the ParameterList
  //
  delete parameters;
  parameters = NULL;
}

void BSDLWriter::incIndent() {
  myIndent++;
}

void BSDLWriter::decIndent() {
  myIndent--;
}

void BSDLWriter::newLineIndent() {
  myDS->os() << std::endl;
  int i;
  for(i=0; i<myIndent*2; i++) {
    myDS->os() << " ";
  }
}

void BSDLWriter::incBracketLevel() {
  myNeedBracket.append(0); // number of items on new level = 0
  // only draw bracket when this number increases
}

void BSDLWriter::openingBracket() {
  int level = myNeedBracket.count()-1;
  if (level >= 0) {
    if (myNeedBracket.item(level) == 0) {
      myDS->os() << " {";
      incIndent();
    }
    myNeedBracket.item(level)+=1;
  }
}

void BSDLWriter::closingBracket() {
  int level = myNeedBracket.count()-1;
  if (level >= 0) {
    if (myNeedBracket.item(level) > 0) {
      decIndent();
      newLineIndent();
      myDS->os() << "}";
    }
    myNeedBracket.remove(level);
  }
}

void BSDLWriter::execute(Makeable* rootMakeable) {
  myNeedBracket.removeAll();
  myDefinedNames.removeAll();
  myDoDefinitionsMode = true;
   
  dispatch(rootMakeable);
}

void BSDLWriter::handle(Makeable* obj) {
  if (obj == NULL) {
    Report::warning("[BSDLWriter::handle] can not handle NULL object");
    return;
  }
  dispatch(obj);
}

void BSDLWriter::dispatch(Makeable* obj) {
  if (dynamic_cast<Shared3D*>(obj) != NULL) { visit(dynamic_cast<Shared3D*>(obj)); return; }
  if (dynamic_cast<Shared2D*>(obj) != NULL) { visit(dynamic_cast<Shared2D*>(obj)); return; }
  if (dynamic_cast<Texture3D*>(obj) != NULL) { visit(dynamic_cast<Texture3D*>(obj)); return; }
  if (dynamic_cast<Texture2D*>(obj) != NULL) { visit(dynamic_cast<Texture2D*>(obj)); return; }
  if (dynamic_cast<World3D*>(obj) != NULL) { visit(dynamic_cast<World3D*>(obj)); return; }
  if (dynamic_cast<World2D*>(obj) != NULL) { visit(dynamic_cast<World2D*>(obj)); return; }
  visit(obj);
}

void BSDLWriter::visit(Makeable *obj) {
  if (myDoDefinitionsMode) {
    obj->iterateAttributes(this); // traverse to objects that need to be defined
  }
  else { // instantiate objects  
    openingBracket();

    // keyword
    newLineIndent();  
    RCString keyword = obj->getKeyword();
    if (!keyword.isEmpty()) {
      myDS->os() << keyword;
    }
  
    // parameters
    List<Value*>* parameters = obj->createParameters();
    printParameters(parameters);

    // recursivley handle attributes
    incBracketLevel();
    obj->iterateAttributes(this);
    closingBracket();

    myDS->os() << ";";
  }
}

void BSDLWriter::visit(Shared3D *obj) {
  if (myDoDefinitionsMode) {
    RCString name(obj->getTypeName());
    RCString aliasName;
    if (myDefinedNames.lookup(name, aliasName)) {
      return; // allready defined -> don't define again
    }
    
    obj->iterateAttributes(this); // traverse to objects that need to be defined
    //
    // now as subobjects are defined: Define current Shared
    //
    myDoDefinitionsMode = false; // switch to instantiations

    myDS->beginDocument(name, "obj3");
    newLineIndent();
    myDS->os() << "using 3D;";
    newLineIndent();
    myDS->os() << "define " << name << " ";
    obj->iterateAttributes(this);
    newLineIndent();
    RCString newName = myDS->endDocument();
    obj->setTypeName(newName);
    myDefinedNames.insert(name, newName);
    if (newName != name) {
      myDefinedNames.insert(newName, newName);
    }

    myDoDefinitionsMode = true;  // switch back to definition mode?
  }
  else {  // instantiate a shared
    openingBracket();

    newLineIndent();  
    RCString keyword = obj->getKeyword();
    if (!keyword.isEmpty()) {
      RCString aliasName;
      if (myDefinedNames.lookup(keyword, aliasName)) { // if is defined
        myDS->includeDocument(aliasName, "obj3"); // use aliasName for aliasing
        myDS->os() << aliasName;

        List<Value*>* parameters = obj->createParameters();
        printParameters(parameters);

        //
        // instantiation of shared
        //
        incBracketLevel();
        RCString instanceName(obj->getName());
        if (!instanceName.isEmpty()) {
          openingBracket();
          RCString quoteName(RCString("\"") + instanceName + RCString("\""));
          newLineIndent();
          myDS->os() << "name " << quoteName << ";";
        }
        obj->Object3D::iterateAttributes(this);
        closingBracket();
      }
      else {
        // something went wrong
        std::stringstream os;
        os << "[BSDLWriter::visit] Shared3D " << aliasName
           << " not yet defined";
        Report::recoverable(os);
      }
    }
    myDS->os() << ";";
  }
}


void BSDLWriter::visit(Shared2D *obj) {
  if (myDoDefinitionsMode) {
    RCString name(obj->getTypeName());
    RCString aliasName;
    if (myDefinedNames.lookup(name, aliasName)) {
      return; // allready defined -> don't define again
    }
    
    obj->iterateAttributes(this); // traverse to objects that need to be defined
    //
    // now as subobjects are defined: Define current Shared
    //
    myDoDefinitionsMode = false; // switch to instantiations

    myDS->beginDocument(name, "obj3");
    newLineIndent();
    myDS->os() << "using 2D;";
    newLineIndent();
    myDS->os() << "define " << name << " ";
    obj->iterateAttributes(this);
    newLineIndent();
    RCString newName = myDS->endDocument();
    obj->setTypeName(newName);
    myDefinedNames.insert(name, newName);
    if (newName != name) {
      myDefinedNames.insert(newName, newName);
    }

    myDoDefinitionsMode = true;  // switch back to definition mode?
  }
  else {  // instantiate a shared
    openingBracket();

    newLineIndent();  
    RCString keyword = obj->getKeyword();
    if (!keyword.isEmpty()) {
      RCString aliasName;
      if (myDefinedNames.lookup(keyword, aliasName)) { // if is defined
        myDS->includeDocument(aliasName, "obj2"); // use aliasName for aliasing
        myDS->os() << aliasName;

        List<Value*>* parameters = obj->createParameters();
        printParameters(parameters);

        //
        // instantiation of shared
        //
        incBracketLevel();
        RCString instanceName(obj->getName());
        if (!instanceName.isEmpty()) {
          openingBracket();
          RCString quoteName(RCString("\"") + instanceName + RCString("\""));
          newLineIndent();
          myDS->os() << "name " << quoteName << ";";
        }
        obj->Object2D::iterateAttributes(this);
        closingBracket();
      }
      else {
        // something went wrong
        std::stringstream os;
        os << "[BSDLWriter::visit] Shared2D " << aliasName
           << " not yet defined";
        Report::recoverable(os);
      }
    }
    myDS->os() << ";";
  }
}

void BSDLWriter::visit(Texture3D *obj) {
  if (myDoDefinitionsMode) {
    RCString name(obj->getName());
    RCString aliasName;
    if (myDefinedNames.lookup(name, aliasName)) {
      return; // allready defined -> don't define again
    }

    obj->iterateAttributes(this); // traverse to objects that need to be defined
    //
    // now as subobjects are defined: Define current Texture
    //

    if (!name.isEmpty() && name != obj->getKeyword()) {
      // texture seems to have a real name
      myDoDefinitionsMode = false; // switch to instantiations

      myDS->beginDocument(name, "mat3");
      newLineIndent();
      myDS->os() << "using 3D;";
      newLineIndent();
      myDS->os() << "define " << obj->getName() << " ";
      myDS->os() << obj->getKeyword();
      printParameters(obj->createParameters());
      incBracketLevel();
      obj->iterateAttributes(this);
      closingBracket();
      myDS->os() << ";";
      newLineIndent();
      RCString newName = myDS->endDocument();
      myDefinedNames.insert(name, newName);
      if (newName != name) {
        myDefinedNames.insert(newName, newName);
      }

      myDoDefinitionsMode = true;  // switch back to definition mode?
    }
  }
  else {
    openingBracket(); // matches closing bracket in higher level function

    RCString name(obj->getName());
    if (name.isEmpty() || name == obj->getKeyword()) { 
      // texture that has not been defined with a name
      visit((Makeable*) obj); // do the whole definition of the texture
      return;
    }
    //
    // Texture has a name:
    // just do instantiation of the previously defined texture
    //
    RCString aliasName;
    if (!myDefinedNames.lookup(name, aliasName)) {
      // something went wrong
      std::stringstream os;
      os << "[BSDLWriter::visit] Texture3D " << name
         << " not yet defined";
      Report::recoverable(os);
      return;
    }

    newLineIndent();
    myDS->includeDocument(aliasName, "mat3"); // allow name aliasing
    myDS->os() << aliasName;
    myDS->os() << ";";
  }
}

void BSDLWriter::visit(Texture2D *obj) {
  if (myDoDefinitionsMode) {
    RCString name(obj->getName());
    RCString aliasName;
    if (myDefinedNames.lookup(name, aliasName)) {
      return; // allready defined -> don't define again
    }

    obj->iterateAttributes(this); // traverse to objects that need to be defined
    //
    // now as subobjects are defined: Define current Texture
    //

    if (!name.isEmpty() && name != obj->getKeyword()) {
      // texture seems to have a real name
      myDoDefinitionsMode = false; // switch to instantiations

      myDS->beginDocument(name, "mat2");
      newLineIndent();
      myDS->os() << "using 2D;";
      newLineIndent();
      myDS->os() << "define " << obj->getName() << " ";
      myDS->os() << obj->getKeyword();
      printParameters(obj->createParameters());
      incBracketLevel();
      obj->iterateAttributes(this);
      myDS->os() << ";";
      closingBracket();
      newLineIndent();
      RCString newName = myDS->endDocument();
      myDefinedNames.insert(name, newName);
      if (newName != name) {
        myDefinedNames.insert(newName, newName);
      }

      myDoDefinitionsMode = true;  // switch back to definition mode?
    }
  }
  else {
    openingBracket(); // matches closing bracket in higher level function

    RCString name(obj->getName());
    if (name.isEmpty() || name == obj->getKeyword()) { 
      // texture that has not been defined with a name
      visit((Makeable*) obj); // do the whole definition of the texture
      return;
    }
    //
    // Texture has a name:
    // just do instantiation of the previously defined texture
    //
    RCString aliasName;
    if (!myDefinedNames.lookup(name, aliasName)) {
      // something went wrong
      std::stringstream os;
      os << "[BSDLWriter::visit] Texture2D " << name
         << " not yet defined";
      Report::recoverable(os);
      return;
    }

    newLineIndent();
    myDS->includeDocument(aliasName, "mat2"); // allow name aliasing
    myDS->os() << aliasName;
    myDS->os() << ";";
  }
}

void BSDLWriter::visit(World3D *obj) {
  if (myDoDefinitionsMode) {
    obj->iterateAttributes(this); // traverse to objects that need to be defined
    //
    // now as subobjects are defined: Define current World
    //
    myDoDefinitionsMode = false; // switch to instantiations

    RCString name(obj->getName());
    myDS->beginDocument(name, "bsdl3");
    newLineIndent();
    myDS->os() << "using 3D;";
    newLineIndent();
    obj->iterateAttributes(this);
    newLineIndent();
    RCString newName = myDS->endDocument();
    obj->setName(newName);
    myDefinedNames.insert(name, newName);
    if (newName != name) {
      myDefinedNames.insert(newName, newName);
    }

    myDoDefinitionsMode = true;  // switch back to definition mode?
  }
}

void BSDLWriter::visit(World2D *obj) {
  if (myDoDefinitionsMode) {
    obj->iterateAttributes(this); // traverse to objects that need to be defined
    //
    // now as subobjects are defined: Define current World
    //
    myDoDefinitionsMode = false; // switch to instantiations

    RCString name(obj->getName());
    myDS->beginDocument(name, "bsdl2");
    newLineIndent();
    myDS->os() << "using 2D;";
    newLineIndent();
    obj->iterateAttributes(this);
    newLineIndent();
    RCString newName = myDS->endDocument();
    obj->setName(newName);
    myDefinedNames.insert(name, newName);
    if (newName != name) {
      myDefinedNames.insert(newName, newName);
    }

    myDoDefinitionsMode = true;  // switch back to definition mode?
  }
}
