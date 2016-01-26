/*
 * $RCSfile: GDBExport.h,v $
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
 *  $Id: GDBExport.h,v 1.1 1996/12/11 13:57:48 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GDBExport_H
#define _GDBExport_H

#include <fstream.h>
#include "booga/base/SymTable.h"
#include "booga/graphicsdb/GDBOperation.h"
#include "booga/graphicsdb/GDBData.h"

//_____________________________________________________________________ GDBExport

class GDBExport : public GDBOperation {
declareRTTI(GDBExport);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GDBExport(DataBase& aDB, 
            GDBDataType* sourceType, GDBRepType* sourceRep,
            GDBDataType* targetType, GDBRepType* targetRep);
  GDBExport(Prototype aPrototype);

private:
  GDBExport(const GDBExport&);             // No copies.

public:
  virtual ~GDBExport();                // Use default version.

private:
  GDBExport& operator=(const GDBExport&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GDBExport
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  RCString getFilename();
  List<RCString> getFilenames();
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class GDBOperation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual bool doExecute();
  virtual GDBTraversal::Result announceVisit(GDBData *gdbData);
  virtual GDBTraversal::Result visit(GDBData *gdbData);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Persistent
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
public:
  virtual Persistent* newInstance();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  List<RCString> myFilenames;
  fstream myFile;
};

//______________________________________________________________________ INLINES

#endif // _GDBExport_H
