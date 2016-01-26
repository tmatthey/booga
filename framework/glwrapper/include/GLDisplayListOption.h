/*
 * GLDisplayListOption.h
 *
 * Copyright (C) 1995, Bernhard Buehlmann <buhlmann@iam.unibe.ch>
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: GLDisplayListOption.h,v 1.1 1998/05/20 13:01:51 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _GLDisplayListOption_H
#define _GLDisplayListOption_H

#include "booga/base/RTTI.h"
#include "booga/base/Option.h"

#include <GL/gl.h>

class GLDisplayListOption : public Option {
declareRTTI(GLDisplayListOption);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GLDisplayListOption(GLuint l);   // Use default version.
  // GLDisplayListOption(const GLDisplayListOption& GLDisplayListOption);    // Use default version.
  
public:
  virtual ~GLDisplayListOption();
  
public: 
  void callList();

public:
  GLDisplayListOption& operator=(const GLDisplayListOption&);   // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class GLDisplayListOption
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Option* copy() const;  // 'virtual copy constructor'
private: 
  GLuint myGLList;
};

#endif // _GLDisplayListOption_H
