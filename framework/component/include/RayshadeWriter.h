/*
 * $RCSfile: RayshadeWriter.h,v $
 *
 * Copyright (C) 1994-96, Bernhard Buehlmann <buhlmann@iam.unibe.ch>
 *                        Andrey Collison <collison@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: RayshadeWriter.h,v 1.11 1996/09/13 08:06:13 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _RayshadeWriter_H
#define _RayshadeWriter_H

#include <fstream.h>
#include "booga/base/Value.h"
#include "booga/base/RCString.h"
#include "booga/component/Operation3D.h"

class Texture3D;
class Object3D;
class Animation3D;
class Grid3D;
class List3D;
class Shared3D;
class Camera3D;
class AmbientLight;
class PointLight;
class Box3D;
class Cone3D;
class Cylinder3D;
class Disc3D;
class Polygon3D;
class Sphere3D;
class Text3D;
class Torus3D;
class Triangle3D;

//_______________________________________________________________ RayshadeWriter

class RayshadeWriter : public Operation3D {
declareRTTI(RayshadeWriter);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  RayshadeWriter(const RCString& filename = "");

private:
  RayshadeWriter(const RayshadeWriter&);             // No copies.

public:
  virtual ~RayshadeWriter();                

private:
  RayshadeWriter& operator=(const RayshadeWriter&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class RayshadeWriter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void adoptCamera(Camera3D* camera);
  // Set camera to use for rendering
  void deleteCamera();
  const Camera3D* getCamera() const;

private:
  Traversal::Result visit(Object3D* object);
  Traversal::Result visit(Animation3D* anim);
  Traversal::Result visit(Grid3D* aggr);
  Traversal::Result visit(List3D* aggr);
  Traversal::Result visit(Shared3D* shared);
  Traversal::Result visit(Camera3D* camera);
  Traversal::Result visit(AmbientLight* light);
  Traversal::Result visit(PointLight* light);
  Traversal::Result visit(Box3D* box);
  Traversal::Result visit(Cone3D* obj);
  Traversal::Result visit(Cylinder3D* cylinder);
  Traversal::Result visit(Disc3D* disc);
  Traversal::Result visit(Polygon3D* poly);
  Traversal::Result visit(Sphere3D* sphere);
  Traversal::Result visit(Text3D* text);
  Traversal::Result visit(Torus3D* obj);
  Traversal::Result visit(Triangle3D* triangle);

private:
  void printObject3DAttributes(Object3D* obj);
  void printParameterList(List<Value>* parList);
  void printTransform(const TransMatrix3D& mat);
  void printTextureDefinition(const Texture3D* texture);
  void printTextureName(const Texture3D* texture);
  void printVector(const Vector3D& v);
  void printCamera(const Camera3D* v);
  void incIndent();
  void decIndent();
  void newLineIndent();

  virtual List<Value>* getParameterList(Object3D* object);
  virtual List<Value>* getParameterList(Grid3D* aggr);
  virtual List<Value>* getParameterList(List3D* aggr);
  virtual List<Value>* getParameterList(Shared3D* shared);
  virtual List<Value>* getParameterList(Camera3D* camera);
  virtual List<Value>* getParameterList(AmbientLight* light);
  virtual List<Value>* getParameterList(PointLight* light);
  virtual List<Value>* getParameterList(Box3D* box);
  virtual List<Value>* getParameterList(Cone3D* obj);
  virtual List<Value>* getParameterList(Cylinder3D* cylinder);
  virtual List<Value>* getParameterList(Disc3D* disc);
  virtual List<Value>* getParameterList(Polygon3D* poly);
  virtual List<Value>* getParameterList(Sphere3D* sphere);
  virtual List<Value>* getParameterList(Text3D* text);
  virtual List<Value>* getParameterList(Torus3D* obj);
  virtual List<Value>* getParameterList(Triangle3D* triangle);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool preprocessing();
  virtual bool doExecute();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Visitor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Traversal::Result dispatch(Makeable* obj);

  virtual void incLevel();
  virtual void decLevel();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  int myLevel;
  int myWriteDefLevel;  // write definitions for shareds < myWriteDefLevel
  int mySkipLevel;      // skip levels < mySkipLevel
  int myIndent;         // indent levels in text output
  RCString myFilename;
  ofstream myOs;
  Camera3D* myCamera; 
  bool myHasAdoptedCamera;
};

//______________________________________________________________________ INLINES

#endif // _RayshadeWriter_H

