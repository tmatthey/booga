/*
 * $RCSfile: PixiWriter.h,v $
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
 *  $Id: PixiWriter.h,v 1.5 1996/08/01 12:00:34 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _PixiWriter_H
#define _PixiWriter_H

#include "booga/component/Pixmap2DWriter.h"

//___________________________________________________________________ PixiWriter

class PixiWriter : public Pixmap2DWriter {
declareRTTI(PixiWriter);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PixiWriter(const RCString& filename="", Type traversalType=FIRST);
  // PixiWriter(const PixiWriter&);          // Use default version.

public:
  // virtual ~PixiWriter();                  // Use default version.

private:
  PixiWriter& operator=(const PixiWriter&);  // No assignments.  

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Pixmap2DWriter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  bool save(const AbstractFile& ofs, const Pixmap2D* pixi) const;
};

#endif // _PixiWriter_H
