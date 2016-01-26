/*
 * PixiReader.C
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
 *  $Id: PixiReader.C,v 1.1 1996/05/03 11:39:01 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#include <string.h>
#include "booga/pixmapOp/PixiReader.h"

//____________________________________________________________________PixiReader

implementInitExemplar(PixiReader);

PixiReader::PixiReader(Exemplar anExemplar)
: ImageReader(anExemplar) 
{}

AbstractPixmap* PixiReader::read(ifstream& ifs)
{
  AbstractPixmap* pm = MPixmapExemplar::createPixmap(1, 1);

  if (pm->load(ifs))		// Can pixi read it ?
    return pm;

  delete pm;
  return NULL;
} 

