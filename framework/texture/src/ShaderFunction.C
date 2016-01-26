/*
 * $RCSfile: ShaderFunction.C,v $
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
 *  $Id: ShaderFunction.C,v 1.13 1997/09/19 07:14:46 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include <math.h>
#include <strstream.h>

#include "booga/base/RTTI.h"
#include "booga/base/mathutilities.h"
#include "booga/base/Report.h"
#include "booga/base/Vector3D.h"
#include "booga/base/PixmapOf.h"

#include "booga/object/AmbientLight.h"
#include "booga/object/DirectedLight.h"
#include "booga/object/Primitive3D.h"
#include "booga/object/Ray3DFactory.h"
#include "booga/object/Ray3DUtilities.h"

#include "booga/pixmapOp/ImageReaders.h"

#include "booga/texture/ShaderFunction.h"
#include "booga/texture/ShaderExpNode.h"
#include "booga/texture/ShaderIdExpNode.h"
#include "booga/texture/TextureUtilities.h"


ShaderFunction::ShaderFunction(int pNumber)
{
  myRequiredParameterNumber = pNumber;
}

ShaderFunction::ShaderFunction()
{}

ShaderFunction::~ShaderFunction()
{}

int ShaderFunction::getRequiredParameterNumber()
{
  return myRequiredParameterNumber;
}

/************************************************************************
 *                UTILITIES                                             *
 ************************************************************************/
//__________________________________________________________________Print

SFPrint::SFPrint()
:ShaderFunction(1)
{}

Value* SFPrint::evaluate(List<ShaderExpNode*>* theArgList,
                         Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);  
  ostrstream os;
  os << "[BSL Print] value is " << *temp;
  Report::hint(os);
  return temp; // pro forma
}

/************************************************************************
 *                MATHEMATICAL FUNCTIONS                                *
 ************************************************************************/

//____________________________________________________________________Sin

SFSin::SFSin()
:ShaderFunction(1)
{}

Value* SFSin::evaluate(List<ShaderExpNode*>* theArgList,
                       Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);  
  Real arg = (Real)*temp;

  delete temp;
  return new Value(sin(dtor(arg)));
}

//____________________________________________________________________Cos

SFCos::SFCos()
{
  myRequiredParameterNumber = 1;
}

Value* SFCos::evaluate(List<ShaderExpNode*>* theArgList,
                       Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);
  Real arg = (Real)*temp;

  delete temp;
  return new Value(cos(dtor(arg)));
}

//____________________________________________________________________Tan

SFTan::SFTan()
{
  myRequiredParameterNumber = 1;
}

Value* SFTan::evaluate(List<ShaderExpNode*>* theArgList,
                       Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);
  Real arg = (Real)*temp;
  
  delete temp;
  return new Value(tan(dtor(arg)));
}

//____________________________________________________________________ASin

SFASin::SFASin()
{
  myRequiredParameterNumber = 1;
}

Value* SFASin::evaluate(List<ShaderExpNode*>* theArgList,
                        Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);
  Real arg = (Real)*temp;

  delete temp;
  return new Value(rtod(asin(arg)));
}

//____________________________________________________________________ACos

SFACos::SFACos()
{
  myRequiredParameterNumber = 1;
}

Value* SFACos::evaluate(List<ShaderExpNode*>* theArgList,
                        Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);
  Real arg = (Real)*temp;
  
  delete temp;
  return new Value(rtod(acos(arg)));
}

//____________________________________________________________________ATan

SFATan::SFATan()
{
  myRequiredParameterNumber = 1;
}

Value* SFATan::evaluate(List<ShaderExpNode*>* theArgList,
                        Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);
  Real arg = (Real)*temp;
  
  delete temp;
  return new Value(rtod(atan(arg)));
}

//____________________________________________________________________Sqrt

SFSqrt::SFSqrt()
{
  myRequiredParameterNumber = 1;
}

Value* SFSqrt::evaluate(List<ShaderExpNode*>* theArgList,
                        Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);
  Real arg = (Real)*temp;
  if (arg <  0)
    cout << "Fatal Error: Negative operand for sqrt()!" << endl;

  delete temp;
  return new Value(sqrt(arg));
}

//____________________________________________________________________Exp

SFExp::SFExp()
{
  myRequiredParameterNumber = 1;
}

Value* SFExp::evaluate(List<ShaderExpNode*>* theArgList,
                       Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);
  Real arg = (Real)*temp;
  
  delete temp;
  return new Value(exp(arg));
}

