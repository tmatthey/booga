/*
 * GSBPolyline.h
 *
 * Copyright (C) 1995, Pascal Habegger <habegger@iam.unibe.ch>
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
 *  $Id: GSBPolyline.h,v 1.4 1997/04/08 11:05:00 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBPolyline_H
#define _GSBPolyline_H

#include "booga/base/Vector2D.h"

//_____________________________________________________________________ GSBPolyline

class GSBPolyline {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBPolyline() : 
    offset(0,0), link(0) {};
  GSBPolyline(float dx, float dy, GSBPolyline* aLink) :
    offset(dx, dy), link(aLink) {};
  GSBPolyline(const GSBPolyline& aPolyline) :
    offset(aPolyline.offset), link(aPolyline.link) {};
  GSBPolyline& operator=(const GSBPolyline& aPolyline);
  
public:
  // virtual ~GSBPolyline();                // Use default version.

private:
//  GSBPolyline& operator=(const GSBPolyline&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Vector2D			offset;
  GSBPolyline*		link;
};

extern ostream& operator<<(ostream& os, GSBPolyline aPolyline);

//______________________________________________________________________ INLINES

inline
GSBPolyline& GSBPolyline::operator=(const GSBPolyline& aPolyline)
{
  offset = aPolyline.offset;
  link = aPolyline.link;
  return *this;
};

#endif // _GSBPolyline_H

