/*
 * TextBox2D.C
 *
 * Copyright (C) 1994-96, Thomas Wenger <wenger@iam.unibe.ch>
 *                        Thomas von Siebenthal <siebenth@iam.unibe.ch>
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
 *  $Id: TextBox2D.C,v 1.18 1996/10/30 15:31:43 amann Exp $
 * -----------------------------------------------------------------------------
 */
 


#include "booga/base/Value.h"
//#include "booga/object/Visitor2D.h"
#include "booga/object/List2D.h"
#include "booga/object/Line2D.h"
#include "booga/object/Text2D.h"
#include "TextBox2D.h"
#include "TextBox2DAttr.h"


//_____________________________________________________________________ TextBox2D

implementRTTI(TextBox2D, Primitive2D);

TextBox2D::TextBox2D(Exemplar exemplar)
: Primitive2D(exemplar), myPosition(0,0)
{
  myWidth = 100;
  myBorderWidth = 10;
  myBorderHeight = 10;
  myFontHeight = 10;
  myTextLineSpacing = 1.5;
}

TextBox2D::TextBox2D(const List<RCString>& textLines)
: myTextLines(textLines), myPosition(0,0)
{
  myWidth = 100;
  myBorderWidth = 10;
  myBorderHeight = 10;
  myFontHeight = 10;
  myTextLineSpacing = 1.5;
}

void TextBox2D::setPosition(const Vector2D& position)
{
  myPosition = position;
}

const Vector2D& TextBox2D::getPosition() const
{
  return myPosition;
}

void TextBox2D::setWidth(Real width)
{
  myWidth = width;
};

Real TextBox2D::getWidth() const
{
  return myWidth;
};


void TextBox2D::setBorderWidth(Real borderWidth)
{
  myBorderWidth = borderWidth;
};

Real TextBox2D::getBorderWidth() const
{
  return myBorderWidth;
};


void TextBox2D::setBorderHeight(Real borderHeight)
{
  myBorderHeight = borderHeight;
};

Real TextBox2D::getBorderHeight() const
{
  return myBorderHeight;
};


void TextBox2D::setFontHeight(Real fontHeight)
{
  myFontHeight = fontHeight;
};


void TextBox2D::setTextLineSpacing(Real textLineSpacing)
{
  myTextLineSpacing = textLineSpacing;
};


Real TextBox2D::calculateHeight() const
{
  int numOfTextLines = myTextLines.count();
  if (numOfTextLines==0) 
    return 2*myBorderHeight;
  else
    return (numOfTextLines-1) * myFontHeight * myTextLineSpacing
          + myFontHeight + 2 * myBorderHeight;
}

// Wrap the textlines of the box to a maximum length of lineLength characters
// per line:
void TextBox2D::wrapText(int lineLength)
{
  for (long i=0; i<myTextLines.count(); i++)
  {
    if (myTextLines.item(i).length()>lineLength)
    {
      RCString newLine = "   " + myTextLines.item(i)(lineLength,myTextLines.item(i).length()-1);
      myTextLines.insert(i+1,newLine);
      newLine = myTextLines.item(i)(0,lineLength-1) + "\\";
      myTextLines.insert(i+1,newLine);
      myTextLines.remove(i);
    }
  }
}   
      

Object2D* TextBox2D::createDecomposition() const
{
  List2D* myDecomposition = new List2D;
  
  // move the whole box to the correct position:
  myDecomposition->addTransform(TransMatrix2D::makeTranslate(myPosition));
  
  // prepare the points of the box:
  Real myHeight = calculateHeight();
  Vector2D UL = Vector2D(0,myHeight);       // upper left
  Vector2D UR = Vector2D(myWidth,myHeight); // upper right
  Vector2D LL = Vector2D(0,0);              // lower right
  Vector2D LR = Vector2D(myWidth,0);        // lower left
  
  // hook up the lines of the box in the List2D:
  myDecomposition->adoptObject(new Line2D(UL,UR));
  myDecomposition->adoptObject(new Line2D(UR,LR));
  myDecomposition->adoptObject(new Line2D(LR,LL));
  myDecomposition->adoptObject(new Line2D(LL,UL));
  
  // hook up the textlines line by line in the List2D:
  for (int i=0; i<myTextLines.count(); i++)
  {
    Text2D* aTextLine = new Text2D(myTextLines.item(i));
    aTextLine->setHeight(myFontHeight);
    // set a transformation matrix for the correct position:
    Real dx = myBorderWidth;
    Real dy = myHeight - myBorderHeight - myFontHeight - i*myFontHeight*myTextLineSpacing;
    aTextLine->addTransform(TransMatrix2D::makeTranslate(dx,dy));
    myDecomposition->adoptObject(aTextLine);
  }
    
  return myDecomposition;
}


