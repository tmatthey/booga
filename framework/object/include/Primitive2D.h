/*
 * $RCSfile: Primitive2D.h,v $ 
 * 
 * Base class for Object2D primitive elements.
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
 *  $Id: Primitive2D.h,v 1.11 1996/08/07 09:21:12 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Primitive2D_H
#define _Primitive2D_H

#include "booga/base/StaticInit.h"
#include "booga/object/Object2D.h"
#include "booga/object/Path2D.h"
#include "booga/object/MPrimitive.h"
#include "booga/object/Primitive2DAttr.h"

//__________________________________________________________________ Primitive2D

class Primitive2D : public MPrimitive<Object2D, Primitive2D, Path2D, Ray2D, Primitive2DAttr> {
declareRTTI(Primitive2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Primitive2D();
  Primitive2D(Exemplar);
  // Primitive2D(const Primitive2D&);          // Use default version.          

public:
  // virtual ~Primitive2D();                   // Use default version.
  
private:
  Primitive2D& operator=(const Primitive2D&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Primitive2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  static void initClass();

protected:
  static const Object2D* getDecomposition(const Name& key);
  static void adoptDecomposition(const Name& key, Object2D* decomposition);

private:
  static SymTable<Name,Object2D*>* ourDecompositionCache;
};

declareInitStatics(Primitive2D);


#endif // _Primitive2D_H
