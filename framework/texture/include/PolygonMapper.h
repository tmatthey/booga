/*
 * $RCSfile: PolygonMapper.h,v $
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
 *  $Id: PolygonMapper.h,v 1.5 1997/05/01 14:02:19 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PolygonMapper_H
#define _PolygonMapper_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/Color.h"
#include "booga/object/Texture3D.h"
#include "booga/pixmapOp/ImageReaders.h"

//________________________________________________________________ PolygonMapper

class PolygonMapper : public Texture3D {
  declareRTTI(PolygonMapper);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PolygonMapper();
  PolygonMapper(Exemplar);
  PolygonMapper(const PolygonMapper& polyMapper);
  
public:
  virtual ~PolygonMapper();            

private:
  PolygonMapper& operator=(const PolygonMapper&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class PolygonMapper
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setBeta(Real beta);
  Real getBeta() const;
  
  void setXRatio(Real xratio);
  Real getXRatio() const;
  
  void setYRatio(Real yratio);
  Real getYRatio() const;
  
  virtual void adoptPixmap(AbstractPixmap* pixmap);
  const AbstractPixmap* getPixmap() const;
  void setPixmapName(const RCString& name);
  const RCString& getPixmapName() const;
  
  const Color& getAmbient() const;
  void setAmbient(const Color& ambient);

  const Color& getSpecular() const;
  void setSpecular(const Color& specular);
  
  int getSpecPow() const;
  void setSpecPow(int specPow);

  void setReflectivity(Real ratio);
  Real getReflectivity() const;
  
  const Vector3D& getNormal() const;
  void setNormal(const Vector3D& normal);

  void setDisplacement(const Vector2D& point);
  const Vector2D& getDisplacement()const;
 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Texture3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Texture3D* copy() const;
  virtual void doTexturing(Texture3DContext& context) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void iterateAttributes(MakeableHandler *handler);
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual RCString getKeyword() const;
  virtual List<Value*>* createParameters();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  AbstractPixmap* myPixmap;
  Real myXRatio;
  Real myYRatio;
  Real myBeta;
  Vector3D myNormal;
  Vector2D myDisplacement; // The relative displacement of the bitmap

  RCString myPixmapName;
  Color    myAmbient;
  Color    mySpecular;
  int      mySpecPow;
  Real     myReflectivity;

};

//______________________________________________________________________ INLINES

inline Real PolygonMapper::getBeta() const
{
  return myBeta;
}

inline void PolygonMapper::setBeta(Real beta)
{
  myBeta = beta;
}

inline void PolygonMapper::setXRatio(Real xratio)
{
  myXRatio = xratio;
}

inline Real PolygonMapper::getXRatio() const
{
  return myXRatio;
}

inline void PolygonMapper::setYRatio(Real yratio)
{
  myYRatio = yratio;
}

inline Real PolygonMapper::getYRatio() const
{
  return myYRatio;
}

inline const AbstractPixmap* PolygonMapper::getPixmap() const
{
  return myPixmap;
}

inline const Color& PolygonMapper::getSpecular() const
{
  return mySpecular;
}

inline void PolygonMapper::setSpecular(const Color& specular)
{
  mySpecular = specular;
}

inline int PolygonMapper::getSpecPow() const
{
  return mySpecPow;
}

inline void PolygonMapper::setSpecPow(int specPow)
{
  mySpecPow = specPow;
}

inline  void PolygonMapper::setReflectivity(Real ratio)
{
  myReflectivity = ratio;
}

inline Real PolygonMapper::getReflectivity() const
{
  return myReflectivity;
}

inline const Color& PolygonMapper::getAmbient() const
{
  return myAmbient;
}

inline void PolygonMapper::setAmbient(const Color& ambient)
{
  myAmbient = ambient;
}

inline const Vector3D& PolygonMapper::getNormal() const
{
  return myNormal;
}

inline const RCString& PolygonMapper::getPixmapName() const
{
  return myPixmapName;
}

inline void PolygonMapper::setPixmapName(const RCString& name)
{
  myPixmapName = name;
}

inline void PolygonMapper::setDisplacement(const Vector2D& point)
{
  myDisplacement = point;
}

inline const Vector2D& PolygonMapper::getDisplacement()const
{
  return myDisplacement;
}
#endif // _PolygonMapper_H
