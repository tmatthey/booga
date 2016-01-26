/*
 * GLPhong.h
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
 *  $Id: GLPhong.h,v 1.3 1996/04/19 15:21:20 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GLPhong_H
#define _GLPhong_H

#include "booga/texture/Phong.h"
#include "booga/glwrapper/GLTexture.h"

//______________________________________________________________________ GLPhong

class GLPhong : public Phong, public GLTexture {
declareRTTI(GLPhong);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GLPhong();
  GLPhong(Exemplar);
  // GLPhong(const GLPhong&);         // Use default version.

public:
  // ~GLPhong();                      // Use default version.
  
private:
  GLPhong& operator=(const GLPhong&); //  No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Texture3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void doTexturing(Texture3DContext& context) const;
  virtual Texture3D* copy() const;
};

#endif // _GLPhong_H
