/*
 * $RCSfile: Triangulator.C,v $
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
 *  $Id: Triangulator.C,v 1.7 1996/11/01 13:35:14 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/RCString.h"
#include "booga/base/Report.h"
#include "booga/base/Geometry3D.h"
#include "booga/object/Triangle3D.h"
#include "booga/component/Triangulator.h"

//_____________________________________________________________________ Triangulator

implementRTTI(Triangulator, Operation3D);

Triangulator::Triangulator(std::ostream& os)
: myStream(os) 
{}

Traversal::Result Triangulator::visit(Triangle3D* obj)
{
  //
  // Add modeling transformation to the vertices.
  // 
  Vector3D v[3];
  for (int i=0; i<3; i++)
    v[i] = getTraversal()->getPath()->getLastTransform().transformAsPoint(
	         obj->getVertex(i));
   
  Vector3D normal(Geometry3D::normal(v[2],v[0],v[1]));
  if (normal.equal(obj->getNormal(0)) && 
      normal.equal(obj->getNormal(1)) && 
      normal.equal(obj->getNormal(2))){
    myStream << "triangle (" 
             << v[0] << "," << std::endl
             << "          " 
             << v[1] << "," << std::endl
             << "          " 
             << v[2] << ");" << std::endl << std::endl;
  }
  else {
    myStream << "triangle (" 
             << v[0] << ", " << obj->getNormal(0) << "," << std::endl
             << "          " 
             << v[1] << ", " << obj->getNormal(1) << "," << std::endl
             << "          " 
             << v[2] << ", " << obj->getNormal(2) << ");" << std::endl << std::endl;
  }
  return Traversal::CONTINUE;
}


Traversal::Result Triangulator::dispatch(Makeable* obj)
{
  tryConcrete(Triangle3D, obj);
  
  //
  // Create decomposition for objects other than triangles.
  //
  return Traversal::UNKNOWN;
}


