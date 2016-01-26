/*
 * $RCSfile: FaceItem.h,v $
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
 *  $Id: FaceItem.h,v 1.4 1997/02/06 14:42:29 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _FaceItem_H
#define _FaceItem_H

#include "booga/building/Face.h"

// ____________________________________________________________________ FaceItem

class FaceItem : public Face {
declareRTTI(FaceItem);
// enable RTTI support


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  FaceItem(Exemplar exemplar);
  FaceItem();
  FaceItem(const FaceItem& faceitem);
  FaceItem(const Vector2D& from,const Vector2D& to, long column, long row);

public:
  virtual ~FaceItem();    
  
private:  
  FaceItem& operator=(const FaceItem&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class FaceItem
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Object3D* getObject() const;
  Object3D* orphanObject();

  void addVertex(const Vector3D& vertex);
  void setVertices(const List<Vector3D>& vertices);
  const List<Vector3D>& getVertices() const;
  List<Vector3D> orphanVertices();

  void holeOn();
  void holeOff();
  bool isHole() const;

  void wallOn();
  void wallOff();
  bool isWall() const;

  void itemBottomRow();
  bool isItemBottomRow() const;
  void itemBothRow();
  bool isItemBothRow() const;
  void itemInsideRow();
  bool isItemInsideRow() const;
  void itemTopRow();
  bool isItemTopRow() const;

  void itemLeftCol();
  bool isItemLeftCol() const;
  void itemBothCol();
  bool isItemBothCol() const;
  void itemInsideCol();
  bool isItemInsideCol() const;
  void itemRightCol();
  bool isItemRightCol() const;
  
  void setDisplacement(const Vector2D& point);
  const Vector2D& getDisplacement()const;

  List<Vector3D> getObjectHole(Building* building) const;  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Face
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual bool isFilled() const;
  virtual List<List<Vector3D> > getAlternativeHoles(Building* building) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual RCString getKeyword() const;
  virtual List<Value*>* createParameters();
  virtual void iterateAttributes(MakeableHandler* handler);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* copy() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class BuildingObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual Object3D* doCreateSubject(Building* building) const;  

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 private:
  Object3D*      myObject;       // Local object.
  List<Vector3D> myVertices;     // Vertices of the hole with z=0 !!!
  bool           myHoleFlag;     
  bool           myWallFlag;     
  bool           myItemLeft;     
  bool           myItemRight;     
  bool           myItemBottom;     
  bool           myItemTop;     
  Vector2D       myDisplacement; // The Displacement of the object
};

//______________________________________________________________________ INLINES

inline Object3D* FaceItem::getObject() const 
{
  return myObject;
}

inline const List<Vector3D>& FaceItem::getVertices() const
{
  return myVertices;
}

inline void FaceItem::setDisplacement(const Vector2D& point)
{
  myDisplacement = point;
}

inline const Vector2D& FaceItem::getDisplacement()const
{
  return myDisplacement;
}

inline void FaceItem::holeOn()
{
  myHoleFlag = true;
  myWallFlag = true;
}

inline void FaceItem::holeOff()
{
  myHoleFlag = false;
}

inline bool FaceItem::isHole() const
{
  return myHoleFlag;
}

inline void FaceItem::wallOn()
{
  myWallFlag = true;
}

inline void FaceItem::wallOff()
{
  myWallFlag = false;
  myHoleFlag = false;
}

inline bool FaceItem::isWall() const
{
  return myWallFlag;
}

inline void FaceItem::itemInsideCol()
{
  myItemLeft   = false;     
  myItemRight  = false;      
}

inline bool FaceItem::isItemInsideCol() const
{
  return (!myItemLeft) && (!myItemRight);
}

inline void FaceItem::itemBothCol()
{
  myItemLeft   = true;     
  myItemRight  = true;      
}

inline bool FaceItem::isItemBothCol() const
{
  return myItemLeft && myItemRight;
}

inline void FaceItem::itemLeftCol()
{
  myItemLeft   = true;     
  myItemRight  = false;      
}

inline bool FaceItem::isItemLeftCol() const
{
  return (myItemLeft) && (!myItemRight);
}

inline void FaceItem::itemRightCol()
{
  myItemLeft   = false;     
  myItemRight  = true;      
}

inline bool FaceItem::isItemRightCol() const
{
  return (!myItemLeft) && myItemRight;
}



inline void FaceItem::itemInsideRow()
{
  myItemBottom   = false;     
  myItemTop  = false;      
}

inline bool FaceItem::isItemInsideRow() const
{
  return (!myItemBottom) && (!myItemTop);
}

inline void FaceItem::itemBothRow()
{
  myItemBottom   = true;     
  myItemTop  = true;      
}

inline bool FaceItem::isItemBothRow() const
{
  return myItemBottom && myItemTop;
}

inline void FaceItem::itemBottomRow()
{
  myItemBottom   = true;     
  myItemTop  = false;      
}

inline bool FaceItem::isItemBottomRow() const
{
  return (myItemBottom) && (!myItemTop);
}

inline void FaceItem::itemTopRow()
{
  myItemBottom   = false;     
  myItemTop  = true;      
}

inline bool FaceItem::isItemTopRow() const
{
  return (!myItemBottom) && myItemTop;
}

inline bool FaceItem::isFilled() const
{
  return isWall();
}

#endif // _FaceItem_H




