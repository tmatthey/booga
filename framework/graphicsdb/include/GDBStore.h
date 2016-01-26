/*
 * $RCSfile: GDBStore.h
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
 *  $Id: GDBStore.h,v 1.2 1996/12/23 10:57:26 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GDBStore_H
#define _GDBStore_H

#include <fstream>
#include "booga/base/SymTable.h"
#include "booga/base/RCString.h"
#include "booga/component/DocumentStore.h"
#include "booga/persistence/Set.h"
#include "booga/graphicsdb/GDBData.h"

class POId;
class World3D;
class DataBase;


//_____________________________________________________________________ GDBStore

class GDBStore : public DocumentStore {
  //declareRTTI(GDBStore);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GDBStore(DataBase& aDB);

private:
  GDBStore(const GDBStore&);             // No copies.

public:
  virtual ~GDBStore();

private:
  GDBStore& operator=(const GDBStore&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GDBStore
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

private:
GDBData* getGDBDataObj(const RCString& documentName);

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
  DataBase* myDataBase;       // user database
  RCString myFilename;        // filename of 'root' file
  RCString myCurrFilename;    // filename of current output file
  RCString myDocumentName;
  RCString myExtension;
  GDBData* myGDBData;
  std::stringstream *myNewData;      // temporary stream for document body
  Set<PRef<GDBData> > *myNewParts;
  SymTable<RCString, PRef<GDBData> > myPartNames;
};

//______________________________________________________________________ INLINES

#endif // _GDBStore_H

