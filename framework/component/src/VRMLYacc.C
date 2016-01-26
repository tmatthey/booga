#define YY_VRMLYacc_h_included

/*  A Bison++ parser, made from /home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y  */

 /* with Bison++ version bison++ Version 1.21-8, adapted from GNU bison by coetmeur@icdc.fr
  */


#line 1 "/usr/local/lib/bison.cc"
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Bob Corbett and Richard Stallman

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* HEADER SECTION */
#if defined( _MSDOS ) || defined(MSDOS) || defined(__MSDOS__) 
#define __MSDOS_AND_ALIKE
#endif
#if defined(_WINDOWS) && defined(_MSC_VER)
#define __HAVE_NO_ALLOCA
#define __MSDOS_AND_ALIKE
#endif

#ifndef alloca
#if defined( __GNUC__)
#define alloca __builtin_alloca

#elif (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc)  || defined (__sgi)
#include <alloca.h>

#elif defined (__MSDOS_AND_ALIKE)
#include <malloc.h>
#ifndef __TURBOC__
/* MS C runtime lib */
#define alloca _alloca
#endif

#elif defined(_AIX)
#include <malloc.h>
#pragma alloca

#elif defined(__hpux)
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */

#endif /* not _AIX  not MSDOS, or __TURBOC__ or _AIX, not sparc.  */
#endif /* alloca not defined.  */
#ifdef c_plusplus
#ifndef __cplusplus
#define __cplusplus
#endif
#endif
#ifdef __cplusplus
#ifndef YY_USE_CLASS
#define YY_USE_CLASS
#endif
#else
#ifndef __STDC__
#define const
#endif
#endif
#include <stdio.h>
#define YYBISON 1  

/* #line 73 "/usr/local/lib/bison.cc" */
#line 85 "VRMLYacc.C"
#line 33 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream.h>

#define YYMAXDEPTH 100000
#line 44 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"


#include "booga/base/Report.h"

#include "booga/object/World3D.h"
#include "booga/object/PerspectiveViewing3D.h"
#include "booga/object/Camera3D.h"

#include "VRML.h"
#include "VRMLObject.h"
#include "VRMLState.h"


#line 61 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
typedef union 
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
} yy_VRMLYacc_stype;
#define YY_VRMLYacc_STYPE yy_VRMLYacc_stype
#define YY_VRMLYacc_DEBUG  1
#define YY_VRMLYacc_DEBUG_FLAG  myParserDebugFlag
#define YY_VRMLYacc_ERROR_VERBOSE 
#define YY_VRMLYacc_ERROR_BODY  =0
#define YY_VRMLYacc_ERROR  fatalError
#define YY_VRMLYacc_NERRS  myErrorCount
#define YY_VRMLYacc_LEX_BODY  =0
#define YY_VRMLYacc_LEX   scan
#define YY_VRMLYacc_LVAL  myTokenValue
#define YY_VRMLYacc_PARSE  parse
#define YY_VRMLYacc_PARSE_PARAM 
#define YY_VRMLYacc_CONSTRUCTOR_PARAM  
#define YY_VRMLYacc_CONSTRUCTOR_INIT  : myParserDebugFlag(0), myWorld3D(NULL), mySymTable(113)
#define YY_VRMLYacc_CONSTRUCTOR_CODE  
#define YY_VRMLYacc_MEMBERS  \
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


#line 73 "/usr/local/lib/bison.cc"
/* %{ and %header{ and %union, during decl */
#define YY_VRMLYacc_BISON 1
#ifndef YY_VRMLYacc_COMPATIBILITY
#ifndef YY_USE_CLASS
#define  YY_VRMLYacc_COMPATIBILITY 1
#else
#define  YY_VRMLYacc_COMPATIBILITY 0
#endif
#endif

#if YY_VRMLYacc_COMPATIBILITY != 0
/* backward compatibility */
#ifdef YYLTYPE
#ifndef YY_VRMLYacc_LTYPE
#define YY_VRMLYacc_LTYPE YYLTYPE
#endif
#endif
#ifdef YYSTYPE
#ifndef YY_VRMLYacc_STYPE 
#define YY_VRMLYacc_STYPE YYSTYPE
#endif
#endif
#ifdef YYDEBUG
#ifndef YY_VRMLYacc_DEBUG
#define  YY_VRMLYacc_DEBUG YYDEBUG
#endif
#endif
#ifdef YY_VRMLYacc_STYPE
#ifndef yystype
#define yystype YY_VRMLYacc_STYPE
#endif
#endif
/* use goto to be compatible */
#ifndef YY_VRMLYacc_USE_GOTO
#define YY_VRMLYacc_USE_GOTO 1
#endif
#endif

/* use no goto to be clean in C++ */
#ifndef YY_VRMLYacc_USE_GOTO
#define YY_VRMLYacc_USE_GOTO 0
#endif

#ifndef YY_VRMLYacc_PURE

/* #line 117 "/usr/local/lib/bison.cc" */
#line 232 "VRMLYacc.C"

#line 117 "/usr/local/lib/bison.cc"
/*  YY_VRMLYacc_PURE */
#endif

/* section apres lecture def, avant lecture grammaire S2 */

/* #line 121 "/usr/local/lib/bison.cc" */
#line 241 "VRMLYacc.C"

#line 121 "/usr/local/lib/bison.cc"
/* prefix */
#ifndef YY_VRMLYacc_DEBUG

/* #line 123 "/usr/local/lib/bison.cc" */
#line 248 "VRMLYacc.C"

#line 123 "/usr/local/lib/bison.cc"
/* YY_VRMLYacc_DEBUG */
#endif


#ifndef YY_VRMLYacc_LSP_NEEDED

/* #line 128 "/usr/local/lib/bison.cc" */
#line 258 "VRMLYacc.C"

#line 128 "/usr/local/lib/bison.cc"
 /* YY_VRMLYacc_LSP_NEEDED*/
#endif



/* DEFAULT LTYPE*/
#ifdef YY_VRMLYacc_LSP_NEEDED
#ifndef YY_VRMLYacc_LTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YY_VRMLYacc_LTYPE yyltype
#endif
#endif
/* DEFAULT STYPE*/
      /* We used to use `unsigned long' as YY_VRMLYacc_STYPE on MSDOS,
	 but it seems better to be consistent.
	 Most programs should declare their own type anyway.  */

#ifndef YY_VRMLYacc_STYPE
#define YY_VRMLYacc_STYPE int
#endif
/* DEFAULT MISCELANEOUS */
#ifndef YY_VRMLYacc_PARSE
#define YY_VRMLYacc_PARSE yyparse
#endif
#ifndef YY_VRMLYacc_LEX
#define YY_VRMLYacc_LEX yylex
#endif
#ifndef YY_VRMLYacc_LVAL
#define YY_VRMLYacc_LVAL yylval
#endif
#ifndef YY_VRMLYacc_LLOC
#define YY_VRMLYacc_LLOC yylloc
#endif
#ifndef YY_VRMLYacc_CHAR
#define YY_VRMLYacc_CHAR yychar
#endif
#ifndef YY_VRMLYacc_NERRS
#define YY_VRMLYacc_NERRS yynerrs
#endif
#ifndef YY_VRMLYacc_DEBUG_FLAG
#define YY_VRMLYacc_DEBUG_FLAG yydebug
#endif
#ifndef YY_VRMLYacc_ERROR
#define YY_VRMLYacc_ERROR yyerror
#endif
#ifndef YY_VRMLYacc_PARSE_PARAM
#ifndef __STDC__
#ifndef __cplusplus
#ifndef YY_USE_CLASS
#define YY_VRMLYacc_PARSE_PARAM
#ifndef YY_VRMLYacc_PARSE_PARAM_DEF
#define YY_VRMLYacc_PARSE_PARAM_DEF
#endif
#endif
#endif
#endif
#ifndef YY_VRMLYacc_PARSE_PARAM
#define YY_VRMLYacc_PARSE_PARAM void
#endif
#endif
#if YY_VRMLYacc_COMPATIBILITY != 0
/* backward compatibility */
#ifdef YY_VRMLYacc_LTYPE
#ifndef YYLTYPE
#define YYLTYPE YY_VRMLYacc_LTYPE
#else
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
#endif
#endif
#ifndef YYSTYPE
#define YYSTYPE YY_VRMLYacc_STYPE
#else
/* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
#endif
#ifdef YY_VRMLYacc_PURE
#ifndef YYPURE
#define YYPURE YY_VRMLYacc_PURE
#endif
#endif
#ifdef YY_VRMLYacc_DEBUG
#ifndef YYDEBUG
#define YYDEBUG YY_VRMLYacc_DEBUG 
#endif
#endif
#ifndef YY_VRMLYacc_ERROR_VERBOSE
#ifdef YYERROR_VERBOSE
#define YY_VRMLYacc_ERROR_VERBOSE YYERROR_VERBOSE
#endif
#endif
#ifndef YY_VRMLYacc_LSP_NEEDED
#ifdef YYLSP_NEEDED
#define YY_VRMLYacc_LSP_NEEDED YYLSP_NEEDED
#endif
#endif
#endif
#ifndef YY_USE_CLASS
/* TOKEN C */

/* #line 236 "/usr/local/lib/bison.cc" */
#line 371 "VRMLYacc.C"
#define	BOOL	258
#define	NUMBER	259
#define	FLOAT	260
#define	VRMLSTRING	261
#define	VRMLWORD	262
#define	ASCIITEXT	263
#define	CONE	264
#define	COORDINATE3	265
#define	CUBE	266
#define	CYLINDER	267
#define	DIRECTIONALLIGHT	268
#define	FONTSTYLE	269
#define	GROUP	270
#define	INDEXEDFACESET	271
#define	INDEXEDLINESET	272
#define	INFO	273
#define	LOD	274
#define	MATERIAL	275
#define	MATERIALBINDING	276
#define	LEVELOFDETAIL	277
#define	MATRIXTRANSFORM	278
#define	NORMAL	279
#define	NORMALBINDING	280
#define	ORTHOGRAPHICCAMERA	281
#define	PERSPECTIVECAMERA	282
#define	POINTLIGHT	283
#define	POINTSET	284
#define	ROTATION	285
#define	SCALE	286
#define	SEPARATOR	287
#define	SHAPEHINTS	288
#define	SPHERE	289
#define	SPOTLIGHT	290
#define	SWITCH	291
#define	TEXTURE2	292
#define	TEXTURE2TRANSFORM	293
#define	TEXTURECOORDINATE2	294
#define	TRANSFORM	295
#define	TRANSFORMSEPARATOR	296
#define	TRANSLATION	297
#define	WWWANCHOR	298
#define	WWWINLINE	299
#define	PARTS	300
#define	BOTTOMRADIUS	301
#define	HEIGHT	302
#define	POINT	303
#define	WIDTH	304
#define	DEPTH	305
#define	STRING	306
#define	SPACING	307
#define	JUSTIFICATION	308
#define	RADIUS	309
#define	ON	310
#define	INTENSITY	311
#define	COLOR	312
#define	DIRECTION	313
#define	SIZE	314
#define	FAMILY	315
#define	STYLE	316
#define	COORDINDEX	317
#define	MATERIALINDEX	318
#define	NORMALINDEX	319
#define	TEXTURECOORDINDEX	320
#define	RANGE	321
#define	SCREENAREA	322
#define	TRANSLATION_F	323
#define	CENTER	324
#define	AMBIENTCOLOR	325
#define	DIFFUSECOLOR	326
#define	SPECULARCOLOR	327
#define	EMISSIVECOLOR	328
#define	SHININESS	329
#define	TRANSPARENCY	330
#define	VALUE	331
#define	MATRIX	332
#define	VECTOR	333
#define	POSITION	334
#define	ORIENTATION	335
#define	FOCALDISTANCE	336
#define	HEIGHTANGLE	337
#define	LOCATION	338
#define	STARTINDEX	339
#define	NUMPOINTS	340
#define	ROTATION_F	341
#define	SCALEFACTOR	342
#define	RENDERCULLING	343
#define	VERTEXORDERING	344
#define	SHAPETYPE	345
#define	FACETYPE	346
#define	CREASEANGLE	347
#define	DROPOFFRATE	348
#define	CUTOFFANGLE	349
#define	WHICHCHILD	350
#define	FILENAME	351
#define	IMAGE	352
#define	WRAPS	353
#define	WRAPT	354
#define	SCALEORIENTATION	355
#define	NAME	356
#define	DESCRIPTION	357
#define	MAP	358
#define	BBOXSIZE	359
#define	BBOXCENTER	360
#define	DEF	361
#define	USE	362
#define	FIELDS	363
#define	UNKNOWNNODE	364


#line 236 "/usr/local/lib/bison.cc"
 /* #defines tokens */
#else
/* CLASS */
#ifndef YY_VRMLYacc_CLASS
#define YY_VRMLYacc_CLASS VRMLYacc
#endif
#ifndef YY_VRMLYacc_INHERIT
#define YY_VRMLYacc_INHERIT
#endif
#ifndef YY_VRMLYacc_MEMBERS
#define YY_VRMLYacc_MEMBERS 
#endif
#ifndef YY_VRMLYacc_LEX_BODY
#define YY_VRMLYacc_LEX_BODY  
#endif
#ifndef YY_VRMLYacc_ERROR_BODY
#define YY_VRMLYacc_ERROR_BODY  
#endif
#ifndef YY_VRMLYacc_CONSTRUCTOR_PARAM
#define YY_VRMLYacc_CONSTRUCTOR_PARAM
#endif
#ifndef YY_VRMLYacc_CONSTRUCTOR_CODE
#define YY_VRMLYacc_CONSTRUCTOR_CODE
#endif
#ifndef YY_VRMLYacc_CONSTRUCTOR_INIT
#define YY_VRMLYacc_CONSTRUCTOR_INIT
#endif
/* choose between enum and const */
#ifndef YY_VRMLYacc_USE_CONST_TOKEN
#define YY_VRMLYacc_USE_CONST_TOKEN 0
/* yes enum is more compatible with flex,  */
/* so by default we use it */ 
#endif
#if YY_VRMLYacc_USE_CONST_TOKEN != 0
#ifndef YY_VRMLYacc_ENUM_TOKEN
#define YY_VRMLYacc_ENUM_TOKEN yy_VRMLYacc_enum_token
#endif
#endif

