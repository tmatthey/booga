/*
 * $RCSfile: BSDLParserInit.C,v $
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: BSDLParserInit.C,v 1.44 1998/05/22 12:25:20 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/component/BSDLParser.h"
#include "booga/component/BSDLParserInit.h"

// Global NS
#include "booga/object/MakeableAttr.h"
#include "booga/object/Function.h"

// 3D NS
#include "booga/object/World3D.h"
#include "booga/object/Transform3D.h"
#include "booga/object/Transform3DAttr.h"
#include "booga/object/Texture3DList.h"
#include "booga/object/ConstantTexture3D.h"
#include "booga/object/Checker.h"
#include "booga/object/CheckerAttr.h"
#include "booga/object/Function.h"
#include "booga/object/List3D.h"
#include "booga/object/LevelOfDetail3D.h"
#include "booga/object/Grid3D.h"
#include "booga/object/Primitive3DAttr.h"
#include "booga/object/Triangle3D.h"
#include "booga/object/TriangleList3D.h"
#include "booga/object/NullObject3D.h"
#include "booga/object/MultiObject3D.h"
#include "booga/object/Box3D.h"
#include "booga/object/Polygon3D.h"
#include "booga/object/Polygon3DAttr.h"
#include "booga/object/PolygonExtrude.h"
#include "booga/object/PolygonExtrudeAttr.h"
#include "booga/object/Text3D.h"
#include "booga/object/Text3DAttr.h"
#include "booga/object/Sphere3D.h"
#include "booga/object/Disc3D.h"
#include "booga/object/Cylinder3D.h"
#include "booga/object/Cylinder3DAttr.h"
#include "booga/object/Cone3D.h"
#include "booga/object/Cone3DAttr.h"
#include "booga/object/Torus3D.h"
#include "booga/object/Camera3D.h"
#include "booga/object/Camera3DAttr.h"
#include "booga/object/Viewing3D.h"
#include "booga/object/Viewing3DAttr.h"
#include "booga/object/PerspectiveViewing3D.h"
#include "booga/object/OrthographicViewing3D.h"
#include "booga/object/LightSource.h"
#include "booga/object/LightSourceAttr.h"
#include "booga/object/PointLight.h"
#include "booga/object/PointLightAttr.h"
#include "booga/object/GeneralLight.h"
#include "booga/object/AmbientLight.h"
#include "booga/component/File3D.h"
#include "booga/component/URL3D.h"
#include "booga/object/BistableObject3D.h"
#include "booga/object/BistableObject3DAttr.h"
#include "booga/object/BistableObject3DAttr.h"
#include "booga/object/BezierCurve3D.h"
#include "booga/object/InterpolationCurve3D.h"
 
#include "booga/building/Building.h"
#include "booga/building/BuildingAttr.h"
#include "booga/building/BuildingObjectAttr.h"
#include "booga/building/FrontAttr.h"
#include "booga/building/FrontRect.h"
#include "booga/building/FrontSimple.h"
#include "booga/building/FrontTriangle.h"
#include "booga/building/FaceAttr.h"
#include "booga/building/FaceArbour.h"
#include "booga/building/FaceArbourAttr.h"
#include "booga/building/FaceWall.h"
#include "booga/building/FaceTunnel.h"
#include "booga/building/FaceTunnelAttr.h"
#include "booga/building/FaceItem.h"
#include "booga/building/FaceItemAttr.h"
#include "booga/building/RoofAttr.h"
#include "booga/building/RoofBorder.h"
#include "booga/building/RoofFlat.h"
#include "booga/building/RoofLayer.h"
#include "booga/building/RoofPlane.h"
#include "booga/building/RoofPoint.h"
#include "booga/building/RoofUser.h"
#include "booga/building/SnatchRoof.h"
#include "booga/building/BottomAttr.h"
#include "booga/building/BottomBorder.h"
#include "booga/building/BottomBorderAttr.h"
#include "booga/building/BottomFlat.h"
#include "booga/building/BottomUser.h"

#include "booga/nurbs/Nurbs3D.h"
#include "booga/nurbs/Nurbs3DAttr.h"
#include "booga/nurbs/NurbsCircle3D.h"
#include "booga/nurbs/NurbsInterpolation3D.h"
#include "booga/nurbs/NurbsLine3D.h"
#include "booga/nurbs/NurbsPolyLine3D.h"
#include "booga/nurbs/NurbsRevolution3D.h"
#include "booga/nurbs/NurbsSquare3D.h"
#include "booga/nurbs/NurbsSphere3D.h"
#include "booga/nurbs/NurbsSweeping3D.h"
#include "booga/nurbs/NurbsSwinging3D.h"
#include "booga/nurbs/NurbsTorus3D.h"
 
 
#include "booga/texture/Shader.h"
#include "booga/texture/Matte.h"
#include "booga/texture/MatteAttr.h"
#include "booga/texture/Phong.h"
#include "booga/texture/PhongAttr.h"
#include "booga/texture/Whitted.h"
#include "booga/texture/PolygonMapper.h"
#include "booga/texture/PolygonMapperAttr.h"
#include "booga/texture/WhittedAttr.h"
#include "booga/animation/Animation3DAttr.h"
#include "booga/animation/ActionInfo.h"
#include "booga/animation/ActionInfoAttr.h"
#include "booga/animation/Cycle3D.h"
#include "booga/animation/Grow3D.h"
#include "booga/animation/Move3D.h"
#include "booga/animation/Morph3D.h"
#include "booga/animation/Tumble3D.h"
#include "booga/animation/TumblePath3D.h"
#include "booga/animation/TumbleCenter3D.h"
#include "booga/animation/TumbleDirection3D.h"
#include "booga/animation/Turn3D.h"
#include "booga/animation/Shear3D.h"
 
// 2D NS
#include "booga/object/World2D.h"
#include "booga/object/Transform2D.h"
#include "booga/object/Transform2DAttr.h"
#include "booga/object/Function.h"
#include "booga/object/Primitive2D.h"
#include "booga/object/Primitive2DAttr.h"
#include "booga/object/List2D.h"
#include "booga/object/Circle2D.h"
#include "booga/object/Line2D.h"
#include "booga/object/Polygon2D.h"
#include "booga/object/Point2D.h"
#include "booga/object/Text2D.h"
#include "booga/object/Text2DAttr.h"
#include "booga/object/Pixmap2D.h"
#include "booga/object/Camera2D.h"
#include "booga/object/Camera2DAttr.h"
#include "booga/object/Texture2DList.h"
#include "booga/object/ConstantTexture2D.h"
#include "booga/object/InterpolatorTexture2D.h"
#include "booga/object/PatternTexture2D.h"
#include "booga/object/PatternTexture2DAttr.h"
#include "booga/object/PixmapTexture2D.h"
#include "booga/component/File2D.h"
#include "booga/component/URL2D.h"
#include "booga/object/BistableObject2D.h"
#include "booga/object/BistableObject2DAttr.h"
#include "booga/object/BezierPatch3D.h"

//___________________________________________________________ Global Namespace
void initBSDLParserGlobalNS()
{
  registerParserExemplar(ScopedName::getGlobalNS(), sin, FunctionSin);
  registerParserExemplar(ScopedName::getGlobalNS(), cos, FunctionCos);
  registerParserExemplar(ScopedName::getGlobalNS(), tan, FunctionTan);
  registerParserExemplar(ScopedName::getGlobalNS(), asin, FunctionASin);
  registerParserExemplar(ScopedName::getGlobalNS(), acos, FunctionACos);
  registerParserExemplar(ScopedName::getGlobalNS(), atan, FunctionATan);
  registerParserExemplar(ScopedName::getGlobalNS(), rand, FunctionRand);
  registerParserExemplar(ScopedName::getGlobalNS(), sqrt, FunctionSqrt);
  registerParserExemplar(ScopedName::getGlobalNS(), pow, FunctionPow);
  registerParserExemplar(ScopedName::getGlobalNS(), exp, FunctionExp);
  registerParserExemplar(ScopedName::getGlobalNS(), log, FunctionLog);
  registerParserExemplar(ScopedName::getGlobalNS(), ln, FunctionLn);
}

//_______________________________________________________________ Namespace 3D
void initBSDLParser3DNS()
{
  registerParserNamespace("3D");
  
  // Base exemplars
  registerParserExemplar("3D", name, MakeableAttrName);
  registerParserExemplar("3D", precision, Primitive3DAttrPrecision); // !!!!
  
  // Object exemplars
  registerParserExemplar("3D", list, List3D);
  registerParserExemplar("3D", grid, Grid3D);
  registerParserExemplar("3D", levelOfDetail, LevelOfDetail3D);
  registerParserExemplar("3D", triangle, Triangle3D);
  registerParserExemplar("3D", triangleList, TriangleList3D);
  registerParserExemplar("3D", box, Box3D);
  registerParserExemplar("3D", nullobject, NullObject3D);
  registerParserExemplar("3D", multiobject, MultiObject3D);
  registerParserExemplar("3D", polygon, Polygon3D);
  registerParserAttribute("3D", hole, polygon, Polygon3DAttrHole);
 
  registerParserExemplar("3D", polyextrude, PolygonExtrude);
  registerParserAttribute("3D", hole, polyextrude, PolygonExtrudeAttrHole);
 
  registerParserExemplar("3D", text, Text3D);
  registerParserAttribute("3D", font, text, Text3DAttrFont);
  registerParserExemplar("3D", sphere, Sphere3D);
  registerParserExemplar("3D", disc, Disc3D);
  registerParserExemplar("3D", torus, Torus3D);
  
  registerParserExemplar("3D", cylinder, Cylinder3D);
  registerParserAttribute("3D", open, cylinder, Cylinder3DAttrOpen);
  registerParserAttribute("3D", close, cylinder, Cylinder3DAttrClose);
  
  registerParserExemplar("3D", cone, Cone3D);
  registerParserAttribute("3D", open, cone, Cone3DAttrOpen);
  registerParserAttribute("3D", close, cone, Cone3DAttrClose);
  
  registerParserExemplar("3D", beziercurve, BezierCurve3D);
  registerParserExemplar("3D", interpolationcurve, InterpolationCurve3D);
  registerParserExemplar("3D", bezierpatch, BezierPatch3D);

    
  registerParserExemplar("3D", nurbs, Nurbs3D);
  registerParserAttribute("3D", uknots, nurbs, Nurbs3DAttrUKnots);
  registerParserAttribute("3D", vknots, nurbs, Nurbs3DAttrVKnots);
  registerParserAttribute("3D", vectors, nurbs, Nurbs3DAttrVectors);
  registerParserAttribute("3D", weights, nurbs, Nurbs3DAttrWeights);
  registerParserAttribute("3D", evaluation, nurbs, Nurbs3DAttrEvaluation);
  registerParserAttribute("3D", diameter, nurbs, Nurbs3DAttrDiameter);
  registerParserExemplar("3D", nurbscircle, NurbsCircle3D);
  registerParserAttribute("3D", evaluation, nurbscircle, Nurbs3DAttrEvaluation);
  registerParserAttribute("3D", diameter, nurbscircle, Nurbs3DAttrDiameter);
  registerParserExemplar("3D", nurbsinterpolation, NurbsInterpolation3D);
  registerParserAttribute("3D", datapoints, nurbsinterpolation, Nurbs3DAttrDataPoints);
  registerParserAttribute("3D", evaluation, nurbsinterpolation, Nurbs3DAttrEvaluation);
  registerParserAttribute("3D", diameter, nurbsinterpolation, Nurbs3DAttrDiameter);
  registerParserExemplar("3D", nurbsline, NurbsLine3D);
  registerParserAttribute("3D", evaluation, nurbsline, Nurbs3DAttrEvaluation);
  registerParserAttribute("3D", diameter, nurbsline, Nurbs3DAttrDiameter);
  registerParserExemplar("3D", nurbspolyline, NurbsPolyLine3D);
  registerParserAttribute("3D", evaluation, nurbspolyline, Nurbs3DAttrEvaluation);
  registerParserAttribute("3D", diameter, nurbspolyline, Nurbs3DAttrDiameter);
  registerParserExemplar("3D", nurbsrevolution, NurbsRevolution3D);
  registerParserAttribute("3D", section, nurbsrevolution, Nurbs3DAttrSection);
  registerParserExemplar("3D", nurbssquare, NurbsSquare3D);
  registerParserAttribute("3D", evaluation, nurbssquare, Nurbs3DAttrEvaluation);
  registerParserAttribute("3D", diameter, nurbssquare, Nurbs3DAttrDiameter);
  registerParserExemplar("3D", nurbssphere, NurbsSphere3D);
  registerParserExemplar("3D", nurbssweeping, NurbsSweeping3D);
  registerParserAttribute("3D", section, nurbssweeping, Nurbs3DAttrSection);
  registerParserAttribute("3D", path, nurbssweeping, Nurbs3DAttrPath);
  registerParserExemplar("3D", nurbsswinging, NurbsSwinging3D);
  registerParserAttribute("3D", section, nurbsswinging, Nurbs3DAttrSection);
  registerParserAttribute("3D", path, nurbsswinging, Nurbs3DAttrPath);
  registerParserExemplar("3D", nurbstorus, NurbsTorus3D);


  // Camera exemplars
  registerParserExemplar("3D", camera, Camera3D);
  registerParserAttribute("3D", on, camera, Camera3DAttrOn);
  registerParserAttribute("3D", off, camera, Camera3DAttrOff);
  registerParserAttribute("3D", background, camera, Camera3DAttrBackground);

  registerParserExemplar("3D", orthographic, OrthographicViewing3D);
  registerParserAttribute("3D", eye, orthographic, Viewing3DAttrEye);
  registerParserAttribute("3D", lookat, orthographic, Viewing3DAttrLookat);
  registerParserAttribute("3D", up, orthographic, Viewing3DAttrUp);
  registerParserAttribute("3D", fov, orthographic, Viewing3DAttrFov);
  registerParserAttribute("3D", eyesep, orthographic, Viewing3DAttrEyeSeparation);
  registerParserAttribute("3D", resolution, orthographic, Viewing3DAttrResolution);
  
  registerParserExemplar("3D", perspective, PerspectiveViewing3D);
  registerParserAttribute("3D", eye, perspective, Viewing3DAttrEye);
  registerParserAttribute("3D", lookat, perspective, Viewing3DAttrLookat);
  registerParserAttribute("3D", up, perspective, Viewing3DAttrUp);
  registerParserAttribute("3D", fov, perspective, Viewing3DAttrFov);
  registerParserAttribute("3D", eyesep, perspective, Viewing3DAttrEyeSeparation);
  registerParserAttribute("3D", resolution, perspective, Viewing3DAttrResolution);

  // Light exemplars
  registerParserExemplar("3D", light, GeneralLight);
  registerParserAttribute("3D", on, light, LightSourceAttrOn);
  registerParserAttribute("3D", off, light, LightSourceAttrOff);
  
  registerParserExemplar("3D", pointLight, PointLight);
  registerParserAttribute("3D", on, pointLight, LightSourceAttrOn);
  registerParserAttribute("3D", off, pointLight, LightSourceAttrOff);
  registerParserAttribute("3D", position, pointLight, PointLightAttrPosition);
  registerParserAttribute("3D", radius, pointLight, PointLightAttrRadius);
  
  registerParserExemplar("3D", ambientLight, AmbientLight);
  registerParserAttribute("3D", on, ambientLight, LightSourceAttrOn);
  registerParserAttribute("3D", off, ambientLight, LightSourceAttrOff);

  // Animation exemplars
  registerParserExemplar("3D", action, ActionInfo);
  registerParserAttribute("3D", scalefactor, action, ActionInfoAttrScaleFactor);
  registerParserAttribute("3D", cycling, action, ActionInfoAttrCycling);
  registerParserAttribute("3D", morphing, action, ActionInfoAttrMorphing);
  registerParserAttribute("3D", center, action, ActionInfoAttrCenter);
  registerParserAttribute("3D", direction, action, ActionInfoAttrDirection);
  registerParserAttribute("3D", axis, action, ActionInfoAttrAxis);
  registerParserAttribute("3D", alpha, action, ActionInfoAttrAlpha);
  registerParserAttribute("3D", shearfactor, action, ActionInfoAttrShearFactor);
  registerParserAttribute("3D", tumblepath, action, TumblePath3D);
  registerParserAttribute("3D", tumblecenter, action, TumbleCenter3D);
  registerParserAttribute("3D", tumbledirection, action, TumbleDirection3D);
 
  registerParserExemplar("3D", cycle, Cycle3D);
  registerParserAttribute("3D", on, cycle, Animation3DAttrOn);
  registerParserAttribute("3D", off, cycle, Animation3DAttrOff);
 
  registerParserExemplar("3D", grow, Grow3D);
  registerParserAttribute("3D", on, grow, Animation3DAttrOn);
  registerParserAttribute("3D", off, grow, Animation3DAttrOff);

  registerParserExemplar("3D", move, Move3D);
  registerParserAttribute("3D", on, move, Animation3DAttrOn);
  registerParserAttribute("3D", off, move, Animation3DAttrOff);

  registerParserExemplar("3D", morph, Morph3D);
  registerParserAttribute("3D", on, morph, Animation3DAttrOn);
  registerParserAttribute("3D", off, morph, Animation3DAttrOff);
 
  registerParserExemplar("3D", tumble, Tumble3D);
  registerParserAttribute("3D", on, tumble, Animation3DAttrOn);
  registerParserAttribute("3D", off, tumble, Animation3DAttrOff);
 
  registerParserExemplar("3D", turn, Turn3D);
  registerParserAttribute("3D", on, turn, Animation3DAttrOn);
  registerParserAttribute("3D", off, turn, Animation3DAttrOff);
 
  registerParserExemplar("3D", shear, Shear3D);
  registerParserAttribute("3D", on, shear, Animation3DAttrOn);
  registerParserAttribute("3D", off, shear, Animation3DAttrOff);
 
  // Building exemplars
  registerParserExemplar("3D", building, Building);
  registerParserAttribute("3D", hole, building, BuildingAttrHole);
  registerParserAttribute("3D", off, building, BuildingAttrOff);

  registerParserExemplar("3D", bottomborder, BottomBorder);
  registerParserAttribute("3D", height, bottomborder, BottomAttrHeight);
  registerParserAttribute("3D", open, bottomborder, BottomBorderAttrOpen);
  registerParserAttribute("3D", close, bottomborder, BottomBorderAttrClose);

  registerParserExemplar("3D", bottomuser, BottomUser);
  registerParserAttribute("3D", height, bottomuser,BottomAttrHeight);

  registerParserExemplar("3D", bottomflat, BottomFlat);
  registerParserAttribute("3D", height, bottomflat,BottomAttrHeight);
 
  registerParserExemplar("3D", roofborder, RoofBorder);
  registerParserAttribute("3D", height, roofborder, RoofAttrHeight);

  registerParserExemplar("3D", roofflat, RoofFlat);
  registerParserAttribute("3D", height, roofflat, RoofAttrHeight);

  registerParserExemplar("3D", rooflayer, RoofLayer);
  registerParserAttribute("3D", height, rooflayer, RoofAttrHeight);
  registerParserAttribute("3D", ledgeoff, rooflayer, RoofAttrLedgeOff);
 
  registerParserExemplar("3D", roofplane, RoofPlane);
  registerParserAttribute("3D", height, roofplane, RoofAttrHeight);
  registerParserAttribute("3D", ledgeoff, roofplane, RoofAttrLedgeOff);

  registerParserExemplar("3D", roofpoint, RoofPoint);
  registerParserAttribute("3D", height, roofpoint, RoofAttrHeight);
  registerParserAttribute("3D", ledgeoff, roofpoint, RoofAttrLedgeOff);

  registerParserExemplar("3D", roofuser, RoofUser);
  registerParserAttribute("3D", height, roofuser, RoofAttrHeight);

  registerParserExemplar("3D", snatch, SnatchRoof);
 
  registerParserExemplar("3D", frontrect, FrontRect);
  registerParserAttribute("3D", wallon, frontrect, FrontAttrWallOn);
  registerParserAttribute("3D", walloff, frontrect, FrontAttrWallOff);
  registerParserAttribute("3D", off, frontrect, BuildingObjectAttrOff);

  registerParserExemplar("3D", fronttri, FrontTriangle);
  registerParserAttribute("3D", wallon, fronttri, FrontAttrWallOn);
  registerParserAttribute("3D", walloff, fronttri, FrontAttrWallOff);
  registerParserAttribute("3D", off, fronttri, BuildingObjectAttrOff);
 
  registerParserExemplar("3D", front, FrontSimple);
  registerParserAttribute("3D", off, front, BuildingObjectAttrOff);

  registerParserExemplar("3D", depth, FaceAttrDepth);
 
  registerParserExemplar("3D", facewall, FaceWall);

  registerParserExemplar("3D", facetunnel, FaceTunnel);
  registerParserAttribute("3D", numberofpoints, facetunnel, FaceTunnelAttrNumberOfPoints);
  registerParserAttribute("3D", wallon, facetunnel, FaceTunnelAttrWallOn);
  registerParserAttribute("3D", walloff, facetunnel, FaceTunnelAttrWallOff);
  registerParserAttribute("3D", bezierparm1, facetunnel, FaceTunnelAttrBezierParameter1);
  registerParserAttribute("3D", bezierparm2, facetunnel, FaceTunnelAttrBezierParameter2);
  registerParserAttribute("3D", columnwidth, facetunnel, FaceTunnelAttrColumnWidth);
 
  registerParserExemplar("3D", facearbour, FaceArbour);
  registerParserAttribute("3D", numberofpoints, facearbour, FaceArbourAttrNumberOfPoints);
  registerParserAttribute("3D", wallon, facearbour, FaceArbourAttrWallOn);
  registerParserAttribute("3D", walloff, facearbour, FaceArbourAttrWallOff);
  registerParserAttribute("3D", bezierparm1, facearbour, FaceArbourAttrBezierParameter1);
  registerParserAttribute("3D", bezierparm2, facearbour, FaceArbourAttrBezierParameter2);
  registerParserAttribute("3D", columndepth, facearbour, FaceArbourAttrColumnDepth);
  registerParserAttribute("3D", columnwidth, facearbour, FaceArbourAttrColumnWidth);
  registerParserAttribute("3D", arbourdepth, facearbour, FaceArbourAttrArbourDepth);
  
  registerParserExemplar("3D", faceitem, FaceItem);
  registerParserAttribute("3D", displacement, faceitem, FaceItemAttrDisplacement);
  registerParserAttribute("3D", hole, faceitem, FaceItemAttrHole);
  registerParserAttribute("3D", wallon, faceitem, FaceItemAttrWallOn);
  registerParserAttribute("3D", walloff, faceitem, FaceItemAttrWallOn);
  registerParserAttribute("3D", leftcolumn,   faceitem, FaceItemAttrItemLeftCol);
  registerParserAttribute("3D", rightcolumn,  faceitem, FaceItemAttrItemRightCol);
  registerParserAttribute("3D", bothcolumn,   faceitem, FaceItemAttrItemBothCol);
  registerParserAttribute("3D", insidecolumn, faceitem, FaceItemAttrItemInsideCol);
  registerParserAttribute("3D", bottomrow,    faceitem, FaceItemAttrItemBottomRow);
  registerParserAttribute("3D", toprow,       faceitem, FaceItemAttrItemTopRow);
  registerParserAttribute("3D", bothrow,      faceitem, FaceItemAttrItemBothRow);
  registerParserAttribute("3D", insiderow,    faceitem, FaceItemAttrItemInsideRow);
 
  // Transformation exemplars
  registerParserExemplar("3D", transform, Transform3D);
  registerParserExemplar("3D", scale,     Transform3DAttrScale);
  registerParserExemplar("3D", translate, Transform3DAttrTranslate);
  registerParserExemplar("3D", rotate,    Transform3DAttrRotate);
  registerParserExemplar("3D", rotateX,   Transform3DAttrRotateX);
  registerParserExemplar("3D", rotateY,   Transform3DAttrRotateY);
  registerParserExemplar("3D", rotateZ,   Transform3DAttrRotateZ);
  registerParserExemplar("3D", matrix,    Transform3DAttrMatrix);

  // Texture exemplars
  registerParserExemplar("3D", texture, Texture3DList);

  registerParserExemplar("3D", constant, ConstantTexture3D);

  registerParserExemplar("3D", matte, Matte);
  registerParserAttribute("3D", ambient, matte, MatteAttrAmbient);
  registerParserAttribute("3D", diffuse, matte, MatteAttrDiffuse);

  registerParserExemplar("3D", phong, Phong);
  registerParserAttribute("3D", ambient, phong, PhongAttrAmbient);
  registerParserAttribute("3D", diffuse, phong, PhongAttrDiffuse);
  registerParserAttribute("3D", specular, phong, PhongAttrSpecular);
  registerParserAttribute("3D", specpow, phong, PhongAttrSpecPow);

  registerParserExemplar("3D", whitted, Whitted);
  registerParserAttribute("3D", ambient, whitted, WhittedAttrAmbient);
  registerParserAttribute("3D", diffuse, whitted, WhittedAttrDiffuse);
  registerParserAttribute("3D", transparency, whitted, WhittedAttrTransparency);
  registerParserAttribute("3D", reflectivity, whitted, WhittedAttrReflectivity);
  registerParserAttribute("3D", refractionIndex, whitted, WhittedAttrRefractionIndex);

  registerParserExemplar("3D", checker, Checker);
  registerParserAttribute("3D", even, checker, CheckerAttrEven);
  registerParserAttribute("3D", odd, checker, CheckerAttrOdd);

  registerParserExemplar("3D", shader, Shader);
  
  registerParserExemplar("3D", polygonmapper, PolygonMapper);
  registerParserAttribute("3D", ambient, polygonmapper, PolygonMapperAttrAmbient);
  registerParserAttribute("3D", specular, polygonmapper, PolygonMapperAttrSpecular);
  registerParserAttribute("3D", specpow, polygonmapper, PolygonMapperAttrSpecPow);
  registerParserAttribute("3D", reflectivity, polygonmapper, PolygonMapperAttrReflectivity);
  
  // Proxy Exemplars
  registerParserExemplar("3D", file, File3D);
  registerParserExemplar("3D", url, URL3D);
  
  // Interactive exemplars
  registerParserExemplar("3D", switch, BistableObject3D);
  registerParserAttribute("3D", on, switch, BistableObject3DAttrOn);
  registerParserAttribute("3D", off, switch, BistableObject3DAttrOff);
}

//_______________________________________________________________ Namespace 2D
void initBSDLParser2DNS()
{
  registerParserNamespace("2D");
  
  // Base exemplars
  registerParserExemplar("2D", name, MakeableAttrName);
  registerParserExemplar("2D", precision, Primitive2DAttrPrecision); // !!!!

  // Object exemplars
  registerParserExemplar("2D", list, List2D);
  registerParserExemplar("2D", circle, Circle2D);
  registerParserExemplar("2D", line, Line2D);
  registerParserExemplar("2D", point, Point2D);
  registerParserExemplar("2D", text, Text2D);
  registerParserAttribute("2D", font, text, Text2DAttrFont);
  registerParserExemplar("2D", pixmap, Pixmap2D);
  registerParserExemplar("2D", polygon, Polygon2D);
 
  // Camera exemplars
  registerParserExemplar("2D", camera, Camera2D);
  registerParserAttribute("2D", resolution, camera, Camera2DAttrResolution);
  registerParserAttribute("2D", window, camera, Camera2DAttrWindow);
  registerParserAttribute("2D", on, camera, Camera2DAttrOn);
  registerParserAttribute("2D", off, camera, Camera2DAttrOff);
  registerParserAttribute("2D", background, camera, Camera2DAttrBackground);

  // Transformation exemplars
  registerParserExemplar("2D", transform,    Transform2D);
  registerParserExemplar("2D", scale,        Transform2DAttrScale);
  registerParserExemplar("2D", translate,    Transform2DAttrTranslate);
  registerParserExemplar("2D", rotate,       Transform2DAttrRotate);
  registerParserExemplar("2D", rotateOrigin, Transform2DAttrRotateOrigin);
  registerParserExemplar("2D", matrix,       Transform2DAttrMatrix);

  // Texture exemplars
  registerParserExemplar("2D", texture, Texture2DList);

  registerParserExemplar("2D", color, ConstantTexture2D);
  registerParserExemplar("2D", interpolate, InterpolatorTexture2D);
  registerParserExemplar("2D", pattern, PatternTexture2D);
  registerParserAttribute("2D", solid, pattern, PatternTexture2DAttrSolid);
  registerParserAttribute("2D", gap, pattern, PatternTexture2DAttrGap);
  registerParserExemplar("2D", image, PixmapTexture2D);

  // Proxy Exemplars
  registerParserExemplar("2D", file, File2D);
  registerParserExemplar("2D", url, URL2D);

  // Interactive exemplars
  registerParserExemplar("2D", switch, BistableObject2D);
  registerParserAttribute("2D", on, switch, BistableObject2DAttrOn);
  registerParserAttribute("2D", off, switch, BistableObject2DAttrOff);
}
