/*
 * $RCSfile: VRMLState.C,v $ 
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
 *  $Id: VRMLState.C,v 1.2 1996/08/01 12:01:37 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Texture3D.h"
#include "VRMLState.h"

//_______________________________________________________________ VRMLState

VRMLState::VRMLState()
{
  myObjects = new List3D();
  myTransMatrix.identity();
  myMaterialBinding = VRML_DEFAULT;
  myNormalBinding = VRML_DEFAULT;    
  myWhichChild = 0;
}

VRMLState::~VRMLState()
{
  deleteMaterials();
  delete myObjects;
}

void VRMLState::setTransMatrix(TransMatrix3D &transMatrix) 
{
  myTransMatrix = transMatrix; 
}

TransMatrix3D& VRMLState::getTransMatrix() 
{
  return myTransMatrix; 
}

List3D& VRMLState::getObjects() 
{ 
  return *myObjects; 
}

List<Vector3D>& VRMLState::getCoordinate3() 
{
  return myCoordinate3; 
}

void VRMLState::setCoordinate3(List<Vector3D>& coordinate3) 
{
  myCoordinate3 = coordinate3; 
}    

List<Texture3D*>& VRMLState::getMaterial() 
{
  return myMaterial; 
}    

VRML_binding_t VRMLState::getMaterialBinding() 
{ 
  return myMaterialBinding; 
}

void VRMLState::setMaterialBinding(VRML_binding_t matBinding) 
{ 
  myMaterialBinding = matBinding; 
}

List<Vector3D>& VRMLState::getNormal() 
{ 
  return myNormal; 
}

void VRMLState::setNormal(List<Vector3D>& normal)
{ 
  myNormal = normal; 
}    

VRML_binding_t VRMLState::getNormalBinding() 
{ 
  return myNormalBinding; 
}

void VRMLState::setNormalBinding(VRML_binding_t norBinding) 
{ 
  myNormalBinding = norBinding; 
}  

long VRMLState::getWhichChild() 
{ 
  return myWhichChild; 
}

void VRMLState::setWhichChild(long whichChild) 
{ 
  myWhichChild = whichChild; 
}

void VRMLState::takeProperties(VRMLState& state)
{
  myTransMatrix = state.getTransMatrix();
  myCoordinate3 = state.getCoordinate3();
  deleteMaterials();
  
  for (int i = 0; i < state.getMaterial().count(); i++)
    myMaterial.append(state.getMaterial().item(i)->copy());

  myMaterialBinding = state.getMaterialBinding();
  myNormal = state.getNormal();
  myNormalBinding = state.getNormalBinding();  
}

List3D *VRMLState::orphanObjects()
{ 
  List3D *objects = myObjects; 
  myObjects = new List3D(); 
  return objects; 
}

void VRMLState::deleteMaterials()
{
  for (int i = 0; i < myMaterial.count(); i++)
    delete myMaterial.item(i);
  myMaterial.removeAll();
}

void VRMLState::deleteObjects()
{  
  delete myObjects;
  myObjects = new List3D(); 
}


