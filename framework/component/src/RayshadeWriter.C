/*
 * $RCSfile: RayshadeWriter.C,v $
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
 *  $Id: RayshadeWriter.C,v 1.12 1997/09/19 07:14:39 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
//________________________________________________________________ RayshadeWriter

#ifdef SVR4
#include <unistd.h>  // STDOUT_FILENO
#endif

#include "booga/object/Shared3D.h"
#include "booga/object/Aggregate3D.h"
#include "booga/object/List3D.h"
#include "booga/object/Grid3D.h"
#include "booga/object/AmbientLight.h"
#include "booga/object/PointLight.h"
#include "booga/object/Camera3D.h"
#include "booga/object/Viewing3D.h"
#include "booga/object/PerspectiveViewing3D.h"
#include "booga/object/OrthographicViewing3D.h"
#include "booga/object/Box3D.h"
#include "booga/object/Cone3D.h"
#include "booga/object/Cylinder3D.h"
#include "booga/object/Disc3D.h"
#include "booga/object/Polygon3D.h"
#include "booga/object/Sphere3D.h"
#include "booga/object/Text3D.h"
#include "booga/object/Torus3D.h"
#include "booga/object/Triangle3D.h"
#include "booga/object/Path3D.h"
#include "booga/object/Texture3DList.h"
#include "booga/object/Texture3D.h"
#include "booga/object/ConstantTexture3D.h"
#include "booga/object/Checker.h"
#include "booga/texture/Whitted.h"
#include "booga/texture/Phong.h"
#include "booga/texture/Matte.h"
#include "booga/component/CollectShared3D.h"
#include "booga/component/CollectTexture3D.h"
#include "booga/component/Collector3DFor.h"
#include "booga/component/RayshadeWriter.h"
#include "booga/animation/Animation3D.h"

//_____________________________________________________________ RayshadeWriter

implementRTTI(RayshadeWriter, Operation3D);

RayshadeWriter::RayshadeWriter(const RCString& filename) 
: myLevel(0), myWriteDefLevel(0), mySkipLevel(0), 
  myIndent(0), myFilename(filename)
{
  myCamera = NULL;
  myHasAdoptedCamera = false;
}

RayshadeWriter::~RayshadeWriter()
{
  if (myCamera != NULL)
    delete myCamera;
}
//
// Warning: Consumes (deletes) the List given to the function
//
void RayshadeWriter::printParameterList(List<Value>* parList) {
  if (parList->count() > 0) {
    for(long i=0; i < parList->count(); i++) {
      if (i!=0) myOs << " ";
      myOs << parList->item(i);
    }
  }
  //
  // destroy the ParameterList
  //
  delete parList;
}

void RayshadeWriter::printObject3DAttributes(Object3D* obj) {
  printTransform(obj->getTransform().getTransMatrix());

//  const Texture3D *texture = obj->getTexture();
//  if (texture != NULL) {
//    RCString textureName = texture->getName();
//    if (textureName.isEmpty()) {
//      printTextureName(texture);
//    }
//    else {
//      myOs << " " << textureName << ";";
//    }
//  }
}
 
void RayshadeWriter::printTransform(const TransMatrix3D& mat)
{
  if (mat != TransMatrix3D::getIdentity()) {
    TransMatrix3D temp = mat;
    temp.translate(-temp(3,0), -temp(3,1), -temp(3,2));
    if (temp != TransMatrix3D::getIdentity()) {
      newLineIndent();
      myOs << "transform "
        << " " << mat(0,0) << " " << mat(0,1) << " " << mat(0,2) << " ";
      newLineIndent();
      myOs << "         " << mat(1,0) << " " << mat(1,1) << " " << mat(1,2) << " ";
      newLineIndent();
      myOs << "         " << mat(2,0) << " " << mat(2,1) << " " << mat(2,2) << " ";
      newLineIndent();
      myOs << "         " << mat(3,0) << " " << mat(3,1) << " " << mat(3,2) << " ";
      newLineIndent();
    } else {
      newLineIndent();
      myOs << "translate "
	   << mat(3,0) << " " << mat(3,1) << " " << mat(3,2) << " ";
    }
  } 
  else {
    // this will write dummy translate [0,0,0]; 
    // to make sure that there is at least one attribute
    newLineIndent();
    myOs << "translate "
	<< mat(3,0) << " " << mat(3,1) << " " << mat(3,2) << "";
  }
}

void RayshadeWriter::printTextureName(const Texture3D* texture)
{
  if (texture != NULL) {
    RCString textureName = texture->getName();
    if (textureName.isEmpty()) {
      printTextureDefinition(texture);
    }
    else {
      myOs << " " << textureName << " ";
    }
  }
}
void RayshadeWriter::printTextureDefinition(const Texture3D* texture_)
{
  Texture3D* texture = const_cast<Texture3D*>(texture_);
  //
  // If the texture object is of type Texture3DList, then we recursively 
  // visit all its members.
  //
  if (dynamic_cast<Texture3DList*>(texture) != NULL) {
    Texture3DList* textlist = dynamic_cast<Texture3DList*>(texture);

    for (textlist->first(); !textlist->isDone(); textlist->next())
      printTextureDefinition(textlist->getTexture());
  }
  //
  // If a checker texture is present, just apply the even texture.
  //
  else if (dynamic_cast<Checker*>(texture) != NULL) {
    Checker* checker = dynamic_cast<Checker*>(texture);
    myOs << "checker {";
    incIndent();
    if (checker->getEven() != NULL) {
      newLineIndent();
      myOs << "even {";
      incIndent();
      newLineIndent();
      printTextureDefinition(checker->getEven());
      decIndent();
      newLineIndent();
      myOs << "}";
    }
    if (checker->getOdd() != NULL) {
      newLineIndent();
      myOs << "odd {";
      incIndent();
      newLineIndent();
      printTextureDefinition(checker->getOdd());
      decIndent();
      newLineIndent();
      myOs << "}";
    }
    decIndent();
    newLineIndent();
    myOs << "}";
}
  //
  // Whitted textures 
  //
  else if (dynamic_cast<Whitted*>(texture) != NULL) {
    Whitted* whitted = dynamic_cast<Whitted*>(texture);

    myOs << "surface " << texture->getName();
    incIndent();
    newLineIndent();
    myOs << "diffuse "; printVector(whitted->getDiffuse());
    newLineIndent();
    myOs << "ambient "; printVector(whitted->getAmbient());
 
    if (whitted->getReflectivity() > 0.0) {
       newLineIndent();
       myOs << "reflect  " << whitted->getReflectivity();
    }
    if (whitted->getTransparency() > 0.0) {
       newLineIndent();
       myOs << "transp " << whitted->getTransparency();
       newLineIndent();
       myOs << "index " << whitted->getRefractionIndex();
       myOs << "\n";
    }
    decIndent();
    newLineIndent();
  }
  //
  // Phong textures
  //
  else if (dynamic_cast<Phong*>(texture) != NULL) {
    Phong* phong = dynamic_cast<Phong*>(texture);

    myOs << "surface " << texture->getName();
    incIndent();
    newLineIndent();
    myOs << "diffuse "; printVector(phong->getDiffuse());
    newLineIndent();
    myOs << "ambient "; printVector(phong->getAmbient());
    if (phong->getSpecular().brightness() > 0.0) {
      newLineIndent();
      myOs << "specular "; printVector(phong->getSpecular());
      newLineIndent();
      myOs << "specpow " <<  phong->getSpecPow();
    }
    decIndent();
    newLineIndent();
  }
  //
  // Matte textures
  //
  else if (dynamic_cast<Matte*>(texture) != NULL) {
    Matte* matte = dynamic_cast<Matte*>(texture);

    myOs << "surface " << texture->getName();
    incIndent();
    newLineIndent();
    myOs << "diffuse "; printVector(matte->getDiffuse());
    newLineIndent();
    myOs << "ambient "; printVector(matte->getAmbient());
    decIndent();
    newLineIndent();
  }
  //
  // Constant textures
  //
  else if (dynamic_cast<ConstantTexture3D*>(texture) != NULL) {
    ConstantTexture3D* consttext = dynamic_cast<ConstantTexture3D*>(texture);

    myOs << "constant { ";
    incIndent();
    newLineIndent();
    myOs << "color " << consttext->getColor() << ";";
    decIndent();
    newLineIndent();
    myOs << "};";
  }
}

void RayshadeWriter::printVector(const Vector3D& v)
{
  myOs << " " << v.x() << " " << v.y() << " " << v.z() << " ";
}

void RayshadeWriter::incIndent() {
  myIndent++;
}

void RayshadeWriter::decIndent() {
  myIndent--;
}

void RayshadeWriter::newLineIndent() {
  myOs << std::endl;
  int i;
  for(i=0; i<myIndent*2; i++) {
    myOs << " ";
  }
}

bool RayshadeWriter::doExecute()
{
  //
  // If myFilename is empty, we try to open stdout for writing
  //
  if (myFilename.isEmpty()) {
    myOs.tie(&std::cout);
    if (myOs.bad()) {
      Report::recoverable("[RayshadeWriter::doExecute] could not attach to stdout");
      return false;
    }
  }
  else {
    //
    // Filename is not empty, so we have to open a regular file:
    // try to open file and save image
    //
    myOs.open(myFilename.chars());
    if (myOs.bad()) {
      Report::recoverable("[RayshadeWriter::apply] could not open file named " + 
                            myFilename);
      return false;
    }
  }

  // write camera setup
  
  printCamera (myCamera);

  //
  // write texture definitions
  //

  newLineIndent();
  CollectTexture3D collectorT;
  collectorT.setSortCollection(false);
  collectorT.execute(getWorld());
  for(collectorT.first(); !collectorT.isDone(); collectorT.next()) {
      newLineIndent();
      printTextureDefinition(collectorT.getCurrent());
      newLineIndent();
  }

  //
  // write shared definitions:
  //
  CollectShared3D collector;
  collector.setSortCollection(false);

  collector.execute(getWorld());
  
  //
  // Store shareds in reverse order (i.e. correct order for writing)
  // 
  List<Shared3D*> sharedList;
  for(collector.first(); !collector.isDone(); collector.next()) {
    sharedList.prepend(collector.getCurrent());
  }

  //
  // write definition of each shared
  //
  World3D dummyWorld;
  for(long i=0; i<sharedList.count(); i++) {
    newLineIndent();
    myLevel = 0;
    myWriteDefLevel = 2;
    mySkipLevel = 1;
    dummyWorld.getObjects()->adoptObject(sharedList.item(i));
    traverse(&dummyWorld);
    dummyWorld.getObjects()->orphanObject(sharedList.item(i));
    newLineIndent();
  }

  //
  // do toplevel objects
  //
  myLevel = 0;
  mySkipLevel = 1;
  myWriteDefLevel = 0;
  traverse(getWorld());

  if (!myFilename.isEmpty())
    myOs.close();
    
  return true;
}

/*
 * visit Functions for Object3D class and derived classes
 */
