/*
 * $RCSfile: Rasterizer.h,v $
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
 *  $Id: Rasterizer.h,v 1.17 1996/09/13 08:06:10 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Rasterizer_H
#define _Rasterizer_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/Color.h"
#include "booga/base/MPixmapExemplar.h"
#include "booga/object/Texture2DContext.h"
#include "booga/component/Operation2D.h"

class Camera2D;
class Point2D;
class Line2D;
class Circle2D;
class Pixmap2D;

//___________________________________________________________________ Rasterizer

class Rasterizer : public Operation2D, public MPixmapExemplar {
declareRTTI(Rasterizer2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Rasterizer();
private:
  Rasterizer(const Rasterizer&);              // No copies.

public:
  virtual ~Rasterizer();

private:
  Rasterizer& operator=(const Rasterizer&);   // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Rasterizer
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void adoptCamera(Camera2D* camera);
  // Set camera to use for rendering
  void deleteCamera();
  const Camera2D* getCamera() const;

private:
  void setPixel(int x, int y);

private: 
  Traversal::Result visit(Point2D* point);
  Traversal::Result visit(Line2D* line);
  Traversal::Result visit(Circle2D* circle);
  Traversal::Result visit(Pixmap2D* pixmap);
  //
  // Operations on the differnt object types, to be called 
  // from dispatch()
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool preprocessing();
  virtual bool postprocessing();

private:
  virtual void cleanupAfterFailure();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Visitor  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Traversal::Result dispatch(Makeable* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Camera2D*        myCamera;
  bool             myHasAdoptedCamera;
  AbstractPixmap*  myPixmap;
  Color            myDefaultColor;
  Texture2DContext myContext;
};

//______________________________________________________________________ INLINES

inline const Camera2D* Rasterizer::getCamera() const
{
  return myCamera;
}

#endif // _Rasterizer_H
