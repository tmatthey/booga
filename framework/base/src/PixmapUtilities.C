/*
 * PixmapUtilities.C 
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
 *  $Id: PixmapUtilities.C,v 1.3 1997/10/27 10:13:11 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/PrimitiveTypes.h"
#include "booga/base/AbstractPixmap.h"
#include "booga/base/PixmapUtilities.h"

//______________________________________________________________ PixmapUtilities

unsigned char* PixmapUtilities::createPPMPicture(bool& didCut, const AbstractPixmap* pixi)
{
  int resX = pixi->getResolutionX();
  int resY = pixi->getResolutionY();
  float rangeMin = pixi->getRangeMin();
  float rangeMax = pixi->getRangeMax();

  unsigned char* ppmPicture = new unsigned char[3*resX*resY];

  float color[3];
  long pos;
  float factor;
  int x,y,c;

  didCut = false;

  for (y=resY-1; y>=0; y--)
    for (x=0; x<resX; x++) {
      pixi->setPosition(x, y);
      pos = (resY-1-y)*resX+x;
      factor = 255.0/(rangeMax-rangeMin);
      pixi->getColor(color[0], color[1], color[2]);
      for (c=0; c<3; c++) {
        if (color[c] < rangeMin) {
          color[c] = rangeMin;
          didCut = true;
        } else if (color[c] > rangeMax) {
          color[c] = rangeMax;
          didCut = true;
        }          
        ppmPicture[3*pos+c]   = (unsigned char)(factor*(color[c]-rangeMin)+0.5);
      }
    }
    
  return ppmPicture;
}

