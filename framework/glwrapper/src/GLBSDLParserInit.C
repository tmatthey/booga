/*
 * GLBSDLParserInit.C 
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: GLBSDLParserInit.C,v 1.6 1998/01/07 16:28:40 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/object/Camera3D.h"

#include "booga/texture/WhittedAttr.h"
#include "booga/texture/PhongAttr.h"
#include "booga/texture/MatteAttr.h"
#include "booga/texture/PolygonMapperAttr.h"

#include "booga/glwrapper/GLConstantTexture2D.h"
#include "booga/glwrapper/GLInterpolatorTexture2D.h"
#include "booga/glwrapper/GLWhitted.h"
#include "booga/glwrapper/GLMatte.h"
#include "booga/glwrapper/GLPhong.h"
#include "booga/glwrapper/GLPolygonMapper.h"

#include "booga/component/BSDLParser.h"
#include "booga/component/BSDLParserInit.h"
#include "booga/glwrapper/GLBSDLParserInit.h"

//___________________________________________________________ Global Namespace

void initGLBSDLParserGlobalNS()
{
  initBSDLParserGlobalNS();
}

//_______________________________________________________________ Namespace 3D

void initGLBSDLParser3DNS()
{
  initBSDLParser3DNS();
  
  // Change exemplar for GL specific classes
  unregisterParserAttribute("3D", ambient, whitted);
  unregisterParserAttribute("3D", diffuse, whitted);
  unregisterParserAttribute("3D", transparency, whitted);
  unregisterParserAttribute("3D", reflectivity, whitted);
  unregisterParserAttribute("3D", refractionIndex, whitted);
  unregisterParserExemplar("3D", whitted);
  
  registerParserExemplar("3D", whitted, GLWhitted);
  registerParserAttribute("3D", ambient, whitted, WhittedAttrAmbient);
  registerParserAttribute("3D", diffuse, whitted, WhittedAttrDiffuse);
  registerParserAttribute("3D", transparency, whitted, WhittedAttrTransparency);
  registerParserAttribute("3D", reflectivity, whitted, WhittedAttrReflectivity);
  registerParserAttribute("3D", refractionIndex, whitted, WhittedAttrRefractionIndex);

  //-----

  unregisterParserAttribute("3D", ambient, phong);
  unregisterParserAttribute("3D", diffuse, phong);
  unregisterParserAttribute("3D", specular, phong);
  unregisterParserAttribute("3D", specpow, phong);
  unregisterParserExemplar("3D", phong);

  registerParserExemplar("3D", phong, GLPhong);
  registerParserAttribute("3D", ambient, phong, PhongAttrAmbient);
  registerParserAttribute("3D", diffuse, phong, PhongAttrDiffuse);
  registerParserAttribute("3D", specular, phong, PhongAttrSpecular);
  registerParserAttribute("3D", specpow, phong, PhongAttrSpecPow);

  //-----

  unregisterParserAttribute("3D", ambient, polygonmapper);
  unregisterParserAttribute("3D", specular, polygonmapper);
  unregisterParserAttribute("3D", specpow, polygonmapper);
  unregisterParserAttribute("3D", reflectivity, polygonmapper);
  unregisterParserExemplar("3D", polygonmapper);

  registerParserExemplar("3D", polygonmapper, GLPolygonMapper);
  registerParserAttribute("3D", ambient, polygonmapper, PolygonMapperAttrAmbient);
  registerParserAttribute("3D", specular, polygonmapper, PolygonMapperAttrSpecular);
  registerParserAttribute("3D", specpow, polygonmapper, PolygonMapperAttrSpecPow);
  registerParserAttribute("3D", reflectivity, polygonmapper, PolygonMapperAttrReflectivity);

  // ---
  
  unregisterParserAttribute("3D", ambient, matte);
  unregisterParserAttribute("3D", diffuse, matte);
  unregisterParserExemplar("3D", matte);

  registerParserExemplar("3D", matte, GLMatte);
  registerParserAttribute("3D", ambient, matte, MatteAttrAmbient);
  registerParserAttribute("3D", diffuse, matte, MatteAttrDiffuse);

}

//_______________________________________________________________ Namespace 2D

void initGLBSDLParser2DNS()
{
  initBSDLParser2DNS();

  // Change exemplar for GL specific classes
  unregisterParserExemplar("2D", color);
  registerParserExemplar("2D", color, GLConstantTexture2D);

  unregisterParserExemplar("2D", interpolate);
  registerParserExemplar("2D", interpolate, GLInterpolatorTexture2D);
}

