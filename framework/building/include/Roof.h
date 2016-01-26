/*
 * $RCSfile: Roof.h,v $
 *
 * Copyright (C) 1996, Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: Roof.h,v 1.1 1997/01/17 10:35:36 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Roof_H
#define _Roof_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/building/BuildingObject.h"

class Building;

// ____________________________________________________________________ Roof

class Roof : public BuildingObject {
declareRTTI(Roof);
// enable RTTI support

public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Roof();
  Roof(Exemplar exemplar);
  Roof(const Roof& roof);      

public:
  // virtual ~Roof();   
  
private:  
  Roof& operator=(const Roof&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Roof
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setLedge(Real ledge);
  Real getLedge() const;
  Real getHeight() const;
  void setHeight(Real);
  void ledgeOn();
  void ledgeOff();
  bool isLedge() const;
  
protected:
  List<Vector3D> computeLedge(const List<Vector3D>& vertices) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class BuildingObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  virtual Object3D* createSubject(Building* building) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual void iterateAttributes(MakeableHandler* handler);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:              // definition of roof
  Real myLedge;
  Real myHeight;   
  bool myLedgeFlag;  
};

//______________________________________________________________________ INLINES

inline void Roof::setLedge(Real ledge)
{
  myLedge = ledge;
}

inline Real Roof::getLedge() const
{
  return myLedge;
}

inline Real Roof::getHeight() const
{
  return myHeight;
}

inline void Roof::setHeight(Real height)
{
  myHeight = height;
}

inline void Roof::ledgeOn()
{
  myLedgeFlag = true;
}

inline void Roof::ledgeOff()
{
  myLedgeFlag = false;
}

inline bool Roof::isLedge() const
{
  return myLedgeFlag;
}

#endif // _Roof_H