Traversal::Result RayshadeWriter::visit(Object3D*)
{
  myOs << "/* RayshadeWriter::unknown object encountered */";
  newLineIndent();
  return Traversal::UNKNOWN;
}

Traversal::Result RayshadeWriter::visit(Animation3D* anim)
{
    for(long i=0;i<anim->countSubobject(); i++) {
      incLevel();
      dispatch(anim->getSubobject(i));
      decLevel();
    }

  printTransform(anim->getTransform().getTransMatrix());
  return Traversal::PRUNE;
}

List<Value>* RayshadeWriter::getParameterList(Object3D*) 
{
  List<Value>* parList = new List<Value>();
  return parList;
}

Traversal::Result RayshadeWriter::visit(Shared3D* shared) 
{ 
  RCString name(shared->getName());
  
  if (name.isEmpty()) {
    shared->setName(RCString("noname"));
    name = (RCString) shared->getName();
  }

  if (myLevel < myWriteDefLevel) {
    myOs << "name " << name << " ";
    printParameterList(getParameterList(shared));
    return Traversal::CONTINUE;
  } else {
    newLineIndent();
    myOs << "object " << name << " ";
    printParameterList(getParameterList(shared));
    incIndent();
    printObject3DAttributes(shared);
    decIndent();
    newLineIndent();
    return Traversal::PRUNE;
  }
  return Traversal::PRUNE;
}

