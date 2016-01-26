/*
 * $RCSfile: DocumentStore.h,v $
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
 *  $Id: DocumentStore.h,v 1.8 1996/12/06 14:55:19 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _DocumentStore_H
#define _DocumentStore_H

#include <iostream>
#include "booga/base/RTTI.h"
class RCString;

//_____________________________________________________________________ DocumentStore

class DocumentStore {
  declareRTTI(DocumentStore);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  DocumentStore() {}                         // Use default version.
private:
  DocumentStore(const DocumentStore&);             // No copies.

public:
  virtual ~DocumentStore() {}

private:
  DocumentStore& operator=(const DocumentStore&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class DocumentStore
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  //
  // beginDocument() and endDocument return documentName 
  // which may have been renamed by the methods
  // 
  virtual void beginDocument(const RCString& documentName, 
                                 const RCString& extension)=0;
  virtual RCString endDocument()=0;
  virtual void includeDocument(const RCString& documentName,
                               const RCString& extension)=0;
  virtual std::ostream& os()=0;  // output stream to document
  //
  // Warning: only to be used between benginDocument() 
  // and endDocument() calls
  //  

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
};

//______________________________________________________________________ INLINES

#endif // _DocumentStore_H

