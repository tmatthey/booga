/*
 * $RCSfile: Wireframe.h,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: Wireframe.h,v 1.11 1997/05/01 12:55:18 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Wireframe_H
#define _Wireframe_H

#include "booga/base/Color.h"
#include "booga/base/List.h"
#include "booga/base/Vector2D.h"
#include "booga/object/Texture3DContext.h"
#include "booga/component/Renderer.h"

class Triangle3D;
class Box3D;
class Polygon3D;
class Line3D;
class Disc3D;
class Line2D;
//____________________________________________________________________ Wireframe

class Wireframe : public Renderer {
declareRTTI(Wireframe);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Wireframe();
private:
  Wireframe(const Wireframe&);	       // No copies.

public:
  // virtual ~Wireframe();                 // Use default version.

private:
  Wireframe& operator=(const Wireframe&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Wireframe
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setSortList(bool sort);
  bool getSortList() const;
  // Switch between sorted list of lines and order of appearence.
  // Set this flag before applying this component!

  void setOptimizeList(bool opt);
  bool getOptimizeList() const;
  // Switch between optimized (no double lines) list of lines
  // Set this flag before applying this component!

private:
  Traversal::Result visit(Triangle3D* obj);
  Traversal::Result visit(Box3D* obj);
  Traversal::Result visit(Polygon3D* obj);
  Traversal::Result visit(Line3D* obj);
  Traversal::Result visit(Disc3D* obj);

  void addLine(const Vector2D& from, const Vector2D& to,
	       const Color& c0, const Color& c1);

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
  Color myDefaultColor;
  Texture3DContext myTextureContext;
  bool mySortList;
  bool myOptimizeList;
  List<Line2D*> myLines;
  long myRemovedLines;
};

#endif // _Wireframe_H
