/*
 * $RCSfile: GLBBTraversal2D.C,v $
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
 *  $Id: GLBBTraversal2D.C,v 1.4 1996/09/13 08:04:19 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifdef HAVE_OPENGL
# include <GL/gl.h>
#endif

#include "booga/glwrapper/GLRasterizer.h"
#include "booga/glwrapper/GLBBTraversal2D.h"

//______________________________________________________________ GLBBTraversal2D

implementRTTI(GLBBTraversal2D, GLAbstractTraversal2D);

bool GLBBTraversal2D::traverse(Object2D* obj)
{
#ifdef HAVE_OPENGL

  // 
  // Check if the traversal has been called with a GLRasterizer object.
  //
  if ((myRasterizer = dynamic_cast<GLRasterizer*>(getVisitor())) == NULL) {
    Report::recoverable("[GLBBTraversal2D::traverse] need GLRasterizer object to work with");
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

void GLBBTraversal2D::handleObject(Object2D* obj, float currentTransform[16])
{
  //
  // Just display the bounding rectangle.
  //
  myRasterizer->drawBounds(obj);

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
    static float m[16] = { 1, 0, 0, 0,
                           0, 1, 0, 0,
                           0, 0, 1, 0,
                           0, 0, 0, 1
                         };
#ifdef HAVE_OPENGL
    glPushMatrix();
#endif // HAVE_OPENGL
      const TransMatrix2D& trans = obj->getTransform().getTransMatrix();
      m[0]  = trans(0, 0); m[1]  = trans(0, 1); 
      m[4]  = trans(1, 0); m[5]  = trans(1, 1); 
      m[12] = trans(2, 0); m[13] = trans(2, 1); 
#ifdef HAVE_OPENGL
      glMultMatrixf(m);
      glGetFloatv(GL_MODELVIEW_MATRIX, entry->transform);
    glPopMatrix();
#endif // HAVE_OPENGL
  }


  myQueue.append(entry);
}
