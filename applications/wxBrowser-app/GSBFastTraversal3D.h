/*
 * $RCSfile: GSBFastTraversal3D.h,v $
 *
 * Copyright (C) 1994-96, Pascal Habegger <habegger@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: GSBFastTraversal3D.h,v 1.4 1997/04/08 11:04:42 habegger Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _GSBFastTraversal3D_H
#define _GSBFastTraversal3D_H

#include "booga/component/AbstractTraversal3D.h"

//__________________________________________________________ GSBFastTraversal3D

class GSBFastTraversal3D : public AbstractTraversal3D {
declareRTTI(GSBFastTraversal3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // GSBFastTraversal3D();            // Use default version.               
  // GSBFastTraversal3D(const GSBFastTraversal3D&);            
  // Use default version.

public:
  //  virtual ~GSBFastTraversal3D();  // Use deafult version.                        
  
public:
  // GSBFastTraversal3D& operator=(const GSBFastTraversal3D&); 
  // Use default version.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBFastTraversal3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  bool doTraverse(Object3D* obj);
  // Recursively traverses the object structure. Calls traverse() for each 
  // object found or generated by a calling decomposition() on a unknown 
  // object
  // Returns true : continue
  //         false: abort the traversal

  void beforeVisitObject(Object3D *object);
  void afterVisitObject(Object3D* object);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class MTraversal<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool traverse(Object3D* obj);
  // Calls doTraverse()
};

#endif // _GSBFastTraversal3D_H
