/*
 * $RCSfile: URL2D.h,v $
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
 *  $Id: URL2D.h,v 1.2 1996/09/13 08:06:53 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _URL2D_H
#define _URL2D_H

#include "booga/base/RCString.h"
#include "booga/object/Proxy2D.h"
#include "booga/object/Aggregate2D.h"
#include "booga/object/World2D.h"
#include "booga/component/MURL.h"
#include "booga/component/BSDL2DParser.h"

//_____________________________________________________________________ URL2D

class URL2D : public MURL<Object2D, Proxy2D, URL2D, Aggregate2D, World2D, BSDL2DParser> {
declareRTTI(URL2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // URL2D();                         // Use default version.
  URL2D(const RCString& url);
  URL2D(Exemplar);
  // URL2D(const URL2D&);             // Use default version.

public:
  // virtual ~URL2D();                // Use default version.

private:
  URL2D& operator=(const URL2D&);     // No assignments.
};

#endif // _URL2D_H

