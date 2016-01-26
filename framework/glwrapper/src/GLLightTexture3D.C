/*
 * GLLightTexture3D.C 
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
 *  $Id: GLLightTexture3D.C,v 1.3 1996/02/23 07:33:55 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#ifdef HAVE_OPENGL
# include <GL/gl.h>
#endif

#include "booga/glwrapper/GLLightTexture3D.h"

//_____________________________________________________________ GLLightTexture3D

implementRTTI(GLLightTexture3D, LightTexture);

GLLightTexture3D::GLLightTexture3D(const Color& color)
: LightTexture(color)
{}

Texture3D* GLLightTexture3D::copy() const
{
  return new GLLightTexture3D(*this);
}

void GLLightTexture3D::doTexturing(Texture3DContext& context) const
{
  if (GLTexture::ourTexturingType == GLTexture::BOOGA) {
    LightTexture::doTexturing(context);
    return;
  }

#ifdef HAVE_OPENGL

  GLfloat glvec[4];
  GLfloat transl = 1.0;
 
  glvec[0] = getColor().getRed();
  glvec[1] = getColor().getGreen();
  glvec[2] = getColor().getBlue();
  glvec[3] = transl;
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glvec);
 
  glvec[0] = glvec[1] =  glvec[2] =  0; glvec[3] = transl;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glvec);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glvec);

  float shininess = 30;
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);

#endif // HAVE_OPENGL
}
