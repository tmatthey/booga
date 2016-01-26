/*
 * $RCSfile: PathOf.h,v $ 
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
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: PathOf.h,v 1.9 1996/08/16 08:38:53 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PathOf_H
#define _PathOf_H

#include "booga/base/PrimitiveTypes.h"

//_____________________________________________________________________ PathOf<>

template <class TObject, class TTransform>
class PathOf {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PathOf();
  // PathOf(const PathOf<TObject,TTransform>&);             
                   // Use default version.

public:
  // ~PathOf();    // Use default version.

public:
  // PathOf<TObject,TTransform>& operator=(const PathOf<TObject,TTransform>&);  
                   // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class PathOf<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  int operator==(const PathOf<TObject,TTransform>& p) const;
  int operator!=(const PathOf<TObject,TTransform>& p) const;

  void append(TObject* object);
  // Append another Object to the path. Be sure to pass a pointer
  // that stays valid!

  void removeLast();
  // Removes the last Object from the path and returns the pointer
  // to the Object. 
  // Returns NULL, if there is no element in the path.
  // After removing the tail of the path the result of getObject() may not 
  // valid!

  void replace(TObject* object);
  // Replaces the current (active) object in the path by 'object'.
  
  void reset();
  // Remove all elements from the path.
    
  void first() const;
  void last() const;
  void next() const;
  void prev() const;
  bool isDone() const;
  // Iteration is done using these member functions:
  //
  // for (path.first(); !path.isDone(); path.next()) { .. }
  //    or
  // for (path.last(); !path.isDone(); path.prev()) { .. }
  
  TObject* getObject() const;
  TObject* createTransformedObject() const;
  const TTransform& getTransform() const;
  // Get the current object/transformation during the iteration 
  // process.

  TObject* getLastObject() const;
  TObject* createLastTransformedObject() const;
  const TTransform& getLastTransform() const;
  // Get the last object/transformation on the path.

  const List<TObject*>& getObjects() const;
  // Access to the objects stored on the path.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  long myPosition;                // Current position in the iteration process.
  List<TObject*> myObjects;       // The objects on the path.
  List<TTransform> myTransforms;  // The cumulatated transformations on the path.
};

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
#define TEMPLATE_IS_INCLUDE_FROM_H
#include "../object/src/PathOf.C"
#endif // TEMPLATE_IN_HEADER

#endif // _PathOf_H

