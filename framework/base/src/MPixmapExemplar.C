/*
 * $RCSfile: MPixmapExemplar.C,v $ 
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
 *  $Id: MPixmapExemplar.C,v 1.4 1996/08/30 13:53:20 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Configuration.h"
#include "booga/base/ValueOption.h" 
#include "booga/base/PixmapOption.h" 
#include "booga/base/PixmapOf.h"
#include "booga/base/MPixmapExemplar.h"

//_____________________________________________________________  MPixmapExemplar

MPixmapExemplar::MPixmapExemplar()
{
  //
  // Get default pixmap type from configuration database.
  //
  getConfigurationOption(PixmapOption, pixiOption, "Pixmap.Type");
  if (pixiOption != NULL)
    myPixmapExemplar = pixiOption->getPixmap()->copy();
  else
    myPixmapExemplar = new PixmapOf<RGB>(1,1);
  
  //
  // Get default resolution for pixmap from configuration database.
  //
  getConfigurationOption(ValueOption, resX, "Pixmap.ResX");
  if (resX != NULL)
    myResX = int((Real)resX->getValue());
  else
    myResX = 512;
 
  getConfigurationOption(ValueOption, resY, "Pixmap.ResY");
  if (resY != NULL)
    myResY = int((Real)resY->getValue());
  else
    myResY = 512;
}

MPixmapExemplar::~MPixmapExemplar()
{
  delete myPixmapExemplar;
}

void MPixmapExemplar::adoptPixmapExemplar(AbstractPixmap* pm)
{
  //
  // Self assignment?
  //
  if (myPixmapExemplar == pm)
    return;
    
  if (pm != NULL) {
    delete myPixmapExemplar;
    myPixmapExemplar = pm;
  }
} 

AbstractPixmap* MPixmapExemplar::createPixmap() const
{
  return createPixmap(myResX, myResY);
}

AbstractPixmap* MPixmapExemplar::createPixmap(int resX, int resY) const
{
  AbstractPixmap* retval = myPixmapExemplar->copy();
  retval->setResolution(resX, resY);

  return retval;
}
