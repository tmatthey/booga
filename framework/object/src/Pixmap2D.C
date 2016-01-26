/*
 * $RCSfile: Pixmap2D.C,v $
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
 *  $Id: Pixmap2D.C,v 1.27 1996/09/13 08:05:40 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Value.h"
#include "booga/base/Report.h"
#include "booga/base/PixmapOf.h"
#include "booga/pixmapOp/ImageReaders.h"

#include "booga/object/PixmapTexture2D.h"

#include "booga/object/Line2D.h"
#include "booga/object/Text2D.h"
#include "booga/object/List2D.h"
#include "booga/object/Pixmap2D.h"

//_____________________________________________________________________ Pixmap2D

implementRTTI(Pixmap2D, Primitive2D);

Pixmap2D::Pixmap2D(Exemplar exemplar)
: Primitive2D(exemplar)
{
  myPixmapTexture = NULL;
}

Pixmap2D::Pixmap2D(AbstractPixmap* adoptPixmap)
: myPixmapTexture(NULL)
{
  if (adoptPixmap == NULL) {
    Report::recoverable("[Pixmap2D(AbstractPixmap*)] passed NULL pointer");
    return;
  }

  //
  // A PixmapTexture2D object is created that handles the dispay of the pixmap!
  // The pixmap texture is appended to the texture list of this object.
  //
  myPixmapTexture = new PixmapTexture2D(adoptPixmap);
  appendTexture((Texture2D*)myPixmapTexture);
}
  
Pixmap2D::Pixmap2D(const Pixmap2D& pm)
: Primitive2D(pm)
{
  if (pm.myPixmapTexture != NULL) {
    //
    // A PixmapTexture2D object is created that handles the dispay of the pixmap!
    // The pixmap texture is appended to the texture list of this object.
    //
    myPixmapTexture = (PixmapTexture2D*)pm.myPixmapTexture->copy();
    appendTexture((Texture2D*)myPixmapTexture);
  }
  else
    myPixmapTexture = NULL;
}

AbstractPixmap* Pixmap2D::getPixmap() const
{
  if (myPixmapTexture == NULL)
    return NULL;
    
  return myPixmapTexture->getPixmap();
}

AbstractPixmap* Pixmap2D::orphanPixmap()
{
  if (myPixmapTexture == NULL)
    return NULL;
    
  return ((PixmapTexture2D*)myPixmapTexture)->orphanPixmap();
}

void Pixmap2D::adoptPixmap(AbstractPixmap* pixmap)
{
  if (pixmap == NULL) {
    Report::recoverable("[Pixmap2D::adoptPixmap] passed NULL pointer");
    return;
  }
  
  if (myPixmapTexture == NULL) {
    //
    // A PixmapTexture2D object is created that handles the dispay of the pixmap!
    // The pixmap texture is appended to the texture list of this object.
    //
    myPixmapTexture = new PixmapTexture2D(pixmap);
    appendTexture((Texture2D*)myPixmapTexture);
  }
  else
    ((PixmapTexture2D*)myPixmapTexture)->adoptPixmap(pixmap);
}

/*
 * The decomposition of the pixmap produces a rectangle (4 lines) 
 * and the text "Pixi" with appropriate dimensions.
 */
Object2D* Pixmap2D::createDecomposition() const
{
  if (myPixmapTexture == NULL)
    return NULL;
    
  List2D* decomposition = new List2D;
  const AbstractPixmap* pixi = myPixmapTexture->getPixmap();
  
  Vector2D pos[4];
  pos[0] = Vector2D(0,0);
  pos[1] = Vector2D(pixi->getResolutionX(), 0);
  pos[2] = Vector2D(pixi->getResolutionX(), pixi->getResolutionY());
  pos[3] = Vector2D(0, pixi->getResolutionY());
  
  decomposition->adoptObject(new Line2D(pos[0], pos[1]));
  decomposition->adoptObject(new Line2D(pos[1], pos[2]));
  decomposition->adoptObject(new Line2D(pos[2], pos[3]));
  decomposition->adoptObject(new Line2D(pos[3], pos[0]));

  Real height = pixi->getResolutionX() / 6;
  Text2D* text = new Text2D("Pixi");
  text->setFont("MONO_ROMAN");
  text->setHeight(height);
  text->addTransform(TransMatrix2D::makeTranslate(height, pixi->getResolutionY()/2));
  decomposition->adoptObject(text);
  decomposition->computeBounds();
  
  return decomposition;
}

Object2D* Pixmap2D::copy() const
{
  return new Pixmap2D(*this);
}

void Pixmap2D::doComputeBounds()
{
  if (myPixmapTexture == NULL) 
    return;

  const AbstractPixmap* pixi = myPixmapTexture->getPixmap();
    
  myBounds.expand(0, 0);
  myBounds.expand(pixi->getResolutionX(), pixi->getResolutionY());
}

bool Pixmap2D::doIntersect(Ray2D& ray)
{
  //
  // We hit the bounding rectangle and the pixmap is filled -> HIT!
  // Any hit has distance 0.
  // 
  ray.setBestHitObject(this);
  ray.setBestHitDistance(0);   

  return true;
}

Makeable* Pixmap2D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, RCString, fileName);
 
  return new Pixmap2D(ImageReader::createPixmap(fileName));
}
