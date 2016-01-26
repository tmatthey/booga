/*
 * $RCSfile: GLViewer3D.h,v $
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
 *  $Id: GLViewer3D.h,v 1.5 1996/08/04 14:24:50 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GLViewer3D_H
#define _GLViewer3D_H

#include "booga/base/StaticInit.h"
#include "booga/base/Arcball.h"
#include "booga/component/Operation3D.h"
#include "booga/glwrapper/GLRenderer.h"

//___________________________________________________________________ GLViewer3D

class GLViewer3D : public Operation3D {
declareRTTI(GLViewer3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // GLViewer3D();                           // Use default version.
  // GLViewer3D(const GLViewer3D&);          // Use default version.

public:
  // virtual ~GLViewer3D();                  // Use default version.

private:
  GLViewer3D& operator=(const GLViewer3D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GLViewer3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  static void setRenderingQuality(GLRenderer::RenderingQuality quality);
  
public:
  static void initClass();
  // do proper initialisation of static members

private:
  static void displayCallback();
  static void keyboardCallback(unsigned char key, int x, int y);
  static void mouseCallback(int button, int state, int x, int y);
  static void motionCallback(int x, int y);
  static void reshapeCallback(int width, int height);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool doExecute();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  static World3D* ourWorld;
  static GLRenderer* ourRenderer;
  static Arcball ourArcball;

  enum MovingMode { NO_BUTTON_DOWN,     // No    mouse button pressed
                    LEFT_BUTTON_DOWN,   // Left        ""
                    MIDDLE_BUTTON_DOWN  // Right       ""
                  };

  static MovingMode ourMovingMode;
};

declareInitStatics(GLViewer3D);

#endif // _GLViewer3D_H

