/*
 * LabelConnectedComponents.C 
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
 *  $Id: LabelConnectedComponents.C,v 1.3 1996/04/14 13:07:00 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <stdio.h>
#include "booga/base/mathutilities.h"
#include "booga/base/Report.h"
#include "booga/base/AbstractPixmap.h"
#include "booga/pixmapOp/LabelConnectedComponents.h"

const int WORKSPACE=2000;

//_____________________________________________________________________ LabelConnectedComponents

LabelConnectedComponents::LabelConnectedComponents(EWriteOption writeOption, int verbose)
{
  myNumber = 0;
  myVerbose = verbose;
  myBackground = 0.0;
  myWriteOption = writeOption;
  mySourceChannel = -1;
  myTargetChannel = -1;
  myObjects = NULL;
}

LabelConnectedComponents::~LabelConnectedComponents() 
{
  delete [] myObjects;
}

static int sourceChannel;
static int targetChannel;

static float setPositionAndGetSourceColor(AbstractPixmap* pm, long position) 
{
  float value;

  pm->setPosition(position);
  pm->getColor(value);
  return(value);
}

static float setPositionAndGetSourceChannel(AbstractPixmap* pm, long position) 
{
  float value;

  pm->setPosition(position);
  pm->getUserChannel(sourceChannel, value);
  return(value);
}

static float setPositionAndGetTargetColor(AbstractPixmap* pm, long position) 
{
  float value;

  pm->setPosition(position);
  pm->getColor(value);
  return(value);
}

static float setPositionAndGetTargetChannel(AbstractPixmap* pm, long position) 
{
  float value;

  pm->setPosition(position);
  pm->getUserChannel(targetChannel, value);
  return(value);
}

static void setPositionAndSetTargetColor(AbstractPixmap* pm, long position, float value)
{
  pm->setPosition(position);
  pm->setColor(value);
}

static void setPositionAndSetTargetChannel(AbstractPixmap* pm, long position, float value)
{
  pm->setPosition(position);
  pm->setUserChannel(targetChannel, value);
}

void LabelConnectedComponents::apply(AbstractPixmap* pm)
{
  if (!pm)
    return;
  
  char	buf[256];
  int	i, j, m, n, x, y;
  int	iwork[WORKSPACE];
  int	height = pm->getResolutionY();
  int	width = pm->getResolutionX();
  long	p;   // position = offset of a pixel relative to origin of image
  float	value;
  float	(*getSourcePixel)(AbstractPixmap* pm, long position);
  float	(*getTargetPixel)(AbstractPixmap* pm, long position);
  void	(*setTargetPixel)(AbstractPixmap* pm, long position, float);

  if (myObjects != NULL) { // apply has already been called before
    delete [] myObjects;
    myNumber = 0;
  }

  if (mySourceChannel >= 0) {
    sourceChannel = getSourceChannel();
    getSourcePixel = setPositionAndGetSourceChannel;
  }
  else
    getSourcePixel = setPositionAndGetSourceColor;

  switch (myWriteOption) {
  case IMAGE:
    myTargetChannel = -1;
    break;
  case NEW_CHANNEL:
    if(pm->getUnusedUserChannel(myTargetChannel))
      myTargetChannel = -1;
    break;
  case EXISTING_CHANNEL:
    myTargetChannel = mySourceChannel;
    break;
  default:
    break;
  }
  if (myTargetChannel >= 0) {
    targetChannel = myTargetChannel;
    getTargetPixel = setPositionAndGetTargetChannel;
    setTargetPixel = setPositionAndSetTargetChannel;
  }
  else {
    getTargetPixel = setPositionAndGetTargetColor;
    setTargetPixel = setPositionAndSetTargetColor;
  }

  for (y=0, p=0; y<height; y++) {
    for (x=0; x<width; x++, p++) {
      
      if (getSourcePixel(pm, p) != myBackground) {
	
	// 1. check
	if (
	    (y > 0) // not first row
	    &&
	    ((value = getTargetPixel(pm, p-width))
	     != 0)
	    )
	  setTargetPixel(pm, p, value);
	
	// 2. check
	else if (
	         (y > 0) // not first row
		 &&
		 ((value = getTargetPixel(pm, p+1-width))
		  != 0)
		 ) {
	  // Combining two connected components
	  m = iwork[(int) value];
	  // Computing MAX
	  n = max((int) getTargetPixel(pm, p-1-width),
		  (int) getTargetPixel(pm, p-1));
	  if ((n > 0) && (m != iwork[n])) {
	    j = min(m,iwork[n]);
	    n = max(m,iwork[n]);
	    m = j;
	    for (i = 1; i <= myNumber; i++)
	      if (iwork[i] == n)
		iwork[i] = m;
	  }
	  setTargetPixel(pm, p, (float) m);
	}
	
	// 3. check
	else if (
	         (x > 0) // not first column
	         &&
	         ((value = getTargetPixel(pm, p-1))
		  != 0)
		 ) {
	  setTargetPixel(pm, p, value);
	}
	
	// 4.check
	else if (
	         (y > 0) && (x > 0) // not first row, not first column
	         &&
	         ((value = getTargetPixel(pm, p-1-width))
		  != 0)
		 )
	  setTargetPixel(pm, p, value);
	
	else {
	  // New connected component
	  if (myNumber >= WORKSPACE) {
	    sprintf(buf, "[LabelConnectedComponents::apply] Workarea too small! (just %d elements)", WORKSPACE);
	    Report::error(buf);
	    exit(1);
	  }
	  myNumber++;
	  setTargetPixel(pm, p, (float)myNumber);
	  iwork[myNumber] = myNumber;
	}      
      }
      else if (myBackground)
	setTargetPixel(pm, p, 0);

    } // for (x=...
  } // for (y=...
    
  if (myNumber==0)
    Report::warning("[LabelConnectedComponents::apply] : no object found");
  
  // compress
  n = 1;
  for (i = 1; i <= myNumber; i++) {
    m = iwork[i];
    if (m > n)
      for (j = i; j <= myNumber; j++) {
	if (iwork[j] == m)
	  iwork[j] = n;
      }
    if (m >= n)
      n++;
  }
  myNumber = n-1;
  if (myTargetChannel == -1) // we're working on the original image -> set range
    pm->setRange(0, myNumber);
  
  myObjects =  new BoundingRect[myNumber+1];    
  
  for (y=0, p=0; y<height; y++) {
    for (x=0; x<width; x++, p++) {
      value = getTargetPixel(pm, p);
      n = iwork[(int) value];
      if (n > 0) {
        setTargetPixel(pm, p, (float) n);
        myObjects[n].expand(x, y);
      }
    }	
  }
  
  if (myVerbose) {
    std::cout << myNumber << " objects found.\n";
    for (i=1; i<=myNumber; i++)
      std::cout << myObjects[i] << std::endl;
  }
}
