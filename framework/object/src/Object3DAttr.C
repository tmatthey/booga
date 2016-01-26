/*
 * $RCSfile: Object3DAttr.C,v $ 
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
 *  $Id: Object3DAttr.C,v 1.2 1996/08/07 09:21:07 amann Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/object/Object3DAttr.h"
#include "booga/object/Object3D.h"

//_____________________________________________________________________ Object3DAttr

implementRTTI(Object3DAttr, ObjectAttr);

//_____________________________________________________________________ Object3DAttrObject

implementRTTI(Object3DAttrObject, Object3DAttr);

Object3DAttrObject::Object3DAttrObject()
: myObject(NULL)
{}

Object3DAttrObject::Object3DAttrObject(Exemplar)
: myObject(NULL)
{}

int Object3DAttrObject::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  myObject = dynamic_cast<Object3D*>(specifier);

  if (myObject != NULL)
    return 1;

  errMsg = "expecting Object3D, type was "  + RCString(typeid(specifier).name());
  return 0;
}
