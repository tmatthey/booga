/*
 * $RCSfile: ImportBSDL3.C,v $
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
 *  $Id: ImportBSDL3.C,v 1.3 1997/02/20 09:31:13 collison Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/object/World3D.h"
#include "booga/component/BSDL3DParser.h"
#include "booga/component/BSDL2DParser.h"
#include "booga/component/Parser3D.h"
#include "booga/component/BSDLWriter.h"
#include "booga/graphicsdb/ImportBSDL3.h"
#include "booga/graphicsdb/GDBStore.h"
#include "booga/graphicsdb/GDBData.h"
#include "booga/graphicsdb/GDBDataType.h"
#include "booga/graphicsdb/GDBRepType.h"

//_____________________________________________________________________ ImportBSDL3

implementRTTI(ImportBSDL3, GDBOperation);

ImportBSDL3::ImportBSDL3(DataBase& aDB,
                         GDBDataType* sourceType, GDBRepType* sourceRep,
                         GDBDataType* targetType, GDBRepType* targetRep) :
GDBOperation(aDB, RCString("BSDL3 Importer"),
             sourceType, sourceRep, targetType, targetRep),
myFilename(""),
myWorld3D(NULL),
myWorld2D(NULL)
{
}

ImportBSDL3::ImportBSDL3(Prototype aPrototype) :
GDBOperation(aPrototype),
myFilename(""),
myWorld3D(NULL),
myWorld2D(NULL)
{
}

Persistent* ImportBSDL3::newInstance() {
  return new ImportBSDL3(aPrototype);
}

void ImportBSDL3::setFilename(const RCString& filename) {
  myFilename = filename;
}

void ImportBSDL3::setWorld3D(World3D* world3D) {
  myWorld3D = world3D;
  myWorld2D = NULL;
}

void ImportBSDL3::setWorld2D(World2D* world2D) {
  myWorld2D = world2D;
  myWorld3D = NULL;
}

bool ImportBSDL3::doExecute() {
  if (myWorld2D == NULL && myWorld3D == NULL) {
    // 
    // Read scene from file
    //
    if (myFilename.find(".bsdl2") >= 0) {
      BSDL2DParser parser;
      parser.setFilename(myFilename);
      parser.execute(myWorld2D);
    }
    else { // assume it's a bsdl3 file
      Parser3D parser;
      parser.setFilename(myFilename);
      parser.execute(myWorld3D);
    }
  }
  //
  // Write BSDLFormat to database.
  //
  if (myTarget == NULL) {
    // this case is not implemented yet
    std::stringstream os;
    os << "[ExportBSDL::doExecute] has no target (sorry can't handle this case yet)";
    Report::recoverable(os);
    return false;
  }
  GDBStore gdbStore(myTarget->getDataBase());
  BSDLWriter writer(gdbStore);
  if (myWorld2D != NULL) {
    writer.execute(myWorld2D);
  }
  else {
    writer.execute(myWorld3D);
  }
  return true;
}
