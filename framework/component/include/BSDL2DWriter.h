/*
 * $RCSfile: BSDL2DWriter.h,v $
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
 *  $Id: BSDL2DWriter.h,v 1.3 1996/10/04 09:45:52 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _BSDL2DWriter_H
#define _BSDL2DWriter_H

#include <fstream>
#include "booga/base/Value.h"
#include "booga/base/RCString.h"
#include "booga/component/DocumentStore.h"
#include "booga/component/BSDLWriter.h"
#include "booga/component/Operation2D.h"

//_____________________________________________________________________ BSDL2DWriter

class BSDL2DWriter : public Operation2D {
declareRTTI(BSDL2DWriter);
// enable RTTI support

private:
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  BSDL2DWriter(DocumentStore& docuStore);
  ~BSDL2DWriter();
private:
  BSDL2DWriter(const BSDL2DWriter&);             // No copies.

public:
  // virtual ~BSDL2DWriter();                // Use default version.

private:
  BSDL2DWriter& operator=(const BSDL2DWriter&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class BSDL2DWriter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Operation2D
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

#endif // _BSDL2DWriter_H
