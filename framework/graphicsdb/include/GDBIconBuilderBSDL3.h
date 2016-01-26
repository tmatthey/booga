/*
 * $RCSfile: GDBIconBuilderBSDL3.h,v $
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
 *  $Id: GDBIconBuilderBSDL3.h,v 1.2 1997/03/21 13:09:11 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GDBIconBuilderBSDL3_H
#define _GDBIconBuilderBSDL3_H

#include "booga/graphicsdb/GDBOperation.h"

//_____________________________________________________________________ GDBIconBuilderBSDL3

class GDBIconBuilderBSDL3 : public GDBOperation {
declareRTTI(GDBIconBuilderBSDL3);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GDBIconBuilderBSDL3(DataBase& aDB, 
    GDBDataType* sourceType, GDBRepType* sourceRep,
    GDBDataType* targetType, GDBRepType* targetRep,
    int xsize=100, int ysize=100);
  GDBIconBuilderBSDL3(Prototype aPrototype);
  
private:
  GDBIconBuilderBSDL3(const GDBIconBuilderBSDL3&);             // No copies.

public:
  virtual ~GDBIconBuilderBSDL3();
  
private:
  GDBIconBuilderBSDL3& operator=(const GDBIconBuilderBSDL3&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GDBIconBuilderBSDL3
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class GDBOperation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual bool doExecute();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Persistent
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  virtual Persistent* newInstance();
 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  int myIconSizeX;
  int myIconSizeY;
};

//______________________________________________________________________ INLINES

#endif // _GDBIconBuilderBSDL3_H

