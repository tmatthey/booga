/*
 * $RCSfile: JPEGWriter.h,v $
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
 *  $Id: JPEGWriter.h,v 1.1 1997/08/20 08:53:48 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _JPEGWriter_H
#define _JPEGWriter_H

#include "booga/component/Pixmap2DWriter.h"

//____________________________________________________________________ JPEGWriter

class JPEGWriter : public Pixmap2DWriter {
declareRTTI(JPEGWriter);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  JPEGWriter(const RCString& filename="", Type traversalType=FIRST);
  // JPEGWriter(const JPEGWriter&);          // Use default version.

  void setQuality (int q) { myQuality = q;};
  
private:
  JPEGWriter& operator=(const JPEGWriter&);  // No assignments.  
  bool save(FILE* fd, const Pixmap2D* pixi) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Pixmap2DWriter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  bool save(const AbstractFile& ofs, const Pixmap2D* pixi) const;

private:
  int myQuality;
};

#endif // _JPEGWriter_H
