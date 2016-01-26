/*
 * GLLightTexture3D.h
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
 *  $Id: GLLightTexture3D.h,v 1.4 1996/02/23 07:33:56 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GLLightTexture3D_H
#define _GLLightTexture3D_H

#include "booga/object/LightTexture.h"
#include "booga/glwrapper/GLTexture.h"

//_____________________________________________________________ GLLightTexture3D

class GLLightTexture3D : public LightTexture, public GLTexture {
declareRTTI(GLLightTexture3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GLLightTexture3D(const Color& color);
  // GLLightTexture3D(const GLLightTexture3D&);          // Use default version.

public:
  // virtual ~GLLightTexture3D();                        // Use default version.

private:  
  GLLightTexture3D& operator=(const GLLightTexture3D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Texture3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Texture3D* copy() const;
  virtual void doTexturing(Texture3DContext& context) const;
};

#endif // _GLLightTexture3D_H

