/*
 * $RCSfile: ActionInfo.h,v $
 *
 * An action is defined by the startframe, the endframe, the repeats and 
 * the numbers waitframes between two repeats. 
 * 
 * Copyright (C) 1996, Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: ActionInfo.h,v 1.4 1996/11/18 15:43:22 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ActionInfo_H
#define _ActionInfo_H

#include "booga/base/Vector3D.h"
#include "booga/base/Vector2D.h"
#include "booga/object/Makeable.h"
#include "booga/nurbs/Nurbs3D.h"
#include "booga/object/InterpolationCurve3D.h"
#include "booga/animation/AnimationFunction.h"
class Nurbs3DEvaluator;
// ____________________________________________________________________ ActionInfo

class ActionInfo : public Makeable {
declareRTTI(ActionInfo);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  ActionInfo(Exemplar);
  ActionInfo();
  ActionInfo(Real startFrame, Real endFrame);
  ActionInfo(Real startFrame, Real endFrame, long times);
  ActionInfo(Real startFrame, Real endFrame, long times, Real wait);
  ActionInfo(const ActionInfo& action);       // copy

public:
  ~ActionInfo();

private:  
  ActionInfo& operator=(const ActionInfo&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class ActionInfo
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // to set the controling parameters of the action
  void setParameters(Real startFrame, Real endFrame, long times, Real wait);
  // to set the parameter of transformation
  void setScaleFactor(const Vector3D& scaleFactor, const RCString& function, Real start, Real end, Real step);
  void setDirection(const Vector3D& direction, const RCString& function, Real start, Real end, Real step);
  void setMorphing(Real alpha, const RCString& function, Real start, Real end, Real step);
  void setCycling(const RCString& function, Real start, Real end, Real step);
  void setAlpha(Real alpha, const RCString& function, Real start, Real end, Real step);
  void setShearFactor(const Vector2D& shearFactor, const RCString& function, Real start, Real end, Real step);
  void setAxis(const Vector3D& axis);
  void setCenter(const Vector3D& direction);  // optional
  void setBoundCenter();                      // optional
  void setTumblePath(Nurbs3D* adoptNurbs, const RCString& function, Real start, Real end, Real step);
  void setTumbleCenter(Nurbs3D* adoptNurbs);    // optional
  void setTumbleDirection(Nurbs3D* adoptNurbs); // optional
  void adoptTumblePath(InterpolationCurve3D* adoptCurve, const RCString& function, Real start, Real end, Real step);
  void adoptTumbleCenter(InterpolationCurve3D* adoptCurve);    // optional
  void adoptTumbleDirection(InterpolationCurve3D* adoptCurve); // optional
  
  // to test if the correct parameters are set
  bool isMorph() const;  
  bool isCycle() const;  
  bool isGrow() const;  
  bool isMove() const;  
  bool isTurn() const;
  bool isShear() const;  
  bool isTumble() const;  
 
  // to test if optional parameters are set
  bool isBound() const;  
  bool isTumbleRotate() const;  

  // to compute the value modeled by the motion function
  Real computeTicks(Real frame);   // with repeats and waits
  Real computeValue(Real frame);   // ignoring repeats and waits
 
  // to get the parameters to control an action
  Real getStartFrame() const;  
  Real getEndFrame() const;    
  Real getTimes() const;       
  Real getWait() const;        

  AnimationFunction* getAnimationFunction() const;
 
  // to get the parameters of tranfsformation
  Vector3D getScaleFactor() const;
  Vector3D getCenter() const;
  Vector3D getDirection() const;
  Vector3D getAxis() const;
  Real getAlpha() const;
  Vector2D getShearFactor() const;
  Vector3D getTumbleMove(Real u);      // with evalution of the NURBS,Curve
  Vector3D getTumbleCenter(Real u);    // with evalution of the NURBS,Curve
  Vector3D getTumbleDirection(Real u); // with evalution of the NURBS,Curve
  InterpolationCurve3D* getTumbleMove();      // with evalution of the Curve
  InterpolationCurve3D* getTumbleCenter();    // with evalution of the Curve
  InterpolationCurve3D* getTumbleDirection(); // with evalution of the Curve
  
private:
  // to create the motion function with the given parameters
  AnimationFunction* createFunction(const RCString& function, Real start, Real end, Real step);
 
  void clearAll();
    		       
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual RCString getKeyword() const; 
  virtual List<Value*>* createParameters();
  virtual void iterateAttributes(MakeableHandler *handler);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

private:

  // the parameters to control an action
  Real               myStartFrame;  // starting point of the action 
  Real               myEndFrame;    // end point of the action
  long               myTimes;       // number of repeats
  Real               myWait;        // waitframes between two repeats
 
  // the motion function
  AnimationFunction* myFunction; 
  
  // the parameters of transformation
  bool               myMorphingFlag;
  bool               myCyclingFlag;
  bool               myScaleFactorFlag;
  Vector3D           myScaleFactor;
  bool               myDirectionFlag;
  Vector3D           myDirection;
  bool               myAlphaFlag;
  Real               myAlpha;
  bool               myAxisFlag;
  Vector3D           myAxis;
  bool               myCenterFlag;
  Vector3D           myCenter;
  bool               myShearFactorFlag;
  Vector2D           myShearFactor;
  
  bool               myNurbsPathFlag;
  Nurbs3DEvaluator*  myNurbsPath;          // the translationpath
  bool               myNurbsCenterFlag;
  Nurbs3DEvaluator*  myNurbsCenter;        // the rotationcenter
  bool               myNurbsDirectionFlag;
  Nurbs3DEvaluator*  myNurbsDirection;     // the direction of the object defined
  bool                   myCurvePathFlag;
  InterpolationCurve3D*  myCurvePath;          // the translationpath
  bool                   myCurveCenterFlag;
  InterpolationCurve3D*  myCurveCenter;        // the rotationcenter
  bool                   myCurveDirectionFlag;
  InterpolationCurve3D*  myCurveDirection;     // the direction of the object
                                               // by the difference of center and direction
};                                          
//______________________________________________________________________ INLINES

inline Real ActionInfo::getStartFrame() const
{
  return myStartFrame;
}

inline Real ActionInfo::getEndFrame() const
{
  return myEndFrame;
}
 
inline Real ActionInfo::getTimes() const
{
  return myTimes;
}
 
inline Real ActionInfo::getWait() const
{
  return myWait;
}

inline bool ActionInfo::isMove() const
{
  return myDirectionFlag;
}

inline bool ActionInfo::isCycle() const
{
  return myCyclingFlag;
}

inline bool ActionInfo::isMorph() const
{
  return myMorphingFlag;
}

inline bool ActionInfo::isTurn() const
{
  return (myAxisFlag && myAlphaFlag);
}

inline bool ActionInfo::isGrow() const
{
  return myScaleFactorFlag;
}

inline bool ActionInfo::isShear() const
{
  return (myShearFactorFlag && myAxisFlag);
}

inline bool ActionInfo::isTumble() const
{
  return (myNurbsPathFlag || myCurvePathFlag);
}

inline bool ActionInfo::isBound() const
{
  return (!myCenterFlag);
}

inline bool ActionInfo::isTumbleRotate() const
{
  return ((myNurbsCenterFlag && myNurbsDirectionFlag) || (myCurveCenterFlag && myCurveDirectionFlag));
}

inline Vector3D ActionInfo::getScaleFactor() const
{
  return myScaleFactor;
}

inline Vector3D ActionInfo::getDirection() const
{
  return myDirection;
}

inline Vector3D ActionInfo::getCenter() const
{
  return myCenter;
}

inline Vector3D ActionInfo::getAxis() const
{
  return myAxis;
}

inline Real ActionInfo::getAlpha() const
{
  return myAlpha;
}

inline Vector2D ActionInfo::getShearFactor() const
{
  return myShearFactor;
}

inline Real ActionInfo::computeValue(Real frame)
{
  return myFunction->computeValue(myStartFrame, myEndFrame, frame);
}

inline InterpolationCurve3D* ActionInfo::getTumbleMove()
{ 
  return myCurvePath;
}

inline InterpolationCurve3D* ActionInfo::getTumbleCenter()
{ 
  return myCurveCenter;
}

inline InterpolationCurve3D* ActionInfo::getTumbleDirection()
{ 
  return myCurveDirection;
}

inline  AnimationFunction* ActionInfo::getAnimationFunction() const
{
  return myFunction;
} 

#endif // _ActionInfo_H

