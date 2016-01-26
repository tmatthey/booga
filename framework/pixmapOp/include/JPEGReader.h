/*
 * JPEGReader.h
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
 *  $Id: JPEGReader.h,v 1.2 1996/05/03 13:27:58 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#ifndef _JPEGReader_H
#define _JPEGReader_H

#include "booga/base/StaticInit.h"
#include "booga/pixmapOp/ImageReader.h"

//____________________________________________________________________JPEGReader

class JPEGReader : public ImageReader {
useInitExemplar(JPEGReader);
// enable Initialization of exemplar

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  JPEGReader(Exemplar);
  JPEGReader(const JPEGReader& );             // No copies.
  
public:
  // virtual ~JPEGReader();                   // Use default version.

private:
  JPEGReader& operator=(const JPEGReader& );  // No assignments.
  AbstractPixmap* read(FILE* fs);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class JPEGReader
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class ImageReader  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  virtual AbstractPixmap* read(const AbstractFile& ifs);
};

declareInitExemplar(JPEGReader);

#endif // _JPEGReader_H
