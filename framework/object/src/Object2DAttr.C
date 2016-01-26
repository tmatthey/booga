/*
 * $RCSfile: Object2DAttr.C,v $ 
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
 *  $Id: Object2DAttr.C,v 1.1 1996/08/07 09:21:05 amann Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/object/Object2DAttr.h"
#include "booga/object/Object2D.h"

//_____________________________________________________________________ Object2DAttr

implementRTTI(Object2DAttr, ObjectAttr);

//_____________________________________________________________________ Object2DAttrObject

implementRTTI(Object2DAttrObject, Object2DAttr);

Object2DAttrObject::Object2DAttrObject()
: myObject(NULL)
{}

Object2DAttrObject::Object2DAttrObject(Exemplar)
: myObject(NULL)
{}

int Object2DAttrObject::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  myObject = dynamic_cast<Object2D*>(specifier);

  if (myObject != NULL)
    return 1;

  errMsg = "expecting Object2D, type was "  + RCString(typeid(specifier).name());
  return 0;
}
