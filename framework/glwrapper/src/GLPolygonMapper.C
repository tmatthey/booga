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
#include "booga/base/Configuration.h"
#include "booga/base/PixmapOf.h"
#include "booga/base/ColorTypes.h"

#include "booga/texture/PolygonMapper.h"

#include "booga/glwrapper/GLPolygonMapper.h"

#include <GL/gl.h>
#include <GL/glu.h>

//______________________________________________________________________ GLPolygonMapper

implementRTTI(GLPolygonMapper, PolygonMapper);

GLPolygonMapper::GLPolygonMapper() : PolygonMapper() 
{
  myGLList = 0;
}

GLPolygonMapper::GLPolygonMapper(Exemplar e) : PolygonMapper(e)
{
  myGLList = 0;
}

GLPolygonMapper::GLPolygonMapper(const GLPolygonMapper& polyMapper) : PolygonMapper(polyMapper)
{
  myGLList = 0;
}

GLPolygonMapper::~GLPolygonMapper()
{
  if(myGLList)
    glDeleteLists(myGLList,1);
}

Texture3D* GLPolygonMapper::copy() const
{
  return new GLPolygonMapper(*this);
}

void GLPolygonMapper::doTexturing(Texture3DContext& context) const
{
  // Report::warning ("[GLPolygonMapper::doTexturing]");

  if (!getPixmap()){	// we have no pixmap
    // Report::warning ("[GLPolygonMapper::doTexturing] no pixmap");
    return;
  }

  if (GLTexture::ourTexturingType == GLTexture::BOOGA) {
    PolygonMapper::doTexturing(context);
    return;
  }

#ifdef HAVE_OPENGL

  if (!myGLList) {
	GLuint l = glGenLists(1);
	GLuint *l1 = (GLuint *) &myGLList;
	*l1 = l;
	glNewList(myGLList, GL_COMPILE_AND_EXECUTE);

	PixmapOf<RGB> *pix = (PixmapOf<RGB> *)getPixmap();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, getPixmap()->getResolutionX(),
                    getPixmap()->getResolutionY(), GL_RGB, GL_FLOAT, pix->getColors());
//                    getPixmap()->getResolutionY(), GL_RGB, GL_UNSIGNED_BYTE, (GLubyte *)pix->getColors());
//    glTexImage2D(GL_TEXTURE_2D, 0, 3, getPixmap()->getResolutionX(),
//                    getPixmap()->getResolutionY(), 0, GL_RGB, GL_FLOAT, 
//myPixels);
  
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glEndList();

  } else
   glCallList(myGLList);

  glEnable(GL_TEXTURE_2D);

  glMatrixMode(GL_TEXTURE);
  glPushMatrix();
  glTranslatef(getDisplacement()[0], getDisplacement()[1], 0); // apply translation
  glScalef(getXRatio(), getYRatio(), 1);
  glRotatef (rtod(getBeta())-90, 0,0,1); // apply rotation
  glMatrixMode(GL_MODELVIEW);
  
  Vector3D s = Vector3D (1,0,0);
  Vector3D t = Vector3D (0,1,0);

  if (!getNormal().zero()) {
    s = getNormal()*Vector3D(1,0,0);
    if (s.zero()) 
      s = getNormal()*Vector3D(0,1,0);
    t = getNormal()*s;
  }

  GLfloat sMapping[4] = { s[0], s[1], s[2], 0 };   
  GLfloat tMapping[4] = { t[0], t[1], t[2], 0 };   

  glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
  glTexGenfv(GL_S, GL_OBJECT_PLANE, sMapping);
  glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
  glTexGenfv(GL_T, GL_OBJECT_PLANE, tMapping);
  glEnable(GL_TEXTURE_GEN_S);
  glEnable(GL_TEXTURE_GEN_T);

#endif
}