List<Value>* RayshadeWriter::getParameterList(Shared3D*) 
{
  List<Value>* parList = new List<Value>();
  return parList;
}

Traversal::Result RayshadeWriter::visit(List3D* aggr) 
{ 
  if (myLevel < mySkipLevel) {
     return Traversal::CONTINUE;
  } else {  
    printParameterList(getParameterList(aggr));
    myOs << "list  ";
    incIndent();
    for(long i=0;i<aggr->countSubobject(); i++) {
      incLevel();
      dispatch(aggr->getSubobject(i));
      decLevel();
    }
    decIndent();
    newLineIndent();
    myOs << "end";
    newLineIndent();
    return Traversal::PRUNE;
  }
  return Traversal::PRUNE;
}

List<Value>* RayshadeWriter::getParameterList(List3D*) 
{
  List<Value>* parList = new List<Value>();
  return parList;
}

Traversal::Result RayshadeWriter::visit(Grid3D* aggr) 
{
  if (myLevel < mySkipLevel) {
     return Traversal::CONTINUE;
  } else {
    printParameterList(getParameterList(aggr));
    myOs << "grid 20 20 20  ";
    incIndent();
    for(long i=0;i<aggr->countSubobject(); i++) {
      incLevel();
      dispatch(aggr->getSubobject(i));
      decLevel();
    }
    decIndent();
    newLineIndent();
    myOs << "end";
    newLineIndent();
    return Traversal::PRUNE;
  }
  return Traversal::PRUNE;
}

