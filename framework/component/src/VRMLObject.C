/*
 * $RCSfile: VRMLObject.C,v $ 
 *
 * Copyright (C) 1996, Beat Liechti <liechti@isbe.ch>
 *                     Ingenieurschule Bern, Switzerland
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
 *  $Id: VRMLObject.C,v 1.7 1998/02/04 12:48:46 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/List.h"
#include "booga/base/Name.h"
#include "booga/base/RCString.h"
#include "booga/base/ScopedName.h"

#include "booga/object/Camera3D.h"
#include "booga/object/Cone3D.h"
#include "booga/object/Cylinder3D.h"
#include "booga/object/Disc3D.h"
#include "booga/object/GeneralLight.h"
#include "booga/object/List3D.h"
#include "booga/object/Object3D.h"
#include "booga/object/OrthographicViewing3D.h"
#include "booga/object/PointLight.h"
#include "booga/object/Polygon3D.h"
#include "booga/object/Triangle3D.h"
#include "booga/object/PerspectiveViewing3D.h"
#include "booga/object/Sphere3D.h"

#include "booga/texture/Phong.h"

#include "VRMLObject.h"

//___________________________________________________________________ VRMLObject

VRMLObject::VRMLObject() 
{}  

VRMLObject::~VRMLObject() 
{}

//___________________________________________________________________ VRMLList

VRMLList::VRMLList() 
{
  myData = new sData;
  myData->ourRefCount = 0;
}

VRMLList::VRMLList(const VRMLList& aList) 
{
  myData = aList.myData;
  myData->ourRefCount++;
}

VRMLList::~VRMLList() 
{
  if (myData->ourRefCount)
    myData->ourRefCount--;
  else
  {
    for (int i = 0; i < myData->ourList.count(); i++)
      delete myData->ourList.item(i);
    myData->ourList.removeAll();
    delete myData;
  }
}

void VRMLList::add(VRMLObject& vrmlObject)
{
  myData->ourList.append(vrmlObject.copy());
}

void VRMLList::reset()
{ 
  //
  // empty list, keep myData
  //
  for (int i = 0; i < myData->ourList.count(); i++)
    delete myData->ourList.item(i);
  myData->ourList.removeAll();
}

void VRMLList::apply(Stack<VRMLState*> &stack)
{ 
  for (int i = 0; i < myData->ourList.count(); i++)
    myData->ourList.item(i)->apply(stack);
}

VRMLObject* VRMLList::copy() 
{ 
  return new VRMLList(*this);
}

//___________________________________________________________________ VRMLMatrixTransform

void VRMLMatrixTransform::setMatrix(const TransMatrix3D& matrix) 
{ 
  myMatrix = matrix; 
}

void VRMLMatrixTransform::reset() 
{ 
  myMatrix.identity(); 
}

void VRMLMatrixTransform::apply(VRMLState &state) 
{ 
  //state.getTransMatrix() *= myMatrix; 
  state.getTransMatrix() = myMatrix * state.getTransMatrix();    
}

void VRMLMatrixTransform::apply(Stack<VRMLState*> &stack) 
{ 
  apply(*stack.top()); 
}

VRMLObject* VRMLMatrixTransform::copy() 
{ 
  return new VRMLMatrixTransform(*this); 
}

//___________________________________________________________________ VRMLRotation

void VRMLRotation::apply(VRMLState &state) 
{ 
  //state.getTransMatrix() *= myRotation; 
  state.getTransMatrix() = myRotation * state.getTransMatrix();  
}

void VRMLRotation::setRotation(const TransMatrix3D& rotation)
{ 
  myRotation = rotation; 
}

void VRMLRotation::reset() 
{ 
  myRotation.identity(); 
}

void VRMLRotation::apply(Stack<VRMLState*> &stack) 
{ 
  apply(*stack.top()); 
}

VRMLObject* VRMLRotation::copy() 
{ 
  return new VRMLRotation(*this); 
}

//___________________________________________________________________ VRMLTransform

void VRMLTransform::apply(VRMLState& state) 
{
  state.getTransMatrix() = TransMatrix3D::makeTranslate(myTranslation) * state.getTransMatrix();
  state.getTransMatrix() = TransMatrix3D::makeTranslate(myCenter) * state.getTransMatrix();
  state.getTransMatrix() = myRotation * state.getTransMatrix();
  state.getTransMatrix() = myScaleOrientation * state.getTransMatrix();
  state.getTransMatrix() = TransMatrix3D::makeScale(myScaleFactor) * state.getTransMatrix();
  state.getTransMatrix() = myScaleOrientationInvert * state.getTransMatrix();
  state.getTransMatrix() = TransMatrix3D::makeTranslate(-myCenter) * state.getTransMatrix();
}    

void VRMLTransform::setTranslation(const Vector3D& translation) 
{ 
  myTranslation = translation; 
}

void VRMLTransform::setRotation(const TransMatrix3D& rotation) 
{ 
  myRotation = rotation; 
}

void VRMLTransform::setScaleFactor(const Vector3D& scaleFactor) 
{ 
  myScaleFactor = scaleFactor; 
}

void VRMLTransform::setScaleOrientation(const TransMatrix3D& scaleOrientation) 
{ 
  myScaleOrientation = scaleOrientation;
  myScaleOrientationInvert = scaleOrientation;
  myScaleOrientationInvert.invert();
}

void VRMLTransform::setCenter(Vector3D& center) 
{ 
  myCenter = center; 
}

void VRMLTransform::reset() 
{  
  myTranslation = Vector3D(0,0,0);
  myRotation = TransMatrix3D::makeRotate(Vector3D(0,0,1),0);
  myScaleFactor = Vector3D(1,1,1);
  myScaleOrientation = TransMatrix3D::makeRotate(Vector3D(0,0,1),0);
  myScaleOrientationInvert = TransMatrix3D::makeRotate(Vector3D(0,0,1),0);
  myScaleOrientationInvert.invert();
  myCenter = Vector3D(0,0,0);         
}

void VRMLTransform::apply(Stack<VRMLState*> &stack) 
{ 
  apply(*stack.top()); 
}    

VRMLObject* VRMLTransform::copy() 
{ 
  return new VRMLTransform(*this); 
}

//___________________________________________________________________ VRMLTranslation

void VRMLTranslation::apply(VRMLState& state)
{ 
  //state.getTransMatrix().translate(myTranslation); 

  TransMatrix3D transMatrix; 
  
  transMatrix.translate(myTranslation);
  state.getTransMatrix() = transMatrix * state.getTransMatrix();  
}

void VRMLTranslation::setTranslation(const Vector3D& translation) 
{ 
  myTranslation = translation; 
}

void VRMLTranslation::reset() 
{ 
  myTranslation = Vector3D(0,0,0); 
}    

void VRMLTranslation::apply(Stack<VRMLState*> &stack) 
{ 
  apply(*stack.top()); 
}    

VRMLObject* VRMLTranslation::copy() 
{ 
  return new VRMLTranslation(*this); 
}

//___________________________________________________________________ VRMLScale

void VRMLScale::apply(VRMLState& state) 
{  
  //state.getTransMatrix().scale(myScaleFactor); 
  TransMatrix3D transMatrix;
  transMatrix.scale(myScaleFactor);
  state.getTransMatrix() = transMatrix * state.getTransMatrix();  
}

void VRMLScale::setScaleFactor(const Vector3D& scaleFactor) 
{ 
  myScaleFactor = scaleFactor; 
}

void VRMLScale::reset() 
{ 
  myScaleFactor = Vector3D(1,1,1); 
}     

void VRMLScale::apply(Stack<VRMLState*> &stack) 
{ 
  apply(*stack.top()); 
}

VRMLObject* VRMLScale::copy() 
{ 
  return new VRMLScale(*this); 
}

//___________________________________________________________________ VRMLOrthographicCamera

void VRMLOrthographicCamera::apply(VRMLState& state)
{
  Vector3D dir(transformAsVector(Vector3D(0,0,-myFocalDistance), myOrientation));
  Vector3D up(transformAsVector(Vector3D(0,1,0), myOrientation));		    
      
  OrthographicViewing3D *orthographicViewing3D = new OrthographicViewing3D;
  orthographicViewing3D->setEye(myPosition);
  orthographicViewing3D->setLookat(myPosition+dir);
  orthographicViewing3D->setUp(up);			    
  orthographicViewing3D->setVFov(2.0*atan((myHeight/2.0)/myFocalDistance));
      
  Camera3D* camera3D = new Camera3D();
  camera3D->adoptViewing(orthographicViewing3D);
  state.getObjects().adoptObject(camera3D);
}

void VRMLOrthographicCamera::setPosition(const Vector3D& position) 
{ 
  myPosition = position; 
}

void VRMLOrthographicCamera::setOrientation(const TransMatrix3D& orientation) 
{ 
  myOrientation = orientation; 
}

void VRMLOrthographicCamera::setFocalDistance(double focalDistance)
{
  myFocalDistance = focalDistance; 
}

void VRMLOrthographicCamera::setHeight(double height) 
{
  myHeight = height; 
}

void VRMLOrthographicCamera::reset() 
{
  myPosition = Vector3D(0,0,1);
  myOrientation = TransMatrix3D::makeRotate(Vector3D(0,0,1),0);
  myFocalDistance = 5;
  myHeight = 2;
}

void VRMLOrthographicCamera::apply(Stack<VRMLState*> &stack) 
{
  apply(*stack.top()); 
}    

VRMLObject* VRMLOrthographicCamera::copy() 
{
  return new VRMLOrthographicCamera(*this); 
}

//___________________________________________________________________ VRMLPerspectiveCamera

void VRMLPerspectiveCamera::apply(VRMLState& state)
{
  Vector3D dir(transformAsVector(Vector3D(0,0,-myFocalDistance), myOrientation));
  Vector3D up(transformAsVector(Vector3D(0,1,0), myOrientation));		    

  PerspectiveViewing3D *perspectiveViewing3D = new PerspectiveViewing3D;
  perspectiveViewing3D->setEye(myPosition);
  perspectiveViewing3D->setLookat(myPosition+dir);
  perspectiveViewing3D->setUp(up);			    
  perspectiveViewing3D->setVFov(myHeightAngle);
      
  Camera3D* camera3D = new Camera3D();
  camera3D->adoptViewing(perspectiveViewing3D);
            
  state.getObjects().adoptObject(camera3D);
}

void VRMLPerspectiveCamera::setPosition(const Vector3D& position) 
{ 
  myPosition = position; 
}

void VRMLPerspectiveCamera::setOrientation(const TransMatrix3D& orientation) 
{ 
  myOrientation = orientation; 
}

void VRMLPerspectiveCamera::setFocalDistance(double focalDistance)
{
   myFocalDistance = focalDistance; 
}

void VRMLPerspectiveCamera::setHeightAngle(double heightAngle) 
{ 
  myHeightAngle = heightAngle; 
}

void VRMLPerspectiveCamera::reset() 
{
  myPosition = Vector3D(0,0,1);
  myOrientation = TransMatrix3D::makeRotate(Vector3D(0,0,1),0);
  myFocalDistance = 5;
  myHeightAngle = 0.785398;
}

void VRMLPerspectiveCamera::apply(Stack<VRMLState*> &stack) 
{ 
  apply(*stack.top()); 
}    

VRMLObject* VRMLPerspectiveCamera::copy() 
{ 
  return new VRMLPerspectiveCamera(*this); 
}

//___________________________________________________________________ VRMLDirectionalLight

void VRMLDirectionalLight::apply(VRMLState& state)
{
  PointLight *pointLight = new PointLight;
  myOn ? pointLight->turnOn() : pointLight->turnOff();
  pointLight->setColor(myColor);
  pointLight->setPosition(myLocation); 
  pointLight->setLuminance(myIntensity);
  pointLight->setRadius(100000); /* very big */
  state.getObjects().adoptObject(pointLight);
}