Object2D* TextBox2D::copy() const
{
  return new TextBox2D(*this);
}

void TextBox2D::doComputeBounds()
{
  myBounds.expand(myPosition);
  myBounds.expand(myPosition[0]+myWidth, myPosition[1]+calculateHeight());
}

/*
 * Compute the distance from the ray origin to the 4 lines.
 *
 * Line:       a + td
 * Ray origin: p
 *
 *         (p-a) . d
 *    v = ----------- * d
 *            d . d
 *
 *    distance = | p - a - v |
 */
bool TextBox2D::doIntersect(Ray2D& ray)
{ 
  Real myHeight = calculateHeight();
  Vector2D UL = myPosition+Vector2D(0,myHeight);       // upper left
  Vector2D UR = myPosition+Vector2D(myWidth,myHeight); // upper right
  Vector2D LL = myPosition;                            // lower right
  Vector2D LR = myPosition+Vector2D(myWidth,0);        // lower left
 
  Vector2D d1 = LL - UL;
  Vector2D d2 = UL - UR;
  Vector2D d3 = UR - LR;
  Vector2D d4 = LR - LL;
  
  Vector2D rayOrigin = ray.getOrigin();
  Vector2D v1 = (((rayOrigin-UL)^d1)/d1.sqr())*d1;
  Vector2D v2 = (((rayOrigin-UR)^d2)/d2.sqr())*d2;
  Vector2D v3 = (((rayOrigin-LR)^d3)/d3.sqr())*d3;
  Vector2D v4 = (((rayOrigin-LL)^d4)/d4.sqr())*d4;
  
  Real distance1 = (rayOrigin-UL-v1).length();
  Real distance2 = (rayOrigin-UR-v2).length();
  Real distance3 = (rayOrigin-LR-v3).length();
  Real distance4 = (rayOrigin-LL-v4).length();
    
  // test if ray is inside of the box:
  if ((rayOrigin.x()>=LL.x()) && (rayOrigin.x()<=UR.x()) &&
     (rayOrigin.y()>=LL.y()) && (rayOrigin.y()<=UR.y())) {
     ray.setBestHitObject(this);
     ray.setBestHitDistance(0.0);
     return true;
  }
  
  // ray is outside of the box, so check all 4 lines:
  if (distance1<ray.getBestHitDistance()) {
     ray.setBestHitObject(this);
     ray.setBestHitDistance(distance1);
     return true;
  }
 
  if (distance2<ray.getBestHitDistance()) {
     ray.setBestHitObject(this);
     ray.setBestHitDistance(distance2);
     return true;
  }
 
  if (distance3<ray.getBestHitDistance()) {
     ray.setBestHitObject(this);
     ray.setBestHitDistance(distance3);
     return true;
  }
 
  if (distance4<ray.getBestHitDistance()) {
     ray.setBestHitObject(this);
     ray.setBestHitDistance(distance4);
     return true;
  }
  
  // if we reach this point, then the ray does not hit this object:
  return false;
}

void TextBox2D::addTextLine(RCString text)
{
  myTextLines.append(text);
}

Makeable* TextBox2D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(2);
  getParameter(1, Vector2D, pos);
  getParameter(2, Real, width);
  
  TextBox2D* newBox = new TextBox2D(*this);
  newBox->setPosition(pos);
  newBox->setWidth(width);
  
  return newBox;
}

int TextBox2D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  TextBox2DAttr* attr = dynamic_cast<TextBox2DAttr*>(specifier);
  if (attr != NULL) {
    // The CTClassDescription2DAttr object knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute(this);

    delete attr;
    return 1;  
  }

  // 
  // Let papa do the rest ...
  //
  return Primitive2D::setSpecifier(errMsg, specifier);
}

