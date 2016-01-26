/*
 * FaceItemAttr.h
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

#ifndef _FaceItemAttr_H
#define _FaceItemAttr_H

#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"

class FaceItem;
class RCString;

//_________________________________________________________________ FaceItemAttr

class FaceItemAttr : public ObjectAttr {
declareRTTI(FaceItemAttr);
// enable RTTI support

public:
  virtual void setAttribute(FaceItem* faceitem) const = 0;
  // Interface to class FaceItem. Whenever setSpecifier(specifier)
  // is called for an instance of class FaceItem,
  // specifier->setAttribute(faceitemObject) will be called. Method
  // setAttribute has to alter the appropriate member of the FaceItem
  // object by executing the right method. The corresponding call graph:
  //
  //   faceitemObject->setSpecifier(specifier)
  //       specifier->setAttribute(faceitemObject)
  //           faceitemObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//______________________________________________________ FaceItemAttrItemLeftCol

class FaceItemAttrItemLeftCol : public FaceItemAttr {
declareRTTI(FaceItemAttrItemLeftCol);
// enable RTTI support

public:
  FaceItemAttrItemLeftCol(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceItem* faceitem) const;
};

//_____________________________________________________ FaceItemAttrItemRightCol

class FaceItemAttrItemRightCol : public FaceItemAttr {
declareRTTI(FaceItemAttrItemRightCol);
// enable RTTI support

public:
  FaceItemAttrItemRightCol(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceItem* faceitem) const;
};

//____________________________________________________ FaceItemAttrItemInsideCol

class FaceItemAttrItemInsideCol : public FaceItemAttr {
declareRTTI(FaceItemAttrItemInsideCol);
// enable RTTI support

public:
  FaceItemAttrItemInsideCol(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceItem* faceitem) const;
};

//______________________________________________________ FaceItemAttrItemBothCol

class FaceItemAttrItemBothCol : public FaceItemAttr {
declareRTTI(FaceItemAttrItemBothCol);
// enable RTTI support

public:
  FaceItemAttrItemBothCol(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceItem* faceitem) const;
};

//____________________________________________________ FaceItemAttrItemBottomRow

class FaceItemAttrItemBottomRow : public FaceItemAttr {
declareRTTI(FaceItemAttrItemBottomRow);
// enable RTTI support

public:
  FaceItemAttrItemBottomRow(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceItem* faceitem) const;
};

//_______________________________________________________ FaceItemAttrItemTopRow

class FaceItemAttrItemTopRow : public FaceItemAttr {
declareRTTI(FaceItemAttrItemTopRow);
// enable RTTI support

public:
  FaceItemAttrItemTopRow(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceItem* faceitem) const;
};

//____________________________________________________ FaceItemAttrItemInsideRow

class FaceItemAttrItemInsideRow : public FaceItemAttr {
declareRTTI(FaceItemAttrItemInsideRow);
// enable RTTI support

public:
  FaceItemAttrItemInsideRow(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceItem* faceitem) const;
};

//______________________________________________________ FaceItemAttrItemBothRow

class FaceItemAttrItemBothRow : public FaceItemAttr {
declareRTTI(FaceItemAttrItemBothRow);
// enable RTTI support

public:
  FaceItemAttrItemBothRow(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceItem* faceitem) const;
};

//_________________________________________________ FaceItemAttrDisplacement

class FaceItemAttrDisplacement : public FaceItemAttr {
declareRTTI(FaceItemAttrDisplacement);
// enable RTTI support

public:
  FaceItemAttrDisplacement(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceItem* faceItem) const;
  FaceItemAttrDisplacement(const Vector2D& displacement);

private:
  Vector2D myDisplacement;
};
//_________________________________________________ FaceItemAttrHole

class FaceItemAttrHole : public FaceItemAttr {
declareRTTI(FaceItemAttrHole);
// enable RTTI support

public:
  FaceItemAttrHole(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceItem* faceitem3D) const;

private:
  FaceItemAttrHole(const List<Vector3D>& vertices);
  FaceItemAttrHole();

  List <Vector3D> myVertices;
};

//_____________________________________________________________ FaceItemAttrwallOff

class FaceItemAttrwallOff : public FaceItemAttr {
declareRTTI(FaceItemAttrwallOff);
// enable RTTI support

public:
  FaceItemAttrwallOff(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceItem* faceitem) const;
};

//______________________________________________________________ FaceItemAttrWallOn

class FaceItemAttrWallOn : public FaceItemAttr {
declareRTTI(FaceItemAttrWallOn);
// enable RTTI support

public:
  FaceItemAttrWallOn(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceItem* faceitem) const;
};

#endif // _FaceItemAttr_H
