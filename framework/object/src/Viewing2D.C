/*
 * Viewing2D.C
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
 *  $Id: Viewing2D.C,v 1.7 1996/10/04 09:49:00 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Report.h"
#include "booga/object/Viewing2D.h"

//____________________________________________________________________ Viewing2D

Viewing2D::Viewing2D()
{
  myWindowOrigin = Vector2D(0,0);
  myWindowSize = Vector2D(1,1);
  myResolutionX = myResolutionY = 512;
  computeConversionFactor();
}

void Viewing2D::setWindow(const Vector2D& origin, const Vector2D& resolution)
{
  if (equal(resolution.x(), 0) || equal(resolution.y(), 0))
    Report::error("[Viewing2D::setWindow] illegal window resolution settings");

  myWindowOrigin = origin;
  myWindowSize = resolution;
  computeConversionFactor();
}

void Viewing2D::setResolution(int resX, int resY)
{
  if ((resX <= 0) || (resY <= 0))
    Report::error("[Viewing2D::setResolution] illegal resolution settings");

  myResolutionX = resX;
  myResolutionY = resY;
  computeConversionFactor();
}

Vector2D Viewing2D::transformWorld2Screen(const Vector2D& p) const
{
  Vector2D tmp = p-myWindowOrigin;

  return Vector2D(myConversionFactor.x()*tmp.x(),
		myConversionFactor.y()*tmp.y());
}

Vector2D Viewing2D::transformScreen2World(const Vector2D& p) const
{
  return Vector2D(p.x()/myConversionFactor.x() + myWindowOrigin.x(),
		p.y()/myConversionFactor.y() + myWindowOrigin.y());
}

void Viewing2D::computeRayThrough(int x, int y, Ray2D& ray) const
{
  ray.setOrigin(Vector2D(Real(x)/myConversionFactor.x() + myWindowOrigin.x(),
                         Real(y)/myConversionFactor.y() + myWindowOrigin.y()));
}

void Viewing2D::computeConversionFactor()
{
  myConversionFactor.x() = myResolutionX/myWindowSize.x();
  myConversionFactor.y() = myResolutionY/myWindowSize.y();
}

ostream& operator<<(ostream& os, const Viewing2D& view)
{
  os << "Resolution : " << view.myResolutionX << " " 
                        << view.myResolutionY << endl
     << "Window     : " << view.myWindowSize << endl;

  return os;
}
