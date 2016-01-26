/*
 * $RCSfile: BottomFlat.C,v $
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
 *  $Id: BottomFlat.C,v 1.7 1997/04/17 14:39:53 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Report.h"
#include "booga/base/Value.h"
#include "booga/object/Polygon3D.h"
#include "booga/building/BottomFlat.h"
#include "booga/building/Building.h"

// ____________________________________________________________________ BottomFlat

implementRTTI(BottomFlat, Bottom);

BottomFlat::BottomFlat(Exemplar exemplar)
:Bottom(exemplar)
{}

BottomFlat::BottomFlat()
{}

Object3D* BottomFlat::copy() const
{
  return new BottomFlat(*this);
}

Makeable* BottomFlat::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new BottomFlat(*this);
}

Object3D* BottomFlat::doCreateSubject(Building* building) const
{
  return new Polygon3D(building->getPolygon(0),building->getHoles());
}

static const RCString bottomflatKeyword("bottomflat");

RCString BottomFlat::getKeyword() const {
  return bottomflatKeyword;
}
