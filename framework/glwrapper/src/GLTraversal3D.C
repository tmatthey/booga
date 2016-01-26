/*
 * $RCSfile: GLTraversal3D.C,v $
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: GLTraversal3D.C,v 1.22 1998/03/19 15:18:55 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifdef HAVE_OPENGL
# include <GL/gl.h>
#endif

#include "booga/object/Texture3D.h"
#include "booga/object/Primitive3D.h"  // dynamic_cast(Primitive3D,...)

#include "booga/glwrapper/GLUtilities.h"
#include "booga/glwrapper/GLTraversal3D.h"
#include "booga/glwrapper/GLWhitted.h"
#include "booga/glwrapper/GLPhong.h"
#include "booga/glwrapper/GLMatte.h"
#include "booga/glwrapper/GLPolygonMapper.h"

//________________________________________________________________ GLTraversal3D

implementRTTI(GLTraversal3D, GLAbstractTraversal3D);

bool GLTraversal3D::traverse(Object3D* obj)
{
  bool retval = true;

  if (obj != NULL) {
    beforeVisitObject(obj);
    retval = doTraverse(obj);
    afterVisitObject(obj);
  }

  return retval;
}

bool GLTraversal3D::doTraverse(Object3D* obj)
{
  if (GLTraversal::abortTraversal())
    return false; 

  if (obj == NULL)
    return true;

  Traversal::Result state = getVisitor()->dispatch(obj);

  switch (state) {
    case Traversal::EXIT:
      return false;

    case Traversal::PRUNE:
      return true;

    case Traversal::CONTINUE:
    case Traversal::UNKNOWN:
      break;

    default:
      Report::recoverable("[GLTraversal3D::doTraverse] unknown tag");
      return false;
  }

  int retval;
  Primitive3D* primitive = dynamic_cast<Primitive3D*>(obj);

  if (primitive != NULL && state != Traversal::CONTINUE) {
    Object3D* decomposition = primitive->createDecomposition();

    retval = traverse(decomposition);
    if (decomposition != NULL)
      delete decomposition;

    return retval;
  }
  else {
    // 
    // Visit the subobjects...
    //
    for (long i=0; i<obj->countSubobject(); i++) {
      if (state == Traversal::CONTINUE)
	getVisitor()->incLevel();
      retval = traverse(obj->getSubobject(i));
      if (state == Traversal::CONTINUE)
	getVisitor()->decLevel();
      
      if (retval == false)
	return false;
    }
  }

  return true;
}

void GLTraversal3D::beforeVisitObject(Object3D* object)
{
#ifdef HAVE_OPENGL

  //
  // Perform texturing.
  //
  if (object->getTexture() != NULL) {
//    if (dynamic_cast(GLTexture, const_cast(Texture3D, object->getTexture()))) { 
      glPushAttrib(GL_LIGHTING_BIT|GL_ENABLE_BIT);
      myTextureContext.setObject(object);
      glDisable(GL_TEXTURE_2D);
      object->getTexture()->doTexturing(myTextureContext);
  }

  //
  // Apply local transformations.
  //
  if (!object->getTransform().isIdentity()) {
    static float m[16];
    glPushMatrix();
    convert(object->getTransform().getTransMatrix(), m);
    glMultMatrixf(m);
  }

#endif // HAVE_OPENGL
}

void GLTraversal3D::afterVisitObject(Object3D* object)
{
#ifdef HAVE_OPENGL

  if (object->getTexture() != NULL) 
//    if (dynamic_cast(GLTexture, const_cast(Texture3D, object->getTexture()))) { 
      glPopAttrib();
 
  if (!object->getTransform().isIdentity())
    glPopMatrix();

  // The GL_TEXTURE matrix stack is pushed in GLPolygonMapper
  // we have to pop it again at this place. 
  // -> not very clever, I know... but maybe we find a better
  // solution later on.
  
  if (dynamic_cast<GLPolygonMapper*>(const_cast<Texture3D*>(object->getTexture()))) {
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
  }
#endif // HAVE_OPENGL
}

