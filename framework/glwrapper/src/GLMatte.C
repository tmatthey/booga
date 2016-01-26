/*
 * GLMatte.C 
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
 *  $Id: GLMatte.C,v 1.4 1995/12/15 09:20:18 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#ifdef HAVE_OPENGL
# include <GL/gl.h>
#endif

#include "booga/glwrapper/GLMatte.h"

//______________________________________________________________________ GLMatte

implementRTTI(GLMatte, Matte);

GLMatte::GLMatte()
{}

GLMatte::GLMatte(Exemplar exemplar)
: Matte(exemplar)
{}

Texture3D* GLMatte::copy() const
{
  return new GLMatte(*this);
}

void GLMatte::doTexturing(Texture3DContext& context) const
{
  if (GLTexture::ourTexturingType == GLTexture::BOOGA) {
    Matte::doTexturing(context);
    return;
  }
  
#ifdef HAVE_OPENGL

  static GLfloat glvec[4] = { 0. , 0., 0., 1. };

  //
  // Disable specular highlights.
  //
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glvec);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.);
 
  glvec[0] = getDiffuse().getRed();
  glvec[1] = getDiffuse().getGreen();
  glvec[2] = getDiffuse().getBlue();
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glvec);
 
  glvec[0] = getAmbient().getRed();
  glvec[1] = getAmbient().getGreen();
  glvec[2] = getAmbient().getBlue();
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glvec);

#endif // HAVE_OPENGL
}

