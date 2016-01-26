/*
 * $RCSfile: MultiFileStore.h,v $
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
 *  $Id: MultiFileStore.h,v 1.9 1996/12/06 14:55:24 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _MultiFileStore_H
#define _MultiFileStore_H

#include <fstream>
#include "booga/base/SymTable.h"
#include "booga/base/RCString.h"
#include "booga/component/DocumentStore.h"

//_____________________________________________________________________ MultiFileStore

class MultiFileStore : public DocumentStore {
  //declareRTTI(MultiFileStore);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  MultiFileStore(const RCString& filename="");

private:
  MultiFileStore(const MultiFileStore&);             // No copies.

public:
  virtual ~MultiFileStore();

private:
  MultiFileStore& operator=(const MultiFileStore&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class MultiFileStore
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class BaseClass
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void beginDocument(const RCString& documentName, 
                             const RCString& extension);
  virtual RCString endDocument();
  virtual void includeDocument(const RCString& documentName, 
                               const RCString& extension);

  virtual std::ostream& os();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  RCString myFilename;        // filename of 'root' file
  RCString myCurrFilename;    // filename of current output file
  RCString myDocumentName; 
  std::ofstream myOs;              // current output file
  std::stringstream *myInclude;      // temporary stream for include statements
  std::stringstream *myBody;         // temporary stream for document body
  SymTable<RCString,int> *myIncludeFiles; // remember included files
};

//______________________________________________________________________ INLINES

#endif // _MultiFileStore_H