class YY_VRMLYacc_CLASS YY_VRMLYacc_INHERIT
{
public: 
#if YY_VRMLYacc_USE_CONST_TOKEN != 0
/* static const int token ... */

/* #line 280 "/usr/local/lib/bison.cc" */
#line 528 "VRMLYacc.C"
static const int BOOL;
static const int NUMBER;
static const int FLOAT;
static const int VRMLSTRING;
static const int VRMLWORD;
static const int ASCIITEXT;
static const int CONE;
static const int COORDINATE3;
static const int CUBE;
static const int CYLINDER;
static const int DIRECTIONALLIGHT;
static const int FONTSTYLE;
static const int GROUP;
static const int INDEXEDFACESET;
static const int INDEXEDLINESET;
static const int INFO;
static const int LOD;
static const int MATERIAL;
static const int MATERIALBINDING;
static const int LEVELOFDETAIL;
static const int MATRIXTRANSFORM;
static const int NORMAL;
static const int NORMALBINDING;
static const int ORTHOGRAPHICCAMERA;
static const int PERSPECTIVECAMERA;
static const int POINTLIGHT;
static const int POINTSET;
static const int ROTATION;
static const int SCALE;
static const int SEPARATOR;
static const int SHAPEHINTS;
static const int SPHERE;
static const int SPOTLIGHT;
static const int SWITCH;
static const int TEXTURE2;
static const int TEXTURE2TRANSFORM;
static const int TEXTURECOORDINATE2;
static const int TRANSFORM;
static const int TRANSFORMSEPARATOR;
static const int TRANSLATION;
static const int WWWANCHOR;
static const int WWWINLINE;
static const int PARTS;
static const int BOTTOMRADIUS;
static const int HEIGHT;
static const int POINT;
static const int WIDTH;
static const int DEPTH;
static const int STRING;
static const int SPACING;
static const int JUSTIFICATION;
static const int RADIUS;
static const int ON;
static const int INTENSITY;
static const int COLOR;
static const int DIRECTION;
static const int SIZE;
static const int FAMILY;
static const int STYLE;
static const int COORDINDEX;
static const int MATERIALINDEX;
static const int NORMALINDEX;
static const int TEXTURECOORDINDEX;
static const int RANGE;
static const int SCREENAREA;
static const int TRANSLATION_F;
static const int CENTER;
static const int AMBIENTCOLOR;
static const int DIFFUSECOLOR;
static const int SPECULARCOLOR;
static const int EMISSIVECOLOR;
static const int SHININESS;
static const int TRANSPARENCY;
static const int VALUE;
static const int MATRIX;
static const int VECTOR;
static const int POSITION;
static const int ORIENTATION;
static const int FOCALDISTANCE;
static const int HEIGHTANGLE;
static const int LOCATION;
static const int STARTINDEX;
static const int NUMPOINTS;
static const int ROTATION_F;
static const int SCALEFACTOR;
static const int RENDERCULLING;
static const int VERTEXORDERING;
static const int SHAPETYPE;
static const int FACETYPE;
static const int CREASEANGLE;
static const int DROPOFFRATE;
static const int CUTOFFANGLE;
static const int WHICHCHILD;
static const int FILENAME;
static const int IMAGE;
static const int WRAPS;
static const int WRAPT;
static const int SCALEORIENTATION;
static const int NAME;
static const int DESCRIPTION;
static const int MAP;
static const int BBOXSIZE;
static const int BBOXCENTER;
static const int DEF;
static const int USE;
static const int FIELDS;
static const int UNKNOWNNODE;


#line 280 "/usr/local/lib/bison.cc"
 /* decl const */
#else
enum YY_VRMLYacc_ENUM_TOKEN { YY_VRMLYacc_NULL_TOKEN=0

/* #line 283 "/usr/local/lib/bison.cc" */
#line 644 "VRMLYacc.C"
	,BOOL=258
	,NUMBER=259
	,FLOAT=260
	,VRMLSTRING=261
	,VRMLWORD=262
	,ASCIITEXT=263
	,CONE=264
	,COORDINATE3=265
	,CUBE=266
	,CYLINDER=267
	,DIRECTIONALLIGHT=268
	,FONTSTYLE=269
	,GROUP=270
	,INDEXEDFACESET=271
	,INDEXEDLINESET=272
	,INFO=273
	,LOD=274
	,MATERIAL=275
	,MATERIALBINDING=276
	,LEVELOFDETAIL=277
	,MATRIXTRANSFORM=278
	,NORMAL=279
	,NORMALBINDING=280
	,ORTHOGRAPHICCAMERA=281
	,PERSPECTIVECAMERA=282
	,POINTLIGHT=283
	,POINTSET=284
	,ROTATION=285
	,SCALE=286
	,SEPARATOR=287
	,SHAPEHINTS=288
	,SPHERE=289
	,SPOTLIGHT=290
	,SWITCH=291
	,TEXTURE2=292
	,TEXTURE2TRANSFORM=293
	,TEXTURECOORDINATE2=294
	,TRANSFORM=295
	,TRANSFORMSEPARATOR=296
	,TRANSLATION=297
	,WWWANCHOR=298
	,WWWINLINE=299
	,PARTS=300
	,BOTTOMRADIUS=301
	,HEIGHT=302
	,POINT=303
	,WIDTH=304
	,DEPTH=305
	,STRING=306
	,SPACING=307
	,JUSTIFICATION=308
	,RADIUS=309
	,ON=310
	,INTENSITY=311
	,COLOR=312
	,DIRECTION=313
	,SIZE=314
	,FAMILY=315
	,STYLE=316
	,COORDINDEX=317
	,MATERIALINDEX=318
	,NORMALINDEX=319
	,TEXTURECOORDINDEX=320
	,RANGE=321
	,SCREENAREA=322
	,TRANSLATION_F=323
	,CENTER=324
	,AMBIENTCOLOR=325
	,DIFFUSECOLOR=326
	,SPECULARCOLOR=327
	,EMISSIVECOLOR=328
	,SHININESS=329
	,TRANSPARENCY=330
	,VALUE=331
	,MATRIX=332
	,VECTOR=333
	,POSITION=334
	,ORIENTATION=335
	,FOCALDISTANCE=336
	,HEIGHTANGLE=337
	,LOCATION=338
	,STARTINDEX=339
	,NUMPOINTS=340
	,ROTATION_F=341
	,SCALEFACTOR=342
	,RENDERCULLING=343
	,VERTEXORDERING=344
	,SHAPETYPE=345
	,FACETYPE=346
	,CREASEANGLE=347
	,DROPOFFRATE=348
	,CUTOFFANGLE=349
	,WHICHCHILD=350
	,FILENAME=351
	,IMAGE=352
	,WRAPS=353
	,WRAPT=354
	,SCALEORIENTATION=355
	,NAME=356
	,DESCRIPTION=357
	,MAP=358
	,BBOXSIZE=359
	,BBOXCENTER=360
	,DEF=361
	,USE=362
	,FIELDS=363
	,UNKNOWNNODE=364


#line 283 "/usr/local/lib/bison.cc"
 /* enum token */
     }; /* end of enum declaration */
#endif
public:
 int YY_VRMLYacc_PARSE (YY_VRMLYacc_PARSE_PARAM);
 virtual void YY_VRMLYacc_ERROR(char *msg) YY_VRMLYacc_ERROR_BODY;
#ifdef YY_VRMLYacc_PURE
#ifdef YY_VRMLYacc_LSP_NEEDED
 virtual int  YY_VRMLYacc_LEX (YY_VRMLYacc_STYPE *YY_VRMLYacc_LVAL,YY_VRMLYacc_LTYPE *YY_VRMLYacc_LLOC) YY_VRMLYacc_LEX_BODY;
#else
 virtual int  YY_VRMLYacc_LEX (YY_VRMLYacc_STYPE *YY_VRMLYacc_LVAL) YY_VRMLYacc_LEX_BODY;
#endif
#else
 virtual int YY_VRMLYacc_LEX() YY_VRMLYacc_LEX_BODY;
 YY_VRMLYacc_STYPE YY_VRMLYacc_LVAL;
#ifdef YY_VRMLYacc_LSP_NEEDED
 YY_VRMLYacc_LTYPE YY_VRMLYacc_LLOC;
#endif
 int   YY_VRMLYacc_NERRS;
 int    YY_VRMLYacc_CHAR;
#endif
#if YY_VRMLYacc_DEBUG != 0
 int YY_VRMLYacc_DEBUG_FLAG;   /*  nonzero means print parse trace     */
#endif
public:
 YY_VRMLYacc_CLASS(YY_VRMLYacc_CONSTRUCTOR_PARAM);
public:
 YY_VRMLYacc_MEMBERS 
};
/* other declare folow */
#if YY_VRMLYacc_USE_CONST_TOKEN != 0

/* #line 314 "/usr/local/lib/bison.cc" */
#line 788 "VRMLYacc.C"
const int YY_VRMLYacc_CLASS::BOOL=258;
const int YY_VRMLYacc_CLASS::NUMBER=259;
const int YY_VRMLYacc_CLASS::FLOAT=260;
const int YY_VRMLYacc_CLASS::VRMLSTRING=261;
const int YY_VRMLYacc_CLASS::VRMLWORD=262;
const int YY_VRMLYacc_CLASS::ASCIITEXT=263;
const int YY_VRMLYacc_CLASS::CONE=264;
const int YY_VRMLYacc_CLASS::COORDINATE3=265;
const int YY_VRMLYacc_CLASS::CUBE=266;
const int YY_VRMLYacc_CLASS::CYLINDER=267;
const int YY_VRMLYacc_CLASS::DIRECTIONALLIGHT=268;
const int YY_VRMLYacc_CLASS::FONTSTYLE=269;
const int YY_VRMLYacc_CLASS::GROUP=270;
const int YY_VRMLYacc_CLASS::INDEXEDFACESET=271;
const int YY_VRMLYacc_CLASS::INDEXEDLINESET=272;
const int YY_VRMLYacc_CLASS::INFO=273;
const int YY_VRMLYacc_CLASS::LOD=274;
const int YY_VRMLYacc_CLASS::MATERIAL=275;
const int YY_VRMLYacc_CLASS::MATERIALBINDING=276;
const int YY_VRMLYacc_CLASS::LEVELOFDETAIL=277;
const int YY_VRMLYacc_CLASS::MATRIXTRANSFORM=278;
const int YY_VRMLYacc_CLASS::NORMAL=279;
const int YY_VRMLYacc_CLASS::NORMALBINDING=280;
const int YY_VRMLYacc_CLASS::ORTHOGRAPHICCAMERA=281;
const int YY_VRMLYacc_CLASS::PERSPECTIVECAMERA=282;
const int YY_VRMLYacc_CLASS::POINTLIGHT=283;
const int YY_VRMLYacc_CLASS::POINTSET=284;
const int YY_VRMLYacc_CLASS::ROTATION=285;
const int YY_VRMLYacc_CLASS::SCALE=286;
const int YY_VRMLYacc_CLASS::SEPARATOR=287;
const int YY_VRMLYacc_CLASS::SHAPEHINTS=288;
const int YY_VRMLYacc_CLASS::SPHERE=289;
const int YY_VRMLYacc_CLASS::SPOTLIGHT=290;
const int YY_VRMLYacc_CLASS::SWITCH=291;
const int YY_VRMLYacc_CLASS::TEXTURE2=292;
const int YY_VRMLYacc_CLASS::TEXTURE2TRANSFORM=293;
const int YY_VRMLYacc_CLASS::TEXTURECOORDINATE2=294;
const int YY_VRMLYacc_CLASS::TRANSFORM=295;
const int YY_VRMLYacc_CLASS::TRANSFORMSEPARATOR=296;
const int YY_VRMLYacc_CLASS::TRANSLATION=297;
const int YY_VRMLYacc_CLASS::WWWANCHOR=298;
const int YY_VRMLYacc_CLASS::WWWINLINE=299;
const int YY_VRMLYacc_CLASS::PARTS=300;
const int YY_VRMLYacc_CLASS::BOTTOMRADIUS=301;
const int YY_VRMLYacc_CLASS::HEIGHT=302;
const int YY_VRMLYacc_CLASS::POINT=303;
const int YY_VRMLYacc_CLASS::WIDTH=304;
const int YY_VRMLYacc_CLASS::DEPTH=305;
const int YY_VRMLYacc_CLASS::STRING=306;
const int YY_VRMLYacc_CLASS::SPACING=307;
const int YY_VRMLYacc_CLASS::JUSTIFICATION=308;
const int YY_VRMLYacc_CLASS::RADIUS=309;
const int YY_VRMLYacc_CLASS::ON=310;
const int YY_VRMLYacc_CLASS::INTENSITY=311;
const int YY_VRMLYacc_CLASS::COLOR=312;
const int YY_VRMLYacc_CLASS::DIRECTION=313;
const int YY_VRMLYacc_CLASS::SIZE=314;
const int YY_VRMLYacc_CLASS::FAMILY=315;
const int YY_VRMLYacc_CLASS::STYLE=316;
const int YY_VRMLYacc_CLASS::COORDINDEX=317;
const int YY_VRMLYacc_CLASS::MATERIALINDEX=318;
const int YY_VRMLYacc_CLASS::NORMALINDEX=319;
const int YY_VRMLYacc_CLASS::TEXTURECOORDINDEX=320;
const int YY_VRMLYacc_CLASS::RANGE=321;
const int YY_VRMLYacc_CLASS::SCREENAREA=322;
const int YY_VRMLYacc_CLASS::TRANSLATION_F=323;
const int YY_VRMLYacc_CLASS::CENTER=324;
const int YY_VRMLYacc_CLASS::AMBIENTCOLOR=325;
const int YY_VRMLYacc_CLASS::DIFFUSECOLOR=326;
const int YY_VRMLYacc_CLASS::SPECULARCOLOR=327;
const int YY_VRMLYacc_CLASS::EMISSIVECOLOR=328;
const int YY_VRMLYacc_CLASS::SHININESS=329;
const int YY_VRMLYacc_CLASS::TRANSPARENCY=330;
const int YY_VRMLYacc_CLASS::VALUE=331;
const int YY_VRMLYacc_CLASS::MATRIX=332;
const int YY_VRMLYacc_CLASS::VECTOR=333;
const int YY_VRMLYacc_CLASS::POSITION=334;
const int YY_VRMLYacc_CLASS::ORIENTATION=335;
const int YY_VRMLYacc_CLASS::FOCALDISTANCE=336;
const int YY_VRMLYacc_CLASS::HEIGHTANGLE=337;
const int YY_VRMLYacc_CLASS::LOCATION=338;
const int YY_VRMLYacc_CLASS::STARTINDEX=339;
const int YY_VRMLYacc_CLASS::NUMPOINTS=340;
const int YY_VRMLYacc_CLASS::ROTATION_F=341;
const int YY_VRMLYacc_CLASS::SCALEFACTOR=342;
const int YY_VRMLYacc_CLASS::RENDERCULLING=343;
const int YY_VRMLYacc_CLASS::VERTEXORDERING=344;
const int YY_VRMLYacc_CLASS::SHAPETYPE=345;
const int YY_VRMLYacc_CLASS::FACETYPE=346;
const int YY_VRMLYacc_CLASS::CREASEANGLE=347;
const int YY_VRMLYacc_CLASS::DROPOFFRATE=348;
const int YY_VRMLYacc_CLASS::CUTOFFANGLE=349;
const int YY_VRMLYacc_CLASS::WHICHCHILD=350;
const int YY_VRMLYacc_CLASS::FILENAME=351;
const int YY_VRMLYacc_CLASS::IMAGE=352;
const int YY_VRMLYacc_CLASS::WRAPS=353;
const int YY_VRMLYacc_CLASS::WRAPT=354;
const int YY_VRMLYacc_CLASS::SCALEORIENTATION=355;
const int YY_VRMLYacc_CLASS::NAME=356;
const int YY_VRMLYacc_CLASS::DESCRIPTION=357;
const int YY_VRMLYacc_CLASS::MAP=358;
const int YY_VRMLYacc_CLASS::BBOXSIZE=359;
const int YY_VRMLYacc_CLASS::BBOXCENTER=360;
const int YY_VRMLYacc_CLASS::DEF=361;
const int YY_VRMLYacc_CLASS::USE=362;
const int YY_VRMLYacc_CLASS::FIELDS=363;
const int YY_VRMLYacc_CLASS::UNKNOWNNODE=364;


