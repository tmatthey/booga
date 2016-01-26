/*
 * $RCSfile: wxAdaptiveTracer.C,v $
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
 *  $Id: wxAdaptiveTracer.C,v 1.1 1997/09/19 08:41:48 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include <strstream.h>  // ostrstream
#include <GL/gl.h>
#include <GL/glu.h>

#include "booga/base/Statistic.h"
#include "booga/object/Pixmap2D.h"
#include "booga/object/Camera3D.h"
#include "booga/object/Primitive3D.h"
#include "booga/object/Aggregate3D.h"
#include "booga/object/Path3D.h"
#include "booga/object/Ray3D.h"
#include "booga/object/Ray3DFactory.h"
#include "booga/object/Texture3D.h"
#include "booga/object/Viewing3D.h"
#include "booga/glwrapper/GLTexture.h"
#include "booga/glwrapper/GLUtilities.h"

#include "booga/wxwrapper/wxAdaptiveTracer.h"

//____________________________________________________________________ wxAdaptiveTracer

implementRTTI(wxAdaptiveTracer, Renderer);
#define MINAREA		3
#define SHARED_EDGES 1
wxAdaptiveTracer::wxAdaptiveTracer() : Renderer() 
{
  SuperSampleMode = 0;
  mySquare = NULL;
  myRectmode = false;
  myRay = Ray3DFactory::createRay(Vector3D(0,0,0), Vector3D(1,0,0));
  myPolyBuffer = NULL;
}

wxAdaptiveTracer::~wxAdaptiveTracer()
{
  delete myRay;
  delete mySquare;
  delete myPolyBuffer;
}

bool wxAdaptiveTracer::postprocessing()
{  
  return Renderer::postprocessing();
}

bool wxAdaptiveTracer::doExecute()
{
  myPolyBuffer = new GLPolyBuffer (getCamera()->getViewing()->getResolutionX(), 
                          getCamera()->getViewing()->getResolutionY(), 100);

  //
  // Setup the texturing context.
  //

  myContext.setWorld(getWorld());
  myContext.setAmbientLightSources(getAmbientLightSources());
  myContext.setDirectedLightSources(getDirectedLightSources());
  
  // Some variables for use in the loop.
  
  int resX = getCamera()->getViewing()->getResolutionX();
  int resY = getCamera()->getViewing()->getResolutionY(); 
  
  RGBPixel p0, p1, p2, p3;
  
  traceRay (0,0,0,p0);
  traceRay (0,resY-1,0,p1);
  traceRay (resX-1,resY-1,0,p2);
  traceRay (resX-1,0,0,p3);
  mySquare = new SSquare(0,0,resX-1,resY-1, p0, p1, p2, p3, 0, NULL);
  glDrawBuffer(GL_BACK);
  draw(mySquare);
  for (long y = 1; y <= 5; y++) {
  // Create and draw every region at depth y.
    subdivideToDepth(mySquare, y);
  }
  GLUtilities::swapBuffers();
  glDrawBuffer(GL_FRONT);
  return true;
}

bool wxAdaptiveTracer::nextSquare()
{
  bool retval = false;
  SSquare *cursq = selectSquare(mySquare);
  
  if (cursq) { 
    subdivideSquare(cursq);
    retval = true;
  }
  else
    retval = false;

  return retval;
}

void wxAdaptiveTracer::setRectangle (BoundingRect b)
{ 
  if (myRectmode) {
    myRectmode = false;
    recomputePriority(mySquare);
  }
  
  myRect = b;
  myRectmode = true;
  /* setup current rect */
  recomputePriority(mySquare);
}

