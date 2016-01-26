/*
 * GSBGLRenderer.C 
 *
 * Copyright (C) 1996, Pascal Habegger <habegger@iam.unibe.ch>
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
 *  $Id: GSBGLRenderer.C,v 1.7 1997/04/08 11:04:44 habegger Exp $
 * -----------------------------------------------------------------------------
 */
 
 
#include "booga/object/Cylinder3D.h" 
#include "booga/object/List3D.h"
#include "booga/object/Polygon3D.h"
//#include "booga/glwrapper/GLPhong.h"
#include "booga/texture/Phong.h"

#include "GSBGLRenderer.h"
#include "GSBConetreeNode3D.h"
#include "GSBNodeTools.h"
#include "GL/gl.h"

//___________________________________________________________________ GSBGLRenderer

implementRTTI(GSBGLRenderer, Renderer);

GSBGLRenderer::GSBGLRenderer()
: GLRenderer()
{}


//Visitor::VisitResult GSBGLRenderer::visit(Aggregate3D* obj)
//{
//cout << "Besuche AGGREGATE" << endl << flush;
//  GSBNodeManager* aManager = GSBNodeTools::hasNodeManager(obj);
//  if (aManager && aManager->isPruned()) 
//    return Visitor::BREAK;
//  else 
//    return GLRenderer::visit(obj);
//}

Traversal::Result GSBGLRenderer::visit(Text3D* )
{
  return Traversal::UNKNOWN;
}


//Visitor::VisitResult GSBGLRenderer::visit(Primitive3D* obj)
//{
//cout << "							entered GSBGLRenderer::visit\n";
//  GSBConetreeNode3D* node = dynamic_cast(GSBConetreeNode3D, obj);
//  if (obj == NULL) 
//		return GLRenderer::visit(obj);
//	
//cout << "							rendering node\n";
//	List3D* segments = new List3D;
//
//  // add box to decomposition list:
//  segments->adoptObject(new Cylinder3D(node->getRadius(), 
//				Vector3D(0, 0,                0), 
//				Vector3D(0, node->getWidth(), 0)));
//				
//  segments->adoptObject(new Cylinder3D(node->getRadius(), 
//				Vector3D(0, node->getWidth(), 0), 
//				Vector3D(0, node->getWidth(), node->getHeight())));
//				
//  segments->adoptObject(new Cylinder3D(node->getRadius(), 
//				Vector3D(0, node->getWidth(), node->getHeight()), 
//				Vector3D(0, 0,                node->getHeight())));
//				
//  segments->adoptObject(new Cylinder3D(node->getRadius(), 
//				Vector3D(0, 0,                node->getHeight()),
//				Vector3D(0, 0,                0)));
//
//  // add polygon for background: 
//  List<Vector3D> vertices;
//  vertices.append(Vector3D(0, 0, 0));
//  vertices.append(Vector3D(0, node->getWidth(), 0));
//  vertices.append(Vector3D(0, node->getWidth(), node->getHeight()));
//  vertices.append(Vector3D(0, 0, node->getHeight()));
//  
//  Polygon3D* background = new Polygon3D(vertices);
//  Phong* texture = new Phong;
//  texture->setDiffuse(Color(.1, .6, .1));
//  texture->setSpecular(Color(.1, .6, .2));
//  background->appendTexture(texture);
//  segments->adoptObject(background);
//  
//  // add text to decomposition list:
////  RCString theLabel = node->getLabel();
////  cout << "LABEL = " << theLabel << endl << flush;
//  Text3D* text = new Text3D("BLA");
//  text->setHeight(node->getHeight() * .8);
//  text->addTransform(TransMatrix3D::makeTranslate(
//		.2, node->getWidth() * .1, node->getHeight() * .1));
//  texture = new Phong;
//  texture->setDiffuse(Color(.05, .05, .05));
//  texture->setSpecular(Color(.05, .05, .05));
//  text->appendTexture(texture);
//  segments->adoptObject(text);
//  
//  segments->computeBounds();
//  cout << "Besuche meine Zerlegung" << endl;
//  GLRenderer::visit(segments);
//  cout << "Fertig mit meiner Zerlegung" << endl << flush;
//  delete segments;
//  return Visitor::CONTINUE;
//}
//
//
