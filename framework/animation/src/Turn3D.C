/*
 * $RCSfile: Turn3D.C,v $
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
 *  $Id: Turn3D.C,v 1.4 1996/11/13 09:38:15 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/mathutilities.h"
#include "booga/base/Report.h"
#include "booga/base/Value.h"
#include "booga/base/Vector3D.h"
#include "booga/object/Transform3D.h"
#include "booga/animation/ActionInfo.h"
#include "booga/animation/Turn3D.h"

// ____________________________________________________________________ Turn3D

implementRTTI(Turn3D, Animation3D);

Turn3D::Turn3D(Exemplar)
{
}

bool Turn3D::doFrame(Real frame)
{  
  TransMatrix3D transform;
  
  for(long i = 0; i < myActionList.count() ; i++){
    ActionInfo* item = myActionList.item(i);
    Real ticks;
    
    if (item->isTurn()) {
      Vector3D v;

      if (item->isBound())
        v = 0.5*(myAnimatedObjects->getBounds().getMin()+myAnimatedObjects->getBounds().getMax());
      else
        v = item->getCenter();

      ticks = item->computeTicks(frame);
      Real alpha = (item->getAlpha() * ticks * M_PI) / 180.0;
      transform.translate(-v);
      transform.rotate(item->getAxis(),alpha); 
      transform.translate(v);

    }
    else {
      std::stringstream os;
      os << "[Turn3D::doTicks] action ("
         <<  item->getStartFrame() << ","
         <<  item->getEndFrame() << ") not of type Turn3D. Skip";
      Report::recoverable(os);     
    }
  }
  return doTransform(transform);
}  


Object3D* Turn3D::copy() const
{
  return new Turn3D(*this);
}

Makeable* Turn3D::make(RCString& , const List<Value*>* ) const
{
  Turn3D* newTurn = new Turn3D(*this);
  return newTurn;
}

static const RCString turnKeyword("turn");

RCString Turn3D::getKeyword() const 
{
  return turnKeyword;
}
