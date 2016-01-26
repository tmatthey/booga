/*
 * $RCSfile: Animation3D.h,v $
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: Animation3D.h,v 1.6 1996/11/13 09:37:59 collison Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _Animation3D_H
#define _Animation3D_H

#include "booga/base/List.h"
#include "booga/object/Object3D.h"

class ActionInfo;

//_________________________________________________________________ Animation3D

class Animation3D : public Object3D {
declareRTTI(Animation3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:  
  Animation3D();
  Animation3D(Exemplar);
  Animation3D(const Animation3D& animation);

public:
  virtual ~Animation3D();

private:
  Animation3D& operator=(const Animation3D&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Animation3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  bool frame(Real frame); // executes all actions of the object
                          
  void turnOn();          // enables the animation
  void turnOff();         // disables the animation
  bool isOn() const;      // to test if the animation is enable
  void adoptAction(ActionInfo* action); // to add an action to the obejct
  const List<ActionInfo*>& getActions() const;
  // ActionInfo* orphanAction();    
  
protected:
  virtual bool doFrame(Real frame)=0;               // does all executions of action 
  bool doTransform(const TransMatrix3D& transform); // does the transformation if needed
                                                    // if a new animationobject doesn't use TransMatrix3D
                                                    // so overload this function!
    
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* makeUnique(Path3D* path = NULL, bool shared = false);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual long countSubobject() const;
  virtual Object3D* getSubobject(long index);
  virtual void adoptObject(Object3D *obj);

protected:
  virtual void doComputeBounds();
private:
  virtual bool doIntersect(Ray3D& ray);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual void iterateAttributes(MakeableHandler *handler);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  Object3D* myAnimatedObjects;     // the animated object
  List<ActionInfo*> myActionList;  // list of actions
  
private:
  bool myIsOn;                     // enable-flag 
  TransMatrix3D myLastTransform;   // to cache the last done transformation
  bool myFirst;                    // 
};

//______________________________________________________________________ INLINES
 
inline void  Animation3D::turnOn()
{
  myIsOn = true;
}
 
inline void  Animation3D::turnOff()
{
  myIsOn = false;
}
 
inline bool Animation3D::isOn() const
{
  return myIsOn;
}

inline const List<ActionInfo*>& Animation3D::getActions() const
{
  return myActionList;
}


#endif // _Animation3D_H
