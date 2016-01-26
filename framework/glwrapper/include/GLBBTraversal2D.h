/*
 * $RCSfile: GLBBTraversal2D.h,v $
 *
 * Traversal logic for GL rasterizer. Performs a breath fisrt traversal of 
 * the world and forces the GLRasterizer to just draw the bounding boxes of 
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
 *  $Id: GLBBTraversal2D.h,v 1.4 1996/09/13 08:04:20 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _GLBBTraversal2D_H
#define _GLBBTraversal2D_H

#include "booga/base/List.h"
#include "booga/glwrapper/GLAbstractTraversal2D.h"

class GLRasterizer;

//______________________________________________________________ GLBBTraversal2D

class GLBBTraversal2D : public GLAbstractTraversal2D {
declareRTTI(GLBBTraversal2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // GLBBTraversal2D();                                  // Use default version.
  // GLBBTraversal2D(const GLBBTraversal2D&);            // Use default version.
 
public:
  // virtual ~GLBBTraversal2D();                         // Use default version.      
  
public:
  // GLBBTraversal2D& operator=(const GLBBTraversal2D&); // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GLBBTraversal2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  void handleObject(Object2D* obj, float currentTransform[16]);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class MTraversal<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool traverse(Object2D* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  struct QueueEntry {
    Object2D* object;
    float transform[16];
  };
  
  List<QueueEntry*> myQueue;

  GLRasterizer* myRasterizer; 
  // The visitor will be casted to GLRasterizer and stored here.
};

#endif // _GLBBTraversal2D_H
