/*
 * $RCSfile: GLBBTraversal3D.h,v $
 *
 * Traversal logic for GL renderer. Performs a breath fisrt traversal of 
 * the world and forces the GLRenderer to just draw the bounding boxes of 
 * the visited objects. No textures are applied.
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
 *  $Id: GLBBTraversal3D.h,v 1.7 1996/09/13 08:04:23 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _GLBBTraversal3D_H
#define _GLBBTraversal3D_H

#include "booga/base/List.h"
#include "booga/glwrapper/GLAbstractTraversal3D.h"

class GLRenderer;

//______________________________________________________________ GLBBTraversal3D

class GLBBTraversal3D : public GLAbstractTraversal3D {
declareRTTI(GLBBTraversal3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // GLBBTraversal3D();                                  // Use default version.
  // GLBBTraversal3D(const GLBBTraversal3D&);            // Use default version.
 
public:
  // virtual ~GLBBTraversal3D();                         // Use default version.      
  
public:
  // GLBBTraversal3D& operator=(const GLBBTraversal3D&); // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GLBBTraversal3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  void handleObject(Object3D* obj, float currentTransform[16]);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class MTraversal<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool traverse(Object3D* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  struct QueueEntry {
    Object3D* object;
    float transform[16];
  };
  
  List<QueueEntry*> myQueue;
  
  GLRenderer* myRenderer; 
  // The visitor will be casted to GLRenderer and stored here.
};

#endif // _GLBBTraversal3D_H
