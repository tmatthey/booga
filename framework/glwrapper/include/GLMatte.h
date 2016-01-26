/*
 * GLMatte.h
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
 *  $Id: GLMatte.h,v 1.3 1996/04/19 15:21:18 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GLMatte_H
# define _GLMatte_H

#include "booga/texture/Matte.h"
#include "booga/glwrapper/GLTexture.h"

//______________________________________________________________________ GLMatte

class GLMatte : public Matte, public GLTexture {
declareRTTI(GLMatte);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GLMatte();
  GLMatte(Exemplar);
  // GLMatte(const GLMatte&);          // Use default version.

public:
  // virtual ~GLMatte();               // Use default version.

private:  
  GLMatte& operator=(const GLMatte&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Texture3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Texture3D* copy() const;
  virtual void doTexturing(Texture3DContext& context) const;
};

#endif // _GLMatte_H