List<Value>* RayshadeWriter::getParameterList(Grid3D*) 
{
  List<Value>* parList = new List<Value>();
  return parList;
}

Traversal::Result RayshadeWriter::visit(Camera3D*)
{
  return Traversal::UNKNOWN;
}

void RayshadeWriter::printCamera(const Camera3D* camera)
{
  if (camera->isOn()) {
    myOs << "/* Setting up viewing parameters */\n"
         << "/*-------------------------------*/\n";
    myOs << "eyep    "; 
    printVector(camera->getViewing()->getEye());
    myOs << "\nlookp ";
    printVector(camera->getViewing()->getLookat());
    myOs << "\nup    ";
    printVector(camera->getViewing()->getUp());
    myOs << "\nfov " << rtod(camera->getViewing()->getHFov());
  
    myOs << "\nbackground " << camera->getBackground().getRed()   << " "
                            << camera->getBackground().getGreen() << " "
                            << camera->getBackground().getBlue();
    myOs << "\nscreen " << camera->getViewing()->getResolutionX() << " "
                        << camera->getViewing()->getResolutionY() << "\n\n";
  }
}

List<Value>* RayshadeWriter::getParameterList(Camera3D*) 
{
  List<Value>* parList = new List<Value>();
  return parList;
}

Traversal::Result RayshadeWriter::visit(PointLight* light)
{
  if (light->isOn()) {
    myOs << "light " << light->getLuminance() << " point ";
	    printVector(light->getPosition());
    myOs << "\n\n";
  }

  return Traversal::PRUNE;
}

List<Value>* RayshadeWriter::getParameterList(PointLight* light) {
  List<Value>* parList = new List<Value>();

  Color col = light->getColor();
  parList->append(Value(light->getLuminance()));
  parList->append(Value(Vector3D(col.getRed(), col.getGreen(), 
                                 col.getBlue())));
  return parList;
}

