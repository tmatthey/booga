/*
 * $RCSfile: AbstractPixmapOperation.h,v $
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
 *  $Id: AbstractPixmapOperation.h,v 1.3 1996/09/13 08:03:06 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _AbstractPixmapOperation_H
#define _AbstractPixmapOperation_H

#include "booga/component/Operation2D.h"

class Pixmap2D;

//______________________________________________________ AbstractPixmapOperation

class AbstractPixmapOperation : public Operation2D {
declareRTTI(AbstractPixmapOperation);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Some local Types
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  enum Type { FIRST, ALL };
  // Operate just on FIRST Pixmap2D in World, or on ALL

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  AbstractPixmapOperation(Type traversalType);
private:
  AbstractPixmapOperation(const AbstractPixmapOperation&); // No copies.

public:
  // virtual ~AbstractPixmapOperation();  // Use default version.

private:
  AbstractPixmapOperation& operator=(const AbstractPixmapOperation&);
                                          // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class AbstractPixmapOperation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Traversal::Result visit(Pixmap2D* obj);
  
private:
  virtual bool operateOnPixmap2D(Pixmap2D* obj) = 0;
  // Do something with Pixmap(s). 
  // Returns true on success, false on failure.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Visitor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Traversal::Result dispatch(Makeable* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  Type myTraversalType;
};

#endif // _AbstractPixmapOperation_H
