/*
 * $RCSfile: VRMLYacc.y,v $ 
 *
 * Parser definition file. Class VRMLYacc is generated using 
 * bison++.
 *
 * Copyright (C) 1996, Beat Liechti <liechti@isbe.ch>
 *                     Ingenieurschule Bern, Switzerland
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
 *  $Id: VRMLYacc.y,v 1.4 1996/08/01 12:01:38 streit Exp $
 * -----------------------------------------------------------------------------
 */

/* 
 * This VRML grammar was taken from the SICS VRML parser implementaton
 * of Emmanuel Frécon and Olof Hagsand. A few corrections and 
 * adaptions were made for the port to bison++.
 */


%{
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define YYMAXDEPTH 100000
%}

%name VRMLYacc

%header{

#include "booga/base/Report.h"

#include "booga/object/World3D.h"
#include "booga/object/PerspectiveViewing3D.h"
#include "booga/object/Camera3D.h"

#include "VRML.h"
#include "VRMLObject.h"
#include "VRMLState.h"

%}

//
// Possible values for an LHS of a production or a tokens.
//
%union 
{
  bool            boolval;
  long            longval;
  unsigned long   ulongval;
  double          doubleval;
  char*           stringval;
  Color*          colorval;
  VRML_binding_t  enumval;
  TransMatrix3D*  transval;
  Vector3D*       vectorval;
  List<Color>*    colorlist;
  List<long>*     longlist;
  List<double>*   doublelist;
  List<Vector3D>* vectorlist;
}

//
// enable all error handling code available
//
%define DEBUG 1
%define DEBUG_FLAG myParserDebugFlag
%define ERROR_VERBOSE

%define ERROR_BODY =0
%define ERROR fatalError
%define NERRS myErrorCount

%define LEX_BODY =0
%define LEX  scan
%define LVAL myTokenValue

%define PARSE parse
%define PARSE_PARAM
%define CONSTRUCTOR_PARAM 
%define CONSTRUCTOR_INIT : myParserDebugFlag(0), myWorld3D(NULL), mySymTable(113)

%define CONSTRUCTOR_CODE 

//
// **** WATCH OUT BUDDY! *****************************
// Whenever you change something in the MEMBER section
// reflex VRMLLex.l and recompile VRMLParser.C
// (you'll be sorry if you don't).
// ***************************************************
//
%define MEMBERS \
public:                                                          \
  void setWorldObject(World3D* world3D) { myWorld3D = world3D; } \
  World3D* getWorldObject() const { return myWorld3D; }          \
private:                                                         \
  /* implementation of these methods is in VRMLYaccImpl.C */     \
  void begDef(const RCString& key);                              \
  void endDef(const RCString& key);                              \
  void objDef(VRMLObject& vrmlObject);                           \
  void useDef(const RCString& key);                              \
  World3D* myWorld3D;                                            \
  bool myHasCamera, myHasLight;                                  \
  VRMLMatrixTransform myMatrixTransform;                         \
  VRMLRotation myRotation;                                       \
  VRMLTransform myTransform;                                     \
  VRMLTranslation myTranslation;                                 \
  VRMLScale myScale;                                             \
  VRMLOrthographicCamera myOrthographicCamera;                   \
  VRMLPerspectiveCamera myPerspectiveCamera;                     \
  VRMLDirectionalLight myDirectionalLight;                       \
  VRMLPointLight myPointLight;                                   \
  VRMLSpotLight mySpotLight;                                     \
  VRMLCone myCone;                                               \
  VRMLCube myCube;                                               \
  VRMLCylinder myCylinder;                                       \
  VRMLIndexedFaceSet myIndexedFaceSet;                           \
  VRMLSphere mySphere;                                           \
  VRMLCoordinate3 myCoordinate3;                                 \
  VRMLMaterial myMaterial;                                       \
  VRMLMaterialBinding myMaterialBinding;                         \
  VRMLNormal myNormal;                                           \
  VRMLNormalBinding myNormalBinding;                             \
  VRMLSeparatorStart mySeparatorStart;                           \
  VRMLSeparatorStop mySeparatorStop;                             \
  VRMLLODStart myLODStart;                                       \
  VRMLLODStop myLODStop;                                         \
  VRMLSwitchStart mySwitchStart;                                 \
  VRMLSwitchStop mySwitchStop;                                   \
  VRMLTransformSeparatorStart myTransSeparatorStart;             \
  VRMLTransformSeparatorStop myTransSeparatorStop;               \
  Stack<VRMLState*> myStateStack;                                \
  List<RCString> myDefList;                                      \
  SymTable<RCString,VRMLList*> mySymTable;                       \

%start vrml