void wxAdaptiveTracer::traceRay (int x, int y, int, RGBPixel p)
{
  const Path3D* path = NULL;

  myRay->reset();

  getCamera()->getViewing()->computeRayThrough(x, y, *myRay);

  if (getWorld()->getObjects()->intersect(*myRay) &&
      ((path = myRay->getPath()) != NULL)) {

    //
    // Setup texture context.
    //
    myContext.setIncidencePosition(myRay->getOrigin());
    myContext.setOCS2WCS(path->getLastTransform());
    myContext.setPositionWCS(myRay->getHitPoint());
    myContext.setNormalOCS(myRay->getBestHitObject()->normal(myContext.getPositionOCS()));
    myContext.setColor(Color::getDefault());
    // switch to BOOGA texturing, so that all textures are evaluated
    // without this command, all pixels have default color!!!
    GLTexture::setTexturingType(GLTexture::BOOGA);
    Texture3D::texturing(myContext, path);
    // switch back to GL texturing
    GLTexture::setTexturingType(GLTexture::GL);

    p[0] = myContext.getColor().getRed();
    p[1] = myContext.getColor().getGreen();
    p[2] = myContext.getColor().getBlue();
  } else {
    p[0] = getCamera()->getBackground().getRed();
    p[1] = getCamera()->getBackground().getGreen();
    p[2] = getCamera()->getBackground().getBlue();
  }    
}

void wxAdaptiveTracer::subdivideToDepth(SSquare *sq, int d)
{
	if (sq->getDepth() == d)
          return;
	if (sq->getLeaf())
          subdivideSquare(sq);
	subdivideToDepth(sq->child[0], d);
	subdivideToDepth(sq->child[1], d);
	subdivideToDepth(sq->child[2], d);
	subdivideToDepth(sq->child[3], d);
}

#define RFAC	0.299
#define GFAC	0.587
#define BFAC	0.114
#define INTENSITY(p)	((RFAC*(p)[0] + GFAC*(p)[1] + BFAC*(p)[2])/255.)

void wxAdaptiveTracer::subdivideSquare(SSquare *sq)
{
  int lowx, lowy, midx, midy, hix, hiy;
  int newxsize, newysize, ndepth, supersample;
	/*
	 * Divide the square into fourths by tracing 12
	 * new samples if necessary.
	 */
  Real xsize = sq->getXsize();
  Real ysize = sq->getYsize();

  ostrstream os;
  os << "[wxAdaptiveTracer::subdivideSquare]: sq=" << *sq;

  newxsize = (int) xsize / 2;
  newysize = (int) ysize / 2;
  lowx = (int)sq->getMin()[0]; lowy = (int)sq->getMin()[1];
  midx = (int)(sq->getMin()[0] + newxsize);
  midy = (int)(sq->getMin()[1] + newysize);
  hix  = (int)(sq->getMin()[0] + xsize);
  hiy  = (int)(sq->getMin()[1] + ysize);
  ndepth = sq->getDepth() + 1;
  // create new samples 
  supersample = false;
  RGBPixel p4, p5, p6, p7, p8;
  traceRay(midx, lowy, supersample,p4);
  traceRay(lowx, midy, supersample,p5);
  traceRay(midx, midy, supersample,p6);
  traceRay(hix,  midy, supersample,p7);
  traceRay(midx, hiy, supersample,p8);
#ifdef SHARED_EDGES
  /* create and draw new squares */
  sq->child[0] = new SSquare(lowx,lowy,newxsize,newysize, 
                              *sq->getColor(0), p5, p6, p4, ndepth,sq);
  sq->child[1] = new SSquare(midx, lowy, (int)(sq->getXsize() - newxsize), (int)newysize,
                              p4, p6, p7, *sq->getColor(3), ndepth,sq);
  sq->child[2] = new SSquare(lowx, midy, (int)newxsize, (int)(sq->getYsize() - newysize), 
                              p5, *sq->getColor(1), p8, p6, ndepth,sq);
  sq->child[3] = new SSquare(midx, midy, (int)(sq->getXsize() - newxsize), (int)(sq->getYsize() - newysize), 
                              p6, p8, *sq->getColor(2), p7, ndepth,sq);

  for (register long i=0; i<4; i++)
    draw(sq->child[i]);  
#else
	/*
	 *  draw additional samples in order to subdivide such that
	 * edges of regions do not overlap
	 */
	traceRay(midx+1, lowy, supersample,p);
	traceRay(midx+1, midy, supersample,p);
	traceRay(lowx, midy+1, supersample,p);
	traceRay(midx, midy+1, supersample,p);
	traceRay(midx+1, midy+1, supersample,p);
	traceRay(hix, midy+1, supersample,p);
	traceRay(midx+1, hiy, supersample,p);

    sq->child[0] = createSquare(lowx,lowy, newxsize, newysize , ndepth, sq);
    sq->child[0]->setColor(0, sq->getColor(0));
	
    sq->child[1] = createSquare(midx+1, lowy, sq->getXsize() - newxsize -1,
			newysize, ndepth,sq);
	
	sq->child[2] = createSquare(lowx, midy+1, newxsize,
			sq->getYsize() - newysize-1, ndepth,sq);
	
	sq->child[3] = createSquare(midx+1, midy+1, sq->getXsize() - newxsize-1,
			 sq->getYsize() - newysize-1, ndepth,sq);

#endif
	sq->setLeaf(false);
	/*
	 * Recompute parent's mean and variance.
	 */
	if (overlapsRect(sq))
		recomputeStats(sq);
}

