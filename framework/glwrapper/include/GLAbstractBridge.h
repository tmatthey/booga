/*
 * GLAbstractBridge.h
 *
 * Abstract base class for toolkit dependend functions like swapBuffers() or
 * isEventPending(). The user may choose the toolkit of his choice at runtime
 * by providing the corresponding toolkit object (instance of a class derived 
 * from class GLAbstractBridge, e.g. GlutBridge) to the GLUtilities class. 
 * This is done by calling GLUtilities::adoptToolkit(toolkit).
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: GLAbstractBridge.h,v 1.1 1996/04/25 09:58:55 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GLAbstractBridge_H
#define _GLAbstractBridge_H

#include "booga/base/PrimitiveTypes.h"

//_____________________________________________________________ GLAbstractBridge

class GLAbstractBridge  {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // GLAbstractBridge();                         // Use default version.
private:
  // GLAbstractBridge(const GLAbstractBridge&);  // Use default version.

public:
  virtual ~GLAbstractBridge();

private:
  // GLAbstractBridge& operator=(const GLAbstractBridge&);  
  // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class GLAbstractBridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual bool isEventPending() = 0;
  // Checks for an entry (e.g. mouse click, etc.) in the event queue.

  virtual void swapBuffers() = 0;
  // Swap buffer in double buffer mode.
};

//______________________________________________________________________ INLINES

#endif // _GLAbstractBridge_H

