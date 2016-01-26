/*
 * Thin.C 
 *
 * Copyright (C) 1995, Daniel Moeri <moeri@iam.unibe.ch>
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
 *  $Id: Thin.C,v 1.2 1996/04/14 13:07:03 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <stdio.h>
#include "booga/base/Report.h"
#include "booga/base/AbstractPixmap.h"
#include "booga/pixmapOp/Thin.h"

//_____________________________________________________________________ Thin

Thin::Thin(int verbose)
{
  myBackground = 0;
  myVerbose = verbose;
  myNumber = 0;
  myWriteOption = IMAGE;
  mySourceChannel = -1;
  myObjects = NULL;
}

Thin::~Thin() 
{
}

static int sourceChannel;
static int targetChannel;
static float conc(float *);

static float setPositionAndGetColor(AbstractPixmap* pm, long position) 
{
  float value;

  pm->setPosition(position);
  pm->getColor(value);
  return(value);
}

static float setPositionAndGetChannel(AbstractPixmap* pm, long position) 
{
  float value;

  pm->setPosition(position);
  pm->getUserChannel(sourceChannel, value);
  return(value);
}

static void setPositionAndSetColor(AbstractPixmap* pm, long position, float value)
{
  pm->setPosition(position);
  pm->setColor(value);
}

static void setPositionAndSetChannel(AbstractPixmap* pm, long position, float value)
{
  pm->setPosition(position);
  pm->setUserChannel(targetChannel, value);
}

// The used algorithm (Hilditch's thinning algorithm) derives from 
// thng1.f -- originally translated by f2c (version of 5 May 1992  15:16:14).
// (file within the Spider distribution).
// The original algorithm has been modified to handle with labeled images
// too (-> better performance because iteration within known bounding box).
void Thin::apply(AbstractPixmap* pm)
{
  if (!pm)
    return;
    
  int m, mMax, // iteration
      x, y;    // coordinates of image
  int i, ir, iv, iw;
  int width = pm->getResolutionX();
  int height = pm->getResolutionY();
  long p;   // position = offset of a pixel relative to origin of image
  float ia[9], ic[9], iu;
  float (*getPixelInfo)(AbstractPixmap* pm, long position);
  void (*setPixelInfo)(AbstractPixmap* pm, long position, float);

  if (myObjects == NULL) {
    // image is not preprocessed
    setNumber(1);
    BoundingRect *objects = new BoundingRect[2];
    objects[1].expand(0, 0);
    objects[1].expand(pm->getResolutionX()-1,
		      pm->getResolutionY()-1);
    setObjects(objects);
  }
    
  if (mySourceChannel >= 0) {
    sourceChannel = getSourceChannel();
    getPixelInfo = setPositionAndGetChannel;
    targetChannel = sourceChannel;
    setPixelInfo = setPositionAndSetChannel;
  }
  else {
    getPixelInfo = setPositionAndGetColor;
    setPixelInfo = setPositionAndSetColor;
  }

  mMax = 0;
  for (int label=1; label<=myNumber; label++) {
    int minY = (int)myObjects[label].getMinY();
    int maxY = (int)myObjects[label].getMaxY();
    int minX = (int)myObjects[label].getMinX();
    int maxX = (int)myObjects[label].getMaxX();

    m = 1;
    do {
      ir = 0;
      
      for (y  = minY; y <= maxY; y++) {
	p = (long)(y*width + minX);
	for (x  = minX; x <= maxX; x++, p++) {
	  if (getPixelInfo(pm, p) == label) {

	    //  5  6  7
	    //  4  x  0
	    //  3  2  1
	    if (x<(width-1))
	      ia[0] = getPixelInfo(pm, p+1);
	    else
	      ia[0] = 0;
	    if ((x<(width-1)) && (y>0))
	      ia[1] = getPixelInfo(pm, p+1-width);
	    else
	      ia[1] = 0;
	    if (y>0)
	      ia[2] = getPixelInfo(pm, p  -width);
	    else
	      ia[2] = 0;
	    if ((x>0) && (y>0))
	      ia[3] = getPixelInfo(pm, p-1-width);
	    else
	      ia[3] = 0;
	    if (x>0)
	      ia[4] = getPixelInfo(pm, p-1);
	    else
	      ia[4] = 0;
	    if ((x>0) && (y<(height-1)))
	      ia[5] = getPixelInfo(pm, p-1+width);
	    else
	      ia[5] = 0;
	    if (y<(height-1))
	      ia[6] = getPixelInfo(pm, p  +width);
	    else
	      ia[6] = 0;
	    if ((x<(width-1)) && (y<(height-1)))
	      ia[7] = getPixelInfo(pm, p+1+width);
	    else
	      ia[7] = 0;
	    
	    // CONDITION 2
	    for (i = 0; i <= 7; ++i) {
	      if (ia[i] != -m) {
		if (ia[i] < 0)
		  ia[i] = 0;
		else if (ia[i] == label)
		  ia[i] = 1;
		else		/* two different symbols 8-connected */
		  ia[i] = 0;
		ic[i] = ia[i];
	      }
	      else {
		ia[i] = 1;
		ic[i] = 0;
	      }
	    }
	    ia[8] = ia[0];
	    ic[8] = ic[0];
	    iu = 4 - (ia[0] + ia[2] + ia[4] + ia[6]);
	    
	    if (iu != 0) {
	      
	      // CONDITION 3 & 4
	      iv = 0;
	      iw = 0;
	      for (i = 0; i <= 7; ++i) {
		if (ia[i] == 1)
		  iv++;
		if (ic[i] == 1)
		  iw++;
	      }
	      if (iv <= 1)
		goto L300;
	      if (iw == 0)
		goto L300;
	      
	      // CONDITION 5
	      if (conc(ia) != 1)
		goto L300;
	      
	      // CONDITION 6
	      if ((y==0) || (getPixelInfo(pm, p-width) != -m))
		goto L180;
	      ia[2] = 0;
	      if (conc(ia) != 1)
		goto L300;
	      ia[2] = 1;
	      
L180:
	      if ((x==0) || (getPixelInfo(pm, p-1) != -m))
		goto L200;
	      
	      ia[4] = 0;
	      if (conc(ia) != 1)
		goto L300;
	      
L200:
	      setPixelInfo(pm, p, (float)(-m));
	      ir++;
	      
	    } // if (iu != 0)
	    
	  }
L300:
	  ;
	} // for (x=...
      } // for (y=...
      
      m++;
    } while(ir > 0);
    if (m > mMax)
      mMax = m;
  }
  pm->setRange(-(mMax-2), myNumber); // 1 iteration w/o doing anything, inc at the end
}


// conc.f -- translated by f2c (version of 5 May 1992  15:16:14).
static float conc(float *inb)
{
  // Local variables
  float icn;
  int i;
  
  // Function Body
  icn = 0;
  
  for (i = 0; i < 7; i += 2)
    icn += (1 - inb[i]) * max(inb[i + 1], inb[i + 2]);

  return icn;
} // conc
