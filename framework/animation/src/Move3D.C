/*
 * $RCSfile: Move3D.C,v $
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
 *  $Id: Move3D.C,v 1.4 1996/11/13 09:38:04 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include <strstream.h>
#include "booga/base/mathutilities.h"
#include "booga/base/Report.h"
#include "booga/base/Value.h"
#include "booga/base/Vector3D.h"
#include "booga/object/Transform3D.h"
#include "booga/animation/ActionInfo.h"
#include "booga/animation/Move3D.h"

// ____________________________________________________________________ Move3D

implementRTTI(Move3D, Animation3D);

Move3D::Move3D(Exemplar)
{
}

bool Move3D::doFrame(Real frame)
{
  TransMatrix3D transform;
    
  for(long i = 0; i < myActionList.count() ; i++){
    ActionInfo* item = myActionList.item(i);
    Real ticks;
   
    if (item->isMove()) {
      ticks = item->computeTicks(frame);
      transform.translate(item->getDirection()*ticks);

    }
    else {
      ostrstream os;
      os << "[Move3D::doTicks] action ("
         <<  item->getStartFrame() << ","
         <<  item->getEndFrame() << ") not of type Move3D. Skip";
      Report::recoverable(os);     
     }
    
  }

  return doTransform(transform);
}  

Object3D* Move3D::copy() const
{
  return new Move3D(*this);
}


Makeable* Move3D::make(RCString&, const List<Value*>* ) const
{
  Move3D* newMove = new Move3D(*this);

  return newMove;
}

static const RCString moveKeyword("move");

RCString Move3D::getKeyword() const 
{
  return moveKeyword;
}
