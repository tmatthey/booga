/*
 * PixmapGenerator.h
 *
 * Copyright (C) 1995, Stephan Amann <amann@iam.unibe.ch>
 *                     Christoph Streit <streit@iam.unibe.ch>
 *                     University of Berne, Switzerland
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
 *  $Id: PixmapGenerator.h,v 1.3 1995/08/16 16:04:37 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PixmapGenerator_H
#define _PixmapGenerator_H

#include "booga/base/AbstractPixmap.h"
#include "booga/base/MPixmapExemplar.h"

//______________________________________________________________ PixmapGenerator

class PixmapGenerator : public MPixmapExemplar {
public:
  PixmapGenerator();
  // virtual ~PixmapGenerator();  // Use default version.

  virtual AbstractPixmap* generate(const AbstractPixmap* pm) = 0;
  // Create a new AbstractPixmap based upon some (whatsoever) 
  // computations on pm.

private:
  PixmapGenerator(const PixmapGenerator&);	           // No copies.
  PixmapGenerator& operator=(const PixmapGenerator&);	  // No assignments.
};

#endif // _PixmapGenerator_H

