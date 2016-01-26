/*
 * $RCSfile: ShowNormals.C,v $
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
 *  $Id: ShowNormals.C,v 1.9 1996/09/13 08:06:26 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/object/Triangle3D.h"
#include "booga/object/Cone3D.h"
#include "booga/object/List3D.h"
#include "booga/object/Texture3D.h"
#include "booga/object/Path3D.h"
#include "booga/component/ShowNormals.h"

//__________________________________________________________________ ShowNormals

implementRTTI(ShowNormals, Operation3D);

ShowNormals::ShowNormals()
{
  myNormalContainer = NULL;
  myNormalTexture = NULL;
  myComputeNormalSize = true;
  myNormalLength = 1;
  myNormalWidth  = 0.1;
}

ShowNormals::~ShowNormals()
{
  delete myNormalTexture;
}

void ShowNormals::adoptTexture(Texture3D* texture)
{
  //
  // Self assignment?
  //
  if (myNormalTexture == texture)
    return;
    
  delete myNormalTexture;
  myNormalTexture = texture;    
}

bool ShowNormals::doExecute()
{
  myNormalContainer = new List3D;

  traverse(getWorld());
  
  ostrstream os;
  os << "[ShowNormals::doExecute] created " << myNormalContainer->countSubobject();
  os << " normals";
  Report::debug(os);
  
  getWorld()->getObjects()->adoptObject(myNormalContainer);
  myNormalContainer = NULL;
  getWorld()->getObjects()->computeBounds();

  return true;
}

Traversal::Result ShowNormals::visit(Triangle3D* obj)
{
  Vector3D from;
  Vector3D normal;
  const Transform3D& currTrans = getTraversal()->getPath()->getLastTransform();
  Cone3D* cone;
  Real length, width;
  
  if (myComputeNormalSize) {
    //
    // Compute size of the normal objects to be generated according 
    // to the size of the object.
    //
    Vector3D bbMin = currTrans.transformAsPoint(obj->getBounds().getMin());
    Vector3D bbMax = currTrans.transformAsPoint(obj->getBounds().getMax());
    Real distance  = max(fabs(bbMax.x() - bbMin.x()), 
                         fabs(bbMax.y() - bbMin.y()), 
                         fabs(bbMax.z() - bbMin.z()));
    length = distance / 3;
    width  = length / 10;
  } else {
    length = myNormalLength;
    width  = myNormalWidth;
  }
  
  for (int i=0; i<3; i++) {
    from   = currTrans.transformAsPoint(obj->getVertex(i));
    normal = currTrans.transformAsNormal(obj->getNormal(i));

    if (equal(normal.length(), 0))
      continue;

    normal.normalize();
    
    cone = new Cone3D(width, from, 0, from + normal*length);
    cone->setPrecision(0.1);
    myNormalContainer->adoptObject(cone);
  }
  
  return Traversal::CONTINUE;
}

Traversal::Result ShowNormals::dispatch(Makeable* obj)
{
  tryConcrete(Triangle3D, obj);
  
  //
  // Create decomposition for objects other than triangles.
  //
  return Traversal::UNKNOWN;
}


