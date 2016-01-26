/*
 * Whitted.h
 *
 * Copyright (C) 1995, Stephan Amann <amann@iam.unibe.ch>
 *                     Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: Whitted.h,v 1.3 1996/10/04 11:33:48 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Whitted_H
# define _Whitted_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/Color.h"
#include "booga/object/Texture3D.h"

//______________________________________________________________________ Whitted

class Whitted : public Texture3D {
declareRTTI(Whitted);
// enable RTTI support

public:
  Whitted();
  // Whitted(const Whitted&);  // Use default version.
  Whitted(Exemplar);
  // ~Whitted();               // Use default version.

  virtual Texture3D* copy() const;
  virtual void doTexturing(Texture3DContext& context) const;

  // ------------------------------------------- set & get for attributes

  const Color& getAmbient() const;
  void setAmbient(const Color& ambient);
  
  const Color& getDiffuse() const;
  void setDiffuse(const Color& diffuse);
  
  Real getTransparency() const;
  void setTransparency(Real transparency);
  
  Real getReflectivity() const;
  void setReflectivity(Real reflectivity);
  
  Real getRefractionIndex() const;
  void setRefractionIndex(Real refractionIndex);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual RCString getKeyword() const;
  virtual void iterateAttributes(MakeableHandler *handler);
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);


private:
  Color myAmbient;
  Color myDiffuse;
  Real myTransparency;
  Real myReflectivity;
  Real myRefractionIndex;

private:
  Whitted& operator=(const Whitted&);  // No assignments.
};

//______________________________________________________________________ INLINES

inline const Color& Whitted::getAmbient() const
{
  return myAmbient;
}

inline void Whitted::setAmbient(const Color& ambient)
{
  myAmbient = ambient;
}

inline const Color& Whitted::getDiffuse() const
{
  return myDiffuse;
}

inline void Whitted::setDiffuse(const Color& diffuse)
{
  myDiffuse = diffuse;
}

inline Real Whitted::getTransparency() const
{
  return myTransparency;
}

inline void Whitted::setTransparency(Real transparency)
{
  myTransparency = transparency;
}

inline Real Whitted::getReflectivity() const
{
  return myReflectivity;
}

inline void Whitted::setReflectivity(Real reflectivity)
{
  myReflectivity = reflectivity;
}

inline Real Whitted::getRefractionIndex() const
{
  return myRefractionIndex;
}

inline void Whitted::setRefractionIndex(Real refractionIndex)
{
  myRefractionIndex = refractionIndex;
}

#endif // _Whitted_H
