/*
 * $RCSfile: BottomBorder.h,v $
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
 *  $Id: BottomBorder.h,v 1.2 1997/02/06 14:13:35 matthey Exp matthey $
 * -----------------------------------------------------------------------------
 */

#ifndef _BottomBorder_H
#define _BottomBorder_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/building/Bottom.h"

// ____________________________________________________________________ BottomBorder

class BottomBorder : public Bottom {
declareRTTI(BottomBorder);
// enable RTTI support

public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  BottomBorder();
  BottomBorder(Exemplar exemplar);
  // BottomBorder(const BottomBorder& BottomBorder);      
  BottomBorder(Real ledge, Real borderwidth,Real borderheight,Real borderdepth);

public:
  // virtual ~BottomBorder();   
  
private:  
  BottomBorder& operator=(const BottomBorder&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class BottomBorder
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setLedge(Real ledge);
  Real getLedge() const;

  void setBorderWidth(Real borderwidth);
  Real getBorderWidth() const;

  void setBorderHeight(Real borderheight);
  Real getBorderHeight() const;

  void setBorderDepth(Real borderdepth);
  Real getBorderDepth() const;

  bool isClosed() const;
  void close();
  void open();

private:
  List<Vector3D> computeLedge(const List<Vector3D>& vertices) const;
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual RCString getKeyword() const;
  virtual List<Value*>* createParameters();
  virtual void iterateAttributes(MakeableHandler *handler);

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
  Real myLedge;
  Real myBorderWidth;
  Real myBorderHeight;
  Real myBorderDepth;
  bool myIsClosed;

};

//______________________________________________________________________ INLINES

inline void BottomBorder::setBorderWidth(Real borderwidth)
{
  myBorderWidth = borderwidth;
}

inline Real BottomBorder::getBorderWidth() const
{
  return myBorderWidth;
}

inline void BottomBorder::setBorderHeight(Real borderheight)
{
  myBorderHeight = borderheight;
}

inline Real BottomBorder::getBorderHeight() const
{
  return myBorderHeight;
}

inline void BottomBorder::setBorderDepth(Real borderdepth)
{
  myBorderDepth = borderdepth;
}

inline Real BottomBorder::getBorderDepth() const
{
  return myBorderDepth;
}

inline void BottomBorder::setLedge(Real ledge)
{
  myLedge = ledge;
}

inline Real BottomBorder::getLedge() const
{
  return myLedge;
}

inline void BottomBorder::open()
{
  myIsClosed = false;
}

inline void BottomBorder::close()
{
  myIsClosed = true;
}

inline bool BottomBorder::isClosed() const
{
  return myIsClosed;
}

#endif // _BottomBorder_H
