/*
 * $RCSfile: ReadImage.C,v $
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
 *  $Id: ReadImage.C,v 1.4 1997/09/19 07:14:41 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
#ifdef SVR4
#include <unistd.h>
#endif
#include <fstream.h>

#include "booga/base/Report.h"
#include "booga/pixmapOp/ImageReaders.h"
#include "booga/object/Aggregate2D.h"
#include "booga/object/Pixmap2D.h"
#include "booga/component/ReadImage.h"
   
//____________________________________________________________________ ReadImage

implementRTTI(ReadImage, Operation2D);

/*
 * Dummy constructor is needed!
 */
ReadImage::ReadImage() {}

void ReadImage::setFilename(const RCString& filename)
{
  myFilename = filename;
}

bool ReadImage::doExecute()
{
  AbstractPixmap* pixi = ImageReader::createPixmap(myFilename);

  if (pixi == NULL) {
    Report::recoverable("[ReadImage::doExecute] could not read image");
    return false;
  }
  else {
    getWorld()->getObjects()->adoptObject(new Pixmap2D(pixi));
    getWorld()->getObjects()->computeBounds();
  }

  return true;
}
