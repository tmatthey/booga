/*
 * Matte.h 
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
 *  $Id: Matte.h,v 1.4 1996/10/04 11:33:41 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Matte_H
# define _Matte_H

#include "booga/base/mathutilities.h"
#include "booga/base/Color.h"
#include "booga/object/Texture3D.h"

//_______________________________________________________________________ Matte

class Matte : public Texture3D {
  declareRTTI(Matte);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Matte();
  Matte(Exemplar);
  // Matte(const Matte&);         // Use default version.

public:
  // ~Matte();                    // Use default version.
  
private:
  Matte& operator=(const Matte&); //  No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Matte
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  const Color& getAmbient() const;
  void setAmbient(const Color& ambient);
  
  const Color& getDiffuse() const;
  void setDiffuse(const Color& diffuse);

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
};

//______________________________________________________________________ INLINES

inline const Color& Matte::getAmbient() const
{
  return myAmbient;
}

inline void Matte::setAmbient(const Color& ambient)
{
  myAmbient = ambient;
}

inline const Color& Matte::getDiffuse() const
{
  return myDiffuse;
}

inline void Matte::setDiffuse(const Color& diffuse)
{
  myDiffuse = diffuse;
}

#endif // _Matte_H

