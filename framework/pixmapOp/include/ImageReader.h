/*
 * ImageReader.h
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
 *  $Id: ImageReader.h,v 1.1 1996/05/03 11:38:57 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _ImageReader_H
#define _ImageReader_H

#include "booga/base/Exemplar.h"
#include "booga/base/List.h"
#include "booga/base/RCString.h"
#include "booga/base/MPixmapExemplar.h"

class ifstream;

//__________________________________________________________________ ImageReader

class ImageReader : public MPixmapExemplar {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  ImageReader();
protected:
  ImageReader(Exemplar);
private:
  ImageReader(const ImageReader& );            // No copies.

public:
  // virtual ~ImageReader();                   // Use default version.

private:
  ImageReader& operator=(const ImageReader& ); // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class ImageReader
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  static AbstractPixmap* createPixmap(const RCString& filename);
  // Tries to read the file specified by filename
  // and returns NULL on failure or the constructed pixmap if reading 
  // was successful. 
  // The user doesn't have to care about the pixmap type.

private:  
  void registerMe();
  // Registers concrete ImageReader in the list of known readers.

  virtual AbstractPixmap* read(ifstream& ifs) = 0;
  // Tries to read the file. This method depends on the image type
  // and must thus be implemented by each concrete ImageReader.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  static List<ImageReader*>* ourReaders;
  // List of known readers.
};

#endif // _ImageReader_H
