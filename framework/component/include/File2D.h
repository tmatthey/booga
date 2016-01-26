/*
 * $RCSfile: File2D.h,v $
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
 *  $Id: File2D.h,v 1.2 1996/09/13 08:04:05 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _File2D_H
#define _File2D_H

#include "booga/base/RCString.h"
#include "booga/object/Proxy2D.h"
#include "booga/object/World2D.h"
#include "booga/object/Aggregate2D.h"
#include "booga/component/MFile.h"
#include "booga/component/BSDL2DParser.h"

//_____________________________________________________________________ File2D

class File2D : public MFile<Object2D, Proxy2D, File2D, Aggregate2D, World2D, BSDL2DParser> {
declareRTTI(File2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // File2D();                         // Use default version.
  File2D(const RCString& name);
  File2D(Exemplar);
  // File2D(const File2D&);            // Use default version.

public:
  // virtual ~File2D();                // Use default version.

private:
  File2D& operator=(const File2D&);    // No assignments.
};

#endif // _File2D_H

