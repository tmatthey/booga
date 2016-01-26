/*
 * $RCSfile: RoofBorder.h,v $
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
 *  $Id: RoofBorder.h,v 1.2 1997/02/06 14:13:55 matthey Exp matthey $
 * -----------------------------------------------------------------------------
 */

#ifndef _RoofBorder_H
#define _RoofBorder_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/building/Roof.h"

// ____________________________________________________________________ RoofBorder

class RoofBorder : public Roof {
declareRTTI(RoofBorder);
// enable RTTI support

public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  RoofBorder();
  RoofBorder(Exemplar exemplar);
  // RoofBorder(const RoofBorder& RoofBorder);      
  RoofBorder(Real ledge, Real borderwidth, Real borderheight, Real borderdepth);

public:
  // virtual ~RoofBorder();   
  
private:  
  RoofBorder& operator=(const RoofBorder&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class RoofBorder
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setBorderWidth(Real borderwidth);
  Real getBorderWidth() const;
  void setBorderHeight(Real borderheight);
  Real getBorderHeight() const;
  void setBorderDepth(Real borderdepth);
  Real getBorderDepth() const;
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual RCString getKeyword() const;
  virtual List<Value*>* createParameters();

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
  Real myBorderWidth;
  Real myBorderHeight;
  Real myBorderDepth;

};

//______________________________________________________________________ INLINES

inline void RoofBorder::setBorderWidth(Real borderwidth)
{
  myBorderWidth = borderwidth;
}

inline Real RoofBorder::getBorderWidth() const
{
  return myBorderWidth;
}

inline void RoofBorder::setBorderHeight(Real borderheight)
{
  myBorderHeight = borderheight;
}

inline Real RoofBorder::getBorderHeight() const
{
  return myBorderHeight;
}

inline void RoofBorder::setBorderDepth(Real borderdepth)
{
  myBorderDepth = borderdepth;
}

inline Real RoofBorder::getBorderDepth() const
{
  return myBorderDepth;
}


#endif // _RoofBorder_H
