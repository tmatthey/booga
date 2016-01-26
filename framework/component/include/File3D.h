/*
 * $RCSfile: File3D.h,v $
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
 *  $Id: File3D.h,v 1.6 1996/09/13 08:04:08 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _File3D_H
#define _File3D_H

#include "booga/base/RCString.h"
#include "booga/object/Proxy3D.h"
#include "booga/object/World3D.h"
#include "booga/object/Aggregate3D.h"
#include "booga/component/MFile.h"
#include "booga/component/Parser3D.h"

//_____________________________________________________________________ File3D

class File3D : public MFile<Object3D, Proxy3D, File3D, Aggregate3D, World3D, Parser3D> {
declareRTTI(File3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // File3D();                         // Use default version.
  File3D(const RCString& name);
  File3D(Exemplar);
  // File3D(const File3D&);            // Use default version.

public:
  // virtual ~File3D();                // Use default version.

private:
  File3D& operator=(const File3D&);    // No assignments.
};

#endif // _File3D_H