#line 314 "/usr/local/lib/bison.cc"
 /* const YY_VRMLYacc_CLASS::token */
#endif
/*apres const  */
YY_VRMLYacc_CLASS::YY_VRMLYacc_CLASS(YY_VRMLYacc_CONSTRUCTOR_PARAM) YY_VRMLYacc_CONSTRUCTOR_INIT
{
#if YY_VRMLYacc_DEBUG != 0
YY_VRMLYacc_DEBUG_FLAG=0;
#endif
YY_VRMLYacc_CONSTRUCTOR_CODE;
};
#endif

/* #line 325 "/usr/local/lib/bison.cc" */
#line 912 "VRMLYacc.C"


#define	YYFINAL		616
#define	YYFLAG		-32768
#define	YYNTBASE	119

#define YYTRANSLATE(x) ((unsigned)(x) <= 364 ? yytranslate[x] : 284)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,   113,
   114,     2,     2,   115,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
   116,     2,   117,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,   110,   112,   111,   118,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
    76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
    86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
    96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
   106,   107,   108,   109
};

#if YY_VRMLYacc_DEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     6,     9,    10,    12,    13,    18,    21,
    23,    25,    27,    29,    31,    33,    35,    37,    39,    41,
    43,    45,    47,    49,    51,    53,    55,    57,    59,    61,
    63,    65,    67,    69,    71,    73,    75,    77,    79,    81,
    83,    85,    87,    89,    91,    93,    95,    97,    99,   100,
   102,   105,   106,   109,   112,   115,   118,   124,   127,   128,
   131,   134,   137,   138,   145,   148,   149,   150,   157,   160,
   161,   164,   167,   170,   171,   178,   181,   182,   185,   188,
   191,   192,   199,   202,   203,   206,   209,   212,   215,   216,
   223,   226,   227,   230,   233,   236,   242,   247,   250,   251,
   254,   257,   260,   263,   264,   271,   274,   275,   278,   281,
   284,   287,   293,   296,   297,   303,   306,   307,   310,   313,
   314,   322,   325,   326,   333,   336,   337,   340,   343,   346,
   349,   352,   355,   356,   363,   366,   367,   370,   371,   378,
   381,   382,   385,   386,   393,   396,   397,   400,   401,   408,
   411,   412,   415,   416,   423,   426,   427,   430,   433,   436,
   439,   440,   447,   450,   451,   454,   457,   460,   463,   464,
   471,   474,   475,   478,   481,   484,   487,   488,   495,   498,
   499,   502,   505,   511,   514,   515,   518,   519,   526,   529,
   530,   533,   534,   541,   544,   545,   548,   549,   557,   560,
   561,   564,   567,   570,   573,   579,   582,   583,   586,   587,
   594,   597,   598,   601,   604,   607,   610,   613,   616,   619,
   620,   627,   630,   631,   634,   635,   636,   645,   648,   649,
   652,   655,   658,   661,   667,   670,   671,   674,   677,   680,
   683,   689,   692,   693,   696,   702,   705,   706,   709,   712,
   715,   718,   721,   722,   729,   730,   737,   740,   741,   744,
   745,   752,   755,   756,   759,   762,   765,   772,   775,   776,
   779,   782,   785,   791,   793,   797,   799,   803,   805,   809,
   811,   813,   815,   818,   819,   824,   826,   843,   848,   850,
   853,   857,   859,   862,   866,   867,   870,   874,   876,   878,
   881,   885,   887,   891,   893,   895,   898,   902,   904,   908,
   910,   912,   913,   918,   920,   924,   926,   929,   933,   935,
   939,   941,   944,   948,   950,   954
};

static const short yyrhs[] = {    -1,
   120,   121,     0,     1,     0,   122,   121,     0,     0,   124,
     0,     0,   106,     7,   123,   124,     0,   107,     7,     0,
   129,     0,   132,     0,   135,     0,   139,     0,   143,     0,
   147,     0,   151,     0,   152,     0,   155,     0,   159,     0,
   161,     0,   164,     0,   167,     0,   170,     0,   174,     0,
   178,     0,   182,     0,   186,     0,   190,     0,   194,     0,
   198,     0,   202,     0,   205,     0,   209,     0,   213,     0,
   217,     0,   220,     0,   224,     0,   228,     0,   233,     0,
   236,     0,   239,     0,   242,     0,   244,     0,   248,     0,
   252,     0,   255,     0,   126,     0,   108,     0,     0,   109,
     0,   128,   127,     0,     0,    51,   279,     0,    52,   261,
     0,    53,   260,     0,    49,   276,     0,     8,   110,   125,
   127,   111,     0,   131,   130,     0,     0,    45,   257,     0,
    46,   261,     0,    47,   261,     0,     0,     9,   133,   110,
   125,   130,   111,     0,    48,   283,     0,     0,     0,    10,
   136,   110,   125,   134,   111,     0,   138,   137,     0,     0,
    49,   261,     0,    47,   261,     0,    50,   261,     0,     0,
    11,   140,   110,   125,   137,   111,     0,   142,   141,     0,
     0,    45,   257,     0,    54,   261,     0,    47,   261,     0,
     0,    12,   144,   110,   125,   141,   111,     0,   146,   145,
     0,     0,    55,   258,     0,    56,   261,     0,    57,   259,
     0,    58,   269,     0,     0,    13,   148,   110,   125,   145,
   111,     0,   150,   149,     0,     0,    59,   261,     0,    60,
   260,     0,    61,   257,     0,    14,   110,   125,   149,   111,
     0,    15,   110,   121,   111,     0,   154,   153,     0,     0,
    62,   274,     0,    63,   274,     0,    64,   274,     0,    65,
   274,     0,     0,    16,   156,   110,   125,   153,   111,     0,
   158,   157,     0,     0,    62,   274,     0,    63,   274,     0,
    64,   274,     0,    65,   274,     0,    17,   110,   125,   157,
   111,     0,    51,   267,     0,     0,    18,   110,   125,   160,
   111,     0,   163,   162,     0,     0,    66,   276,     0,    69,
   269,     0,     0,    19,   110,   125,   162,   165,   121,   111,
     0,    67,   276,     0,     0,    22,   110,   125,   166,   121,
   111,     0,   169,   168,     0,     0,    70,   271,     0,    71,
   271,     0,    72,   271,     0,    73,   271,     0,    74,   276,
     0,    75,   276,     0,     0,    20,   171,   110,   125,   168,
   111,     0,   173,   172,     0,     0,    76,   260,     0,     0,
    21,   175,   110,   125,   172,   111,     0,   177,   176,     0,
     0,    77,   265,     0,     0,    23,   179,   110,   125,   176,
   111,     0,   181,   180,     0,     0,    78,   283,     0,     0,
    24,   183,   110,   125,   180,   111,     0,   185,   184,     0,
     0,    76,   260,     0,     0,    25,   187,   110,   125,   184,
   111,     0,   189,   188,     0,     0,    79,   269,     0,    80,
   266,     0,    81,   261,     0,    47,   261,     0,     0,    26,
   191,   110,   125,   188,   111,     0,   193,   192,     0,     0,
    79,   269,     0,    80,   266,     0,    81,   261,     0,    82,
   261,     0,     0,    27,   195,   110,   125,   192,   111,     0,
   197,   196,     0,     0,    55,   258,     0,    56,   261,     0,
    57,   259,     0,    83,   269,     0,     0,    28,   199,   110,
   125,   196,   111,     0,   201,   200,     0,     0,    84,   264,
     0,    85,   264,     0,    29,   110,   125,   200,   111,     0,
   204,   203,     0,     0,    86,   266,     0,     0,    30,   206,
   110,   125,   203,   111,     0,   208,   207,     0,     0,    87,
   269,     0,     0,    31,   210,   110,   125,   207,   111,     0,
   212,   211,     0,     0,    88,   260,     0,     0,    32,   110,
   125,   211,   214,   121,   111,     0,   216,   215,     0,     0,
    89,   260,     0,    90,   260,     0,    91,   260,     0,    92,
   261,     0,    33,   110,   125,   215,   111,     0,   219,   218,
     0,     0,    54,   261,     0,     0,    34,   221,   110,   125,
   218,   111,     0,   223,   222,     0,     0,    55,   258,     0,
    56,   261,     0,    57,   259,     0,    83,   269,     0,    58,
   269,     0,    93,   261,     0,    94,   261,     0,     0,    35,
   225,   110,   125,   222,   111,     0,   227,   226,     0,     0,
    95,   264,     0,     0,     0,    36,   229,   110,   125,   226,
   230,   121,   111,     0,   232,   231,     0,     0,    96,   267,
     0,    97,   263,     0,    98,   260,     0,    99,   260,     0,
    37,   110,   125,   231,   111,     0,   235,   234,     0,     0,
    68,   268,     0,    86,   261,     0,    87,   268,     0,    69,
   268,     0,    38,   110,   125,   234,   111,     0,   238,   237,
     0,     0,    48,   281,     0,    39,   110,   125,   237,   111,
     0,   241,   240,     0,     0,    68,   269,     0,    86,   266,
     0,    87,   269,     0,   100,   266,     0,    69,   269,     0,
     0,    40,   243,   110,   125,   240,   111,     0,     0,    41,
   110,   125,   245,   121,   111,     0,   247,   246,     0,     0,
    68,   269,     0,     0,    42,   249,   110,   125,   246,   111,
     0,   251,   250,     0,     0,   101,   267,     0,   102,   267,
     0,   103,   260,     0,    43,   110,   125,   250,   121,   111,
     0,   254,   253,     0,     0,   101,   267,     0,   104,   269,
     0,   105,   269,     0,    44,   110,   125,   253,   111,     0,
     4,     0,   256,   112,     4,     0,     4,     0,   113,   256,
   114,     0,     3,     0,   261,   261,   261,     0,     4,     0,
     5,     0,     4,     0,     4,   262,     0,     0,     4,     4,
     4,   262,     0,     4,     0,   261,   261,   261,   261,   261,
   261,   261,   261,   261,   261,   261,   261,   261,   261,   261,
   261,     0,   261,   261,   261,   261,     0,     6,     0,   261,
   261,     0,   261,   261,   261,     0,   259,     0,   259,   115,
     0,   259,   115,   270,     0,     0,   272,   259,     0,   116,
   270,   117,     0,   118,     0,   264,     0,   264,   115,     0,
   264,   115,   273,     0,   264,     0,   116,   273,   117,     0,
   118,     0,   261,     0,   261,   115,     0,   261,   115,   275,
     0,   261,     0,   116,   275,   117,     0,   118,     0,   267,
     0,     0,   267,   278,   115,   277,     0,   267,     0,   116,
   277,   117,     0,   268,     0,   268,   115,     0,   268,   115,
   280,     0,   268,     0,   116,   280,   117,     0,   269,     0,
   269,   115,     0,   269,   115,   282,     0,   269,     0,   116,
   282,   117,     0,   118,     0
};

#endif