//____________________________________________________________________Log

SFLog::SFLog()
{
  myRequiredParameterNumber = 1;
}

Value* SFLog::evaluate(List<ShaderExpNode*>* theArgList,
                       Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);
  Real arg = (Real)*temp;
  if (arg < 0)
    cout << "Fatal Error: Negative operand for log10()!" << endl;

  delete temp;
  return new Value(log10(arg));
}

//____________________________________________________________________Ln

SFLn::SFLn()
{
  myRequiredParameterNumber = 1;
}

Value* SFLn::evaluate(List<ShaderExpNode*>* theArgList,
                      Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);
  Real arg = (Real)*temp;
  if (arg <  0)
    cout << "Fatal Error: Negative operand for Ln()!" << endl;
  
  delete temp;
  return new Value(log(arg));
}

//____________________________________________________________________Rand

SFRand::SFRand()
{
  myRequiredParameterNumber = 0;
}

Value* SFRand::evaluate(List<ShaderExpNode*>*,
                        Texture3DContext&)
{
  return new Value(drand48());
}

//____________________________________________________________________Abs

SFAbs::SFAbs()
{
  myRequiredParameterNumber = 1;
}

Value* SFAbs::evaluate(List<ShaderExpNode*>* theArgList,
                       Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);
  Real arg = (Real)*temp;
  
  delete temp;
  return new Value(fabs(arg));
}

//____________________________________________________________________Min

SFMin::SFMin()
{
  myRequiredParameterNumber = 2;
}


Value* SFMin::evaluate(List<ShaderExpNode*>* theArgList,
                       Texture3DContext& context)
{ 
  Value* temp0 = theArgList->item(0)->evaluate(context);
  Value* temp1 = theArgList->item(0)->evaluate(context);  
  Real arg1 = (Real)*temp0;
  Real arg2 = (Real)*temp1;

  delete temp0;
  delete temp1;
  return new Value(arg1 <= arg2 ? arg1 : arg2);
}

//____________________________________________________________________Max

SFMax::SFMax()
{
  myRequiredParameterNumber = 2;
}


Value* SFMax::evaluate(List<ShaderExpNode*>* theArgList,
                       Texture3DContext& context)
{ 
  Value* temp0 = theArgList->item(0)->evaluate(context);
  Value* temp1 = theArgList->item(0)->evaluate(context);  
  Real arg1 = (Real)*temp0;
  Real arg2 = (Real)*temp1;

  delete temp0;
  delete temp1;
  return new Value(arg1 >= arg2 ? arg1 : arg2);
}

//____________________________________________________________________Mod

SFMod::SFMod()
{
  myRequiredParameterNumber = 2;
}


Value* SFMod::evaluate(List<ShaderExpNode*>* theArgList,
                       Texture3DContext& context)
{
  Value* temp0 = theArgList->item(0)->evaluate(context);
  Value* temp1 = theArgList->item(1)->evaluate(context);
  Real a = (Real)*temp0;
  Real b = (Real)*temp1;
  int n = (int)(a/b);
  a -= b*n;
  if (a < 0)
    a += b;
  
  delete temp0;
  delete temp1;  
  return new Value(a);
}

//____________________________________________________________________SimpleFloor

SFSimpleFloor::SFSimpleFloor()
{
  myRequiredParameterNumber = 1;
}

Value* SFSimpleFloor::evaluate(List<ShaderExpNode*>* theArgList,
                               Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);
  Real arg = (Real)*temp;
  Real retval = simplefloor(arg);

  delete temp;
  return new Value(retval);
}

//____________________________________________________________________Floor

SFFloor::SFFloor()
{
  myRequiredParameterNumber = 1;
}

Value* SFFloor::evaluate(List<ShaderExpNode*>* theArgList,
                         Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);
  Real arg = (Real)*temp;
  Real tempdoub;
  Real retval = floor(arg);

  delete temp;
  return new Value(retval);
}

//____________________________________________________________________Frac

SFFrac::SFFrac()
{
  myRequiredParameterNumber = 1;
}

Value* SFFrac::evaluate(List<ShaderExpNode*>* theArgList,
                        Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);
  Real arg = (Real)*temp;
  Real retval = frac(arg);

  delete temp;
  return new Value(retval);
}

//____________________________________________________________________Clamp

SFClamp::SFClamp()
{
  myRequiredParameterNumber = 3;
}


