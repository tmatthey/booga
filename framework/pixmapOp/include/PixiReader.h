/*
 * PixiReader.h
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
 *  $Id: PixiReader.h,v 1.1 1996/05/03 11:39:02 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _PixiReader_H
#define _PixiReader_H

#include "booga/base/StaticInit.h"
#include "booga/pixmapOp/ImageReader.h"

//____________________________________________________________________PixiReader

class PixiReader : public ImageReader {
useInitExemplar(PixiReader);
// enable Initialization of exemplar

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  PixiReader(Exemplar);
  PixiReader(const PixiReader& );             // No copies.
  
public:
  // virtual ~PixiReader();                   // Use default version.

private:
  PixiReader& operator=(const PixiReader& );  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class ImageReader  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  virtual AbstractPixmap* read(const AbstractFile& ifs);
  AbstractPixmap* read(std::istream& ifs);
};

declareInitExemplar(PixiReader);

#endif // _PixiReader_H