Traversal::Result RayshadeWriter::visit(AmbientLight* light)
{
  newLineIndent();
  myOs << "ambientLight ";
  printParameterList(getParameterList(light));
  myOs << "{ ";
  if (light->isOn()) {
    myOs << "on; ";
  } else {
    myOs << "off; ";
  }
  myOs << "};";
  return Traversal::PRUNE;
}

List<Value>* RayshadeWriter::getParameterList(AmbientLight* light) {
  List<Value>* parList = new List<Value>();

  Color col = light->getColor();
  parList->append(Value(light->getLuminance()));
  parList->append(Value(Vector3D(col.getRed(), col.getGreen(), 
                                 col.getBlue())));
  return parList;
}

Traversal::Result RayshadeWriter::visit(Box3D* box)
{
  newLineIndent();
  myOs << "box";
  printTextureName(box->getTexture());
  printVector(box->getFrom());
  printVector(box->getTo());
  newLineIndent();

//  myOs << "box";
//  printParameterList(getParameterList(box));
//  
//  myOs << " {";
//  incIndent();
  printObject3DAttributes(box);
  decIndent();

  return Traversal::CONTINUE;
}

List<Value>* RayshadeWriter::getParameterList(Box3D* box) {
  List<Value>* parList = new List<Value>();

  parList->append(Value(box->getFrom()));
  parList->append(Value(box->getTo()));
  return parList;
}

Traversal::Result RayshadeWriter::visit(Cone3D* cone)
{
  myOs << "cone ";
  printTextureName(cone->getTexture());
  myOs << cone->getStartRadius();
  printVector(cone->getStart());
  myOs << cone->getEndRadius();
  printVector(cone->getEnd());
  newLineIndent(); 
  
  if (cone->isClosed()) {
    Vector3D n = cone->getEnd() - cone->getStart();
    
    if (!equal(cone->getStartRadius(), 0)) {
      myOs << "disc " << cone->getStartRadius();
      n.normalize();
      printVector(cone->getStart());
      printVector(n);
      newLineIndent(); 
    }
    if (!equal(cone->getEndRadius(), 0)) {
      myOs << "disc " << cone->getEndRadius();
      printVector(cone->getEnd());
      printVector(-n);
      newLineIndent(); 
    }
  }
  


//  myOs << "cone";
//  printParameterList(getParameterList(cone));
//  myOs << " {";
//  incIndent();
//  if (cone->isClosed()) {
//    myOs << "close; ";
//  } else {
//    myOs << "open; ";
//  }
  printObject3DAttributes(cone);
  decIndent();

  return Traversal::CONTINUE;
}

List<Value>* RayshadeWriter::getParameterList(Cone3D* cone) {
  List<Value>* parList = new List<Value>();

  parList->append(Value(cone->getStartRadius()));
  parList->append(Value(cone->getStart()));
  parList->append(Value(cone->getEndRadius())); 
  parList->append(Value(cone->getEnd()));
 
  return parList;
}

Traversal::Result RayshadeWriter::visit(Cylinder3D* cylinder)
{
  newLineIndent(); 
   
  myOs << "cylinder "; printTextureName(cylinder->getTexture());
  myOs << cylinder->getRadius();
  printVector(cylinder->getStart());
  printVector(cylinder->getEnd());   
  newLineIndent(); 
  
  if (cylinder->isClosed()) {
    Vector3D n = cylinder->getEnd() - cylinder->getStart();
    n.normalize();
    
    myOs << "disc " << cylinder->getRadius();
    printVector(cylinder->getStart());
    printVector(n); 
    newLineIndent(); 
    
    myOs << "disc " << cylinder->getRadius();
    printVector(cylinder->getEnd());
    printVector(-n);
    newLineIndent(); 
  }
  
  printObject3DAttributes(cylinder);
  decIndent();

  return Traversal::CONTINUE;
}