%type <ulongval> SFBitMask bitmasklist
%type <boolval> SFBool
%type <colorval> SFColor
%type <enumval> SFEnum
%type <doubleval> SFFloat
%type <longval> SFLong
%type <transval> SFMatrix SFRotation
%type <stringval> SFString  
%type <vectorval> SFVec3f
%type <colorlist> MFColor colorlist
%type <longlist> MFLong longlist
%type <doublelist> MFFloat floatlist
%type <vectorlist> MFVec3f vec3flist

%token <boolval> BOOL
%token <longval> NUMBER 
%token <doubleval> FLOAT
%token <stringval> VRMLSTRING VRMLWORD

%token ASCIITEXT CONE COORDINATE3 CUBE CYLINDER DIRECTIONALLIGHT FONTSTYLE
%token GROUP INDEXEDFACESET INDEXEDLINESET INFO LOD MATERIAL MATERIALBINDING
%token LEVELOFDETAIL MATRIXTRANSFORM
%token NORMAL NORMALBINDING ORTHOGRAPHICCAMERA PERSPECTIVECAMERA
%token POINTLIGHT POINTSET ROTATION SCALE SEPARATOR SHAPEHINTS SPHERE
%token SPOTLIGHT SWITCH TEXTURE2 TEXTURE2TRANSFORM TEXTURECOORDINATE2
%token TRANSFORM TRANSFORMSEPARATOR TRANSLATION WWWANCHOR WWWINLINE

%token PARTS BOTTOMRADIUS HEIGHT POINT WIDTH DEPTH STRING SPACING
%token JUSTIFICATION RADIUS ON INTENSITY COLOR DIRECTION SIZE FAMILY STYLE
%token COORDINDEX MATERIALINDEX NORMALINDEX TEXTURECOORDINDEX RANGE
%token SCREENAREA TRANSLATION_F
%token CENTER AMBIENTCOLOR DIFFUSECOLOR SPECULARCOLOR EMISSIVECOLOR SHININESS
%token TRANSPARENCY VALUE MATRIX VECTOR POSITION ORIENTATION FOCALDISTANCE
%token HEIGHTANGLE LOCATION STARTINDEX NUMPOINTS ROTATION_F SCALEFACTOR
%token RENDERCULLING VERTEXORDERING SHAPETYPE FACETYPE CREASEANGLE DROPOFFRATE
%token CUTOFFANGLE WHICHCHILD FILENAME IMAGE WRAPS WRAPT SCALEORIENTATION
%token NAME DESCRIPTION MAP BBOXSIZE BBOXCENTER

%token DEF USE

%token FIELDS UNKNOWNNODE

%%

vrml		        : { //
                            // make the first status and push onto state stack 
			    //
                            VRMLState *state = new VRMLState(); myStateStack.push(state);
			    myHasLight = false; 
			    myHasCamera = false;
                          } 
                          Nodes 
                          { //
			    // get status from stack and adopt objects into world 
			    //
                            VRMLState *state = myStateStack.top();
                            myWorld3D->getObjects()->adoptObject(state->orphanObjects());
			    myWorld3D->getObjects()->computeBounds();

			    //
			    // check whether camera and light is in world 
			    //
			    if (!myHasCamera)
                            { //
			      // compute bounding box for world and adapt camera 
			      //
			      PerspectiveViewing3D *perspectiveViewing3D = new PerspectiveViewing3D;
			      perspectiveViewing3D->setView(myWorld3D->getObjects()->getBounds().getMin(), 
							    myWorld3D->getObjects()->getBounds().getMax());
			      Camera3D* camera3D = new Camera3D();
			      camera3D->adoptViewing(perspectiveViewing3D);
			      myWorld3D->getObjects()->adoptObject(camera3D);
			    }
			    if (!myHasLight)
                            { //
			      // some nice lights 
			      //
			      myPointLight.reset();
			      myPointLight.setOn(true);
			      myPointLight.setColor(Color(1,1,1));
			      myPointLight.setIntensity(1);
			      myPointLight.setLocation(Vector3D( 100000, 100000, 100000)); 
			      myPointLight.apply(myStateStack);
			      myPointLight.setLocation(Vector3D(-100000, 100000,-100000)); 
			      myPointLight.apply(myStateStack);
			      myPointLight.setLocation(Vector3D(-100000,-100000, 100000)); 
			      myPointLight.apply(myStateStack);
			      myPointLight.setLocation(Vector3D( 100000,-100000,-100000)); 
			      myPointLight.apply(myStateStack);
			      myWorld3D->getObjects()->adoptObject(state->orphanObjects());
			    }			    
			    //
			    // pop last state and delete it
			    // 
			    myStateStack.pop();			                                
			    delete state;
                            YYACCEPT;
                          }
		        | error {YYABORT;}
                        ;

Nodes		        : Node Nodes
		        |
		        ;

