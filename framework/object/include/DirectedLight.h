/*
 * DirectedLight.h
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: DirectedLight.h,v 1.3 1996/02/09 08:29:57 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _DirectedLight_H
#define _DirectedLight_H

#include "booga/object/LightSource.h"

//________________________________________________________________ DirectedLight

class DirectedLight : public LightSource {
declareRTTI(DirectedLight);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  DirectedLight() {}
  DirectedLight(Exemplar exemplar) : LightSource(exemplar) {}
  DirectedLight(Real lum, Color color) : LightSource(lum, color) {}
protected:
  // DirectedLight(const DirectedLight&);           // Use default version.

public:
  // virtual ~DirectedLight();                      // Use default version.

private:
  DirectedLight& operator=(const DirectedLight&);   // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class DirectedLight
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void getDirection(Texture3DContext& context) const = 0;
  virtual bool isVisible(Texture3DContext& context) const = 0;
};

#endif // _DirectedLight_H

