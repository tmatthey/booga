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
 *  $Id: ImportBSDL3.C,v 1.3 1996/12/06 16:44:48 collison Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "ImportBSDL3.h"
#include "booga/object/World3D.h"
#include "booga/component/BSDL3DParser.h"
#include "booga/component/BSDLWriter.h"
#include "GDBStore.h"

//_____________________________________________________________________ ImportBSDL3

implementRTTI(ImportBSDL3, GDBOperation);

ImportBSDL3::ImportBSDL3(DataBase& aDB,
                         GDBDataType* sourceType, GDBRepType* sourceRep,
                         GDBDataType* targetType, GDBRepType* targetRep) :
GDBOperation(aDB, RCString("BSDL3 Importer"),
             sourceType, sourceRep, targetType, targetRep),
myFilename(""),
myWorld(NULL)
{
}

ImportBSDL3::ImportBSDL3(Prototype aPrototype) :
GDBOperation(aPrototype),
myFilename(""),
myWorld(NULL)
{
}

Persistent* ImportBSDL3::newInstance() {
  return new ImportBSDL3(aPrototype);
}

void ImportBSDL3::setFilename(const RCString& filename) {
  myFilename = filename;
}

void ImportBSDL3::setWorld3D(World3D* world3D) {
  myWorld = world3D;
}

bool ImportBSDL3::doExecute() {
  if (myWorld == NULL) {
    // 
    // Read scene from file
    //
    BSDL3DParser parser;
    parser.setFilename(myFilename);
    parser.execute(myWorld);
  }
  //
  // Write BSDLFormat to database.
  //
  if (myTarget == NULL) {
    // this case is not implemented yet
    ostrstream os;
    os << "[ExportBSDL::doExecute] has no target (sorry can't handle this case yet)";
    Report::recoverable(os);
    return false;
  }
  GDBStore gdbStore(myTarget->getDataBase());
  BSDLWriter writer(gdbStore);
  writer.execute(myWorld);
  return true;
}
