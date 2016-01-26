/*
 * $RCSfile: BuildingAttr.C,v $
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
 *  $Id: BuildingAttr.C,v 1.2 1997/02/20 09:39:56 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Value.h"
#include "booga/building/BuildingAttr.h"

//_____________________________________________________________ BuildingAttr

implementRTTI(BuildingAttr, Makeable);

//_________________________________________________ BuildingAttrHole

implementRTTI(BuildingAttrHole, BuildingAttr);

BuildingAttrHole::BuildingAttrHole(const List<Vector3D>& vertices)
: myVertices(vertices)
{
}

Makeable* BuildingAttrHole::make(RCString& errMsg,
                                             const List<Value*>* parameters) const
{
  List<Vector3D> vertices;
  if (parameters != NULL) {
    for (int i=1; i<=parameters->count(); i++){
      getParameter(i, Vector3D, vertex);
      if (i > 1) {
        if (vertices.item(i-2) == vertex) {
          std::stringstream os;
          os << "[BuildingAttrHole::make] two consecutive vertices ("
             << vertex << ") must not have the same value";
          Report::recoverable(os);
          return NULL;
        }
     }
     vertices.append(vertex);
    }
  }
  return new BuildingAttrHole(vertices);
}

void BuildingAttrHole::setAttribute(Building* building) const
{
  building->addHole(myVertices);
}

//_________________________________________________________ BuildingAttrOn

implementRTTI(BuildingAttrOn, BuildingAttr);

Makeable* BuildingAttrOn::make(RCString& errMsg,
                                     const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new BuildingAttrOn(anExemplar);
}

void BuildingAttrOn::setAttribute(Building* building) const
{
  building->turnOn();
}

//________________________________________________________ BuildingAttrOff

implementRTTI(BuildingAttrOff, BuildingAttr);

Makeable* BuildingAttrOff::make(RCString& errMsg,
                                      const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new BuildingAttrOff(anExemplar);
}

void BuildingAttrOff::setAttribute(Building* building) const
{
  building->turnOff();
}