Node		        : NodeBody
                        | DEF VRMLWORD 
                          { //
			    // start definition 
			    //
			    begDef(RCString($2)); 
			  } 
                          NodeBody
                          { //
			    // end definition 
			    //
			    endDef(RCString($2)); 
			  }
			| USE VRMLWORD 
                          { //
			    // use definition 
			    //
			    
			    useDef(RCString($2)); 
			  }
			;

NodeBody	        : AsciiText
			| Cone
			| Coordinate3
			| Cube
			| Cylinder
			| Dlight
			| FontStyle
			| Group
			| IdxFaceSet
			| IdxLineSet
			| Info
			| Lod
			| LevelOfDetail
			| Material
			| MaterialBinding
			| MatrixTransform
			| Normal
			| NormalBinding
			| OrthographicCamera
			| PerspectiveCamera
			| PointLight
			| PointSet
			| Rotation
			| Scale
			| Separator
			| ShapeHints
			| Sphere
			| SpotLight
			| Switch
			| Texture2
			| Tex2Transform
			| TexCoordinate2
			| Transform
			| TransSeparator
			| Translation
			| WWWAnchor
			| WWWInline
			| UnknownNode
			;

// Field specification 
FieldSpecs	        : FIELDS
			| // empty 
			;

// Unknown node 
UnknownNode	        : UNKNOWNNODE
			;

// Ascii Text 
asciitextfields	        : asciitextfield asciitextfields
			| // empty
			;

asciitextfield	        : STRING MFString
			| SPACING SFFloat
			| JUSTIFICATION	SFEnum
			| WIDTH	MFFloat
			;
		
AsciiText	        : ASCIITEXT '{' FieldSpecs asciitextfields '}'
			  {
			    Report::warning("AsciiText node ignored");
			  }
			;

// Cones
conefields	        : conefield conefields
			|
			;

conefield	        : PARTS	SFBitMask 
                          {			    
			    myCone.setParts($2); 
			  }
			| BOTTOMRADIUS SFFloat
                          {
			    myCone.setBottomRadius($2); 
			  }
			| HEIGHT SFFloat 
                          { 
			    myCone.setHeight($2); 
			  }
			;

Cone		        : CONE 
                          {
			    myCone.reset(); 
			  }
                          '{' FieldSpecs conefields '}' 
                          { 
			    myCone.apply(myStateStack); 
			    objDef(myCone);
			  }
			;

// Coordinate 3
coordinatefield         : POINT MFVec3f 
                          { 
			    myCoordinate3.setPoint(*$2); 
			    delete $2; 
			  }
			| // empty
			;

Coordinate3	        : COORDINATE3 
                          {
			    myCoordinate3.reset(); 
			  }
                          '{' FieldSpecs coordinatefield '}' 
                          { 
			    myCoordinate3.apply(myStateStack); 
    			    objDef(myCoordinate3);
			  }
		        ;

// Cubes 
cubefields	        : cubefield cubefields
			| // empty 
			;

cubefield	        : WIDTH SFFloat 
                          { 
			    myCube.setWidth($2); 
			  }
			| HEIGHT SFFloat 
                          {
			    myCube.setHeight($2); 
			  }
			| DEPTH	SFFloat 
                          { 
			    myCube.setDepth($2); 
			  }
			;

Cube		        : CUBE 
                          { 
			    myCube.reset(); 
			  }
                          '{' FieldSpecs cubefields '}' 
                          {
			    myCube.apply(myStateStack); 
			    objDef(myCube);
			  }
		        ;


// Cylinder
cylinderfields	        : cylinderfield cylinderfields
			|
			;

cylinderfield	        : PARTS SFBitMask 
                          { 
			    myCylinder.setParts($2); 
			  }
			| RADIUS SFFloat 
                          {
			    myCylinder.setRadius($2); 
			  }
			| HEIGHT SFFloat
                          {
			    myCylinder.setHeight($2); 
			  }
			;

Cylinder	        : CYLINDER 
                          {
			    myCylinder.reset(); 
			  }
                          '{' FieldSpecs cylinderfields '}' 
                          {
			    myCylinder.apply(myStateStack);
			    objDef(myCylinder);
			  }
			;

// Directional Light 
dlightfields	        : dlightfield dlightfields
			| // empty
			;

dlightfield	        : ON SFBool 
                          {
			    myDirectionalLight.setOn($2); 
			  }
			| INTENSITY SFFloat 
                          { 
			    myDirectionalLight.setIntensity($2); 
			  }
			| COLOR SFColor 
                          {
			    myDirectionalLight.setColor(*$2); 
			    delete $2; 
			  }
			| DIRECTION SFVec3f 
                          {
			    myDirectionalLight.setDirection(*$2); 
			    delete $2; 
			  }
			;

