/*
 * CTCPPRenderer2D.h
 *
 * Copyright (C) 1994-96, Thomas Wenger
 *                        Thomas von Siebenthal
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: CTCPPRenderer2D.h,v 1.11 1996/10/30 15:31:25 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _CTCPPRenderer2D_H
#define _CTCPPRenderer2D_H

#include <iostream.h>
#include "booga/component/Operation2D.h"
#include "CTClassDescription2D.h"

//_____________________________________________________________ CTCPPRenderer2D

class CTCPPRenderer2D : public Operation2D {
declareRTTI(CTCPPRenderer2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  CTCPPRenderer2D(const RCString filename);
  CTCPPRenderer2D();
  
private:
  CTCPPRenderer2D(const CTCPPRenderer2D&);               // No copies.

public:
  // virtual ~CTCPPRenderer2D();               // Use default version.

private:
  CTCPPRenderer2D& operator=(const CTCPPRenderer2D&); // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class CTCPPRenderer2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Traversal::Result visit(CTClassDescription2D* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Visitor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Traversal::Result dispatch(Makeable* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  RCString myCurrentIdent;
  RCString myIdent;
  ostream *myOutput;
  ofstream *myFileOutput;
};

#endif // _CTCPPRenderer2D_H

