/*
 * Shader.C
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
 *  $Id: Shader.C,v 1.6 1996/06/06 11:49:35 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#include "booga/base/Value.h"
#include "booga/texture/Shader.h"
#include "booga/texture/ShaderParser.h"
#include "booga/object/Texture3DContext.h"
#include "booga/object/DummyMakeable.h"
#include "booga/object/MakeableHandler.h"

//______________________________________________________________________ Shader

implementRTTI(Shader, Texture3D);

Shader::Shader()
{
  myParseTree = NULL;
}

Shader::Shader(Exemplar)
{
  myParseTree = NULL;
}

Shader::Shader(const Shader& theShader)
{
  if (theShader.myParseTree != NULL)
    myParseTree = new ShaderProgNode(theShader.myParseTree);
  else
    myParseTree = NULL;
}

Shader::~Shader()
{
  delete myParseTree;
}
  
Makeable* Shader::make(RCString&, const List<Value*>* arguments) const
{
  // varying number of parameters -> no checkParameterNumber() possible.

  RCString fileToParse = (RCString)*arguments->item(0);
  
  // all but the first parameter (that is the fileToParse)
  // will be propagated to the parse tree to overwrite the 
  // default values defined in the shader's head. 

//  List<Value*>* theArguments = new List<Value*>(arguments->count());
//  for (int i = 0; i < arguments->count(); i++)
//    theArguments->append(arguments->item(i));
  ShaderParser parser;
  parser.parse(fileToParse);
  Texture3DContext context;
  parser.getParseTree()->overwriteDefaults(arguments, context);
//  delete theArguments;
  Shader* newShader = new Shader(*this);
  newShader->setParseTree(parser.getParseTree());
  return newShader;
}

Texture3D* Shader::copy() const
{
  return new Shader(*this);
}

void Shader::doTexturing(Texture3DContext& context) const
{
  myParseTree->execute(context);
}

static const RCString shaderKeyword("shader");

RCString Shader::getKeyword() const {
  return shaderKeyword;
}

List<Value*>* Shader::createParameters() {
  return myParseTree->createParameters();
}
