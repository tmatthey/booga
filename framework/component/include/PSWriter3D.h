/*
 * $RCSfile: PSWriter3D.h,v $
 *
 * Render an arbitrary 3D world to a postscript file. 
 * The task is performed by executing a Wireframe component to produce a 
 * World2D object which is converted to a postscript representation by 
 * applying the PSWriter2D component.
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: PSWriter3D.h,v 1.3 1996/08/01 12:00:59 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PSWriter3D_H
#define _PSWriter3D_H

#include <fstream.h>

#include "booga/base/RCString.h"
#include "booga/base/PrimitiveTypes.h"
#include "booga/component/Operation3D.h"

class Camera3D;

//___________________________________________________________________ PSWriter3D

class PSWriter3D : public Operation3D {
declareRTTI(PSWriter3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PSWriter3D(const RCString& filename = "");                             
private:
  PSWriter3D(const PSWriter3D&);             // No copies.

public:
  // virtual ~PSWriter3D();                  // Use default version.

private:
  PSWriter3D& operator=(const PSWriter3D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class PSWriter3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void adoptCamera(Camera3D* camera);
  void deleteCamera();
  // Set or delete camera for rendering.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool doExecute();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Camera3D*  myCamera;
  bool       myHasAdoptedCamera;
  RCString   myFilename;
  ofstream   myOfs;    
};

//______________________________________________________________________ INLINES

#endif // _PSWriter3D_H

