/*
 * $RCSfile: Shared2D.h,v $ 
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
 *  $Id: Shared2D.h,v 1.10 1996/09/13 08:06:18 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Shared2D_H
#define _Shared2D_H

#include "booga/object/Object2D.h"
#include "booga/object/Path2D.h"
#include "booga/object/MShared.h"
#include "booga/base/ReferenceCounting.h"

//_____________________________________________________________________ Shared2D

class Shared2D : public MShared<Object2D, Shared2D, Path2D, Ray2D> {
declareRTTI(Shared2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Shared2D(Object2D* adoptObject);
  // Shared2D(Exemplar);  // No exemplar constructor!
  Shared2D(Object2D* adoptObject, const Name defName);
  // Shared2D(const Shared2D&);           // Use default version.

public:
  // virtual ~Shared2D();                 // Use default version.

private:
  Shared2D& operator=(const Shared2D& );  // No assignments.
};

#endif // _Shared2D_H
