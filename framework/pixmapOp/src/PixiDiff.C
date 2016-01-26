/*
 * $RCSfile: PixiDiff.C,v $ 
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
 *  $Id: PixiDiff.C,v 1.2 1996/08/30 13:53:29 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <strstream.h>
#include <math.h>

#include "booga/base/Report.h"
#include "booga/pixmapOp/PixiDiff.h"

//_____________________________________________________________________ PixiDiff

PixiDiff::PixiDiff()
{
  myReference = NULL;
}
                      
PixiDiff::~PixiDiff()
{
  delete myReference;
}

void PixiDiff::adoptReference(AbstractPixmap* pixi)
{
  //
  // Self assignment?
  //
  if (myReference == pixi)
    return;

  delete pixi;
  myReference = pixi;
}

AbstractPixmap* PixiDiff::generate(const AbstractPixmap* pm)
{
  if (pm->getResolutionX() != myReference->getResolutionX() ||
      pm->getResolutionY() != myReference->getResolutionY()) {
    ostrstream os;
    os << "[PixiDiff::generate] resolution of pixmaps differ: cannot compare [";
    os << pm->getResolutionX() << ", " << pm->getResolutionY() << "] with [";
    os << myReference->getResolutionX() << ", " << myReference->getResolutionY() << "]";
    
    Report::warning(os);
    
    return NULL;
  }
  
  AbstractPixmap* newPm = createPixmap(pm->getResolutionX(), pm->getResolutionY());
  
  long size = pm->getSize();
  float ar, ag, ab, br, bg, bb; // Image a and b, Channel RGB
  float ad, bd;                 // Depth
  
  for (long p=0; p<size; p++) {
    pm->setPosition(p);
    pm->getColor(ar, ag, ab);
    pm->getDepth(ad);
    
    myReference->setPosition(p);
    myReference->getColor(br, bg, bb);
    myReference->getDepth(bd);
    
    newPm->setPosition(p);
    newPm->setColor(fabs(ar-br), fabs(ag-bg), fabs(ab-bb));
    newPm->setDepth(fabs(ad-bd));
  }
  
  return newPm;
}
