/*
 * $RCSfile: Primitive3D.h,v $ 
 * 
 * Base class for Object3D primitive elements.
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
 *  $Id: Primitive3D.h,v 1.13 1996/08/07 09:21:13 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Primitive3D_H
#define _Primitive3D_H

#include "booga/base/StaticInit.h"
#include "booga/object/Object3D.h"
#include "booga/object/Path3D.h"
#include "booga/object/MPrimitive.h"
#include "booga/object/Primitive3DAttr.h"

//__________________________________________________________________ Primitive3D

class Primitive3D : public MPrimitive<Object3D, Primitive3D, Path3D, Ray3D, Primitive3DAttr> {
declareRTTI(Primitive3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Primitive3D();
  Primitive3D(Exemplar);
  // Primitive3D(const Primitive3D&);          // Use default version.          

public:
  // virtual ~Primitive3D();                   // Use default version.
  
private:
  Primitive3D& operator=(const Primitive3D&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Primitive3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Vector3D normal(const Vector3D& point) const = 0;
  // get normal of primitive in point (in object coordinate system)

public:
  static void initClass();

protected:
  static const Object3D* getDecomposition(const Name& key);
  static void adoptDecomposition(const Name& key, Object3D* decomposition);

private:
  static SymTable<Name,Object3D*>* ourDecompositionCache;
};

declareInitStatics(Primitive3D);

#endif // _Primitive3D_H