Dlight		        : DIRECTIONALLIGHT 
                          {
			    Report::warning("DirectionalLight node simulated with point light at 100000 * -direction");
			    myDirectionalLight.reset(); 
			  }
                          '{' FieldSpecs dlightfields '}'
                          {
			    //
			    // since the default camera position is calculated with
			    // bounding boxes, we collect the directional lights
			    // and apply them after the default camera is inserted
			    // 
			    myHasLight |= myDirectionalLight.getOn();
			    myDirectionalLight.apply(myStateStack);
			    objDef(myDirectionalLight);
			  }
		        ;

// Font Style 
fstylefields	        : fstylefield fstylefields
			| // empty
			;

fstylefield	        : SIZE		SFFloat
			| FAMILY	SFEnum
			| STYLE		SFBitMask
			;

FontStyle	        : FONTSTYLE '{' FieldSpecs fstylefields '}'
			  {
			    Report::warning("FontStyle node ignored");
			  }
		        ;

// Groups
Group		        : GROUP '{' Nodes '}'
		        ;

// Indexed Face Set 
ifacesetfields	        : ifacesetfield ifacesetfields
		        | // empty
		        ;

ifacesetfield	        : COORDINDEX MFLong 
                          {
			    myIndexedFaceSet.setCoordIndex(*$2); 
			    delete $2; 
			  }
			| MATERIALINDEX	MFLong 
			  {
			    myIndexedFaceSet.setMaterialIndex(*$2); 
			    delete $2; 
			  }
			| NORMALINDEX MFLong 
			  {
			    myIndexedFaceSet.setNormalIndex(*$2); 
			    delete $2; 
			  }
			| TEXTURECOORDINDEX MFLong
			  {
			    delete $2; 
			  }
			;

IdxFaceSet	        : INDEXEDFACESET
			  { 
			    myIndexedFaceSet.reset() 
			  }
                          '{' FieldSpecs ifacesetfields '}' 
                          {
			    myIndexedFaceSet.apply(myStateStack); 
			    objDef(myIndexedFaceSet);
			  }
		        ;

// Indexed Line Set 
ilinesetfields	        : ilinesetfield ilinesetfields
		        | // empty
		        ;

ilinesetfield	        : COORDINDEX MFLong 
			  {
			    delete $2; 
			  }
			| MATERIALINDEX	MFLong 
			  {
			    delete $2; 
			  }
			| NORMALINDEX MFLong 
			  {
			    delete $2; 
			  }
			| TEXTURECOORDINDEX MFLong 
			  {
			    delete $2; 
			  }
			;

IdxLineSet	        : INDEXEDLINESET '{' FieldSpecs ilinesetfields '}'
			  {
			    Report::warning("IndexedLineSet node ignored");
			  }
			;

// Info 
infofield	        : STRING SFString 
			  {
			    delete $2; 
			  }
			| // empty
			;

Info		        : INFO '{' FieldSpecs infofield '}'
			  {
			    Report::warning("Info node ignored");
			  }	
		        ;

// Level of Detail 
// LOD comes from the new VRML draft, LEVELOFDETAIL from the old one !! 

lodfields	        : lodfield lodfields
			| // empty
			;

lodfield	        : RANGE	MFFloat
			| CENTER SFVec3f 
			  {
			    delete $2; 
			  }
			;

Lod		        : LOD '{' FieldSpecs lodfields 
                          { 
			    Report::warning("LOD node, only highest level of detail child taken");
			    myLODStart.apply(myStateStack); 
			    objDef(myLODStart);
			  }
                          Nodes '}'
                          {
			    myLODStop.apply(myStateStack); 
			    objDef(myLODStop);
			  }
		        ;

oldlodfield	        : SCREENAREA MFFloat
			|
			;

LevelOfDetail	        : LEVELOFDETAIL '{' FieldSpecs oldlodfield Nodes '}'
			  {
			    Report::warning("LevelOfDetail node ignored");
			  }	
                        ;

// Material 
materialfields	        : materialfield materialfields
			| // empty 
			;

materialfield	        : AMBIENTCOLOR MFColor
                          {
			    myMaterial.setAmbientColor(*$2); 
			    delete $2; 
			  }
			| DIFFUSECOLOR MFColor 
                          {
			    myMaterial.setDiffuseColor(*$2); 
			    delete $2; 
			  }
			| SPECULARCOLOR	MFColor 
                          {
			    myMaterial.setSpecularColor(*$2); 
			    delete $2; 
			  }
			| EMISSIVECOLOR	MFColor 
			  {
			    Report::warning("Material node, field emissiveColor ignored");
			    delete $2; 
			  }
			| SHININESS MFFloat 
			  {
			    Report::warning("Material node, field shininess ignored");
			    delete $2; 
			  }
			| TRANSPARENCY MFFloat 
			  {
			    Report::warning("Material node, field transparency ignored");
			    delete $2; 
			  }
			;

