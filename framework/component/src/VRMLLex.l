/*
 * $RCSfile: VRMLLex.l,v $ 
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
 *  $Id: VRMLLex.l,v 1.2 1996/08/01 12:01:31 streit Exp $
 * -----------------------------------------------------------------------------
 */

/* 
 * This VRML lexer was taken from the SICS VRML parser implementaton
 * of Emmanuel Frécon and Olof Hagsand. A few corrections and 
 * adaptions were made for the port to flex++.
 */

%header{
#include "VRMLYacc.h"
%}

%{
#include <string.h>
#include "VRML.h"
%}

%name VRMLLex

%define DEBUG 1
%define DEBUG_FLAG myScannerDebugFlag
%define DEBUG_INIT 0

%define CONSTRUCTOR_PARAM void
%define CONSTRUCTOR_INIT : myCurrentLine(1)
%define CONSTRUCTOR_CODE 

%define IN inputFile

%define MEMBERS                                              \
  public:                                                    \
     const char* getCurrentToken() const { return yytext; }  \
     int getCurrentLine() const { return myCurrentLine; }    \
     const RCString& getCurrentFilename() const              \
     { return myCurrentFilename; }                           \
  private:                                                   \
     int myLineNo;                                           \
     int myCurrentLine;                                      \
     RCString myCurrentFilename;

%define LEX scan
%define LEX_PARAM YY_VRMLYacc_STYPE& yylval

%{
/*
#undef yywrap
int yywrap()
{
  return 1;
} 
*/
%}

%e 1800
%p 14000
%a 22000
%n 2000
%s use_and_def