Value* SFClamp::evaluate(List<ShaderExpNode*>* theArgList,
                         Texture3DContext& context)
{ 
  Value* temp0 = theArgList->item(0)->evaluate(context);
  Value* temp1 = theArgList->item(1)->evaluate(context);
  Value* temp2 = theArgList->item(2)->evaluate(context);
  Real x = (Real)*temp0;
  Real a = (Real)*temp1;
  Real b = (Real)*temp2;

  delete temp0;
  delete temp1;
  delete temp2;
  return new Value(x < a ? a : (x <= b ? x : b));
}

//____________________________________________________________________Step

SFStep::SFStep()
{
  myRequiredParameterNumber = 2;
}


Value* SFStep::evaluate(List<ShaderExpNode*>* theArgList,
                        Texture3DContext& context)
{
  Value* temp0 = theArgList->item(0)->evaluate(context);
  Value* temp1 = theArgList->item(1)->evaluate(context);
  Real x = (Real)*temp0;
  Real a = (Real)*temp1;

  delete temp0;
  delete temp1;
  return new Value(x >= a);
}

//____________________________________________________________________Pulse

SFPulse::SFPulse()
{
  myRequiredParameterNumber = 3;
}


Value* SFPulse::evaluate(List<ShaderExpNode*>* theArgList,
                         Texture3DContext& context)
{
  Value* temp0 = theArgList->item(0)->evaluate(context);
  Value* temp1 = theArgList->item(1)->evaluate(context);
  Value* temp2 = theArgList->item(2)->evaluate(context);
  Real x = (Real)*temp0;
  Real a = (Real)*temp1;
  Real b = (Real)*temp2;

  delete temp0;
  delete temp1;
  delete temp2;
  return new Value((x >= a) - (x >= b));
}

//____________________________________________________________________SmoothStep

SFSmoothStep::SFSmoothStep()
{
  myRequiredParameterNumber = 3;
}


Value* SFSmoothStep::evaluate(List<ShaderExpNode*>* theArgList,
                              Texture3DContext& context)
{
  Value* temp0 = theArgList->item(0)->evaluate(context);
  Value* temp1 = theArgList->item(1)->evaluate(context);
  Value* temp2 = theArgList->item(2)->evaluate(context);
  Real x = (Real)*temp0;
  Real a = (Real)*temp1;
  Real b = (Real)*temp2;

  delete temp0;
  delete temp1;
  delete temp2;
  
  if (x < a) 
    return new Value(0.);
  if (x > b)
    return new Value(1.);
  x = (x - a)/(b - a);  // normalize x into the interval [0..1]
  return new Value(x*x * (3 - 2*x));
}

//____________________________________________________________________Noise

SFNoise::SFNoise()
{
  myRequiredParameterNumber = 1;
  TextureUtilities::initNoise();
}


Value* SFNoise::evaluate(List<ShaderExpNode*>* theArgList,
                         Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);
  Vector3D point = (Vector3D)*temp;
  
  delete temp;
  return new Value(TextureUtilities::Noise3(point));
}

//____________________________________________________________________Chaos

SFChaos::SFChaos()
{
  myRequiredParameterNumber = 2;
}


Value* SFChaos::evaluate(List<ShaderExpNode*>* theArgList,
                         Texture3DContext& context)
{ 
  Value* temp0 = theArgList->item(0)->evaluate(context);
  Value* temp1 = theArgList->item(1)->evaluate(context);
  Vector3D point = (Vector3D)*temp0;
  Real octaves = (Real)*temp1;
  
  delete temp0;
  delete temp1;
  return new Value(TextureUtilities::Chaos(point, (int)octaves));
}

/************************************************************************
 *                GEOMETRIC FUNCTIONS                                   *
 ************************************************************************/

//____________________________________________________________________GetX

SFGetX::SFGetX()
{
  myRequiredParameterNumber = 1;
}


Value* SFGetX::evaluate(List<ShaderExpNode*>* theArgList,
                        Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);
  Vector3D point = (Vector3D)*temp;

  delete temp;
  return new Value(point.x());
}

//____________________________________________________________________GetY

SFGetY::SFGetY()
{
  myRequiredParameterNumber = 1;
}


Value* SFGetY::evaluate(List<ShaderExpNode*>* theArgList,
                        Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);
  Vector3D point = (Vector3D)*temp;

  delete temp;
  return new Value(point.y());
}

