/*
 * AnimationFunction.C
 *
 * Copyright (C) 1996, Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: AnimationFunction.C,v 1.3 1996/11/13 09:38:00 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include <strstream.h>
#include "booga/base/mathutilities.h"
#include "booga/base/Report.h"
#include "booga/animation/AnimationFunction.h"

// ____________________________________________________________________ AnimationFunction

AnimationFunction::~AnimationFunction() {}

void AnimationFunction::setParameters(Real start, Real end, Real step)
{
  if ((start >= 0) && (end >= 0) && (step >= 0) && (start <= 1) &&
      (end <= 1) && (step <= 1) && ( start <= end)){
    myStart = start;
    myEnd   = end;
    myStep  = step;
  }
  else {
    ostrstream os;
    os << "[AnimationFunction::setParameters] 0 <= start, end, step <= 1 and start <= end. "
       << "Default start = 0, end = 1, step = 0.";
    Report::recoverable(os);
    myStart = 0;
    myEnd   = 1;
    myStep  = 0;
  }
}  

Real AnimationFunction::AFTransformation(Real startFrame, Real endFrame, Real frame)
{
  Real factor;
  Real start = getStart();
  Real end   = getEnd();
  Real step  = getStep();

  if (frame <= (startFrame + EPSILON))
    factor = start;
  else if ((frame < (endFrame - EPSILON)) && ( start < end)){
    factor = start + ((frame - startFrame)/ (endFrame - startFrame)) * (end - start);
    if ((step - EPSILON) > 0)
      factor = step * floor(factor / step + EPSILON);     // step  
  }
  else
    factor = end;
   

  return factor;
}

// ____________________________________________________________________ AFConst

AFConst::AFConst(Real start, Real end, Real step)
{
  setParameters(start, end, step);
}

Real AFConst::computeValue(Real, Real, Real)
{
  return getStart();
}

AnimationFunction* AFConst::copy() const
{
  return new AFConst(*this);
}

static const RCString AFConstKeyword("const");

RCString AFConst::getKeyword() const {
  return AFConstKeyword;
}

// ____________________________________________________________________ AFId

AFId::AFId(Real start, Real end, Real step)
{
  setParameters(start, end, step);
}

Real AFId::computeValue(Real startFrame, Real endFrame, Real frame)
{
  return AFTransformation(startFrame, endFrame, frame);
}

AnimationFunction* AFId::copy() const
{
  return new AFId(*this);
}

static const RCString AFIdKeyword("id");

RCString AFId::getKeyword() const {
  return AFIdKeyword;
}

// ____________________________________________________________________ AFSin

AFSin::AFSin(Real start, Real end, Real step)
{
  setParameters(start, end, step);
}

Real AFSin::computeValue(Real startFrame, Real endFrame, Real frame)
{
  return sin(AFTransformation(startFrame, endFrame, frame) * M_PI * 20.0);
}

AnimationFunction* AFSin::copy() const
{
  return new AFSin(*this);
}

static const RCString AFSinKeyword("sin");

RCString AFSin::getKeyword() const {
  return AFSinKeyword;
}

// ____________________________________________________________________ AFSaw

AFSaw::AFSaw(Real start, Real end, Real step)
{
  setParameters(start, end, step);
}

Real AFSaw::computeValue(Real startFrame, Real endFrame, Real frame)
{ 
  Real x = AFTransformation(startFrame, endFrame, frame);
  
  if ((x + EPSILON) >= 1)
    return 0;
  else
    return x; 
}

AnimationFunction* AFSaw::copy() const
{
  return new AFSaw(*this);
}

static const RCString AFSawKeyword("saw");

RCString AFSaw::getKeyword() const {
  return AFSawKeyword;
}

// ____________________________________________________________________ AFStep

AFStep::AFStep(Real start, Real end, Real Step)
{
  setParameters(start, end, Step);
}

Real AFStep::computeValue(Real startFrame, Real endFrame, Real frame)
{
  if (AFTransformation(startFrame, endFrame, frame) < (0.5 - EPSILON))
    return 0;
  else
    return 1;
}

AnimationFunction* AFStep::copy() const
{
  return new AFStep(*this);
}

static const RCString AFStepKeyword("saw");

RCString AFStep::getKeyword() const {
  return AFStepKeyword;
}

// ____________________________________________________________________ AFPulse

AFPulse::AFPulse(Real start, Real end, Real step)
{
  setParameters(start, end, step);
}

Real AFPulse::computeValue(Real startFrame, Real endFrame, Real frame)
{
  Real x = AFTransformation(startFrame, endFrame, frame);
  
  if ((x < (0.25 - EPSILON)) || (x >= (0.75 - EPSILON)))
    return 0;
  else
    return 1; 
}

AnimationFunction* AFPulse::copy() const
{
  return new AFPulse(*this);
}

static const RCString AFPulseKeyword("pulse");

RCString AFPulse::getKeyword() const {
  return AFPulseKeyword;
}

// ____________________________________________________________________ AFSmoothStep

AFSmoothStep::AFSmoothStep(Real start, Real end, Real step)
{
  setParameters(start, end, step);
}

Real AFSmoothStep::computeValue(Real startFrame, Real endFrame, Real frame)
{
  Real x = AFTransformation(startFrame, endFrame, frame);
  return (x * x * (3 - 2 * x));
}

AnimationFunction* AFSmoothStep::copy() const
{
  return new AFSmoothStep(*this);
}

static const RCString AFSmoothStepKeyword("smoothstep");

RCString AFSmoothStep::getKeyword() const {
  return AFSmoothStepKeyword;
}

// ____________________________________________________________________ AFTriangle

AFTriangle::AFTriangle(Real start, Real end, Real step)
{
  setParameters(start, end, step);
}

Real AFTriangle::computeValue(Real startFrame, Real endFrame, Real frame)
{
  Real x = AFTransformation(startFrame, endFrame, frame);
  
  if (x < 0.5)
    return (x * 2);
  else
    return (2 - x * 2); 
}

AnimationFunction* AFTriangle::copy() const
{
  return new AFTriangle(*this);
}

static const RCString AFTriangleKeyword("triangle");

RCString AFTriangle::getKeyword() const {
  return AFTriangleKeyword;
}

// ____________________________________________________________________ AFSqrt

AFSqrt::AFSqrt(Real start, Real end, Real step)
{
  setParameters(start, end, step);
}

Real AFSqrt::computeValue(Real startFrame, Real endFrame, Real frame)
{
  return sqrt(fabs(AFTransformation(startFrame, endFrame, frame)*2-1)); 
}

AnimationFunction* AFSqrt::copy() const
{
  return new AFSqrt(*this);
}

static const RCString AFSqrtKeyword("sqrt");

RCString AFSqrt::getKeyword() const {
  return AFSqrtKeyword;
}

// ____________________________________________________________________ AFQuad

AFQuad::AFQuad(Real start, Real end, Real step)
{
  setParameters(start, end, step);
}

Real AFQuad::computeValue(Real startFrame, Real endFrame, Real frame)
{
  Real x = AFTransformation(startFrame, endFrame, frame);
  
  return (4 * x * x - 4 * x + 1);  // (((x-0.5)*2)^2)
}

AnimationFunction* AFQuad::copy() const
{
  return new AFQuad(*this);
}


static const RCString AFQuadKeyword("quad");

RCString AFQuad::getKeyword() const {
  return AFQuadKeyword;
}

