/*
 * GLInterpolatorTexture2D.C 
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
 *  $Id: GLInterpolatorTexture2D.C,v 1.1 1995/12/28 12:50:51 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#ifdef HAVE_OPENGL
# include <GL/gl.h>
#endif

#include "booga/glwrapper/GLInterpolatorTexture2D.h"

//______________________________________________________ GLInterpolatorTexture2D

implementRTTI(GLInterpolatorTexture2D, InterpolatorTexture2D);

GLInterpolatorTexture2D::GLInterpolatorTexture2D()
{}

GLInterpolatorTexture2D::GLInterpolatorTexture2D(Exemplar) 
{}

Texture2D* GLInterpolatorTexture2D::copy() const
{
  return new GLInterpolatorTexture2D(*this);
}

void GLInterpolatorTexture2D::doTexturing(Texture2DContext& context) const
{
  if (GLTexture::ourTexturingType == GLTexture::BOOGA) {
    InterpolatorTexture2D::doTexturing(context);
    return;
  }

#ifdef HAVE_OPENGL

  Color color = (getColorFrom() + getColorTo()) / 2;
  glColor3f(color.getRed(), color.getGreen(), color.getBlue());
  
#endif // HAVE_OPENGL
}
