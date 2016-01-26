/*
 * Transform2D.h
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
 *  $Id: Transform2D.h,v 1.8 1996/10/04 09:48:46 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Transform2D_H
# define _Transform2D_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/object/ObjectSpecifier.h"
#include "booga/base/TransMatrix2D.h"

//__________________________________________________________________ Transform2D

class Transform2D : public ObjectSpecifier {
  declareRTTI(Transform2D);
// enable RTTI support

public:
  Transform2D();
  Transform2D(const TransMatrix2D& matrix);
  Transform2D(Exemplar);
  Transform2D(const Transform2D& transform);
  ~Transform2D();

  Transform2D& operator=(const Transform2D& transform);
  Transform2D& operator*=(const Transform2D& transform);
  
  Transform2D operator*(const Transform2D& transform) const;

  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;

  void addTransform(const Transform2D& transform);
  void addTransMatrix(const TransMatrix2D& tm);
  const TransMatrix2D& getTransMatrix() const;
  const TransMatrix2D& getInvTransMatrix() const;

  bool isIdentity() const;

  Vector2D transformAsPoint(const Vector2D& vec)  const;
  Vector2D transformAsVector(const Vector2D& vec) const;

  Vector2D invTransformAsPoint(const Vector2D& vec)  const;
  Vector2D invTransformAsVector(const Vector2D& vec) const;

private:
  void buildInverse() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
public:
  virtual RCString getKeyword() const;
  virtual void iterateAttributes(MakeableHandler *handler);

private:
  TransMatrix2D* myTrans;
  TransMatrix2D* myInvTrans;
};

//______________________________________________________________________ INLINES

inline bool Transform2D::isIdentity() const
{
  return (myTrans == NULL);
}

#endif // _Transform2D_H
