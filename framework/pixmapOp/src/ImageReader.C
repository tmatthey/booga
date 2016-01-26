/*
 * ImageReader.C
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
 *  $Id: ImageReader.C,v 1.3 1997/09/19 07:14:11 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifdef SVR4
#include <unistd.h>
#endif
#include <fstream.h>
#include <strstream.h>  // ostrstream

#include "booga/base/Report.h"
#include "booga/pixmapOp/ImageReader.h"
   
//__________________________________________________________________ ImageReader

List<ImageReader*>* ImageReader::ourReaders;

/*
 * Dummy constructor is needed!
 */
ImageReader::ImageReader() {}

ImageReader::ImageReader(Exemplar)
{
  registerMe();
}

AbstractPixmap* ImageReader::createPixmap(const RCString& filename)
{
  ifstream ifs;
#ifdef SVR4
  // 
  // Open file if file name is set, else
  // attach stream to stdin.
  //
  if (filename.isEmpty())
    ifs.rdbuf()->attach(STDIN_FILENO);
  else
#endif

#ifdef WIN32
  ifs.open(filename.chars(),ios::binary);
#else
  ifs.open(filename.chars());
#endif

  AbstractPixmap* pixi = NULL;
  if (ourReaders != NULL) 
    for (long i=0; i<ourReaders->count(); i++) {
      if ((pixi = ourReaders->item(i)->read(ifs)) != NULL) 
	break;
      if (ifs.rdbuf()->seekpos(0) != 0) {
	Report::warning("[ImageReader::createPixmap] couldn't reset istream");
	break;
      }
    }

  ifs.close();

  if (pixi == NULL) {
    ostrstream os;
    os << "[ImageReader::createPixmap] couldn't read file ";
    
    if (filename.isEmpty())
      os << "from stdin";
    else
      os << "\"" << filename << "\"";
      
    Report::recoverable(os);
  }
  
  return pixi;
}


void ImageReader::registerMe()
{
  if (ourReaders == NULL)
    ourReaders = new List<ImageReader*>;

  ImageReader* thisOne = (ImageReader*)this;
  ourReaders->append(thisOne);
}
