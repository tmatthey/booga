/*
 * $RCSfile: Shear3D.C,v $
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
 *  $Id: Shear3D.C,v 1.4 1996/11/13 09:38:06 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/mathutilities.h"
#include "booga/base/Report.h"
#include "booga/base/Value.h"
#include "booga/base/Vector3D.h"
#include "booga/base/Vector2D.h"
#include "booga/object/Transform3D.h"
#include "booga/animation/ActionInfo.h"
#include "booga/animation/Shear3D.h"

// ____________________________________________________________________ Shear3D

implementRTTI(Shear3D, Animation3D);

Shear3D::Shear3D(Exemplar)
{
}

bool Shear3D::doFrame(Real frame)
{  
  TransMatrix3D transform;
  
  for(long i = 0; i < myActionList.count() ; i++){
    ActionInfo* item = myActionList.item(i);
    Real ticks;
    
    if (item->isShear()) {
      Vector3D v;
      Real alpha;

      if (item->isBound())
        v = 0.5*(myAnimatedObjects->getBounds().getMin()+myAnimatedObjects->getBounds().getMax());
      else
        v = item->getCenter();

      Vector3D w(item->getAxis()*Vector3D(0,0,1));
      if (equal(w.length(), 0 )) {   // axis parallel to z axis?
        w = Vector3D(1,0,0);
        if (item->getAxis().z() > 0) // direction of axis towards positive z axis?   
          alpha = 0;
        else
          alpha = M_PI;
      }
      else
        alpha = acos(w.z() / w.length()); // cos(alpha) = (w * (0,0,1))/(|w|*|(0,0,1)|) 
      
      ticks = item->computeTicks(frame);
      Vector2D shearFactor(item->getShearFactor() * ticks);
      transform.translate(-v);
      transform.rotate(w,alpha);
      transform *= TransMatrix3D(Vector3D(1,0,0), Vector3D(0,1,0),
                                 Vector3D(shearFactor.x(),shearFactor.y(),1));
      transform.rotate(w,- alpha); 
      transform.translate(v);

    }
    else {
      ostrstream os;
      os << "[Shear3D::doTicks] action ("
         <<  item->getStartFrame() << ","
         <<  item->getEndFrame() << ") not of type Shear3D. Skip";
      Report::recoverable(os);     
    }
  }
  return doTransform(transform);
}  


Object3D* Shear3D::copy() const
{
  return new Shear3D(*this);
}

Makeable* Shear3D::make(RCString& , const List<Value*>* ) const
{
  Shear3D* newTurn = new Shear3D(*this);
  return newTurn;
}
static const RCString shearKeyword("shear");

RCString Shear3D::getKeyword() const 
{
  return shearKeyword;
}
