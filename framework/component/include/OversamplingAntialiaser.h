/*
 * $RCSfile: OversamplingAntialiaser.h,v $
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
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: OversamplingAntialiaser.h,v 1.4 1996/08/01 12:00:19 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _OversamplingAntialiaser_H
#define _OversamplingAntialiaser_H

#include "booga/component/Antialiaser.h"

//______________________________________________________ OversamplingAntialiaser

class OversamplingAntialiaser : public Antialiaser {
declareRTTI(OversamplingAntialiaser);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  OversamplingAntialiaser();
  // OversamplingAntialiaser(const OversamplingAntialiaser&); // Use default version.

public:
  // virtual ~OversamplingAntialiaser();                      // Use default version.

public:
  // OversamplingAntialiaser& operator=(const OversamplingAntialiaser&); 
  // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class OversamplingAntialiaser
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setSamplingRate(int samplingRate);
  // This parameter specifies how much oversampling shouldbe performed
  // for anti-aliasing. Each pixel will be rendered internally as a mesh 
  // of [ samplingRate x samplingRate ] subpixels and the average color
  // in this mesh will be used to represent the final pixel.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool doExecute();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  int mySamplingRate;
};

//______________________________________________________________________ INLINES

#endif // _OversamplingAntialiaser_H

