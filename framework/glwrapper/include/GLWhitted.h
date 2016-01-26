/*
 * GLWhitted.h
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
 *  $Id: GLWhitted.h,v 1.5 1996/04/19 15:21:22 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GLWhitted_H
# define _GLWhitted_H

#include "booga/texture/Whitted.h"
#include "booga/glwrapper/GLTexture.h"

//____________________________________________________________________ GLWhitted

class GLWhitted : public Whitted, public GLTexture {
declareRTTI(GLWhitted);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GLWhitted();
  GLWhitted(Exemplar);
  // GLWhitted(const GLWhitted&);          // Use default version.

public:
  // virtual ~GLWhitted();                 // Use default version.

private:  
  GLWhitted& operator=(const GLWhitted&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Texture3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Texture3D* copy() const;
  virtual void doTexturing(Texture3DContext& context) const;
};

#endif // _GLWhitted_H

