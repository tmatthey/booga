/*
 * $RCSfile: MPixmapExemplar.h,v $
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
 *  $Id: MPixmapExemplar.h,v 1.2 1996/08/30 13:53:22 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _MPixmapExemplar_H
#define _MPixmapExemplar_H

#include "booga/base/AbstractPixmap.h"

//_____________________________________________________________  MPixmapExemplar

class MPixmapExemplar {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  MPixmapExemplar();
private:
  MPixmapExemplar(const MPixmapExemplar&);	         // No copies.

public:
  virtual ~MPixmapExemplar();

private:
  MPixmapExemplar& operator=(const MPixmapExemplar&); // No assignments.


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class MPixmapExemplar
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void adoptPixmapExemplar(AbstractPixmap* pm);
  void setResolution(int resX, int resY);
  
protected: 
  AbstractPixmap* createPixmap() const;
  AbstractPixmap* createPixmap(int resX, int resY) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  AbstractPixmap* myPixmapExemplar;
  int myResX, myResY;
};

//_____________________________________________________________________  INLINES

inline void MPixmapExemplar::setResolution(int resX, int resY)
{
  myResX = resX;
  myResY = resY;
}

#endif // _MPixmapExemplar_H
