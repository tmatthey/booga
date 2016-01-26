#ifndef YY_VRMLYacc_h_included
#define YY_VRMLYacc_h_included

#line 1 "/usr/local/lib/bison.h"
/* before anything */
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
#endif
#include "booga/base/Report.h"

#include <stdio.h>

/* #line 14 "/usr/local/lib/bison.h" */
#line 21 "VRMLYacc.h"
#line 44 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/VRMLYacc.y"



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


#line 14 "/usr/local/lib/bison.h"
 /* %{ and %header{ and %union, during decl */
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
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
/* use %define LTYPE */
#endif
#endif
#ifdef YYSTYPE
#ifndef YY_VRMLYacc_STYPE 
#define YY_VRMLYacc_STYPE YYSTYPE
/* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
/* use %define STYPE */
#endif
#endif
#ifdef YYDEBUG
#ifndef YY_VRMLYacc_DEBUG
#define  YY_VRMLYacc_DEBUG YYDEBUG
/* WARNING obsolete !!! user defined YYDEBUG not reported into generated header */
/* use %define DEBUG */
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

/* #line 63 "/usr/local/lib/bison.h" */
#line 165 "VRMLYacc.h"

#line 63 "/usr/local/lib/bison.h"
/* YY_VRMLYacc_PURE */
#endif

/* #line 65 "/usr/local/lib/bison.h" */
#line 172 "VRMLYacc.h"

#line 65 "/usr/local/lib/bison.h"
/* prefix */
#ifndef YY_VRMLYacc_DEBUG

/* #line 67 "/usr/local/lib/bison.h" */
#line 179 "VRMLYacc.h"

#line 67 "/usr/local/lib/bison.h"
/* YY_VRMLYacc_DEBUG */
#endif
#ifndef YY_VRMLYacc_LSP_NEEDED

/* #line 70 "/usr/local/lib/bison.h" */
#line 187 "VRMLYacc.h"

#line 70 "/usr/local/lib/bison.h"
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

/* TOKEN C */
#ifndef YY_USE_CLASS

#ifndef YY_VRMLYacc_PURE
extern YY_VRMLYacc_STYPE YY_VRMLYacc_LVAL;
#endif


/* #line 143 "/usr/local/lib/bison.h" */
#line 265 "VRMLYacc.h"
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


#line 143 "/usr/local/lib/bison.h"
 /* #defines token */
/* after #define tokens, before const tokens S5*/
#else
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

/* #line 182 "/usr/local/lib/bison.h" */
#line 417 "VRMLYacc.h"
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


#line 182 "/usr/local/lib/bison.h"
 /* decl const */
#else
enum YY_VRMLYacc_ENUM_TOKEN { YY_VRMLYacc_NULL_TOKEN=0

/* #line 185 "/usr/local/lib/bison.h" */
#line 533 "VRMLYacc.h"
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


#line 185 "/usr/local/lib/bison.h"
 /* enum token */
     }; /* end of enum declaration */
#endif
public:
 int YY_VRMLYacc_PARSE(YY_VRMLYacc_PARSE_PARAM);
 virtual void YY_VRMLYacc_ERROR(char *msg) YY_VRMLYacc_ERROR_BODY;
#ifdef YY_VRMLYacc_PURE
#ifdef YY_VRMLYacc_LSP_NEEDED
 virtual int  YY_VRMLYacc_LEX(YY_VRMLYacc_STYPE *YY_VRMLYacc_LVAL,YY_VRMLYacc_LTYPE *YY_VRMLYacc_LLOC) YY_VRMLYacc_LEX_BODY;
#else
 virtual int  YY_VRMLYacc_LEX(YY_VRMLYacc_STYPE *YY_VRMLYacc_LVAL) YY_VRMLYacc_LEX_BODY;
#endif
#else
 virtual int YY_VRMLYacc_LEX() YY_VRMLYacc_LEX_BODY;
 YY_VRMLYacc_STYPE YY_VRMLYacc_LVAL;
#ifdef YY_VRMLYacc_LSP_NEEDED
 YY_VRMLYacc_LTYPE YY_VRMLYacc_LLOC;
#endif
 int YY_VRMLYacc_NERRS;
 int YY_VRMLYacc_CHAR;
#endif
#if YY_VRMLYacc_DEBUG != 0
public:
 int YY_VRMLYacc_DEBUG_FLAG;	/*  nonzero means print parse trace	*/
#endif
public:
 YY_VRMLYacc_CLASS(YY_VRMLYacc_CONSTRUCTOR_PARAM);
public:
 YY_VRMLYacc_MEMBERS 
};
/* other declare folow */
#endif


#if YY_VRMLYacc_COMPATIBILITY != 0
/* backward compatibility */
#ifndef YYSTYPE
#define YYSTYPE YY_VRMLYacc_STYPE
#endif

#ifndef YYLTYPE
#define YYLTYPE YY_VRMLYacc_LTYPE
#endif
#ifndef YYDEBUG
#ifdef YY_VRMLYacc_DEBUG 
#define YYDEBUG YY_VRMLYacc_DEBUG
#endif
#endif

#endif
/* END */

/* #line 236 "/usr/local/lib/bison.h" */
#line 697 "VRMLYacc.h"
#endif
