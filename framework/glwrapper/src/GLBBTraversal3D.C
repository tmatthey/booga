/*
 * $RCSfile: GLBBTraversal3D.C,v $
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
 * for any purpose. It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: GLBBTraversal3D.C,v 1.6 1996/09/13 08:04:22 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifdef HAVE_OPENGL
# include <GL/gl.h>
#endif

#include "booga/glwrapper/GLRenderer.h"
#include "booga/glwrapper/GLBBTraversal3D.h"
#include <string.h>

//______________________________________________________________ GLBBTraversal3D

implementRTTI(GLBBTraversal3D, GLAbstractTraversal3D);

bool GLBBTraversal3D::traverse(Object3D* obj)
{
#ifdef HAVE_OPENGL

  // 
  // Check if the traversal has been called with a GLRenderer object.
  //
  if ((myRenderer = dynamic_cast<GLRenderer*>(getVisitor())) == NULL) {
    Report::recoverable("[GLBBTraversal3D::traverse] need GLRenderer object to work with");
    return false;
  }

  // 
  // Transformations of the object are already applied to the bounding box 
  // of the object. So we apply the transformation after the bounding box of 
  // the current object is drawn.
  //

  float transform[16];
  glGetFloatv(GL_MODELVIEW_MATRIX, transform);
  handleObject(obj, transform);

  while (myQueue.count() > 0) {
    QueueEntry* entry = myQueue.item(0);
    myQueue.remove(0);
	
    glPushMatrix();
      glLoadMatrixf(entry->transform);
      for (register long i=0; i<entry->object->countSubobject(); i++) {
	handleObject(entry->object->getSubobject(i), entry->transform);
         //
         // Check for user event.
         //
	if (GLTraversal::abortTraversal())
	  break;
      } 
    glPopMatrix();
      
    delete entry;

    //
    // Check for user event.
    //
    if (GLTraversal::abortTraversal()) {
      for (long i=0; i<myQueue.count(); i++)
        delete myQueue.item(i);
      myQueue.removeAll();
      break;
    }
  }

#endif // HAVE_OPENGL

  return true;
}

void GLBBTraversal3D::handleObject(Object3D* obj, float currentTransform[16])
{

#ifdef HAVE_OPENGL

  //
  // Just display the bounding box.
  //
  myRenderer->drawBounds(obj);

  //
  // An object has to be added if the number of subobjects is > 0 in order to 
  // display the bounding boxes of the subobjects in the next step of the 
  // rendering process. This is usually the case for aggregate and shared objects. 
  //
  if (obj->countSubobject() <= 0)
    return;

  QueueEntry* entry = new QueueEntry;
  entry->object = obj;

  //
  // The entry->transform field stores the cummulated transformation to be applied
  // to the object.
  //
  if (obj->getTransform().isIdentity()) 
    memcpy(entry->transform, currentTransform, 16*sizeof(float));
  else {
    static float m[16];
    glPushMatrix();
      convert(obj->getTransform().getTransMatrix(), m);
      glMultMatrixf(m);
      glGetFloatv(GL_MODELVIEW_MATRIX, entry->transform);
    glPopMatrix();
  }

  myQueue.append(entry);

#endif // HAVE_OPENGL

}
