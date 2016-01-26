/*
 * $RCSfile: GLTraversal2D.C,v $
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
 *  $Id: GLTraversal2D.C,v 1.8 1996/09/13 08:04:32 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifdef HAVE_OPENGL
# include <GL/gl.h>
#endif

#include "booga/object/Texture2D.h"
#include "booga/object/Primitive2D.h"  // dynamic_cast(Primitive2D,...)

#include "booga/glwrapper/GLUtilities.h"
#include "booga/glwrapper/GLTraversal2D.h"

//________________________________________________________________ GLTraversal2D

implementRTTI(GLTraversal2D, GLAbstractTraversal2D);

bool GLTraversal2D::traverse(Object2D* obj)
{
  bool retval = true;

  if (obj != NULL) {
    beforeVisitObject(obj);
    retval = doTraverse(obj);
    afterVisitObject(obj);
  }

  return retval;
}

bool GLTraversal2D::doTraverse(Object2D* obj)
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
      Report::recoverable("[GLTraversal2D::doTraverse] unknown tag");
      return false;
  }

  int retval;
  Primitive2D* primitive = dynamic_cast<Primitive2D*>(obj);

  if (primitive != NULL && state != Traversal::CONTINUE) {
    Object2D* decomposition = primitive->createDecomposition();

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

void GLTraversal2D::beforeVisitObject(Object2D *object)
{
#ifdef HAVE_OPENGL

  //
  // Perform texturing.
  //
  if (object->getTexture() != NULL) {
    glPushAttrib((GLbitfield) (GL_LIGHTING_BIT | GL_CURRENT_BIT));
    myTextureContext.setObject(object);
    object->getTexture()->doTexturing(myTextureContext);
  }

  //
  // Apply local transformations.
  //
  if (!object->getTransform().isIdentity()) {
    static float m[16] = { 1, 0, 0, 0,
                           0, 1, 0, 0,
                           0, 0, 1, 0,
                           0, 0, 0, 1
                         };
    glPushMatrix();
    const TransMatrix2D& trans = object->getTransform().getTransMatrix();
    m[0]  = trans(0, 0); m[1]  = trans(0, 1); 
    m[4]  = trans(1, 0); m[5]  = trans(1, 1); 
    m[12] = trans(2, 0); m[13] = trans(2, 1); 
    glMultMatrixf(m);
  }

#endif // HAVE_OPENGL
}

void GLTraversal2D::afterVisitObject(Object2D* object)
{
#ifdef HAVE_OPENGL
  
  if (object->getTexture() != NULL) 
    glPopAttrib();

  if (!object->getTransform().isIdentity())
    glPopMatrix();
  
#endif // HAVE_OPENGL
}

