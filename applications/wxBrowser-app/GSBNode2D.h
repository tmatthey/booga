/*
 * GSBNode2D.h
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
 *  $Id: GSBNode2D.h,v 1.9 1997/04/22 13:39:37 habegger Exp $
 * -----------------------------------------------------------------------------
 */


#ifndef _GSBNode2D_H
#define _GSBNode2D_H

#include "booga/object/Object3D.h"
#include "booga/object/Primitive2D.h"
#include "booga/object/Texture2D.h"

#include "GSBNode.h"

//_____________________________________________________________________ GSBNode2D

class GSBNode2D : public Primitive2D {
declareRTTI(GSBNode2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBNode2D(Exemplar);
  GSBNode2D(const RCString& label, Real width, Real height);
  GSBNode2D(const GSBNode2D&);          // Use default version.

public:
  virtual ~GSBNode2D();

private:
  GSBNode2D& operator=(const GSBNode2D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBNode2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setLabel(const RCString& text) { myText = text; };
  const RCString& getLabel() const    { return myText; };

  void setWidth(Real width);
  const Real getWidth() const { return myWidth; };
  
  void setHeight(Real height);
  const Real getHeight() const { return myHeight; };
  
  void setRepresentWho(Object3D* original) { myObject = original; };
  Object3D* getRepresentWho() { return myObject; };

  static void adoptNodeTexture(Texture2D* nodeTexture);
  static void adoptTextTexture(Texture2D* textTexture);
  static void adoptSharedTexture(Texture2D* sharedTexture);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Primitive2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object2D* createDecomposition() const;
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object2D* copy() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual void doComputeBounds();

private:
  virtual bool doIntersect(Ray2D& ray);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual RCString getKeyword() const;
  virtual void iterateAttributes(MakeableHandler *handler);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  RCString    myText;

  Real        myWidth;         // node x-length
  Real        myHeight;        // node y-length
  
  static Texture2D* myNodeTexture;
  static Texture2D* myTextTexture;
  static Texture2D* mySharedTexture;
  
  Object3D*   myObject;        // Object represented by *this
  
  Object2D*   myDecomposition; 
    // The decomposition ist cached for each node object.
};


//______________________________________________________________________ INLINES

inline
void GSBNode2D::setHeight(Real height)
{
  if (height <= 0.0)
    Report::error("[GSBNode2D::setHeight] Illegal height specified");
  myHeight = height;
};


inline
void GSBNode2D::setWidth(Real width)
{
  if (width <= 0.0)
    Report::error("[GSBNode2D::setWidth] Illegal width specified");
  myWidth = width;
};

#endif // _GSBNode2D_H