Material	        : MATERIAL 
                          {
			    myMaterial.reset(); 
			  }
                          '{' FieldSpecs materialfields '}'
                          {
			    myMaterial.apply(myStateStack); 
			    objDef(myMaterial);
			  }
			;

// Material Binding 
mbindingfields	        : mbindingfield mbindingfields
			| // empty 
			;

mbindingfield	        : VALUE	SFEnum 
			  {
			    if ($2 == VRML_PER_VERTEX)
			      Report::warning("MaterialBinding node, PER_VERTEX binding not supported");
                            if ($2 == VRML_PER_VERTEX_INDEXED)
			      Report::warning("MaterialBinding node, PER_VERTEX_INDEXED binding not supported");
			    myMaterialBinding.setValue($2); 
			  }
		        ;

MaterialBinding	        : MATERIALBINDING 
			  {
			    myMaterialBinding.reset(); 
			  }
                          '{' FieldSpecs mbindingfields '}' 
                          {
			    myMaterialBinding.apply(myStateStack); 
			    objDef(myMaterialBinding);
			  }
		        ;

// Matrix Transform 
mxtransformfields	: mxtransformfield mxtransformfields
			| // empty
			;

mxtransformfield	: MATRIX SFMatrix  
			  {
			    myMatrixTransform.setMatrix(*$2); 
			    delete $2; 
			  }
			;

MatrixTransform	        : MATRIXTRANSFORM 
			  {
			    myMatrixTransform.reset(); 
			  }
                          '{' FieldSpecs mxtransformfields '}' 
                          {
			    myMatrixTransform.apply(myStateStack);
			    objDef(myMatrixTransform);
			  }
		        ;

// Normal 
normalfields	        : normalfield normalfields
		        | // empty 
		        ;

normalfield	        : VECTOR MFVec3f 
			  { 
			    myNormal.setVector(*$2); 
			    delete $2; 
			  }
		        ;

Normal		        : NORMAL 
			  {
			    Report::warning("Normal node ignored");
			    myNormal.reset(); 
			  }
			  '{' FieldSpecs normalfields '}'
                          {
			    myNormal.apply(myStateStack); 
			    objDef(myNormal);
			  }
		        ;

// Normal Binding 
nbindingfields	        : nbindingfield nbindingfields
			| // empty 
			;

nbindingfield	        : VALUE	SFEnum 
			  {
			    myNormalBinding.setValue($2); 
			  }
			;

NormalBinding	        : NORMALBINDING 
			  {
			    Report::warning("NormalBinding node ignored");
			    myNormalBinding.reset(); 
			  }
                          '{' FieldSpecs nbindingfields '}' 
                          {
			    myNormalBinding.apply(myStateStack); 
			    objDef(myNormalBinding);
			  }
		        ;

// Orthographic camera 
ocamerafields	        : ocamerafield ocamerafields
			| // empty 
			;

ocamerafield	        : POSITION SFVec3f 
			  {
			    myOrthographicCamera.setPosition(*$2); 
			    delete $2; 
			  }
			| ORIENTATION SFRotation 
			  {
			    myOrthographicCamera.setOrientation(*$2); 
			    delete $2; 
			  }
			| FOCALDISTANCE SFFloat
			  {
			    myOrthographicCamera.setFocalDistance($2); 
			  }
			| HEIGHT SFFloat
			  {
			    myOrthographicCamera.setHeight($2); 
			  }
			;

OrthographicCamera	: ORTHOGRAPHICCAMERA 
			  {
			    myOrthographicCamera.reset(); 
			  }
                          '{' FieldSpecs ocamerafields '}' 
                          {
			    myHasCamera = true;
			    myOrthographicCamera.apply(myStateStack); 
			    objDef(myOrthographicCamera);
			  }
			;

// Perspective camera 
pcamerafields	        : pcamerafield pcamerafields
			| // empty 
			;

pcamerafield	        : POSITION SFVec3f 
			  {
			    myPerspectiveCamera.setPosition(*$2); 
			    delete $2; 
			  }
			| ORIENTATION SFRotation 
			  {
			    myPerspectiveCamera.setOrientation(*$2); 
			    delete $2; 
			  }
			| FOCALDISTANCE SFFloat 
			  {
			    myPerspectiveCamera.setFocalDistance($2); 
			  }
			| HEIGHTANGLE SFFloat 
			  {
			    myPerspectiveCamera.setHeightAngle($2); 
			  }
			;

PerspectiveCamera       : PERSPECTIVECAMERA 
			  {
			    myPerspectiveCamera.reset(); 
			  }
                          '{' FieldSpecs pcamerafields '}'
                          {
			    myHasCamera = true;
			    myPerspectiveCamera.apply(myStateStack); 
			    objDef(myPerspectiveCamera);
			  }
			;

