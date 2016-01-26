/*
 * CTUMRenderer2D.h
 *
 * Copyright (C) 1994-96, Thomas Wenger
 *                        Thomas von Siebenthal
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: CTUMRenderer2D.h,v 1.25 1996/10/30 15:31:42 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _CTUMRenderer2D_H
#define _CTUMRenderer2D_H

#include <iostream.h>
#include "booga/component/Operation2D.h"
#include "CTClassDescription2D.h"

//_________________________________________________________________ CTUMRenderer2D

class CTUMRenderer2D : public Operation2D {
declareRTTI(CTUMRenderer2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  CTUMRenderer2D();
private:
  CTUMRenderer2D(const CTUMRenderer2D&);            // No copies.

public:
  // virtual ~CTUMRenderer2D();                   // Use default version.

private:
  void CTUMRenderer2DClean();
  CTUMRenderer2D& operator=(const CTUMRenderer2D&); // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class TextBox2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // Methods to manage the Dockingpoints:
  void generateDockingPoints(CTClassDescription2D* theClass);
  long getDockingPointIndexMax(CTClassDescription2D* theClass);
  long getDockingPointIndexMin(CTClassDescription2D* theClass);
  Vector2D getDockingPointByIndex(CTClassDescription2D* theClass, long index) const;
  void getNearestDockingPoints(CTClassDescription2D* thiaClass, CTClassDescription2D* otherClass, Vector2D &thisPoint, Vector2D &otherPoint);
  // Methods to set the rendering option flags:
  void setViewsIsVisible(bool isOn);
  void setOperationsIsVisible(bool isOn);
  void setAttributesIsVisible(bool isOn);
  void setOperationDetailsIsVisible(bool isOn);
  // If next flag is set to false, then no positioning is done by the 
  // renderer; so existing positions in the world are kept
  void setmyPositioningIsEnabled(bool isEnabled);
  
 
private:
  void doBodies(CTClassDescription2D* obj);
  void doPositioning(CTClassDescription2D* obj);
  void doConnectors(CTClassDescription2D* obj);
  
private:
  Traversal::Result visit(CTClassDescription2D* obj);
 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Operation2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual bool doExecute();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Visitor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Traversal::Result dispatch(Makeable* obj);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  enum ERenderingStatus {DoingBodies, DoingPositioning, DoingConnectors} myRenderingStatus;
  Real myBodyMaxHeight;
  int myNumberOfClasses;
  int myNumberOfActualClass;
  int myClassesPerRow;
  int myClassesPerColumn;
  Real myClassGridDx, myClassGridDy;
  bool myViewsIsVisible;
  bool myOperationsIsVisible;
  bool myAttributesIsVisible;
  bool myOperationDetailsIsVisible;
  bool myPositioningIsEnabled;

  // constants for this class:
  Real FONT_HEIGHT_CLASSNAME;           // titleline with classname
  Real FONT_HEIGHT_STANDARD;            // all the normal text
  Real TEXTBOX_STANDARD_WIDTH;          // fixed width of the boxes
  Real TEMPLATE_PARAMETER_BOXWIDTH_FACTOR;  // to be multiplied with TEXTBOX_STANDARD_WIDTH
  int  TEXTBOX_STANDARD_LINELENGTH;     // number of charachter per Line
  Real STANDARD_ARROW_LENGTH;           // length of an arrow-wing
  Real ARROW_ALPHA;                     // opening of the arrows

  // the textures:
  Texture2D* BlueGLTexture;
  Texture2D* BlueTexture;
  Texture2D* RedGLTexture; 
  Texture2D* RedTexture;
  Texture2D* GreenGLTexture;
  Texture2D* GreenTexture;
  Texture2D* BlackGLTexture;
  Texture2D* BlackTexture;
  Texture2D* WhiteGLTexture;
  Texture2D* WhiteTexture;

};

#endif // _CTUMRenderer2D_H

