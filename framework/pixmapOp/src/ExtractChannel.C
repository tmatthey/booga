/*
 * ExtractChannel.C 
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
 *  $Id: ExtractChannel.C,v 1.5 1995/09/01 08:47:49 amann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/mathutilities.h"
#include "booga/base/AbstractPixmap.h"
#include "booga/base/Report.h"
#include "booga/pixmapOp/ExtractChannel.h"

//_______________________________________________________________ ExtractChannel

ExtractChannel::ExtractChannel()
{
  myType = USER;
  myChannel = 0;
}

AbstractPixmap* ExtractChannel::generate(const AbstractPixmap* pm)
{
  AbstractPixmap* newPm;
  float minV = MAXFLOAT, maxV = -MAXFLOAT;
  
  if (!haveChannel(pm))
    return NULL;
  
  newPm = createPixmap(pm->getResolutionX(), pm->getResolutionY());
  float value;
  for (long p=0; p<newPm->getSize(); p++) {
    pm->setPosition(p);
    getChannel(pm, value);
    
    minV = min(minV, value);
    maxV = max(maxV, value);
        
    newPm->setPosition(p);
    newPm->setColor(value);
  }

  newPm->setRange(minV, maxV);
      
  return newPm;
}

void ExtractChannel::selectUserChannel(int channel)
{
  if (channel<0 || channel>=AbstractPixmap::MAX_USERCHANNELS) {
    Report::recoverable("[ExtractChannel::setChannel] illegal channel selected");
    return;
  }
  
  myType = USER;
  myChannel = channel;
}

void ExtractChannel::selectAlpha()
{
  myType = ALPHA;
}

void ExtractChannel::selectDepth()
{
  myType = DEPTH;
}

bool ExtractChannel::haveChannel(const AbstractPixmap* pm) const
{
  switch (myType) {
    case USER:  return pm->haveUserChannel(myChannel);
    case ALPHA: return pm->haveAlpha();
    case DEPTH: return pm->haveDepth();
    default:    Report::error("[ExtractChannel::haveChannel] Illegal channel type");
  }

  return false;
}

void ExtractChannel::getChannel(const AbstractPixmap* pm, float& value) const
{
  switch (myType) {
    case USER:  pm->getUserChannel(myChannel, value);
                return;
    case ALPHA: pm->getAlpha(value);
                return;
    case DEPTH: pm->getDepth(value);
                return;
    default:    Report::error("[ExtractChannel::getChannel] Illegal channel type");
  }
}

