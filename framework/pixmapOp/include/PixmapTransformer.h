/*
 * PixmapTransformer.h
 *
 * Base class for all the pixmap operations.
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
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: PixmapTransformer.h,v 1.4 1996/04/14 13:07:01 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PixmapTransformer_H
#define _PixmapTransformer_H

class AbstractPixmap;

//____________________________________________________________ PixmapTransformer

class PixmapTransformer {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PixmapTransformer();
private:
  PixmapTransformer(const PixmapTransformer&);             // No copies.

public:
  virtual ~PixmapTransformer();

private:  
  PixmapTransformer& operator=(const PixmapTransformer&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class PixmapTransformer
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void apply(AbstractPixmap* pm) = 0;
  // Apply some computations on pm and change it.
};

#endif // _PixmapTransformer_H

