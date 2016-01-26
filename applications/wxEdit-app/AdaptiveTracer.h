/*
 * $RCSfile: AdaptiveTracer.h,v $
 *
 * Copyright (C) 1994-96, Bernhard Bühlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: AdaptiveTracer.h,v 1.5 1997/02/20 09:41:53 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _AdaptiveTracer_H
#define _AdaptiveTracer_H

#include "booga/base/BoundingRect.h"
#include "booga/object/Texture3DContext.h"
#include "booga/component/Renderer.h"

typedef GLfloat RGBPixel[3];
typedef GLint Coordinate[2];

class SSquare;

class SSquare : public BoundingRect {
public:
enum ClosedValue {
  NOT_CLOSED = 0,
  CLOSED_PARTIAL = 1,
  SSCLOSED = 1,
  CLOSED_SUPER = 2
};

public:
  SSquare (int x1, int y1, int xsize, int ysize, RGBPixel p0, RGBPixel p1, RGBPixel p2, RGBPixel p3, int d, SSquare *parent);
  ~SSquare();

  void recomputeStats();
  
  Real getXsize();
  Real getYsize();
  
  bool getClosedValue() { return myClosedValue;};
  void setClosedValue (ClosedValue v);

  void setPrio(Real p);
  Real getPrio() {return myPrio;};

  void setMean(Real mean);
  Real getMean() {return myMean;};

  Real getVar()  {return myVar;};
  void setVar (Real v);

  void setLeaf(bool l);
  bool getLeaf() {return myLeafFlag;};

  int getDepth() { return myDepth;};
  SSquare *getParent() {return myParent;};
  
  RGBPixel *getColor(int i);
  void setColor(int i, RGBPixel p);
  
  Real getArea();
  
  SSquare *child[4];
  
private:
  SSquare *myParent;
  int myDepth;
  ClosedValue myClosedValue;
  bool myLeafFlag;
  Real myVar;
  Real myPrio;
  Real myMean;
  RGBPixel myColor[4];
};

class GLPolyBuffer {
public: 
  GLPolyBuffer(int resX, int resY, int BufferSize = 50);
 ~GLPolyBuffer(); 

  void append (SSquare *s);
  void flush();

private:
  RGBPixel *myColor;
  Coordinate *myCoordinate;
  int myBufferSize;
  int myCurrentElement;
  int myResX, myResY;
};

//____________________________________________________________________ AdaptiveTracer

class AdaptiveTracer : public Renderer {
declareRTTI(AdaptiveTracer);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  AdaptiveTracer();
private:
  AdaptiveTracer(const AdaptiveTracer&);             // No copies.

public:
  ~AdaptiveTracer();                 // Use default version.

private:
  AdaptiveTracer& operator=(const AdaptiveTracer&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class AdaptiveTracer
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:

  void subdivideToDepth(SSquare *s, int depth);
  void subdivideSquare(SSquare *sq);
  SSquare *createSquare(int xp, int yp, int xs, int ys, RGBPixel p0, RGBPixel p1, RGBPixel p2, RGBPixel p3, int d, SSquare *parent);
  void traceRay(int x, int y, int smode, RGBPixel p);
  SSquare *selectSquare(SSquare *s);
  void recomputeStats(SSquare *sq);
  bool recomputePriority(SSquare *sq);

  bool nextSquare();

  void setRectangle (BoundingRect b);

  void draw(SSquare *s);
  bool overlapsRect(SSquare *s);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class PixmapRenderer
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool postprocessing();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component3Dto2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool doExecute();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  SSquare *mySquare;
  int  SuperSampleMode;
  Texture3DContext myContext;
  Ray3D *myRay;
  BoundingRect myRect;
  bool myRectmode;
  GLPolyBuffer *myPolyBuffer;
};

//______________________________________________________________________ INLINES

#endif // _AdaptiveTracer_H
