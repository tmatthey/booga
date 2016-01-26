/*
 * GLTexture.C
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
 *  $Id: GLTexture.C,v 1.2 1996/04/10 15:52:12 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/glwrapper/GLTexture.h"

//____________________________________________________________________ GLTexture

GLTexture::TexturingType GLTexture::ourTexturingType = GLTexture::GL;

void GLTexture::setTexturingType(GLTexture::TexturingType type)
{
  ourTexturingType = type;
}

GLTexture::TexturingType GLTexture::getTexturingType()
{
  return ourTexturingType;
}
