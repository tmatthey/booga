/*
 * $RCSfile: IconBuilderForBSDL3.h,v $
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
 *  $Id: IconBuilderForBSDL3.h,v 1.4 1996/10/09 14:12:29 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _IconBuilderForBSDL3_H
#define _IconBuilderForBSDL3_H

#include "GDBOperation.h"

//_____________________________________________________________________ IconBuilderForBSDL3

class IconBuilderForBSDL3 : public GDBOperation {
declareRTTI(IconBuilderForBSDL3);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  IconBuilderForBSDL3(RCString inputType, int xsize=100, int ysize=100);
private:
  IconBuilderForBSDL3(const IconBuilderForBSDL3&);             // No copies.

public:
  // virtual ~IconBuilderForBSDL3();                // Use default version.

private:
  IconBuilderForBSDL3& operator=(const IconBuilderForBSDL3&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class IconBuilderForBSDL3
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class GDBOperation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual bool doExecute();
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  int myIconSizeX;
  int myIconSizeY;
};

//______________________________________________________________________ INLINES

#endif // _IconBuilderForBSDL3_H

