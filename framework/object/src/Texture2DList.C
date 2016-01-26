/*
 * Texture2DList.C
 *
 * Copyright (C) 1995, Christoph Streit <streit@iam.unibe.ch>
 *                     Stephan Amann <amann@iam.unibe.ch>
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: Texture2DList.C,v 1.7 1996/10/04 09:48:33 collison Exp $
 * -----------------------------------------------------------------------------
 */
   
#include "booga/object/Texture2DList.h"
#include "booga/object/MakeableHandler.h"
//________________________________________________________________ Texture2DList

implementRTTI(Texture2DList, Texture2D);

Texture2DList::Texture2DList() {}
Texture2DList::Texture2DList(Exemplar) {}

Texture2DList::Texture2DList(const Texture2DList& textureList)
{
  for (long i=0; i<textureList.myTextures.count(); i++)
    appendTexture(textureList.myTextures.item(i)->copy());
}

Texture2DList::~Texture2DList()
{
  for (long i=0; i<myTextures.count(); i++)
    delete myTextures.item(i);
}
  
int Texture2DList::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  Texture2D* texture = dynamic_cast(Texture2D, specifier);
  if (texture != NULL) {
    appendTexture(texture);
    return 1;
  }

  // 
  // Let papa do the rest ...
  //
  return Texture2D::setSpecifier(errMsg, specifier); 
}

Texture2D* Texture2DList::copy() const
{
  return new Texture2DList(*this);
}

void Texture2DList::doTexturing(Texture2DContext& context) const
{
  for (long i=0; i<myTextures.count(); i++)
    myTextures.item(i)->texturing(context);
}

void Texture2DList::computeCumulatedTransform(const Transform2D& additionalTransform)
{
  Texture2D::computeCumulatedTransform(additionalTransform);

  for (long i=0; i<myTextures.count(); i++)
    myTextures.item(i)->computeCumulatedTransform(additionalTransform);
}

void Texture2DList::appendTexture(Texture2D* adoptTexture)
{
  if (adoptTexture == NULL) {
    Report::warning("{Texture2DList::adoptTexture} NULL pointer passed");
    return;
  }
  
  adoptTexture->computeCumulatedTransform(getCumulatedTransform());
  myTextures.append(adoptTexture);
}

const Texture2D* Texture2DList::getTexture() const
{
  return curItem();
}

List<Texture2D*>* Texture2DList::getContainer()
{
  return &myTextures;
}

void Texture2DList::iterateAttributes(MakeableHandler *handler) {
  Texture2D::iterateAttributes(handler);
  for (int i=0; i<myTextures.count(); i++) {
    handler->handle(myTextures.item(i));
  }
}
