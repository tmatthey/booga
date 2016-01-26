/*
 * FaceItemAttr.C
 *
 * Copyright (C) 1994-96, University of Berne, Switzerland
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
 */

#include "booga/base/Value.h"
#include "booga/base/Report.h"
#include "booga/building/FaceItemAttr.h"
#include "booga/building/FaceItem.h"

//_________________________________________________________________ FaceItemAttr

implementRTTI(FaceItemAttr, ObjectAttr);

//______________________________________________________ FaceItemAttrItemLeftCol

implementRTTI(FaceItemAttrItemLeftCol, FaceItemAttr);

Makeable* FaceItemAttrItemLeftCol::make(RCString& errMsg,
                                        const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new FaceItemAttrItemLeftCol(anExemplar);
}

void FaceItemAttrItemLeftCol::setAttribute(FaceItem* faceitem) const
{
  faceitem->itemLeftCol();
}

//_____________________________________________________ FaceItemAttrItemRightCol

implementRTTI(FaceItemAttrItemRightCol, FaceItemAttr);

Makeable* FaceItemAttrItemRightCol::make(RCString& errMsg,
                                         const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new FaceItemAttrItemRightCol(anExemplar);
}

void FaceItemAttrItemRightCol::setAttribute(FaceItem* faceitem) const
{
  faceitem->itemRightCol();
}

//____________________________________________________ FaceItemAttrItemInsideCol

implementRTTI(FaceItemAttrItemInsideCol, FaceItemAttr);

Makeable* FaceItemAttrItemInsideCol::make(RCString& errMsg,
                                          const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new FaceItemAttrItemInsideCol(anExemplar);
}

void FaceItemAttrItemInsideCol::setAttribute(FaceItem* faceitem) const
{
  faceitem->itemInsideCol();
}

//______________________________________________________ FaceItemAttrItemBothCol

implementRTTI(FaceItemAttrItemBothCol, FaceItemAttr);

Makeable* FaceItemAttrItemBothCol::make(RCString& errMsg,
                                        const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new FaceItemAttrItemBothCol(anExemplar);
}

void FaceItemAttrItemBothCol::setAttribute(FaceItem* faceitem) const
{
  faceitem->itemBothCol();
}

//____________________________________________________ FaceItemAttrItemBottomRow

implementRTTI(FaceItemAttrItemBottomRow, FaceItemAttr);

Makeable* FaceItemAttrItemBottomRow::make(RCString& errMsg,
                                          const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new FaceItemAttrItemBottomRow(anExemplar);
}

void FaceItemAttrItemBottomRow::setAttribute(FaceItem* faceitem) const
{
  faceitem->itemBottomRow();
}

//_______________________________________________________ FaceItemAttrItemTopRow

implementRTTI(FaceItemAttrItemTopRow, FaceItemAttr);

Makeable* FaceItemAttrItemTopRow::make(RCString& errMsg,
                                       const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new FaceItemAttrItemTopRow(anExemplar);
}

void FaceItemAttrItemTopRow::setAttribute(FaceItem* faceitem) const
{
  faceitem->itemTopRow();
}

//____________________________________________________ FaceItemAttrItemInsideRow

implementRTTI(FaceItemAttrItemInsideRow, FaceItemAttr);

Makeable* FaceItemAttrItemInsideRow::make(RCString& errMsg,
                                          const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new FaceItemAttrItemInsideRow(anExemplar);
}

void FaceItemAttrItemInsideRow::setAttribute(FaceItem* faceitem) const
{
  faceitem->itemInsideRow();
}

//______________________________________________________ FaceItemAttrItemBothRow

implementRTTI(FaceItemAttrItemBothRow, FaceItemAttr);

Makeable* FaceItemAttrItemBothRow::make(RCString& errMsg,
                                        const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new FaceItemAttrItemBothRow(anExemplar);
}

void FaceItemAttrItemBothRow::setAttribute(FaceItem* faceitem) const
{
  faceitem->itemBothRow();
}
//_________________________________________________ FaceItemAttrDisplacement

implementRTTI(FaceItemAttrDisplacement, FaceItemAttr);

FaceItemAttrDisplacement::FaceItemAttrDisplacement(const Vector2D& displacement)
: myDisplacement(displacement)
{}

Makeable* FaceItemAttrDisplacement::make(RCString& errMsg,
                                             const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector2D, displacement);

  return new FaceItemAttrDisplacement(displacement);
}

void FaceItemAttrDisplacement::setAttribute(FaceItem* faceItem) const
{
  faceItem->setDisplacement(myDisplacement);
}

//_________________________________________________ Polygon3DAttrHole

implementRTTI(FaceItemAttrHole, FaceItemAttr);

FaceItemAttrHole::FaceItemAttrHole(const List<Vector3D>& vertices)
: myVertices(vertices)
{
}

FaceItemAttrHole::FaceItemAttrHole()
{
}

Makeable* FaceItemAttrHole::make(RCString& errMsg,
                                             const List<Value*>* parameters) const
{
  List<Vector3D> vertices;
  Vector3D vertex;
  if (parameters != NULL) {
    for (int i=1; i<=parameters->count(); i++){
      getParameter(i, Vector2D, vertex2D);
      vertex = Vector3D(vertex2D.x(),vertex2D.y(),0);
      if (i > 1) {
        if (vertices.item(i-2) == vertex) {
          ostrstream os;
          os << "[FaceItemAttrHole::make] two consecutive vertices ("
             << vertex << ") must not have the same value";
          Report::recoverable(os);
          return NULL;
        }
     }
     vertices.append(vertex);
    }
  }
  return new FaceItemAttrHole(vertices);
}

void FaceItemAttrHole::setAttribute(FaceItem* faceItem) const
{
  faceItem->setVertices(myVertices);
  faceItem->holeOn();
}

//_____________________________________________________________ FaceItemAttrwallOff

implementRTTI(FaceItemAttrwallOff, FaceItemAttr);

Makeable* FaceItemAttrwallOff::make(RCString& errMsg,
                                 const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new FaceItemAttrwallOff(anExemplar);
}

void FaceItemAttrwallOff::setAttribute(FaceItem* faceitem) const
{
  faceitem->wallOff();
}

//______________________________________________________________ FaceItemAttrWallOn

implementRTTI(FaceItemAttrWallOn, FaceItemAttr);

Makeable* FaceItemAttrWallOn::make(RCString& errMsg,
                                const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new FaceItemAttrWallOn(anExemplar);
}

void FaceItemAttrWallOn::setAttribute(FaceItem* faceitem) const
{
  faceitem->wallOn();
}
