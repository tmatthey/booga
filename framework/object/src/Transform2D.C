/*
 * Transform2D.C
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
 *  $Id: Transform2D.C,v 1.8 1996/10/04 09:48:45 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Transform2D.h"
#include "booga/object/Transform2DAttr.h"
#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"
//__________________________________________________________________ Transform2D

implementRTTI(Transform2D, ObjectSpecifier);

Transform2D::Transform2D()
{
  myTrans = myInvTrans = NULL;
}

Transform2D::Transform2D(const TransMatrix2D& matrix)
{
  myTrans    = new TransMatrix2D(matrix);
  myInvTrans = NULL;
}

Transform2D::Transform2D(Exemplar)
// : ObjectSpecifier(exemplar) !!!!!!!!!!!!!!!!
{
  myTrans = myInvTrans = NULL;
}

Transform2D::Transform2D(const Transform2D& transform)
{
  if (transform.myTrans != NULL)
    myTrans = new TransMatrix2D(*transform.myTrans);
  else
    myTrans = NULL;

  if (transform.myInvTrans != NULL)
    myInvTrans = new TransMatrix2D(*transform.myInvTrans);
  else
    myInvTrans = NULL;
}

Transform2D::~Transform2D()
{
  delete myTrans;
  delete myInvTrans;
}

Transform2D& Transform2D::operator=(const Transform2D& transform)
{
  if (this == &transform)
    return *this;

  if (transform.myTrans == NULL) {
    delete myTrans;
    myTrans = NULL;
  }
  else {
    if (myTrans == NULL)
      myTrans = new TransMatrix2D(*transform.myTrans);
    else
      (*myTrans) = (*transform.myTrans);
  }

  if (transform.myInvTrans == NULL) {
    delete myInvTrans;
    myInvTrans = NULL;
  } 
  else {
    if (myInvTrans == NULL)
      myInvTrans = new TransMatrix2D(*transform.myInvTrans);
    else
     (*myInvTrans) = (*transform.myInvTrans);
  } 

  return *this;
}

Transform2D& Transform2D::operator*=(const Transform2D& transform)
{
  if (transform.myTrans == NULL)
    return *this;

  addTransMatrix(*transform.myTrans);

  return *this;
}

Transform2D Transform2D::operator*(const Transform2D& transform) const
{
  return Transform2D(getTransMatrix() * transform.getTransMatrix());
}

int Transform2D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  // First check if specifier is of type Transform2D (nestet or named 
  // transformations)
  Transform2D* anotherTrans = dynamic_cast(Transform2D, specifier);
  if (anotherTrans != NULL)
    addTransMatrix(*(anotherTrans->myTrans));
  else {
    castSpecifier(Transform2DAttr, trans, "transformation attribute");

    // The Transform2DAttr knows best which method has to be called.
    // So let the object do the job.
    trans->setAttribute(this);
  }

  delete specifier;
  return 1;
}

Makeable* Transform2D::make(RCString& errMsg, 
			    const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new Transform2D(*this);
}

void Transform2D::addTransform(const Transform2D& transform)
{
  if (transform.myTrans != NULL)
    addTransMatrix(*transform.myTrans);
}

void Transform2D::addTransMatrix(const TransMatrix2D& tm)
{
  if (myTrans == NULL)
    myTrans = new TransMatrix2D(tm);
  else 
    *myTrans *= tm;

  //
  // Inverse is no longer valid.
  //
  delete myInvTrans;
  myInvTrans = NULL;
}

const TransMatrix2D& Transform2D::getTransMatrix() const
{
  if (myTrans == NULL)
    return TransMatrix2D::getIdentity();
  else
    return *myTrans;
}

const TransMatrix2D& Transform2D::getInvTransMatrix() const
{
  if (myInvTrans != NULL)
    return *myInvTrans;   

  if (myTrans == NULL)
    return TransMatrix2D::getIdentity();
  else {
    buildInverse();
    return *myInvTrans;
  }
}

Vector2D Transform2D::transformAsPoint(const Vector2D& vec) const
{
  if (myTrans == NULL)
    return vec;
  else
    return ::transformAsPoint(vec, *myTrans);
}

Vector2D Transform2D::transformAsVector(const Vector2D& vec) const
{
  if (myTrans == NULL)
    return vec;
  else
    return ::transformAsVector(vec, *myTrans);
}

Vector2D Transform2D::invTransformAsPoint(const Vector2D& vec) const
{
  if (myTrans == NULL)
    return vec;
  else
    return ::transformAsPoint(vec, getInvTransMatrix());
}

Vector2D Transform2D::invTransformAsVector(const Vector2D& vec) const
{
 if (myTrans == NULL)
    return vec;
  else
    return ::transformAsVector(vec, getInvTransMatrix());
}

void Transform2D::buildInverse() const
{
  //
  // This method alters the *internal* state of the object only ->
  // Locical const-ness of 'this' is casted away.
  //
  Transform2D* This = (Transform2D*) this;

  This->myInvTrans = new TransMatrix2D(*myTrans);

  //
  // Singular matrix ?
  //
  if (!This->myInvTrans->invert())
    Report::error("[Transform2D::buildInverse] singular matrix specified." 
		    "Cannot compute inverse");
}

static const RCString transform2DKeyword("transform");

RCString Transform2D::getKeyword() const {
  return transform2DKeyword;
}

void Transform2D::iterateAttributes(MakeableHandler *handler) {
  TransMatrix2D temp = getTransMatrix();
  temp.translate(-temp(2,0), -temp(2,1));
  if (temp == TransMatrix2D::getIdentity()) {
    DummyMakeable translate("translate", Value(Vector2D(
      getTransMatrix()(2,0),
      getTransMatrix()(2,1)
    )));
    handler->handle(&translate);
  }
  else {
    DummyMakeable matrix("matrix", Value(getTransMatrix()));
    handler->handle(&matrix);
  }
}
