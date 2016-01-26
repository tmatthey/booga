/*
 * $RCSfile: Shared3D.h,v $
 *
 * A object of class Shared3D may share a Object3D hierarchy with 
 * others. Reference counting is used to handle memory management.
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
 *  $Id: Shared3D.h,v 1.10 1996/09/13 08:06:20 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Shared3D_H
#define _Shared3D_H

#include "booga/object/Object3D.h"
#include "booga/object/Path3D.h"
#include "booga/object/MShared.h"
#include "booga/base/ReferenceCounting.h"

//_____________________________________________________________________ Shared3D

class Shared3D : public MShared<Object3D, Shared3D, Path3D, Ray3D> {
declareRTTI(Shared3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Shared3D(Object3D* adoptObject);
  // Shared3D(Exemplar);                  // No exemplar constructor!
  Shared3D(Object3D* adoptObject, const Name defName);
  // Shared3D(const Shared3D&);           // Use default version.

public:
  // virtual ~Shared3D();                 // Use default version.

private:
  Shared3D& operator=(const Shared3D& );  // No assignments.
};

#endif // _Shared3D_H
