/*
 * PatternTexture2DAttr.C
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
 *  $Id: PatternTexture2DAttr.C,v 1.1 1995/08/24 10:19:05 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#include "booga/object/PatternTexture2D.h"
#include "booga/object/PatternTexture2DAttr.h"

//_________________________________________________________ PatternTexture2DAttr

implementRTTI(PatternTexture2DAttr, Texture2DAttr);

//__________________________________________________ PatternTexture2DAttrTexture

implementRTTI(PatternTexture2DAttrTexture, PatternTexture2DAttr);

PatternTexture2DAttrTexture::PatternTexture2DAttrTexture()
: myTexture(NULL)
{}

PatternTexture2DAttrTexture::PatternTexture2DAttrTexture(Exemplar)
: myTexture(NULL)
{}

int PatternTexture2DAttrTexture::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  myTexture = dynamic_cast(Texture2D, specifier);

  if (myTexture != NULL)
    return 1;

  errMsg = "expecting Texture2D, type was "  + RCString(typeid(specifier).name());
  return 0;
}

//____________________________________________________ PatternTexture2DAttrSolid

implementRTTI(PatternTexture2DAttrSolid, PatternTexture2DAttrTexture);

PatternTexture2DAttrSolid::PatternTexture2DAttrSolid(Exemplar exemplar)
: PatternTexture2DAttrTexture(exemplar)
{}

Makeable* PatternTexture2DAttrSolid::make(RCString& errMsg, 
				      const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new PatternTexture2DAttrSolid(anExemplar);
}

void PatternTexture2DAttrSolid::setAttribute(PatternTexture2D* pattern) const
{
  pattern->adoptSolid(myTexture);
}

//______________________________________________________ PatternTexture2DAttrGap

implementRTTI(PatternTexture2DAttrGap, PatternTexture2DAttrTexture);

PatternTexture2DAttrGap::PatternTexture2DAttrGap(Exemplar exemplar)
: PatternTexture2DAttrTexture(exemplar)
{}

Makeable* PatternTexture2DAttrGap::make(RCString& errMsg, 
				    const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new PatternTexture2DAttrGap(anExemplar);
}

void PatternTexture2DAttrGap::setAttribute(PatternTexture2D* pattern) const
{
  pattern->adoptGap(myTexture);
}

