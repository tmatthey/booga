/*
 * GLPhong.C 
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
 *  $Id: GLPhong.C,v 1.3 1995/12/15 09:20:19 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#ifdef HAVE_OPENGL
# include <GL/gl.h>
#endif

#include "booga/glwrapper/GLPhong.h"

//______________________________________________________________________ GLPhong

implementRTTI(GLPhong, Phong);

GLPhong::GLPhong()
{}

GLPhong::GLPhong(Exemplar exemplar)
: Phong(exemplar)
{}

Texture3D* GLPhong::copy() const
{
  return new GLPhong(*this);
}

void GLPhong::doTexturing(Texture3DContext& context) const
{
  if (GLTexture::ourTexturingType == GLTexture::BOOGA) {
    Phong::doTexturing(context);
    return;
  }

#ifdef HAVE_OPENGL

  static GLfloat glvec[4] = { 0. , 0., 0., 1. };
 
  glvec[0] = getDiffuse().getRed();
  glvec[1] = getDiffuse().getGreen();
  glvec[2] = getDiffuse().getBlue();
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glvec);
 
  glvec[0] = getAmbient().getRed();
  glvec[1] = getAmbient().getGreen();
  glvec[2] = getAmbient().getBlue();
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glvec);

  glvec[0] = getSpecular().getRed();
  glvec[1] = getSpecular().getGreen();
  glvec[2] = getSpecular().getBlue();
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glvec);
  
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, getSpecPow());
  
#endif // HAVE_OPENGL
}
