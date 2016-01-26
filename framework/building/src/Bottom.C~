/*
 * $RCSfile: Bottom.C,v $
 *
 * Copyright (C) 1996, Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: Bottom.C,v 1.3 1997/02/20 09:39:50 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Report.h"
#include "booga/base/Value.h"
#include "booga/building/Bottom.h"
#include "booga/building/BottomAttr.h"
#include "booga/building/Building.h"
#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"

// ____________________________________________________________________ Bottom

implementRTTI(Bottom, BuildingObject);

Bottom::Bottom(Exemplar exemplar)
:BuildingObject(exemplar)
{
  myHeight = 0;
}

Bottom::Bottom()
{
  myHeight = 0;
}

Bottom::Bottom(const Bottom& bottom) : BuildingObject(bottom)
{
  myHeight = bottom.myHeight;
}

Object3D* Bottom::createSubject(Building* building) const
{
  if (building->getHeight() < EPSILON || ! isOn())
    return new NullObject3D();

  Bottom* This = (Bottom*)this;
  This->setTransform(TransMatrix3D::makeTranslate(0,0,getHeight()));
  return doCreateSubject(building);
}

int Bottom::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  // Check for Bottom attributes
  BottomAttr* attr = dynamic_cast(BottomAttr, specifier);
  if (attr != NULL) {
    // The Bottom object knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute(this);

    delete attr;
    return 1;  
  }

  // 
  // Let papa do the rest ...
  //
  return BuildingObject::setSpecifier(errMsg, specifier);
}

void Bottom::iterateAttributes(MakeableHandler *handler) {
  this->BuildingObject::iterateAttributes(handler);
  if (!equal(myHeight,0)) {
    DummyMakeable height("height");
    height.addParameter(Value(myHeight));
    handler->handle(&height);
  }
}