List<Value>* RayshadeWriter::getParameterList(Cylinder3D* cylinder) {
  List<Value>* parList = new List<Value>();

  parList->append(Value(cylinder->getRadius()));
  parList->append(Value(cylinder->getStart()));
  parList->append(Value(cylinder->getEnd()));
  return parList;
}

Traversal::Result RayshadeWriter::visit(Disc3D* disc)
{
  newLineIndent(); 
  myOs << "disc ";
  printTextureName(disc->getTexture());
  myOs << disc->getRadius() << " ";  printVector(disc->getCenter());
  myOs << " ";  printVector(disc->getNormal());
  incIndent();
  printObject3DAttributes(disc);
  decIndent();

  return Traversal::CONTINUE;
}

List<Value>* RayshadeWriter::getParameterList(Disc3D* disc) {
  List<Value>* parList = new List<Value>();

  parList->append(Value(disc->getRadius()));
  parList->append(Value(disc->getCenter()));
  parList->append(Value(disc->getNormal()));
  return parList;
}

Traversal::Result RayshadeWriter::visit(Polygon3D* poly)
{
  newLineIndent();
  myOs << "polygon "; printTextureName (poly->getTexture());
  printVector(poly->getVertices().item(0));
  myOs << "\n";
  
  for (long i=1; i<poly->getVertices().count(); i++) {
    myOs << "       "; 
    printVector(poly->getVertices().item(i));
    newLineIndent();
  }

  incIndent();
  printObject3DAttributes(poly);
  decIndent();
  
  return Traversal::CONTINUE;
}

List<Value>* RayshadeWriter::getParameterList(Polygon3D* poly) {
  List<Value>* parList = new List<Value>();

  for (long i=0; i<poly->getVertices().count(); i++) {
    parList->append(Value(poly->getVertices().item(i)));
  }
  return parList;
}


Traversal::Result RayshadeWriter::visit(Sphere3D* sphere)
{
  newLineIndent();
  myOs << "sphere ";
  printTextureName (sphere->getTexture()); 
  myOs << sphere->getRadius();
  printVector(sphere->getCenter());
  newLineIndent();

  incIndent();
  printObject3DAttributes(sphere);
  decIndent();

  return Traversal::CONTINUE;
}

List<Value>* RayshadeWriter::getParameterList(Sphere3D* sphere) {
  List<Value>* parList = new List<Value>();

  parList->append(Value(sphere->getRadius()));
  parList->append(Value(sphere->getCenter()));
  return parList;
}

Traversal::Result RayshadeWriter::visit(Text3D*)
{
  return Traversal::UNKNOWN;
  
//  newLineIndent();
//  myOs << "text";
//  //
//  // printParameterList(getParameterList(text));
//  // need special treatment of 3rd parameter as constant string here
//  //
//  myOs << "(" << Value(text->getHeight()) 
//       << ", "<< Value(text->getRadius())
//       << ", \"" << Value(text->getText()) << "\") ";
//  myOs << " {";
//  incIndent();
//  if (text->getFont() != NULL) {
//    RCString fontname(text->getFont()->getName());
//    if (!fontname.isEmpty()) {
//      newLineIndent();
//      myOs << "font \"" << fontname << "\";";
//    }
//  }
//  printObject3DAttributes(text);
//  decIndent();
//  myOs << "};";
//  
//  return Traversal::CONTINUE;
}

List<Value>* RayshadeWriter::getParameterList(Text3D* text) {
  List<Value>* parList = new List<Value>();

  parList->append(Value(text->getHeight()));
  parList->append(Value(text->getRadius()));
  parList->append(Value(text->getText()));
  return parList;
}

Traversal::Result RayshadeWriter::visit(Torus3D* torus)
{
  newLineIndent();
  myOs << "torus "; printTextureName(torus->getTexture());
  myOs << torus->getSweptRadius() << " " << torus->getTubeRadius() << " ";
  printVector(torus->getCenter());
  printVector(torus->getNormal());
  newLineIndent();

  printObject3DAttributes(torus);
  decIndent();
 
  return Traversal::CONTINUE;
}

