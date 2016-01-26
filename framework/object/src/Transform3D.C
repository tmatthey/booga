/*
 * Transform3D.C
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
 *  $Id: Transform3D.C,v 1.11 1998/03/31 07:55:51 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Transform3D.h"
#include "booga/object/Transform3DAttr.h"
#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"
//__________________________________________________________________ Transform3D

implementRTTI(Transform3D, ObjectSpecifier);

Transform3D::Transform3D()
{
  myTrans = myInvTrans = NULL;
}

Transform3D::Transform3D(const TransMatrix3D& matrix)
{
  myTrans    = new TransMatrix3D(matrix);
  myInvTrans = NULL;
}

Transform3D::Transform3D(Exemplar)
// : ObjectSpecifier(exemplar) !!!!!!!!!!!!!!!!
{
  myTrans = myInvTrans = NULL;
}

Transform3D::Transform3D(const Transform3D& transform)
{
  if (transform.myTrans != NULL)
    myTrans = new TransMatrix3D(*transform.myTrans);
  else
    myTrans = NULL;

  if (transform.myInvTrans != NULL)
    myInvTrans = new TransMatrix3D(*transform.myInvTrans);
  else
    myInvTrans = NULL;
}

Transform3D::~Transform3D()
{
  delete myTrans;
  delete myInvTrans;
}

Transform3D& Transform3D::operator=(const Transform3D& transform)
{
  if (this == &transform)
    return *this;

  if (transform.myTrans == NULL) {
    delete myTrans;
    myTrans = NULL;
  }
  else {
    if (myTrans == NULL)
      myTrans = new TransMatrix3D(*transform.myTrans);
    else
      (*myTrans) = (*transform.myTrans);
  }

  if (transform.myInvTrans == NULL) {
    delete myInvTrans;
    myInvTrans = NULL;
  } 
  else {
    if (myInvTrans == NULL)
      myInvTrans = new TransMatrix3D(*transform.myInvTrans);
    else
     (*myInvTrans) = (*transform.myInvTrans);
  } 

  return *this;
}

Transform3D& Transform3D::operator=(const TransMatrix3D& transform)
{
  if (this->myTrans == &transform)
    return *this;
  
  if (this->myInvTrans == &transform) {
    if (myTrans)
      delete myTrans;
    myTrans = myInvTrans;
    myInvTrans = NULL;
    return *this;
  }
  
  if (myTrans == NULL)
    myTrans = new TransMatrix3D(transform);
  else
    (*myTrans) = transform;

  if (myInvTrans != NULL)
    delete myInvTrans;

  return *this;
}

Transform3D& Transform3D::operator*=(const Transform3D& transform)
{
  if (transform.myTrans == NULL)
    return *this;

  addTransMatrix(*transform.myTrans);

  return *this;
}

Transform3D& Transform3D::operator*=(const TransMatrix3D& transform)
{
  addTransMatrix(transform);
  return *this;
}

Transform3D Transform3D::operator*(const Transform3D& transform) const
{
  return Transform3D(getTransMatrix() * transform.getTransMatrix());
}

Transform3D Transform3D::operator*(const TransMatrix3D& transform) const
{
  return Transform3D(getTransMatrix() * transform);
}

int Transform3D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  // First check if specifier is of type Transform3D (nestet or named 
  // transformations)
  Transform3D* anotherTrans = dynamic_cast(Transform3D, specifier);
  if (anotherTrans != NULL)
    addTransMatrix(*(anotherTrans->myTrans));
  else {
    castSpecifier(Transform3DAttr, trans, "transformation attribute");

    // The Transform3DAttr knows best which method has to be called.
    // So let the object do the job.
    trans->setAttribute(this);
  }

  delete specifier;
  return 1;
}

Makeable* Transform3D::make(RCString& errMsg, 
			    const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new Transform3D(*this);
}

void Transform3D::addTransform(const Transform3D& transform)
{
  if (transform.myTrans != NULL)
    addTransMatrix(*transform.myTrans);
}

void Transform3D::addTransMatrix(const TransMatrix3D& tm)
{
  if (myTrans == NULL)
    myTrans = new TransMatrix3D(tm);
  else 
    *myTrans *= tm;

  //
  // Inverse is no longer valid.
  //
  //!!!!!! when removing this, Cylinder3D can update canonocalTransform without error. !!!///
  if(myInvTrans)
    delete myInvTrans;

  myInvTrans = NULL;
}

const TransMatrix3D& Transform3D::getTransMatrix() const
{
  if (myTrans == NULL)
    return TransMatrix3D::getIdentity();
  else
    return *myTrans;
}

const TransMatrix3D& Transform3D::getInvTransMatrix() const
{
  if (myInvTrans != NULL)
    return *myInvTrans;   

  if (myTrans == NULL)
    return TransMatrix3D::getIdentity();
  else {
    buildInverse();
    return *myInvTrans;
  }
}

Vector3D Transform3D::transformAsPoint(const Vector3D& vec) const
{
  if (myTrans == NULL)
    return vec;
  else
    return ::transformAsPoint(vec, *myTrans);
}

Vector3D Transform3D::transformAsVector(const Vector3D& vec) const
{
  if (myTrans == NULL)
    return vec;
  else
    return ::transformAsVector(vec, *myTrans);
}

Vector3D Transform3D::transformAsNormal(const Vector3D& vec) const
{
  if (myTrans == NULL)
    return vec;
  else
    return ::transformAsNormal(vec, getInvTransMatrix());
}

Vector3D Transform3D::invTransformAsPoint(const Vector3D& vec) const
{
  if (myTrans == NULL)
    return vec;
  else
    return ::transformAsPoint(vec, getInvTransMatrix());
}

Vector3D Transform3D::invTransformAsVector(const Vector3D& vec) const
{
 if (myTrans == NULL)
    return vec;
  else
    return ::transformAsVector(vec, getInvTransMatrix());
}

Vector3D Transform3D::invTransformAsNormal(const Vector3D& vec) const
{
  if (myTrans == NULL)
    return vec;
  else
    return ::transformAsNormal(vec, *myTrans);
}

void Transform3D::buildInverse() const
{
  //
  // This method alters the *internal* state of the object only ->
  // Locical const-ness of 'this' is casted away.
  //
  Transform3D* This = (Transform3D*) this;

  This->myInvTrans = new TransMatrix3D(*myTrans);

  //
  // Singular matrix ?
  //
  if (!This->myInvTrans->invert())
    Report::warning("[Transform3D::buildInverse] singular matrix specified." 
		  " Cannot compute inverse");
}

static const RCString transform3DKeyword("transform");

RCString Transform3D::getKeyword() const {
  return transform3DKeyword;
}

void Transform3D::iterateAttributes(MakeableHandler *handler) {
  TransMatrix3D temp = getTransMatrix();
  temp.translate(-temp(3,0), -temp(3,1), -temp(3,2));
  if (temp == TransMatrix3D::getIdentity()) {
    DummyMakeable translate("translate", Value(Vector3D(
      getTransMatrix()(3,0),
      getTransMatrix()(3,1),
      getTransMatrix()(3,2)
    )));
    handler->handle(&translate);
  }
  else {
    DummyMakeable matrix("matrix", Value(getTransMatrix()));
    handler->handle(&matrix);
  }
}
