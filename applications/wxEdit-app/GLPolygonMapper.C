/*
 * $RCSfile: GLPolygonMapper.C,v $
 *
 * Copyright (C) 1996, Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: GLPolygonMapper.C,v 1.2 1997/02/20 09:42:00 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include <math.h>
#include "booga/base/mathutilities.h"
#include "booga/base/Value.h"
#include "GLPolygonMapper.h"

#include <GL/gl.h>
#include <GL/glu.h>

//______________________________________________________________________ GLPolygonMapper

implementRTTI(GLPolygonMapper, PolygonMapper);

GLPolygonMapper::GLPolygonMapper() : PolygonMapper() 
{
  myPixels = NULL;
}

GLPolygonMapper::GLPolygonMapper(Exemplar e) : PolygonMapper(e)
{
  myPixels = NULL;
}

GLPolygonMapper::~GLPolygonMapper()
{
  delete myPixels;
}

Texture3D* GLPolygonMapper::copy() const
{
  return new GLPolygonMapper(*this);
}

void GLPolygonMapper::doTexturing(Texture3DContext&) const
{
//  Report::warning ("[GLPolygonMapper::doTexturing]");
    
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, getPixmap()->getResolutionX(),
                    getPixmap()->getResolutionY(), GL_RGB, GL_FLOAT, myPixels);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glEnable(GL_TEXTURE_2D);
}

Makeable* GLPolygonMapper::make(RCString& errMsg, const List<Value*>* parameters) const
{
  GLPolygonMapper* newGLPolygonMapper = NULL;

  if ((parameters->count() < 1) || (parameters->count() > 4))
    errMsg = "Wrong number of parameters: pixmap name, [x-ratio [, y-ratio [, beta]]]";   
  else if (parameters->count() == 1) {
    getParameter(1, RCString, filename);
    newGLPolygonMapper = new GLPolygonMapper(*this);
    newGLPolygonMapper->adoptPixmap(ImageReader::createPixmap(filename));
  }
  else if (parameters->count() == 2) {
    getParameter(1, RCString, filename);
    getParameter(2, Real, xratio);
    newGLPolygonMapper = new GLPolygonMapper(*this);
    newGLPolygonMapper->adoptPixmap(ImageReader::createPixmap(filename));
    newGLPolygonMapper->setXRatio(xratio);
  }
  else if (parameters->count() == 3) {
    getParameter(1, RCString, filename);
    getParameter(2, Real, xratio);
    getParameter(3, Real, yratio);
    newGLPolygonMapper = new GLPolygonMapper(*this);
    newGLPolygonMapper->adoptPixmap(ImageReader::createPixmap(filename));
    newGLPolygonMapper->setXRatio(xratio);
    newGLPolygonMapper->setYRatio(yratio);
 }
  else {
    getParameter(1, RCString, filename);
    getParameter(2, Real, xratio);
    getParameter(3, Real, yratio);
    getParameter(4, Real, beta);
    newGLPolygonMapper = new GLPolygonMapper(*this);
    newGLPolygonMapper->adoptPixmap(ImageReader::createPixmap(filename));
    newGLPolygonMapper->setXRatio(xratio);
    newGLPolygonMapper->setYRatio(yratio);
    newGLPolygonMapper->setBeta(dtor(beta));    
  }
  
  // initialize my pixels;
  int resX = newGLPolygonMapper->getPixmap()->getResolutionX();
  int resY = newGLPolygonMapper->getPixmap()->getResolutionY();
  float *p = new float[resX*resY* 3];
  for (long i=0, pos=0; i<resX*resY*3; i+=3, pos++) {
      newGLPolygonMapper->getPixmap()->setPosition(pos);
      newGLPolygonMapper->getPixmap()->getColor(p[i+0],p[i+1],p[i+2]);
  }        
  newGLPolygonMapper->adoptPixels (p);
  return newGLPolygonMapper;
}

void GLPolygonMapper::adoptPixels (float *p)
{
  if (myPixels)
    delete [] myPixels;
    
  myPixels = p;
}
