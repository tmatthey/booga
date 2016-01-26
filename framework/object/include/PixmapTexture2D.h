/*
 * $RCSfile: PixmapTexture2D.h,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: PixmapTexture2D.h,v 1.4 1996/08/30 13:53:36 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PixmapTexture2D_H
#define _PixmapTexture2D_H

#include "booga/object/Texture2D.h"

class AbstractPixmap;

//______________________________________________________________ PixmapTexture2D

class PixmapTexture2D : public Texture2D {
declareRTTI(PixmapTexture2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PixmapTexture2D(AbstractPixmap* adoptPixmap);
  PixmapTexture2D(Exemplar);
  PixmapTexture2D(const PixmapTexture2D&);

public:
  virtual ~PixmapTexture2D();

private:
  PixmapTexture2D& operator=(const PixmapTexture2D&); // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class PixmapTexture2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  AbstractPixmap* getPixmap() const;
  AbstractPixmap* orphanPixmap();
  void adoptPixmap(AbstractPixmap* pixmap);
  //
  // Access methods for the pixmap.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Texture2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Texture2D* copy() const;
  virtual void doTexturing(Texture2DContext& context) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  AbstractPixmap* myPixmap;
};

//______________________________________________________________________ INLINES

#endif // _PixmapTexture2D_H