#if YY_VRMLYacc_DEBUG != 0
static const short yyrline[] = { 0,
   197,   205,   251,   254,   255,   258,   259,   266,   271,   280,
   281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
   291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
   301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
   311,   312,   313,   314,   315,   316,   317,   321,   322,   326,
   330,   331,   334,   335,   336,   337,   340,   347,   348,   351,
   355,   359,   365,   369,   377,   382,   385,   389,   397,   398,
   401,   405,   409,   415,   419,   428,   429,   432,   436,   440,
   446,   450,   458,   459,   462,   466,   470,   475,   482,   487,
   501,   502,   505,   506,   507,   510,   517,   521,   522,   525,
   530,   535,   540,   546,   550,   558,   559,   562,   566,   570,
   574,   580,   587,   591,   594,   603,   604,   607,   608,   614,
   620,   627,   628,   631,   638,   639,   642,   647,   652,   657,
   662,   667,   674,   678,   686,   687,   690,   700,   704,   712,
   713,   716,   723,   727,   735,   736,   739,   746,   751,   759,
   760,   763,   769,   774,   782,   783,   786,   791,   796,   800,
   806,   810,   819,   820,   823,   828,   833,   837,   843,   847,
   856,   857,   860,   864,   868,   873,   880,   881,   890,   891,
   894,   895,   898,   905,   906,   909,   916,   920,   928,   929,
   932,   939,   943,   951,   952,   955,   958,   963,   971,   972,
   975,   976,   977,   978,   981,   988,   989,   992,   998,   999,
  1007,  1008,  1011,  1015,  1019,  1024,  1029,  1034,  1038,  1044,
  1049,  1058,  1059,  1062,  1068,  1069,  1074,  1082,  1083,  1086,
  1090,  1091,  1092,  1095,  1102,  1103,  1106,  1107,  1108,  1109,
  1112,  1119,  1120,  1123,  1126,  1133,  1134,  1137,  1142,  1147,
  1152,  1157,  1164,  1165,  1173,  1178,  1186,  1187,  1190,  1197,
  1198,  1206,  1207,  1210,  1214,  1218,  1221,  1228,  1229,  1232,
  1236,  1240,  1246,  1257,  1258,  1261,  1262,  1265,  1268,  1271,
  1274,  1275,  1278,  1279,  1282,  1285,  1288,  1302,  1306,  1309,
  1312,  1316,  1317,  1318,  1321,  1321,  1322,  1323,  1326,  1327,
  1328,  1331,  1332,  1333,  1336,  1337,  1338,  1341,  1342,  1343,
  1346,  1347,  1347,  1350,  1351,  1354,  1355,  1356,  1359,  1360,
  1363,  1364,  1365,  1368,  1369,  1370
};

static const char * const yytname[] = {   "$","error","$illegal.","BOOL","NUMBER",
"FLOAT","VRMLSTRING","VRMLWORD","ASCIITEXT","CONE","COORDINATE3","CUBE","CYLINDER",
"DIRECTIONALLIGHT","FONTSTYLE","GROUP","INDEXEDFACESET","INDEXEDLINESET","INFO",
"LOD","MATERIAL","MATERIALBINDING","LEVELOFDETAIL","MATRIXTRANSFORM","NORMAL",
"NORMALBINDING","ORTHOGRAPHICCAMERA","PERSPECTIVECAMERA","POINTLIGHT","POINTSET",
"ROTATION","SCALE","SEPARATOR","SHAPEHINTS","SPHERE","SPOTLIGHT","SWITCH","TEXTURE2",
"TEXTURE2TRANSFORM","TEXTURECOORDINATE2","TRANSFORM","TRANSFORMSEPARATOR","TRANSLATION",
"WWWANCHOR","WWWINLINE","PARTS","BOTTOMRADIUS","HEIGHT","POINT","WIDTH","DEPTH",
"STRING","SPACING","JUSTIFICATION","RADIUS","ON","INTENSITY","COLOR","DIRECTION",
"SIZE","FAMILY","STYLE","COORDINDEX","MATERIALINDEX","NORMALINDEX","TEXTURECOORDINDEX",
"RANGE","SCREENAREA","TRANSLATION_F","CENTER","AMBIENTCOLOR","DIFFUSECOLOR",
"SPECULARCOLOR","EMISSIVECOLOR","SHININESS","TRANSPARENCY","VALUE","MATRIX",
"VECTOR","POSITION","ORIENTATION","FOCALDISTANCE","HEIGHTANGLE","LOCATION","STARTINDEX",
"NUMPOINTS","ROTATION_F","SCALEFACTOR","RENDERCULLING","VERTEXORDERING","SHAPETYPE",
"FACETYPE","CREASEANGLE","DROPOFFRATE","CUTOFFANGLE","WHICHCHILD","FILENAME",
"IMAGE","WRAPS","WRAPT","SCALEORIENTATION","NAME","DESCRIPTION","MAP","BBOXSIZE",
"BBOXCENTER","DEF","USE","FIELDS","UNKNOWNNODE","'{'","'}'","'|'","'('","')'",
"','","'['","']'","'~'","vrml","@1","Nodes","Node","@2","NodeBody","FieldSpecs",
"UnknownNode","asciitextfields","asciitextfield","AsciiText","conefields","conefield",
"Cone","@3","coordinatefield","Coordinate3","@4","cubefields","cubefield","Cube",
"@5","cylinderfields","cylinderfield","Cylinder","@6","dlightfields","dlightfield",
"Dlight","@7","fstylefields","fstylefield","FontStyle","Group","ifacesetfields",
"ifacesetfield","IdxFaceSet","@8","ilinesetfields","ilinesetfield","IdxLineSet",
"infofield","Info","lodfields","lodfield","Lod","@9","oldlodfield","LevelOfDetail",
"materialfields","materialfield","Material","@10","mbindingfields","mbindingfield",
"MaterialBinding","@11","mxtransformfields","mxtransformfield","MatrixTransform",
"@12","normalfields","normalfield","Normal","@13","nbindingfields","nbindingfield",
"NormalBinding","@14","ocamerafields","ocamerafield","OrthographicCamera","@15",
"pcamerafields","pcamerafield","PerspectiveCamera","@16","plightfields","plightfield",
"PointLight","@17","psetfields","psetfield","PointSet","rotationfields","rotationfield",
"Rotation","@18","scalefields","scalefield","Scale","@19","separatorfields",
"separatorfield","Separator","@20","shapehintsfields","shapehintsfield","ShapeHints",
"spherefields","spherefield","Sphere","@21","spotlightfields","spotlightfield",
"SpotLight","@22","switchfields","switchfield","Switch","@23","@24","texture2fields",
"texture2field","Texture2","tex2transfields","tex2transfield","Tex2Transform",
"texcoord2fields","texcoord2field","TexCoordinate2","transformfields","transformfield",
"Transform","@25","TransSeparator","@26","translationfields","translationfield",
"Translation","@27","WWWanchorfields","WWWanchorfield","WWWAnchor","WWWinlinefields",
"WWWinlinefield","WWWInline","bitmasklist","SFBitMask","SFBool","SFColor","SFEnum",
"SFFloat","imglist","SFImage","SFLong","SFMatrix","SFRotation","SFString","SFVec2f",
"SFVec3f","colorlist","MFColor","@28","longlist","MFLong","floatlist","MFFloat",
"stringlist","@29","MFString","vec2flist","MFVec2f","vec3flist","MFVec3f",""
};
#endif

static const short yyr1[] = {     0,
   120,   119,   119,   121,   121,   122,   123,   122,   122,   124,
   124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
   124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
   124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
   124,   124,   124,   124,   124,   124,   124,   125,   125,   126,
   127,   127,   128,   128,   128,   128,   129,   130,   130,   131,
   131,   131,   133,   132,   134,   134,   136,   135,   137,   137,
   138,   138,   138,   140,   139,   141,   141,   142,   142,   142,
   144,   143,   145,   145,   146,   146,   146,   146,   148,   147,
   149,   149,   150,   150,   150,   151,   152,   153,   153,   154,
   154,   154,   154,   156,   155,   157,   157,   158,   158,   158,
   158,   159,   160,   160,   161,   162,   162,   163,   163,   165,
   164,   166,   166,   167,   168,   168,   169,   169,   169,   169,
   169,   169,   171,   170,   172,   172,   173,   175,   174,   176,
   176,   177,   179,   178,   180,   180,   181,   183,   182,   184,
   184,   185,   187,   186,   188,   188,   189,   189,   189,   189,
   191,   190,   192,   192,   193,   193,   193,   193,   195,   194,
   196,   196,   197,   197,   197,   197,   199,   198,   200,   200,
   201,   201,   202,   203,   203,   204,   206,   205,   207,   207,
   208,   210,   209,   211,   211,   212,   214,   213,   215,   215,
   216,   216,   216,   216,   217,   218,   218,   219,   221,   220,
   222,   222,   223,   223,   223,   223,   223,   223,   223,   225,
   224,   226,   226,   227,   229,   230,   228,   231,   231,   232,
   232,   232,   232,   233,   234,   234,   235,   235,   235,   235,
   236,   237,   237,   238,   239,   240,   240,   241,   241,   241,
   241,   241,   243,   242,   245,   244,   246,   246,   247,   249,
   248,   250,   250,   251,   251,   251,   252,   253,   253,   254,
   254,   254,   255,   256,   256,   257,   257,   258,   259,   260,
   261,   261,   262,   262,   263,   264,   265,   266,   267,   268,
   269,   270,   270,   270,   272,   271,   271,   271,   273,   273,
   273,   274,   274,   274,   275,   275,   275,   276,   276,   276,
   277,   278,   277,   279,   279,   280,   280,   280,   281,   281,
   282,   282,   282,   283,   283,   283
};

static const short yyr2[] = {     0,
     0,     2,     1,     2,     0,     1,     0,     4,     2,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     0,     1,
     2,     0,     2,     2,     2,     2,     5,     2,     0,     2,
     2,     2,     0,     6,     2,     0,     0,     6,     2,     0,
     2,     2,     2,     0,     6,     2,     0,     2,     2,     2,
     0,     6,     2,     0,     2,     2,     2,     2,     0,     6,
     2,     0,     2,     2,     2,     5,     4,     2,     0,     2,
     2,     2,     2,     0,     6,     2,     0,     2,     2,     2,
     2,     5,     2,     0,     5,     2,     0,     2,     2,     0,
     7,     2,     0,     6,     2,     0,     2,     2,     2,     2,
     2,     2,     0,     6,     2,     0,     2,     0,     6,     2,
     0,     2,     0,     6,     2,     0,     2,     0,     6,     2,
     0,     2,     0,     6,     2,     0,     2,     2,     2,     2,
     0,     6,     2,     0,     2,     2,     2,     2,     0,     6,
     2,     0,     2,     2,     2,     2,     0,     6,     2,     0,
     2,     2,     5,     2,     0,     2,     0,     6,     2,     0,
     2,     0,     6,     2,     0,     2,     0,     7,     2,     0,
     2,     2,     2,     2,     5,     2,     0,     2,     0,     6,
     2,     0,     2,     2,     2,     2,     2,     2,     2,     0,
     6,     2,     0,     2,     0,     0,     8,     2,     0,     2,
     2,     2,     2,     5,     2,     0,     2,     2,     2,     2,
     5,     2,     0,     2,     5,     2,     0,     2,     2,     2,
     2,     2,     0,     6,     0,     6,     2,     0,     2,     0,
     6,     2,     0,     2,     2,     2,     6,     2,     0,     2,
     2,     2,     5,     1,     3,     1,     3,     1,     3,     1,
     1,     1,     2,     0,     4,     1,    16,     4,     1,     2,
     3,     1,     2,     3,     0,     2,     3,     1,     1,     2,
     3,     1,     3,     1,     1,     2,     3,     1,     3,     1,
     1,     0,     4,     1,     3,     1,     2,     3,     1,     3,
     1,     2,     3,     1,     3,     1
};

static const short yydefact[] = {     0,
     3,     5,     0,    63,    67,    74,    81,    89,     0,     0,
   104,     0,     0,     0,   133,   138,     0,   143,   148,   153,
   161,   169,   177,     0,   187,   192,     0,     0,   209,   220,
   225,     0,     0,     0,   253,     0,   260,     0,     0,     0,
     0,    50,     2,     5,     6,    47,    10,    11,    12,    13,
    14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
    24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
    34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
    44,    45,    46,    49,     0,     0,     0,     0,     0,    49,
     5,     0,    49,    49,    49,     0,     0,    49,     0,     0,
     0,     0,     0,     0,    49,     0,     0,    49,    49,     0,
     0,     0,    49,    49,    49,     0,    49,     0,    49,    49,
     7,     9,     4,    48,    52,    49,    49,    49,    49,    49,
    92,     0,    49,   107,   114,   117,    49,    49,   123,    49,
    49,    49,    49,    49,    49,   180,    49,    49,   195,   200,
    49,    49,    49,   229,   236,   243,    49,   255,    49,   263,
   269,     0,     0,     0,     0,     0,     0,    52,    59,    66,
    70,    77,    84,     0,     0,     0,     0,    92,    97,    99,
     0,     0,     0,     0,     0,   107,     0,     0,     0,     0,
   120,   117,   126,   136,     0,     5,   141,   146,   151,   156,
   164,   172,     0,     0,     0,   180,   185,   190,     0,   197,
   195,     0,     0,     0,     0,     0,   200,   207,   212,   223,
     0,     0,     0,     0,     0,   229,     0,     0,     0,     0,
     0,   236,     0,     0,   243,   247,     5,   258,     0,     0,
     0,     5,   263,     0,     0,     0,     0,   269,     8,   282,
   281,     0,   310,   308,    56,   289,     0,   314,    53,    54,
   280,    55,    57,    51,     0,     0,     0,     0,    59,     0,
     0,     0,     0,     0,     0,    70,     0,     0,     0,     0,
    77,     0,     0,     0,     0,     0,    84,    93,    94,   276,
     0,    95,    96,    91,     0,     0,     0,     0,     0,    99,
   286,     0,   304,   302,   108,   109,   110,   111,   112,   106,
   113,   115,   118,     0,   119,     5,   116,   295,   295,   295,
   295,     0,     0,     0,   126,     0,     0,   136,   122,     0,
     0,     0,   141,     0,     0,   146,     0,     0,   151,     0,
     0,     0,     0,     0,   156,     0,     0,     0,     0,     0,
   164,     0,     0,     0,     0,     0,   172,   181,   182,   183,
   179,     0,     0,   185,     0,     0,   190,   196,     5,   194,
   201,   202,   203,   204,   205,   199,     0,     0,   207,     0,
     0,     0,     0,     0,     0,     0,     0,   212,     0,   226,
   223,   230,     0,   231,   232,   233,   234,   228,     0,   237,
   240,   238,   239,   241,   235,     0,   319,   244,   245,   242,
     0,     0,     0,     0,     0,     0,   247,     0,     0,     0,
   258,   264,   265,   266,     0,   262,   270,   271,   272,   273,
   268,   305,     0,   311,     0,    60,    61,    62,    64,    58,
     0,   326,   324,    65,    68,    72,    71,    73,    75,    69,
    78,    80,    79,    82,    76,   278,    85,    86,    87,     0,
    88,    90,    83,   274,     0,   100,   101,   102,   103,   105,
    98,   299,     0,     0,     0,     0,   298,   127,     0,   128,
   129,   130,   131,   132,   134,   125,   137,   139,   135,   124,
     0,   142,   144,   140,   147,   149,   145,   152,   154,   150,
   160,   157,     0,   158,   159,   162,   155,   165,   166,   167,
   168,   170,   163,   173,   174,   175,   176,   178,   171,   186,
   188,   184,   191,   193,   189,     0,   208,   210,   206,   213,
   214,   215,   217,   216,   218,   219,   221,   211,   224,     5,
   222,     0,   290,   316,     0,   248,   252,   249,   250,   251,
   254,   246,   256,   259,   261,   257,   267,   306,   309,     0,
   315,   321,     0,     0,     0,   277,   300,   303,   291,   121,
   292,     0,   296,     0,     0,   198,     0,   284,   317,   320,
   307,     0,   322,   325,   279,   275,   301,   293,   297,     0,
     0,   227,   284,   285,   318,   313,   323,   294,     0,   288,
   283,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   287,     0,     0,     0
};