//____________________________________________________________________GetZ

SFGetZ::SFGetZ()
{
  myRequiredParameterNumber = 1;
}


Value* SFGetZ::evaluate(List<ShaderExpNode*>* theArgList,
                        Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);
  Vector3D point = (Vector3D)*temp;

  delete temp;
  return new Value(point.z());
}

//____________________________________________________________________SetX

SFSetX::SFSetX()
{
  myRequiredParameterNumber = 2;
}


Value* SFSetX::evaluate(List<ShaderExpNode*>* theArgList,
                        Texture3DContext& context)
{
  Value* temp0 = theArgList->item(0)->evaluate(context);
  Value* temp1 = theArgList->item(1)->evaluate(context);
  Vector3D point = (Vector3D)*temp0;
  RCString name = *((ShaderIdExpNode*)theArgList->item(0))->getName();
  Real newXValue = (Real)*temp1;
  
  point = Vector3D(newXValue, point.y(), point.z());
  int i = 0;
  List<SymTable<RCString, Value>*>* theScopes = ShaderNode::getScopes();
  while((i < theScopes->count()) &&
        (!theScopes->item(i)->findAndReplace(name, point)))
    i++;
  
  // we can't find it in neither scope --> it's a texture attribute.
  if (i == theScopes->count())
    TextureUtilities::evaluateTextureAttributes(name, point, context);
    
  delete temp0;
  delete temp1;
  return new Value(1);  // pro forma
}

//____________________________________________________________________SetY

SFSetY::SFSetY()
{
  myRequiredParameterNumber = 2;
}


Value* SFSetY::evaluate(List<ShaderExpNode*>* theArgList,
                        Texture3DContext& context)
{
  Value* temp0 = theArgList->item(0)->evaluate(context);
  Value* temp1 = theArgList->item(1)->evaluate(context);
  Vector3D point = (Vector3D)*temp0;
  RCString name = *((ShaderIdExpNode*)theArgList->item(0))->evaluate(context);
  Real newYValue = (Real)*temp1;
  
  point = (Vector3D(point.x(), newYValue, point.z()));
  int i = 0;
  List<SymTable<RCString, Value>*>* theScopes = ShaderNode::getScopes();
  while((i < theScopes->count()) &&
        (!theScopes->item(i)->findAndReplace(name, point)))
    i++;
  
  // we can't find it in neither scope --> it's a texture attribute.
  if (i == theScopes->count()) 
    TextureUtilities::evaluateTextureAttributes(name, point, context);

  delete temp0;
  delete temp1;
  return new Value(1);  // pro forma
}

//____________________________________________________________________SetZ

SFSetZ::SFSetZ()
{
  myRequiredParameterNumber = 2;
}


Value* SFSetZ::evaluate(List<ShaderExpNode*>* theArgList,
                        Texture3DContext& context)
{
  Value* temp0 = theArgList->item(0)->evaluate(context);
  Value* temp1 = theArgList->item(1)->evaluate(context);
  Vector3D point = (Vector3D)*temp0;
  RCString name = *((ShaderIdExpNode*)theArgList->item(0))->getName();
  Real newZValue = (Real)*temp1;

  point = (Vector3D(point.x(), point.y(), newZValue));
  int i = 0;
  List<SymTable<RCString, Value>*>* theScopes = ShaderNode::getScopes();
  while((i < theScopes->count()) &&
        (!theScopes->item(i)->findAndReplace(name, point)))
    i++;
  
  // we can't find it in neither scope --> it's a texture attribute.
  if (i == theScopes->count()) 
    TextureUtilities::evaluateTextureAttributes(name, point, context);
    
  delete temp0;
  delete temp1;
  return new Value(1);  // pro forma
}

//____________________________________________________________________Length

SFLength::SFLength()
{
  myRequiredParameterNumber = 1;
}


Value* SFLength::evaluate(List<ShaderExpNode*>* theArgList,
                          Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);
  Vector3D point = (Vector3D)*temp;
  
  delete temp;
  return new Value(point.length());
}

//____________________________________________________________________Distance

SFDistance::SFDistance()
{
  myRequiredParameterNumber = 2;
}


Value* SFDistance::evaluate(List<ShaderExpNode*>* theArgList,
                            Texture3DContext& context)
{
  Value* temp0 = theArgList->item(0)->evaluate(context);
  Value* temp1 = theArgList->item(1)->evaluate(context);
  Vector3D point1 = (Vector3D)*temp0;
  Vector3D point2 = (Vector3D)*temp1;

  delete temp0;
  delete temp1;
  return new Value(point1.distance(point2));
}