void wxAdaptiveTracer::recomputeStats(SSquare *sq)
{
	Real maxp;
	int in[4];

 	in[0] = overlapsRect(sq->child[0]);
	in[1] = overlapsRect(sq->child[1]);
	in[2] = overlapsRect(sq->child[2]);
	in[3] = overlapsRect(sq->child[3]);

	if ( (in[0] &&  (sq->child[0]->getClosedValue() < SSquare::SSCLOSED)) ||
	     (in[1] &&  (sq->child[1]->getClosedValue() < SSquare::SSCLOSED)) ||
	     (in[2] &&  (sq->child[2]->getClosedValue() < SSquare::SSCLOSED)) ||
	     (in[3] &&  (sq->child[3]->getClosedValue() < SSquare::SSCLOSED))) {
		maxp = 0.;
		if (in[0])
			maxp = max(maxp, sq->child[0]->getPrio());
		if (in[1])
			maxp = max(maxp, sq->child[1]->getPrio());
		if (in[2])
			maxp = max(maxp, sq->child[2]->getPrio());
		if (in[3])
			maxp = max(maxp, sq->child[3]->getPrio());
		sq->setClosedValue(SSquare::NOT_CLOSED);
		sq->setPrio(maxp);
	} else if ((sq->child[0]->getClosedValue() == SSquare::CLOSED_SUPER) &&
		   (sq->child[1]->getClosedValue() == SSquare::CLOSED_SUPER) &&
		   (sq->child[2]->getClosedValue() == SSquare::CLOSED_SUPER) &&
		   (sq->child[3]->getClosedValue() == SSquare::CLOSED_SUPER)) {
		sq->setClosedValue(SSquare::CLOSED_SUPER);
		sq->setPrio(0);
#if 0
	} else if ((!in[0] || sq->child[0]->getClosedValue() >= SSquare::SSCLOSED) &&
		   (!in[1] || sq->child[1]->getClosedValue() >= SSquare::SSCLOSED) &&
		   (!in[2] || sq->child[2]->getClosedValue() >= SSquare::SSCLOSED) &&
		   (!in[3] || sq->child[3]->getClosedValue() >= SSquare::SSCLOSED)) {
		sq->setClosedValue(SSquare::SSCLOSED);
		sq->setPrio(0);
#endif
	} else {
		sq->setClosedValue(SSquare::SSCLOSED);
		sq->setPrio(0);
	}
	if (sq->getParent())
		recomputeStats(sq->getParent());
}

SSquare *wxAdaptiveTracer::selectSquare(SSquare *list)
{
  if (list->getClosedValue()  >= SSquare::SSCLOSED) {
    if (myRectmode) {
      myRectmode = false;
      recomputePriority(mySquare);
      return selectSquare(list);
    }
    return NULL;
  }

//	
//	 Otherwise, find the square with the greatest
//	 'priority'.
//	
  SSquare *res, *which;
  int i;

  res = list;
  while (res && !res->getLeaf()) {
    which = (SSquare *)NULL;
    for (i = 0; i < 4; i++) {
      if ((res->child[i]->getClosedValue() < SSquare::SSCLOSED) && overlapsRect(res->child[i])) {
        which = res->child[i];
        break;
      }
    }
    while (++i < 4) {
      if ((res->child[i]->getClosedValue() < SSquare::SSCLOSED) &&
        which->getPrio() < res->child[i]->getPrio() && overlapsRect(res->child[i]))
        which = res->child[i];
    }
    res = which;
  }
  return res;
}

