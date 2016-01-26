/*
 * $RCSfile: PointLight.h,v $
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
 *  $Id: PointLight.h,v 1.13 1996/10/04 09:47:56 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PointLight_H
#define _PointLight_H

#include "booga/object/Sphere3D.h"
#include "booga/object/DirectedLight.h"

//___________________________________________________________________ PointLight

class PointLight : public DirectedLight {
declareRTTI(PointLight);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PointLight(Exemplar);
  PointLight(Real luminance = 0, const Color& color = Color::getDefault());
  // PointLight(const PointLight&);          // Use default version.

public:
  // virtual ~PointLight();                  // Use default version.
  
private:
  PointLight& operator=(const PointLight&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class PointLight
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setRadius(Real radius);
  Real getRadius() const;
  
  void setPosition(const Vector3D& position);
  const Vector3D& getPosition() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class DirectedLight
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void getDirection(Texture3DContext& context) const;
  virtual bool isVisible(Texture3DContext& context) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* copy() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual RCString getKeyword() const;
  virtual void iterateAttributes(MakeableHandler* handler);
};

//______________________________________________________________________ INLINES

inline Real PointLight::getRadius() const
{
  return dynamic_cast<Sphere3D*>(myLightRep)->getRadius();
}
  
inline const Vector3D& PointLight::getPosition() const
{
  return dynamic_cast<Sphere3D*>(myLightRep)->getCenter();
}

#endif // _PointLight_H
