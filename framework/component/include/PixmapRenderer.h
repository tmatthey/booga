/*
 * $RCSfile: PixmapRenderer.h,v $
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
 *  $Id: PixmapRenderer.h,v 1.8 1996/08/02 08:42:11 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PixmapRenderer_H
#define _PixmapRenderer_H

#include "booga/base/MPixmapExemplar.h"
#include "booga/component/Renderer.h"

//_____________________________________________________________ PixmapRenderer

class PixmapRenderer : public Renderer, public MPixmapExemplar {
declareRTTI(PixmapRenderer);
// declare RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PixmapRenderer();
private:
  PixmapRenderer(const PixmapRenderer&);             // No copies.

public:
  // virtual ~PixmapRenderer();                      // Use default version.

private:
  PixmapRenderer& operator=(const PixmapRenderer&);  // No assignment.

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
  AbstractPixmap* myPixmap;
};

#endif
