/*
 * $RCSfile: Morph3D.C,v $
 *
 * Copyright (C) 1995-96, Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: Morph3D.C,v 1.1 1996/11/18 15:43:26 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <strstream.h>
#include "booga/base/mathutilities.h"
#include "booga/base/Report.h"
#include "booga/base/Value.h"
#include "booga/base/TransMatrix3D.h"
#include "booga/base/Vector2D.h"
#include "booga/base/Vector3D.h"
#include "booga/base/ListUtilities.h"
#include "booga/object/List3D.h"
#include "booga/object/Aggregate3D.h"
#include "booga/object/NullObject3D.h"
#include "booga/object/DummyMakeable.h"
#include "booga/object/MakeableHandler.h"
#include "booga/texture/Matte.h"
#include "booga/texture/Phong.h"
#include "booga/texture/Whitted.h"
#include "booga/animation/ActionInfo.h"
#include "booga/animation/Morph3D.h"

// ____________________________________________________________________ Morph3D

implementRTTI(Morph3D, Animation3D);

Morph3D::Morph3D(Exemplar)
{
  myLastFactor = 0.0;
  myFrom = NULL;
  myTo = NULL;
}

Morph3D::Morph3D()
{
  myLastFactor = 0.0;
  myFrom = NULL;
  myTo = NULL;
}

Morph3D::Morph3D(const Morph3D& morph)
: Animation3D(morph)
{
  myLastFactor = morph.myLastFactor;

  if (morph.myFrom != NULL)
    myFrom = morph.myFrom->copy();
  else
    myFrom = NULL;

  if (morph.myTo != NULL)
    myTo = morph.myTo->copy();
  else
    myTo = NULL;


}
Morph3D::~Morph3D()
{
  if(myFrom != NULL)
    delete myFrom;
  if(myTo != NULL)
    delete myTo;
}

long Morph3D::countSubobject() const
{
  return (myFrom == NULL && myTo == NULL) ? 0 : 1;
}

Object3D* Morph3D::getSubobject(long index) 
{
  if (index != 0)
    Report::error("[Morph3D::getSubobject] index out of range");

  if(myAnimatedObjects == NULL)
    doFrame(myLastFactor);

  return myAnimatedObjects;
}

Object3D* Morph3D::doInterpolate(Real ticks, Object3D* from, Object3D* to)
{
  Real ticksInv = 1 - ticks;
  RCString err("Morph3D::doInterpolate");

  Object3D* obj = NULL;
  List<Value*>* fromList = NULL;
  List<Value*>* toList = NULL;

  if(from != NULL)
    fromList = from->createParameters();

  if(to != NULL)
    toList = to->createParameters();

  if (to == NULL || from == NULL){
    if(from != NULL){
      obj = dynamic_cast (Object3D,from->make(err, fromList));
      if(from->getTexture() != NULL)
	obj->appendTexture(from->getTexture()->copy());
      obj->setTransform(from->getTransform());
    }
    else if(to != NULL){
      obj = dynamic_cast (Object3D,to->make(err, toList));
      if(to->getTexture() != NULL)
	obj->appendTexture(to->getTexture()->copy());
      obj->setTransform(to->getTransform());
    }
    else {
      obj = new NullObject3D();
    }
  }
  // The interpolation
  else{
    if(equal(ticks,0)){
      obj = dynamic_cast (Object3D,from->make(err, fromList));
      if(from->getTexture() != NULL)
	obj->appendTexture(from->getTexture()->copy());
      obj->setTransform(from->getTransform());
    }
    else if(equal(ticks,1)){
      obj = dynamic_cast (Object3D,to->make(err, toList));
      if(to->getTexture() != NULL)
	obj->appendTexture(to->getTexture()->copy());
      obj->setTransform(to->getTransform());
    }
    else {
      List<Value*>* valueList = new List<Value*>;

      if(toList->count() != fromList->count()){
	if(ticks < 0.5){
	  obj = dynamic_cast (Object3D,from->make(err, fromList));
	  if(from->getTexture() != NULL)
	    obj->appendTexture(from->getTexture()->copy());
	}
	else{
	  obj = dynamic_cast (Object3D,to->make(err, toList));
	  if(to->getTexture() != NULL)
	    obj->appendTexture(to->getTexture()->copy());
	}
      }
      else {

	Vector3D v3D1;
	Vector3D v3D2;
	Vector2D v2D1;
	Vector2D v2D2;
	Real     x1;
	Real     x2;

	ticksInv = 1-ticks;
	for (long i=0; i<fromList->count(); i++){
	  // Interpolate the parameters
	  if(fromList->item(i)->toVector3D(v3D1)>0){
	    if(toList->item(i)->toVector3D(v3D2)>0)
	      valueList->append (new Value (ticks*v3D2+ticksInv*v3D1));
	    else
	      valueList->append (new Value (*fromList->item(i)));	    
	  }
	  else if(fromList->item(i)->toVector2D(v2D1)>0){
	    if(toList->item(i)->toVector2D(v2D2)>0)
	      valueList->append (new Value (ticks*v2D2+ticksInv*v2D1));
	    else
	      valueList->append (new Value (*fromList->item(i)));	    
	  }
	  else if(fromList->item(i)->toReal(x1)>0){
	    if(toList->item(i)->toReal(x2)>0)
	      valueList->append (new Value (ticks*x2+ticksInv*x1));
	    else
	      valueList->append (new Value (*fromList->item(i)));	    
	  }
	  else {
	    valueList->append (new Value (*fromList->item(i)));	
	  }
	}

	// Make an object with the interpolated parameters
	if (ticks < 0.5)
	  obj = dynamic_cast (Object3D,from->make(err, valueList));
	else
	  obj = dynamic_cast (Object3D,to->make(err, valueList));

	if(obj == NULL)
	  obj = new NullObject3D();
	else {
	  // Interpolate the local transformation
	  TransMatrix3D t1 = from->getTransform().getTransMatrix();
	  TransMatrix3D t2 = to->getTransform().getTransMatrix();

	  Vector3D v0 =Vector3D(t1(0,0)*ticksInv+t2(0,0)*ticks,
				t1(0,1)*ticksInv+t2(0,1)*ticks,
				t1(0,2)*ticksInv+t2(0,2)*ticks);
	  Vector3D v1 =Vector3D(t1(1,0)*ticksInv+t2(1,0)*ticks,
				t1(1,1)*ticksInv+t2(1,1)*ticks,
				t1(1,2)*ticksInv+t2(1,2)*ticks);
	  Vector3D v2 =Vector3D(t1(2,0)*ticksInv+t2(2,0)*ticks,
				t1(2,1)*ticksInv+t2(2,1)*ticks,
				t1(2,2)*ticksInv+t2(2,2)*ticks);
	  Vector3D v3 =Vector3D(t1(3,0)*ticksInv+t2(3,0)*ticks,
				t1(3,1)*ticksInv+t2(3,1)*ticks,
				t1(3,2)*ticksInv+t2(3,2)*ticks);
	  TransMatrix3D t3(v0,v1,v2,v3);
	  obj->setTransform(t3);

	  // Interpolate the colors/textures
	  Texture3D* fromTexture = (Texture3D*)from->getTexture();
	  Texture3D* toTexture = (Texture3D*)to->getTexture();
	  Texture3D* newTexture = NULL;
	  Matte* fromMatte = NULL;
	  Matte* toMatte = NULL;
	  Phong* fromPhong = NULL;
	  Phong* toPhong = NULL;
	  Whitted* fromWhitted = NULL;
	  Whitted* toWhitted = NULL;
	  Vector3D v;
	  List<Value*>* tmpList = new List<Value*>;

	  if(fromTexture != NULL && toTexture != NULL){
	    if(fromTexture->getKeyword() == toTexture->getKeyword()){
	      // Matte
	      if((fromMatte = dynamic_cast(Matte,fromTexture)) != NULL){
		toMatte = dynamic_cast(Matte,toTexture);
		Matte* newMatte = dynamic_cast(Matte,toMatte->make(err, tmpList));
		v = ticksInv*(Vector3D)(fromMatte->getAmbient())+ticks*(Vector3D)(toMatte->getAmbient());
		newMatte->setAmbient(v);
		v = ticksInv*(Vector3D)(fromMatte->getDiffuse())+ticks*(Vector3D)(toMatte->getDiffuse());
		newMatte->setDiffuse(v);
		newTexture = newMatte;
	      }
	      // Phong
	      else if((fromPhong = dynamic_cast(Phong,fromTexture)) != NULL){
		toPhong = dynamic_cast(Phong,toTexture);
		Phong* newPhong = dynamic_cast(Phong,toPhong->make(err, tmpList));
		v = ticksInv*(Vector3D)(fromPhong->getAmbient())+ticks*(Vector3D)(toPhong->getAmbient());
		newPhong->setAmbient(v);
		v = ticksInv*(Vector3D)(fromPhong->getDiffuse())+ticks*(Vector3D)(toPhong->getDiffuse());
		newPhong->setDiffuse(v);
		v = ticksInv*(Vector3D)(fromPhong->getSpecular())+ticks*(Vector3D)(toPhong->getSpecular());
		newPhong->setSpecular(v);
		newPhong->setSpecPow((int)(ticksInv*(Real)(fromPhong->getSpecPow())+ticks*(Real)(toPhong->getSpecPow())));
		newTexture = newPhong;
	      }
	      // Whitted
	      else if((fromWhitted = dynamic_cast(Whitted,fromTexture)) != NULL){
		toWhitted = dynamic_cast(Whitted,toTexture);
		Whitted* newWhitted = dynamic_cast(Whitted,toWhitted->make(err, tmpList));
		v = ticksInv*(Vector3D)(fromWhitted->getAmbient())+ticks*(Vector3D)(toWhitted->getAmbient());
		newWhitted->setAmbient(v);
		v = ticksInv*(Vector3D)(fromWhitted->getDiffuse())+ticks*(Vector3D)(toWhitted->getDiffuse());
		newWhitted->setDiffuse(v);
		newWhitted->setTransparency(ticksInv*fromWhitted->getTransparency()+ticks*toWhitted->getTransparency());
		newWhitted->setReflectivity(ticksInv*fromWhitted->getReflectivity()+ticks*toWhitted->getReflectivity());
		newWhitted->setRefractionIndex(ticksInv*fromWhitted->getRefractionIndex()+ticks*toWhitted->getRefractionIndex());
		newTexture = newWhitted;
	      }
	    }
	  }
	  else if(fromTexture != NULL)
	    newTexture = fromTexture->copy();
	  else if(toTexture != NULL)
	    newTexture = toTexture->copy();

	  if(newTexture != NULL){
	    delete obj->orphanTexture();
	    obj->appendTexture(newTexture);
	  }
	  
	  delete tmpList;
	}
      }
      
      if(valueList != NULL)
	deleteList(valueList);
    }
  }
  
  if(fromList != NULL)
    deleteList(fromList);
  if(toList != NULL)
    deleteList(toList);

  return obj;
}

bool Morph3D::doFrame(Real frame)
{
  Real ticks = 0;

  for(long i = 0; i < myActionList.count() ; i++){
    ActionInfo* item = myActionList.item(i);
    if (item->isMorph()) {
      ticks += item->computeTicks(frame)*item->getAlpha();
    }
    else {
      ostrstream os;
      os << "[Morph3D::doFrame] action ("
         <<  item->getStartFrame() << ","
         <<  item->getEndFrame() << ") not of type Morph3D. Skip";
      Report::recoverable(os);          
    }
  }
  

  if (ticks > 1)
    ticks = 1;
  if (ticks < 0)
    ticks = 0;

  if (myTo == NULL || myFrom == NULL)
    ticks = 0;

  if (equal(myLastFactor,ticks) && myAnimatedObjects != NULL)
    return false;

  Object3D* obj;

  if (dynamic_cast(Primitive3D,myFrom) != NULL){
    obj = doInterpolate(ticks, myFrom, myTo);
  }
  else {

    Aggregate3D* agg = dynamic_cast(Aggregate3D,doInterpolate(ticks, myFrom, myTo));
    Aggregate3D* from = dynamic_cast(Aggregate3D,myFrom);
    Aggregate3D* to = dynamic_cast(Aggregate3D,myTo);
      
    for(int i=0;(i < from->countSubobject() || i < to->countSubobject());i++){
      if(i >= from->countSubobject())
	agg->adoptObject(doInterpolate(ticks, NULL, to->getSubobject(i)));
      else if(i >= to->countSubobject())
	agg->adoptObject(doInterpolate(ticks, from->getSubobject(i), NULL));
      else
	agg->adoptObject(doInterpolate(ticks, from->getSubobject(i), to->getSubobject(i)));
    }
    obj = agg;
  }
  
  myLastFactor = ticks;
  if (myAnimatedObjects != NULL)
    delete myAnimatedObjects;
  myAnimatedObjects = obj;

  return true;  

}

Object3D* Morph3D::copy() const
{
  return new Morph3D(*this);
}

Makeable* Morph3D::make(RCString&, const List<Value*>* ) const
{
  Morph3D* newMorph = new Morph3D(*this);

  return newMorph;
}

static const RCString MorphKeyword("morph");

RCString Morph3D::getKeyword() const 
{
  return MorphKeyword;
}

void Morph3D::iterateAttributes(MakeableHandler *handler)
{
  Object3D::iterateAttributes(handler);
  for(long i=0; i<myActionList.count(); i++)
    handler->handle(myActionList.item(i));
  
  if (myTo != NULL)
      handler->handle(myTo);
  if (myFrom != NULL)
      handler->handle(myFrom);

}

int Morph3D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  //
  // There might be an object passed, so lets try to cast
  // specifier to Object3D* :
  //
  // Take two Primitive3D of the same class or an aggregate.
  //
  Aggregate3D* agg = dynamic_cast(Aggregate3D, specifier);
  if (agg != NULL) {
    if (myFrom == NULL){
      myFrom = agg;
      return 1;
    }
    else if (myTo == NULL){
      myTo = agg;
      return 1;
    }
  }
  Primitive3D* object = dynamic_cast(Primitive3D, specifier);
  if (object != NULL) {
    if (myFrom == NULL){
      myFrom = object;
      return 1;
    }
    else if (myTo == NULL && myFrom->getKeyword()==object->getKeyword()){
      myTo = object;
      return 1;
    }
  }

  // 
  // Let papa do the rest ...
  //
  return Animation3D::setSpecifier(errMsg, specifier);
}


