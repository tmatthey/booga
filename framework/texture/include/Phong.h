/*
 * Phong.h
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
 *  $Id: Phong.h,v 1.4 1996/10/04 11:33:45 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Phong_H
#define _Phong_H

#include "booga/base/Color.h"
#include "booga/object/Texture3D.h"

//________________________________________________________________________ Phong

class Phong : public Texture3D {
declareRTTI(Phong);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Phong();
  Phong(Exemplar);
  // Phong(const Phong&);         // Use default version.

public:
  // ~Phong();                    // Use default version.
  
private:
  Phong& operator=(const Phong&); //  No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Phong
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  const Color& getAmbient() const;
  void setAmbient(const Color& ambient);
  
  const Color& getDiffuse() const;
  void setDiffuse(const Color& diffuse);

  const Color& getSpecular() const;
  void setSpecular(const Color& specular);
  
  int getSpecPow() const;
  void setSpecPow(int specPow);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Texture3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void doTexturing(Texture3DContext& context) const;
  virtual Texture3D* copy() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual RCString getKeyword() const;
  virtual void iterateAttributes(MakeableHandler *handler);
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Color myAmbient;
  Color myDiffuse;
  Color mySpecular;
  int mySpecPow;
};

//______________________________________________________________________ INLINES

inline const Color& Phong::getAmbient() const
{
  return myAmbient;
}

inline void Phong::setAmbient(const Color& ambient)
{
  myAmbient = ambient;
}

inline const Color& Phong::getDiffuse() const
{
  return myDiffuse;
}

inline void Phong::setDiffuse(const Color& diffuse)
{
  myDiffuse = diffuse;
}

inline const Color& Phong::getSpecular() const
{
  return mySpecular;
}

inline void Phong::setSpecular(const Color& specular)
{
  mySpecular = specular;
}

inline int Phong::getSpecPow() const
{
  return mySpecPow;
}

inline void Phong::setSpecPow(int specPow)
{
  mySpecPow = specPow;
}

#endif // _Phong_H
