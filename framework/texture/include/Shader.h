/*
 * Shader.h
 *
 * Interface to the Booga Shading Language
 *
 * Copyright (C) 1995-96, Thomas Teuscher <teuscher@iam.unibe.ch>
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: Shader.h,v 1.5 1996/06/06 11:49:36 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _Shader_H
# define _Shader_H

#include "booga/base/Color.h"
#include "booga/object/Texture3D.h"
// #include "booga/texture/ShaderParser.h"
#include "booga/texture/ShaderProgNode.h"
//______________________________________________________________________ Shader

class Shader : public Texture3D {
declareRTTI(Shader);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Shader();
  Shader(Exemplar);
  Shader(const Shader& theShader);
  virtual ~Shader();
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Shader
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setParseTree(ShaderProgNode* theParseTree);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Texture3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Texture3D* copy() const;
  virtual void doTexturing(Texture3DContext& context) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;

  virtual RCString getKeyword() const;
  virtual List<Value*>* createParameters();
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  ShaderProgNode* myParseTree;
};

//______________________________________________________________________ INLINES

inline void Shader::setParseTree(ShaderProgNode* theParseTree)
{
  myParseTree = theParseTree;
}

#endif // _Shader_H
