/*
 * PPMReader.h
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
 *  $Id: PPMReader.h,v 1.1 1996/05/03 11:39:11 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#ifndef _PPMReader_H
#define _PPMReader_H

#include "booga/base/StaticInit.h"
#include "booga/pixmapOp/ImageReader.h"

//_____________________________________________________________________PPMReader

class PPMReader : public ImageReader {
useInitExemplar(PPMReader);
// enable Initialization of exemplar

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  PPMReader(Exemplar);
  PPMReader(const PPMReader& );             // No copies.
  
public:
  // virtual ~PPMReader();                  // Use default version.

private:
  PPMReader& operator=(const PPMReader& );  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class PPMReader
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  void readComment(ifstream& ifs) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class ImageReader  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  virtual AbstractPixmap* read(ifstream& ifs);
};

declareInitExemplar(PPMReader);

#endif // _PPMReader_H
