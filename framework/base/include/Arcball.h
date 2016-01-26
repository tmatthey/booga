/*
 * $RCSfile: Arcball.h,v $
 *
 * Implementaion of the Arcball Rotation Control by Ken Shoemake. The code 
 * presented here is adapted from the article 
 *    "Arcball Rotation Control"
 *       by Ken Shoemake, shoemake@graphics.cis.upenn.edu
 *       in "Graphics Gems IV", Academic Press, 1994
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
 *  $Id: Arcball.h,v 1.2 1996/08/04 14:24:48 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Arcball_H
#define _Arcball_H

#include "booga/base/Quaternion.h"
#include "booga/base/Vector3D.h"
#include "booga/base/TransMatrix3D.h"

/*______________________________________________________________________ Arcball
 *
 * Usage:
 *
 *        Arcball ball;
 *        World3D world;
 *        
 *        switch (readEvent()) {
 *          case MOUSE_X:
 *            pos.x() = getValue();
 *            break;
 *          case MOUSE_Y:
 *            pos.y() = getValue();
 *            break;
 *          case LEFT_DOWN:
 *            ball.beginDrag();
 *            break;
 *          case LEFT_UP:
 *            ball.endDrag();
 *            break;
 *        }
 *        ball.mouse(pos);
 *        ball.update();
 *        world.preTransform(ball.value());
 *        drawScene();
 */
 
class Arcball {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Local types
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

enum AxisSet { NoAxes, CameraAxes, BodyAxes, OtherAxes, NSets };

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Arcball();
private:
  Arcball(const Arcball&);             // No copies.

public:
  // ~Arcball();                       // Use default version.

private:
  Arcball& operator=(const Arcball&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class Arcball
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void place(const Vector3D& center, Real radius);
  // Set the center and size of the controller.

  void mouse(Real x, Real y);
  // Incorporate new mouse position. 

  void useSet(Arcball::AxisSet axisSet);
  // Choose a constraint set, or none. 

  void update();
  // Using vDown, vNow, dragging, and axisSet, compute rotation etc. 

  TransMatrix3D value() const;
  // Return rotation matrix defined by controller use. 

  void beginDrag();
  void endDrag();
  // Begin and end drag sequence.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
    Vector3D myCenter;
    Real myRadius;
    Quaternion myQNow, myQDown, myQDrag;
    Vector3D myVNow, myVDown, myVFrom, myVTo, myVrFrom, myVrTo;
    TransMatrix3D myMNow, myMDown;
    bool myDragging;

    // Constraints not implemented yet!
    //    typedef Real* ConstraintSet;
    //    ConstraintSet mySets[NSets];
    //    int setSizes[NSets];
    //    AxisSet myAxisSet;
    //    int myAxisIndex;
};

//______________________________________________________________________ INLINES

#endif // _Arcball_H