//____________________________________________________________________Normalize

SFNormalize::SFNormalize()
{
  myRequiredParameterNumber = 1;
}


Value* SFNormalize::evaluate(List<ShaderExpNode*>* theArgList,
                             Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);
  Vector3D point = (Vector3D)*temp;
 
  delete temp; 
  return new Value(point.normalized());
}

//____________________________________________________________________FaceForward

SFFaceForward::SFFaceForward()
{
  myRequiredParameterNumber = 2;
}


Value* SFFaceForward::evaluate(List<ShaderExpNode*>* theArgList,
                               Texture3DContext& context)
{
  Value* temp0 = theArgList->item(0)->evaluate(context);
  Vector3D vec0 = (Vector3D)*temp0;
  Value* temp1 = theArgList->item(1)->evaluate(context);
  Vector3D vec1 = (Vector3D)*temp1;

  delete temp0;
  delete temp1; 
  if ((vec0^vec1) > 0)
    return new Value(-vec0);
  else
    return new Value(vec0);  
}

//____________________________________________________________________GetNormal

SFGetNormal::SFGetNormal()
{
  myRequiredParameterNumber = 1;
}

Value* SFGetNormal::evaluate(List<ShaderExpNode*>* theArgList,
                             Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);
  Vector3D point = (Vector3D)*temp;

  Primitive3D* primitive = dynamic_cast(Primitive3D,const_cast(Object3D,context.getObject()));
  Vector3D normal(context.getNormalOCS());
  
  // The normal for an arbitrarily placed point may be computed 
  // only for primitives!
  if (primitive != NULL)
    normal = primitive->normal(point);
  
  delete temp;
  return new Value(normal);
}

/************************************************************************
 *                COLOR AND SHADING FUNCTIONS                           *
 ************************************************************************/
 
//____________________________________________________________________Ambient

SFAmbient::SFAmbient()
{
  myRequiredParameterNumber = 1;
}

Value* SFAmbient::evaluate(List<ShaderExpNode*>* theArgList,
                           Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);
  
  // collect ambient illumination
  Vector3D colorValue = (Vector3D)*temp;
  Color ambientColor = colorValue;
  Color ambientIllumination(0,0,0);
  
  forEachLight(AmbientLight, ambLight) {
    ambLight->getIllumination(context);
    ambientIllumination += context.getIllumination();
  }
  
  delete temp;
  return new Value(Vector3D(ambientColor * ambientIllumination));
}

//____________________________________________________________________Diffuse

SFDiffuse::SFDiffuse()
{
  myRequiredParameterNumber = 1;
}

Value* SFDiffuse::evaluate(List<ShaderExpNode*>* theArgList,
                           Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);

  //collect directed illumination
  Vector3D colorValue = (Vector3D)*temp;
  Color diffuseColor = colorValue; // Implicit vector3D->Color conversion.
  float cosAlpha;
  Color directedIllumination(0,0,0);
  Vector3D normal = context.getNormalWCS();
  
  forEachLight(DirectedLight, dirLight) {
    dirLight->getDirection(context);
    cosAlpha = normal ^ context.getLightDirection();
    if (cosAlpha > 0) {
      dirLight->getIllumination(context);
      directedIllumination += context.getIllumination() * cosAlpha;
    }        
  }
  
  delete temp;
  return new Value(Vector3D(diffuseColor * directedIllumination));  
}

//____________________________________________________________________SDiffuse

SFSDiffuse::SFSDiffuse()
{
  myRequiredParameterNumber = 1;
}

Value* SFSDiffuse::evaluate(List<ShaderExpNode*>* theArgList,
                           Texture3DContext& context)
{
  Value* temp = theArgList->item(0)->evaluate(context);

  //collect directed illumination
  Vector3D colorValue = (Vector3D)*temp;
  Color diffuseColor = colorValue; // Implicit vector3D->Color conversion.
  float cosAlpha;
  Color directedIllumination(0,0,0);
  Vector3D normal = context.getNormalWCS();
  
  forEachLight(DirectedLight, dirLight) {
    dirLight->getDirection(context);
    cosAlpha = normal ^ context.getLightDirection();
    if ((cosAlpha > 0) && dirLight->isVisible(context)) {
      dirLight->getIllumination(context);
      directedIllumination += context.getIllumination() * cosAlpha;
    }        
  }
  
  delete temp;
  return new Value(Vector3D(diffuseColor * directedIllumination));  
}