void VRMLDirectionalLight::setOn(bool on) 
{ 
  myOn = on; 
}

void VRMLDirectionalLight::setIntensity(double intensity) 
{ 
  myIntensity = intensity; 
}

void VRMLDirectionalLight::setColor(const Color& color) 
{ 
  myColor = color; 
}

void VRMLDirectionalLight::setDirection(const Vector3D& direction) 
{ 
  myLocation = direction; 
  myLocation *= -100000; /* far away */
}

bool VRMLDirectionalLight::getOn() 
{
  return myOn; 
}

void VRMLDirectionalLight::reset()
{
  myOn = true;
  myIntensity = 1;
  myColor = Color(1,1,1);
  myLocation = Vector3D(0,100000,0); /* far away */
}

void VRMLDirectionalLight::apply(Stack<VRMLState*> &stack) 
{
  apply(*stack.top()); 
}    

VRMLObject* VRMLDirectionalLight::copy()
{
  return new VRMLDirectionalLight(*this); 
}

//___________________________________________________________________ VRMLPointLight

void VRMLPointLight::apply(VRMLState& state)
{
  PointLight *pointLight = new PointLight;
  myOn ? pointLight->turnOn() : pointLight->turnOff();
  pointLight->setColor(myColor);
  pointLight->setPosition(myLocation); 
  pointLight->setLuminance(myIntensity);      
  state.getObjects().adoptObject(pointLight);
}

