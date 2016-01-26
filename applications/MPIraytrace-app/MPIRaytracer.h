/*
 * $RCSfile: MPIRaytracer.h,v $
 *
 * Copyright (C) 1996, Bernhard Buhlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: MPIRaytracer.h,v 1.3 1996/08/01 12:00:02 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _MPIRaytracer_H
#define _MPIRaytracer_H

#include "booga/component/PixmapRenderer.h"

//____________________________________________________________________ MPIRaytracer

class MPIRaytracer : public PixmapRenderer {
declareRTTI(MPIRaytracer);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  MPIRaytracer(int numtask, int taskid, bool show, int number, 
	       int pipe, int argc, char* argv[]);
private:
  MPIRaytracer(const MPIRaytracer&);             // No copies.

public:
  // virtual ~MPIRaytracer();                 // Use default version.
  
private:
  MPIRaytracer& operator=(const MPIRaytracer&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class MPIRaytracer
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  void collect_pixels();
  void compute_pixels();
  void display_pixels();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool doExecute();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  int myNumtask;
  int myTaskid;
  int myLinesLeft;
  int myNumber;
  int myPipe;
  float *myRowData;
  int myRowDataEntrySize;
  bool myShow;
};

#endif // _MPIRaytracer_H

