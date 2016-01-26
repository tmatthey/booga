/*
 * GSBConetreeNode3D.h
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
 *  $Id: GSBConetreeNode3D.h,v 1.7 1997/04/08 11:04:40 habegger Exp $
 * -----------------------------------------------------------------------------
 */


#ifndef _GSBConetreeNode3D_H
#define _GSBConetreeNode3D_H

#include "booga/object/Text3D.h"
#include "booga/object/Texture3D.h"


//_____________________________________________________________________ GSBConetreeNode3D

class GSBConetreeNode3D : public Primitive3D {
declareRTTI(GSBConetreeNode3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBConetreeNode3D(Exemplar);
  GSBConetreeNode3D(const RCString& label, const Real& width, const Real& height);
  GSBConetreeNode3D(const GSBConetreeNode3D&);          // Use default version.

public:
  virtual ~GSBConetreeNode3D();

private:
  GSBConetreeNode3D& operator=(const GSBConetreeNode3D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBConetreeNode3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setLabel(const RCString& text) { myText = text; };
  const RCString& getLabel() const { return myText; };

  void setWidth(Real width) { myWidth = width; };
  const Real getWidth() const { return myWidth; };
  
  void setHeight(Real height) { myHeight = height; };
  const Real getHeight() const { return myHeight; };
  
  void setRadius(Real radius) { myRadius = radius; };
  const Real getRadius() const { return myRadius; };
  
  void setRepresentWho(Object3D* original) { myObject = original; };
  Object3D* getRepresentWho() { return myObject; };

  static void adoptNodeTexture(Texture3D* nodeTexture);
  static void adoptTextTexture(Texture3D* textTexture);
  static void adoptSharedTexture(Texture3D* sharedTexture);
  static void adoptPickedTexture(Texture3D* pickedTexture);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Primitive3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* createDecomposition() const;
  virtual Vector3D normal(const Vector3D& point) const; 
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* copy() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual void doComputeBounds();
private:
  virtual bool doIntersect(Ray3D& ray);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  RCString    myText;             // node text
  Real        myRadius;           // node x-length
  Real        myWidth;            // node y-length
  Real        myHeight;           // node z-length

  Object3D*   myObject;           // object represented by *this
  
  static Texture3D* myNodeTexture;
  static Texture3D* myTextTexture;
  static Texture3D* mySharedTexture;
  static Texture3D* myPickedTexture;
  
  Object3D*   myDecomposition; 
  // The decomposition ist cached for each node object.
};

//______________________________________________________________________ INLINES

#endif // _GSBConetreeNode3D_H