void VRMLPointLight::setOn(bool on) 
{
  myOn = on; 
}

void VRMLPointLight::setIntensity(double intensity) 
{ 
  myIntensity = intensity; 
}

void VRMLPointLight::setColor(const Color& color)
{ 
  myColor = color; 
}

void VRMLPointLight::setLocation(const Vector3D& location) 
{
  myLocation = location; 
}

bool VRMLPointLight::getOn() 
{ 
  return myOn; 
}

void VRMLPointLight::reset() 
{
  myOn = true;
  myIntensity = 1;
  myColor = Color(1,1,1);
  myLocation = Vector3D(0,1,0);
}

void VRMLPointLight::apply(Stack<VRMLState*> &stack) 
{
  apply(*stack.top()); 
}     

VRMLObject* VRMLPointLight::copy() 
{ 
  return new VRMLPointLight(*this); 
}

//___________________________________________________________________ VRMLSpotLight

void VRMLSpotLight::apply(VRMLState& state)
{
  PointLight *pointLight = new PointLight;
  myOn ? pointLight->turnOn() : pointLight->turnOff();
  pointLight->setColor(myColor);
  pointLight->setPosition(myLocation); 
  pointLight->setLuminance(myIntensity);
  state.getObjects().adoptObject(pointLight);
}

