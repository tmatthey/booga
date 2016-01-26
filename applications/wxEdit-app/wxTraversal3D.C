/*
 * $RCSfile: wxTraversal3D.C,v $
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
 *  $Id: wxTraversal3D.C,v 1.1 1996/09/27 15:08:04 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifdef HAVE_OPENGL
# include <GL/gl.h>
#endif

#include "booga/object/Texture3D.h"
#include "booga/object/Primitive3D.h"  // dynamic_cast(Primitive3D,...)

#include "booga/glwrapper/GLUtilities.h"
#include "wxTraversal3D.h"
#include "booga/glwrapper/GLRenderer.h"

//________________________________________________________________ wxTraversal3D

implementRTTI(wxTraversal3D, GLAbstractTraversal3D);

bool wxTraversal3D::traverse(Object3D* obj)
{
  bool retval = true;

  if (obj != NULL) {
    beforeVisitObject(obj);
    retval = doTraverse(obj);
    afterVisitObject(obj);
  }

  return retval;
}

bool wxTraversal3D::doTraverse(Object3D* obj)
{
  if (GLTraversal::abortTraversal())
    return false; 

  if (getCurrentTime() > (1. / getFrameRate()))
    return false; 

  if (obj == NULL)
    return true;

//  BoundingBox bb = obj->getBounds();
//  
//  GLRenderer *r = dynamic_cast (GLRenderer, getVisitor());
//  
//  if (!r) {
//    Report::warning("[GLTraversal3D::doTraverse]: dynamic_cast (GLRenderer, getVisitor()) failed!");
//    return false;
//  }
//        
//  static GLfloat m[16];
//  glGetFloatv(GL_MODELVIEW_MATRIX, m);
//                       
////  ostrstream os;
////  os << "[GLTraversal3D::doTraverse]: m = " << TransMatrix3D(m) << endl;
////  os << "[GLTraversal3D::doTraverse]: bb = " << bb;  
////  Report::warning(os);
//        
//  // transform boundingbox with current transformation matrix
//        
//  bb.transform (TransMatrix3D (m));
//  
//  Vector3D n(0,0,-1);
//  
//  Vector3D min = bb.getMin();
//  Vector3D max = bb.getMax();
//
//  
//  if ((n^min) < 0.0 && (n^max) < 0.0 ) {
//    ostrstream os; 
//    os << "[GLTraversal3D::doTraverse]:" << typeid(obj).name() << " is outside frustrum!";        
////  if (!r->getCamera()->getViewing()->isInside (bb)) {
//    Report::warning(os);
//    return true;
//  }

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
      Report::recoverable("[wxTraversal3D::doTraverse] unknown tag");
      return false;
  }

  int retval;
  Primitive3D* primitive = dynamic_cast(Primitive3D, obj);

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

void wxTraversal3D::beforeVisitObject(Object3D* object)
{
#ifdef HAVE_OPENGL

  //
  // Perform texturing.
  //
  if (object->getTexture() != NULL) {
    glPushAttrib(GL_LIGHTING_BIT);
    myTextureContext.setObject(object);
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

void wxTraversal3D::afterVisitObject(Object3D* object)
{
#ifdef HAVE_OPENGL

  if (object->getTexture() != NULL) 
    glPopAttrib();
 
  if (!object->getTransform().isIdentity())
    glPopMatrix();
  
#endif // HAVE_OPENGL
}

