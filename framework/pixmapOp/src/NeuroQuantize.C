/*
 * NeuroQuantize.C 
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: NeuroQuantize.C,v 1.2 1996/04/18 07:37:17 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <sstream>  // class std::stringstream

#include "neuroQuant.h"

#include "booga/base/Report.h"
#include "booga/base/Color.h"
#include "booga/base/AbstractPixmap.h"
#include "booga/base/PixmapUtilities.h"
#include "booga/pixmapOp/NeuroQuantize.h"

//________________________________________________________________ NeuroQuantize

NeuroQuantize::NeuroQuantize()
{
  myMaxColors = 256;
  mySamplingFactor = 3;
}

void NeuroQuantize::setMaxColors(int colors)
{
  if (colors != 256) {
    std::stringstream os;
    os << "[NeuroQuantize::setMaxColors] only 256 colors supported yet, "
       << colors << " requested";
    Report::warning(os);
  }
}

void NeuroQuantize::setSamplingFactor(int factor)
{
  if (factor < 1 || factor > 30) {
    std::stringstream os;
    os << "[NeuroQuantize::setSamplingFactor] sampling factor has to be in range [1..30], "
       << factor << " requested";
    Report::warning(os);
  }
  else
    mySamplingFactor = factor;
}

void NeuroQuantize::apply(AbstractPixmap* pm)
{
  if (pm == NULL) {
    Report::warning("[NeuroQuantize::apply] NULL pointe passed");
    return;
  }
  
  int resX = pm->getResolutionX();
  int resY = pm->getResolutionY();
  int size = resX*resY;
  float rangeMin = pm->getRangeMin();
  float rangeMax = pm->getRangeMax();
  float factor = 255.0/(rangeMax-rangeMin);
  
  float color[3];
  int c;
  long pos;
  long bgrPos;
  unsigned char* bgrData = new unsigned char[3*resX*resY];
 
  for (pos=0, bgrPos=0; pos < size; pos++) {
    pm->setPosition(pos);
      // RGB -> BGR
    pm->getColor(color[2], color[1], color[0]);
    for (c=0; c<3; c++) {
      if (color[c] < rangeMin)
        color[c] = rangeMin;
      else if (color[c] > rangeMax)
        color[c] = rangeMax;

      bgrData[bgrPos++] = (unsigned char)(factor*(color[c]-rangeMin)+0.5);
    }
  }
  
  neuroInitnet(bgrData, 3*size, mySamplingFactor);
  neuroLearn();
  neuroUnbiasnet();

  Color* colorMap = new Color[myMaxColors];
  for (int n=0; n<myMaxColors; n++) {
    colorMap[n] = Color(neuroColorMapEntry(n, 2) / 255.0, 
                        neuroColorMapEntry(n, 1) / 255.0, 
                        neuroColorMapEntry(n, 0) / 255.0);
  }

  neuroInxbuild();

  int index;
  for (pos=0, bgrPos=0; pos<size; pos++,bgrPos+=3) {
    index = neuroInxsearch(bgrData[bgrPos], bgrData[bgrPos+1], bgrData[bgrPos+2]);
    
    pm->setPosition(pos);
    pm->setColor(colorMap[index].getRed(), 
                 colorMap[index].getGreen(), 
                 colorMap[index].getBlue());
  }
  
  delete [] bgrData;
  delete [] colorMap;
}