INSTANCE	[^0-9{}\'\"\\ \t\n\f[:cntrl:]][^{}\'\"\\ \t\n\f[:cntrl:]]*
ID		[A-Za-z_][0-9A-Za-z_]*

%%

DEF				{ BEGIN(use_and_def); return VRMLYacc::DEF; }
<use_and_def>{ID}		         { yylval.stringval = strdup(yytext);
				  BEGIN(INITIAL);
				  return VRMLYacc::VRMLWORD; }
<use_and_def>[ \t]*		;
<use_and_def>\n			myCurrentLine++;
USE				{ BEGIN(use_and_def); return VRMLYacc::USE; }

AsciiText			{ return VRMLYacc::ASCIITEXT; }
Cone				{ return VRMLYacc::CONE; }
Coordinate3			{ return VRMLYacc::COORDINATE3; }
Cube				{ return VRMLYacc::CUBE; }
Cylinder			         { return VRMLYacc::CYLINDER; }
DirectionalLight		         { return VRMLYacc::DIRECTIONALLIGHT; }
FontStyle			{ return VRMLYacc::FONTSTYLE; }
Group				{ return VRMLYacc::GROUP; }
IndexedFaceSet			{ return VRMLYacc::INDEXEDFACESET; }
IndexedLineSet			{ return VRMLYacc::INDEXEDLINESET; }
Info				{ return VRMLYacc::INFO; }
LOD				{ return VRMLYacc::LOD; }
LevelOfDetail			{ return VRMLYacc::LEVELOFDETAIL; }
Material			         { return VRMLYacc::MATERIAL; }
MaterialBinding			{ return VRMLYacc::MATERIALBINDING; }
MatrixTransform			{ return VRMLYacc::MATRIXTRANSFORM; }
Normal				{ return VRMLYacc::NORMAL; }
NormalBinding			{ return VRMLYacc::NORMALBINDING; }
OrthographicCamera		{ return VRMLYacc::ORTHOGRAPHICCAMERA; }
PerspectiveCamera		         { return VRMLYacc::PERSPECTIVECAMERA; }
PointLight			{ return VRMLYacc::POINTLIGHT; }
PointSet			         { return VRMLYacc::POINTSET; }
Rotation			         { return VRMLYacc::ROTATION; }
Scale				{ return VRMLYacc::SCALE; }
Separator			{ return VRMLYacc::SEPARATOR; }
ShapeHints			{ return VRMLYacc::SHAPEHINTS; }
Sphere				{ return VRMLYacc::SPHERE; }
SpotLight			{ return VRMLYacc::SPOTLIGHT; }
Switch				{ return VRMLYacc::SWITCH; }
Texture2			         { return VRMLYacc::TEXTURE2; }
Texture2Transform		         { return VRMLYacc::TEXTURE2TRANSFORM; }
TextureCoordinate2		{ return VRMLYacc::TEXTURECOORDINATE2; }
Transform			{ return VRMLYacc::TRANSFORM; }
TransformSeparator		{ return VRMLYacc::TRANSFORMSEPARATOR; }
Translation			{ return VRMLYacc::TRANSLATION; }
WWWAnchor			{ return VRMLYacc::WWWANCHOR; }
WWWInline			{ return VRMLYacc::WWWINLINE; }

parts				{ return VRMLYacc::PARTS; }
bottomRadius			{ return VRMLYacc::BOTTOMRADIUS; }
height				{ return VRMLYacc::HEIGHT; }
point				{ return VRMLYacc::POINT; }
width				{ return VRMLYacc::WIDTH; }
depth				{ return VRMLYacc::DEPTH; }
string				{ return VRMLYacc::STRING; }
spacing				{ return VRMLYacc::SPACING; }
justification			{ return VRMLYacc::JUSTIFICATION; }
radius				{ return VRMLYacc::RADIUS; }
on				{ return VRMLYacc::ON; }
intensity			{ return VRMLYacc::INTENSITY; }
color				{ return VRMLYacc::COLOR; }
direction			{ return VRMLYacc::DIRECTION; }
size				{ return VRMLYacc::SIZE; }
family				{ return VRMLYacc::FAMILY; }
style				{ return VRMLYacc::STYLE; }
coordIndex			{ return VRMLYacc::COORDINDEX; }
materialIndex			{ return VRMLYacc::MATERIALINDEX; }
normalIndex			{ return VRMLYacc::NORMALINDEX; }
textureCoordIndex		         { return VRMLYacc::TEXTURECOORDINDEX; }
range				{ return VRMLYacc::RANGE; }
center				{ return VRMLYacc::CENTER; }
screenArea			{ return VRMLYacc::SCREENAREA; }
ambientColor			{ return VRMLYacc::AMBIENTCOLOR; }
diffuseColor			{ return VRMLYacc::DIFFUSECOLOR; }
specularColor			{ return VRMLYacc::SPECULARCOLOR; }
emissiveColor			{ return VRMLYacc::EMISSIVECOLOR; }
shininess			{ return VRMLYacc::SHININESS; }
transparency			{ return VRMLYacc::TRANSPARENCY; }
value				{ return VRMLYacc::VALUE; }
matrix				{ return VRMLYacc::MATRIX; }
vector				{ return VRMLYacc::VECTOR; }
position			         { return VRMLYacc::POSITION; }
orientation			{ return VRMLYacc::ORIENTATION; }
focalDistance			{ return VRMLYacc::FOCALDISTANCE; }
heightAngle			{ return VRMLYacc::HEIGHTANGLE; }
location			         { return VRMLYacc::LOCATION; }
startIndex			{ return VRMLYacc::STARTINDEX; }
numPoints			{ return VRMLYacc::NUMPOINTS; }
rotation			         { return VRMLYacc::ROTATION_F; }
scaleFactor			{ return VRMLYacc::SCALEFACTOR; }
renderCulling			{ return VRMLYacc::RENDERCULLING; }
vertexOrdering			{ return VRMLYacc::VERTEXORDERING; }
shapeType			{ return VRMLYacc::SHAPETYPE; }
faceType			         { return VRMLYacc::FACETYPE; }
creaseAngle			{ return VRMLYacc::CREASEANGLE; }
dropOffRate			{ return VRMLYacc::DROPOFFRATE; }
cutOffAngle			{ return VRMLYacc::CUTOFFANGLE; }
whichChild			{ return VRMLYacc::WHICHCHILD; }
filename			         { return VRMLYacc::FILENAME; }
image				{ return VRMLYacc::IMAGE; }
wrapS				{ return VRMLYacc::WRAPS; }
wrapT				{ return VRMLYacc::WRAPT; }
scaleOrientation		         { return VRMLYacc::SCALEORIENTATION; }
translation			{ return VRMLYacc::TRANSLATION_F; }
name				{ return VRMLYacc::NAME; }
description			{ return VRMLYacc::DESCRIPTION; }
map				{ return VRMLYacc::MAP; }
bboxSize			         { return VRMLYacc::BBOXSIZE; }
bboxCenter			{ return VRMLYacc::BBOXCENTER; }

LEFT				{ yylval.longval = (long)VRML_LEFT; return VRMLYacc::NUMBER; }
CENTER				{ yylval.longval = (long)VRML_CENTER; return VRMLYacc::NUMBER; }
RIGHT				{ yylval.longval = (long)VRML_RIGHT; return VRMLYacc::NUMBER; }

SIDES				{ yylval.longval = (long)VRML_SIDES; return VRMLYacc::NUMBER; }
BOTTOM				{ yylval.longval = (long)VRML_BOTTOM; return VRMLYacc::NUMBER; }
TOP				{ yylval.longval = (long)VRML_TOP; return VRMLYacc::NUMBER; }
ALL				{ yylval.longval = (long)VRML_ALL; return VRMLYacc::NUMBER; }

TRUE				{ yylval.boolval = true; return VRMLYacc::BOOL; }
FALSE				{ yylval.boolval = false; return VRMLYacc::BOOL; }

SERIF				{ yylval.longval = (long)VRML_SERIF; return VRMLYacc::NUMBER; }
SANS				{ yylval.longval = (long)VRML_SANS; return VRMLYacc::NUMBER; }
TYPEWRITER			{ yylval.longval = (long)VRML_TYPEWRITER; return VRMLYacc::NUMBER; }

NONE				{ yylval.longval = (long)VRML_NONE; return VRMLYacc::NUMBER; }
BOLD				{ yylval.longval = (long)VRML_BOLD; return VRMLYacc::NUMBER; }
ITALIC				{ yylval.longval = (long)VRML_ITALIC; return VRMLYacc::NUMBER; }

DEFAULT				{ yylval.longval = (long)VRML_DEFAULT; return VRMLYacc::NUMBER; }
OVERALL				{ yylval.longval = (long)VRML_OVERALL; return VRMLYacc::NUMBER; }
PER_PART			         { yylval.longval = (long)VRML_PER_PART; return VRMLYacc::NUMBER; }
PER_PART_INDEXED		         { yylval.longval = (long)VRML_PER_PART_INDEXED; return VRMLYacc::NUMBER; }
PER_FACE			         { yylval.longval = (long)VRML_PER_FACE; return VRMLYacc::NUMBER; }
PER_FACE_INDEXED		         { yylval.longval = (long)VRML_PER_FACE_INDEXED; return VRMLYacc::NUMBER; }
PER_VERTEX			{ yylval.longval = (long)VRML_PER_VERTEX; return VRMLYacc::NUMBER; }
PER_VERTEX_INDEXED		{ yylval.longval = (long)VRML_PER_VERTEX_INDEXED; return VRMLYacc::NUMBER; }

ON				{ yylval.longval = (long)VRML_ON; return VRMLYacc::NUMBER; }
OFF				{ yylval.longval = (long)VRML_OFF; return VRMLYacc::NUMBER; }
AUTO				{ yylval.longval = (long)VRML_AUTO; return VRMLYacc::NUMBER; }

UNKNOWN_ORDERING		         { yylval.longval = (long)VRML_UNKNOWN_ORDERING; return VRMLYacc::NUMBER; }
CLOCKWISE			{ yylval.longval = (long)VRML_CLOCKWISE; return VRMLYacc::NUMBER; }
COUNTERCLOCKWISE		         { yylval.longval = (long)VRML_COUNTERCLOCKWISE; return VRMLYacc::NUMBER; }

UNKNOWN_SHAPE_TYPE		{ yylval.longval = (long)VRML_UNKNOWN_SHAPE_TYPE; return VRMLYacc::NUMBER; }
SOLID				{ yylval.longval = (long)VRML_SOLID; return VRMLYacc::NUMBER; }

UNKNOWN_FACE_TYPE		         { yylval.longval = (long)VRML_UNKNOWN_FACE_TYPE; return VRMLYacc::NUMBER; }
CONVEX				{ yylval.longval = (long)VRML_CONVEX; return VRMLYacc::NUMBER; }

REPEAT				{ yylval.longval = (long)VRML_REPEAT; return VRMLYacc::NUMBER; }
CLAMP				{ yylval.longval = (long)VRML_CLAMP; return VRMLYacc::NUMBER; }

fields				{
				register int c;

				for ( ; ; ) {
				  do {
				    c = input();
				  } while (c!=']' && c!=EOF && c!='\n');
				  if (c=='\n') {
				    myCurrentLine ++;
				  } else if (c==']') {
				    return VRMLYacc::FIELDS;
				  } else {
				    yyterminate();
				    break;
				  }
				}
				return VRMLYacc::FIELDS;
				}

0				{ yylval.longval = 0; return VRMLYacc::NUMBER;}
-?[1-9][0-9]*			{ yylval.longval = atol(yytext); return VRMLYacc::NUMBER;}
0[1-7][0-7]*			{ sscanf((const char *)yytext, "%lo", &yylval.longval);
				  return VRMLYacc::NUMBER; }
-?[0-9]*\.?[0-9]*([eE][+-]?[0-9]+)? { yylval.doubleval = atof (yytext); return VRMLYacc::FLOAT;}
0x[0-9A-Fa-f]+			{ sscanf((const char *)yytext,
				  "0x%lx", &yylval.longval); return VRMLYacc::NUMBER; }

[\#].*\n			myCurrentLine++; /* Skip rest of line. */

\"				{
				register int c, oldc;
				char *buffer;
				int buflen=8;
				int len=0;

				c = EOF;
				buffer = (char *)malloc(buflen);
				if (!buffer)
				  yyterminate();
				buffer[0] = '\0';
				for (;;) {
				  oldc = c;
				  c = input();
				  if (c=='\"') {
				    if (oldc=='\\') {
				      buffer[len-1] = '\"';
				    } else {
				      yylval.stringval = buffer;
				      return VRMLYacc::VRMLSTRING;
				    }
				  } else {
				    if (len+2 >= buflen) {
				      buflen *= 2;
				      buffer = (char *)realloc(buffer, buflen);
				      if (!buffer)
					yyterminate();
				    }
				    buffer[len] = c;
				    buffer[++len] = '\0';
				  }
				}
				return VRMLYacc::VRMLSTRING;
				}				    
[ \t]+				;
\n				myCurrentLine++;

{ID}				{
				register int c;
				int stack = 0;

				for ( ; ; ) {
				  do {
				    c = input();
				  } while (c!='{' && c!='}' && c!=EOF &&
					   c!='\n');
				  if (c=='{') {
				    stack ++;
				  } else if (c=='}') {
				    stack --;
				  } else if (c=='\n') {
				    myCurrentLine++;
				  } else {
				    yyterminate();
				    break;
				  }
				  if (!stack)
				    break;
				}
				return VRMLYacc::UNKNOWNNODE;
				}

[|]				{ return *yytext; }
","				{ return ','; }
"}"				{ return '}'; }
"{"				{ return '{'; }
"["				{ return '['; }
"]"				{ return ']'; }
"~"                             { return '~'; }
.				;

%%


