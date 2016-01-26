/*
 * $RCSfile: PolygonMapper.C,v $
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
 *  $Id: PolygonMapper.C,v 1.8 1998/03/19 15:18:58 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include <math.h>
#include "booga/base/mathutilities.h"
#include "booga/object/Ray3DFactory.h"
#include "booga/object/Ray3DUtilities.h"
#include "booga/object/DirectedLight.h"
#include "booga/object/AmbientLight.h"
#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"
#include "booga/texture/TextureUtilities.h"
#include "booga/texture/PolygonMapper.h"
#include "booga/texture/PolygonMapperAttr.h"

// #define fracabs(x) ((x)<0.0?((x) - (long)(x) + 1):((x) - (long)(x)))

inline Real fracabs(Real x)
{
  return (x<0.0) ? (x - (long)x + 1) : (x - (long)x);
}

//______________________________________________________________________ PolygonMapper

implementRTTI(PolygonMapper, Texture3D);

static const Real aaDistance = 0.01;

PolygonMapper::PolygonMapper() 
{
  myXRatio = 1;
  myYRatio = 1;
  myBeta = 0;
  myPixmap = NULL;
  myAmbient = Color(0,0,0);
  mySpecular = Color(0,0,0);
  mySpecPow = 0;
  myReflectivity = 0;
  myNormal = Vector3D(0,0,0);
  myDisplacement = Vector2D(0,0);
}

PolygonMapper::PolygonMapper(Exemplar) 
{
  myXRatio = 1;
  myYRatio = 1;
  myBeta = 0;
  myPixmap = NULL;
  mySpecular = Color(0,0,0);
  mySpecPow = 0;
  myReflectivity = 0;
  myNormal = Vector3D(0,0,0);
  myDisplacement = Vector2D(0,0);
}

PolygonMapper::PolygonMapper(const PolygonMapper& polyMapper)
{
  myXRatio = polyMapper.myXRatio;
  myYRatio = polyMapper.myYRatio;
  myBeta   = polyMapper.myBeta;

  if (polyMapper.myPixmap != NULL)
    myPixmap = polyMapper.myPixmap->copy();
  else
    myPixmap = NULL;
    
  myAmbient      = polyMapper.myAmbient;
  mySpecular     = polyMapper.mySpecular;
  mySpecPow      = polyMapper.mySpecPow;
  myReflectivity = polyMapper.myReflectivity;
  myPixmapName   = polyMapper.myPixmapName; 
  myNormal       = polyMapper.myNormal;
  myDisplacement = polyMapper.myDisplacement;
}

PolygonMapper::~PolygonMapper()
{
  delete myPixmap;
}

void PolygonMapper::adoptPixmap(AbstractPixmap* pixmap)
{
  //
  // Self assignment?
  //
  if (myPixmap == pixmap)
    return;
    
  delete myPixmap;
  myPixmap = pixmap;
}

Texture3D* PolygonMapper::copy() const
{
  return new PolygonMapper(*this);
}

/*
 * Make sure, Context::setIncidencePosition has been called by 
 * any component that would like to make use of PolygonMapper textures!
 */
void PolygonMapper::doTexturing(Texture3DContext& context) const
{
  Color result(context.getColor()); 
  
  if (myPixmap != NULL){
    Vector3D opos(context.getPositionOCS());
    Vector3D normal(myNormal);
    if (normal.equal(Vector3D(0,0,0)))
      normal = context.getNormalOCS();     
    Vector3D normalLight(context.getNormalWCS());

    Vector3D s = Vector3D (1,0,0);
    Vector3D t = Vector3D (0,1,0);

    if (!normal.zero()) {
	  s = normal*Vector3D(1,0,0);
	  if (s.zero()) 
		  s = normal*Vector3D(0,1,0);
	  t = normal*s;
	}

	Vector2D vec(opos^s,opos^t);

    // scale and rotate the pixmap
	if (equal(myBeta,0)) {
      vec *= myXRatio;
	} else {
	  TransMatrix2D t; t.rotateOrigin(myBeta); t.scale(myXRatio,myYRatio);
      vec = vec*t;
	}

	Real u = vec[0];
	Real v = vec[1];

    // repeat the pixmap
    u = fracabs(u + myDisplacement.x()) * myPixmap->getResolutionX();
    v = fracabs(v + myDisplacement.y()) * myPixmap->getResolutionY();

    // get the pixmap color
    Vector3D colorValue = TextureUtilities::calculateTexelValue(myPixmap,u,v,aaDistance);

    Color ambientIllumination(0,0,0);
    forEachLight(AmbientLight, ambLight) {
      ambLight->getIllumination(context);
      ambientIllumination += context.getIllumination();
    }
    //sdiffuse

    double cosAlphaLight;
    Color directedIllumination(0,0,0);

    forEachLight(DirectedLight, dirLight) {
      dirLight->getDirection(context);
      cosAlphaLight = normalLight ^ context.getLightDirection();
      if ((cosAlphaLight > 0) && dirLight->isVisible(context)) {
        dirLight->getIllumination(context);
        directedIllumination += context.getIllumination() * (float)cosAlphaLight;
      }
    } 
    result = myAmbient*ambientIllumination + Color(colorValue) * directedIllumination;
  
    // Shiny
    if (getReflectivity() > 0.0) {
      // trace
      Vector3D rdir(context.getIncidenceRay()->getDirection());
      Color traceColor = result;
      
      Ray3D* newRay = Ray3DFactory::createSecondaryRay(context.getPositionWCS(), rdir - 2*(rdir^normalLight)*normalLight, context.getIncidenceRay());
      Ray3DUtilities::shadeSecondary(newRay, traceColor, context);
      delete newRay;

      // mix
      result = result * (float)(1-myReflectivity) + traceColor * (float)myReflectivity; 

      // sspecular
      double RV;
      Color specularIllumination(0,0,0);
      Vector3D toView = (context.getIncidencePosition() - 
                     context.getPositionWCS()).normalized();

      forEachLight(DirectedLight, dirLight) {
        dirLight->getDirection(context);
        cosAlphaLight = normalLight ^ context.getLightDirection();
        if ((cosAlphaLight > 0) && dirLight->isVisible(context)) {
          dirLight->getIllumination(context);
          RV = fabs((2*normalLight*cosAlphaLight-context.getLightDirection())^toView);
          specularIllumination += context.getIllumination() * (float)pow((float)RV, (float)mySpecPow);
        }
      }                    
      result +=  mySpecular * specularIllumination; 
 
    }
  }  
  context.setColor(result);
}

