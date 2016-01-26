/*
 * Nurbs3DHandler.h
 *
 * Copyright (C) 1995, Richard Baechler <baechler@iam.unibe.ch>
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
 *  $Id: Nurbs3DHandler.h,v 1.3 1996/01/12 16:09:45 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Nurbs3DHandler_H
# define _Nurbs3DHandler_H

#include "booga/base/RTTI.h"

class Nurbs3D;     // Forward declaration

//_______________________________________________________________ Nurbs3DHandler

class Nurbs3DHandler {
  declareRTTI(Nurbs3DHandler);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Nurbs3DHandler (void);
  Nurbs3DHandler (Nurbs3D *adoptNurbs);
  virtual ~Nurbs3DHandler (void);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Nurbs3DHandler
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void    adoptNurbs (Nurbs3D *nurbs);
  virtual Nurbs3D *copyNurbs (void) const;
  virtual Nurbs3D *orphanNurbs (void);

protected:
  virtual void dummy (void) = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  Nurbs3D *myNurbs;
};

//______________________________________________________________________ INLINES

#endif // _Nurbs3DHandler_H