static const short yydefgoto[] = {   614,
     2,    43,    44,   162,    45,   125,    46,   167,   168,    47,
   268,   269,    48,    85,   271,    49,    86,   275,   276,    50,
    87,   280,   281,    51,    88,   286,   287,    52,    89,   177,
   178,    53,    54,   299,   300,    55,    92,   185,   186,    56,
   188,    57,   191,   192,    58,   316,   196,    59,   324,   325,
    60,    96,   327,   328,    61,    97,   332,   333,    62,    99,
   335,   336,    63,   100,   338,   339,    64,   101,   344,   345,
    65,   102,   350,   351,    66,   103,   356,   357,    67,   104,
   205,   206,    68,   363,   364,    69,   106,   366,   367,    70,
   107,   210,   211,    71,   369,   216,   217,    72,   378,   379,
    73,   110,   387,   388,    74,   111,   390,   391,    75,   112,
   540,   225,   226,    76,   231,   232,    77,   234,   235,    78,
   416,   417,    79,   116,    80,   237,   420,   421,    81,   118,
   242,   243,    82,   247,   248,    83,   465,   292,   457,   571,
   262,   314,   594,   394,   304,   492,   504,   434,   544,   443,
   572,   478,   479,   473,   305,   433,   255,   435,   560,   259,
   545,   408,   563,   444
};

static const short yypact[] = {   489,
-32768,   526,   -61,-32768,-32768,-32768,-32768,-32768,   -56,   -55,
-32768,   -46,   -16,   -12,-32768,-32768,   -11,-32768,-32768,-32768,
-32768,-32768,-32768,    13,-32768,-32768,    16,    25,-32768,-32768,
-32768,    29,    38,    43,-32768,    44,-32768,    52,    56,    80,
   144,-32768,-32768,   526,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,    59,    64,    65,    75,    76,    81,    59,
   526,    87,    59,    59,    59,    89,    91,    59,    92,    94,
    99,   102,   107,   114,    59,   126,   127,    59,    59,   141,
   142,   143,    59,    59,    59,   145,    59,   147,    59,    59,
-32768,-32768,-32768,-32768,    53,    59,    59,    59,    59,    59,
    50,    85,    59,   115,   207,   -23,    59,    59,   158,    59,
    59,    59,    59,    59,    59,   -50,    59,    59,   171,   116,
    59,    59,    59,   117,    -2,   212,    59,-32768,    59,    68,
    45,   628,    22,     1,    78,   257,   151,    53,   174,   215,
    42,    41,   173,    78,   257,     8,   153,    50,-32768,   170,
    12,    12,    12,    12,   154,   115,   260,   156,    22,    78,
-32768,   -23,    86,   193,    22,   526,   194,   192,   197,   -39,
   163,   -18,   270,   270,   164,   -50,   190,   191,   257,-32768,
   171,   257,   257,   257,    78,   166,   116,   225,   -33,   185,
   260,   277,   257,   257,   172,   117,    78,    78,    78,    78,
   175,    -2,     6,   176,   212,   -10,   526,   214,   260,   260,
   257,   526,    68,   260,    78,    78,   177,    45,-32768,-32768,
-32768,    78,-32768,-32768,-32768,-32768,   260,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,     8,    78,    78,   178,   174,    27,
   179,    78,    78,    78,   180,    42,     8,    78,    78,   181,
    41,   281,    78,    78,    78,   182,   173,-32768,-32768,-32768,
   290,-32768,-32768,-32768,    12,    12,    12,    12,   184,   170,
-32768,   270,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,    78,-32768,   526,-32768,     0,     0,     0,
     0,    22,    22,   186,    86,   257,   187,   193,-32768,   188,
    78,   189,   194,    27,   195,   192,   257,   196,   197,    78,
    78,    78,    78,   198,   -39,    78,    78,    78,    78,   199,
   163,   281,    78,    78,    78,   200,   -18,-32768,-32768,-32768,
-32768,    78,   201,   190,    78,   202,   191,-32768,   526,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,    78,   203,   225,   281,
    78,    78,    78,    78,    78,    78,   205,   -33,   270,-32768,
   185,-32768,   292,-32768,-32768,-32768,-32768,-32768,    78,-32768,
-32768,-32768,-32768,-32768,-32768,    78,-32768,-32768,-32768,-32768,
    78,    78,    78,    78,    78,   208,   -10,   210,    78,   211,
   214,-32768,-32768,-32768,   213,-32768,-32768,-32768,-32768,-32768,
-32768,   218,   168,   219,   220,-32768,-32768,-32768,-32768,-32768,
    78,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    78,
-32768,-32768,-32768,-32768,    15,-32768,-32768,-32768,-32768,-32768,
-32768,   221,   222,    78,   224,    78,-32768,-32768,    78,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
    78,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,    78,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   229,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   526,
-32768,   298,-32768,   228,   232,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,    78,-32768,   230,
-32768,   236,   237,    78,   299,-32768,   270,-32768,-32768,-32768,
   240,   239,-32768,    78,    78,-32768,   246,   300,    78,-32768,
-32768,   260,    78,-32768,-32768,-32768,-32768,    78,-32768,    78,
    78,-32768,   300,-32768,-32768,-32768,-32768,-32768,    78,-32768,
-32768,    78,    78,    78,    78,    78,    78,    78,    78,    78,
    78,    78,-32768,   305,   308,-32768
};

static const short yypgoto[] = {-32768,
-32768,   -44,-32768,-32768,   167,   233,-32768,   150,-32768,-32768,
    61,-32768,-32768,-32768,-32768,-32768,-32768,    82,-32768,-32768,
-32768,    83,-32768,-32768,-32768,    95,-32768,-32768,-32768,   209,
-32768,-32768,-32768,    67,-32768,-32768,-32768,   183,-32768,-32768,
-32768,-32768,   204,-32768,-32768,-32768,-32768,-32768,    47,-32768,
-32768,-32768,    40,-32768,-32768,-32768,    46,-32768,-32768,-32768,
    55,-32768,-32768,-32768,    49,-32768,-32768,-32768,    48,-32768,
-32768,-32768,    32,-32768,-32768,-32768,    37,-32768,-32768,-32768,
   206,-32768,-32768,    31,-32768,-32768,-32768,    30,-32768,-32768,
-32768,   216,-32768,-32768,-32768,   217,-32768,-32768,    10,-32768,
-32768,-32768,    14,-32768,-32768,-32768,     7,-32768,-32768,-32768,
-32768,   231,-32768,-32768,   169,-32768,-32768,   165,-32768,-32768,
   -14,-32768,-32768,-32768,-32768,-32768,   -17,-32768,-32768,-32768,
   223,-32768,-32768,   159,-32768,-32768,-32768,  -232,  -323,  -279,
  -161,  -159,  -187,-32768,  -202,-32768,  -334,  -143,   -86,  -173,
  -180,   -71,-32768,  -158,  -164,  -147,  -186,  -169,-32768,-32768,
  -165,-32768,  -166,    84
};


#define	YYLAST		737


static const short yytable[] = {   123,
   358,   359,   313,   254,   459,   260,   256,   340,   329,   250,
   251,   290,   509,   289,   288,   301,   315,   306,   307,   308,
   258,   380,   381,   382,   383,   250,   251,   520,   514,   254,
   250,   251,   436,   203,   204,   254,   352,   353,   354,   341,
   342,   343,   189,   311,   451,   190,   132,   368,    84,   384,
   371,   372,   373,    90,    91,   374,   530,   411,   412,   385,
   386,   395,   396,    93,   355,   227,   228,   399,   399,   402,
   399,   428,   429,   399,   516,   413,   414,   392,   548,   424,
   550,   250,   251,   229,   230,   277,   121,   278,   272,   415,
   273,   274,   432,    94,   279,   422,   423,    95,    98,   472,
   427,   163,   532,   164,   165,   166,   437,   438,   174,   175,
   176,   461,   446,   447,   448,   476,   257,   477,   452,   453,
   291,   406,   105,   458,   460,   108,   565,   302,   566,   303,
   466,   467,   468,   469,   109,   483,   484,   252,   113,   253,
   400,   401,   441,   403,   442,   244,   407,   114,   245,   246,
   122,   330,   115,   117,   474,   318,   319,   320,   321,   322,
   323,   119,   254,   254,   487,   120,   124,   502,   239,   240,
   241,   491,   508,   126,   127,   498,   181,   182,   183,   184,
   501,   517,   503,   505,   128,   129,   539,   503,   510,   511,
   130,   523,   418,   515,   460,   179,   133,   425,   137,   573,
   138,   140,   503,   141,   212,   213,   214,   215,   142,   533,
   534,   143,   221,   222,   223,   224,   144,   527,   265,   266,
   267,   531,   460,   145,   195,   535,   536,   282,   283,   284,
   285,   295,   296,   297,   298,   147,   148,   546,   547,   543,
   549,   346,   347,   348,   349,   554,   399,   480,   481,   482,
   151,   152,   153,   503,   157,   503,   159,   187,   209,   233,
   261,   263,   270,   293,   309,   256,   312,   562,   326,   334,
   331,   475,   337,   301,   360,   362,   375,   365,   377,   389,
   393,   419,   397,   456,   559,   404,   409,   430,   439,   445,
   449,   454,   462,   464,   470,   542,   485,   488,   490,   493,
   564,   578,   586,   593,   615,   496,   499,   616,   506,   512,
   518,   521,   524,   528,   569,   537,   460,   264,   551,   460,
   553,   555,   131,   557,   526,   134,   135,   136,   249,   440,
   139,   574,   558,  -312,   570,   567,   561,   146,   568,   576,
   149,   150,   579,   575,   582,   154,   155,   156,   580,   158,
   583,   160,   161,   584,   588,   589,   592,   450,   169,   170,
   171,   172,   173,   455,   472,   180,   471,   489,   310,   193,
   194,   486,   197,   198,   199,   200,   201,   202,   494,   207,
   208,   463,   513,   218,   219,   220,   294,   500,   529,   236,
   497,   238,   507,   519,   522,   317,   525,   541,   432,   410,
   405,   538,   552,   556,   585,   601,   431,   598,   587,   562,
   581,   361,   596,   595,   590,   591,   597,   495,     0,   399,
     0,     0,     0,     0,     0,     0,   370,     0,   460,     0,
   599,   600,     0,   376,     0,     0,     0,     0,     0,   602,
     0,     0,   603,   604,   605,   606,   607,   608,   609,   610,
   611,   612,   613,     0,     0,     0,   398,     0,     0,     0,
     0,     0,     0,     0,     0,   426,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    -1,     1,
     0,     0,     0,     0,     0,   577,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
    10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
    20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
    30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    -1,    -1,     0,    -1,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    40,    41,     0,    42,     3,     4,     5,     6,     7,
     8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
    18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
    28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
    38,    39,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    42
};