void VRMLSpotLight::setOn(bool on) 
{ 
  myOn = on; 
}

void VRMLSpotLight::setIntensity(double intensity)
{ 
  myIntensity = intensity; 
}

void VRMLSpotLight::setColor(const Color& color)
{ 
  myColor = color; 
}

void VRMLSpotLight::setLocation(const Vector3D& location)
{ 
  myLocation = location; 
}

void VRMLSpotLight::setDirection(const Vector3D& direction)
{
  myDirection = direction; 
}

bool VRMLSpotLight::getOn() 
{ 
  return myOn; 
}

void VRMLSpotLight::reset() 
{
  myOn = true;
  myIntensity = 1;
  myColor = Color(1,1,1);
  myLocation = Vector3D(0,1,0); 
  myDirection = Vector3D(0,-1,0); 
}

void VRMLSpotLight::apply(Stack<VRMLState*> &stack) 
{ 
  apply(*stack.top()); 
}

VRMLObject* VRMLSpotLight::copy() 
{ 
  return new VRMLSpotLight(*this); 
}

//___________________________________________________________________ VRMLCone

void VRMLCone::addMaterial(VRMLState& state, Object3D* object3D, int matIndex)
{
  if (state.getMaterial().count())
  {
    if (state.getMaterialBinding() == VRML_PER_PART 
	|| state.getMaterialBinding() == VRML_PER_PART_INDEXED)
      matIndex %= state.getMaterial().count();
    else
      matIndex = 0;

      object3D->appendTexture(state.getMaterial().item(matIndex)->copy());
  }
}

void VRMLCone::apply(VRMLState& state)
{
  List3D *list3D = new List3D;
  list3D->addTransform(state.getTransMatrix());
  if (myParts & VRML_SIDES)
  {
    Cone3D *cone3D = new Cone3D(myBottomRadius, Vector3D(0,-myHeight/2,0),
				0.0, Vector3D(0,myHeight/2,0));
    cone3D->open();
    addMaterial(state, cone3D, 0);
    list3D->adoptObject(cone3D);
  }
  if (myParts & VRML_BOTTOM)
  {
    Disc3D *disc3D = new Disc3D(myBottomRadius,Vector3D(0,-myHeight/2,0),Vector3D(0,-1,0));
    addMaterial(state, disc3D, 1);
    list3D->adoptObject(disc3D);
  }
  if (list3D->countSubobject())
    state.getObjects().adoptObject(list3D);
  else
    delete list3D;
}
    
void VRMLCone::setParts(unsigned long parts) 
{ 
  myParts = parts; 
}

void VRMLCone::setBottomRadius(double bottomRadius) 
{
  myBottomRadius = bottomRadius; 
}

void VRMLCone::setHeight(double height) 
{ 
  myHeight = height; 
}

void VRMLCone::reset()
{
  myParts = VRML_ALL;
  myBottomRadius = 1.0;
  myHeight = 2.0;
}

void VRMLCone::apply(Stack<VRMLState*> &stack) 
{
  apply(*stack.top()); 
}