void wxAdaptiveTracer::draw(SSquare *sq)
{
  if (sq->getArea() >= MINAREA*MINAREA)         
    myPolyBuffer->append(sq);
  else {
    int xsize = (int)(sq->getMax()[0] - sq->getMin()[0]) + 1;
    int ysize = (int)(sq->getMax()[1] - sq->getMin()[1]) + 1;
    
    RGBPixel *p = new RGBPixel[xsize*ysize];
    long position = 0;
    for (register int y = (int)sq->getMin()[1]; y <= (int)sq->getMax()[1]; y++) {
      for (register int x = (int)sq->getMin()[0]; x <= (int)sq->getMax()[0]; x++, position++) 
        traceRay(x, y, 0, p[position]);
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      glRasterPos2d(sq->getMin()[0], sq->getMin()[1]);
      glDrawPixels (xsize, ysize, GL_RGB, GL_FLOAT, p);
    }
    delete p;
    glFlush();  
  }

  if (!sq->getLeaf()) {
    draw(sq->child[0]);
    draw(sq->child[1]);
    draw(sq->child[2]);
    draw(sq->child[3]);
  }
}

bool wxAdaptiveTracer::recomputePriority(SSquare *sq /*,ClosedValue SSCLOSED*/)
{
  if (!overlapsRect(sq)) {
    sq->setClosedValue(SSquare::SSCLOSED);
    return false;
  }

  if (sq->getLeaf()) {
    if (sq->getArea() >= MINAREA*MINAREA)
      sq->setClosedValue(SSquare::NOT_CLOSED);
      return true;
  }
  
  Real maxp = 0.;
  
  if (recomputePriority(sq->child[0]/*,SSCLOSED*/))
    maxp = max(maxp, sq->child[0]->getPrio());
  if (recomputePriority(sq->child[1]/*,SSCLOSED*/))
    maxp = max(maxp, sq->child[1]->getPrio());
  if (recomputePriority(sq->child[2]/*,SSCLOSED*/))
    maxp = max(maxp, sq->child[2]->getPrio());
  if (recomputePriority(sq->child[3]/*,SSCLOSED*/))
    maxp = max(maxp, sq->child[3]->getPrio());
  sq->setPrio(maxp);

  if ((sq->child[0]->getClosedValue() >= SSquare::SSCLOSED) &&
      (sq->child[1]->getClosedValue() >= SSquare::SSCLOSED) &&
      (sq->child[2]->getClosedValue() >= SSquare::SSCLOSED) &&
      (sq->child[3]->getClosedValue() >= SSquare::SSCLOSED))
    sq->setClosedValue(SSquare::SSCLOSED);
  else
    sq->setClosedValue(SSquare::NOT_CLOSED);

  return true;
}

bool wxAdaptiveTracer::overlapsRect(SSquare *s)
{
  if (!myRectmode || 
      (s->getMinX() <= myRect.getMaxX() && 
       s->getMinY() <= myRect.getMaxY() && 
       s->getMaxX() >= myRect.getMinX() && 
       s->getMaxY() >= myRect.getMinY()))
    return true;
  else 
    return false;
}

//-----------------------------------------------------------
// SSQuare
//-----------------------------------------------------------

SSquare::SSquare (int x1, int y1, int xsize, int ysize, RGBPixel p0, RGBPixel p1, RGBPixel p2, RGBPixel p3, int d, SSquare *parent) : BoundingRect()
{
  expand(x1, y1); 
  expand(x1+xsize, y1+ysize);


  myParent = parent;
  myDepth = d;
  
  Real i1 = INTENSITY(p0);
  setColor(0,p0);
  
  Real i2 = INTENSITY(p1);
  setColor(1,p1);

  Real i3 = INTENSITY(p2);
  setColor(2,p2);

  Real i4 = INTENSITY(p3);
  setColor(3,p3);

  setMean(0.25 * (i1+i2+i3+i4));
    
  if (getArea() < MINAREA*MINAREA) {
    myPrio = 0;
    myClosedValue = SSCLOSED;
  } else {
    // compute variance
    Real res, diff;
    diff = i1 - myMean;
    res = diff*diff;
    diff = i2 - myMean;
    res += diff*diff;
    diff = i3 - myMean;
    res += diff*diff;
    diff = i4 - myMean;
    setVar(res + diff*diff);
    myPrio = myVar*getArea();
    myClosedValue = NOT_CLOSED;
  }
  myLeafFlag = true;
  
  for(int i=0; i<4; i++)
   child[i] = NULL;
}

