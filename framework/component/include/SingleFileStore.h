/*
 * $RCSfile: SingleFileStore.h,v $
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
 *  $Id: SingleFileStore.h,v 1.8 1997/09/19 07:14:51 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _SingleFileStore_H
#define _SingleFileStore_H
#ifdef SVR4
#include <unistd.h>  // STDOUT_FILENO
#endif
#include <fstream.h>
#include "booga/base/RCString.h"
#include "booga/component/DocumentStore.h"

//_____________________________________________________________________ SingleFileStore

class SingleFileStore : public DocumentStore {
// declareRTTI(SingleFileStore);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  SingleFileStore(const RCString& filename="");

private:
  SingleFileStore(const SingleFileStore&);             // No copies.

public:
  virtual ~SingleFileStore();                

private:
  SingleFileStore& operator=(const SingleFileStore&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class SingleFileStore
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
  virtual ostream& os() { return myOs; }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  RCString myFilename;
  RCString myDocumentName;
  ofstream myOs;
};

//______________________________________________________________________ INLINES

#endif // _SingleFileStore_H

