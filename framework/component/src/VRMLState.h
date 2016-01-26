/*
 * $RCSfile: VRMLState.h,v $ 
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
 *  $Id: VRMLState.h,v 1.2 1996/08/01 12:01:37 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _VRMLState_H
#define _VRMLState_H

#include "booga/base/List.h"
#include "booga/base/TransMatrix3D.h"
#include "booga/base/Vector3D.h"

#include "booga/object/Object3D.h"
#include "booga/object/List3D.h"

#include "VRML.h"

class Texture3D;

class VRMLState
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  VRMLState();
private:
  VRMLState(const VRMLState&);              // no copies
public:
  ~VRMLState();
private:
  VRMLState& operator=(const VRMLState&);   // no assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class VRMLState
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setTransMatrix(TransMatrix3D &transMatrix);
  TransMatrix3D& getTransMatrix();
  List3D& getObjects();
  List<Vector3D>& getCoordinate3();
  void setCoordinate3(List<Vector3D>& coordinate3);
  List<Texture3D*>& getMaterial();
  VRML_binding_t getMaterialBinding();
  void setMaterialBinding(VRML_binding_t matBinding);
  List<Vector3D>& getNormal();
  void setNormal(List<Vector3D>& normal);
  VRML_binding_t getNormalBinding();
  void setNormalBinding(VRML_binding_t norBinding);
  long getWhichChild();
  void setWhichChild(long whichChild);
  void takeProperties(VRMLState& state);
  List3D *orphanObjects();
  void deleteMaterials();
  void deleteObjects();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:  
  List3D* myObjects;
  TransMatrix3D myTransMatrix;
  List<Vector3D> myCoordinate3;  
  List<Texture3D*> myMaterial;
  VRML_binding_t myMaterialBinding;
  List<Vector3D> myNormal;
  VRML_binding_t myNormalBinding;      
  long myWhichChild;
};


#endif // _VRMLState_H