//____________________________________________________________________Specular

SFSpecular::SFSpecular()
{
  myRequiredParameterNumber = 2;
}

Value* SFSpecular::evaluate(List<ShaderExpNode*>* theArgList,
                            Texture3DContext& context)
{
  Value* temp0 = theArgList->item(0)->evaluate(context);
  Value* temp1 = theArgList->item(1)->evaluate(context);
  
  //collect directed illumination 
  Vector3D colorValue = (Vector3D)*temp0;
  Color specularColor = colorValue;  // Implicit vector3D->Color conversion.
  Real specPow = (Real)*temp1;
  float cosAlpha;
  Real RV;
  Color specularIllumination(0,0,0);
  Vector3D normal = context.getNormalWCS();
  Vector3D toView = (context.getIncidencePosition() - 
                     context.getPositionWCS()).normalized();

  forEachLight(DirectedLight, dirLight) {
    dirLight->getDirection(context);
    cosAlpha = normal ^ context.getLightDirection();
    if (cosAlpha > 0) {
      dirLight->getIllumination(context);
      RV = fabs((2*normal*cosAlpha-context.getLightDirection())^toView);
      specularIllumination += context.getIllumination() * (float)pow(RV, specPow);
    }        
  }
  
  delete temp0;
  delete temp1;
  return new Value(Vector3D(specularColor * specularIllumination));
}

//____________________________________________________________________SSpecular

SFSSpecular::SFSSpecular()
{
  myRequiredParameterNumber = 2;
}

Value* SFSSpecular::evaluate(List<ShaderExpNode*>* theArgList,
                             Texture3DContext& context)
{
  Value* temp0 = theArgList->item(0)->evaluate(context);
  Value* temp1 = theArgList->item(1)->evaluate(context);
  
  //collect directed illumination 
  Vector3D colorValue = (Vector3D)*temp0;
  Color specularColor = colorValue;  // Implicit vector3D->Color conversion.
  Real specPow = (Real)*temp1;
  float cosAlpha;
  Real RV;
  Color specularIllumination(0,0,0);
  Vector3D normal = context.getNormalWCS();
  Vector3D toView = (context.getIncidencePosition() - 
                     context.getPositionWCS()).normalized();

  forEachLight(DirectedLight, dirLight) {
    dirLight->getDirection(context);
    cosAlpha = normal ^ context.getLightDirection();
    if ((cosAlpha > 0) && dirLight->isVisible(context)) {
      dirLight->getIllumination(context);
      RV = fabs((2*normal*cosAlpha-context.getLightDirection())^toView);
      specularIllumination += context.getIllumination() * (float)pow(RV, specPow);
    }        
  }
  
  delete temp0;
  delete temp1;
  return new Value(Vector3D(specularColor * specularIllumination));
}

//____________________________________________________________________Phong

SFPhong::SFPhong()
{
  myRequiredParameterNumber = 4;
}

Value* SFPhong::evaluate(List<ShaderExpNode*>* theArgList,
                         Texture3DContext& context)
{
  Value* temp0 = theArgList->item(0)->evaluate(context);
  Value* temp1 = theArgList->item(1)->evaluate(context);
  Value* temp2 = theArgList->item(2)->evaluate(context);
  Value* temp3 = theArgList->item(3)->evaluate(context);      
  Vector3D colorValue;
  
  // collect ambient illumination
  colorValue = (Vector3D)*temp0;
  Color ambientColor = colorValue;
  Color ambientIllumination(0,0,0);
  
  forEachLight(AmbientLight, ambLight) {
    ambLight->getIllumination(context);
    ambientIllumination += context.getIllumination();
  }
  
  // collect directed illumination
  colorValue = (Vector3D)*temp1;
  Color diffuseColor = colorValue;
  colorValue = (Vector3D)*temp2;
  Color specularColor = colorValue;
  Real specPow = (Real)*temp3;
  float cosAlpha;
  Real RV;
  Color directedIllumination(0,0,0);
  Color specularIllumination(0,0,0);
  Vector3D normal = context.getNormalWCS();
  Vector3D toView = (context.getIncidencePosition() - 
                     context.getPositionWCS()).normalized();

  forEachLight(DirectedLight, dirLight) {
    dirLight->getDirection(context);
    cosAlpha = normal ^ context.getLightDirection();
    if (cosAlpha > 0) {
      dirLight->getIllumination(context);
      directedIllumination += context.getIllumination() * cosAlpha;
      RV = fabs((2*normal*cosAlpha-context.getLightDirection())^toView);
      specularIllumination += context.getIllumination() * (float)pow(RV, specPow);
    }        
  }
  
  delete temp0;
  delete temp1;
  delete temp2;
  delete temp3;
  return new Value(Vector3D(ambientColor * ambientIllumination +
                            diffuseColor* directedIllumination +
                            specularColor * specularIllumination));
}