static const short yycheck[] = {    44,
   203,   204,   189,   163,   284,   165,     6,    47,   195,     4,
     5,     4,   347,   175,   174,     4,   190,   182,   183,   184,
   164,    55,    56,    57,    58,     4,     5,   362,   352,   189,
     4,     5,   265,    84,    85,   195,    55,    56,    57,    79,
    80,    81,    66,   187,   277,    69,    91,   209,   110,    83,
   212,   213,   214,   110,   110,   215,   380,    68,    69,    93,
    94,   223,   224,   110,    83,    68,    69,   227,   228,   229,
   230,   245,   246,   233,   354,    86,    87,   221,   413,   241,
   415,     4,     5,    86,    87,    45,     7,    47,    47,   100,
    49,    50,   252,   110,    54,   239,   240,   110,   110,   302,
   244,    49,   382,    51,    52,    53,   266,   267,    59,    60,
    61,   285,   272,   273,   274,   116,   116,   118,   278,   279,
   113,   116,   110,   283,   284,   110,   112,   116,   114,   118,
   295,   296,   297,   298,   110,   322,   323,   116,   110,   118,
   227,   228,   116,   230,   118,   101,   233,   110,   104,   105,
     7,   196,   110,   110,   314,    70,    71,    72,    73,    74,
    75,   110,   322,   323,   326,   110,   108,   341,   101,   102,
   103,   331,   346,   110,   110,   337,    62,    63,    64,    65,
   340,   355,   342,   343,   110,   110,   389,   347,   348,   349,
   110,   365,   237,   353,   354,   111,   110,   242,   110,   479,
   110,   110,   362,   110,    89,    90,    91,    92,   110,   383,
   384,   110,    96,    97,    98,    99,   110,   377,    45,    46,
    47,   381,   382,   110,    67,   385,   386,    55,    56,    57,
    58,    62,    63,    64,    65,   110,   110,   411,   412,   399,
   414,    79,    80,    81,    82,   419,   406,   319,   320,   321,
   110,   110,   110,   413,   110,   415,   110,    51,    88,    48,
     4,   111,    48,   111,   111,     6,   111,   441,    76,    78,
    77,   316,    76,     4,   111,    86,   111,    87,    54,    95,
     4,    68,   111,     3,   117,   111,   111,   111,   111,   111,
   111,   111,   111,     4,   111,     4,   111,   111,   111,   111,
   460,     4,     4,     4,     0,   111,   111,     0,   111,   111,
   111,   111,   111,   111,   474,   111,   476,   168,   111,   479,
   111,   111,    90,   111,   369,    93,    94,    95,   162,   269,
    98,   491,   115,   115,   111,   115,   117,   105,   117,   111,
   108,   109,   115,   503,   115,   113,   114,   115,   117,   117,
   115,   119,   120,   117,   115,   117,   111,   276,   126,   127,
   128,   129,   130,   281,   567,   133,   300,   328,   186,   137,
   138,   325,   140,   141,   142,   143,   144,   145,   333,   147,
   148,   287,   351,   151,   152,   153,   178,   339,   379,   157,
   336,   159,   345,   357,   364,   192,   367,   391,   558,   235,
   232,   388,   417,   421,   564,   593,   248,   588,   567,   583,
   558,   206,   582,   579,   574,   575,   583,   334,    -1,   579,
    -1,    -1,    -1,    -1,    -1,    -1,   211,    -1,   588,    -1,
   590,   591,    -1,   217,    -1,    -1,    -1,    -1,    -1,   599,
    -1,    -1,   602,   603,   604,   605,   606,   607,   608,   609,
   610,   611,   612,    -1,    -1,    -1,   226,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,   243,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     0,     1,
    -1,    -1,    -1,    -1,    -1,   540,     8,     9,    10,    11,
    12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
    22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
    32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
    42,    43,    44,     8,     9,    10,    11,    12,    13,    14,
    15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
    25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
    35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,   106,   107,    -1,   109,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   106,   107,    -1,   109,     8,     9,    10,    11,    12,
    13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
    23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
    33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,   109
};

#line 325 "/usr/local/lib/bison.cc"
 /* fattrs + tables */

/* parser code folow  */


/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: dollar marks section change
   the next  is replaced by the list of actions, each action
   as one case of the switch.  */ 

#if YY_VRMLYacc_USE_GOTO != 0
/* 
 SUPRESSION OF GOTO : on some C++ compiler (sun c++)
  the goto is strictly forbidden if any constructor/destructor
  is used in the whole function (very stupid isn't it ?)
 so goto are to be replaced with a 'while/switch/case construct'
 here are the macro to keep some apparent compatibility
*/
#define YYGOTO(lb) {yy_gotostate=lb;continue;}
#define YYBEGINGOTO  enum yy_labels yy_gotostate=yygotostart; \
                     for(;;) switch(yy_gotostate) { case yygotostart: {
#define YYLABEL(lb) } case lb: {
#define YYENDGOTO } } 
#define YYBEGINDECLARELABEL enum yy_labels {yygotostart
#define YYDECLARELABEL(lb) ,lb
#define YYENDDECLARELABEL  };
#else
/* macro to keep goto */
#define YYGOTO(lb) goto lb
#define YYBEGINGOTO 
#define YYLABEL(lb) lb:
#define YYENDGOTO
#define YYBEGINDECLARELABEL 
#define YYDECLARELABEL(lb)
#define YYENDDECLARELABEL 
#endif
/* LABEL DECLARATION */
YYBEGINDECLARELABEL
  YYDECLARELABEL(yynewstate)
  YYDECLARELABEL(yybackup)
/* YYDECLARELABEL(yyresume) */
  YYDECLARELABEL(yydefault)
  YYDECLARELABEL(yyreduce)
  YYDECLARELABEL(yyerrlab)   /* here on detecting error */
  YYDECLARELABEL(yyerrlab1)   /* here on error raised explicitly by an action */
  YYDECLARELABEL(yyerrdefault)  /* current state does not do anything special for the error token. */
  YYDECLARELABEL(yyerrpop)   /* pop the current state because it cannot handle the error token */
  YYDECLARELABEL(yyerrhandle)  
YYENDDECLARELABEL
/* ALLOCA SIMULATION */
/* __HAVE_NO_ALLOCA */
#ifdef __HAVE_NO_ALLOCA
int __alloca_free_ptr(char *ptr,char *ref);
//{if(ptr!=ref) free(ptr);
// return 0;}

#define __ALLOCA_alloca(size) malloc(size)
#define __ALLOCA_free(ptr,ref) __alloca_free_ptr((char *)ptr,(char *)ref)

#ifdef YY_VRMLYacc_LSP_NEEDED
#define __ALLOCA_return(num) \
            return( __ALLOCA_free(yyss,yyssa)+\
		    __ALLOCA_free(yyvs,yyvsa)+\
		    __ALLOCA_free(yyls,yylsa)+\
		   (num))
#else
#define __ALLOCA_return(num) \
            return( __ALLOCA_free(yyss,yyssa)+\
		    __ALLOCA_free(yyvs,yyvsa)+\
		   (num))
#endif
#else
#define __ALLOCA_return(num) return(num)
#define __ALLOCA_alloca(size) alloca(size)
#define __ALLOCA_free(ptr,ref) 
#endif

/* ENDALLOCA SIMULATION */

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (YY_VRMLYacc_CHAR = YYEMPTY)
#define YYEMPTY         -2
#define YYEOF           0
#define YYACCEPT        __ALLOCA_return(0)
#define YYABORT         __ALLOCA_return(1)
#define YYERROR         YYGOTO(yyerrlab1)
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL          YYGOTO(yyerrlab)
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do                                                              \
  if (YY_VRMLYacc_CHAR == YYEMPTY && yylen == 1)                               \
    { YY_VRMLYacc_CHAR = (token), YY_VRMLYacc_LVAL = (value);                 \
      yychar1 = YYTRANSLATE (YY_VRMLYacc_CHAR);                                \
      YYPOPSTACK;                                               \
      YYGOTO(yybackup);                                            \
    }                                                           \
  else                                                          \
    { YY_VRMLYacc_ERROR ("syntax error: cannot back up"); YYERROR; }   \
while (0)

#define YYTERROR        1
#define YYERRCODE       256

#ifndef YY_VRMLYacc_PURE
/* UNPURE */
#define YYLEX           YY_VRMLYacc_LEX()
#ifndef YY_USE_CLASS
/* If nonreentrant, and not class , generate the variables here */
int     YY_VRMLYacc_CHAR;                      /*  the lookahead symbol        */
YY_VRMLYacc_STYPE      YY_VRMLYacc_LVAL;              /*  the semantic value of the */
				/*  lookahead symbol    */
int YY_VRMLYacc_NERRS;                 /*  number of parse errors so far */
#ifdef YY_VRMLYacc_LSP_NEEDED
YY_VRMLYacc_LTYPE YY_VRMLYacc_LLOC;   /*  location data for the lookahead     */
			/*  symbol                              */
#endif
#endif


#else
/* PURE */
#ifdef YY_VRMLYacc_LSP_NEEDED
#define YYLEX           YY_VRMLYacc_LEX(&YY_VRMLYacc_LVAL, &YY_VRMLYacc_LLOC)
#else
#define YYLEX           YY_VRMLYacc_LEX(&YY_VRMLYacc_LVAL)
#endif
#endif
#ifndef YY_USE_CLASS
#if YY_VRMLYacc_DEBUG != 0
int YY_VRMLYacc_DEBUG_FLAG;                    /*  nonzero means print parse trace     */
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif
#endif



/*  YYINITDEPTH indicates the initial size of the parser's stacks       */

#ifndef YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif


#if __GNUC__ > 1                /* GNU C and GNU C++ define this.  */
#define __yy_bcopy(FROM,TO,COUNT)       __builtin_memcpy(TO,FROM,COUNT)
#else                           /* not GNU C or C++ */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */

#ifdef __cplusplus
static void __yy_bcopy (char *from, char *to, int count)
#else
#ifdef __STDC__
static void __yy_bcopy (char *from, char *to, int count)
#else
static void __yy_bcopy (from, to, count)
     char *from;
     char *to;
     int count;
#endif
#endif
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}
#endif

int
#ifdef YY_USE_CLASS
 YY_VRMLYacc_CLASS::
#endif
     YY_VRMLYacc_PARSE(YY_VRMLYacc_PARSE_PARAM)
#ifndef __STDC__
#ifndef __cplusplus
#ifndef YY_USE_CLASS
/* parameter definition without protypes */
YY_VRMLYacc_PARSE_PARAM_DEF
#endif
#endif
#endif
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YY_VRMLYacc_STYPE *yyvsp;
  int yyerrstatus;      /*  number of tokens to shift before error messages enabled */
  int yychar1=0;          /*  lookahead token as an internal (translated) token number */

  short yyssa[YYINITDEPTH];     /*  the state stack                     */
  YY_VRMLYacc_STYPE yyvsa[YYINITDEPTH];        /*  the semantic value stack            */

  short *yyss = yyssa;          /*  refer to the stacks thru separate pointers */
  YY_VRMLYacc_STYPE *yyvs = yyvsa;     /*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YY_VRMLYacc_LSP_NEEDED
  YY_VRMLYacc_LTYPE yylsa[YYINITDEPTH];        /*  the location stack                  */
  YY_VRMLYacc_LTYPE *yyls = yylsa;
  YY_VRMLYacc_LTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YY_VRMLYacc_PURE
  int YY_VRMLYacc_CHAR;
  YY_VRMLYacc_STYPE YY_VRMLYacc_LVAL;
  int YY_VRMLYacc_NERRS;
#ifdef YY_VRMLYacc_LSP_NEEDED
  YY_VRMLYacc_LTYPE YY_VRMLYacc_LLOC;
#endif
#endif

  YY_VRMLYacc_STYPE yyval;             /*  the variable used to return         */
				/*  semantic values from the action     */
				/*  routines                            */

  int yylen;
/* start loop, in which YYGOTO may be used. */
YYBEGINGOTO

#if YY_VRMLYacc_DEBUG != 0
  if (YY_VRMLYacc_DEBUG_FLAG)
    fprintf(stderr, "Starting parse\n");
#endif
  yystate = 0;
  yyerrstatus = 0;
  YY_VRMLYacc_NERRS = 0;
  YY_VRMLYacc_CHAR = YYEMPTY;          /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YY_VRMLYacc_LSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
YYLABEL(yynewstate)

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YY_VRMLYacc_STYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YY_VRMLYacc_LSP_NEEDED
      YY_VRMLYacc_LTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YY_VRMLYacc_LSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YY_VRMLYacc_LSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  YY_VRMLYacc_ERROR("parser stack overflow");
	  __ALLOCA_return(2);
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) __ALLOCA_alloca (yystacksize * sizeof (*yyssp));
      __yy_bcopy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      __ALLOCA_free(yyss1,yyssa);
      yyvs = (YY_VRMLYacc_STYPE *) __ALLOCA_alloca (yystacksize * sizeof (*yyvsp));
      __yy_bcopy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
      __ALLOCA_free(yyvs1,yyvsa);
#ifdef YY_VRMLYacc_LSP_NEEDED
      yyls = (YY_VRMLYacc_LTYPE *) __ALLOCA_alloca (yystacksize * sizeof (*yylsp));
      __yy_bcopy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
      __ALLOCA_free(yyls1,yylsa);
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YY_VRMLYacc_LSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YY_VRMLYacc_DEBUG != 0
      if (YY_VRMLYacc_DEBUG_FLAG)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YY_VRMLYacc_DEBUG != 0
  if (YY_VRMLYacc_DEBUG_FLAG)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  YYGOTO(yybackup);
