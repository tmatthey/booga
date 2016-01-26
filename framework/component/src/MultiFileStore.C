/*
 * $RCSfile: MultiFileStore.C,v $
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
 *  $Id: MultiFileStore.C,v 1.11 1997/09/19 07:14:22 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
#ifdef SVR4
#include <unistd.h>  // STDOUT_FILENO
#endif
#include <fstream>
#include "booga/component/MultiFileStore.h"

//_____________________________________________________________________ MultiFileStore

//implementRTTI(MultiFileStore, DocumentStore);

MultiFileStore::MultiFileStore(const RCString& filename) 
: DocumentStore(),
  myFilename(filename),
  myCurrFilename(RCString("")),
  myDocumentName(RCString("")),
  myInclude(NULL),
  myBody(NULL),
  myIncludeFiles(NULL)
{
}

MultiFileStore::~MultiFileStore() 
{
  // 
  // close files and free memory
  //
  if (myBody != NULL) {
     endDocument();
  }
  // just to be real sure:
  delete myBody;
  delete myInclude;
  delete myIncludeFiles;
}

void 
MultiFileStore::beginDocument(const RCString& documentName, 
                              const RCString& extension)
{
  if (myBody != NULL) {
    endDocument(); // close current document first if necessary
  }
  //
  // open new file for new document
  //
  if (documentName.isEmpty()) {  // World3D
    myCurrFilename = myFilename;
  }
  else {
    myCurrFilename = documentName + "." + extension;
  }

  myDocumentName = documentName;
  
  if (myCurrFilename.isEmpty()) {
    myOs.tie(&std::cout);
    if (myOs.bad()) {
      Report::warning("[MultiFileStore::beginDocument] could not attach to stdout");
    }
  }
  else {  
    myOs.open(myCurrFilename.chars());
    if (myOs.bad()) {
      Report::warning("[MultiFileStore::beginDocument] could not open file named " + 
        myCurrFilename);
    }
  }
  myOs << "#ifndef " << documentName << "_" << extension << std::endl;
  myOs << "#define " << documentName << "_" << extension << std::endl << std::endl;  
  myIncludeFiles = new SymTable<RCString, int>(128);
  myInclude = new std::stringstream();
  myBody = new std::stringstream();
}

RCString MultiFileStore::endDocument() 
{  
  //
  // write preprocessor include statements to current file
  //
  if (myInclude != NULL) {
    // strstreams may not directly be written to an std::ostream.
    // The only way to copy the content of a stream to another
    // is by accessing the buffer.
    // Accessing the buffer of a strstream freezes the strstream
    // and resets it. The responsability for the buffer is with
    // the caller of str().
    *myInclude << '\0'; // null terminate the strstream buffer!
    const char* tmpStr = myInclude->str().c_str();
    myOs << tmpStr;
    myOs.flush();
    delete tmpStr;

    delete myInclude; 
    myInclude = NULL;
    
    delete myIncludeFiles;
    myIncludeFiles = NULL;
  }
  
  //
  // write the document body to the current file 
  //
  if (myBody != NULL) {
    // see above.
    *myBody << '\0'; // null terminate the strstream buffer!
    const char* tmpStr = myBody->str().c_str();
    myOs << tmpStr;
    myOs.flush();
    delete tmpStr;
        
    delete myBody;
    myBody = NULL;
  }
  
  myOs << std::endl << "#endif" << std::endl;
  if (!myCurrFilename.isEmpty()) {
    myOs.close();
  }
  return myDocumentName;
}

void MultiFileStore::includeDocument(const RCString& documentName, 
                                     const RCString& extension) {
  if (myInclude != NULL) {
    RCString fullName(documentName + "." + extension);
    // 
    // check if this file has allready been included
    //
    int dummy = 1;
    if (!myIncludeFiles->lookup(fullName,dummy)) {
      //
      // generate include statement
      //
      myIncludeFiles->insert(fullName,dummy);
      *myInclude << "#include \"" << fullName << "\"" << std::endl;
    }
  }
}
  
std::ostream& MultiFileStore::os() {
  if (myBody != NULL) {
    return *myBody;
  }
  Report::error("[MultiFileStore::os] no stream");
  exit(1); // fatal error
  return *myBody; // to quiesce compiler
  //
  // only call os() between beginDocument() and endDocument() calls
  //
}