VRMLObject *VRMLCone::copy() 
{
  return new VRMLCone(*this); 
}

//___________________________________________________________________ VRMLCube

void VRMLCube::addMaterial(VRMLState& state, Object3D *object3D, int matIndex)
{
  if (state.getMaterial().count())
  {
    if (state.getMaterialBinding() == VRML_PER_PART 
	|| state.getMaterialBinding() == VRML_PER_PART_INDEXED
	|| state.getMaterialBinding() == VRML_PER_FACE 
	|| state.getMaterialBinding() == VRML_PER_FACE_INDEXED)
      matIndex %= state.getMaterial().count();
    else
      matIndex = 0;

    object3D->appendTexture(state.getMaterial().item(matIndex)->copy());
  }
}

void VRMLCube::apply(VRMLState& state)
{ 
  List3D *list3D = new List3D;			    
  list3D->addTransform(state.getTransMatrix());
  List<Vector3D> listVector3D;
  double x = myWidth/2, y = myHeight/2, z = myDepth/2;
  double v[8][3]={{-x,y,-z},{x,y,-z},{x,-y,-z},{-x,-y,-z},
		{-x,y, z},{x,y, z},{x,-y, z},{-x,-y, z}};
  for (int k = 0; k < 8; k++) listVector3D.append(Vector3D(v[k][0],v[k][1],v[k][2]));
  int f[6][4] = {{0,1,5,4},{3,7,6,2},{0,4,7,3},{1,2,6,5},{4,5,6,7},{0,3,2,1}};
  for (int i = 0; i < 6; i++)
  {
    List<Vector3D> listVertices;
    for (int j = 0; j < 4; j++)
      listVertices.append(listVector3D.item(f[i][j]));
    Polygon3D* polygon3D = new Polygon3D(listVertices);
    addMaterial(state, polygon3D, i);
    list3D->adoptObject(polygon3D);
  }
  if (list3D->countSubobject())
    state.getObjects().adoptObject(list3D);
  else
    delete list3D;
}
   
void VRMLCube::setWidth(double width)
{
  myWidth = width; 
}

void VRMLCube::setHeight(double height) 
{ 
  myHeight = height; 
}

void VRMLCube::setDepth(double depth) 
{ 
  myDepth = depth; 
}

void VRMLCube::reset() 
{
  myWidth = 2.0;
  myHeight = 2.0;
  myDepth = 2.0;
}     

void VRMLCube::apply(Stack<VRMLState*> &stack)
{ 
  apply(*stack.top()); 
}
  
VRMLObject *VRMLCube::copy() 
{
  return new VRMLCube(*this); 
}

//___________________________________________________________________ VRMLCylinder

void VRMLCylinder::addMaterial(VRMLState& state, Object3D* object3D, int matIndex)
{
  if (state.getMaterial().count())
  {
    if (state.getMaterialBinding() == VRML_PER_PART 
	|| state.getMaterialBinding() == VRML_PER_PART_INDEXED)
      matIndex %= state.getMaterial().count();
    else
      matIndex = 0;

    object3D->appendTexture(state.getMaterial().item(matIndex)->copy());
  }
}

void VRMLCylinder::apply(VRMLState& state)
{
  List3D *list3D = new List3D;
  list3D->addTransform(state.getTransMatrix());
  if (myParts & VRML_SIDES)
  {
    Cylinder3D *cylinder3D;
    cylinder3D = new Cylinder3D(myRadius,Vector3D(0,-myHeight/2,0),Vector3D(0,myHeight/2,0));
    cylinder3D->open();
    addMaterial(state, cylinder3D, 0);
    list3D->adoptObject(cylinder3D);
  }
  if (myParts & VRML_TOP)
  {	
    Disc3D *disc3D = new Disc3D(myRadius,Vector3D(0,myHeight/2,0),Vector3D(0,1,0));
    addMaterial(state, disc3D, 1);
    list3D->adoptObject(disc3D);
  }
  if (myParts & VRML_BOTTOM)
  {
    Disc3D *disc3D = new Disc3D(myRadius,Vector3D(0,-myHeight/2,0),Vector3D(0,-1,0));
    addMaterial(state, disc3D, 2);
    list3D->adoptObject(disc3D);
  }
  if (list3D->countSubobject())
    state.getObjects().adoptObject(list3D);
  else
    delete list3D;
}

void VRMLCylinder::setParts(unsigned long parts) 
{ 
  myParts = parts; 
}

