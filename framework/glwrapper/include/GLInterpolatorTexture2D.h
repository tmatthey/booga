/*
 * GLInterpolatorTexture2D.h
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
 *  $Id: GLInterpolatorTexture2D.h,v 1.1 1995/12/28 12:50:52 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GLInterpolatorTexture2D_H
#define _GLInterpolatorTexture2D_H

#include "booga/object/InterpolatorTexture2D.h"
#include "booga/glwrapper/GLTexture.h"

//______________________________________________________ GLInterpolatorTexture2D

class GLInterpolatorTexture2D : public InterpolatorTexture2D, public GLTexture {
declareRTTI(GLInterpolatorTexture2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GLInterpolatorTexture2D();
  GLInterpolatorTexture2D(Exemplar);
  // GLInterpolatorTexture2D(const GLInterpolatorTexture2D&);          // Use default version.

public:
  // virtual ~GLInterpolatorTexture2D();                           // Use default version.

private:  
  GLInterpolatorTexture2D& operator=(const GLInterpolatorTexture2D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Texture2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Texture2D* copy() const;
  virtual void doTexturing(Texture2DContext& context) const;
};

#endif // _GLInterpolatorTexture2D_H

