/*
 * GLWhitted.C 
 *
 * Copyright (C) 1995, Christoph Streit <streit@iam.unibe.ch>
 *                     Stephan Amann <amann@iam.unibe.ch>
 *                     University of Berne, Switzerland
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
 *  $Id: GLWhitted.C,v 1.7 1995/12/15 09:20:20 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#ifdef HAVE_OPENGL
# include <GL/gl.h>
#endif

#include "booga/glwrapper/GLWhitted.h"

//____________________________________________________________________ GLWhitted

implementRTTI(GLWhitted, Whitted);

GLWhitted::GLWhitted()
{}

GLWhitted::GLWhitted(Exemplar exemplar)
: Whitted(exemplar)
{}

Texture3D* GLWhitted::copy() const
{
  return new GLWhitted(*this);
}

void GLWhitted::doTexturing(Texture3DContext& context) const
{
  if (GLTexture::ourTexturingType == GLTexture::BOOGA) {
    Whitted::doTexturing(context);
    return;
  }

#ifdef HAVE_OPENGL

  static GLfloat glvec[4];
  static GLfloat trans = 1.0;

  if (getTransparency() > 0.0) {
     trans = 1 - getTransparency();
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }
 
  glvec[0] = getDiffuse().getRed();
  glvec[1] = getDiffuse().getGreen();
  glvec[2] = getDiffuse().getBlue();
  glvec[3] = trans;
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glvec);
 
  glvec[0] = getAmbient().getRed();
  glvec[1] = getAmbient().getGreen();
  glvec[2] = getAmbient().getBlue();
  glvec[3] = trans;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glvec);
  
#endif // HAVE_OPENGL
}
