/*
 * $RCSfile: TriangleInterpolator.h,v $
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
 *  $Id: TriangleInterpolator.h,v 1.1 1996/09/13 08:06:43 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _TriangleInterpolator_H
#define _TriangleInterpolator_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/Vector3D.h"
#include "booga/base/Color.h"
#include "booga/object/Transform3D.h"
#include "booga/object/Texture3DContext.h"
#include "booga/component/AbstractTraversal3D.h"

class Viewing3D;
class Triangle3D;

//_________________________________________________________ TriangleInterpolator

class TriangleInterpolator {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  TriangleInterpolator();
  // TriangleInterpolator(const TriangleInterpolator&); // Use default version.
  
public:
  virtual ~TriangleInterpolator(); 

private:
  TriangleInterpolator& operator=(const TriangleInterpolator&);  
  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class TriangleInterpolatorOption
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setTraversal(AbstractTraversal3D* traversal); 
  // Need traversal to access path to object
  void setViewing(Viewing3D* viewing);
  // set current Viewing
  void setWorld(World3D* world);
  // set current world
  void setAmbientLightSources(const List<AmbientLight*>* lightSources);
  void setDirectedLightSources(const List<DirectedLight*>* lightSources);
  // set current light sources
  void setDefaultColor(const Color& color);
  const Color& getDefaultColor() const;
  // set/get default color for initialising texture context
  
  virtual TriangleInterpolator* copy() const = 0;
  // virtual "copy constructor"
  
  void init(Triangle3D* triangle);
  bool isDone() const;
  void next();
  // Iteration over Triangle
  
  void getSCPoint(int& x, int& y, Real& z) const;
  void getOCPoint(Vector3D& point) const;
  virtual void getColor(Color& color) = 0;
  // get Results

private: // template methods:
  virtual void doInit(int firstPoint) = 0;
  virtual void doComputeScanLine(Real startFactor, Real endFactor) = 0;
  void swapPoints(int i, int j);
  void nextScanLine();
  bool nextPoint();
  void computeScanLine();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  Texture3DContext myTextureContext;
  const AbstractTraversal3D* myTraversal;
  Triangle3D* myCurTriangle;
  
  // ----------------------- general stuff
private:
  const Viewing3D* myViewing;
  int mySizeX, mySizeY;
  Color myDefaultColor;
  bool myIsDone;            // Have we finished?

  // -----------------------nonlinear interpolation
protected:
  Real myAy1[3], myAy2[3];  // interp. factor for scanline increment.
  Real myDy1[3], myDy2[3];  // Increment for myAy1, myAy2, resp.
  Real myAx1, myAx2;        // interp. factor for scanline interpolation.
  Real myDx1, myDx2;        // Increment for myAx1, myAx2, resp.

  // ----------------------- algorithm dependent general
protected:
  char myLeftEdge, myRightEdge;      // Which edges are currently in use?
  char myStartVertex[3]; 
  char myEndVertex[3];               // Start/End Vertices of each edge.   
  
private:
  int myChangeDelta;  // Y position of middle point (change the deltas there!)
  int myLastVertex;   // Y position of last vertex
  enum { CLOCKWISE, COUNTERCLOCKWISE } 
       myOrientation; // Orientation of projected triangle

  // ----------------------- object coordinates
protected:
  Vector3D myOCPoints[3];
  Vector3D myOCNormals[3];
private:
  Vector3D myStartOCPoint, myEndOCPoint;  // Start/End of scanline

  // ----------------------- view coordinates
private:
  Vector3D myViewPoints[3];   // Applied view transformation
  Real myStartZ, myEndZ;      // start and End of scan 

  // ----------------------- screen coordinates
private:
  Vector3D mySCPoints[3];      // Applied view to screen transformation
  Vector3D myNSCPoints[3];     // normalized screen coordinates
  int mySCX, mySCY;            // Pixel
  Real myStartNSCX, myEndNSCX; // Unrounded coordinates 
  int myEndSCX;                // End of scan line
  Real myDeltaNSCX[3];         // Deltas for every edge
};

//______________________________________________________________________ INLINES

inline void TriangleInterpolator::setDefaultColor(const Color& color)
{
  myDefaultColor = color;
}

inline const Color& TriangleInterpolator::getDefaultColor() const
{
  return myDefaultColor;
}

inline void TriangleInterpolator::setAmbientLightSources(const List<AmbientLight*>* lightSources)
{
  myTextureContext.setAmbientLightSources(lightSources);
}

inline void TriangleInterpolator::setDirectedLightSources(const List<DirectedLight*>* lightSources)
{
  myTextureContext.setDirectedLightSources(lightSources);
}

inline void TriangleInterpolator::setTraversal(AbstractTraversal3D* traversal)
{
  myTraversal = traversal;
}

inline void TriangleInterpolator::setWorld(World3D* world)
{
  myTextureContext.setWorld(world);
}

#endif // _TriangleInterpolator_H