List<Value>* RayshadeWriter::getParameterList(Torus3D* torus) {
  List<Value>* parList = new List<Value>();

  parList->append(Value(torus->getSweptRadius()));
  parList->append(Value(torus->getTubeRadius()));
  parList->append(Value(torus->getCenter()));
  parList->append(Value(torus->getNormal()));
  return parList;
}


Traversal::Result RayshadeWriter::visit(Triangle3D* triangle)
{
  newLineIndent();

  myOs << "triangle "; printTextureName(triangle->getTexture()); printVector(triangle->getVertex(0));
                       printVector(triangle->getNormal(0));
  newLineIndent();
  myOs << "        "; printVector(triangle->getVertex(1));
                      printVector(triangle->getNormal(1));
  newLineIndent();
  myOs << "        "; printVector(triangle->getVertex(2));
                      printVector(triangle->getNormal(2));
  newLineIndent();
  incIndent();
  printObject3DAttributes(triangle);
  decIndent();

  return Traversal::CONTINUE;
}

List<Value>* RayshadeWriter::getParameterList(Triangle3D* triangle) {
  List<Value>* parList = new List<Value>();
  parList->append(Value(triangle->getVertex(0)));
  parList->append(Value(triangle->getNormal(0)));
  parList->append(Value(triangle->getVertex(1)));
  parList->append(Value(triangle->getNormal(1)));
  parList->append(Value(triangle->getVertex(2)));
  parList->append(Value(triangle->getNormal(2)));

  return parList;
}

Traversal::Result RayshadeWriter::dispatch(Makeable* obj)
{
  tryConcrete(Triangle3D,   obj);
  tryConcrete(Torus3D,      obj);
  tryConcrete(Text3D,       obj);
  tryConcrete(Sphere3D,     obj);
  tryConcrete(Polygon3D,    obj);
  tryConcrete(Disc3D,       obj);
  tryConcrete(Cylinder3D,   obj);
  tryConcrete(Cone3D,       obj);
  tryConcrete(Box3D,        obj);
  tryConcrete(PointLight,   obj);
  tryConcrete(AmbientLight, obj);
  tryConcrete(Camera3D,     obj);
  tryConcrete(Shared3D,     obj);
  tryConcrete(List3D,       obj);
  tryConcrete(Grid3D,       obj);
  tryAbstract(Animation3D,  obj);
  tryAbstract(Object3D,     obj);
  
  return Traversal::CONTINUE;
}

void RayshadeWriter::incLevel() {
  myLevel++;
}

void RayshadeWriter::decLevel() {
  myLevel--;
}

void RayshadeWriter::adoptCamera(Camera3D* camera)
{
  if (camera == NULL) {
    Report::warning("[Renderer::adoptCamera] NULL pointer passed");
    return;
  }
    
  if (myCamera != NULL && myCamera != camera)
    delete myCamera;

  myCamera = camera; 
  myHasAdoptedCamera = true;
}

void RayshadeWriter::deleteCamera()
{
  if (myCamera != NULL) {
    delete myCamera;
    myCamera = NULL;
  }
  myHasAdoptedCamera = false;
}

bool RayshadeWriter::preprocessing()
{
  if (!Operation3D::preprocessing())
    return false;

  if (!myHasAdoptedCamera) {
    //
    // Collect all cameras in the world.
    //  
    Collector3DFor<Camera3D> camCollector;
    camCollector.execute(getWorld());
  
    //
    // Look for first camera in world, that is switched on.
    //
    if (myCamera != NULL) {
      delete myCamera;
      myCamera = NULL;
    }
      
    for (camCollector.first(); !camCollector.isDone(); camCollector.next())
      if (camCollector.getObject()->isOn()) {
        myCamera = camCollector.createTransformedObject(); 
        break;
      }
  }
  if (myCamera == NULL) {
    Report::warning("[RayshadeWriter::preprocessing] camera and/or light sources declaration missing");
    return false;
  }
  else
    return true;
}
