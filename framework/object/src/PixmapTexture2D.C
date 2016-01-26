/*
 * $RCSfile: PixmapTexture2D.C,v $
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
 *  $Id: PixmapTexture2D.C,v 1.7 1996/08/30 13:53:35 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Value.h"
#include "booga/base/AbstractPixmap.h"
#include "booga/pixmapOp/ImageReaders.h"
#include "booga/object/Texture2DContext.h"
#include "booga/object/PixmapTexture2D.h"

//______________________________________________________________ PixmapTexture2D

implementRTTI(PixmapTexture2D, Texture2D);

PixmapTexture2D::PixmapTexture2D(AbstractPixmap* adoptPixmap)
: myPixmap(adoptPixmap)
{
  if (adoptPixmap == NULL)
    Report::error("[PixmapTexture2D::PixmapTexture2D(pixmap)] NULL pointer passed");
}

PixmapTexture2D::PixmapTexture2D(Exemplar)
// : Texture2D(exemplar)
{
  myPixmap = NULL;
}

PixmapTexture2D::PixmapTexture2D(const PixmapTexture2D& pt)
{
  if (pt.myPixmap != NULL)
    myPixmap = pt.myPixmap->copy();
  else
    myPixmap = NULL;
}

PixmapTexture2D::~PixmapTexture2D()
{
  if (myPixmap != NULL)
    delete myPixmap;
}

AbstractPixmap* PixmapTexture2D::getPixmap() const
{
  return myPixmap;
}

AbstractPixmap* PixmapTexture2D::orphanPixmap()
{
  AbstractPixmap* tmp = myPixmap;
  myPixmap = NULL;
  
  return tmp;
}

void PixmapTexture2D::adoptPixmap(AbstractPixmap* pixmap)
{
  if (pixmap == NULL) {
    Report::recoverable("[Pixmap2D::adoptPixmap] NULL pointer passed");
    return;
  }

  if (pixmap == myPixmap)
    return;  // self assignment.

  delete myPixmap;  
  myPixmap = pixmap;
}

Texture2D* PixmapTexture2D::copy() const
{
  return new PixmapTexture2D(*this);
}

void PixmapTexture2D::doTexturing(Texture2DContext& context) const
{
  if (myPixmap == NULL)
    return;
    
  Real x = fmod(fabs(context.getPositionTCS().x()), myPixmap->getResolutionX());
  Real y = fmod(fabs(context.getPositionTCS().y()), myPixmap->getResolutionY());

  float r, g, b;
  myPixmap->setPosition((int)x, (int)y);
  myPixmap->getColor(r, g, b);

  context.setColor(Color(r, g, b));
}

Makeable* PixmapTexture2D::make(RCString& errMsg, 
                                const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, RCString, fileName);
 
  return new PixmapTexture2D(ImageReader::createPixmap(fileName));
}                                

