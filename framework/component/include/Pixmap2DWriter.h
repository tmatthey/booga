/*
 * $RCSfile: Pixmap2DWriter.h,v $
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
 *                        University of Berne, Switzerland
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: Pixmap2DWriter.h,v 1.7 1996/08/01 12:00:36 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _Pixmap2DWriter_H
#define _Pixmap2DWriter_H

#include "booga/base/RCString.h"
#include "booga/component/AbstractPixmapOperation.h"
#include "booga/base/fdstream.h"

#include <iostream>

//______________________________________________________________ Pixmap2DWriter

class Pixmap2DWriter : public AbstractPixmapOperation {
declareRTTI(Pixmap2DWriter);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Pixmap2DWriter(const RCString& filename="", Type traversalType=FIRST);
private:
  Pixmap2DWriter(const Pixmap2DWriter&);  // No copies.

public:
  // virtual ~Pixmap2DWriter();
  
private:
  Pixmap2DWriter& operator=(const Pixmap2DWriter&); // No assignment.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Pixmap2DWriter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool save(const AbstractFile& os, const Pixmap2D* pixi) const = 0;
  // Save pixi on os. Returns 1 on success, 0 on failure

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class AbstractPixmapOperation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  virtual bool operateOnPixmap2D(Pixmap2D* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  RCString myFilename;
  long myCurrentPixmap;
};

#endif // _Pixmap2DWriter_H
