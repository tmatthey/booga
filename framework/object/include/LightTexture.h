/*
 * LightTexture.h
 *
 * LightTextures are internally attached to LightSources in order to render
 * the light source itself.
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
 *  $Id: LightTexture.h,v 1.4 1996/02/23 07:33:58 streit Exp buhlmann $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _LightTexture_H
#define _LightTexture_H

#include "booga/base/Color.h"
#include "booga/object/Texture3D.h"

//_________________________________________________________________ LightTexture

class LightTexture : public Texture3D {
declareRTTI(LightTexture);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  LightTexture(const Color& color);
  // LightTexture(const LightTexture&);          // Use default version.

public:
  // virtual ~LightTexture();                    // Use default version.
  
private:
  LightTexture& operator=(const LightTexture&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class LightTexture
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  const Color& getColor() const;
  void setColor(const Color& color);

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
  virtual RCString getKeyword() const;
  virtual void iterateAttributes(MakeableHandler *handler);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Color myColor;
};

//______________________________________________________________________ INLINES

inline const Color& LightTexture::getColor() const
{
  return myColor;
}

inline void LightTexture::setColor(const Color& color)
{
  myColor = color;
}

#endif // _LightTexture_H
