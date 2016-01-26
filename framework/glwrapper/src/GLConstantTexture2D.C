/*
 * GLConstantTexture2D.C 
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
 *  $Id: GLConstantTexture2D.C,v 1.3 1996/04/12 14:00:14 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#ifdef HAVE_OPENGL
# include <GL/gl.h>
#endif

#include "booga/glwrapper/GLConstantTexture2D.h"

//__________________________________________________________ GLConstantTexture2D

implementRTTI(GLConstantTexture2D, ConstantTexture2D);

GLConstantTexture2D::GLConstantTexture2D(const Color& color)
: ConstantTexture2D(color)
{}

GLConstantTexture2D::GLConstantTexture2D(Exemplar exemplar) 
: ConstantTexture2D(exemplar)
{}

Texture2D* GLConstantTexture2D::copy() const
{
  return new GLConstantTexture2D(*this);
}

void GLConstantTexture2D::doTexturing(Texture2DContext& context) const
{
  if (GLTexture::ourTexturingType == GLTexture::BOOGA) {
    ConstantTexture2D::doTexturing(context);
    return;
  }

#ifdef HAVE_OPENGL

  glColor3f(getColor().getRed(), getColor().getGreen(), getColor().getBlue());

#endif // HAVE_OPENGL
}
