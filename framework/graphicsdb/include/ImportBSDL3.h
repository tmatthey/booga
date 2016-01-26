/*
 * $RCSfile: ImportBSDL3.h,v $
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
 *  $Id: ImportBSDL3.h,v 1.2 1997/02/20 09:31:23 collison Exp buhlmann $
 * -----------------------------------------------------------------------------
 */

#ifndef _ImportBSDL3_H
#define _ImportBSDL3_H

#include <fstream>
#include "booga/base/SymTable.h"
#include "booga/graphicsdb/GDBOperation.h"
#include "booga/graphicsdb/GDBData.h"

class World3D;
class World2D;
//_____________________________________________________________________ ImportBSDL3

class ImportBSDL3 : public GDBOperation {
declareRTTI(ImportBSDL3);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
ImportBSDL3(DataBase& aDB, GDBDataType* sourceType, GDBRepType* sourceRep,
                           GDBDataType* targetType, GDBRepType* targetRep);
ImportBSDL3(Prototype aPrototype);

private:
  ImportBSDL3(const ImportBSDL3&);             // No copies.

public:
  // virtual ~ImportBSDL3();                // Use default version.

private:
  ImportBSDL3& operator=(const ImportBSDL3&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class ImportBSDL3
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setFilename(const RCString& filename);
  void setWorld3D(World3D* world3D);
  void setWorld2D(World2D* world2D);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class GDBOperation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual bool doExecute();
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Persistent
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
public:
  virtual Persistent* newInstance();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  RCString myFilename;
  World3D* myWorld3D;
  World2D* myWorld2D;
};

//______________________________________________________________________ INLINES

#endif // _ImportBSDL3_H
