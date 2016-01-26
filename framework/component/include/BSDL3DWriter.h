/*
 * $RCSfile: BSDL3DWriter.h,v $
 *
 * Copyright (C) 1996, Andrey Collison <collison@iam.unibe.ch>
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
 *  $Id: BSDL3DWriter.h,v 1.3 1996/10/04 09:45:55 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _BSDL3DWriter_H
#define _BSDL3DWriter_H

#include <fstream>
#include "booga/base/Value.h"
#include "booga/base/RCString.h"
#include "booga/component/DocumentStore.h"
#include "booga/component/BSDLWriter.h"
#include "booga/component/Operation3D.h"

//_____________________________________________________________________ BSDL3DWriter

class BSDL3DWriter : public Operation3D {
declareRTTI(BSDL3DWriter);
// enable RTTI support

private:
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  BSDL3DWriter(DocumentStore& docuStore);
  ~BSDL3DWriter();
private:
  BSDL3DWriter(const BSDL3DWriter&);             // No copies.

public:
  // virtual ~BSDL3DWriter();                // Use default version.

private:
  BSDL3DWriter& operator=(const BSDL3DWriter&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class BSDL3DWriter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Operation3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual bool doExecute();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Visitor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  BSDLWriter myBSDLWriter;
};

//______________________________________________________________________ INLINES

#endif // _BSDL3DWriter_H

