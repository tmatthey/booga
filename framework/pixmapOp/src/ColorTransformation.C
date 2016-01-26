/*
 * ColorTransformation.C 
 *
 * Copyright (C) 1995, Stephan Amann <amann@iam.unibe.ch>
 *                     Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: ColorTransformation.C,v 1.3 1995/08/15 14:51:54 amann Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/pixmapOp/ColorTransformation.h"

//__________________________________________________________ ColorTransformation

ColorTransformation::ColorTransformation()
{}

AbstractPixmap* ColorTransformation::generate(const AbstractPixmap* pm)
{
  AbstractPixmap* newPm = createPixmap(pm->getResolutionX(), pm->getResolutionY());
  
  long size = pm->getSize();
  float c1, c2, c3;
  for (long p=0; p<size; p++) {
    pm->setPosition(p);
    pm->getColor(c1, c2, c3);
    
    newPm->setPosition(p);
    newPm->setColor(c1, c2, c3);
  }
  
  return newPm;
}
