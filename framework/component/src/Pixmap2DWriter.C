/*
 * $RCSfile: Pixmap2DWriter.C,v $
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
 *  $Id: Pixmap2DWriter.C,v 1.9 1997/09/19 07:14:27 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include <fstream>   
#include "booga/base/Report.h"
#include "booga/component/Pixmap2DWriter.h"

//______________________________________________________________ Pixmap2DWriter

implementRTTI(Pixmap2DWriter, AbstractPixmapOperation);

Pixmap2DWriter::Pixmap2DWriter(const RCString& filename, Type traversalType)
: AbstractPixmapOperation(traversalType), 
  myFilename(filename)
{
  myCurrentPixmap = 0;
}

bool Pixmap2DWriter::operateOnPixmap2D(Pixmap2D* obj)
{

  AbstractFile ofs;
  //
  // If myFilename is empty, we try to open stdout for writing
  //
  if (myFilename.isEmpty()) {
    //
    // Write only to stdout, if traversal type is FIRST!
    //
    if (myTraversalType == FIRST) {
      ofs.attach(STDOUT_FILENO);
    } else {
      Report::warning("[Pixmap2DWriter::operateOnPixmap2D]" 
		      " can't write multiple Pixmaps to stdout");
      return false;
    }
  }
  else {
    //
    // filename is not empty, so we have to open a regular file:
    // Build file name ...
    //
    std::stringstream filename(myFilename.chars());
    if (myTraversalType != FIRST)
      filename << "." << myCurrentPixmap << ".";
    
    //
    // try to open file and save image
    //
    ofs.attach(filename.str().c_str());
  }
  return save(ofs, obj);
}