Makeable* PolygonMapper::make(RCString& errMsg, const List<Value*>* parameters) const
{
  PolygonMapper* newPolygonMapper = NULL;
  
  if (parameters  == NULL || parameters->count() < 1)
      return new PolygonMapper(*this);

  if ((parameters->count() < 1) || (parameters->count() > 6))
    errMsg = "Wrong number of parameters: pixmap name, [x-ratio [, y-ratio [, beta [, dispacement [, normal]]]]]";   
  else if (parameters->count() == 1) {
    getParameter(1, RCString, filename);
    newPolygonMapper = new PolygonMapper(*this);
    newPolygonMapper->adoptPixmap(ImageReader::createPixmap(filename));
    newPolygonMapper->setPixmapName(filename);
  }
  else if (parameters->count() == 2) {
    getParameter(1, RCString, filename);
    getParameter(2, Real, xratio);
    newPolygonMapper = new PolygonMapper(*this);
    newPolygonMapper->adoptPixmap(ImageReader::createPixmap(filename));
    newPolygonMapper->setPixmapName(filename);
    newPolygonMapper->setXRatio(xratio);
  }
  else if (parameters->count() == 3) {
    getParameter(1, RCString, filename);
    getParameter(2, Real, xratio);
    getParameter(3, Real, yratio);
    newPolygonMapper = new PolygonMapper(*this);
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
    newPolygonMapper = new PolygonMapper(*this);
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
    newPolygonMapper = new PolygonMapper(*this);
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
    newPolygonMapper = new PolygonMapper(*this);
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


int PolygonMapper::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  PolygonMapperAttr* attr = dynamic_cast(PolygonMapperAttr, specifier);
  if (attr != NULL) {
    // The MatteAttr knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute(this);
    delete attr;

    return 1;
  }
    
  // 
  // Let papa do the rest ...
  //
  return Texture3D::setSpecifier(errMsg, specifier);
}

void PolygonMapper::setNormal(const Vector3D& normal)
{
  if (!normal.equal(Vector3D(0,0,0)))
    myNormal = normal.normalized();
  else
    myNormal = Vector3D(0,0,0);
}
 
static const RCString polygonMapperKeyword("polygonmapper");
 
RCString PolygonMapper::getKeyword() const {
  return polygonMapperKeyword;
}
 
List<Value*>* PolygonMapper::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value("\"" + getPixmapName() + "\""));
  parameters->append(new Value(getXRatio()));
  parameters->append(new Value(getYRatio()));
  parameters->append(new Value(rtod(getBeta())));
  parameters->append(new Value(getDisplacement()));
  if (!getNormal().zero())
    parameters->append(new Value(getNormal()));
  return parameters;
}
 
void PolygonMapper::iterateAttributes(MakeableHandler *handler) {
  Texture3D::iterateAttributes(handler);
  if (!equal(getAmbient().brightness(), 0.0)) {
    DummyMakeable ambient("ambient", Value(getAmbient()));
    handler->handle(&ambient);
  }
  if (!equal(getReflectivity(), 0.0)) {
    DummyMakeable reflectivity("reflectivity", Value(getReflectivity()));
    handler->handle(&reflectivity);
  }
  if (!equal(getSpecular().brightness(), 0.0)) {
    DummyMakeable specular("specular", Value(getSpecular()));
    handler->handle(&specular);
    DummyMakeable specpow("specpow", Value(getSpecPow()));
    handler->handle(&specpow);
  }
}