Makeable* GLPolygonMapper::make(RCString& errMsg, const List<Value*>* parameters) const
{
  GLPolygonMapper* newPolygonMapper = NULL;
  // we set the default pixmap type to RGBchar

//  Configuration::setOption(Name("Pixmap.Type"),Name("RGBchar"));
  
  if (parameters  == NULL || parameters->count() < 1)
      return new PolygonMapper(*this);

  if ((parameters->count() < 1) || (parameters->count() > 6))
    errMsg = "Wrong number of parameters: pixmap name, [x-ratio [, y-ratio [, beta [, dispacement [, normal]]]]]";   
  else if (parameters->count() == 1) {
    getParameter(1, RCString, filename);
    newPolygonMapper = new GLPolygonMapper(*this);
    newPolygonMapper->adoptPixmap(ImageReader::createPixmap(filename));
    newPolygonMapper->setPixmapName(filename);
  }
  else if (parameters->count() == 2) {
    getParameter(1, RCString, filename);
    getParameter(2, Real, xratio);
    newPolygonMapper = new GLPolygonMapper(*this);
    newPolygonMapper->adoptPixmap(ImageReader::createPixmap(filename));
    newPolygonMapper->setPixmapName(filename);
    newPolygonMapper->setXRatio(xratio);
  }
  else if (parameters->count() == 3) {
    getParameter(1, RCString, filename);
    getParameter(2, Real, xratio);
    getParameter(3, Real, yratio);
    newPolygonMapper = new GLPolygonMapper(*this);
    newPolygonMapper->adoptPixmap(ImageReader::createPixmap(filename));
    newPolygonMapper->setPixmapName(filename);
    newPolygonMapper->setXRatio(xratio);
    newPolygonMapper->setYRatio(yratio);
  }
  else if (parameters->count() == 4) {
    getParameter(1, RCString, filename);
    getParameter(2, Real, xratio);
    getParameter(3, Real, yratio);
    getParameter(4, Real, beta);
    newPolygonMapper = new GLPolygonMapper(*this);
    newPolygonMapper->setPixmapName(filename); 
    newPolygonMapper->adoptPixmap(ImageReader::createPixmap(filename));
    newPolygonMapper->setXRatio(xratio);
    newPolygonMapper->setYRatio(yratio);
    newPolygonMapper->setBeta(dtor(beta));    
  }
  else if (parameters->count() == 5) {
    getParameter(1, RCString, filename);
    getParameter(2, Real, xratio);
    getParameter(3, Real, yratio);
    getParameter(4, Real, beta);
    getParameter(5, Vector2D, displacement);
    newPolygonMapper = new GLPolygonMapper(*this);
    newPolygonMapper->adoptPixmap(ImageReader::createPixmap(filename));
    newPolygonMapper->setPixmapName(filename);
    newPolygonMapper->setXRatio(xratio);
    newPolygonMapper->setYRatio(yratio);
    newPolygonMapper->setBeta(dtor(beta));    
    newPolygonMapper->setDisplacement(displacement);    
  }
  else {
    getParameter(1, RCString, filename);
    getParameter(2, Real, xratio);
    getParameter(3, Real, yratio);
    getParameter(4, Real, beta);
    getParameter(5, Vector2D, displacement);
    getParameter(6, Vector3D, normal);
    newPolygonMapper = new GLPolygonMapper(*this);
    newPolygonMapper->adoptPixmap(ImageReader::createPixmap(filename));
    newPolygonMapper->setPixmapName(filename);
    newPolygonMapper->setXRatio(xratio);
    newPolygonMapper->setYRatio(yratio);
    newPolygonMapper->setBeta(dtor(beta));    
    newPolygonMapper->setDisplacement(displacement);    
    newPolygonMapper->setNormal(normal);    
  }
  
  return newPolygonMapper;
}

void GLPolygonMapper::adoptPixmap(AbstractPixmap* pixmap)
{
  if(myGLList)
    glDeleteLists(myGLList,1);
  myGLList = 0;

  PolygonMapper::adoptPixmap(pixmap);
}