// Point Light 
plightfields	        : plightfield plightfields
			| // empty
			;

plightfield	        : ON SFBool 
			  {
			    myPointLight.setOn($2); 
			  }
			| INTENSITY SFFloat 
			  {
			    myPointLight.setIntensity($2); 
			  }
			| COLOR	SFColor 
			  {
			    myPointLight.setColor(*$2); 
			    delete $2; 
			  }
			| LOCATION SFVec3f 
			  {
			    myPointLight.setLocation(*$2); 
			    delete $2; 
			  }
			;	

PointLight	        : POINTLIGHT { myPointLight.reset() }
                          '{' FieldSpecs plightfields '}'
                          {
			    myHasLight |= myPointLight.getOn();
			    myPointLight.apply(myStateStack);
			    objDef(myPointLight);
			  }
		        ;

// Point Set 
psetfields	        : psetfield psetfields
			| // empty
			;

psetfield	        : STARTINDEX SFLong
			| NUMPOINTS SFLong
			;

PointSet	        : POINTSET '{' FieldSpecs psetfields '}'
			  {
			    Report::warning("PointSet node ignored");
			  }
		        ;

// Rotation 
rotationfields	        : rotationfield rotationfields
		        |
		        ;

rotationfield	        : ROTATION_F SFRotation 
			  {
			    myRotation.setRotation(*$2); 
			    delete $2; 
			  }
		        ;

Rotation	        : ROTATION 
			  {
			    myRotation.reset(); 
			  }
                          '{' FieldSpecs rotationfields '}'
                          {
			    myRotation.apply(myStateStack);
			    objDef(myRotation);
			  }
		        ;

// Scale 
scalefields	        : scalefield scalefields
		        | // empty
		        ;

scalefield	        : SCALEFACTOR SFVec3f 
			  {
			    myScale.setScaleFactor(*$2); 
			    delete $2; 
			  }
		        ;

Scale		        : SCALE 
			  {
			    myScale.reset(); 
			  }
                          '{' FieldSpecs scalefields '}' 
                          {
			    myScale.apply(myStateStack); 
			    objDef(myScale);
			  }
		        ;

// Separator 
separatorfields	        : separatorfield separatorfields
		        | // empty
		        ;

separatorfield	        : RENDERCULLING	SFEnum
		        ;

Separator	        : SEPARATOR '{' FieldSpecs separatorfields 
                          {
			    mySeparatorStart.apply(myStateStack);
			    objDef(mySeparatorStart);
			  }
                          Nodes '}' 
                          {
			    mySeparatorStop.apply(myStateStack);
			    objDef(mySeparatorStop);
			  }
		        ;

// Shape Hints 
shapehintsfields	: shapehintsfield shapehintsfields
			| // empty
			;

shapehintsfield	        : VERTEXORDERING SFEnum
			| SHAPETYPE SFEnum
			| FACETYPE SFEnum
			| CREASEANGLE SFFloat
			;

ShapeHints	        : SHAPEHINTS '{' FieldSpecs shapehintsfields '}'
			  {
			    Report::warning("ShapeHints node ignored");
			  }
		        ;

// Sphere 
spherefields	        : spherefield spherefields
			| // empty
			;

spherefield	        : RADIUS SFFloat 
			  {
			    mySphere.setRadius($2); 
			  }
		        ;

Sphere		        : SPHERE { mySphere.reset(); }
                          '{' FieldSpecs spherefields '}' 
                          {
			    mySphere.apply(myStateStack); 
			    objDef(mySphere);
			  }
		        ;

// Spotlight 
spotlightfields	        : spotlightfield spotlightfields
		        | // empty
		        ;

spotlightfield	        : ON SFBool 
			  {
			    mySpotLight.setOn($2); 
			  }
			| INTENSITY SFFloat 
			  {
			    mySpotLight.setIntensity($2); 
			  }
			| COLOR	SFColor 
			  {
			    mySpotLight.setColor(*$2); 
			    delete $2; 
			  }
			| LOCATION SFVec3f 
			  {
			    mySpotLight.setLocation(*$2); 
			    delete $2; 
			  }
			| DIRECTION SFVec3f 
			  {
			    mySpotLight.setDirection(*$2); 
			    delete $2; 
			  }
			| DROPOFFRATE SFFloat 
			  {
			    Report::warning("SpotLight node, field dropOffRate ignored");
			  }
			| CUTOFFANGLE SFFloat
			  {
			    Report::warning("SpotLight node, field cutOffAngle ignored");
			  }			
                        ;

SpotLight	        : SPOTLIGHT 
			  {
			    Report::warning("SpotLight node simulated with point light");
			    mySpotLight.reset(); 
			  }
                          '{' FieldSpecs spotlightfields '}'
                          {
			    myHasLight |= mySpotLight.getOn();
			    mySpotLight.apply(myStateStack);
			    objDef(mySpotLight);
			  }
			;