//____________________________________________________________________CMult

SFCMult::SFCMult()
{
  myRequiredParameterNumber = 2;
}


Value* SFCMult::evaluate(List<ShaderExpNode*>* theArgList,
                         Texture3DContext& context)
{
  Value* temp0 = theArgList->item(0)->evaluate(context);
  Value* temp1 = theArgList->item(1)->evaluate(context);
  Vector3D color1 = (Vector3D)*temp0;
  Vector3D color2 = (Vector3D)*temp1;
  
  Vector3D retcolor = Vector3D(color1.x() * color2.x(),
                               color1.y() * color2.y(),
                               color1.z() * color2.z());

  delete temp0;
  delete temp1;
  return new Value(retcolor);
}

//____________________________________________________________________Mix

SFMix::SFMix()
{
  myRequiredParameterNumber = 3;
}


Value* SFMix::evaluate(List<ShaderExpNode*>* theArgList,
                       Texture3DContext& context)
{
  Value* temp0 = theArgList->item(0)->evaluate(context);
  Value* temp1 = theArgList->item(1)->evaluate(context);
  Value* temp2 = theArgList->item(2)->evaluate(context);
  Vector3D color1 = (Vector3D)*temp0;
  Vector3D color2 = (Vector3D)*temp1;
  Real  mixval = (Real)*temp2;

  delete temp0;
  delete temp1;
  delete temp2;
  return new Value((1 - mixval) * color1 + mixval * color2);
}

//____________________________________________________________________Trace

SFTrace::SFTrace()
{
  myRequiredParameterNumber = 2;
}

Value* SFTrace::evaluate(List<ShaderExpNode*>* theArgList,
                         Texture3DContext& context)
{
  Value* temp0 = theArgList->item(0)->evaluate(context);
  Value* temp1 = theArgList->item(1)->evaluate(context);
  Vector3D from = (Vector3D)*temp0;
  Vector3D dir = (Vector3D)*temp1;
  Color retColor = context.getColor();
  
  Ray3D* newRay = Ray3DFactory::createSecondaryRay(from, dir, context.getIncidenceRay());
  Ray3DUtilities::shadeSecondary(newRay, retColor, context);

  delete temp0;
  delete temp1;
  delete newRay;
  return new Value(Vector3D(retColor));
}

/************************************************************************
 *                MAPPING FUNCTIONS                                     *
 ************************************************************************/

//____________________________________________________________________GetUV

SFGetUV::SFGetUV()
{
  myRequiredParameterNumber = 3;
}