YYLABEL(yybackup)

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* YYLABEL(yyresume) */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    YYGOTO(yydefault);

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (YY_VRMLYacc_CHAR == YYEMPTY)
    {
#if YY_VRMLYacc_DEBUG != 0
      if (YY_VRMLYacc_DEBUG_FLAG)
	fprintf(stderr, "Reading a token: ");
#endif
      YY_VRMLYacc_CHAR = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (YY_VRMLYacc_CHAR <= 0)           /* This means end of input. */
    {
      yychar1 = 0;
      YY_VRMLYacc_CHAR = YYEOF;                /* Don't call YYLEX any more */

#if YY_VRMLYacc_DEBUG != 0
      if (YY_VRMLYacc_DEBUG_FLAG)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(YY_VRMLYacc_CHAR);

#if YY_VRMLYacc_DEBUG != 0
      if (YY_VRMLYacc_DEBUG_FLAG)
	{
	  fprintf (stderr, "Next token is %d (%s", YY_VRMLYacc_CHAR, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, YY_VRMLYacc_CHAR, YY_VRMLYacc_LVAL);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    YYGOTO(yydefault);

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	YYGOTO(yyerrlab);
      yyn = -yyn;
      YYGOTO(yyreduce);
    }
  else if (yyn == 0)
    YYGOTO(yyerrlab);

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YY_VRMLYacc_DEBUG != 0
  if (YY_VRMLYacc_DEBUG_FLAG)
    fprintf(stderr, "Shifting token %d (%s), ", YY_VRMLYacc_CHAR, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (YY_VRMLYacc_CHAR != YYEOF)
    YY_VRMLYacc_CHAR = YYEMPTY;

  *++yyvsp = YY_VRMLYacc_LVAL;
#ifdef YY_VRMLYacc_LSP_NEEDED
  *++yylsp = YY_VRMLYacc_LLOC;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  YYGOTO(yynewstate);

/* Do the default action for the current state.  */
YYLABEL(yydefault)

  yyn = yydefact[yystate];
  if (yyn == 0)
    YYGOTO(yyerrlab);

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
YYLABEL(yyreduce)
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YY_VRMLYacc_DEBUG != 0
  if (YY_VRMLYacc_DEBUG_FLAG)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


/* #line 811 "/usr/local/lib/bison.cc" */
#line 2070 "VRMLYacc.C"

  switch (yyn) {

case 1:
#line 197 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ //
                            // make the first status and push onto state stack 
			    //
                            VRMLState *state = new VRMLState(); myStateStack.push(state);
			    myHasLight = false; 
			    myHasCamera = false;
                          ;
    break;}
case 2:
#line 205 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
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
                          ;
    break;}
case 3:
#line 251 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{YYABORT;;
    break;}
case 7:
#line 260 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ //
			    // start definition 
			    //
			    begDef(RCString(yyvsp[0].stringval)); 
			  ;
    break;}
case 8:
#line 266 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ //
			    // end definition 
			    //
			    endDef(RCString(yyvsp[-2].stringval)); 
			  ;
    break;}
case 9:
#line 272 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ //
			    // use definition 
			    //
			    
			    useDef(RCString(yyvsp[0].stringval)); 
			  ;
    break;}
case 57:
#line 341 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    Report::warning("AsciiText node ignored");
			  ;
    break;}
case 60:
#line 352 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{			    
			    myCone.setParts(yyvsp[0].ulongval); 
			  ;
    break;}
case 61:
#line 356 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myCone.setBottomRadius(yyvsp[0].doubleval); 
			  ;
    break;}
case 62:
#line 360 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ 
			    myCone.setHeight(yyvsp[0].doubleval); 
			  ;
    break;}
case 63:
#line 366 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myCone.reset(); 
			  ;
    break;}
case 64:
#line 370 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ 
			    myCone.apply(myStateStack); 
			    objDef(myCone);
			  ;
    break;}
case 65:
#line 378 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ 
			    myCoordinate3.setPoint(*yyvsp[0].vectorlist); 
			    delete yyvsp[0].vectorlist; 
			  ;
    break;}
case 67:
#line 386 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myCoordinate3.reset(); 
			  ;
    break;}
case 68:
#line 390 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ 
			    myCoordinate3.apply(myStateStack); 
    			    objDef(myCoordinate3);
			  ;
    break;}
case 71:
#line 402 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ 
			    myCube.setWidth(yyvsp[0].doubleval); 
			  ;
    break;}
case 72:
#line 406 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myCube.setHeight(yyvsp[0].doubleval); 
			  ;
    break;}
case 73:
#line 410 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ 
			    myCube.setDepth(yyvsp[0].doubleval); 
			  ;
    break;}
case 74:
#line 416 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ 
			    myCube.reset(); 
			  ;
    break;}
case 75:
#line 420 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myCube.apply(myStateStack); 
			    objDef(myCube);
			  ;
    break;}
case 78:
#line 433 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ 
			    myCylinder.setParts(yyvsp[0].ulongval); 
			  ;
    break;}
case 79:
#line 437 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myCylinder.setRadius(yyvsp[0].doubleval); 
			  ;
    break;}
case 80:
#line 441 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myCylinder.setHeight(yyvsp[0].doubleval); 
			  ;
    break;}
case 81:
#line 447 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myCylinder.reset(); 
			  ;
    break;}
case 82:
#line 451 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myCylinder.apply(myStateStack);
			    objDef(myCylinder);
			  ;
    break;}
case 85:
#line 463 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myDirectionalLight.setOn(yyvsp[0].boolval); 
			  ;
    break;}
case 86:
#line 467 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ 
			    myDirectionalLight.setIntensity(yyvsp[0].doubleval); 
			  ;
    break;}
case 87:
#line 471 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myDirectionalLight.setColor(*yyvsp[0].colorval); 
			    delete yyvsp[0].colorval; 
			  ;
    break;}
case 88:
#line 476 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myDirectionalLight.setDirection(*yyvsp[0].vectorval); 
			    delete yyvsp[0].vectorval; 
			  ;
    break;}
case 89:
#line 483 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    Report::warning("DirectionalLight node simulated with point light at 100000 * -direction");
			    myDirectionalLight.reset(); 
			  ;
    break;}
case 90:
#line 488 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    //
			    // since the default camera position is calculated with
			    // bounding boxes, we collect the directional lights
			    // and apply them after the default camera is inserted
			    // 
			    myHasLight |= myDirectionalLight.getOn();
			    myDirectionalLight.apply(myStateStack);
			    objDef(myDirectionalLight);
			  ;
    break;}
case 96:
#line 511 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    Report::warning("FontStyle node ignored");
			  ;
    break;}
case 100:
#line 526 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myIndexedFaceSet.setCoordIndex(*yyvsp[0].longlist); 
			    delete yyvsp[0].longlist; 
			  ;
    break;}
case 101:
#line 531 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myIndexedFaceSet.setMaterialIndex(*yyvsp[0].longlist); 
			    delete yyvsp[0].longlist; 
			  ;
    break;}
case 102:
#line 536 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myIndexedFaceSet.setNormalIndex(*yyvsp[0].longlist); 
			    delete yyvsp[0].longlist; 
			  ;
    break;}
case 103:
#line 541 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    delete yyvsp[0].longlist; 
			  ;
    break;}
case 104:
#line 547 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ 
			    myIndexedFaceSet.reset() 
			  ;
    break;}
case 105:
#line 551 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myIndexedFaceSet.apply(myStateStack); 
			    objDef(myIndexedFaceSet);
			  ;
    break;}
case 108:
#line 563 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    delete yyvsp[0].longlist; 
			  ;
    break;}
case 109:
#line 567 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    delete yyvsp[0].longlist; 
			  ;
    break;}
case 110:
#line 571 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    delete yyvsp[0].longlist; 
			  ;
    break;}
case 111:
#line 575 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    delete yyvsp[0].longlist; 
			  ;
    break;}
case 112:
#line 581 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    Report::warning("IndexedLineSet node ignored");
			  ;
    break;}
case 113:
#line 588 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    delete yyvsp[0].stringval; 
			  ;
    break;}
case 115:
#line 595 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    Report::warning("Info node ignored");
			  ;
    break;}
case 119:
#line 609 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    delete yyvsp[0].vectorval; 
			  ;
    break;}
case 120:
#line 615 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ 
			    Report::warning("LOD node, only highest level of detail child taken");
			    myLODStart.apply(myStateStack); 
			    objDef(myLODStart);
			  ;
    break;}
case 121:
#line 621 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myLODStop.apply(myStateStack); 
			    objDef(myLODStop);
			  ;
    break;}
case 124:
#line 632 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    Report::warning("LevelOfDetail node ignored");
			  ;
    break;}
case 127:
#line 643 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myMaterial.setAmbientColor(*yyvsp[0].colorlist); 
			    delete yyvsp[0].colorlist; 
			  ;
    break;}
case 128:
#line 648 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myMaterial.setDiffuseColor(*yyvsp[0].colorlist); 
			    delete yyvsp[0].colorlist; 
			  ;
    break;}
case 129:
#line 653 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myMaterial.setSpecularColor(*yyvsp[0].colorlist); 
			    delete yyvsp[0].colorlist; 
			  ;
    break;}
case 130:
#line 658 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    Report::warning("Material node, field emissiveColor ignored");
			    delete yyvsp[0].colorlist; 
			  ;
    break;}
case 131:
#line 663 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    Report::warning("Material node, field shininess ignored");
			    delete yyvsp[0].doublelist; 
			  ;
    break;}
case 132:
#line 668 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    Report::warning("Material node, field transparency ignored");
			    delete yyvsp[0].doublelist; 
			  ;
    break;}
case 133:
#line 675 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myMaterial.reset(); 
			  ;
    break;}
case 134:
#line 679 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myMaterial.apply(myStateStack); 
			    objDef(myMaterial);
			  ;
    break;}
case 137:
#line 691 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    if (yyvsp[0].enumval == VRML_PER_VERTEX)
			      Report::warning("MaterialBinding node, PER_VERTEX binding not supported");
                            if (yyvsp[0].enumval == VRML_PER_VERTEX_INDEXED)
			      Report::warning("MaterialBinding node, PER_VERTEX_INDEXED binding not supported");
			    myMaterialBinding.setValue(yyvsp[0].enumval); 
			  ;
    break;}
case 138:
#line 701 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myMaterialBinding.reset(); 
			  ;
    break;}
case 139:
#line 705 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myMaterialBinding.apply(myStateStack); 
			    objDef(myMaterialBinding);
			  ;
    break;}
case 142:
#line 717 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myMatrixTransform.setMatrix(*yyvsp[0].transval); 
			    delete yyvsp[0].transval; 
			  ;
    break;}
case 143:
#line 724 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myMatrixTransform.reset(); 
			  ;
    break;}
case 144:
#line 728 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myMatrixTransform.apply(myStateStack);
			    objDef(myMatrixTransform);
			  ;
    break;}
case 147:
#line 740 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ 
			    myNormal.setVector(*yyvsp[0].vectorlist); 
			    delete yyvsp[0].vectorlist; 
			  ;
    break;}
case 148:
#line 747 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    Report::warning("Normal node ignored");
			    myNormal.reset(); 
			  ;
    break;}
case 149:
#line 752 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myNormal.apply(myStateStack); 
			    objDef(myNormal);
			  ;
    break;}
case 152:
#line 764 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myNormalBinding.setValue(yyvsp[0].enumval); 
			  ;
    break;}
case 153:
#line 770 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    Report::warning("NormalBinding node ignored");
			    myNormalBinding.reset(); 
			  ;
    break;}
case 154:
#line 775 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myNormalBinding.apply(myStateStack); 
			    objDef(myNormalBinding);
			  ;
    break;}
case 157:
#line 787 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myOrthographicCamera.setPosition(*yyvsp[0].vectorval); 
			    delete yyvsp[0].vectorval; 
			  ;
    break;}
case 158:
#line 792 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myOrthographicCamera.setOrientation(*yyvsp[0].transval); 
			    delete yyvsp[0].transval; 
			  ;
    break;}
case 159:
#line 797 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myOrthographicCamera.setFocalDistance(yyvsp[0].doubleval); 
			  ;
    break;}
case 160:
#line 801 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myOrthographicCamera.setHeight(yyvsp[0].doubleval); 
			  ;
    break;}
case 161:
#line 807 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myOrthographicCamera.reset(); 
			  ;
    break;}
case 162:
#line 811 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myHasCamera = true;
			    myOrthographicCamera.apply(myStateStack); 
			    objDef(myOrthographicCamera);
			  ;
    break;}
case 165:
#line 824 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myPerspectiveCamera.setPosition(*yyvsp[0].vectorval); 
			    delete yyvsp[0].vectorval; 
			  ;
    break;}
case 166:
#line 829 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myPerspectiveCamera.setOrientation(*yyvsp[0].transval); 
			    delete yyvsp[0].transval; 
			  ;
    break;}
case 167:
#line 834 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myPerspectiveCamera.setFocalDistance(yyvsp[0].doubleval); 
			  ;
    break;}
case 168:
#line 838 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myPerspectiveCamera.setHeightAngle(yyvsp[0].doubleval); 
			  ;
    break;}
case 169:
#line 844 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myPerspectiveCamera.reset(); 
			  ;
    break;}
case 170:
#line 848 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myHasCamera = true;
			    myPerspectiveCamera.apply(myStateStack); 
			    objDef(myPerspectiveCamera);
			  ;
    break;}
case 173:
#line 861 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myPointLight.setOn(yyvsp[0].boolval); 
			  ;
    break;}
case 174:
#line 865 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myPointLight.setIntensity(yyvsp[0].doubleval); 
			  ;
    break;}
case 175:
#line 869 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myPointLight.setColor(*yyvsp[0].colorval); 
			    delete yyvsp[0].colorval; 
			  ;
    break;}
case 176:
#line 874 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myPointLight.setLocation(*yyvsp[0].vectorval); 
			    delete yyvsp[0].vectorval; 
			  ;
    break;}
case 177:
#line 880 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ myPointLight.reset() ;
    break;}
case 178:
#line 882 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myHasLight |= myPointLight.getOn();
			    myPointLight.apply(myStateStack);
			    objDef(myPointLight);
			  ;
    break;}
case 183:
#line 899 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    Report::warning("PointSet node ignored");
			  ;
    break;}
case 186:
#line 910 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myRotation.setRotation(*yyvsp[0].transval); 
			    delete yyvsp[0].transval; 
			  ;
    break;}
case 187:
#line 917 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myRotation.reset(); 
			  ;
    break;}
case 188:
#line 921 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myRotation.apply(myStateStack);
			    objDef(myRotation);
			  ;
    break;}
case 191:
#line 933 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myScale.setScaleFactor(*yyvsp[0].vectorval); 
			    delete yyvsp[0].vectorval; 
			  ;
    break;}
case 192:
#line 940 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myScale.reset(); 
			  ;
    break;}
case 193:
#line 944 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myScale.apply(myStateStack); 
			    objDef(myScale);
			  ;
    break;}
case 197:
#line 959 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    mySeparatorStart.apply(myStateStack);
			    objDef(mySeparatorStart);
			  ;
    break;}
case 198:
#line 964 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    mySeparatorStop.apply(myStateStack);
			    objDef(mySeparatorStop);
			  ;
    break;}
