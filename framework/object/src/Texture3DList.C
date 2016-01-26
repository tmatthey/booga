/*
 * Texture3DList.C
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
 *  $Id: Texture3DList.C,v 1.10 1996/10/04 09:48:37 collison Exp $
 * -----------------------------------------------------------------------------
 */
   
#include "booga/object/Texture3DList.h"
#include "booga/object/MakeableHandler.h"

//________________________________________________________________ Texture3DList

implementRTTI(Texture3DList, Texture3D);

Texture3DList::Texture3DList() {}
Texture3DList::Texture3DList(Exemplar) {}

Texture3DList::Texture3DList(const Texture3DList& textureList)
{
  for (long i=0; i<textureList.myTextures.count(); i++)
    appendTexture(textureList.myTextures.item(i)->copy());
}

Texture3DList::~Texture3DList()
{
  for (long i=0; i<myTextures.count(); i++)
    delete myTextures.item(i);
}
  
int Texture3DList::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  Texture3D* texture = dynamic_cast(Texture3D, specifier);
  if (texture != NULL) {
    appendTexture(texture);
    return 1;
  }

  // 
  // Let papa do the rest ...
  //
  return Texture3D::setSpecifier(errMsg, specifier); 
}

Texture3D* Texture3DList::copy() const
{
  return new Texture3DList(*this);
}

void Texture3DList::doTexturing(Texture3DContext& context) const
{
  for (long i=0; i<myTextures.count(); i++)
    myTextures.item(i)->texturing(context);
}

void Texture3DList::computeCumulatedTransform(const Transform3D& additionalTransform)
{
  Texture3D::computeCumulatedTransform(additionalTransform);

  for (long i=0; i<myTextures.count(); i++)
    myTextures.item(i)->computeCumulatedTransform(additionalTransform);
}

void Texture3DList::appendTexture(Texture3D* adoptTexture)
{
  if (adoptTexture == NULL) {
    Report::warning("{Texture3DList::adoptTexture} NULL pointer passed");
    return;
  }
  
  adoptTexture->computeCumulatedTransform(getCumulatedTransform());
  myTextures.append(adoptTexture);
}

const Texture3D* Texture3DList::getTexture() const
{
  return curItem();
}

List<Texture3D*>* Texture3DList::getContainer()
{
  return &myTextures;
}

void Texture3DList::iterateAttributes(MakeableHandler *handler) {
  Texture3D::iterateAttributes(handler);
  for (int i=0; i<myTextures.count(); i++) {
    handler->handle(myTextures.item(i));
  }
}

