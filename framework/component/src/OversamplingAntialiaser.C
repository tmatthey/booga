/*
 * $RCSfile: OversamplingAntialiaser.C,v $
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
 *  $Id: OversamplingAntialiaser.C,v 1.9 1996/08/01 12:00:18 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <sstream>
#include "booga/object/Camera3D.h"
#include "booga/object/Viewing3D.h"
#include "booga/component/Renderer.h"
#include "booga/component/OversamplingAntialiaser.h"

//______________________________________________________ OversamplingAntialiaser

implementRTTI(OversamplingAntialiaser, Antialiaser);

OversamplingAntialiaser::OversamplingAntialiaser()
{
  mySamplingRate = 2;
}

void OversamplingAntialiaser::setSamplingRate(int samplingRate)
{
  if (samplingRate <= 0) {
    std::stringstream os;
    os << "[OversamplingAntialiaser::setSamplingRate] illegal sampling rate: " << samplingRate;
    Report::warning(os);
    return;
  }

  mySamplingRate = samplingRate;
}

bool OversamplingAntialiaser::doExecute()
{
  int resX = myRenderer->getCamera()->getViewing()->getResolutionX();
  int resY = myRenderer->getCamera()->getViewing()->getResolutionY();
  
  myRenderer->getCamera()->getViewing()->setResolution(resX*mySamplingRate, 
                                                       resY*mySamplingRate);
  AbstractPixmap* resultPixi = Antialiaser::performRendering();

  if (resultPixi == NULL)
    return false;
      
  float r, g, b;
  float tmpR, tmpG, tmpB;
  int x, y;
  int sampleX, sampleY;
  float sampleNr = mySamplingRate*mySamplingRate;
  
  for (y = 0; y<resY; y++) {
    for (x = 0; x<resX; x++) {
      r = g = b = 0.0;
      for (sampleY = y*mySamplingRate; sampleY < (y+1)*mySamplingRate; sampleY++) {
        for (sampleX = x*mySamplingRate; sampleX < (x+1)*mySamplingRate; sampleX++) {
            resultPixi->setPosition(sampleX, sampleY);
            resultPixi->getColor(tmpR, tmpG, tmpB);
            r += tmpR; g += tmpG; b += tmpB;
        }
      }
      myResultPixmap->setPosition(x, y);
      myResultPixmap->setColor(r/sampleNr, g/sampleNr, b/sampleNr);
    }
  }
  delete resultPixi;
  
  return true;
}
