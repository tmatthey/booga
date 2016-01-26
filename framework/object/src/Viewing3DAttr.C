/*
 * Viewing3DAttr.C
 *
 * Copyright (C) 1994-96, University of Berne, Switzerland
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
 */

#include "booga/base/Value.h"
#include "booga/base/Report.h"
#include "booga/object/Viewing3DAttr.h"
#include "booga/object/Viewing3D.h"

//________________________________________________________________ Viewing3DAttr

implementRTTI(Viewing3DAttr, ObjectAttr);

//_____________________________________________________________ Viewing3DAttrEye

implementRTTI(Viewing3DAttrEye, Viewing3DAttr);

Viewing3DAttrEye::Viewing3DAttrEye(const Vector3D& eye)
: myEye(eye)
{}

Makeable* Viewing3DAttrEye::make(RCString& errMsg,
                                 const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector3D, value);

  return new Viewing3DAttrEye(value);
}

void Viewing3DAttrEye::setAttribute(Viewing3D* viewing3d) const
{
  viewing3d->setEye(myEye);
}

//__________________________________________________________ Viewing3DAttrLookat

implementRTTI(Viewing3DAttrLookat, Viewing3DAttr);

Viewing3DAttrLookat::Viewing3DAttrLookat(const Vector3D& lookat)
: myLookat(lookat)
{}

Makeable* Viewing3DAttrLookat::make(RCString& errMsg,
                                    const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector3D, value);

  return new Viewing3DAttrLookat(value);
}

void Viewing3DAttrLookat::setAttribute(Viewing3D* viewing3d) const
{
  viewing3d->setLookat(myLookat);
}

//______________________________________________________________ Viewing3DAttrUp

implementRTTI(Viewing3DAttrUp, Viewing3DAttr);

Viewing3DAttrUp::Viewing3DAttrUp(const Vector3D& up)
: myUp(up)
{}

Makeable* Viewing3DAttrUp::make(RCString& errMsg,
                                const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector3D, value);

  return new Viewing3DAttrUp(value);
}

void Viewing3DAttrUp::setAttribute(Viewing3D* viewing3d) const
{
  viewing3d->setUp(myUp);
}

//_____________________________________________________________ Viewing3DAttrFov

implementRTTI(Viewing3DAttrFov, Viewing3DAttr);

Viewing3DAttrFov::Viewing3DAttrFov(const Real& hFov, const Real& vFov)
: myHFov(hFov), myVFov(vFov)
{}

Makeable* Viewing3DAttrFov::make(RCString& errMsg,
                                 const List<Value*>* parameters) const
{
  long provided_ = (!parameters ? 0 : parameters->count());
  if (provided_ < 1 || provided_ > 2) {
    extern char* form(const char * ...);
    errMsg = RCString("between 1 and 2 parameter(s) required, ")
             + form("%ld", provided_) + " provided";
    return NULL;
  }

  getParameter(1, Real, hFov);
  if (!(hFov > EPSILON)) {
    errMsg = "negative value for field of view";
    return NULL;
  }

  Real vFov = -1;
  if (provided_ > 1) {
    getParameter(2, Real, tmpVal);
    vFov = tmpVal;
    if (!(vFov > EPSILON)) {
      errMsg = "negative value for field of view";
      return NULL;
    }
  }

  return new Viewing3DAttrFov(dtor(hFov), dtor(vFov));
}

void Viewing3DAttrFov::setAttribute(Viewing3D* viewing3d) const
{
  viewing3d->setFov(myHFov, myVFov);
}

//___________________________________________________ Viewing3DAttrEyeSeparation

implementRTTI(Viewing3DAttrEyeSeparation, Viewing3DAttr);

Viewing3DAttrEyeSeparation::Viewing3DAttrEyeSeparation(const Real& eyeSep)
: myEyeSep(eyeSep)
{}

Makeable* Viewing3DAttrEyeSeparation::make(RCString& errMsg,
                                           const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, value);

  return new Viewing3DAttrEyeSeparation(value);
}

void Viewing3DAttrEyeSeparation::setAttribute(Viewing3D* viewing3d) const
{
  viewing3d->setEyeSeparation(myEyeSep);
}

//______________________________________________________ Viewing3DAttrResolution

implementRTTI(Viewing3DAttrResolution, Viewing3DAttr);

Viewing3DAttrResolution::Viewing3DAttrResolution(const Real& resX, const Real& resY)
: myResX(resX), myResY(resY)
{}

Makeable* Viewing3DAttrResolution::make(RCString& errMsg,
                                        const List<Value*>* parameters) const
{
  checkParameterNumber(2);
  getParameter(1, Real, resX);
  if (!((frac(resX) < EPSILON) && resX >= 1)) {
    Report::warning("expecting integer number (real passed -> converting to int)");
  }

  getParameter(2, Real, resY);
  if (!((frac(resY) < EPSILON) && resY >= 1)) {
    Report::warning("expecting integer number (real passed -> converting to int)");
  }

  return new Viewing3DAttrResolution(resX, resY);
}

void Viewing3DAttrResolution::setAttribute(Viewing3D* viewing3d) const
{
  viewing3d->setResolution(int(rint(myResX)), int(rint(myResY)));
}

