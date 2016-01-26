/*
 * $RCSfile: InterpolatorTexture2D.h,v $
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
 *  $Id: InterpolatorTexture2D.h,v 1.3 1996/08/30 13:53:18 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _InterpolatorTexture2D_H
#define _InterpolatorTexture2D_H

#include "booga/base/Color.h"
#include "booga/object/Texture2D.h"

//________________________________________________________ InterpolatorTexture2D

class InterpolatorTexture2D : public Texture2D {
declareRTTI(InterpolatorTexture2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  InterpolatorTexture2D();
  InterpolatorTexture2D(Exemplar);
  // InterpolatorTexture2D(const InterpolatorTexture2D&);            //  Use default version.

public:
  // virtual ~InterpolatorTexture2D();                               //  Use default version.

public:
  // InterpolatorTexture2D& operator=(const InterpolatorTexture2D&); // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class InterpolatorTexture2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setColor(const Color& from, const Color& to);
  const Color& getColorFrom() const;
  const Color& getColorTo() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Texture2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Texture2D* copy() const;
  virtual void doTexturing(Texture2DContext& context) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual RCString getKeyword() const;
  virtual List<Value*>* createParameters();
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Color myColorFrom;
  Color myColorTo;
};

//______________________________________________________________________ INLINES

inline void InterpolatorTexture2D::setColor(const Color& from, const Color& to)
{
  myColorFrom = from;
  myColorTo = to;
}

inline const Color& InterpolatorTexture2D::getColorFrom() const
{
  return myColorFrom;
}

inline const Color& InterpolatorTexture2D::getColorTo() const
{
  return myColorTo;
}

#endif // _InterpolatorTexture2D_H