// Switch 
switchfields	        : switchfield switchfields
			| // empty
			;

switchfield	        : WHICHCHILD SFLong 
			  {
			    mySwitchStart.setWhichChild($2); 
			  }
		        ;

Switch		        : SWITCH { mySwitchStart.reset(); }
                          '{' FieldSpecs switchfields 
                          {
			    mySwitchStart.apply(myStateStack); 
			    objDef(mySwitchStart);
			  }
                          Nodes '}'
                          {
			    mySwitchStop.apply(myStateStack); 
			    objDef(mySwitchStop);
			  }
		        ;

// Texture2 
texture2fields	        : texture2field texture2fields
			| // empty
			;

texture2field	        : FILENAME SFString 
			  {
			    delete $2; 
			  }
			| IMAGE	SFImage
			| WRAPS	SFEnum
			| WRAPT	SFEnum
			;

Texture2	        : TEXTURE2 '{' FieldSpecs texture2fields '}'
			  {
			    Report::warning("Texture2 node ignored");
			  }
		        ;

// Texture transformation 
tex2transfields	        : tex2transfield tex2transfields
		        | // empty
		        ;

tex2transfield	        : TRANSLATION_F	SFVec2f
			| ROTATION_F SFFloat
			| SCALEFACTOR SFVec2f
			| CENTER SFVec2f
			;

Tex2Transform	        : TEXTURE2TRANSFORM '{' FieldSpecs tex2transfields '}'
			  {
			    Report::warning("Texture2Transform node ignored");
			  }
		        ;

/* Texcoord2 */
texcoord2fields	        : texcoord2field texcoord2fields
		        | // empty
		        ;

texcoord2field	        : POINT MFVec2f
		        ;

TexCoordinate2	        : TEXTURECOORDINATE2 '{' FieldSpecs texcoord2fields '}'
			  {
			    Report::warning("TextureCoordinate2 node ignored");
			  }
		        ;

/* Transformation */
transformfields	        : transformfield transformfields
			| // empty
			;

transformfield	        : TRANSLATION_F	SFVec3f 
			  {
			    myTransform.setTranslation(*$2); 
			    delete $2; 
			  }
			| ROTATION_F SFRotation 
			  {
			    myTransform.setRotation(*$2); 
			    delete $2; 
			  }
			| SCALEFACTOR SFVec3f 
			  {
			    myTransform.setScaleFactor(*$2); 
			    delete $2; 
			  }
			| SCALEORIENTATION SFRotation 
			  {
			    myTransform.setScaleOrientation(*$2); 
			    delete $2; 
			  }
			| CENTER SFVec3f
			  {
			    myTransform.setCenter(*$2); 
			    delete $2; 
			  }
			;

Transform	        : TRANSFORM { myTransform.reset(); }
                          '{' FieldSpecs transformfields '}' 
                          {
			    myTransform.apply(myStateStack); 
			    objDef(myTransform);
			  }
		        ;

// Transform Separator 
TransSeparator	        : TRANSFORMSEPARATOR '{' FieldSpecs 
                          {
			    myTransSeparatorStart.apply(myStateStack); 
			    objDef(myTransSeparatorStart);
			  }
                          Nodes '}'
                          {
			    myTransSeparatorStop.apply(myStateStack); 
			    objDef(myTransSeparatorStop);
			  }
		        ;

// Translation 
translationfields	: translationfield translationfields
			| // empty
			;

translationfield	: TRANSLATION_F	SFVec3f 
			  {
			    myTranslation.setTranslation(*$2); 
			    delete $2; 
			  }
			;

Translation	        : TRANSLATION { myTranslation.reset(); }
                          '{' FieldSpecs translationfields '}' 
                          { 
			    myTranslation.apply(myStateStack);
			    objDef(myTranslation);
			  }
		        ;

// WWWAnchor 
WWWanchorfields	        : WWWanchorfield WWWanchorfields
		        | // empty
		        ;

WWWanchorfield	        : NAME SFString
			  {
			    delete $2; 
			  }
			| DESCRIPTION SFString 
			  {
			    delete $2; 
			  }
			| MAP SFEnum
			;

WWWAnchor	        : WWWANCHOR '{' FieldSpecs WWWanchorfields Nodes '}'
			  {
			    Report::warning("WWWAnchor node ignored");
			  }	
		        ;

/* WWWinline */
WWWinlinefields	        : WWWinlinefield WWWinlinefields
		        | // empty
		        ;

WWWinlinefield	        : NAME SFString 
			  {
			    delete $2; 
			  }
			| BBOXSIZE SFVec3f 
			  {
			    delete $2; 
			  }
			| BBOXCENTER SFVec3f 
			  {
			    delete $2; 
			  }
			;

