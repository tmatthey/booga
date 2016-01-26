/*
 * Nurbs3DAttr.h
 *
 * Copyright (C) 1995, Richard Baechler <baechler@iam.unibe.ch>
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
 *  $Id: Nurbs3DAttr.h,v 1.3 1996/01/12 16:09:41 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Nurbs3DAttr_H
# define _Nurbs3DAttr_H

#include "booga/base/List.h"
#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"
#include "booga/nurbs/Nurbs3DTypes.h"

class Nurbs3D;            // Forward declarations
class NurbsCompound3D;
class NurbsData3D;
class Nurbs3DKnots;
class Nurbs3DPoints;
class Nurbs3DWeights;

//__________________________________________________________________ Nurbs3DAttr

class Nurbs3DAttr : public ObjectAttr {
declareRTTI(Nurbs3DAttr);
// enable RTTI support

public:
  virtual void setAttribute (Nurbs3D *nurbs) = 0;

  // Interface to class Nurbs3D. Whenever setSpecifier(specifier)
  // is called for an instance of class Nurbs3D,
  // specifier->setAttribute(Nurbs3DObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Nurbs3D
  // object by executing the right method. The corresponding call graph:
  //
  //   Nurbs3DObject->setSpecifier(specifier)
  //       specifier->setAttribute(Nurbs3DObject)
  //           Nurbs3DObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//______________________________________________________________ Nurbs3DDataAttr

class Nurbs3DDataAttr : public ObjectAttr {
declareRTTI(Nurbs3DPathAttr);
// enable RTTI support
public:
  virtual void setAttribute (NurbsData3D *nurbs) = 0;
};

//______________________________________________________________ Nurbs3DPathAttr

class Nurbs3DPathAttr : public ObjectAttr {
declareRTTI(Nurbs3DPathAttr);
// enable RTTI support
public:
  virtual void setAttribute (NurbsCompound3D *nurbs) = 0;
  virtual void adoptCurve (Nurbs3D *curve) = 0;
};

//____________________________________________________________ Nurbs3DAttrUKnots

class Nurbs3DAttrUKnots : public Nurbs3DAttr {
declareRTTI(Nurbs3DAttrUKnots);
// enable RTTI support

public:
  Nurbs3DAttrUKnots (void) : myKnots (NULL) {}
  Nurbs3DAttrUKnots (Exemplar) : myKnots (NULL) {}
  virtual Makeable* make (RCString &errMsg, const List<Value*> *parameters) const;
  virtual void setAttribute (Nurbs3D *nurbs);

protected:
  Nurbs3DKnots *myKnots;
};

//____________________________________________________________ Nurbs3DAttrVKnots

class Nurbs3DAttrVKnots : public Nurbs3DAttr {
declareRTTI(Nurbs3DAttrVKnots);
// enable RTTI support

public:
  Nurbs3DAttrVKnots (void) : myKnots (NULL) {}
  Nurbs3DAttrVKnots (Exemplar) : myKnots (NULL) {}
  virtual Makeable* make (RCString &errMsg, const List<Value*> *parameters) const;
  virtual void setAttribute (Nurbs3D *nurbs);

protected:
  Nurbs3DKnots *myKnots;
};

//________________________________________________________ NrbElementAttrVectors

class Nurbs3DAttrVectors : public Nurbs3DAttr {
declareRTTI(Nurbs3DAttrVectors);
// enable RTTI support

public:
  Nurbs3DAttrVectors (void) : myVectors (NULL) {}
  Nurbs3DAttrVectors (Exemplar) : myVectors (NULL) {}
  virtual Makeable* make (RCString &errMsg, const List<Value*> *parameters) const;
  virtual void setAttribute (Nurbs3D *nurbs);

protected:
   Nurbs3DPoints *myVectors;
};

//___________________________________________________________ Nurbs3DAttrWeights

class Nurbs3DAttrWeights : public Nurbs3DAttr {
declareRTTI(Nurbs3DAttrWeights);
// enable RTTI support

public:
  Nurbs3DAttrWeights (void) : myWeights (NULL) {}
  Nurbs3DAttrWeights (Exemplar) : myWeights (NULL) {}
  virtual Makeable* make (RCString &errMsg, const List<Value*> *parameters) const;
  virtual void setAttribute (Nurbs3D *nurbs);

protected:
  Nurbs3DWeights *myWeights;
};

//_____________________________________________________ NrbElementAttrEvaluation

class Nurbs3DAttrEvaluation : public Nurbs3DAttr {
declareRTTI(Nurbs3DAttrEvaluation);
// enable RTTI support

public:
  Nurbs3DAttrEvaluation (Exemplar) {}
  virtual Makeable* make (RCString &errMsg, const List<Value*> *parameters) const;
  virtual void setAttribute (Nurbs3D *nurbs);

protected:
   Nurbs3DTypes::EEvaluation myType;
};

//_______________________________________________________ NrbElementAttrDiameter

class Nurbs3DAttrDiameter : public Nurbs3DAttr {
declareRTTI(Nurbs3DAttrDiameter);
// enable RTTI support

public:
  Nurbs3DAttrDiameter (Exemplar) {}
  virtual Makeable* make (RCString &errMsg, const List<Value*> *parameters) const;
  virtual void setAttribute (Nurbs3D *nurbs);

protected:
  Real myDiameter;
};

//________________________________________________________ Nurbs3DAttrDataPoints

class Nurbs3DAttrDataPoints : public Nurbs3DDataAttr {
declareRTTI(Nurbs3DAttrDataPoints);
// enable RTTI support

public:
  Nurbs3DAttrDataPoints (void) : myCurveData (NULL), mySurfaceData (NULL) {}
  Nurbs3DAttrDataPoints (Exemplar) : myCurveData (NULL), mySurfaceData (NULL) {}
  virtual Makeable* make (RCString &errMsg, const List<Value*> *parameters) const;
  virtual void setAttribute (NurbsData3D *nurbs);

protected:
  PtArray1D *myCurveData;
  PtArray2D *mySurfaceData;
};

//___________________________________________________________ Nurbs3DAttrSection

class Nurbs3DAttrSection : public Nurbs3DPathAttr {
declareRTTI(Nurbs3DAttrSection);
// enable RTTI support

public:
  Nurbs3DAttrSection (void) : mySectionCurve (NULL) {}
  Nurbs3DAttrSection (Exemplar) : mySectionCurve (NULL) {}
  virtual Makeable* make (RCString &errMsg, const List<Value*> *parameters) const;
  virtual void setAttribute (NurbsCompound3D *nurbs);
  virtual int setSpecifier (RCString &errMsg, Makeable *specifier);

public:
  virtual void adoptCurve (Nurbs3D *curve);

protected:
  Nurbs3D *mySectionCurve;
};

//______________________________________________________________ Nurbs3DAttrPath

class Nurbs3DAttrPath : public Nurbs3DPathAttr {
declareRTTI(Nurbs3DAttrPath);
// enable RTTI support

public:
  Nurbs3DAttrPath (void) : myPathCurve (NULL) {}
  Nurbs3DAttrPath (Exemplar) : myPathCurve (NULL) {}
  virtual Makeable* make (RCString &errMsg, const List<Value*> *parameters) const;
  virtual void setAttribute (NurbsCompound3D *nurbs);
  virtual int setSpecifier (RCString &errMsg, Makeable *specifier);

public:
  virtual void adoptCurve (Nurbs3D *curve);

protected:
  Nurbs3D *myPathCurve;
};

#endif // _Nurbs3DAttr_H
