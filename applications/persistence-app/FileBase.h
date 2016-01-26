/*
 * $RCSfile: FileBase.h
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
 *  $Id: FileBase.h,v 1.10 1996/12/06 16:44:03 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _FileBase_H
#define _FileBase_H

#include <fstream>
#include "DataBase.h"
#include "POId.h"
#include "booga/base/RCString.h"

class Persistent;
//_____________________________________________________________________ FileBase

class FileBase : public DataBase {
declareRTTI(FileBase);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  FileBase(char *dirPath);
private:
  FileBase(const FileBase&);             // No copies.

public:
  virtual ~FileBase();

private:
  FileBase& operator=(const FileBase&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class FileBase
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  void readDBInfo();
  void writeDBInfo();
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class DataBase
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual POId getUniquePOId();

  virtual int write(Persistent* p);
  virtual Persistent* load(const POId& id);

  virtual int setObjectName(char* name, PRef<Persistent>& refAny);
  virtual PRef<Persistent> lookupObject(char* name);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  RCString myDirPath;
  RCString myFilename;
  RCString myInfoFilename;
  PObjectId myOIdCount;
  POId myCurrPOId;
  std::fstream myFile;
  std::fstream myInfoFile;
  // myNamedObjects(RCString,POId);
};

//______________________________________________________________________ INLINES

#endif // _FileBase_H

