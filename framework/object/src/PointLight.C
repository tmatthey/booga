/*
 * $RCSfile: PointLight.C,v $
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: PointLight.C,v 1.23 1997/10/30 09:38:14 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
  
#include "booga/base/Deleter.h"   
#include "booga/object/Ray3D.h"
#include "booga/object/Ray3DFactory.h"   
#include "booga/object/Sphere3D.h"
#include "booga/object/Aggregate3D.h"
#include "booga/object/World3D.h"
#include "booga/object/PointLight.h"
#include "booga/object/PointLightAttr.h"
#include "booga/object/DummyMakeable.h"
#include "booga/object/MakeableHandler.h"

//___________________________________________________________________ PointLight

implementRTTI(PointLight, DirectedLight);

PointLight::PointLight(Exemplar exemplar)
: DirectedLight(exemplar)
{
  myLightRep = new Sphere3D(1, Vector3D(0,0,0));
} 

PointLight::PointLight(Real luminance, const Color& color)
: DirectedLight(luminance, color)
{
  myLightRep = new Sphere3D(1, Vector3D(0,0,0));
}

void PointLight::setRadius(Real radius)
{
  dynamic_cast<Sphere3D*>(myLightRep)->setRadius(radius);
}

void PointLight::setPosition(const Vector3D& position)
{
  dynamic_cast<Sphere3D*>(myLightRep)->setCenter(position);
}

void PointLight::getDirection(Texture3DContext& context) const
{
  // !!!!!!!!! Transformation der Lichtquelle beruecksichtigen
  Vector3D toLight = dynamic_cast<Sphere3D*>(myLightRep)->getCenter() -
                     context.getPositionWCS();
  Real dist = toLight.normalize();
  context.setLightDirection(toLight);
  context.setLightDistance(dist);
}

bool PointLight::isVisible(Texture3DContext& context) const
{
  // !!!!!!!!! Transformation der Lichtquelle beruecksichtigen
  Vector3D origin(dynamic_cast<Sphere3D*>(myLightRep)->getCenter());
  Real radius = dynamic_cast<Sphere3D*>(myLightRep)->getRadius();

  //
  // Inside light source? Really?
  //
  if (context.getPositionWCS().distance(origin) <= radius) {
    Report::debug("[PointLight::isVisible] inside light source");
    return true;    
  }

  Vector3D direction(context.getPositionWCS()-origin);
  Deleter<Ray3D> ray(Ray3DFactory::createRay(origin, direction));
  ray->setTolerance(radius*1.01);  // we should start outside the sphere !!! (98.07.16/tm)
  
  if (context.getWorld()->getObjects()->intersect(ray)) {

    //
    // Same hit point => nothing in between.
    // This case is usally true, if using raytcasting as a HSD 
    // (hidden surface determination) algorithmn.
    //
    // Maybe we hit an object which is behind us due to numeric problems! (98.07.22/tm)
    //

    // if (ray->getHitPoint()).equal(context.getPositionWCS())
    if (direction.length() <= ((ray->getHitPoint()-origin).length() + EPSILON))
      return true;
    else 
      return false;


//
// The idea was good, but it doesn't work! (5.9.96/cs)
//
//    //
//    // We hit the primitive requesting the visibility test.
//    // This usally holds true, if using a scan conversion method 
//    // (e.g. z-buffer) for HSD calculations. In this case the hit point
//    // determined by the scan conversion process is surely not the same, as
//    // the one computed by shooting a ray during the visibility calculations.
//    //
//    else if (ray->getBestHitObject() == context.getObject())
//      return true;
//    //
//    // Third case:
//    // The above case doesn't hold true, if a decomposed primitive is beeing
//    // scan converted, e.g. :
//    //    Scan converting a sphere will first decompose the sphere into a 
//    //    triangle mesh. Each triangle is scan converted seperately. The ray
//    //    shooted in this method will hit the sphere and not the triangle 
//    //    currently beeing scan converted...
//    // So, we have to check if the "ray->getBestHitObject()" can be found on 
//    // the path to the current object.
//    //
//    else {
//      const List<Object3D*>& objects = context.getPath()->getObjects();
//      
//      for (long i=objects.count()-1; i>=0; i--) {
//        if (ray->getBestHitObject() == objects.item(i))
//          return true;
//      }
//
//      // 
//      // There has to be an object inbetween!      
//      //
//      return false;
//    }
  } else {
    // Should really not happen !

    //Report::warning("[PointLight::isVisible] gulp: ray must have been mixed up");
    //return false;

    //
    // numeric problems !!!
    // but if we do not hit anything then nothing is between (98.07.22/tm) !!!
    // 
    return true;
  }
}

Object3D* PointLight::copy() const
{
  return new PointLight(*this);
}

int PointLight::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  PointLightAttr* attr = dynamic_cast<PointLightAttr*>(specifier);
  if (attr != NULL) {
    // The PointLightAttr object knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute(this);

    delete attr;
    return 1;  
  }

  // 
  // Let papa do the rest ...
  //
  return DirectedLight::setSpecifier(errMsg, specifier);
}

static const RCString pointLightKeyword("pointLight");

RCString PointLight::getKeyword() const {
  return pointLightKeyword;
}

void PointLight::iterateAttributes(MakeableHandler *handler) {
  LightSource::iterateAttributes(handler);
  DummyMakeable m1("position",Value(getPosition()));
  handler->handle(&m1);
  DummyMakeable m2("radius",Value(getRadius()));
  handler->handle(&m2);
}
