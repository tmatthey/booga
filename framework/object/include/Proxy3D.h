/*
 * $RCSfile: Proxy3D.h,v $
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
 *  $Id: Proxy3D.h,v 1.6 1996/08/09 14:53:22 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Proxy3D_H
#define _Proxy3D_H

#include "booga/object/MProxy.h"
#include "booga/object/Object3D.h"
#include "booga/object/Path3D.h"
#include "booga/object/Ray3D.h"

//_____________________________________________________________________ Proxy3D

class Proxy3D : public MProxy<Object3D, Proxy3D, Path3D, Ray3D> {
declareRTTI(Proxy3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Proxy3D();
  Proxy3D(Exemplar);
  // Proxy3D(const Proxy3D&);          // Use default version.

public:
  // virtual ~Proxy3D();               // Use default version.

private:
  Proxy3D& operator=(const Proxy3D&);  // No assignments.
};

//______________________________________________________________________ INLINES

#endif // _Proxy3D_H

