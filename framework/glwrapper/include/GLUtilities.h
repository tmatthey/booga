/*
 * GLUtilities.h
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
 *  $Id: GLUtilities.h,v 1.8 1996/04/25 11:40:31 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GLUtilities_H
#define _GLUtilities_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/StaticInit.h"
#include "booga/base/RCString.h"

class AbstractPixmap;
class Viewing3D;
class GLAbstractBridge;

//__________________________________________________________________ GLUtilities

class GLUtilities  {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // GLUtilities();                               // Use default version.
private:
  // GLUtilities(const GLUtilities&);             // Use default version.

public:
  // virtual ~GLUtilities();                      // Use default version.

private:
  // GLUtilities& operator=(const GLUtilities&);  // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class GLUtilities
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  static void initClass();
  // do proper initialisation of static members

  static void adoptBridge(GLAbstractBridge* toolkit);
  //
  
public:
  static AbstractPixmap* createPixmapFromFramebuffer(AbstractPixmap* proto = NULL);
  // 
  // Copy the current content of the GL framebuffer to a BOOGA pixmap. The size
  // of the created pixmap corresponds to the settings of the viewport.
  //    width  = viewport.start.x - viewport.totalWidth
  //    height = viewport.start.y - viewport.totalHeight
  //
  // The "proto" parameter serves as a prototype for the type of pixmap to create.
  // If a NULL pointer is passed, the pixmap type as determined based on the 
  // entry in the configuration database.

  static bool isEventPending();
  // Checks for an entry (e.g. mouse click, etc.) in the event queue.

  static void swapBuffers();
  // Swap buffer in double buffer mode.
  
public:
  static void setupViewingMatrix(Viewing3D* viewing);
  
public:
  enum RenderingType { WIRE,   // wireframe mode
                       SOLID   // solid rendering mode
                     };

  static void drawCube(RenderingType type);
  // Draws a cube object with dimensions x:[-0.5, 0.5], y:[-0.5, 0.5]
  // and z:[-0.5,0.5].
  
  static void drawSphere(Real radius, int slices, int stacks, 
                         RenderingType type);
  // Draws a sphere of the given radius centered around the origin. The sphere
  // is subdivided around the z axis into slices and along the z axis into 
  // stacks (similar to lines of lomgitude and latitude).
                           
  static void drawCone(Real radiusStart, Real radiusEnd, Real height, bool isClosed, 
                       int slices, int stacks, RenderingType type);
  // Draws a cone object oriented along the z axis. The base of the cone is 
  // placed at z=0, and the top at z=height. The closed flags indicates whether
  // closing disc at the base and top are drawn.
  // A cone is subdivided around the z axis into slices, and along the z axis 
  // into stacks.
  
  static void drawTorus(Real sweptRadius, Real tubeRadius, int nsides, int rings, 
                        RenderingType type);
  // Draws a torus centered around the origin. The torus is subdivided around the
  // z axis into rings, and around each ring into nsides.

  static void drawText(const RCString& text); 
  // Draws the string using a 9x15 bitmap font.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  static GLAbstractBridge* ourToolkitBridge;
  // To delegate toolkit depend functions like swapBuffers() or isEventPending().
};

declareInitStatics(GLUtilities);

#endif // _GLUtilities_H

