/*
 * GLDisplayListOption.C
 *
 * Copyright (C) 1998, Bernhard Buehlmann <buhlmann@iam.unibe.ch>
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: GLDisplayListOption.C,v 1.1 1998/05/20 13:01:50 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
   
#include "booga/glwrapper/GLDisplayListOption.h"

implementRTTI(GLDisplayListOption,Option);


GLDisplayListOption::GLDisplayListOption (GLuint l)
{
  myGLList = l;
}

GLDisplayListOption::~GLDisplayListOption()
{
  glDeleteLists(myGLList,1);
}

void GLDisplayListOption::callList()
{
  glCallList(myGLList);
}

Option* GLDisplayListOption::copy() const
{
  return new GLDisplayListOption(myGLList);
}
