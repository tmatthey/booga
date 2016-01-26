/*
 * $RCSfile: Antialiaser.h,v $
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
 *  $Id: Antialiaser.h,v 1.5 1996/08/02 08:42:04 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Antialiaser_H
#define _Antialiaser_H

#include "booga/base/MPixmapExemplar.h"
#include "booga/component/Operation3DTo2D.h"

class Renderer;
class AbtractPixmap;

//__________________________________________________________________ Antialiaser

class Antialiaser : public Operation3DTo2D, public MPixmapExemplar {
declareRTTI(Antialiaser);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Antialiaser();
  // Antialiaser(const Antialiaser&);             // Use default version.

public:
  // virtual ~Antialiaser();                      // Use default version.

public:
  // Antialiaser& operator=(const Antialiaser&);  // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Antialiaser
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setRenderer(Renderer* renderer);
  
protected:
  AbstractPixmap* performRendering();
  // Execute the renderer object and create a pixmap as a result.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool preprocessing();
  virtual bool postprocessing();

private:
  virtual void cleanupAfterFailure();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  Renderer* myRenderer;
  AbstractPixmap* myResultPixmap;
};

//______________________________________________________________________ INLINES

inline void Antialiaser::setRenderer(Renderer* renderer)
{
  myRenderer = renderer;
}

#endif // _Antialiaser_H

