/*
 * $RCSfile: GIFReader.h,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: GIFReader.h,v 1.1 1996/07/19 14:22:36 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GIFReader_H
#define _GIFReader_H


#include "booga/base/StaticInit.h"
#include "booga/pixmapOp/ImageReader.h"

//____________________________________________________________________ GIFReader

class GIFReader : public ImageReader {
useInitExemplar(GIFReader);
// enable Initialization of exemplar

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  GIFReader(Exemplar);
  GIFReader(const GIFReader&);              // No copies.
  
public:
  // virtual ~GIFReader();                  // Use default version.

private:
  GIFReader& operator=(const GIFReader& );  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class ImageReader  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  virtual AbstractPixmap* read(const AbstractFile& ifs);
  AbstractPixmap* read(FILE* fs);
};

declareInitExemplar(GIFReader);

#endif // _GIFReader_H