Value* SFGetUV::evaluate(List<ShaderExpNode*>* theArgList,
                         Texture3DContext& context)
{
  // Calculates the u- and v-Parameter by directly mapping
  // the point's coordinates onto a sphere.
  // uParam and vParam are additional parameters for determining
  // how many tiles on which part of the surface have to be mapped.
  // The x-component of the uParam- and vParam-vector contains the
  // "left" ("lower") boundary, the y-component the "right" ("upper").
  // The z-component contains the number of tiles that have
  // to be mapped.
  // An example: uParam = (.25,.5,2), vParam = (.25,.75,3):
  // This will map 2x3 copies of the picture onto
  // the area [[.25,25],[.5,.75]];

  Value* temp0 = theArgList->item(0)->evaluate(context);
  Value* temp1 = theArgList->item(1)->evaluate(context);
  Value* temp2 = theArgList->item(2)->evaluate(context);
  Vector3D pos = (Vector3D)*temp0;
  Vector3D uParam = (Vector3D)*temp1;
  Vector3D vParam = (Vector3D)*temp2;    

  Vector3D BBoxMin = context.getObject()->getBounds().getMin();
  Vector3D BBoxMax = context.getObject()->getBounds().getMax();
  Vector3D transVec = (BBoxMin + BBoxMax) / 2;
  transVec = context.getObject()->getTransform().invTransformAsPoint(transVec);
  Vector3D tempPos = pos - transVec;

  Vector3D retVector;        // retVector will be of form (u, v, 0);

  // spherical mapping
  Vector3D unit = tempPos.normalized();
  Real phi = acos(unit.z());
  Real theta = unit.y() / sqrt(1 - unit.z() * unit.z()); 
  if (fabs(theta) > 1) {
    retVector = Vector3D(0,1-phi / M_PI,0);
    return new Value(retVector);
  }
  theta = acos(-theta) / (2 * M_PI);
  if (unit.x() > 0)
    retVector = Vector3D(theta,1-phi / M_PI, 0);
  else
    retVector = Vector3D(1-theta,1-phi / M_PI, 0);
  

  if (retVector.x() >= uParam.x() && retVector.x() <= uParam.y()) {
    // map into the interval [uParam.x(),uParam.y()]
    retVector.x() = (retVector.x() - uParam.x()) / (uParam.y() - uParam.x());
    // tile with factor uParam.z()
    retVector.x() = frac(uParam.z() * retVector.x());
  }
  else
    retVector.x() = -1;
  
  if (retVector.y() >= vParam.x() && retVector.y() <= vParam.y()) {
    // map into the interval [vParam.x(),vParam.y()]
    retVector.y() = (retVector.y() - vParam.x()) / (vParam.y() - vParam.x());
    // tile with factor vParam.z()
    retVector.y() = frac(vParam.z() * retVector.y());
  }
  else
    retVector.y() = -1;
 
  delete temp0;
  delete temp1;
  delete temp2;    
  return new Value(retVector);
}

//____________________________________________________________________TextureMap

SFTextureMap::SFTextureMap()
{
  myRequiredParameterNumber = 2;
}

Value* SFTextureMap::evaluate(List<ShaderExpNode*>* theArgList,
                              Texture3DContext& context)
{
  ShaderExpNode* tempExp = theArgList->item(0);
  Value* temp0 = tempExp->evaluate(context);   
  SymTable<RCString, AbstractPixmap*>* thePixmaps = tempExp->getPixmaps();
  RCString pixmapName  = (RCString)*temp0;

  // HACK !!! to delete the last "
  if (pixmapName.length() > 1 && pixmapName[pixmapName.length()-1] == '\"')
    pixmapName = pixmapName(0,pixmapName.length()-2);

  AbstractPixmap* aPixmap;
  if(!thePixmaps->lookup(pixmapName, aPixmap)) {
    aPixmap = ImageReader::createPixmap(pixmapName);
    thePixmaps->insert(pixmapName, aPixmap);
  }

  //
  // Defensive! ImageReader::createPixmap() may return a NULL pointer!
  //
  if (aPixmap == NULL)
    return new Value(0,0,0);
    
  Value* temp1 = theArgList->item(1)->evaluate(context);
  Real u = ((Vector3D)*temp1).x();
  Real v = ((Vector3D)*temp1).y();

  Real aaDistance = 0.01;
  int xres = aPixmap->getResolutionX();
  int yres = aPixmap->getResolutionY();
  Vector3D retVector = context.getColor();
  
  if (u >= 0 && v >= 0) { 
    Real x = fmod((u * xres),xres);
    Real y = fmod((v * yres),yres);
    retVector = TextureUtilities::calculateTexelValue(aPixmap,x,y,aaDistance);
  }
  delete temp0;
  delete temp1; 
  return new Value(retVector);
}

//____________________________________________________________________Bump

SFBump::SFBump()
{
  myRequiredParameterNumber = 2;
}

Value* SFBump::evaluate(List<ShaderExpNode*>* theArgList,
                        Texture3DContext& context)
{ 
  Value* temp0 = theArgList->item(0)->evaluate(context);
  Value* temp1 = theArgList->item(1)->evaluate(context);
  Real freq1 = (Real)*temp0;
  Real freq2 = (Real)*temp1;

  Vector3D pos = context.getPositionTCS();
  Vector3D temp = Vector3D(freq2 * pos);
  Vector3D perturb =
          2 * Vector3D(TextureUtilities::DNoise3(temp)) - Vector3D(1, 1, 1);

  delete temp0;
  delete temp1;
  return new Value(freq1 * perturb);
}
