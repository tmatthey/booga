/*
 * $RCSfile: SetStandardView3D.h,v $
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
 *  $Id: SetStandardView3D.h,v 1.2 1996/12/06 16:47:15 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _SetStandardView3D_H
#define _SetStandardView3D_H

#include "booga/component/Operation3D.h"
#include "booga/object/Viewing3D.h"


//_____________________________________________________________________ SetStandardView3D

class SetStandardView3D : public Operation3D {
declareRTTI(SetStandardView3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  SetStandardView3D(Viewing3D::ViewPlane viewplane = Viewing3D::AUTOSELECT);
  // SetStandardView3D(const SetStandardView3D&);            // Use default version.

public:
  virtual ~SetStandardView3D();  

public:
  // SetStandardView3D& operator=(const SetStandardView3D&);  // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class SetStandardView3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setHFov(double hfov);
  void setViewPlane(Viewing3D::ViewPlane viewplane);
  void setResolution(int resX, int resY);
  // Result accessors.
  //
  // Usage:
  //
  //    SetStandardView3D p(Viewing3D::XZ_PLANE);
  //    p.execute(world);
  //

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool doExecute();
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  int myResX;
  int myResY;
  double myHFov;
  Viewing3D::ViewPlane myViewPlane;
};

//______________________________________________________________________ INLINES
#endif 
