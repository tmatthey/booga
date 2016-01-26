/*
 * Transform3D.h
 *
 * Objects of class Transform3D are used as a specifier for Object3D instances.
 *
 * Copyright (C) 1995, Christoph Streit <streit@iam.unibe.ch>
 *                     Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: Transform3D.h,v 1.8 1996/10/04 09:48:48 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Transform3D_H
# define _Transform3D_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/TransMatrix3D.h"
#include "booga/object/ObjectSpecifier.h"

//__________________________________________________________________ Transform3D

class Transform3D : public ObjectSpecifier {
declareRTTI(Transform3D);
// enable RTTI support

public:
  Transform3D();
  Transform3D(const TransMatrix3D& matrix);
  Transform3D(Exemplar);
  Transform3D(const Transform3D& transform);
  ~Transform3D();

  Transform3D& operator=(const Transform3D& transform);
  Transform3D& operator=(const TransMatrix3D& transform);
  Transform3D& operator*=(const Transform3D& transform);
  Transform3D& operator*=(const TransMatrix3D& transform);
  
  Transform3D operator*(const Transform3D& transform) const;
  Transform3D operator*(const TransMatrix3D& transform) const;

  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;

  void addTransform(const Transform3D& transform);
  void addTransMatrix(const TransMatrix3D& tm);
  const TransMatrix3D& getTransMatrix() const;
  const TransMatrix3D& getInvTransMatrix() const;

  bool isIdentity() const;

  Vector3D transformAsPoint(const Vector3D& vec)  const;
  Vector3D transformAsVector(const Vector3D& vec) const;
  Vector3D transformAsNormal(const Vector3D& vec) const;

  Vector3D invTransformAsPoint(const Vector3D& vec)  const;
  Vector3D invTransformAsVector(const Vector3D& vec) const;
  Vector3D invTransformAsNormal(const Vector3D& vec) const;

private:
  void buildInverse() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
  virtual RCString getKeyword() const;
  virtual void iterateAttributes(MakeableHandler *handler);

private:
  TransMatrix3D* myTrans;
  TransMatrix3D* myInvTrans;
};

//______________________________________________________________________ INLINES

inline bool Transform3D::isIdentity() const
{
  return (myTrans == NULL);
}

#endif // _Transform3D_H
