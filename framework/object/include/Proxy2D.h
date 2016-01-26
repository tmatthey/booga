/*
 * $RCSfile: Proxy2D.h,v $
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
 *  $Id: Proxy2D.h,v 1.2 1996/08/09 14:53:19 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Proxy2D_H
#define _Proxy2D_H

#include "booga/object/MProxy.h"
#include "booga/object/Object2D.h"
#include "booga/object/Path2D.h"
#include "booga/object/Ray2D.h"

//_____________________________________________________________________ Proxy2D

class Proxy2D : public MProxy<Object2D, Proxy2D, Path2D, Ray2D> {
declareRTTI(Proxy2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Proxy2D();
  Proxy2D(Exemplar);
  // Proxy2D(const Proxy2D&);          // Use default version.

public:
  // virtual ~Proxy2D();               // Use default version.

private:
  Proxy2D& operator=(const Proxy2D&);  // No assignments.
};

//______________________________________________________________________ INLINES

#endif // _Proxy2D_H

