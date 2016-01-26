/*
 * $RCSfile: SingleFileStore.C,v $
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
 *  $Id: SingleFileStore.C,v 1.6 1997/09/19 07:14:50 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
#ifdef SVR4
#include <unistd.h>  // STDOUT_FILENO
#endif
#include <fstream>
#include "booga/component/SingleFileStore.h"

//_____________________________________________________________________ SingleFileStore

//implementRTTI(SingleFileStore, DocumentStore);

SingleFileStore::SingleFileStore(const RCString& filename) :
DocumentStore(),
myFilename(filename),
myDocumentName("")
{
  //
  // If myFilename is empty, we try to open stdout for writing
  //
  if (myFilename.isEmpty()) {
    myOs.tie(&std::cout);//->attach(STDOUT_FILENO);
    if (myOs.bad()) {
      Report::warning("[SingleFileStore::SingleFileStore] could not attach to stdout");
      // failed();
      return;
    }
  }
  else {
    //
    // Filename is not empty, so we have to open a regular file:
    // try to open file and save image
    //
    myOs.open(myFilename.chars());
    if (myOs.bad()) {
      Report::warning("[SingleFileStore::SingleFileStore] could not open file named " + 
		      myFilename);
      // failed();
      return;
    }
  }
}

SingleFileStore::~SingleFileStore() {
  if (!myFilename.isEmpty())
    myOs.close();
}

void 
SingleFileStore::beginDocument(const RCString& documentName, 
                               const RCString& )
{  
  myDocumentName = documentName;
}

RCString 
SingleFileStore::endDocument() {
  return myDocumentName;
}

void SingleFileStore::includeDocument(const RCString&, const RCString&) {
}
