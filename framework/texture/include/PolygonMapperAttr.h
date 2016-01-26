/*
 * PolygonMapperAttr.h
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

#ifndef _PolygonMapperAttr_H
#define _PolygonMapperAttr_H

#include "booga/base/Value.h"
#include "booga/base/Color.h"
#include "booga/object/Texture3DAttr.h"
#include "booga/base/mathutilities.h"

class PolygonMapper;
class RCString;

//____________________________________________________________ PolygonMapperAttr

class PolygonMapperAttr : public Texture3DAttr {
declareRTTI(PolygonMapperAttr);
// enable RTTI support

public:
  virtual void setAttribute(PolygonMapper* polygonmapper) const = 0;
  // Interface to class PolygonMapper. Whenever setSpecifier(specifier)
  // is called for an instance of class PolygonMapper,
  // specifier->setAttribute(polygonmapperObject) will be called. Method
  // setAttribute has to alter the appropriate member of the PolygonMapper
  // object by executing the right method. The corresponding call graph:
  //
  //   polygonmapperObject->setSpecifier(specifier)
  //       specifier->setAttribute(polygonmapperObject)
  //           polygonmapperObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//____________________________________________________ PolygonMapperAttrSpecular

class PolygonMapperAttrSpecular : public PolygonMapperAttr {
declareRTTI(PolygonMapperAttrSpecular);
// enable RTTI support

public:
  PolygonMapperAttrSpecular(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(PolygonMapper* polygonmapper) const;
  PolygonMapperAttrSpecular(const Color& specular);

private:
  Color mySpecular;
};

//_____________________________________________________ PolygonMapperAttrSpecPow

class PolygonMapperAttrSpecPow : public PolygonMapperAttr {
declareRTTI(PolygonMapperAttrSpecPow);
// enable RTTI support

public:
  PolygonMapperAttrSpecPow(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(PolygonMapper* polygonmapper) const;
  PolygonMapperAttrSpecPow(const int& specPow);

private:
  int mySpecPow;
};

//________________________________________________ PolygonMapperAttrReflectivity

class PolygonMapperAttrReflectivity : public PolygonMapperAttr {
declareRTTI(PolygonMapperAttrReflectivity);
// enable RTTI support

public:
  PolygonMapperAttrReflectivity(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(PolygonMapper* polygonmapper) const;
  PolygonMapperAttrReflectivity(const Real& reflectivity);

private:
  Real myReflectivity;
};

//_____________________________________________________ PolygonMapperAttrAmbient

class PolygonMapperAttrAmbient : public PolygonMapperAttr {
declareRTTI(PolygonMapperAttrAmbient);
// enable RTTI support

public:
  PolygonMapperAttrAmbient(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(PolygonMapper* polygonmapper) const;
  PolygonMapperAttrAmbient(const Color& ambient);

private:
  Color myAmbient;
};

#endif // _PolygonMapperAttr_H
