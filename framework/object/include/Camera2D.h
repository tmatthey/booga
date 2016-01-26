/*
 * $RCSfile: Camera2D.h,v $
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
 * for any purpose. It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: Camera2D.h,v 1.14 1996/10/04 09:46:01 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Camera2D_H
#define _Camera2D_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/Color.h"
#include "booga/object/Viewing2D.h"
#include "booga/object/Object2D.h"

//_____________________________________________________________________ Camera2D

class Camera2D : public Object2D {
declareRTTI(Camera2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Camera2D();
  Camera2D(Exemplar);
protected:
  Camera2D(const Camera2D& Camera2D);    // Internal use only.

public:
  virtual ~Camera2D();

private:
  Camera2D& operator=(const Camera2D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Camera2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void turnOn();
  void turnOff();
  bool isOn() const;

  const Color& getBackground() const;
  void setBackground(const Color& bgColor);
  
  Viewing2D* getViewing() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object2D* copy() const;
  virtual Object2D* makeUnique(Path2D* path = NULL, bool shared = false);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual long countSubobject() const;
  virtual Object2D* getSubobject(long index);
protected:
  virtual void doComputeBounds();
private:
  virtual bool doIntersect(Ray2D& ray);

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
  Viewing2D* myViewing;
  bool myIsOn;
  Color myBackgroundColor;
};

//______________________________________________________________________ INLINES

inline void Camera2D::turnOn()
{
  myIsOn = true;
}

inline void Camera2D::turnOff()
{
  myIsOn = false;
}

inline bool Camera2D::isOn() const
{
  return myIsOn;
}

inline const Color& Camera2D::getBackground() const
{
  return myBackgroundColor;
}

inline void Camera2D::setBackground(const Color& bgColor)
{
  myBackgroundColor = bgColor;
}

inline Viewing2D* Camera2D::getViewing() const
{
  return myViewing;
}

#endif // _Camera2D_H

