/*
 * $RCSfile: ShaderFunction.h,v $
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
 *  $Id: ShaderFunction.h,v 1.5 1996/08/16 14:21:20 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShaderFunction_H
#define _ShaderFunction_H

#include "booga/base/Value.h"
#include "booga/base/AbstractPixmap.h"
#include "booga/object/Texture3DContext.h"

class ShaderExpNode;

class ShaderFunction {

public:
  ShaderFunction();
  ShaderFunction(int pNumber);
  virtual~ShaderFunction();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext) = 0;
  int getRequiredParameterNumber();
  
protected:
  int myRequiredParameterNumber;
};

/************************************************************************
 *                UTILITIES                                             *
 ************************************************************************/
//__________________________________________________________________Print

class SFPrint : public ShaderFunction {

public:
  SFPrint();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

 /************************************************************************
 *                MATHEMATICAL FUNCTIONS                                *
 ************************************************************************/

//____________________________________________________________________Sin

class SFSin : public ShaderFunction {

public:
  SFSin();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Cos

class SFCos : public ShaderFunction {

public:
  SFCos();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Tan

class SFTan : public ShaderFunction {

public:
  SFTan();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________ASin

class SFASin : public ShaderFunction {

public:
  SFASin();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________ACos

class SFACos : public ShaderFunction {

public:
  SFACos();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________ATan

class SFATan : public ShaderFunction {

public:
  SFATan();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Sqrt

class SFSqrt : public ShaderFunction {

public:
  SFSqrt();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Exp

class SFExp : public ShaderFunction {

public:
  SFExp();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Log

class SFLog : public ShaderFunction {

public:
  SFLog();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Ln

class SFLn : public ShaderFunction {

public:
  SFLn();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Rand

class SFRand : public ShaderFunction {

public:
  SFRand();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Abs

class SFAbs : public ShaderFunction {

public:
  SFAbs();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Min

class SFMin : public ShaderFunction {

public:
  SFMin();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Max

class SFMax : public ShaderFunction {

public:
  SFMax();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Mod

class SFMod : public ShaderFunction {

public:
  SFMod();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________SimpleFloor

class SFSimpleFloor : public ShaderFunction {

public:
  SFSimpleFloor();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Floor

class SFFloor : public ShaderFunction {

public:
  SFFloor();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Frac

class SFFrac : public ShaderFunction {

public:
  SFFrac();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Clamp

class SFClamp : public ShaderFunction {

public:
  SFClamp();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Step

class SFStep : public ShaderFunction {

public:
  SFStep();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Pulse

class SFPulse : public ShaderFunction {

public:
  SFPulse();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________SmoothStep

class SFSmoothStep : public ShaderFunction {

public:
  SFSmoothStep();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Noise

class SFNoise : public ShaderFunction {

public:
  SFNoise();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Chaos

class SFChaos : public ShaderFunction {

public:
  SFChaos();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

/************************************************************************
 *                GEOMETRIC FUNCTIONS                                   *
 ************************************************************************/

//____________________________________________________________________GetX

class SFGetX : public ShaderFunction {

public:
  SFGetX();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________GetY

class SFGetY : public ShaderFunction {

public:
  SFGetY();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________GetZ

class SFGetZ : public ShaderFunction {

public:
  SFGetZ();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________SetX

class SFSetX : public ShaderFunction {

public:
  SFSetX();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________SetY

class SFSetY : public ShaderFunction {

public:
  SFSetY();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________SetZ

class SFSetZ : public ShaderFunction {

public:
  SFSetZ();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Length

class SFLength : public ShaderFunction {

public:
  SFLength();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Distance

class SFDistance : public ShaderFunction {

public:
  SFDistance();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Normalize

class SFNormalize : public ShaderFunction {

public:
  SFNormalize();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________FaceForward

class SFFaceForward : public ShaderFunction {

public:
  SFFaceForward();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________GetNormal

class SFGetNormal : public ShaderFunction {

public:
  SFGetNormal();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

/************************************************************************
 *                COLOR AND SHADING FUNCTIONS                           *
 ************************************************************************/
 
//____________________________________________________________________Ambient

class SFAmbient : public ShaderFunction {

public:
  SFAmbient();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Diffuse

class SFDiffuse : public ShaderFunction {

public:
  SFDiffuse();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________SDiffuse

class SFSDiffuse : public ShaderFunction {

// This is the "shadowed" version of the diffuse function.
// It will send shadow feelers to each light source to
// determine its visibility.

public:
  SFSDiffuse();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Specular

class SFSpecular : public ShaderFunction {

public:
  SFSpecular();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//___________________________________________________________________SSpecular

class SFSSpecular : public ShaderFunction {

public:
  SFSSpecular();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Phong

class SFPhong : public ShaderFunction {

public:
  SFPhong();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________CMult

class SFCMult : public ShaderFunction {

public:
  SFCMult();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Mix

class SFMix : public ShaderFunction {

public:
  SFMix();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Trace

class SFTrace : public ShaderFunction {

public:
  SFTrace();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

/************************************************************************
 *                MAPPING FUNCTIONS                                     *
 ************************************************************************/

//____________________________________________________________________GetUV

class SFGetUV : public ShaderFunction {

public:
  SFGetUV();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________TextureMap

class SFTextureMap : public ShaderFunction {
  //declareRTTI(SFTextureMap);
// enable RTTI support
public:
  SFTextureMap();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

//____________________________________________________________________Bump

class SFBump : public ShaderFunction {

public:
  SFBump();
  virtual Value* evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& theContext);
};

// ____________________________________________________________________Inlines

#endif