void VRMLCylinder::setRadius(double radius) 
{
  myRadius = radius; 
}

void VRMLCylinder::setHeight(double height)
{
  myHeight = height; 
}

void VRMLCylinder::reset()
{
  myParts = VRML_ALL;
  myRadius = 1.0;
  myHeight = 2.0;
}

void VRMLCylinder::apply(Stack<VRMLState*> &stack) 
{
  apply(*stack.top()); 
}

VRMLObject *VRMLCylinder::copy() 
{
  return new VRMLCylinder(*this); 
}

//___________________________________________________________________ VRMLIndexedFaceSet

void VRMLIndexedFaceSet::addMaterial(VRMLState& state, Object3D *object3D, int matIndex)
{
  if (state.getMaterial().count())
  {
    if (state.getMaterialBinding() == VRML_PER_PART 
	|| state.getMaterialBinding() == VRML_PER_FACE)
      ;
    else if (myMaterialIndex.count() 
	     && (state.getMaterialBinding() == VRML_PER_PART_INDEXED 
		 || state.getMaterialBinding() == VRML_PER_FACE_INDEXED))
      matIndex = myMaterialIndex.item(matIndex % myMaterialIndex.count());
    else
      matIndex = 0;
    matIndex %= state.getMaterial().count();

    object3D->appendTexture(state.getMaterial().item(matIndex)->copy());
  }  
}

void VRMLIndexedFaceSet::apply(VRMLState& state)
{
  if (state.getCoordinate3().count())
  {
    List3D* list3D = new List3D;
    list3D->addTransform(state.getTransMatrix());
    List<Vector3D> listVector3D;
    for (int i = 0, j = 0, k = 0; i < myCoordIndex.count(); i++)
    {
      if (myCoordIndex.item(i) != -1)
      {				
	//
	// some of the faces are given closed, we don't need the last one
	// 
	if (i == k || myCoordIndex.item(i) != myCoordIndex.item(k))
	{
	  long l = myCoordIndex.item(i) % state.getCoordinate3().count();
	  listVector3D.append(state.getCoordinate3().item(l));
	}
      }
      else
      {				  
        // if possible use triangles !!!			  
	if (listVector3D.count() == 3) {
          Triangle3D* triangle3D = new Triangle3D(listVector3D.item(0),listVector3D.item(1),listVector3D.item(2));
          addMaterial(state, triangle3D, j); j++; k = i+1;
          list3D->adoptObject(triangle3D);
	}
	else {
	Polygon3D* polygon3D = new Polygon3D(listVector3D);
	addMaterial(state, polygon3D, j); j++; k = i+1;
	list3D->adoptObject(polygon3D);
	}
	
	listVector3D.removeAll();
      }
    }			    
    if (list3D->countSubobject())
      state.getObjects().adoptObject(list3D);
    else
      delete list3D;
  }
}

void VRMLIndexedFaceSet::setCoordIndex(const List<long>& coordIndex) 
{ 
  myCoordIndex = coordIndex; 
}

void VRMLIndexedFaceSet::setMaterialIndex(const List<long>& materialIndex) 
{ 
  myMaterialIndex = materialIndex; 
}

void VRMLIndexedFaceSet::setNormalIndex(const List<long>& normalIndex) 
{ 
  myNormalIndex = normalIndex; 
}

void VRMLIndexedFaceSet::reset() 
{ 
  myCoordIndex.removeAll();
  myMaterialIndex.removeAll();
  myNormalIndex.removeAll();
}

void VRMLIndexedFaceSet::apply(Stack<VRMLState*> &stack) 
{
  apply(*stack.top()); 
}
 
VRMLObject *VRMLIndexedFaceSet::copy() 
{ 
  return new VRMLIndexedFaceSet(*this); 
}

//___________________________________________________________________ VRMLSphere

void VRMLSphere::addMaterial(VRMLState& state, Object3D* object3D, int matIndex)
{
  if (state.getMaterial().count())
  {
    if (state.getMaterialBinding() == VRML_PER_PART 
	|| state.getMaterialBinding() == VRML_PER_PART_INDEXED)
      matIndex %= state.getMaterial().count();
    else
      matIndex = 0;

    object3D->appendTexture(state.getMaterial().item(matIndex)->copy());
  }
}

void VRMLSphere::apply(VRMLState& state)
{
  Sphere3D* sphere3D = new Sphere3D(myRadius, Vector3D(0,0,0));
  sphere3D->addTransform(state.getTransMatrix());
  addMaterial(state, sphere3D, 0);
  state.getObjects().adoptObject(sphere3D);
}
   
