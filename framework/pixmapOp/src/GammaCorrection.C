/*
 * GammaCorrection.C 
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: GammaCorrection.C,v 1.5 1996/04/14 13:06:59 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <math.h>       // pow
#include <sstream>  // class std::stringstream

#include "booga/base/Report.h"
#include "booga/base/AbstractPixmap.h"
#include "booga/pixmapOp/GammaCorrection.h"

//______________________________________________________________ GammaCorrection

GammaCorrection::GammaCorrection()
{
  myInvGamma = 1/2.2;
}

void GammaCorrection::setGamma(Real gamma)
{
  if (gamma <= 0.0) {
    std::stringstream os;
    os << "[GammaCorrection::setGamma] : illegal gamma value " << gamma;
    Report::warning(os);
  } else
    myInvGamma = 1/gamma;
}

void GammaCorrection::apply(AbstractPixmap* pm)
{
  if (!pm)
    return;

  long size = pm->getSize();
  int c;
  float rgb[3];

  for (long p=0; p<size; p++) {
    pm->setPosition(p);
    pm->getColor(rgb[0], rgb[1], rgb[2]);
      
    for (c=0; c<3; c++)
      rgb[c] = pow(rgb[c], myInvGamma);
      
    pm->setColor(rgb[0], rgb[1], rgb[2]);
  } 
}
