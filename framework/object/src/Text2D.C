/*
 * $RCSfile: Text2D.C,v $ 
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
 *  $Id: Text2D.C,v 1.17 1997/09/19 07:14:59 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include <strstream.h>

#include "booga/base/Value.h"
#include "booga/base/Report.h"

#include "booga/object/Shared2D.h"
#include "booga/object/List2D.h"
#include "booga/object/Line2D.h"
#include "booga/object/Text2D.h"
#include "booga/object/Text2DAttr.h"
#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"
//_______________________________________________________________________ Text2D

implementRTTI(Text2D, Primitive2D);

Text2D::Text2D(Exemplar exemplar)
: Primitive2D(exemplar)
{
  myHeight = 10;  
  myFont = StrokeFont::searchFont("ROMAN");
  myDecomposition = NULL;
}

Text2D::Text2D(const RCString& text)
: myText(text)
{
  myHeight = 10;
  myFont = StrokeFont::searchFont("ROMAN");
  myDecomposition = NULL;
}

Text2D::Text2D(const Text2D& text)
: Primitive2D(text)
{
  myHeight = text.myHeight;
  myText   = text.myText;
  myFont   = text.myFont;

  if (text.myDecomposition != NULL)
    myDecomposition = text.myDecomposition->copy();
  else
    myDecomposition = NULL;
}

Text2D::~Text2D()
{
  delete myDecomposition;
}

void Text2D::setHeight(Real height)
{
  myHeight = height;
}

void Text2D::setText(const RCString& text)
{
  myText = text;
}

void Text2D::setFont(const RCString& fontName)
{
  const StrokeFont* font = StrokeFont::searchFont(fontName);
  if (font == NULL) {
    ostrstream os;
    os << "[Text2D::setFont] unknown font \"" << fontName << "\"";;
    Report::warning(os);
    return;
  }
  
  myFont = font;
}

void Text2D::setFont(const StrokeFont* font)
{
  if (font == NULL) {
    Report::warning("[Text2D::setFont] NULL pointer passed");
    return;
  }

  myFont = font;
}

Object2D* Text2D::createDecomposition() const
{
  //
  // We already have a valid decomposition of the text object -> just make a copy.
  //
  if (myDecomposition != NULL)
    return myDecomposition->copy();
    
  if (myText.isEmpty() || myFont == NULL)
    return NULL;
    
  List2D* segments = new List2D;

  const CharRec* ch = NULL;
  StrokeRec* stroke = NULL;
  Vector2D*  coord  = NULL;
  int numStrokes, numCoords;
  Vector2D translate;
  Real scaleFactor = myHeight/(myFont->getTop());
  
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
        for (numCoords=stroke->myNumCoords-1, coord=stroke->myCoords; 
             numCoords > 0; 
             numCoords--, coord++) {
          segments->adoptObject(new Line2D(translate + (*coord)*scaleFactor, 
                                           translate + (*(coord+1))*scaleFactor));
        }
      }
      translate += Vector2D(ch->myRight*scaleFactor, 0);
    }
  }

  ((Text2D*)this)->myDecomposition = new Shared2D(segments);
  ((Text2D*)this)->myDecomposition->computeBounds();
  return myDecomposition->copy();
}

Object2D* Text2D::copy() const
{
  return new Text2D(*this);
}

void Text2D::doComputeBounds()
{
  if (myFont == NULL)
    return;

  if (myDecomposition != NULL) {
    delete myDecomposition;
    myDecomposition = NULL;
  }
    
  Real scaleFactor = myHeight/(myFont->getTop());
  Vector2D extent(0, myHeight);
  const CharRec* ch = NULL;

  for (int i=0; i<myText.length(); i++) {
    ch = myFont->getChar(myText[i]);
    if (ch != NULL)
      extent += Vector2D(ch->myRight*scaleFactor, 0);
  }
  
  myBounds.expand(Vector2D(0, myFont->getBottom()*scaleFactor));
  myBounds.expand(extent);
}

bool Text2D::doIntersect(Ray2D& ray)
{
  if (myDecomposition == NULL)
    delete Text2D::createDecomposition();

  return myDecomposition->intersect(ray);
}
//
//  Vector2D to = Vector2D(myText.length()*myHeight, myHeight);
//  Vector2D d1 = to - ray.getOrigin();
//  Vector2D d2 = ray.getOrigin();
//  Real distance = min(min(d1.x(), d1.y()), min(d2.x(), d2.y()));
//
//  if (distance >= ray.getBestHitDistance())
//    return false;
//
//  //
//  // HIT!!! 
//  // 
//  ray.setBestHitObject(this);
//  ray.setBestHitDistance(distance); 
//  
//  return true;
//}

int Text2D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  Text2DAttr* attr = dynamic_cast(Text2DAttr, specifier);
  if (attr != NULL) {
    // The Text2DAttr object knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute(this);

    delete attr;
    return 1;  
  }

  // 
  // Let papa do the rest ...
  //
  return Object2D::setSpecifier(errMsg, specifier);
}

Makeable* Text2D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(2);
  getParameter(1, Real, height);
  getParameter(2, RCString, text);

  Text2D* newText = new Text2D(*this);
  newText->setHeight(height);
  newText->setText(text);

  return newText;
}

static const RCString text2DKeyword("text");

RCString Text2D::getKeyword() const {
  return text2DKeyword;
}

List<Value*>* Text2D::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getHeight()));
  parameters->append(new Value(RCString("\"") + getText() + RCString("\"")));
  return parameters;
}

void Text2D::iterateAttributes(MakeableHandler* handler) {
  Object2D::iterateAttributes(handler);
  RCString fontname(getFont()->getName());
  if (!fontname.isEmpty()) {
    fontname = RCString("\"") + fontname + RCString("\"");
    Value myValue(fontname);
    DummyMakeable m("font", myValue) ;
    handler->handle(&m);
  }
}
