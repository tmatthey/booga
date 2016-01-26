/*
 * $RCSfile: PreorderTraversal2D.h,v $
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
 *  $Id: PreorderTraversal2D.h,v 1.1 1996/09/13 08:05:49 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _PreorderTraversal2D_H
#define _PreorderTraversal2D_H

#include "booga/component/AbstractTraversal2D.h"

//__________________________________________________________ PreorderTraversal2D

class PreorderTraversal2D : public AbstractTraversal2D {
declareRTTI(PreorderTraversal2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // PreorderTraversal2D();            // Use default version.               
  // PreorderTraversal2D(const PreorderTraversal2D&);            
  // Use default version.

public:
  //  virtual ~PreorderTraversal2D();  // Use deafult version.                        
  
public:
  // PreorderTraversal2D& operator=(const PreorderTraversal2D&); 
  // Use default version.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class PreorderTraversal2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  bool doTraverse(Object2D* obj);
  // Recursively traverses the object structure. Calls traverse() for each 
  // object found or generated by a calling decomposition() on a unknown 
  // object
  // Returns true : continue
  //         false: abort the traversal

  void beforeVisitObject(Object2D *object);
  void afterVisitObject(Object2D* object);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class MTraversal<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool traverse(Object2D* obj);
  // Calls doTraverse()
};

#endif // _PreorderTraversal2D_H