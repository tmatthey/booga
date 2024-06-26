/*
 * TumblePath3D.h
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
 *  $Id: TumblePath3D.h,v 1.3 1996/11/13 09:38:14 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _TumblePath3D_H
#define _TumblePath3D_H

#include "booga/nurbs/Nurbs3D.h"          
#include "booga/nurbs/Nurbs3DEvaluator.h"          
#include "booga/object/InterpolationCurve3D.h"          
#include "booga/animation/ActionInfoAttr.h"

// ____________________________________________________________________ TumblePath3D

class TumblePath3D : public ActionInfoAttr {
declareRTTI(TumblePath3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  TumblePath3D(Exemplar);
  TumblePath3D(AnimationFunction* function, Nurbs3DEvaluator* nurbsEvaluator, InterpolationCurve3D* curve);
  TumblePath3D(const TumblePath3D& tumblePath3D);

public:
  virtual ~TumblePath3D(); 
  
private:  
  TumblePath3D& operator=(const TumblePath3D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class TumblePath3D
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
  virtual List<Value*>* createParameters();
  virtual void iterateAttributes(MakeableHandler *handler);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  RCString myFunctionName;
  Real myStart;
  Real myEnd;
  Real myStep;
  Nurbs3D*  myNurbs;
  InterpolationCurve3D*  myCurve;
};
  
//______________________________________________________________________ INLINES
 

#endif // _TumblePath3D_H
