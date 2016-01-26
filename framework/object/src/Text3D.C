/*
 * $RCSfile: Text3D.C,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *		        Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: Text3D.C,v 1.15 1997/09/19 07:15:00 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include <sstream>

#include "booga/base/Value.h"
#include "booga/base/Report.h"
#include "booga/object/List3D.h"
#include "booga/object/Shared3D.h"
#include "booga/object/Sphere3D.h"
#include "booga/object/Cylinder3D.h"
#include "booga/object/Text3D.h"
#include "booga/object/Text3DAttr.h"
#include "booga/object/DummyMakeable.h"
#include "booga/object/MakeableHandler.h"

//_______________________________________________________________________ Text3D

implementRTTI(Text3D, Primitive3D);

Text3D::Text3D(Exemplar exemplar)
: Primitive3D(exemplar)
{
  myHeight = 10; 
  myRadius = 1; 
  myFont = StrokeFont::searchFont("ROMAN");
  myDecomposition = NULL;
}

Text3D::Text3D(const RCString& text)
: myText(text)
{
  myHeight = 10;
  myRadius = 1; 
  myFont = StrokeFont::searchFont("ROMAN");
  myDecomposition = NULL;
}

Text3D::Text3D(const Text3D& text)
: Primitive3D(text)
{
  myHeight = text.myHeight;
  myRadius = text.myRadius;
  myText   = text.myText;
  myFont   = text.myFont;

  if (text.myDecomposition != NULL)
    myDecomposition = text.myDecomposition->copy();
  else
    myDecomposition = NULL;
}

Text3D::~Text3D()
{
  delete myDecomposition;
}

void Text3D::setHeight(Real height)
{
  if (height < EPSILON) {
    std::stringstream os;
    os << "[Text3D::setHeight] illegal value for height: " << height;
    Report::warning(os);
    return;
  }
  
  myHeight = height;
}

void Text3D::setRadius(Real radius)
{
  if (radius < EPSILON) {
    std::stringstream os;
    os << "[Text3D::setRadius] illegal value for radius: " << radius;
    Report::warning(os);
    return;
  }

  myRadius = radius;
}

void Text3D::setText(const RCString& text)
{
  myText = text;
}

void Text3D::setFont(const RCString& fontName)
{
  const StrokeFont* font = StrokeFont::searchFont(fontName);
  if (font == NULL) {
    std::stringstream os;
    os << "[Text3D::setFont] unknown font \"" << fontName << "\"";;
    Report::warning(os);
    return;
  }
  
  myFont = font;
}

void Text3D::setFont(const StrokeFont* font)
{
  if (font == NULL) {
    Report::warning("[Text3D::setFont] NULL pointer passed");
    return;
  }

  myFont = font;
}

Object3D* Text3D::createDecomposition() const
{
  //
  // We already have a valid decomposition of the text object -> just make a copy.
  //
  if (myDecomposition != NULL)
    return myDecomposition->copy();
    
  if (myText.isEmpty() || myFont == NULL)
    return NULL;

  List3D* segments = new List3D;

  const CharRec* ch = NULL;
  StrokeRec* stroke = NULL;
  Vector2D*  coord  = NULL;
  int numStrokes, numCoords;
  Vector3D translate;
  Real scaleFactor = myHeight/(myFont->getTop());
  Vector3D last, curr;
  Primitive3D* primitive;

  //
  // For every character in the text, look up the strokes in the font definition
  // and create line segments out of it.
  //
  for (int i=0; i<myText.length(); i++) {
    ch = myFont->getChar(myText[i]);
    if (ch != NULL) {
      for (numStrokes=ch->myNumStrokes, stroke=ch->myStrokes; 
           numStrokes > 0; 
           numStrokes--, stroke++) {
        curr = Vector3D(0, (*stroke->myCoords).x(), (*stroke->myCoords).y());
        for (numCoords=stroke->myNumCoords-1, coord=stroke->myCoords+1; 
             numCoords > 0; 
             numCoords--, coord++) {
          last = curr;
          curr = Vector3D(0, (*coord).x(), (*coord).y());

          primitive = new Cylinder3D(myRadius, (translate+last*scaleFactor), 
                                               (translate+curr*scaleFactor));
          primitive->setPrecision(0.2);                                    
          segments->adoptObject(primitive);
          
          primitive = new Sphere3D(myRadius, translate+last*scaleFactor);
          primitive->setPrecision(0.2);                                    
          segments->adoptObject(primitive);
        }
        primitive = new Sphere3D(myRadius, translate+curr*scaleFactor);
        primitive->setPrecision(0.2);                                    
        segments->adoptObject(primitive);
      }
      translate += Vector3D(0, ch->myRight*scaleFactor+myRadius*2, 0);
    }
  }

  ((Text3D*)this)->myDecomposition = new Shared3D(segments);
  ((Text3D*)this)->myDecomposition->computeBounds();
  
  return myDecomposition->copy();
}

Vector3D Text3D::normal(const Vector3D&) const
{
  return Vector3D(1,0,0);
}

Object3D* Text3D::copy() const
{
  return new Text3D(*this);
}

void Text3D::doComputeBounds()
{
  if (myFont == NULL)
    return;

  if (myDecomposition != NULL) {
    delete myDecomposition;
    myDecomposition = NULL;
  }

  Real scaleFactor = myHeight/(myFont->getTop());
  Real length = 0;
  const CharRec* ch = NULL;

  for (int i=0; i<myText.length(); i++) {
    ch = myFont->getChar(myText[i]);
    if (ch != NULL)
      length += ch->myRight*scaleFactor+2*myRadius;
  }
  
  myBounds.expand(Vector3D(myRadius, -myRadius, myFont->getBottom()*scaleFactor-myRadius));
  myBounds.expand(Vector3D(-myRadius, length, myHeight+myRadius));
}

bool Text3D::doIntersect(Ray3D& ray)
{
  if (myDecomposition == NULL)
    delete Text3D::createDecomposition();

  return myDecomposition->intersect(ray);
}

int Text3D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  Text3DAttr* attr = dynamic_cast<Text3DAttr*>(specifier);
  if (attr != NULL) {
    // The Text3DAttr object knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute(this);

    delete attr;
    return 1;  
  }

  // 
  // Let papa do the rest ...
  //
  return Object3D::setSpecifier(errMsg, specifier);
}

Makeable* Text3D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(3);
  getParameter(1, Real, height);
  getParameter(2, Real, radius);
  getParameter(3, RCString, text);

  Text3D* newText = new Text3D(*this);
  newText->setHeight(height);
  newText->setRadius(radius);
  newText->setText(text);

  return newText;
}

static const RCString text3DKeyword("text");

RCString Text3D::getKeyword() const {
  return text3DKeyword;
}

List<Value*>* Text3D::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getHeight()));
  parameters->append(new Value(getRadius()));
  parameters->append(new Value(RCString("\"") + getText() + RCString("\"")));
  return parameters;
}

void Text3D::iterateAttributes(MakeableHandler* handler) {
  Object3D::iterateAttributes(handler);
  RCString fontname(getFont()->getName());
  if (!fontname.isEmpty()) {
    fontname = RCString("\"") + fontname + RCString("\"");
    Value myValue(fontname);
    DummyMakeable m("font", myValue);
    handler->handle(&m);
  }
}
