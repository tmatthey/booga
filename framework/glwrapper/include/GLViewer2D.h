/*
 * $RCSfile: GLViewer2D.h,v $
 *
 * Display of a World2D object using the GLRasterizer component. The viewer 
 * allows panning (press left mouse button an move) and zooming (press middle 
 * mouse button and move).
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
 *  $Id: GLViewer2D.h,v 1.4 1996/08/01 11:59:52 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GLViewer2D_H
#define _GLViewer2D_H

#include "booga/base/StaticInit.h"
#include "booga/component/Operation2D.h"

class GLRasterizer;

//___________________________________________________________________ GLViewer2D

class GLViewer2D : public Operation2D {
declareRTTI(GLViewer2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // GLViewer2D();                           // Use default version.
  // GLViewer2D(const GLViewer2D&);          // Use default version.

public:
  // virtual ~GLViewer2D();                  // Use default version.

private:
  GLViewer2D& operator=(const GLViewer2D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GLViewer2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  static void initClass();
  // Do proper initialisation of static members.

private:
  static void displayCallback();
  static void keyboardCallback(unsigned char key, int x, int y);
  static void mouseCallback(int button, int state, int x, int y);
  static void motionCallback(int x, int y);
  static void reshapeCallback(int width, int height);

  static void pan(Real dx, Real dy);
  static void zoom(Real dx, Real dy);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool doExecute();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  static World2D* ourWorld;
  static GLRasterizer* ourRasterizer;

  enum MovingMode { NO_BUTTON_DOWN, LEFT_BUTTON_DOWN, MIDDLE_BUTTON_DOWN };
  static MovingMode ourMovingMode;

  static int ourOldX, ourOldY;
};

declareInitStatics(GLViewer2D);

#endif // _GLViewer2D_H

