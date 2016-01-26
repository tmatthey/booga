/*
 * $RCSfile: bsdlWriter.C,v $ 
 *
 * Copyright (C) 1996-97, Andrey Collison <collison@iam.unibe.ch>
 *                        Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: bsdlWriter.C,v 1.5 1996/11/28 13:50:32 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <string.h>  // strcmp()
#include <stdlib.h>  // atoi()

#include "booga/base/RCString.h"
#include "booga/base/BoundingBox.h"
#include "booga/base/Geometry3D.h"
#include "booga/object/Shared3D.h"
#include "booga/object/Texture3D.h"
#include "booga/object/Triangle3D.h"
#include "booga/object/List3D.h"
#include "booga/object/Grid3D.h"
#include "booga/object/Polygon3D.h"
#include "booga/object/Ray3D.h"
#include "booga/object/Ray3DFactory.h"
#include "booga/building/Building.h"
#include "booga/component/Parser3D.h"
#include "booga/component/BSDLParserInit.h"
#include "booga/component/PrintWorld3D.h"
#include "booga/component/ConfigurationHandlers.h"
#include "booga/component/BSDL3DWriter.h"
#include "booga/component/SingleFileStore.h"
#include "booga/component/MultiFileStore.h"

static void usage(const RCString& name);
static void parseCmdLine(int argc, char* argv[], RCString& in0, RCString& in1, RCString& in2, RCString& out);

int main(int argc, char* argv[])
{
  // 
  //  Setup world.
  // -----------------------------------------------------------
  // Configuration::setOption(Name("Report.ErrorStream.Filename"),Name("/dev/console"));
  // Configuration::setOption(Name("Report.ErrorStream"),Name("file"));
  Configuration::setOption(Name("Report.ErrorStream"),Name("cerr"));
  
  initBSDLParserGlobalNS();
  initBSDLParser3DNS();
  
  RCString in0, in1, in2, out;

  parseCmdLine(argc, argv, in0, in1, in2,  out);

  //
  // Read scene
  //
  World3D* world0 = new World3D;
  World3D* world1 = new World3D;
  World3D* world2 = new World3D;
  Parser3D parser;
  parser.setFilename(in0);
  std::cerr << "Reading curves. " << std::endl;
  parser.execute(world0);
  parser.setFilename(in1);
  std::cerr << "Reading holes. " << std::endl;
  parser.execute(world1);
  parser.setFilename(in2);
  std::cerr << "Reading buildings. " << std::endl;
  parser.execute(world2);

  BoundingBox bounds;  
  long j,i,count;
  List<Vector3D> tmp,mesh;
  List<List<Vector3D> > holes;
  Object3D* obj;
  Polygon3D* polygon;
  Geometry3D::Triangle triangle;      
  Geometry3D::Triangulation* triangulation;
  Vector3D a,b,c;
  Real z;
  Grid3D* poly;
  Aggregate3D* agg;
  List3D* terrain = new List3D;
  Building* building;
  Ray3D* ray;
  Texture3D* col1 = NULL;
  Texture3D* col2 = NULL;
  
  // collect all polygons on the first level
  agg = world0->orphanObjects();
  i = 0;
  count = 0;
  while(agg->countSubobject()){
    obj = agg->getSubobject(0);
    agg->orphanObject(obj);
    polygon = dynamic_cast<Polygon3D*>(obj);
    if (polygon){
      if (col1 == NULL && polygon->getTexture())
        col1 = polygon->getTexture()->copy(); 
      tmp = polygon->getVertices();
      // remove near points
      j = 0;
      while (j < tmp.count()){
        if (tmp.item(j).equal(tmp.item((j+1) % tmp.count()),.5)){
          tmp.remove(j);
          j = 0;
        }
        else
          j++;
      }  
      for(j=0;j<tmp.count();j++){
        mesh.append(tmp.item(j));
        bounds.expand(tmp.item(j));
      }
      count++;
    }
    
    delete obj;
    
    i++;
  }
  delete world0;
  delete agg;
  std::cerr << "Number of curves: " << count << std::endl;

  // get the holes
  agg = world1->orphanObjects();
  i = 0;
  while(agg->countSubobject()){
    obj = agg->getSubobject(0);
    agg->orphanObject(obj);
    polygon = dynamic_cast<Polygon3D*>(obj);
    if (polygon){ 
      tmp = polygon->getVertices();
      // remove near points
      j = 0;
      if (polygon->getTexture())
        col2 = polygon->getTexture()->copy(); 
      else
        col2 = NULL;
        
      while (j < tmp.count()){
        if (tmp.item(j).equal(tmp.item((j+1) % tmp.count()),.5)){
          tmp.remove(j);
          j = 0;
        }
        else
          j++;
      }  
      for(j=0;j<tmp.count();j++)
        bounds.expand(tmp.item(j));
      
      triangulation = Geometry3D::createPolygonTriangulation(tmp,polygon->getHoles());
      if (triangulation) {
        poly = new Grid3D(20,20,20);
        poly->appendTexture(col2);
        for(j=0; j < triangulation->myTriangleList.count();j++){
          triangle = triangulation->myTriangleList.item(j);
          a = triangulation->myPoints.item(triangle.myIndex1);
          b = triangulation->myPoints.item(triangle.myIndex2);
          c = triangulation->myPoints.item(triangle.myIndex3);
          if (Geometry3D::area(a,b,c) > EPSILON){  
            if (Geometry3D::normal(a,b,c).z() >=0)  
              poly->adoptObject(new Triangle3D(a,b,c));
            else
              poly->adoptObject(new Triangle3D(a,c,b));
          }
        }
        delete triangulation;
        terrain->adoptObject(poly);
      }      
      holes.append(tmp);  
    }    
    delete obj;
    i++;
  }
  std::cerr << "Number of holes: " << holes.count() << std::endl;
  delete world1;
  delete agg;
  
  // compute the mesh
  if (mesh.count() > 0){
    a = bounds.getMin() - Vector3D(10,10,0);
    b = bounds.getMax() + Vector3D(10,10,0);
    tmp.removeAll();      
    tmp.append(Vector3D(a.x(),a.y(),b.z()));
    tmp.append(Vector3D(b.x(),a.y(),b.z()));
    tmp.append(Vector3D(b.x(),b.y(),b.z()));
    tmp.append(Vector3D(a.x(),b.y(),b.z()));
    triangulation = Geometry3D::createPolygonTriangulation(tmp, holes,mesh);
    if (triangulation) {
      poly = new Grid3D(20,20,20);
      poly->appendTexture(col1);
      for(j=0; j < triangulation->myTriangleList.count();j++){
        triangle = triangulation->myTriangleList.item(j);
        a = triangulation->myPoints.item(triangle.myIndex1);
        b = triangulation->myPoints.item(triangle.myIndex2);
        c = triangulation->myPoints.item(triangle.myIndex3);
        if (Geometry3D::area(a,b,c) > EPSILON){
          if (Geometry3D::normal(a,b,c).z() >=0)  
            poly->adoptObject(new Triangle3D(a,b,c));
          else
            poly->adoptObject(new Triangle3D(a,c,b));
        }
      }
      delete triangulation;
      terrain->adoptObject(poly);
    }          
  }  
  terrain->computeBounds();
  
  // collect all buildings on the first level
  agg = world2->getObjects();
  count = 0;
  b = Vector3D(0,0,-1);
  a = Vector3D(0,0,10+bounds.getMax().z());
  for(i=0;i<agg->countSubobject();i++){
    obj = agg->getSubobject(i);
    building = dynamic_cast<Building*>(obj);
    if (building){ 
      tmp = building->getVertices();
      for(j=0;j<tmp.count();j++){
        c = tmp.item(j)*(building->getTransform().getTransMatrix());
        ray = Ray3DFactory::createRay(a+Vector3D(c.x(),c.y(),0),b);
        if (terrain->intersect(*ray) && (j == 0 || c.z() - ray->getHitPoint().z() > z))
          z = c.z()-ray->getHitPoint().z();
        delete ray;       
      }
      building->addTransform(TransMatrix3D::makeTranslate(0,0,-z));
      count++;
    }    
  }
  std::cerr << "Number of buildings: " << count << std::endl;

  
  world2->getObjects()->adoptObject(terrain);
  //
  // Print world
  //
  // PrintWorld3D printer(cout);
  // printer.apply(world3D);  
   
  //
  // Write BSDL format.
  //

  DocumentStore* docuStore = new SingleFileStore(out);

  BSDL3DWriter writer(*docuStore);
  writer.execute(world2);

  delete world2;

  return 0;
}

void parseCmdLine(int argc, char* argv[], RCString& in0, RCString& in1, RCString& in2, RCString& out)
{
  if ((argc == 2 && !strcmp(argv[1], "-h")) || argc > 5 || argc < 4) {
    usage(argv[0]);
    exit(0);
  }

  in0 = argv[1];
  in1 = argv[2];
  in2 = argv[3];
  if (argc == 5)
    out = argv[4]; 
}

void usage(const RCString& name)
{
    std::cerr << "Usage: " << name << " in-file1 in-file2 in-file3 [out-file]]\n";
    std::cerr << " where:\n";
    std::cerr << "  in-file 1      : filename of input 3D-Model\n";
    std::cerr << "  in-file 2      : filename of input holes\n";
    std::cerr << "  in-file 3      : filename of input building\n";
    std::cerr << "  out-file       : (optional) filename of output\n";
}

