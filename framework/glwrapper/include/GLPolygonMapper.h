/*
 * $RCSfile: GLPolygonMapper.h,v $
 *
 * Copyright (C) 1996, Bernhard Bühlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: GLPolygonMapper.h,v 1.3 1998/02/04 12:51:18 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GLPolygonMapper_H
#define _GLPolygonMapper_H

#include <GL/gl.h>

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/Color.h"
#include "booga/object/Texture3D.h"
#include "booga/texture/PolygonMapper.h"
#include "booga/glwrapper/GLTexture.h"

//________________________________________________________________ GLPolygonMapper

class GLPolygonMapper : public PolygonMapper , public GLTexture {
declareRTTI(GLPolygonMapper);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GLPolygonMapper();
  GLPolygonMapper(Exemplar);
  GLPolygonMapper(const GLPolygonMapper& polyMapper);
  
public:
  virtual ~GLPolygonMapper();            

private:
  GLPolygonMapper& operator=(const GLPolygonMapper&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class PolygonMapper
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void adoptPixmap(AbstractPixmap* pixmap);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Texture3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Texture3D* copy() const;
  virtual void doTexturing(Texture3DContext& context) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  GLuint myGLList;
};

#endif // _GLPolygonMapper_H
