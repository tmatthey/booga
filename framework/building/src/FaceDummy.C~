/*
 * $RCSfile: FaceDummy.C,v $
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
 *  $Id: FaceDummy.C,v 1.3 1997/02/06 14:13:43 matthey Exp matthey $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/List.h"
#include "booga/building/FaceDummy.h"
#include "booga/building/Building.h"
#include "booga/object/NullObject3D.h"

// ____________________________________________________________________ FaceDummy

implementRTTI(FaceDummy, Face);

FaceDummy::FaceDummy()
:Face()
{
}

FaceDummy::FaceDummy(const Vector2D& from, const Vector2D& to, long frontindex, long polygonindex)
{
  setFrom(from);
  setTo(to);
  setFrontIndex(frontindex);
  setPolygonIndex(polygonindex);
}

FaceDummy::FaceDummy(const FaceDummy& face) 
: Face(face), myHoles(face.myHoles)  
{}

Object3D* FaceDummy::copy() const
{
  return new FaceDummy(*this);
}

Object3D* FaceDummy::doCreateSubject(Building*) const
{
  return new NullObject3D();
}

Makeable* FaceDummy::make(RCString&, const List<Value*>*) const
{
  return NULL;
}

List<List<Vector3D> > FaceDummy::getAlternativeHoles(Building* building) const
{
  List<List<Vector3D> > holes;
  List<Vector3D> temp;

  Real x = getWidth(building);
  Real y = building->getHeight();

  for(long i=0; i< myHoles.count(); i++){
    temp.removeAll();
    for(long j=0; j<myHoles.item(i).count(); j++)
      temp.append(Vector3D(myHoles.item(i).item(j).x()*x,
                           myHoles.item(i).item(j).y()*y,
                           0));
    holes.append(temp);
  }
            
  return holes;
}
