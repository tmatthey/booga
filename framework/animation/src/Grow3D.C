/*
 * $RCSfile: Grow3D.C,v $
 *
 * Copyright (C) 1995-96, Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: Grow3D.C,v 1.4 1996/11/13 09:38:02 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/mathutilities.h"
#include "booga/base/Report.h"
#include "booga/base/Value.h"
#include "booga/base/Vector3D.h"
#include "booga/object/Transform3D.h"
#include "booga/animation/ActionInfo.h"
#include "booga/animation/Grow3D.h"

// ____________________________________________________________________ Grow3D

implementRTTI(Grow3D, Animation3D);

Grow3D::Grow3D(Exemplar)
{
}

bool Grow3D::doFrame(Real frame)
{
  TransMatrix3D transform;
  
  for(long i = 0; i < myActionList.count() ; i++){
    ActionInfo* item = myActionList.item(i);
    Real ticks;
    
    if (item->isGrow()) {
      Vector3D v;

      if (item->isBound())
        v = 0.5*(myAnimatedObjects->getBounds().getMin()+myAnimatedObjects->getBounds().getMax());
      else
        v = item->getCenter();

      ticks = item->computeTicks(frame);

      transform.translate(-v);
      transform.scale(Vector3D(1,1,1) + (item->getScaleFactor() - Vector3D(1,1,1))*ticks);
      transform.translate(v);

    }
    else {
      ostrstream os;
      os << "[Grow3D::doTicks] action ("
         <<  item->getStartFrame() << ","
         <<  item->getEndFrame() << ") not of type Grow3D. Skip";
      Report::recoverable(os);     
     }
  }
  
  return doTransform(transform);
}  

Object3D* Grow3D::copy() const
{
  return new Grow3D(*this);
}


Makeable* Grow3D::make(RCString&, const List<Value*>*) const
{
  Grow3D* newGrow = new Grow3D(*this);
  return newGrow;
}

static const RCString growKeyword("grow");

RCString Grow3D::getKeyword() const 
{
  return growKeyword;
}
