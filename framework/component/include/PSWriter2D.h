/*
 * $RCSfile: PSWriter2D.h,v $
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: PSWriter2D.h,v 1.11 1997/09/19 07:14:38 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PSWriter2D_H
#define _PSWriter2D_H

#include <fstream.h>

#include "booga/base/RCString.h"
#include "booga/base/PrimitiveTypes.h"
#include "booga/component/Operation2D.h"

class Line2D;
class Circle2D;
class Text2D;
class Pixmap2D;
class Camera2D;

//___________________________________________________________________ PSWriter2D

class PSWriter2D : public Operation2D {
declareRTTI(PSWriter2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PSWriter2D(const RCString& filename = "");                             
private:
  PSWriter2D(const PSWriter2D&);            // No copies.

public:
  // virtual ~PSWriter2D();                 // Use default version.

private:
  PSWriter2D& operator=(const PSWriter2D&); // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class PSWriter2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void adoptCamera(Camera2D* camera);
  void deleteCamera();
  // Set or delete camera for rendering.

private:
  void printPostScriptHeader();
  void printPostScriptFooter();

private:
  Traversal::Result visit(Line2D* line);
  Traversal::Result visit(Text2D* text);
  Traversal::Result visit(Circle2D* circle);
  Traversal::Result visit(Pixmap2D* pixi);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool preprocessing();
  virtual bool postprocessing();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Visitor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Traversal::Result dispatch(Makeable* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Camera2D*  myCamera;
  bool       myHasAdoptedCamera;
  RCString   myFilename;
  ofstream   myOfs;    
};

//______________________________________________________________________ INLINES

#endif // _PSWriter2D_H

