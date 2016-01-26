/*
 * $RCSfile: PixiWriter.C,v $
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
 *  $Id: PixiWriter.C,v 1.7 1996/08/01 12:00:33 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/AbstractPixmap.h"
#include "booga/object/Pixmap2D.h"
#include "booga/component/PixiWriter.h"

//________________________________________________________________ PixiWriter

implementRTTI(PixiWriter, Pixmap2DWriter);

PixiWriter::PixiWriter(const RCString& filename, Type traversalType)
: Pixmap2DWriter(filename, traversalType) 
{}

bool PixiWriter::save(const AbstractFile& ofs, const Pixmap2D* pixi) const 
{
  FileSTDOut fs(ofs);
  if (fs.bad()) {
    Report::warning("PixiWriter:can't open file\n");
    return false;
  }
  return pixi->getPixmap()->save(fs);
}  
