/*
 * $RCSfile: Tumble3D.C,v $
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
 *  $Id: Tumble3D.C,v 1.4 1996/11/13 09:38:07 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/mathutilities.h"
#include "booga/base/Report.h"
#include "booga/base/Value.h"
#include "booga/base/Vector3D.h"
#include "booga/object/Transform3D.h"
#include "booga/animation/ActionInfo.h"
#include "booga/animation/Tumble3D.h"

// ____________________________________________________________________ Tumble3D

implementRTTI(Tumble3D, Animation3D);

Tumble3D::Tumble3D(){}

Tumble3D::Tumble3D(Exemplar){}

bool Tumble3D::doFrame(Real frame)
{  
  TransMatrix3D transform;
  
  for(long i = 0; i < myActionList.count() ; i++){
    ActionInfo* item = myActionList.item(i);
    
    if (item->isTumble()) {
      Real u = item->computeValue(frame);
      if (u < 0)
        u = 0;
      if (u > 1)
        u = 1;
      Real alpha;
      if (item->isTumbleRotate()) {
        Vector3D v(item->getTumbleCenter(u));
        Vector3D x(item->getTumbleDirection(0).normalized());
        Vector3D y(item->getTumbleDirection(u).normalized());
        if ((equal(x.length(),0)) || (equal(y.length(),0))) {
          ostrstream os;
          os << "[Tumble3D::doTicks]  no rotation (u = " << u << "), tumbledirection is zero";
          Report::recoverable(os);             
        }
        else {
          Vector3D w(x * y);
          if (equal(w.length(), 0 )) { // actual axis parallel to start axis ?
            if (x == y) {              // direction of actual axis the same as start axis?   
              alpha = 0;
              w = Vector3D(1,0,0);     // no rotation
            }
            else {
              ostrstream os;
              os << "[Tumble3D::doTicks] rotation at u = " << u << " maybe not correct";
              Report::recoverable(os);
              u -= 2 * EPSILON;          // !!! dirty - but it works !!!
              if (u < 0)
                u = 0;           
              y = item->getTumbleDirection(u).normalized(); // try this direction
              w = x * y;
              alpha = M_PI;
            }
          }
          else {
            alpha = acos(x ^ y); // cos(alpha) = (x ^ y)/(|x|*|y|) 
          }
          transform.translate(-v);
          transform.rotate(w,alpha);
          transform.translate(v);
        }
      }
      transform.translate(item->getTumbleMove(u));
    }
    else {
      ostrstream os;
      os << "[Tumble3D::doTicks] action ("
         <<  item->getStartFrame() << ","
         <<  item->getEndFrame() << ") not of type Tumble3D. Skip";
      Report::recoverable(os);     
    }
  }
  return doTransform(transform);
}  


Object3D* Tumble3D::copy() const
{
  return new Tumble3D(*this);
}

Makeable* Tumble3D::make(RCString& , const List<Value*>* ) const
{
  Tumble3D* newTurn = new Tumble3D(*this);
  return newTurn;
}

static const RCString tumbleKeyword("tumble");

RCString Tumble3D::getKeyword() const 
{
  return tumbleKeyword;
}
