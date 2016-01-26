/*
 * $RCSfile: ShowNormals.h,v $
 *
 * This component decomposes the object in the world into triangles, and 
 * adds small cones representing the normals for each triangle vertex
 * to the world. 
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
 *  $Id: ShowNormals.h,v 1.4 1996/09/13 08:06:27 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShowNormals_H
#define _ShowNormals_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/component/Operation3D.h"

class Texture3D;
class Triangle3D;
class List3D;

//__________________________________________________________________ ShowNormals

class ShowNormals : public Operation3D {
declareRTTI(PrintWorld3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  ShowNormals();
private:
  ShowNormals(const ShowNormals&);	           // No copies.

public:
  virtual ~ShowNormals();

private:
  ShowNormals& operator=(const ShowNormals&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class ShowNormals
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:  
  void adoptTexture(Texture3D* texture);
  // Provide the texture that has to be used for the created cylinders.

  void computeNormalSize(bool flag);
  void setNormalLength(Real length);
  void setNormalWidth(Real width);

private:
  Traversal::Result visit(Triangle3D* obj);
    
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool doExecute();
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Visitor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Traversal::Result dispatch(Makeable* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  List3D* myNormalContainer;
  Texture3D* myNormalTexture;
  
  bool myComputeNormalSize;
  Real myNormalLength;
  Real myNormalWidth;
};

//______________________________________________________________________ INLINES

inline void ShowNormals::computeNormalSize(bool flag)
{
  myComputeNormalSize = flag;
}

inline void ShowNormals::setNormalLength(Real length)
{
  myNormalLength = length;
}

inline void ShowNormals::setNormalWidth(Real width)
{
  myNormalWidth = width;
}

#endif // _ShowNormals_H
