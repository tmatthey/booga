/*
 * $RCSfile: convex.C,v $
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
 *  $Id: convex.C,v 1.6 1996/08/01 11:59:33 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <stdlib.h> // drand48(), srand48(), atoi()
#include <time.h>   // time()
#include <cstring>

#include <booga/base/RCString.h>

#include <booga/object/Point2D.h>
#include <booga/object/Circle2D.h>
#include <booga/object/List2D.h>
#include <booga/object/World2D.h>
#include <booga/object/Camera2D.h>

#include <booga/component/ConvexHull2D.h>

#include <booga/glwrapper/GLConstantTexture2D.h>
#include <booga/glwrapper/GLViewer2D.h>

//
// Create world containing 'numPoints' Point2D objects placed at random
// positions (coordinates are in the range [0,1), [0,1)).
//
static World2D* createRandomWorld(int numPoints)
{
  World2D* createdWorld = new World2D;
  List2D* pointSet = new List2D;;

  for (int i=0; i<numPoints; i++)
    pointSet->adoptObject(new Point2D(Vector2D(drand48(), drand48())));

  pointSet->appendTexture(new GLConstantTexture2D(Color(1, 1, 1)));
  createdWorld->getObjects()->adoptObject(pointSet);

  //
  // Add camera to the world.
  //
  Camera2D* camera = new Camera2D;
  camera->getViewing()->setResolution(600, 600);
  camera->getViewing()->setWindow(Vector2D(-0.5, -0.5), Vector2D(2, 2));
  camera->setBackground(Color(.0, .21, .55));
  createdWorld->getObjects()->adoptObject(camera);
  createdWorld->getObjects()->computeBounds();
  
  return createdWorld;
}

static void usage(const RCString& name)
{
    std::cerr << "Usage: " << name << " [-h] [numPoints]\n";
    std::cerr << " where:\n";
    std::cerr << "   -h        : (optional) This message.\n";
    std::cerr << "   numPoints : (optional) number of random points to be generated\n";
}

int main(int argc, char* argv[])
{
  //
  // Parse command line.
  //
  if ((argc == 2 && !strcmp(argv[1], "-h")) || argc>2) {
    usage(argv[0]);
    exit(0);
  }
  
  int numPoints = 100;
  if (argc > 1) 
    numPoints = atoi(argv[1]);

  //
  // Initialize random number generator.
  //
  long now;
  time(&now); 
  srand48(now % 37);
  
  World2D* world = createRandomWorld(numPoints);

  //
  // Compute the convex hull.
  // 
  ConvexHull2D convex;
  convex.adoptTexture(new GLConstantTexture2D(Color(1,0,0)));
  convex.execute(world);
  
  //
  // Display the result.
  //
  GLViewer2D viewer;
  viewer.execute(world);
  
  delete world;
  
  return 1;
}
