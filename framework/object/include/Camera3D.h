/*
 * $RCSfile: Camera3D.h,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: Camera3D.h,v 1.15 1996/10/04 09:46:05 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Camera3D_H
#define _Camera3D_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/Color.h"
#include "booga/object/Object3D.h"

class Viewing3D;

//_____________________________________________________________________ Camera3D

class Camera3D : public Object3D {
declareRTTI(Camera3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Camera3D();
  Camera3D(Exemplar);
protected:
  Camera3D(const Camera3D& Camera3D);    // Internal use only.

public:
  virtual ~Camera3D();

private:
  Camera3D& operator=(const Camera3D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Camera3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void turnOn();
  void turnOff();
  bool isOn() const;
  
  const Color& getBackground() const;
  void setBackground(const Color& bgColor);

  Viewing3D* getViewing() const;
  void adoptViewing(Viewing3D* viewing);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* copy() const;
  virtual Object3D* makeUnique(Path3D* path = NULL, bool shared = false);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual long countSubobject() const;
  virtual Object3D* getSubobject(long index);
protected:
  virtual void doComputeBounds();
private:
  virtual bool doIntersect(Ray3D& ray);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual RCString getKeyword() const;
  virtual void iterateAttributes(MakeableHandler* handler);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Viewing3D* myViewing;
  bool myIsOn;
  Color myBackgroundColor;
};

//______________________________________________________________________ INLINES

inline void Camera3D::turnOn()
{
  myIsOn = true;
}

inline void Camera3D::turnOff()
{
  myIsOn = false;
}

inline bool Camera3D::isOn() const
{
  return myIsOn;
}

inline const Color& Camera3D::getBackground() const
{
  return myBackgroundColor;
}

inline void Camera3D::setBackground(const Color& bgColor)
{
  myBackgroundColor = bgColor;
}

inline Viewing3D* Camera3D::getViewing() const
{
  return myViewing;
}

#endif // _Camera3D_H
