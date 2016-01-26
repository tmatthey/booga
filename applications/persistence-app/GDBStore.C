/*
 * $RCSfile: GDBStore.C 
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
 *  $Id: GDBStore.C,v 1.6 1996/12/06 16:44:30 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include <unistd.h>  // STDOUT_FILENO dup()
#include <stdio.h>          // fdopen(), ...
#include <string.h>  // strfind()
#include <sstream>
#include <fstream>
#include "GDBStore.h"
#include "POId.h"
#include "GDBData.h"
#include "booga/component/BSDL3DParser.h"

//_____________________________________________________________________ GDBStore

implementRTTI(GDBStore, DocumentStore);

GDBStore::GDBStore(DataBase& aDB) :
DocumentStore(),
myDataBase(&aDB),
myFilename(""),
myCurrFilename(RCString("")),
myDocumentName(RCString("")),
myGDBData(NULL),
myNewData(NULL),
myPartNames(1024)
{
}

GDBStore::~GDBStore() {
  // 
  // close files and free memory
  //
  if (myNewData != NULL) {
     endDocument();
  }
  // just to be sure
  delete myGDBData;
  delete myNewData;
}

GDBData*
GDBStore::getGDBDataObj(const RCString& documentName) {
  List<RCString>* tokens = documentName.createTokens(RCString("."));
  if (tokens->count() >= 2) {
    PDBId dbId        = atol(tokens->item(tokens->count()-2).chars());
    PObjectId objectId= atol(tokens->item(tokens->count()-1).chars());
    PRef<GDBData> gdbRef(POId(dbId, objectId)); 
    if (gdbRef.getPtr() != NULL) {
      return gdbRef.getPtr();
    }
  } 
  // lookup name in symbol table
  PRef<GDBData> gdbRef;
  if (myPartNames.lookup(documentName,gdbRef)) {
    if (gdbRef.getPtr() != NULL) {
      return gdbRef.getPtr();
    }
  }
  return NULL;
}

void 
GDBStore::beginDocument(const RCString& documentName, 
                              const RCString& extension)
{
  if (myNewData != NULL) {
    endDocument(); // close current document first if necessary
  }
  
  myDocumentName = documentName;
  myExtension = extension;
 
  myNewParts = new Set<PRef<GDBData> >;
  myNewData = new std::stringstream();
}

RCString GDBStore::endDocument() {
  // 
  // if there exists a GDB Object associated to documentName then get it
  //
  RCString oldDocumentName(myDocumentName);
  myGDBData = getGDBDataObj(myDocumentName);

  if (myGDBData == NULL) {
    // we have to create a new GDBObject
    myGDBData = new GDBData(*myDataBase, myDocumentName);
    if (myExtension != "mat") {
      std::stringstream os;
      os <<  myDocumentName 
         << "." << (unsigned long) myGDBData->getPOId().getPDBId()
         << "." << (unsigned long) myGDBData->getPOId().getPObjectId();
      myDocumentName = RCString(os);
    }
    if (myExtension == "mat3") myGDBData->setType("Texture3D");
    else if (myExtension == "obj3") myGDBData->setType("Object3D");
    else if (myExtension == "bsdl3") myGDBData->setType("Scene3D");
    myGDBData->setFormat("BSDL3");
    myPartNames.insert(myDocumentName,PRef<GDBData>(*myGDBData));
  }

  //
  // did the object data change?
  //
  *myNewData << '\0'; // null terminate the strstream buffer!
  const char* data = myNewData->str().c_str(); // freeze the strstream. now caller is responsible for the buf.
  RCString newData(data);
  delete data;

  if (newData != myGDBData->getData() || *myNewParts != myGDBData->getParts()) {
    // yes -> is the object frozen 
    //   yes -> create new object and rename definition!
    //   no  -> write the differences
    int pos = newData.find(RCString("define ") + oldDocumentName); // for Shareds
    if (pos != -1) {
      newData = RCString(newData(0,pos+6) + 
                         myDocumentName +
                         newData(pos+7+oldDocumentName.length(), newData.length()-1));
    } 
    else { // for World
      pos = newData.find(RCString("name \"" + oldDocumentName + "\";"));
      if (pos != -1) {
        newData = RCString(newData(0,pos+5) + 
                         myDocumentName +
                         newData(pos+6+oldDocumentName.length(), newData.length()-1)); 
      }
    }
    myGDBData->setData(newData);
    myGDBData->setParts(*myNewParts);
    myGDBData->markChanged();

    // inform user about writing
    std::stringstream ss;
    ss << "[GDBStore::endDocument()] processed gdbData: " 
       << myDocumentName;
    Report::hint(ss);
  }
  else {
    std::stringstream ss;
    ss << "[GDBStore::endDocument()] unchanged gdbData: " 
       << myDocumentName;
    Report::hint(ss);
  }

  if (myNewData != NULL) {
    delete myNewData;
    myNewData = NULL;
  }
  
  myGDBData = NULL;
  return myDocumentName;
}

void GDBStore::includeDocument(const RCString& documentName, 
                                     const RCString& ) {
  if (myNewParts != NULL) {
    //
    // get associated GDBData
    //
    GDBData* part = getGDBDataObj(documentName);
    if (part == NULL) {
        std::stringstream os;
        os << "[GBDStore::includeDocument] document " << documentName
           << " not found";
        Report::recoverable(os);
        return;
    }
    // add the part
    PRef<GDBData> partRef(*part);
    myNewParts->insertElement(partRef);
  }
}

std::ostream& GDBStore::os() { 
  if (myNewData != NULL) {
    return *myNewData;
  }
  Report::error("[GDBStore::os] no stream");
  exit(1); // fatal error
  //
  // only call os() between beginDocument() and endDocument() calls
  //
}