void VRMLSphere::setRadius(double radius)
{
  myRadius = radius; 
}

void VRMLSphere::reset()
{
  myRadius = 1.0; 
}

void VRMLSphere::apply(Stack<VRMLState*> &stack) 
{
  apply(*stack.top()); 
}     

VRMLObject* VRMLSphere::copy() 
{
  return new VRMLSphere(*this); 
}

//___________________________________________________________________ VRMLCoordinate3

void VRMLCoordinate3::apply(VRMLState& state)
{
  state.setCoordinate3(myPoint); 
}

void VRMLCoordinate3::setPoint(List<Vector3D>& point) 
{ 
  myPoint = point; 
}

void VRMLCoordinate3::reset() 
{
  myPoint.removeAll(); 
}

void VRMLCoordinate3::apply(Stack<VRMLState*> &stack)
{
  apply(*stack.top()); 
}

VRMLObject* VRMLCoordinate3::copy()
{
  return new VRMLCoordinate3(*this); 
}

//___________________________________________________________________ VRMLMaterial

void VRMLMaterial::apply(VRMLState& state)
{ 
  state.deleteMaterials();
  
  int maxCount = myAmbientColor.count();
  if (myDiffuseColor.count() > maxCount) 
    maxCount = myDiffuseColor.count();
  if (mySpecularColor.count() > maxCount) 
    maxCount = mySpecularColor.count();
  
  for (int i = 0; i < maxCount; i++) {
    RCString errMsg;
    Phong* phong = dynamic_cast<Phong*>(Makeable::make(errMsg, ScopedName("3D", "phong"), NULL));

    if (phong == NULL)
      phong = new Phong();
    
    if (myAmbientColor.count())
      phong->setAmbient(myAmbientColor.item(i % myAmbientColor.count()));
    if (myDiffuseColor.count())
      phong->setDiffuse(myDiffuseColor.item(i % myDiffuseColor.count()));
    if (mySpecularColor.count())
      phong->setSpecular(mySpecularColor.item(i % mySpecularColor.count()));
    state.getMaterial().append(phong);
  }
}  
    
void VRMLMaterial::setAmbientColor(List<Color>& ambientColor) 
{
   myAmbientColor = ambientColor; 
}

void VRMLMaterial::setDiffuseColor(List<Color>& diffuseColor) 
{ 
  myDiffuseColor = diffuseColor; 
}

void VRMLMaterial::setSpecularColor(List<Color>& specularColor) 
{ 
  mySpecularColor = specularColor; 
}

void VRMLMaterial::reset() 
{ 
  myAmbientColor.removeAll();
  myDiffuseColor.removeAll(); 
  mySpecularColor.removeAll();
}
 
void VRMLMaterial::apply(Stack<VRMLState*> &stack) 
{
  apply(*stack.top()); 
}

VRMLObject* VRMLMaterial::copy() 
{
  return new VRMLMaterial(*this); 
}

//___________________________________________________________________ VRMLMaterialBinding

void VRMLMaterialBinding::apply(VRMLState& state)
{
  state.setMaterialBinding(myValue); 
}

void VRMLMaterialBinding::setValue(VRML_binding_t value) 
{
  myValue = value; 
}

void VRMLMaterialBinding::reset()
{
  myValue = VRML_DEFAULT; 
}

void VRMLMaterialBinding::apply(Stack<VRMLState*> &stack)
{
  apply(*stack.top()); 
}

VRMLObject* VRMLMaterialBinding::copy()
{
  return new VRMLMaterialBinding(*this); 
}

//___________________________________________________________________ VRMLNormal

void VRMLNormal::apply(VRMLState& state)
{
  state.setNormal(myVector); 
}

void VRMLNormal::setVector(List<Vector3D> vector)
{
  myVector = vector; 
}

void VRMLNormal::reset()
{
  myVector.removeAll(); 
}

void VRMLNormal::apply(Stack<VRMLState*> &stack)
{
  apply(*stack.top()); 
}

VRMLObject* VRMLNormal::copy() 
{ 
  return new VRMLNormal(*this); 
}

//___________________________________________________________________ VRMLNormalBinding

void VRMLNormalBinding::apply(VRMLState& state) 
{
  state.setNormalBinding(myValue); 
}

void VRMLNormalBinding::setValue(VRML_binding_t value) 
{ 
  myValue = value; 
}

