/*
 * LightSource.h
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: LightSource.h,v 1.12 1996/10/04 09:46:45 collison Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _LightSource_H
#define _LightSource_H

#include "booga/base/Color.h"
#include "booga/object/Object3D.h"
#include "booga/object/Texture3DContext.h"

//__________________________________________________________________ LightSource

class LightSource : public Object3D {
declareRTTI(LightSource);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:  
  LightSource(Exemplar);
  LightSource(Real luminance = 0, const Color& color = Color::getDefault());
protected:
  LightSource(const LightSource& lightSource);

public:
  virtual ~LightSource();

private:
  LightSource& operator=(const LightSource&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class LightSource
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setLuminance(Real luminance);
  Real getLuminance() const;

  void setColor(const Color& color);
  const Color&  getColor() const;

  void turnOn();
  void turnOff();
  bool isOn() const;

  void getIllumination(Texture3DContext& context) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
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
  virtual List<Value*>* createParameters();
  virtual void iterateAttributes(MakeableHandler *handler);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  Object3D* myLightRep;
  
private:
  Real myLuminance;
  Color myColor;
  bool myIsOn;
};

//______________________________________________________________________ INLINES

inline void LightSource::setLuminance(Real luminance)
{
  myLuminance = luminance;
}

inline Real LightSource::getLuminance() const
{
  return myLuminance;
}

inline void LightSource::setColor(const Color& color)
{
  myColor = color;
}

inline const Color&  LightSource::getColor() const
{
  return myColor;
}

inline void LightSource::turnOn()
{
  myIsOn = true;
}

inline void LightSource::turnOff()
{
  myIsOn = false;
}

inline bool LightSource::isOn() const
{
  return myIsOn;
}

inline void LightSource::getIllumination(Texture3DContext& context) const
{
  context.setIllumination(myColor*(float)myLuminance);
}

#endif // _LightSource_H
