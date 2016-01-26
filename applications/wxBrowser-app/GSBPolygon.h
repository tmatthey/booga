/*
 * GSBPolygon.h
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
 *  $Id: GSBPolygon.h,v 1.4 1997/04/08 11:04:57 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBPolygon_H
#define _GSBPolygon_H

#include "GSBPolyline.h"

//_____________________________________________________________________ GSBPolygon

class GSBPolygon {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
//  GSBPolygon() {};                         // Use default version.
//  GSBPolygon(const GSBPolygon& pcopy);
//  GSBPolygon& operator=(const GSBPolygon&);  // No assignments.

public:
//  virtual ~GSBPolygon();                // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  struct {
    GSBPolyline* head;
    GSBPolyline* tail;
  } upper, lower;
};

#endif // _GSBPolygon_H