Real SSquare::getArea()
{
  Real xsize = getMax()[0] - getMin()[0];
  Real ysize = getMax()[1] - getMin()[1];
  return ((xsize+1)*(ysize+1));
}

Real SSquare::getXsize()
{
  return getMaxX()-getMinX();
}

Real SSquare::getYsize()
{
  return getMaxY()-getMinY();
}

void SSquare::setLeaf (bool l)
{
  myLeafFlag = l;
}

void SSquare::setMean (Real m)
{
  myMean = m;
}

void SSquare::setPrio (Real p)
{
  myPrio = p;
}

void SSquare::setVar (Real v)
{
  myVar = v;
}

void SSquare::setClosedValue (ClosedValue c)
{
  myClosedValue = c;
}

RGBPixel *SSquare::getColor(int i)
{
  if (i < 0 || i > 3) {
    Report::warning("[wxAdaptiveTracer::getColor]: index out of range");
    return NULL;   
  } else
    return &myColor[i];
}

void SSquare::setColor(int i, RGBPixel p)
{
  if (i < 0 || i > 3) {
    Report::warning("[wxAdaptiveTracer::getColor]: index out of range");
    return;   
  } else
    for (register long j=0; j<3; j++)
      myColor[i][j] = p[j];  
}

SSquare::~SSquare()
{
  for (int i=0; i<4; i++)
    if (child[i])
      delete child[i];
}


GLPolyBuffer::GLPolyBuffer(int resX, int resY, int)
{
  myBufferSize = 50;
  myCurrentElement = 0;
  myCoordinate = NULL;
  myColor = NULL;
  myResX = resX;
  myResY = resY;
}

GLPolyBuffer::~GLPolyBuffer()
{
  if (myColor)
    delete myColor;
    
  if (myCoordinate)
    delete myCoordinate;
}

void GLPolyBuffer::append (SSquare *s)
{
  if (!myCoordinate)
    myCoordinate = new Coordinate[4*myBufferSize];
  if (!myColor)
    myColor = new RGBPixel[4*myBufferSize];
    
  if (myCurrentElement > myBufferSize-1)
    flush();  
  
  myCoordinate[4*myCurrentElement+0][0] = (int)s->getMinX();
  myCoordinate[4*myCurrentElement+0][1] = (int)s->getMinY();
  myCoordinate[4*myCurrentElement+1][0] = (int)s->getMinX();
  myCoordinate[4*myCurrentElement+1][1] = (int)s->getMaxY();
  myCoordinate[4*myCurrentElement+2][0] = (int)s->getMaxX();
  myCoordinate[4*myCurrentElement+2][1] = (int)s->getMaxY();
  myCoordinate[4*myCurrentElement+3][0] = (int)s->getMaxX();
  myCoordinate[4*myCurrentElement+3][1] = (int)s->getMinY();
  
  for (register long i=0; i<3; i++) {
    myColor[4*myCurrentElement+0][i] = (*s->getColor(0))[i];
    myColor[4*myCurrentElement+1][i] = (*s->getColor(1))[i];
    myColor[4*myCurrentElement+2][i] = (*s->getColor(2))[i];
    myColor[4*myCurrentElement+3][i] = (*s->getColor(3))[i];
  }  
//  for (register long i=0; i<3; i++) {
//    myColor[4*myCurrentElement+0][i] = p0[i];
//    myColor[4*myCurrentElement+1][i] = p1[i];
//    myColor[4*myCurrentElement+2][i] = p2[i];
//    myColor[4*myCurrentElement+3][i] = p3[i];
//  }  
  
  myCurrentElement++;
}

void GLPolyBuffer::flush()
{
  //
  // init OpenGL viewing:
  //

  glMatrixMode(GL_PROJECTION);
  //  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, myResX, 0, myResY);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glShadeModel(GL_SMOOTH);
  glViewport(0, 0, myResX, myResY);

  for (int i=0; i<myCurrentElement; i++) {
    glBegin(GL_POLYGON);
    for (register long j=0; j<4; j++) {
      glColor3fv (&myColor[4*i+j][0]);
      glVertex2iv(&myCoordinate[4*i+j][0]);
    }
    
    glEnd();  
  }
  glFlush();
  myCurrentElement = 0;
}