case 205:
#line 982 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    Report::warning("ShapeHints node ignored");
			  ;
    break;}
case 208:
#line 993 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    mySphere.setRadius(yyvsp[0].doubleval); 
			  ;
    break;}
case 209:
#line 998 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ mySphere.reset(); ;
    break;}
case 210:
#line 1000 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    mySphere.apply(myStateStack); 
			    objDef(mySphere);
			  ;
    break;}
case 213:
#line 1012 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    mySpotLight.setOn(yyvsp[0].boolval); 
			  ;
    break;}
case 214:
#line 1016 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    mySpotLight.setIntensity(yyvsp[0].doubleval); 
			  ;
    break;}
case 215:
#line 1020 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    mySpotLight.setColor(*yyvsp[0].colorval); 
			    delete yyvsp[0].colorval; 
			  ;
    break;}
case 216:
#line 1025 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    mySpotLight.setLocation(*yyvsp[0].vectorval); 
			    delete yyvsp[0].vectorval; 
			  ;
    break;}
case 217:
#line 1030 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    mySpotLight.setDirection(*yyvsp[0].vectorval); 
			    delete yyvsp[0].vectorval; 
			  ;
    break;}
case 218:
#line 1035 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    Report::warning("SpotLight node, field dropOffRate ignored");
			  ;
    break;}
case 219:
#line 1039 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    Report::warning("SpotLight node, field cutOffAngle ignored");
			  ;
    break;}
case 220:
#line 1045 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    Report::warning("SpotLight node simulated with point light");
			    mySpotLight.reset(); 
			  ;
    break;}
case 221:
#line 1050 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myHasLight |= mySpotLight.getOn();
			    mySpotLight.apply(myStateStack);
			    objDef(mySpotLight);
			  ;
    break;}
case 224:
#line 1063 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    mySwitchStart.setWhichChild(yyvsp[0].longval); 
			  ;
    break;}
case 225:
#line 1068 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ mySwitchStart.reset(); ;
    break;}
case 226:
#line 1070 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    mySwitchStart.apply(myStateStack); 
			    objDef(mySwitchStart);
			  ;
    break;}
case 227:
#line 1075 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    mySwitchStop.apply(myStateStack); 
			    objDef(mySwitchStop);
			  ;
    break;}
case 230:
#line 1087 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    delete yyvsp[0].stringval; 
			  ;
    break;}
case 234:
#line 1096 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    Report::warning("Texture2 node ignored");
			  ;
    break;}
case 241:
#line 1113 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    Report::warning("Texture2Transform node ignored");
			  ;
    break;}
case 245:
#line 1127 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    Report::warning("TextureCoordinate2 node ignored");
			  ;
    break;}
case 248:
#line 1138 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myTransform.setTranslation(*yyvsp[0].vectorval); 
			    delete yyvsp[0].vectorval; 
			  ;
    break;}
case 249:
#line 1143 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myTransform.setRotation(*yyvsp[0].transval); 
			    delete yyvsp[0].transval; 
			  ;
    break;}
case 250:
#line 1148 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myTransform.setScaleFactor(*yyvsp[0].vectorval); 
			    delete yyvsp[0].vectorval; 
			  ;
    break;}
case 251:
#line 1153 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myTransform.setScaleOrientation(*yyvsp[0].transval); 
			    delete yyvsp[0].transval; 
			  ;
    break;}
case 252:
#line 1158 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myTransform.setCenter(*yyvsp[0].vectorval); 
			    delete yyvsp[0].vectorval; 
			  ;
    break;}
case 253:
#line 1164 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ myTransform.reset(); ;
    break;}
case 254:
#line 1166 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myTransform.apply(myStateStack); 
			    objDef(myTransform);
			  ;
    break;}
case 255:
#line 1174 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myTransSeparatorStart.apply(myStateStack); 
			    objDef(myTransSeparatorStart);
			  ;
    break;}
case 256:
#line 1179 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myTransSeparatorStop.apply(myStateStack); 
			    objDef(myTransSeparatorStop);
			  ;
    break;}
case 259:
#line 1191 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    myTranslation.setTranslation(*yyvsp[0].vectorval); 
			    delete yyvsp[0].vectorval; 
			  ;
    break;}
case 260:
#line 1197 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ myTranslation.reset(); ;
    break;}
case 261:
#line 1199 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ 
			    myTranslation.apply(myStateStack);
			    objDef(myTranslation);
			  ;
    break;}
case 264:
#line 1211 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    delete yyvsp[0].stringval; 
			  ;
    break;}
case 265:
#line 1215 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    delete yyvsp[0].stringval; 
			  ;
    break;}
case 267:
#line 1222 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    Report::warning("WWWAnchor node ignored");
			  ;
    break;}
case 270:
#line 1233 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    delete yyvsp[0].stringval; 
			  ;
    break;}
case 271:
#line 1237 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    delete yyvsp[0].vectorval; 
			  ;
    break;}
case 272:
#line 1241 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    delete yyvsp[0].vectorval; 
			  ;
    break;}
case 273:
#line 1247 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{
			    Report::warning("WWWInline node ignored");
			  ;
    break;}
case 274:
#line 1257 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.ulongval = yyvsp[2].ulongval; ;
    break;}
case 275:
#line 1258 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.ulongval = (yyvsp[-2].ulongval | yyvsp[0].ulongval);;
    break;}
case 276:
#line 1261 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{yyval.ulongval = (unsigned long)yyvsp[0].longval;;
    break;}
case 277:
#line 1262 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{yyval.ulongval = (unsigned long)yyvsp[-1].ulongval;;
    break;}
case 279:
#line 1268 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.colorval = new Color(yyvsp[-2].doubleval,yyvsp[-1].doubleval,yyvsp[0].doubleval); ;
    break;}
case 280:
#line 1271 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{yyval.enumval = (VRML_binding_t)yyvsp[0].longval;;
    break;}
case 281:
#line 1274 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.doubleval = (double)yyvsp[0].doubleval; ;
    break;}
case 282:
#line 1275 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.doubleval = (double)yyvsp[0].longval; ;
    break;}
case 283:
#line 1278 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{;
    break;}
case 285:
#line 1282 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{;
    break;}
case 287:
#line 1292 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ 
                            yyval.transval = new TransMatrix3D(Vector3D(yyvsp[-15].doubleval,yyvsp[-14].doubleval,yyvsp[-13].doubleval),
                                                   Vector3D(yyvsp[-11].doubleval,yyvsp[-10].doubleval,yyvsp[-9].doubleval),
                                                   Vector3D(yyvsp[-7].doubleval,yyvsp[-6].doubleval,yyvsp[-5].doubleval), 
                                                   Vector3D(yyvsp[-3].doubleval,yyvsp[-2].doubleval,yyvsp[-1].doubleval)); 
                            if (!equal(yyvsp[-12].doubleval, 0) || !equal(yyvsp[-8].doubleval, 0) || !equal(yyvsp[-4].doubleval, 0) || !equal(yyvsp[0].doubleval,1))
                              Report::warning("MatrixTransform node, last column set to [ 0 0 0 1 ]");
                          ;
    break;}
case 288:
#line 1303 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.transval = new TransMatrix3D(TransMatrix3D::makeRotate(Vector3D(yyvsp[-3].doubleval,yyvsp[-2].doubleval,yyvsp[-1].doubleval),yyvsp[0].doubleval)); ;
    break;}
case 290:
#line 1309 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{;
    break;}
case 291:
#line 1312 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.vectorval = new Vector3D(yyvsp[-2].doubleval,yyvsp[-1].doubleval,yyvsp[0].doubleval); ;
    break;}
case 292:
#line 1316 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.colorlist = new List<Color>; yyval.colorlist->append(*yyvsp[0].colorval); delete yyvsp[0].colorval; ;
    break;}
case 293:
#line 1317 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.colorlist = new List<Color>; yyval.colorlist->append(*yyvsp[-1].colorval); delete yyvsp[-1].colorval; ;
    break;}
case 294:
#line 1318 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.colorlist = yyvsp[0].colorlist; yyval.colorlist->prepend(*yyvsp[-2].colorval); delete yyvsp[-2].colorval; ;
    break;}
case 295:
#line 1321 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.colorlist = new List<Color>; ;
    break;}
case 296:
#line 1321 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.colorlist->append(*yyvsp[0].colorval); delete yyvsp[0].colorval; ;
    break;}
case 297:
#line 1322 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.colorlist = yyvsp[-1].colorlist; ;
    break;}
case 298:
#line 1323 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.colorlist = new List<Color>; ;
    break;}
case 299:
#line 1326 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.longlist = new List<long>; yyval.longlist->append(yyvsp[0].longval); ;
    break;}
case 300:
#line 1327 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.longlist = new List<long>; yyval.longlist->append(yyvsp[-1].longval); ;
    break;}
case 301:
#line 1328 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.longlist = yyvsp[0].longlist; yyval.longlist->prepend(yyvsp[-2].longval); ;
    break;}
case 302:
#line 1331 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.longlist = new List<long>; yyval.longlist->append(yyvsp[0].longval); ;
    break;}
case 303:
#line 1332 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.longlist = yyvsp[-1].longlist; ;
    break;}
case 304:
#line 1333 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.longlist = new List<long>; ;
    break;}
case 305:
#line 1336 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.doublelist = new List<double>; yyval.doublelist->append(yyvsp[0].doubleval); ;
    break;}
case 306:
#line 1337 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.doublelist = new List<double>; yyval.doublelist->append(yyvsp[-1].doubleval); ;
    break;}
case 307:
#line 1338 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.doublelist = yyvsp[0].doublelist; yyval.doublelist->prepend(yyvsp[-2].doubleval); ;
    break;}
case 308:
#line 1341 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.doublelist = new List<double>; yyval.doublelist->append(yyvsp[0].doubleval); ;
    break;}
case 309:
#line 1342 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.doublelist = yyvsp[-1].doublelist; ;
    break;}
case 310:
#line 1343 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.doublelist = new List<double>; ;
    break;}
case 311:
#line 1346 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ delete yyvsp[0].stringval; ;
    break;}
case 312:
#line 1347 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ delete yyvsp[0].stringval; ;
    break;}
case 314:
#line 1350 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ delete yyvsp[0].stringval; ;
    break;}
case 315:
#line 1351 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{;
    break;}
case 321:
#line 1363 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.vectorlist = new List<Vector3D>; yyval.vectorlist->append(*yyvsp[0].vectorval); delete yyvsp[0].vectorval; ;
    break;}
case 322:
#line 1364 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.vectorlist = new List<Vector3D>; yyval.vectorlist->append(*yyvsp[-1].vectorval); delete yyvsp[-1].vectorval; ;
    break;}
case 323:
#line 1365 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.vectorlist = yyvsp[0].vectorlist; yyval.vectorlist->prepend(*yyvsp[-2].vectorval); delete yyvsp[-2].vectorval; ;
    break;}
case 324:
#line 1368 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.vectorlist = new List<Vector3D>; yyval.vectorlist->append(*yyvsp[0].vectorval); delete yyvsp[0].vectorval; ;
    break;}
case 325:
#line 1369 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.vectorlist = yyvsp[-1].vectorlist; ;
    break;}
case 326:
#line 1370 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"
{ yyval.vectorlist = new List<Vector3D>; ;
    break;}
}

#line 811 "/usr/local/lib/bison.cc"
   /* the action file gets copied in in place of this dollarsign  */
  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YY_VRMLYacc_LSP_NEEDED
  yylsp -= yylen;
#endif

#if YY_VRMLYacc_DEBUG != 0
  if (YY_VRMLYacc_DEBUG_FLAG)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YY_VRMLYacc_LSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = YY_VRMLYacc_LLOC.first_line;
      yylsp->first_column = YY_VRMLYacc_LLOC.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  YYGOTO(yynewstate);

YYLABEL(yyerrlab)   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++YY_VRMLYacc_NERRS;

#ifdef YY_VRMLYacc_ERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      YY_VRMLYacc_ERROR(msg);
	      free(msg);
	    }
	  else
	    YY_VRMLYacc_ERROR ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YY_VRMLYacc_ERROR_VERBOSE */
	YY_VRMLYacc_ERROR("parse error");
    }

  YYGOTO(yyerrlab1);
YYLABEL(yyerrlab1)   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (YY_VRMLYacc_CHAR == YYEOF)
	YYABORT;

#if YY_VRMLYacc_DEBUG != 0
      if (YY_VRMLYacc_DEBUG_FLAG)
	fprintf(stderr, "Discarding token %d (%s).\n", YY_VRMLYacc_CHAR, yytname[yychar1]);
#endif

      YY_VRMLYacc_CHAR = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;              /* Each real token shifted decrements this */

  YYGOTO(yyerrhandle);

YYLABEL(yyerrdefault)  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) YYGOTO(yydefault);
#endif

YYLABEL(yyerrpop)   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YY_VRMLYacc_LSP_NEEDED
  yylsp--;
#endif

#if YY_VRMLYacc_DEBUG != 0
  if (YY_VRMLYacc_DEBUG_FLAG)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

YYLABEL(yyerrhandle)

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    YYGOTO(yyerrdefault);

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    YYGOTO(yyerrdefault);

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	YYGOTO(yyerrpop);
      yyn = -yyn;
      YYGOTO(yyreduce);
    }
  else if (yyn == 0)
    YYGOTO(yyerrpop);

  if (yyn == YYFINAL)
    YYACCEPT;

#if YY_VRMLYacc_DEBUG != 0
  if (YY_VRMLYacc_DEBUG_FLAG)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = YY_VRMLYacc_LVAL;
#ifdef YY_VRMLYacc_LSP_NEEDED
  *++yylsp = YY_VRMLYacc_LLOC;
#endif

  yystate = yyn;
  YYGOTO(yynewstate);
/* end loop, in which YYGOTO may be used. */
  YYENDGOTO
}

/* END */

/* #line 1010 "/usr/local/lib/bison.cc" */
#line 3393 "VRMLYacc.C"
#line 1373 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"