void VRMLNormalBinding::reset() 
{ 
  myValue = VRML_DEFAULT; 
}

void VRMLNormalBinding::apply(Stack<VRMLState*> &stack) 
{
  apply(*stack.top()); 
}

VRMLObject* VRMLNormalBinding::copy() 
{
  return new VRMLNormalBinding(*this); 
}

//___________________________________________________________________ VRMLSeparatorStart

void VRMLSeparatorStart::apply(Stack<VRMLState*> &stack)
{
  VRMLState* state = new VRMLState();
  state->takeProperties(*stack.top());
  stack.push(state);
}

VRMLObject* VRMLSeparatorStart::copy() 
{
  return new VRMLSeparatorStart(*this); 
}

//___________________________________________________________________ VRMLSeparatorStop

void VRMLSeparatorStop::apply(Stack<VRMLState*> &stack)
{
  VRMLState *state = stack.top();
  stack.pop();
  stack.top()->getObjects().adoptObject(state->orphanObjects());
  delete state;
}

VRMLObject* VRMLSeparatorStop::copy() 
{
  return new VRMLSeparatorStop(*this); 
}

//___________________________________________________________________ VRMLLODStart

void VRMLLODStart::apply(Stack<VRMLState*> &stack)
{
  VRMLState* state = new VRMLState();
  state->takeProperties(*stack.top());
  stack.push(state);
}

VRMLObject* VRMLLODStart::copy() 
{
  return new VRMLLODStart(*this); 
}

//___________________________________________________________________ VRMLLODStop

void  VRMLLODStop::apply(Stack<VRMLState*> &stack)
{
  VRMLState *state = stack.top();
  stack.pop();
  if (state->getObjects().countSubobject())
  {
    Object3D *object3D = state->getObjects().getSubobject(0);
    state->getObjects().orphanObject(object3D);
    stack.top()->getObjects().adoptObject(object3D);
  }
  delete state;
}

VRMLObject * VRMLLODStop::copy() 
{
  return new VRMLLODStop(*this); 
}

//___________________________________________________________________ VRMLSwitchStart

void VRMLSwitchStart::setWhichChild(long whichChild) 
{ 
  myWhichChild = whichChild; 
}

void VRMLSwitchStart::reset() 
{
  myWhichChild = 0; 
}

void VRMLSwitchStart::apply(Stack<VRMLState*> &stack)
{
  stack.top()->setWhichChild(myWhichChild);
  VRMLState* state = new VRMLState();
  state->takeProperties(*stack.top());
  stack.push(state);
}
VRMLObject* VRMLSwitchStart::copy() 
{
  return new VRMLSwitchStart(*this); 
}

//___________________________________________________________________ VRMLSwitchStop

void VRMLSwitchStop::apply(Stack<VRMLState*> &stack)
{
  VRMLState *state = stack.top();
  stack.pop();
  if (stack.top()->getWhichChild() == -3) // behave like group node 
  {
    stack.top()->getObjects().adoptObject(state->orphanObjects());
    stack.top()->takeProperties(*state);
  }
  else if (stack.top()->getWhichChild() >= 0
   && stack.top()->getWhichChild() < state->getObjects().countSubobject())
  {
    Object3D *object3D = state->getObjects().getSubobject(stack.top()->getWhichChild());
    state->getObjects().orphanObject(object3D);
    stack.top()->getObjects().adoptObject(object3D);
  }      
  delete state;
}

VRMLObject *VRMLSwitchStop::copy() 
{
  return new VRMLSwitchStop(*this); 
}

//___________________________________________________________________ VRMLTransformSeparatorStart

void VRMLTransformSeparatorStart::apply(Stack<VRMLState*> &stack)
{
  VRMLState* state = new VRMLState();
  state->takeProperties(*stack.top());
  stack.push(state);
}

VRMLObject* VRMLTransformSeparatorStart::copy() 
{
  return new VRMLTransformSeparatorStart(*this); 
}

//___________________________________________________________________ VRMLTransformSeparatorStop

void VRMLTransformSeparatorStop::apply(Stack<VRMLState*> &stack)
{
  VRMLState *state = stack.top();
  stack.pop();
  state->setTransMatrix(stack.top()->getTransMatrix());      
  stack.top()->getObjects().adoptObject(state->orphanObjects());
  stack.top()->takeProperties(*state);
  delete state;
}

VRMLObject* VRMLTransformSeparatorStop::copy() 
{ 
  return new VRMLTransformSeparatorStop(*this); 
}
