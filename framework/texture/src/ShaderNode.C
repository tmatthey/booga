/*
 * $RCSfile: ShaderNode.C,v $
 *
 * Copyright (C) 1995-96, Thomas Teuscher <teuscher@iam.unibe.ch>
 *                        University of Berne, Switzerland
 *
 * All rights reserved.
 *
 * This software may be freely copied, modified and redistributed
 * provided that this copyright note be preserved on all copies.
 * 
 * You may not distribute this software, in whole or in part, as part
 * of any commercial product without the express consent of the author.
 *
 * There is no warranty or other guarantee of fitness of this software
 * for any purpose. It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: ShaderNode.C,v 1.8 1996/08/16 14:21:20 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include "booga/texture/ShaderFunction.h"
#include "booga/texture/ShaderNode.h"

//____________________________________________________________________ShaderNode

implementInitStatics(ShaderNode);

bool ShaderNode::ourFatalErrorFlag;
int ShaderNode::ourBlockDepth;
List<SymTable<RCString, Value>*>* ShaderNode::ourScopes;
SymTable<RCString, ShaderFunction*>* ShaderNode::ourFunctions;
SymTable<RCString, AbstractPixmap*>* ShaderNode::ourPixmaps;

ShaderNode::~ShaderNode()
{}

void ShaderNode::printValues()
{}

void ShaderNode::printSpaces(int times)
{
  for (int i = 0; i < times - 2; i++)
    std::cout << " ";
}

void ShaderNode::initClass()
{
  ourFatalErrorFlag = false;
  ourBlockDepth = 0;
  ourScopes = new List<SymTable<RCString, Value>*>(1);
  initFunctionScope();
  ourPixmaps = new SymTable<RCString, AbstractPixmap*>(19);
}

void ShaderNode::initFunctionScope()
{
  ourFunctions = new SymTable<RCString, ShaderFunction*>(107);

  // Utilities
  ourFunctions->insert("print", new SFPrint());

  // Mathematical functions
  ourFunctions->insert("sin", new SFSin());
  ourFunctions->insert("cos", new SFCos());
  ourFunctions->insert("tan", new SFTan());
  ourFunctions->insert("asin", new SFASin());
  ourFunctions->insert("acos", new SFACos());
  ourFunctions->insert("atan", new SFATan());
  ourFunctions->insert("sqrt", new SFSqrt());
  ourFunctions->insert("exp", new SFExp());
  ourFunctions->insert("log", new SFLog());
  ourFunctions->insert("ln", new SFLn());
  ourFunctions->insert("rand", new SFRand());  
  ourFunctions->insert("abs", new SFAbs());
  ourFunctions->insert("min", new SFMin());
  ourFunctions->insert("max", new SFMax());
  ourFunctions->insert("mod", new SFMod());
  ourFunctions->insert("simplefloor", new SFSimpleFloor());            
  ourFunctions->insert("floor", new SFFloor());
  ourFunctions->insert("frac", new SFFrac());          
  ourFunctions->insert("clamp", new SFClamp());
  ourFunctions->insert("step", new SFStep());
  ourFunctions->insert("pulse", new SFPulse());
  ourFunctions->insert("smoothstep", new SFSmoothStep());
  ourFunctions->insert("noise", new SFNoise());
  ourFunctions->insert("chaos", new SFChaos());

  // Geometric functions
  ourFunctions->insert("getx", new SFGetX());
  ourFunctions->insert("gety", new SFGetY());
  ourFunctions->insert("getz", new SFGetZ());  
  ourFunctions->insert("setx", new SFSetX());
  ourFunctions->insert("sety", new SFSetY());
  ourFunctions->insert("setz", new SFSetZ());
  ourFunctions->insert("length", new SFLength());
  ourFunctions->insert("distance", new SFDistance());
  ourFunctions->insert("normalize", new SFNormalize());
  ourFunctions->insert("faceforward", new SFFaceForward());            
  ourFunctions->insert("getnormal", new SFGetNormal());          


  // Color and shading functions
  ourFunctions->insert("ambient", new SFAmbient());
  ourFunctions->insert("diffuse", new SFDiffuse());
  ourFunctions->insert("sdiffuse", new SFSDiffuse());  
  ourFunctions->insert("specular", new SFSpecular());  
  ourFunctions->insert("sspecular", new SFSSpecular());  
  ourFunctions->insert("phong", new SFPhong());
  ourFunctions->insert("cmult", new SFCMult());        
  ourFunctions->insert("mix", new SFMix());        
  ourFunctions->insert("trace", new SFTrace());

  // Mapping functions
  ourFunctions->insert("getuv", new SFGetUV());
  ourFunctions->insert("texturemap", new SFTextureMap());
  ourFunctions->insert("bump", new SFBump());
 }

void ShaderNode::enterBlock()
{
  ourBlockDepth++;
  SymTable<RCString, Value>* aLocalScope = new SymTable<RCString, Value>(127);
  ourScopes->prepend(aLocalScope);
}

void ShaderNode::leaveBlock()
{
  ourBlockDepth--;
  ourScopes->remove(0);
}

bool ShaderNode::isFatalError()
{
  return ourFatalErrorFlag;
}

void ShaderNode::setFatalError(bool enable)
{
  ourFatalErrorFlag = enable;
}
