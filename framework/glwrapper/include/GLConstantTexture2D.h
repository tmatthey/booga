/*
 * GLConstantTexture2D.h
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
 *  $Id: GLConstantTexture2D.h,v 1.2 1996/04/12 14:00:15 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GLConstantTexture2D_H
#define _GLConstantTexture2D_H

#include "booga/object/ConstantTexture2D.h"
#include "booga/glwrapper/GLTexture.h"

//__________________________________________________________ GLConstantTexture2D

class GLConstantTexture2D : public ConstantTexture2D, public GLTexture {
declareRTTI(GLConstantTexture2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GLConstantTexture2D(const Color& color = Color::getDefault());
  GLConstantTexture2D(Exemplar);
  // GLConstantTexture2D(const GLConstantTexture2D&);          // Use default version.

public:
  // virtual ~GLConstantTexture2D();                           // Use default version.

private:  
  GLConstantTexture2D& operator=(const GLConstantTexture2D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Texture2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Texture2D* copy() const;
  virtual void doTexturing(Texture2DContext& context) const;
};

#endif // _GLConstantTexture2D_H

