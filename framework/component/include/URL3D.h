/*
 * $RCSfile: URL3D.h,v $
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
 *  $Id: URL3D.h,v 1.6 1996/09/13 08:06:59 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _URL3D_H
#define _URL3D_H

#include "booga/base/RCString.h"
#include "booga/object/Proxy3D.h"
#include "booga/object/Aggregate3D.h"
#include "booga/object/World3D.h"
#include "booga/component/MURL.h"
#include "booga/component/Parser3D.h"

//_____________________________________________________________________ URL3D

class URL3D : public MURL<Object3D, Proxy3D, URL3D, Aggregate3D, World3D, Parser3D> {
declareRTTI(URL3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // URL3D();                         // Use default version.
  URL3D(const RCString& url);
  URL3D(Exemplar);
  // URL3D(const URL3D&);             // Use default version.

public:
  // virtual ~URL3D();                // Use default version.

private:
  URL3D& operator=(const URL3D&);     // No assignments.
};

#endif // _URL3D_H

