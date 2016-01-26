/*
 * Viewing3D.h
 *
 * View transformation from 3-space to 2-space.
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
 *  $Id: Viewing3D.h,v 1.10 1997/09/19 07:15:16 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Viewing3D_H
#define _Viewing3D_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/Vector3D.h"
#include "booga/base/TransMatrix3D.h"
#include "booga/object/Ray3D.h"
#include "booga/object/Makeable.h"

/*____________________________________________________________________ Viewing3D
 *
 * Class Viewing3D implements a simple camera model. Four parameters are 
 * accepted:
 *
 *    eye    : eyepoint of the observer (position of the camera)
 *    lookat : where do we lookat (lookat - eye == look direction)
 *    up     : orientation
 *    fov    : field fo view (horizontal and vertical)
 */

class Viewing3D : public Makeable {
declareRTTI(Viewing3D); 
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Local types/enums
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
enum ViewPlane { 
  AUTOSELECT=1,
  XY_PLANE, 
  XZ_PLANE, 
  YZ_PLANE
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Viewing3D();
  // Viewing3D(const Viewing3D&);           // Use default version.

public:
  // virtual ~Viewing3D();                  // Use default version.

private:
  // Viewing3D& operator=(const Viewing3D);    // No assignments

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class Viewing3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setEye(const Vector3D& eye);
  const Vector3D& getEye() const;

  void setLookat(const Vector3D& lookat);
  const Vector3D& getLookat() const;

  void setUp(const Vector3D& up);
  const Vector3D& getUp() const;

  void setHFov(Real hFov);
  void setVFov(Real vFov);
  void setFov(Real hFov, Real vFov = -1);
  Real getHFov() const;
  Real getVFov() const;

  void setEyeSeparation(Real eyeSeparation);
  Real getEyeSeparation() const;

  void setResolution(int resX, int resY);
  int getResolutionX() const;
  int getResolutionY() const;
 
  void setView(const Vector3D& bbMin, const Vector3D& bbMax, 
               Real zoomFactor = 1.1, ViewPlane viewPlane = AUTOSELECT);
  // Setup viewing parameters regarding the provided bounding box (Given as 
  // Vectors min, max, representing the minimal and maximal vertices). As a
  // result all the objects within the bounding box will be projected on 
  // the screen. If zoomFactor < 1 we go closer to the bounding box, for
  // zoomFactor > 1 we step back.
  //   -> eye and lookat are altered.

  virtual Vector3D transformWorld2View(const Vector3D& p) const;

  virtual Vector3D transformWorld2Screen(const Vector3D& p) const = 0;
  virtual Vector3D transformView2Screen(const Vector3D& p) const = 0;
  virtual Vector3D transformView2NormalScreen(const Vector3D& p) const = 0;

  virtual Vector3D transformNormalScreen2Screen(const Vector3D& p) const;
  virtual Real transformNormalScreen2ScreenX(Real x) const;
  virtual Real transformNormalScreen2ScreenY(Real y) const;

  virtual void computeRayThrough(int x, int y, Ray3D& ray) const = 0;

  virtual Viewing3D* copy() const = 0;
  
  friend ostream& operator<<(ostream& os, const Viewing3D& view);

public:
  Vector3D getScreenDeltaU() const;  // size of screen pixel (x direction, WC)
  Vector3D getScreenDeltaV() const;  // size of screen pixel (y direction, WC)
  Vector3D getScreenOrigin() const;  // Position of screen origin (WC)
  // These functions are usually used in ray tracing applications.
  //
  //    Origin __
  //             ` _________
  //          /\  |         |
  //  Delta v |   | Screen  |   
  //          |   |         |  
  //              `---------'
  //                 ---->
  //                Delta u

  virtual bool buildView() const; 
  // Generate the ViewingMatrix.
  //   Returns:  true on success, 
  //             false if view and up direction or eye and look point
  //                   are identical
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void iterateAttributes(MakeableHandler* handler);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  bool myNeedInit;  // true -> buildView must be called to set up myViewMat
  Vector3D myEye;
  Vector3D myLookat;
  Vector3D myUp;
  Real myHFov;        // Radians
  Real myVFov;        // Radians 
  bool myComputeVFov; // Indicates, that the value of vFov has to be 
                      // computed in order to get an undistorted image.
  Real myEyeSeparation;
  int myResolutionX, myResolutionY;

  TransMatrix3D myViewMat;

  Real myHWVP;   // half of the width of the view plane
  Real myHHVP;   // half of the height of the view plane
  Vector3D myScreenDeltaU;
  Vector3D myScreenDeltaV;
  Vector3D myScreenOrigin;
  Real myXScreenOffset, myXScreenFactor;
  Real myYScreenOffset, myYScreenFactor;
};

//______________________________________________________________________ INLINES

inline const Vector3D& Viewing3D::getEye() const 
{ 
  return myEye; 
}

inline const Vector3D& Viewing3D::getLookat() const 
{ 
  return myLookat; 
}

inline const Vector3D& Viewing3D::getUp() const 
{ 
  return myUp; 
}

inline Real Viewing3D::getHFov() const 
{ 
  return myHFov; 
}

inline void Viewing3D::setEyeSeparation(Real eyeSeparation)
{
  myEyeSeparation = eyeSeparation;
}

inline Real Viewing3D::getEyeSeparation() const
{
  return myEyeSeparation;
}

inline int Viewing3D::getResolutionX() const 
{ 
  return myResolutionX; 
}

inline int Viewing3D::getResolutionY() const 
{ 
  return myResolutionY; 
}
 
#endif // _Viewing3D_H
