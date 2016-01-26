/*
 * $RCSfile: MultiObject3D.C,v $
 *
 * Copyright (C) 1997, Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: MultiObject3D.C,v 1.4 1997/09/19 07:14:23 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
#include <sstream>

#include "booga/object/MultiObject3D.h"
#include "booga/object/NullObject3D.h"
#include "booga/object/Shared3D.h"
#include "booga/object/List3D.h"
#include "booga/object/DummyMakeable.h"
#include "booga/object/MakeableHandler.h"

//_______________________________________________________________________ MultiObject3D

implementRTTI(MultiObject3D, Object3D);

MultiObject3D::MultiObject3D()
{
  myDirectionList.removeAll();
  myNumberList.removeAll();
  myMultiObject = NULL;
  mySubject = NULL;
}

MultiObject3D::MultiObject3D(Exemplar exemplar)
: Object3D(exemplar)
{
  myDirectionList.removeAll();
  myNumberList.removeAll();
  myMultiObject = NULL;
  mySubject = NULL;
}

MultiObject3D::~MultiObject3D()
{
  myDirectionList.removeAll();
  myNumberList.removeAll();
  delete myMultiObject;
  delete mySubject;
}

MultiObject3D::MultiObject3D(const MultiObject3D& multiobject)
:Object3D(multiobject),myDirectionList(multiobject.myDirectionList),
 myNumberList(multiobject.myNumberList)
{
  if(multiobject.myMultiObject)
    myMultiObject = multiobject.myMultiObject->copy();
  else
    myMultiObject = NULL;
    
  if(multiobject.mySubject)
    mySubject = multiobject.mySubject->copy();
  else
    mySubject = NULL;
}

Object3D* MultiObject3D::copy() const
{
  return new MultiObject3D(*this);
}

long MultiObject3D::countSubobject() const
{
  return (myMultiObject == NULL) ? 0 : 1;
}

Object3D* MultiObject3D::getSubobject(long index)
{
  if (index != 0)
    Report::error("[MultiObject3D::getSubobject] index out of range");

  return getSubject();
}
 
Object3D* MultiObject3D::makeUnique(Path3D* path, bool shared)
{
  // If we are at the end of the path or path == NULL, don't do anything.
  //
  if (path == NULL || path->isDone())
    return this;

  //
  // If a predecessor is shared more than once, we have to provide a copy
  // of ourself.
  //
  if (shared == true) {
    Object3D* newMultiObject3D = copy();
    path->replace(newMultiObject3D);
    return newMultiObject3D;
  }
  else
    return this;
}

void MultiObject3D::doComputeBounds()
{
  myBounds.expand(getSubject()->getBounds());
}

bool MultiObject3D::doIntersect(Ray3D& ray)
{
  return getSubject()->intersect(ray);
}

int MultiObject3D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  //
  // There might be an object passed, so lets try to cast
  // specifier to Object3D* :
  //
  Object3D* object = dynamic_cast<Object3D*>(specifier);
  if (object != NULL){
    adoptObject(object);
    return 1;
  }

  // 
  // Let papa do the rest ...
  //
  return Object3D::setSpecifier(errMsg, specifier);
}

Object3D* MultiObject3D::getSubject() const
{
  if (mySubject == NULL) {
    // Cache does not affect logical constness
    MultiObject3D* This = (MultiObject3D*)this;
    This->mySubject = createSubject();
  } 
  return mySubject;
}

Makeable* MultiObject3D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  if (parameters == NULL || (parameters->count() % 2) != 0 ){
    errMsg = "Number of parameters is not even";   
    return NULL;
  }
  
  MultiObject3D* newMultiObject = new MultiObject3D(*this);

  newMultiObject->removeDimensions();

  for (int i=1; i<=parameters->count() ; i += 2) {
    getParameter(i, Real, number);
    getParameter(i + 1, Vector3D, direction);
    newMultiObject->addDimension((long)number,direction);
  }
    
  return newMultiObject;

}

void MultiObject3D::addDimension(long number, Vector3D direction)
{
  if (number > 1 && direction.length() > EPSILON){
    myNumberList.append(number);
    myDirectionList.append(direction);
  }
  else {
    std::stringstream os;
    os << "[MultiObject3D::addDimension] parameters "
       <<  number << ", "
       <<  direction << " are not accepted";
    Report::recoverable(os);     
  }
}

void MultiObject3D::removeDimensions()
{
  myNumberList.removeAll();
  myDirectionList.removeAll();
}

static const RCString multiobject3DKeyword("multiobject");

RCString MultiObject3D::getKeyword() const {
  return multiobject3DKeyword;
}

void MultiObject3D::iterateAttributes(MakeableHandler *handler) {
  //
  // add Makeable name "multiobjectName" (if not empty)
  // 
  this->Object3D::iterateAttributes(handler);

  if (!RCString(getName()).isEmpty()) {
    RCString quoteName(RCString("\"") + getName() + RCString("\""));
    Value v(quoteName);
    DummyMakeable m("name", v);
    handler->handle(&m);
  }
  if (myMultiObject)
    handler->handle(myMultiObject);
  
}

List<Value*>* MultiObject3D::createParameters()
{
  List<Value*>* parameters = new List<Value*>;
  for(long i=0; i<myNumberList.count();i++){
    parameters->append(new Value(myNumberList.item(i)));
    parameters->append(new Value(myDirectionList.item(i)));
  }
  return parameters;
}

void MultiObject3D::adoptObject(Object3D* object)
{
  if (object != NULL) {
    if (myMultiObject != NULL)
      delete myMultiObject;
    myMultiObject = object;
  }
}

void MultiObject3D::subjectChanged() const
{
  if (mySubject != NULL) {
    // Cache does not affect logical constness
    MultiObject3D* This = (MultiObject3D*)this;
    delete This->mySubject;
    This->mySubject = NULL;
  } 
}

Object3D* MultiObject3D::createSubject() const
{
  if (myMultiObject){

    Object3D* last = myMultiObject->copy();
    if (!dynamic_cast<Shared3D*>(last))
      last = new Shared3D(last);
    
    Object3D* obj;
    
    for(long i=0;i<myNumberList.count();i++){
      List3D* list = new List3D;
      for(long j=0;j<myNumberList.item(i);j++){
        if (j < myNumberList.item(i) -1)
          obj = last->copy();
        else
          obj = last;
          
        obj->addTransform(TransMatrix3D::makeTranslate(myDirectionList.item(i) * j));
        list->adoptObject(obj);  
      }
      last = new Shared3D(list);
    }
    return last;
  }
  else
    return new NullObject3D();
}
