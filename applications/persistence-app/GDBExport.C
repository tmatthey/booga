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
 *  $Id: GDBExport.C,v 1.2 1996/12/06 16:44:15 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "GDBExport.h"
#include "GDBDataType.h"
#include "GDBRepType.h"
#include "booga/base/Report.h"


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
  if (mySource->getFormat()->getName() == "BSDL3") {
    myFilenames.insert(0, mySource->getNameIdFormat());
    myFile.open(myFilenames.item(0).chars(),std::ios::out);
    myTraversal->traverse(mySource);
    myFile.close();
  }
  else {
    myTraversal->traverse(mySource);
  }
  return true;
}

GDBTraversal::Result GDBExport::announceVisit(GDBData *gdbData) {
  if (gdbData->getFormat()->getName() != RCString("BSDL3")) {
      std::stringstream ss;
      ss << "[GDBExport::export] non BSDL3 object encountered " 
         << gdbData->getPOId() << " " << gdbData->getName() << " . Ignoring";
      Report::hint(ss);
      return GDBTraversal::PRUNE;
  }
  return GDBTraversal::CONTINUE;
}

GDBTraversal::Result GDBExport::visit(GDBData* gdbData) {
  if (gdbData->getFormat()->getName() == RCString("BSDL3")) {
    myFile << gdbData->getData();
    std::stringstream ss;
    ss << "[GDBExport::export] exporting BSDL Object " 
       << gdbData->getPOId() << " " << gdbData->getName();
    Report::hint(ss);
    return GDBTraversal::CONTINUE;
  } 
  else {
    myFilenames.append(gdbData->getNameIdFormat());
    std::fstream file;
    if (gdbData->getBinaryData() != NULL && gdbData->getBinaryData()->getBuffer() != NULL) {
      file.open(myFilenames.item(myFilenames.count()-1).chars(),std::ios::out);
      file.write(gdbData->getBinaryData()->getBuffer(),
                 gdbData->getBinaryData()->getSize());
      file.close();
      std::stringstream ss;
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
