/*
 * TumbleDirection3D.h
 *
 * Copyright (C) 1995-96, Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: TumbleDirection3D.h,v 1.3 1996/11/13 09:38:12 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _TumbleDirection3D_H
#define _TumbleDirection3D_H

#include "booga/object/InterpolationCurve3D.h"          
#include "booga/nurbs/Nurbs3D.h"          
#include "booga/animation/ActionInfoAttr.h"

// ____________________________________________________________________ TumbleDirection3D

class TumbleDirection3D : public ActionInfoAttr {
declareRTTI(TumbleDirection3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  TumbleDirection3D(Exemplar);
  TumbleDirection3D(Nurbs3DEvaluator* nurbsEvaluator, InterpolationCurve3D* curve);
  TumbleDirection3D(const TumbleDirection3D& tumbleDirection3D);

public:
  virtual ~TumbleDirection3D(); 
  
private:  
  TumbleDirection3D& operator=(const TumbleDirection3D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class TumbleDirection3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class ActionInfoAttr
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void setAttribute(ActionInfo* actionInfo) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual RCString getKeyword() const; 
  virtual void iterateAttributes(MakeableHandler *handler);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  InterpolationCurve3D*  myCurve;
  Nurbs3D*  myNurbs;
};
  
//______________________________________________________________________ INLINES
 

#endif // _TumbleDirection3D_H
