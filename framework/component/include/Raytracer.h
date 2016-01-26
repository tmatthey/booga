/*
 * $RCSfile: Raytracer.h,v $
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
 *  $Id: Raytracer.h,v 1.6 1996/09/18 12:05:33 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Raytracer_H
#define _Raytracer_H

#include "booga/component/PixmapRenderer.h"

//____________________________________________________________________ Raytracer

class Raytracer : public PixmapRenderer {
declareRTTI(Raytracer);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Raytracer();
private:
  Raytracer(const Raytracer&);             // No copies.

public:
  // virtual ~Raytracer();                 // Use default version.

private:
  Raytracer& operator=(const Raytracer&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Raytracer
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void computeDepthMap(bool flag);
  void computeAlphaMap(bool flag);
  // Depth and alpha maps are computed by default. This may lead to 
  // a problem if not enough memory is available (8 additional bytes 
  // per pixel). If this problem occurs to you, just turn of this feature 
  // by calling:
  //
  //   Raytracer r;
  //   r.computeDepthMap(false);
  //   r.computeAlphaMap(false);
  //  

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool doExecute();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  bool myComputeDepthMap;
  bool myComputeAlphaMap;
};

//______________________________________________________________________ INLINES

#endif // _Raytracer_H

