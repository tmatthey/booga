/*
 * $RCSfile: Primitive3D.C,v $
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
 *  $Id: Primitive3D.C,v 1.11 1996/08/07 09:21:13 amann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Primitive3D.h"

//__________________________________________________________________ Primitive3D

implementRTTI(Primitive3D, Object3D);
implementInitStatics(Primitive3D);

SymTable<Name,Object3D*>* Primitive3D::ourDecompositionCache;

void Primitive3D::initClass()
{
  ourDecompositionCache = new SymTable<Name,Object3D*>(103);
}

Primitive3D::Primitive3D()
: MPrimitive<Object3D, Primitive3D, Path3D, Ray3D, Primitive3DAttr>() {}

Primitive3D::Primitive3D(Exemplar exemplar)
: MPrimitive<Object3D, Primitive3D, Path3D, Ray3D, Primitive3DAttr>(exemplar) {}

const Object3D* Primitive3D::getDecomposition(const Name& key)
{
  Object3D* decomposition = NULL;
  ourDecompositionCache->lookup(key, decomposition);

  return decomposition;
}

void Primitive3D::adoptDecomposition(const Name& key, Object3D* decomposition)
{
 Object3D* oldDecomposition = NULL;
 if (ourDecompositionCache->findAndRemove(key, oldDecomposition))
   delete oldDecomposition;
 ourDecompositionCache->insert(key, decomposition); 
}

