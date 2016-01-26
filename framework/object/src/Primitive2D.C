/*
 * $RCSfile: Primitive2D.C,v $
 *
 * Copyright (C) 1995, Stephan Amann <amann@iam.unibe.ch>
 *                     Christoph Streit <streit@iam.unibe.ch>
 *                     University of Berne, Switzerland
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
 *  $Id: Primitive2D.C,v 1.9 1996/08/07 09:21:11 amann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Primitive2D.h"

//__________________________________________________________________ Primitive2D

implementRTTI(Primitive2D, Object2D);
implementInitStatics(Primitive2D);

SymTable<Name,Object2D*>* Primitive2D::ourDecompositionCache;

void Primitive2D::initClass()
{
  ourDecompositionCache = new SymTable<Name,Object2D*>(103);
}

Primitive2D::Primitive2D()
: MPrimitive<Object2D, Primitive2D, Path2D, Ray2D, Primitive2DAttr>() {}

Primitive2D::Primitive2D(Exemplar exemplar)
: MPrimitive<Object2D, Primitive2D, Path2D, Ray2D, Primitive2DAttr>(exemplar) {}

const Object2D* Primitive2D::getDecomposition(const Name& key)
{
  Object2D* decomposition = NULL;
  ourDecompositionCache->lookup(key, decomposition);

  return decomposition;
}

void Primitive2D::adoptDecomposition(const Name& key, Object2D* decomposition)
{
 Object2D* oldDecomposition = NULL;
 if (ourDecompositionCache->findAndRemove(key, oldDecomposition))
   delete oldDecomposition;
 ourDecompositionCache->insert(key, decomposition); 
}

