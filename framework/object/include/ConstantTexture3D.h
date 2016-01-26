/*
 * ConstantTexture3D.h 
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
 *  $Id: ConstantTexture3D.h,v 1.6 1996/10/04 09:46:25 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ConstantTexture3D_H
# define _ConstantTexture3D_H

#include "booga/base/mathutilities.h"
#include "booga/base/Color.h"
#include "booga/object/Texture3D.h"

//____________________________________________________________ ConstantTexture3D

class ConstantTexture3D : public Texture3D {
declareRTTI(ConstantTexture3D);
// enable RTTI support 

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  ConstantTexture3D(Exemplar);
  // ConstantTexture3D(const ConstantTexture3D&);  // Use default version.

public:
  // ~ConstantTexture3D();                         // Use default version.
  
private:
  ConstantTexture3D& operator=(const ConstantTexture3D&); //  No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class ConstantTexture3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  const Color& getColor() const;
  void setColor(const Color& color);

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
  Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual RCString getKeyword() const;
  virtual void iterateAttributes(MakeableHandler *handler);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Color myColor;
};

//______________________________________________________________________ INLINES

inline const Color& ConstantTexture3D::getColor() const
{
  return myColor;
}

inline void ConstantTexture3D::setColor(const Color& color)
{
  myColor = color;
}

#endif // _ConstantTexture3D_H

