/*
 * $RCSfile: PNGWriter.h,v $
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
 *  $Id: PNGWriter.h,v 1.5 1996/08/01 12:00:48 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _PNGWriter_H
#define _PNGWriter_H

#include "booga/component/Pixmap2DWriter.h"

//____________________________________________________________________ PNGWriter

class PNGWriter : public Pixmap2DWriter {
declareRTTI(PNGWriter);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PNGWriter(const RCString& filename="", Type traversalType=FIRST);
  // PNGWriter(const PNGWriter&);          // Use default version.

public:
  // virtual ~PNGWriter();                 // Use default version.

private:
  PNGWriter& operator=(const PNGWriter&);  // No assignments.  
  bool save(FILE* fd, const Pixmap2D* pixi) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Pixmap2DWriter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  bool save(const AbstractFile& ofs, const Pixmap2D* pixi) const;
};

#endif // _PNGWriter_H
