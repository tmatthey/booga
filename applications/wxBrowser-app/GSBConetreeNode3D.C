/*
 * GSBConetreeNode3D.C 
 *
 * Copyright (C) 1996, Pascal Habegger <habegger@iam.unibe.ch>
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
 *  $Id: GSBConetreeNode3D.C,v 1.9 1997/04/08 11:04:38 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Value.h"

#include "GSBConetreeNode3D.h"
#include "booga/object/Cylinder3D.h"
#include "booga/object/List3D.h"
#include "booga/object/Polygon3D.h"
#include "booga/object/Shared3D.h"
#include "GSBNodeTools.h"

//_____________________________________________________________________ GSBConetreeNode3D

implementRTTI(GSBConetreeNode3D, Primitive3D);

// initialize static members of GSBConetreeNode3D:
Texture3D* GSBConetreeNode3D::myNodeTexture = NULL;
Texture3D* GSBConetreeNode3D::myTextTexture = NULL;
Texture3D* GSBConetreeNode3D::mySharedTexture = NULL;
Texture3D* GSBConetreeNode3D::myPickedTexture = NULL;


GSBConetreeNode3D::GSBConetreeNode3D(Exemplar exemplar)
: Primitive3D(exemplar), 
  myObject(NULL)
{
  myText = "GSBConetreeNode3D";
}


GSBConetreeNode3D::GSBConetreeNode3D(const RCString& label, const Real& width, const Real& height)
: myText(label),              // node text
  myRadius(1),                // node x-length
  myWidth(width),             // node y-length (depending on text length)
  myHeight(height),           // node z-length (depending on text height)
  myObject(NULL),             // object which is represented by *this
  myDecomposition(NULL)       // decomposition of *this
{}


GSBConetreeNode3D::GSBConetreeNode3D(const GSBConetreeNode3D& node)
: myText(node.myText),
  myRadius(node.myRadius),
  myWidth(node.myWidth),
  myHeight(node.myHeight),
  myObject(node.myObject),
  myDecomposition(node.myDecomposition)
{}


GSBConetreeNode3D::~GSBConetreeNode3D()
{
  delete myDecomposition;
}


Object3D* GSBConetreeNode3D::createDecomposition() const
{
  // test if there's already a decompositon of the node object
  // ==> make a copy.
  if (myDecomposition != NULL)
    return myDecomposition->copy();
    
  List3D* segments = new List3D;

  // add box to decomposition list:
  List3D* frame = new List3D;
  frame->adoptObject(new Cylinder3D(myRadius, 
        Vector3D(0, 0,          -myHeight/2),
        Vector3D(0, myWidth, -myHeight/2)));
  frame->adoptObject(new Cylinder3D(myRadius, 
        Vector3D(0, myWidth, -myHeight/2), 
        Vector3D(0, myWidth,  myHeight/2)));
  frame->adoptObject(new Cylinder3D(myRadius, 
        Vector3D(0, myWidth,  myHeight/2), 
        Vector3D(0, 0,           myHeight/2)));
  frame->adoptObject(new Cylinder3D(myRadius, 
        Vector3D(0, 0,           myHeight/2),
        Vector3D(0, 0,          -myHeight/2)));

  GSBNodeManager* aManager = GSBNodeTools::hasNodeManager(myObject);
  if (aManager && aManager->isMarked() && myPickedTexture) {
    frame->appendTexture(myPickedTexture->copy());
  }
  segments->adoptObject(frame);
  
  // add polygon for background: 
  List<Vector3D> vertices;
  vertices.append(Vector3D(0, 0,          -myHeight/2));
  vertices.append(Vector3D(0, myWidth, -myHeight/2));
  vertices.append(Vector3D(0, myWidth,  myHeight/2));
  vertices.append(Vector3D(0, 0,           myHeight/2));
  
  Polygon3D* background = new Polygon3D(vertices);
  if (myNodeTexture) {
    background->appendTexture(myNodeTexture->copy());
  }
  segments->adoptObject(background);
  
  // add text to decomposition list:
  Text3D* text = new Text3D(myText);
  text->setHeight(myHeight * .8);
  text->addTransform(TransMatrix3D::makeTranslate(
        .2, myWidth * .1, myHeight * .1 - myHeight/2));

  if (myTextTexture) 
    text->appendTexture(myTextTexture->copy());
  
  if (dynamic_cast(Shared3D, myObject) && mySharedTexture) 
    text->appendTexture(mySharedTexture->copy());
    
  segments->adoptObject(text);
  
  ((GSBConetreeNode3D*) this)->myDecomposition = new Shared3D(segments);
  ((GSBConetreeNode3D*) this)->myDecomposition->computeBounds();
  
  return myDecomposition->copy();
}


Vector3D GSBConetreeNode3D::normal(const Vector3D&) const
{
  return Vector3D(1, 0, 0);
}


Object3D* GSBConetreeNode3D::copy() const
{
  return new GSBConetreeNode3D(*this);
}


void GSBConetreeNode3D::doComputeBounds()
{
  delete myDecomposition;
  myBounds.expand(-myRadius/2, 0,      -myHeight/2);
  myBounds.expand( myRadius/2, myWidth, myHeight/2);
}


bool GSBConetreeNode3D::doIntersect(Ray3D& ray)
{
  if (myDecomposition == NULL)
    delete createDecomposition();

  return myDecomposition->intersect(ray);
}


Makeable* GSBConetreeNode3D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(3);
  getParameter(1, RCString, label);
  getParameter(2, Real, width);
  getParameter(3, Real, height);

  if (label.isEmpty()) {
    errMsg = "degenerated label";
    return NULL;
  }

  GSBConetreeNode3D* newNode = new GSBConetreeNode3D(*this);
  newNode->setLabel(label);
  newNode->setWidth(width);
  newNode->setHeight(height);
  
  return newNode;
}


void GSBConetreeNode3D::adoptNodeTexture(Texture3D* texture)
{
  if (texture == myNodeTexture)
    return;
  delete myNodeTexture;
  myNodeTexture = texture;
}


void GSBConetreeNode3D::adoptTextTexture(Texture3D* texture)
{
  if (texture == myTextTexture)
    return;
  delete myTextTexture;
  myTextTexture = texture;
}


void GSBConetreeNode3D::adoptSharedTexture(Texture3D* texture)
{
  if (texture == mySharedTexture)
    return;
  delete mySharedTexture;
  mySharedTexture = texture;
}


void GSBConetreeNode3D::adoptPickedTexture(Texture3D* texture)
{
  if (texture == myPickedTexture)
    return;
  delete myPickedTexture;
  myPickedTexture = texture;
}
