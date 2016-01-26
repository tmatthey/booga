/*
 * CheckerAttr.C
 *
 * Copyright (C) 1995, Christoph Streit <streit@iam.unibe.ch>
 *                     Stephan Amann <amann@iam.unibe.ch>
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: CheckerAttr.C,v 1.3 1995/08/15 14:02:03 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#include "booga/object/CheckerAttr.h"

//__________________________________________________________________ CheckerAttr

implementRTTI(CheckerAttr, Texture3DAttr);

//___________________________________________________________ CheckerAttrTexture

implementRTTI(CheckerAttrTexture, CheckerAttr);

CheckerAttrTexture::CheckerAttrTexture()
: myTexture(NULL)
{}

CheckerAttrTexture::CheckerAttrTexture(Exemplar)
: myTexture(NULL)
{}

int CheckerAttrTexture::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  myTexture = dynamic_cast<Texture3D*>(specifier);

  if (myTexture != NULL)
    return 1;

  errMsg = "expecting Texture3D, type was "  + RCString(typeid(specifier).name());
  return 0;
}

//______________________________________________________________ CheckerAttrEven

implementRTTI(CheckerAttrEven, CheckerAttrTexture);

CheckerAttrEven::CheckerAttrEven(Exemplar exemplar)
: CheckerAttrTexture(exemplar)
{}

Makeable* CheckerAttrEven::make(RCString& errMsg, 
				const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new CheckerAttrEven(anExemplar);
}

void CheckerAttrEven::setAttribute(Checker* checker) const
{
  checker->adoptEven(myTexture);
}

//_______________________________________________________________ CheckerAttrOdd

implementRTTI(CheckerAttrOdd, CheckerAttrTexture);

CheckerAttrOdd::CheckerAttrOdd(Exemplar exemplar)
: CheckerAttrTexture(exemplar)
{}

Makeable* CheckerAttrOdd::make(RCString& errMsg, 
			       const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new CheckerAttrOdd(anExemplar);
}

void CheckerAttrOdd::setAttribute(Checker* checker) const
{
  checker->adoptOdd(myTexture);
}