WWWInline	        : WWWINLINE '{' FieldSpecs WWWinlinefields '}'
			  {
			    Report::warning("WWWInline node ignored");
			  }	
		        ;



// ========== Classes of Fields ========== 

// Single Value Fields 
bitmasklist	        : NUMBER  { $$ = $<ulongval>3; }
			| bitmasklist '|' NUMBER { $$ = ($1 | $<ulongval>3);}
			;

SFBitMask	        : NUMBER {$$ = (unsigned long)$1;}
			| '(' bitmasklist ')' {$$ = (unsigned long)$2;}
			;

SFBool		        : BOOL
		        ;

SFColor		        : SFFloat SFFloat SFFloat { $$ = new Color($1,$2,$3); }
		        ;

SFEnum		        : NUMBER {$$ = (VRML_binding_t)$1;}
		        ;

SFFloat		        : FLOAT { $$ = (double)$1; }
		        | NUMBER { $$ = (double)$1; }
		        ;

imglist		        : NUMBER imglist {}
		        | // empty
		        ;

SFImage		        : NUMBER NUMBER NUMBER imglist {}
		        ;

SFLong		        : NUMBER
		        ;

SFMatrix	                 :  SFFloat SFFloat SFFloat SFFloat
			  SFFloat SFFloat SFFloat SFFloat
			  SFFloat SFFloat SFFloat SFFloat
			  SFFloat SFFloat SFFloat SFFloat 
                          { 
                            $$ = new TransMatrix3D(Vector3D($1,$2,$3),
                                                   Vector3D($5,$6,$7),
                                                   Vector3D($9,$10,$11), 
                                                   Vector3D($13,$14,$15)); 
                            if (!equal($4, 0) || !equal($8, 0) || !equal($12, 0) || !equal($16,1))
                              Report::warning("MatrixTransform node, last column set to [ 0 0 0 1 ]");
                          }
			;

SFRotation	        : SFFloat SFFloat SFFloat SFFloat 
                          { $$ = new TransMatrix3D(TransMatrix3D::makeRotate(Vector3D($1,$2,$3),$4)); }
		        ;

SFString	        : VRMLSTRING
		        ;

SFVec2f		        : SFFloat SFFloat {}
		        ;

SFVec3f		        : SFFloat SFFloat SFFloat { $$ = new Vector3D($1,$2,$3); }
		        ;

// Multiple Value Field 
colorlist	        : SFColor { $$ = new List<Color>; $$->append(*$1); delete $1; }
		        | SFColor ',' { $$ = new List<Color>; $$->append(*$1); delete $1; }
		        | SFColor ',' colorlist { $$ = $3; $$->prepend(*$1); delete $1; }
		        ;

MFColor		        : { $$ = new List<Color>; } SFColor { $$->append(*$2); delete $2; }
                          | '[' colorlist ']' { $$ = $2; }
                          | '~' { $$ = new List<Color>; }
			;

longlist	        : SFLong { $$ = new List<long>; $$->append($1); }
			| SFLong ',' { $$ = new List<long>; $$->append($1); }
			| SFLong ',' longlist { $$ = $3; $$->prepend($1); }
			;

MFLong		        : SFLong { $$ = new List<long>; $$->append($1); }
			| '[' longlist ']' { $$ = $2; }
                           | '~' { $$ = new List<long>; }
			; 

floatlist	        : SFFloat { $$ = new List<double>; $$->append($1); }
			| SFFloat ',' { $$ = new List<double>; $$->append($1); }
			| SFFloat ',' floatlist { $$ = $3; $$->prepend($1); }
			;

MFFloat		        : SFFloat { $$ = new List<double>; $$->append($1); }
			| '[' floatlist ']' { $$ = $2; }
                           | '~' { $$ = new List<double>; }
			; 

stringlist	        : SFString { delete $1; }
			| SFString { delete $1; } ',' stringlist
			;

MFString	        : SFString { delete $1; }
			| '[' stringlist ']' {}
			; 

vec2flist	        : SFVec2f
			| SFVec2f ',' 
			| SFVec2f ',' vec2flist
			;

MFVec2f		        : SFVec2f
			| '[' vec2flist ']'
			; 

vec3flist	        : SFVec3f { $$ = new List<Vector3D>; $$->append(*$1); delete $1; }
                           | SFVec3f ',' { $$ = new List<Vector3D>; $$->append(*$1); delete $1; }
			| SFVec3f ',' vec3flist { $$ = $3; $$->prepend(*$1); delete $1; }
			;

MFVec3f		        : SFVec3f { $$ = new List<Vector3D>; $$->append(*$1); delete $1; }
			| '[' vec3flist ']' { $$ = $2; }
                           | '~' { $$ = new List<Vector3D>; }
			; 

%%

