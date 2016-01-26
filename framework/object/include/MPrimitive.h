/*
 * $RCSfile: MPrimitive.h,v $
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: MPrimitive.h,v 1.3 1996/08/09 14:35:52 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _MPrimitive_H
#define _MPrimitive_H

#include "booga/base/Name.h"

//__________________________________________________________________ MPrimitive

template <class TObject, class TPrimitive, class TPath, class TRay, class TPrimitiveAttr>
class MPrimitive : public TObject {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  MPrimitive();
  MPrimitive(Exemplar);
  // MPrimitive(const MPrimitive<TObject, TPrimitive, TPath, TRay, TPrimitiveAttr>&);          
  // Use default version.          

public:
  // virtual ~MPrimitive();                  // Use default version.
  
private:
  MPrimitive<TObject, TPrimitive, TPath, TRay, TPrimitiveAttr>& 
    operator=(const MPrimitive<TObject, TPrimitive, TPath, TRay, TPrimitiveAttr>&);  
  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class MPrimitive<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual TObject* createDecomposition() const = 0;
  // Create a decomposition of the primitive. 
  // E.g. a Sphere3D object tesselates itself into a set of triangles.
  // The caller of the method is responsible for the clean up.
  // Returns NULL on failure or if no decomposition is possible.
 
  void setPrecision(float precision);
  float getPrecision() const;

public:
  static void initClass();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class TObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual TObject* makeUnique(TPath* path = NULL, bool shared = false);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual long countSubobject() const;
  virtual TObject* getSubobject(long index);
private:
  virtual bool doIntersect(TRay& ray);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  float myPrecision;  
  // Parameter to control the result of the createDecomposition method.
  // 'myPrecision' has values in the range [0,1]; 
  // 0 = poor, 1 = excellent quality of decomposition (tesselation).
};

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
#define TEMPLATE_IS_INCLUDE_FROM_H
#include "../object/src/MPrimitive.C"
#endif // TEMPLATE_IN_HEADER


#endif // _MPrimitive_H

