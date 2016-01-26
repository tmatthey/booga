/*
 * $RCSfile: Texture2DContext.C,v $
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
 *  $Id: Texture2DContext.C,v 1.5 1996/08/30 12:21:23 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Texture2DContext.h"

//_____________________________________________________________ Texture2DContext

Texture2DContext::Texture2DContext()
{
  myWorld        = NULL;
  myObject       = NULL;

  myIsPositionOCSValid = false;
  myIsPositionTCSValid = false;
}

void Texture2DContext::setOCS2WCS(const Transform2D& transform)
{
  myIsPositionOCSValid = false;
  
  myOCS2WCS = transform;
}

void Texture2DContext::setOCS2TCS(const Transform2D& transform)
{
  myIsPositionTCSValid = false;
  
  myOCS2TCS = transform;
}

const Vector2D& Texture2DContext::getPositionWCS() const
{
  return myPositionWCS;
}

const Vector2D& Texture2DContext::getPositionOCS() const
{
  if (!myIsPositionOCSValid) {
    ((Texture2DContext*)this)->myPositionOCS = myOCS2WCS.invTransformAsPoint(myPositionWCS);
    ((Texture2DContext*)this)->myIsPositionOCSValid = true;
  }

  return myPositionOCS;
}

const Vector2D& Texture2DContext::getPositionTCS() const
{
  if (!myIsPositionTCSValid) {
    ((Texture2DContext*)this)->myPositionTCS = myOCS2TCS.invTransformAsPoint(getPositionOCS());
    ((Texture2DContext*)this)->myIsPositionTCSValid = true;
  }
  
  return myPositionTCS;
}

void Texture2DContext::setPositionWCS(const Vector2D& position)
{
  myPositionWCS = position;

  myIsPositionOCSValid = false;
  myIsPositionTCSValid = false;
}

void Texture2DContext::setPositionOCS(const Vector2D& position)
{
  myIsPositionOCSValid = true;
  myIsPositionTCSValid = false;
  myPositionOCS = position;
  myPositionWCS = myOCS2WCS.transformAsPoint(myPositionOCS);
}

void Texture2DContext::setPositionTCS(const Vector2D& position)
{
  myPositionTCS = position;
  myIsPositionTCSValid = true;

  myPositionOCS = myOCS2TCS.transformAsPoint(myPositionTCS);
  myIsPositionOCSValid = true;
  myPositionWCS = myOCS2WCS.transformAsPoint(myPositionOCS);
}
