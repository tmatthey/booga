/*
 * Nurbs3DParameters.h
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
 *  $Id: Nurbs3DParameters.h,v 1.3 1996/01/12 16:09:48 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Nurbs3DParameters_H
# define _Nurbs3DParameters_H

#include "booga/base/RTTI.h"
#include "booga/nurbs/Nurbs3DTypes.h"

//____________________________________________________________ Nurbs3DParameters

class Nurbs3DParameters {
  declareRTTI(Nurbs3DParameters);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Nurbs3DParameters (void);
//   virtual ~Nurbs3DParameters (void);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Nurbs3DParameters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void reset (void) = 0;
  
  virtual void setType (Nurbs3DTypes::EObject type);
  virtual Nurbs3DTypes::EObject getType (void) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  Nurbs3DTypes::EObject myType;
};

//______________________________________________________________________ INLINES

inline void Nurbs3DParameters::setType (Nurbs3DTypes::EObject type)
{
  myType = type;
}

inline Nurbs3DTypes::EObject Nurbs3DParameters::getType (void) const
{
  return myType;
}

#endif // _Nurbs3DParameters_H
