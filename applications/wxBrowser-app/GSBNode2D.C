/*
 * GSBNode2D.C 
 *
 * Copyright (C) 1996, Pascal Habegger <habegger@iam.unibe.ch>
 *                     Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: GSBNode2D.C,v 1.12 1997/04/22 13:39:12 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#include "GSBNode2D.h"
#include "booga/base/Value.h"
#include "booga/object/Line2D.h"
#include "booga/object/Shared2D.h"
#include "booga/object/Shared3D.h"
#include "booga/object/List2D.h"
#include "booga/object/Text2D.h"
#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"

//_____________________________________________________________________ GSBNode2D

implementRTTI(GSBNode2D, Primitive2D);

// initialize static members of GSBConetreeNode3D:
Texture2D* GSBNode2D::myNodeTexture = NULL;
Texture2D* GSBNode2D::myTextTexture = NULL;
Texture2D* GSBNode2D::mySharedTexture = NULL;


GSBNode2D::GSBNode2D(Exemplar exemplar)
: Primitive2D(exemplar), myText(""), myObject(NULL)
{
  myWidth  = 10;
  myHeight = 10;  
  myDecomposition = NULL;
}


GSBNode2D::GSBNode2D(const RCString& label, Real width, Real height)
: myText(label),           // node text
  myWidth(width),          // node x-length (depending on text length)
  myHeight(height),        // node y-length (depending on text height)
  myObject(NULL),          // object which is represented by *this
  myDecomposition(NULL)    // decomposition of *this
{}


GSBNode2D::GSBNode2D(const GSBNode2D& node)
: myText(node.myText),
  myWidth(node.myWidth),
  myHeight(node.myHeight),
  myObject(node.myObject),
  myDecomposition(node.myDecomposition)
{}


GSBNode2D::~GSBNode2D()
{
  delete myDecomposition;
}


Object2D* GSBNode2D::createDecomposition() const
{
  // test if there's already a decompositon of the node object
  // ==> make a copy.
  if (myDecomposition != NULL)
    return myDecomposition->copy();
    
  List2D* segments = new List2D;

//  if (dynamic_cast(Shared3D, myObject)) {
//    List2D* box = new List2D;
//    box->adoptObject(new Line2D(Vector2D(myWidth * .9, myHeight),
//                                Vector2D(myWidth * .9, myHeight * .9)));
//    box->adoptObject(new Line2D(Vector2D(myWidth * .9, myHeight * .9),
//                                Vector2D(myWidth,      myHeight * .9)));
//    segments->adoptObject(box);
//  }
  
  // add box to decomposition list:
  List2D* box = new List2D;
  box->adoptObject(new Line2D(Vector2D(0,       0       ), 
                              Vector2D(myWidth, 0       )) );
  box->adoptObject(new Line2D(Vector2D(myWidth, 0       ), 
                              Vector2D(myWidth, myHeight)) );
  box->adoptObject(new Line2D(Vector2D(myWidth, myHeight), 
                              Vector2D(0,       myHeight)) );
  box->adoptObject(new Line2D(Vector2D(0,       myHeight),
                              Vector2D(0,       0       )) );
  
  if (myNodeTexture)
    box->appendTexture(myNodeTexture->copy());
  segments->adoptObject(box);
  
  // add text to decomposition list:
  Text2D* text = new Text2D(myText);
  text->setHeight(myHeight * .8);
  text->computeBounds();
  Real width = (text->getBounds().getMax() - 
                text->getBounds().getMin()).x();
  text->addTransform(TransMatrix2D::makeScale(myWidth/width * .8, 1));
  text->addTransform(TransMatrix2D::makeTranslate(
        myWidth * .1, myHeight * .1));

  if (myTextTexture)
    text->appendTexture(myTextTexture->copy());
    
  if (dynamic_cast(Shared3D, myObject) && mySharedTexture) 
    text->appendTexture(mySharedTexture->copy());
    
  segments->adoptObject(text);
  
  ((GSBNode2D*) this)->myDecomposition = new Shared2D(segments);
  ((GSBNode2D*) this)->myDecomposition->computeBounds();
  
  return myDecomposition->copy();
}


Object2D* GSBNode2D::copy() const
{
  return new GSBNode2D(*this);
}


void GSBNode2D::doComputeBounds()
{
  delete myDecomposition;
  myBounds.expand(0, 0);
  myBounds.expand(myWidth, myHeight);
}


bool GSBNode2D::doIntersect(Ray2D& ray)
{
  if (myDecomposition == NULL)
    delete createDecomposition();

//  return myDecomposition->intersect(ray);

  // Since we hit bounding box, we also hit the node!
  ray.setBestHitObject(this);
  // Best hit distance is always zero
  ray.setBestHitDistance(0);
  return true;
}


Makeable* GSBNode2D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(3);
  getParameter(1, RCString, label);
  getParameter(2, Real, width);
  getParameter(3, Real, height);

  if (label.isEmpty()) {
    errMsg = "degenerated label";
    return NULL;
  }

  GSBNode2D* newNode = new GSBNode2D(*this);
  newNode->setLabel(label);
  newNode->setWidth(width);
  newNode->setHeight(height);
  
  return newNode;
}


void GSBNode2D::adoptNodeTexture(Texture2D* texture)
{
  if (texture == myNodeTexture)
    return;
  delete myNodeTexture;
  myNodeTexture = texture;
}


void GSBNode2D::adoptTextTexture(Texture2D* texture)
{
  if (texture == myTextTexture)
    return;
  delete myTextTexture;
  myTextTexture = texture;
}


void GSBNode2D::adoptSharedTexture(Texture2D* texture)
{
  if (texture == mySharedTexture)
    return;
  delete mySharedTexture;
  mySharedTexture = texture;
}

static const RCString GSBNode2DKeyword("list");

RCString GSBNode2D::getKeyword() const {
  return GSBNode2DKeyword;
}

void GSBNode2D::iterateAttributes(MakeableHandler *handler) {
  Primitive2D::iterateAttributes(handler);
  if (myDecomposition == NULL)
    delete createDecomposition();
  
  handler->handle(myDecomposition->getSubobject(0));
}

