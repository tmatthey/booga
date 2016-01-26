/*
 * $RCSfile: GDBExport.C,v $
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
 *  $Id: GDBExport.C,v 1.2 1997/02/20 09:30:32 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Report.h"
#include "booga/graphicsdb/GDBExport.h"
#include "booga/graphicsdb/GDBDataType.h"
#include "booga/graphicsdb/GDBRepType.h"

//_____________________________________________________________________ GDBExport

implementRTTI(GDBExport, GDBOperation);

GDBExport::GDBExport(DataBase& aDB, 
                     GDBDataType* sourceType, GDBRepType* sourceRep,
                     GDBDataType* targetType, GDBRepType* targetRep) :
GDBOperation(aDB, RCString("Exporter"),
             sourceType, sourceRep, targetType, targetRep)
{
  myTraversal = new GDBTraversal();
  myTraversal->setOperation(this);
  myTraversal->setTraverseRelation(GDBTraversal::PARTS);
  myTraversal->setSingleVisit();
  myTraversal->setPostorder();
}

GDBExport::GDBExport(Prototype aPrototype) :
GDBOperation(aPrototype)
{
  myTraversal = new GDBTraversal();
  myTraversal->setOperation(this);
  myTraversal->setTraverseRelation(GDBTraversal::PARTS);
  myTraversal->setSingleVisit();
  myTraversal->setPostorder();
}

GDBExport::~GDBExport() {
  delete myTraversal;
  myTraversal = NULL;
}


bool GDBExport::doExecute() {
  myFilenames.removeAll();
  RCString formatName = mySource->getFormat()->getName();
  if ((formatName == "BSDL3") || (formatName == "BSDL2")) {
    myFilenames.insert(0, mySource->getNameIdFormat());
    myFile.open(myFilenames.item(0).chars(),ios::out);
    myTraversal->traverse(mySource);
    myFile.close();
  }
  else {
    myTraversal->traverse(mySource);
  }
  return true;
}

GDBTraversal::Result GDBExport::announceVisit(GDBData *gdbData) {
  RCString formatName = gdbData->getFormat()->getName();
  if (formatName != RCString("BSDL3") && formatName != RCString("BSDL2")) {
      ostrstream ss;
      ss << "[GDBExport::export] non BSDL object encountered " 
         << gdbData->getPOId() << " " << gdbData->getName() << " . Ignoring";
      Report::hint(ss);
      return GDBTraversal::PRUNE;
  }
  return GDBTraversal::CONTINUE;
}

GDBTraversal::Result GDBExport::visit(GDBData* gdbData) {
  RCString formatName = gdbData->getFormat()->getName();
  if (formatName == RCString("BSDL3") || formatName == RCString("BSDL2")) {
    myFile << gdbData->getData();
    ostrstream ss;
    ss << "[GDBExport::export] exporting BSDL Object " 
       << gdbData->getPOId() << " " << gdbData->getName();
    Report::hint(ss);
    return GDBTraversal::CONTINUE;
  } 
  else {
    myFilenames.append(gdbData->getNameIdFormat());
    fstream file;
    if (gdbData->getBinaryData() != NULL && gdbData->getBinaryData()->getBuffer() != NULL) {
      file.open(myFilenames.item(myFilenames.count()-1).chars(),ios::out);
      file.write(gdbData->getBinaryData()->getBuffer(),
                 gdbData->getBinaryData()->getSize());
      file.close();
      ostrstream ss;
      ss << "[GDBExport::export] exporting object " 
         << gdbData->getPOId() << " " << gdbData->getName();
      Report::hint(ss);
    }
  }
  return GDBTraversal::PRUNE;
}

RCString GDBExport::getFilename() {
  if (myFilenames.count() > 0) {
    return myFilenames.item(0);
  }
  return RCString("");
}

List<RCString> GDBExport::getFilenames() {
  return myFilenames;
}
Persistent* GDBExport::newInstance()
{
  return new GDBExport(aPrototype);
}
