#define YY_ShaderYacc_h_included

/*  A Bison++ parser, made from /home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y  */

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
#line 85 "ShaderYacc.C"
#line 26 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"

#include <string.h>
#include <iostream.h>

#include "booga/base/List.h"
#include "booga/base/SymTable.h"
#include "booga/base/RCString.h"
#include "booga/base/Value.h"
#include "booga/base/mathutilities.h"

#include "booga/texture/ShaderNode.h"
#include "booga/texture/ShaderProgNode.h"
#include "booga/texture/ShaderHeadNode.h"
#include "booga/texture/ShaderCmpStmtNode.h"
#include "booga/texture/ShaderDeclNode.h"
#include "booga/texture/ShaderStmtNode.h"
#include "booga/texture/ShaderExpNode.h"
#include "booga/texture/ShaderIfNode.h"
#include "booga/texture/ShaderIfThenElseNode.h"
#include "booga/texture/ShaderForNode.h"
#include "booga/texture/ShaderShaderNode.h"
#include "booga/texture/ShaderWhileNode.h"
#include "booga/texture/ShaderIdExpNode.h"
#include "booga/texture/ShaderParExpNode.h"
#include "booga/texture/ShaderArithExpNode.h"
#include "booga/texture/ShaderCompExpNode.h"
#include "booga/texture/ShaderLogicExpNode.h"
#include "booga/texture/ShaderFuncNode.h"
#include "booga/texture/ShaderAssExpNode.h"
#include "booga/texture/ShaderRealValueNode.h"
#include "booga/texture/ShaderStringValueNode.h"
#include "booga/texture/ShaderVecValueNode.h"


#line 61 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
typedef union {
        Real                    number;
	RCString*		id;
	List<NVPair*>*	        nvlist;
	ShaderNode*            	node;
        ShaderExpNode*          expnode;
        List<ShaderExpNode*>*   expnodelist;
        ShaderIdExpNode*        idexpnode;
	List<ShaderNode*>*      nodelist;
	} yy_ShaderYacc_stype;
#define YY_ShaderYacc_STYPE yy_ShaderYacc_stype
#define YY_ShaderYacc_DEBUG  1
#define YY_ShaderYacc_DEBUG_FLAG  myDebugFlag
#define YY_ShaderYacc_PARSE  parse
#define YY_ShaderYacc_LEX_BODY  =0
#define YY_ShaderYacc_LEX  scan
#define YY_ShaderYacc_ERROR_VERBOSE 
#define YY_ShaderYacc_ERROR_BODY  =0
#define YY_ShaderYacc_ERROR  fatalError
#define YY_ShaderYacc_LVAL  myTokenValue
#define YY_ShaderYacc_NERRS  myErrorCount
#define YY_ShaderYacc_CONSTRUCTOR_CODE  {myDebugFlag = 0;}
#define YY_ShaderYacc_MEMBERS                                 \
public:                                        \
  ShaderProgNode* getParseTree() {return myParseTree;}    \
private:                                        \
  virtual void recoverableError(const RCString& errorMsg) = 0; \
  virtual void warning(const RCString& warnMsg) = 0; \
private:                                       \
  ShaderProgNode* myParseTree;

#line 73 "/usr/local/lib/bison.cc"
/* %{ and %header{ and %union, during decl */
#define YY_ShaderYacc_BISON 1
#ifndef YY_ShaderYacc_COMPATIBILITY
#ifndef YY_USE_CLASS
#define  YY_ShaderYacc_COMPATIBILITY 1
#else
#define  YY_ShaderYacc_COMPATIBILITY 0
#endif
#endif

#if YY_ShaderYacc_COMPATIBILITY != 0
/* backward compatibility */
#ifdef YYLTYPE
#ifndef YY_ShaderYacc_LTYPE
#define YY_ShaderYacc_LTYPE YYLTYPE
#endif
#endif
#ifdef YYSTYPE
#ifndef YY_ShaderYacc_STYPE 
#define YY_ShaderYacc_STYPE YYSTYPE
#endif
#endif
#ifdef YYDEBUG
#ifndef YY_ShaderYacc_DEBUG
#define  YY_ShaderYacc_DEBUG YYDEBUG
#endif
#endif
#ifdef YY_ShaderYacc_STYPE
#ifndef yystype
#define yystype YY_ShaderYacc_STYPE
#endif
#endif
/* use goto to be compatible */
#ifndef YY_ShaderYacc_USE_GOTO
#define YY_ShaderYacc_USE_GOTO 1
#endif
#endif

/* use no goto to be clean in C++ */
#ifndef YY_ShaderYacc_USE_GOTO
#define YY_ShaderYacc_USE_GOTO 0
#endif

#ifndef YY_ShaderYacc_PURE

/* #line 117 "/usr/local/lib/bison.cc" */
#line 200 "ShaderYacc.C"

#line 117 "/usr/local/lib/bison.cc"
/*  YY_ShaderYacc_PURE */
#endif

/* section apres lecture def, avant lecture grammaire S2 */

/* #line 121 "/usr/local/lib/bison.cc" */
#line 209 "ShaderYacc.C"

#line 121 "/usr/local/lib/bison.cc"
/* prefix */
#ifndef YY_ShaderYacc_DEBUG

/* #line 123 "/usr/local/lib/bison.cc" */
#line 216 "ShaderYacc.C"

#line 123 "/usr/local/lib/bison.cc"
/* YY_ShaderYacc_DEBUG */
#endif


#ifndef YY_ShaderYacc_LSP_NEEDED

/* #line 128 "/usr/local/lib/bison.cc" */
#line 226 "ShaderYacc.C"

#line 128 "/usr/local/lib/bison.cc"
 /* YY_ShaderYacc_LSP_NEEDED*/
#endif



/* DEFAULT LTYPE*/
#ifdef YY_ShaderYacc_LSP_NEEDED
#ifndef YY_ShaderYacc_LTYPE
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

#define YY_ShaderYacc_LTYPE yyltype
#endif
#endif
/* DEFAULT STYPE*/
      /* We used to use `unsigned long' as YY_ShaderYacc_STYPE on MSDOS,
	 but it seems better to be consistent.
	 Most programs should declare their own type anyway.  */

#ifndef YY_ShaderYacc_STYPE
#define YY_ShaderYacc_STYPE int
#endif
/* DEFAULT MISCELANEOUS */
#ifndef YY_ShaderYacc_PARSE
#define YY_ShaderYacc_PARSE yyparse
#endif
#ifndef YY_ShaderYacc_LEX
#define YY_ShaderYacc_LEX yylex
#endif
#ifndef YY_ShaderYacc_LVAL
#define YY_ShaderYacc_LVAL yylval
#endif
#ifndef YY_ShaderYacc_LLOC
#define YY_ShaderYacc_LLOC yylloc
#endif
#ifndef YY_ShaderYacc_CHAR
#define YY_ShaderYacc_CHAR yychar
#endif
#ifndef YY_ShaderYacc_NERRS
#define YY_ShaderYacc_NERRS yynerrs
#endif
#ifndef YY_ShaderYacc_DEBUG_FLAG
#define YY_ShaderYacc_DEBUG_FLAG yydebug
#endif
#ifndef YY_ShaderYacc_ERROR
#define YY_ShaderYacc_ERROR yyerror
#endif
#ifndef YY_ShaderYacc_PARSE_PARAM
#ifndef __STDC__
#ifndef __cplusplus
#ifndef YY_USE_CLASS
#define YY_ShaderYacc_PARSE_PARAM
#ifndef YY_ShaderYacc_PARSE_PARAM_DEF
#define YY_ShaderYacc_PARSE_PARAM_DEF
#endif
#endif
#endif
#endif
#ifndef YY_ShaderYacc_PARSE_PARAM
#define YY_ShaderYacc_PARSE_PARAM void
#endif
#endif
#if YY_ShaderYacc_COMPATIBILITY != 0
/* backward compatibility */
#ifdef YY_ShaderYacc_LTYPE
#ifndef YYLTYPE
#define YYLTYPE YY_ShaderYacc_LTYPE
#else
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
#endif
#endif
#ifndef YYSTYPE
#define YYSTYPE YY_ShaderYacc_STYPE
#else
/* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
#endif
#ifdef YY_ShaderYacc_PURE
#ifndef YYPURE
#define YYPURE YY_ShaderYacc_PURE
#endif
#endif
#ifdef YY_ShaderYacc_DEBUG
#ifndef YYDEBUG
#define YYDEBUG YY_ShaderYacc_DEBUG 
#endif
#endif
#ifndef YY_ShaderYacc_ERROR_VERBOSE
#ifdef YYERROR_VERBOSE
#define YY_ShaderYacc_ERROR_VERBOSE YYERROR_VERBOSE
#endif
#endif
#ifndef YY_ShaderYacc_LSP_NEEDED
#ifdef YYLSP_NEEDED
#define YY_ShaderYacc_LSP_NEEDED YYLSP_NEEDED
#endif
#endif
#endif
#ifndef YY_USE_CLASS
/* TOKEN C */

/* #line 236 "/usr/local/lib/bison.cc" */
#line 339 "ShaderYacc.C"
#define	IDENTIFIER	258
#define	NUMBER	259
#define	SURFACE	260
#define	COLOR	261
#define	VECTOR	262
#define	REAL	263
#define	STRING	264
#define	ANYSTRING	265
#define	IF	266
#define	ELSE	267
#define	FOR	268
#define	WHILE	269
#define	AND	270
#define	OR	271
#define	NOT	272
#define	SHADER	273
#define	GE	274
#define	LE	275
#define	EQ	276
#define	NE	277
#define	PE	278
#define	ME	279
#define	TE	280
#define	DE	281
#define	RE	282
#define	PP	283
#define	MM	284
#define	UMINUS	285
#define	PI	286


#line 236 "/usr/local/lib/bison.cc"
 /* #defines tokens */
#else
/* CLASS */
#ifndef YY_ShaderYacc_CLASS
#define YY_ShaderYacc_CLASS ShaderYacc
#endif
#ifndef YY_ShaderYacc_INHERIT
#define YY_ShaderYacc_INHERIT
#endif
#ifndef YY_ShaderYacc_MEMBERS
#define YY_ShaderYacc_MEMBERS 
#endif
#ifndef YY_ShaderYacc_LEX_BODY
#define YY_ShaderYacc_LEX_BODY  
#endif
#ifndef YY_ShaderYacc_ERROR_BODY
#define YY_ShaderYacc_ERROR_BODY  
#endif
#ifndef YY_ShaderYacc_CONSTRUCTOR_PARAM
#define YY_ShaderYacc_CONSTRUCTOR_PARAM
#endif
#ifndef YY_ShaderYacc_CONSTRUCTOR_CODE
#define YY_ShaderYacc_CONSTRUCTOR_CODE
#endif
#ifndef YY_ShaderYacc_CONSTRUCTOR_INIT
#define YY_ShaderYacc_CONSTRUCTOR_INIT
#endif
/* choose between enum and const */
#ifndef YY_ShaderYacc_USE_CONST_TOKEN
#define YY_ShaderYacc_USE_CONST_TOKEN 0
/* yes enum is more compatible with flex,  */
/* so by default we use it */ 
#endif
#if YY_ShaderYacc_USE_CONST_TOKEN != 0
#ifndef YY_ShaderYacc_ENUM_TOKEN
#define YY_ShaderYacc_ENUM_TOKEN yy_ShaderYacc_enum_token
#endif
#endif

class YY_ShaderYacc_CLASS YY_ShaderYacc_INHERIT
{
public: 
#if YY_ShaderYacc_USE_CONST_TOKEN != 0
/* static const int token ... */

/* #line 280 "/usr/local/lib/bison.cc" */
#line 418 "ShaderYacc.C"
static const int IDENTIFIER;
static const int NUMBER;
static const int SURFACE;
static const int COLOR;
static const int VECTOR;
static const int REAL;
static const int STRING;
static const int ANYSTRING;
static const int IF;
static const int ELSE;
static const int FOR;
static const int WHILE;
static const int AND;
static const int OR;
static const int NOT;
static const int SHADER;
static const int GE;
static const int LE;
static const int EQ;
static const int NE;
static const int PE;
static const int ME;
static const int TE;
static const int DE;
static const int RE;
static const int PP;
static const int MM;
static const int UMINUS;
static const int PI;


#line 280 "/usr/local/lib/bison.cc"
 /* decl const */
#else
enum YY_ShaderYacc_ENUM_TOKEN { YY_ShaderYacc_NULL_TOKEN=0

/* #line 283 "/usr/local/lib/bison.cc" */
#line 456 "ShaderYacc.C"
	,IDENTIFIER=258
	,NUMBER=259
	,SURFACE=260
	,COLOR=261
	,VECTOR=262
	,REAL=263
	,STRING=264
	,ANYSTRING=265
	,IF=266
	,ELSE=267
	,FOR=268
	,WHILE=269
	,AND=270
	,OR=271
	,NOT=272
	,SHADER=273
	,GE=274
	,LE=275
	,EQ=276
	,NE=277
	,PE=278
	,ME=279
	,TE=280
	,DE=281
	,RE=282
	,PP=283
	,MM=284
	,UMINUS=285
	,PI=286


#line 283 "/usr/local/lib/bison.cc"
 /* enum token */
     }; /* end of enum declaration */
#endif
public:
 int YY_ShaderYacc_PARSE (YY_ShaderYacc_PARSE_PARAM);
 virtual void YY_ShaderYacc_ERROR(char *msg) YY_ShaderYacc_ERROR_BODY;
#ifdef YY_ShaderYacc_PURE
#ifdef YY_ShaderYacc_LSP_NEEDED
 virtual int  YY_ShaderYacc_LEX (YY_ShaderYacc_STYPE *YY_ShaderYacc_LVAL,YY_ShaderYacc_LTYPE *YY_ShaderYacc_LLOC) YY_ShaderYacc_LEX_BODY;
#else
 virtual int  YY_ShaderYacc_LEX (YY_ShaderYacc_STYPE *YY_ShaderYacc_LVAL) YY_ShaderYacc_LEX_BODY;
#endif
#else
 virtual int YY_ShaderYacc_LEX() YY_ShaderYacc_LEX_BODY;
 YY_ShaderYacc_STYPE YY_ShaderYacc_LVAL;
#ifdef YY_ShaderYacc_LSP_NEEDED
 YY_ShaderYacc_LTYPE YY_ShaderYacc_LLOC;
#endif
 int   YY_ShaderYacc_NERRS;
 int    YY_ShaderYacc_CHAR;
#endif
#if YY_ShaderYacc_DEBUG != 0
 int YY_ShaderYacc_DEBUG_FLAG;   /*  nonzero means print parse trace     */
#endif
public:
 YY_ShaderYacc_CLASS(YY_ShaderYacc_CONSTRUCTOR_PARAM);
public:
 YY_ShaderYacc_MEMBERS 
};
/* other declare folow */
#if YY_ShaderYacc_USE_CONST_TOKEN != 0

/* #line 314 "/usr/local/lib/bison.cc" */
#line 522 "ShaderYacc.C"
const int YY_ShaderYacc_CLASS::IDENTIFIER=258;
const int YY_ShaderYacc_CLASS::NUMBER=259;
const int YY_ShaderYacc_CLASS::SURFACE=260;
const int YY_ShaderYacc_CLASS::COLOR=261;
const int YY_ShaderYacc_CLASS::VECTOR=262;
const int YY_ShaderYacc_CLASS::REAL=263;
const int YY_ShaderYacc_CLASS::STRING=264;
const int YY_ShaderYacc_CLASS::ANYSTRING=265;
const int YY_ShaderYacc_CLASS::IF=266;
const int YY_ShaderYacc_CLASS::ELSE=267;
const int YY_ShaderYacc_CLASS::FOR=268;
const int YY_ShaderYacc_CLASS::WHILE=269;
const int YY_ShaderYacc_CLASS::AND=270;
const int YY_ShaderYacc_CLASS::OR=271;
const int YY_ShaderYacc_CLASS::NOT=272;
const int YY_ShaderYacc_CLASS::SHADER=273;
const int YY_ShaderYacc_CLASS::GE=274;
const int YY_ShaderYacc_CLASS::LE=275;
const int YY_ShaderYacc_CLASS::EQ=276;
const int YY_ShaderYacc_CLASS::NE=277;
const int YY_ShaderYacc_CLASS::PE=278;
const int YY_ShaderYacc_CLASS::ME=279;
const int YY_ShaderYacc_CLASS::TE=280;
const int YY_ShaderYacc_CLASS::DE=281;
const int YY_ShaderYacc_CLASS::RE=282;
const int YY_ShaderYacc_CLASS::PP=283;
const int YY_ShaderYacc_CLASS::MM=284;
const int YY_ShaderYacc_CLASS::UMINUS=285;
const int YY_ShaderYacc_CLASS::PI=286;


#line 314 "/usr/local/lib/bison.cc"
 /* const YY_ShaderYacc_CLASS::token */
#endif
/*apres const  */
YY_ShaderYacc_CLASS::YY_ShaderYacc_CLASS(YY_ShaderYacc_CONSTRUCTOR_PARAM) YY_ShaderYacc_CONSTRUCTOR_INIT
{
#if YY_ShaderYacc_DEBUG != 0
YY_ShaderYacc_DEBUG_FLAG=0;
#endif
YY_ShaderYacc_CONSTRUCTOR_CODE;
};
#endif

/* #line 325 "/usr/local/lib/bison.cc" */
#line 568 "ShaderYacc.C"


#define	YYFINAL		149
#define	YYFLAG		-32768
#define	YYNTBASE	49

#define YYTRANSLATE(x) ((unsigned)(x) <= 286 ? yytranslate[x] : 70)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,    39,     2,     2,    41,
    42,    37,    35,    43,    36,     2,    38,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,    46,    33,
    32,    34,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    47,     2,    48,    40,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    44,     2,    45,     2,     2,     2,     2,     2,
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
    26,    27,    28,    29,    30,    31
};

#if YY_ShaderYacc_DEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     5,    11,    13,    14,    16,    20,    23,    27,
    28,    34,    35,    38,    41,    45,    47,    49,    51,    53,
    56,    61,    62,    65,    66,    69,    72,    75,    77,    79,
    85,    93,   103,   109,   115,   117,   119,   122,   127,   133,
   135,   138,   141,   144,   146,   149,   153,   157,   161,   165,
   169,   173,   177,   181,   184,   188,   192,   196,   200,   204,
   208,   212,   216,   220,   224,   228,   232,   234,   236,   244,
   246,   247,   249,   253,   255
};

static const short yyrhs[] = {    -1,
    50,    51,    55,     0,    52,     3,    41,    53,    42,     0,
     5,     0,     0,    54,     0,    53,    43,    54,     0,     3,
    61,     0,    59,     3,    61,     0,     0,    56,    44,    57,
    62,    45,     0,     0,    57,    58,     0,    57,     1,     0,
    59,    60,    46,     0,     8,     0,     6,     0,     7,     0,
     9,     0,     3,    61,     0,    60,    43,     3,    61,     0,
     0,    32,    64,     0,     0,    62,    63,     0,    62,     1,
     0,    64,    46,     0,    46,     0,    55,     0,    11,    41,
    64,    42,    63,     0,    11,    41,    64,    42,    63,    12,
    63,     0,    13,    41,    64,    46,    64,    46,    64,    42,
    63,     0,    14,    41,    64,    42,    63,     0,    18,    41,
    67,    42,    46,     0,    65,     0,    66,     0,    36,    66,
     0,     3,    41,    67,    42,     0,    36,     3,    41,    67,
    42,     0,    68,     0,    36,    68,     0,    68,    28,     0,
    68,    29,     0,    69,     0,    36,    69,     0,    65,    35,
    65,     0,    65,    36,    65,     0,    65,    37,    65,     0,
    65,    38,    65,     0,    65,    39,    65,     0,    65,    40,
    65,     0,    65,    15,    65,     0,    65,    16,    65,     0,
    17,    65,     0,    65,    34,    65,     0,    65,    33,    65,
     0,    65,    19,    65,     0,    65,    20,    65,     0,    65,
    21,    65,     0,    65,    22,    65,     0,    68,    32,    65,
     0,    68,    26,    65,     0,    68,    24,    65,     0,    68,
    23,    65,     0,    68,    27,    65,     0,    68,    25,    65,
     0,     4,     0,    31,     0,    47,    65,    43,    65,    43,
    65,    48,     0,    10,     0,     0,    65,     0,    67,    43,
    65,     0,     3,     0,    41,    64,    42,     0
};

#endif

#if YY_ShaderYacc_DEBUG != 0
static const short yyrline[] = { 0,
   149,   154,   162,   168,   174,   179,   185,   192,   205,   218,
   223,   230,   235,   251,   254,   263,   268,   273,   278,   284,
   291,   299,   304,   310,   315,   331,   334,   339,   344,   349,
   354,   359,   364,   369,   375,   381,   386,   392,   400,   410,
   416,   422,   429,   436,   441,   447,   452,   457,   462,   467,
   472,   477,   482,   487,   492,   497,   502,   507,   512,   517,
   522,   527,   534,   541,   548,   555,   563,   567,   572,   577,
   583,   588,   594,   601,   610
};

static const char * const yytname[] = {   "$","error","$illegal.","IDENTIFIER",
"NUMBER","SURFACE","COLOR","VECTOR","REAL","STRING","ANYSTRING","IF","ELSE",
"FOR","WHILE","AND","OR","NOT","SHADER","GE","LE","EQ","NE","PE","ME","TE","DE",
"RE","PP","MM","UMINUS","PI","'='","'<'","'>'","'+'","'-'","'*'","'/'","'%'",
"'^'","'('","')'","','","'{'","'}'","';'","'['","']'","program","@1","head",
"shader_type","parameters","parameter","compound_statement","@2","declarations",
"declaration","valid_type","declarator_list","optional_init","statements","statement",
"expression","binary","value","arguments","Identifier","parexp",""
};
#endif

static const short yyr1[] = {     0,
    50,    49,    51,    52,    53,    53,    53,    54,    54,    56,
    55,    57,    57,    57,    58,    59,    59,    59,    59,    60,
    60,    61,    61,    62,    62,    62,    63,    63,    63,    63,
    63,    63,    63,    63,    64,    65,    65,    65,    65,    65,
    65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
    65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
    65,    65,    65,    65,    65,    65,    66,    66,    66,    66,
    67,    67,    67,    68,    69
};

static const short yyr2[] = {     0,
     0,     3,     5,     1,     0,     1,     3,     2,     3,     0,
     5,     0,     2,     2,     3,     1,     1,     1,     1,     2,
     4,     0,     2,     0,     2,     2,     2,     1,     1,     5,
     7,     9,     5,     5,     1,     1,     2,     4,     5,     1,
     2,     2,     2,     1,     2,     3,     3,     3,     3,     3,
     3,     3,     3,     2,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     1,     1,     7,     1,
     0,     1,     3,     1,     3
};

static const short yydefact[] = {     1,
     0,     4,    10,     0,     2,     0,     0,    12,     5,     0,
    22,    17,    18,    16,    19,     0,     6,     0,    14,    13,
     0,     0,     0,     8,     3,     0,    22,    22,     0,    26,
    74,    67,    70,     0,     0,     0,     0,     0,    68,     0,
     0,    11,    28,     0,    29,    25,     0,    35,    36,    40,
    44,    23,     7,     9,    20,     0,    15,    71,     0,     0,
     0,    54,    71,    74,    37,    41,    45,     0,     0,    27,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    42,
    43,     0,    22,    72,     0,     0,     0,     0,     0,    71,
    75,     0,    52,    53,    57,    58,    59,    60,    56,    55,
    46,    47,    48,    49,    50,    51,    64,    63,    66,    62,
    65,    61,    21,    38,     0,    10,     0,    10,     0,     0,
     0,    73,    30,     0,    33,    34,    39,     0,    10,     0,
     0,    31,     0,    69,    10,    32,     0,     0,     0
};

static const short yydefgoto[] = {   147,
     1,     3,     4,    16,    17,    45,     6,    10,    20,    18,
    29,    24,    22,    46,    47,    48,    49,    95,    50,    51
};

static const short yypact[] = {-32768,
    -2,-32768,-32768,     4,-32768,   -19,    21,-32768,     7,    74,
    31,-32768,-32768,-32768,-32768,   -15,-32768,     6,-32768,-32768,
    61,   121,   167,-32768,-32768,     7,    31,    31,   -35,-32768,
    25,-32768,-32768,    28,    30,    32,   167,    33,-32768,    55,
   167,-32768,-32768,   167,-32768,-32768,    26,   267,-32768,   293,
-32768,-32768,-32768,-32768,-32768,    73,-32768,   167,   167,   167,
   167,-32768,   167,    38,-32768,-32768,-32768,    47,   215,-32768,
   167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
   167,   167,   167,   167,   167,   167,   167,   167,   167,-32768,
-32768,   167,    31,   267,   -13,    48,    49,    52,   -10,   167,
-32768,   167,   207,   275,   229,   229,   153,   153,   229,   229,
   -18,   -18,    57,    57,    57,-32768,   267,   267,   267,   267,
   267,   267,-32768,-32768,   167,   133,   167,   133,    53,    -8,
   241,   267,    86,    54,-32768,-32768,-32768,   167,   133,   167,
   185,-32768,    59,-32768,   133,-32768,   103,   107,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,    82,   106,-32768,-32768,-32768,   101,
-32768,   -26,-32768,  -122,   -23,   -32,    72,   -39,    76,    83
};


#define	YYLAST		325


static const short yytable[] = {    52,
    54,    55,     2,   133,    62,   135,     7,    56,    27,    11,
    57,    69,    12,    13,    14,    15,   142,    68,    81,    82,
    83,    84,   146,    99,     8,    94,    25,    26,   124,   125,
    94,   129,   125,   137,   125,    96,    97,    98,   103,   104,
   105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
   115,   116,   117,   118,   119,   120,   121,    64,    32,   122,
   130,     9,    23,    28,    33,    58,   123,    94,    59,   131,
    60,    70,    61,    63,    19,    93,   -24,   -24,   100,    12,
    13,    14,    15,   -24,   -24,    39,   -24,   -24,   101,   126,
   -24,   -24,   132,   128,   127,    41,    84,   139,   136,   140,
   145,    44,   148,   134,   -24,   141,   149,    53,     5,   -24,
    21,    65,     0,     0,   -24,    66,   143,   -24,   -24,   -24,
   -24,    30,    67,    31,    32,     0,     0,     0,     0,     0,
    33,    34,     0,    35,    36,    31,    32,    37,    38,     0,
     0,     0,    33,    34,     0,    35,    36,     0,     0,    37,
    38,    39,     0,     0,     0,     0,    40,     0,     0,     0,
     0,    41,     0,    39,   -10,    42,    43,    44,    40,    31,
    32,    73,    74,    41,     0,     0,    33,     0,    43,    44,
     0,     0,     0,    37,     0,    77,    78,    79,    80,    81,
    82,    83,    84,     0,     0,     0,     0,    39,     0,    71,
    72,     0,    40,    73,    74,    75,    76,    41,     0,     0,
     0,     0,     0,    44,     0,     0,     0,    77,    78,    79,
    80,    81,    82,    83,    84,    73,    74,    75,    76,    71,
    72,     0,   144,    73,    74,    75,    76,     0,     0,    77,
    78,    79,    80,    81,    82,    83,    84,    77,    78,    79,
    80,    81,    82,    83,    84,    71,    72,   102,     0,    73,
    74,    75,    76,    79,    80,    81,    82,    83,    84,     0,
     0,     0,     0,    77,    78,    79,    80,    81,    82,    83,
    84,    71,    72,   138,     0,    73,    74,    75,    76,    71,
     0,     0,     0,    73,    74,    75,    76,     0,     0,    77,
    78,    79,    80,    81,    82,    83,    84,    77,    78,    79,
    80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
    90,    91,     0,     0,    92
};

static const short yycheck[] = {    23,
    27,    28,     5,   126,    37,   128,     3,    43,     3,     3,
    46,    44,     6,     7,     8,     9,   139,    41,    37,    38,
    39,    40,   145,    63,    44,    58,    42,    43,    42,    43,
    63,    42,    43,    42,    43,    59,    60,    61,    71,    72,
    73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
    83,    84,    85,    86,    87,    88,    89,     3,     4,    92,
   100,    41,    32,     3,    10,    41,    93,   100,    41,   102,
    41,    46,    41,    41,     1,     3,     3,     4,    41,     6,
     7,     8,     9,    10,    11,    31,    13,    14,    42,    42,
    17,    18,   125,    42,    46,    41,    40,    12,    46,    46,
    42,    47,     0,   127,    31,   138,     0,    26,     3,    36,
    10,    40,    -1,    -1,    41,    40,   140,    44,    45,    46,
    47,     1,    40,     3,     4,    -1,    -1,    -1,    -1,    -1,
    10,    11,    -1,    13,    14,     3,     4,    17,    18,    -1,
    -1,    -1,    10,    11,    -1,    13,    14,    -1,    -1,    17,
    18,    31,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,
    -1,    41,    -1,    31,    44,    45,    46,    47,    36,     3,
     4,    19,    20,    41,    -1,    -1,    10,    -1,    46,    47,
    -1,    -1,    -1,    17,    -1,    33,    34,    35,    36,    37,
    38,    39,    40,    -1,    -1,    -1,    -1,    31,    -1,    15,
    16,    -1,    36,    19,    20,    21,    22,    41,    -1,    -1,
    -1,    -1,    -1,    47,    -1,    -1,    -1,    33,    34,    35,
    36,    37,    38,    39,    40,    19,    20,    21,    22,    15,
    16,    -1,    48,    19,    20,    21,    22,    -1,    -1,    33,
    34,    35,    36,    37,    38,    39,    40,    33,    34,    35,
    36,    37,    38,    39,    40,    15,    16,    43,    -1,    19,
    20,    21,    22,    35,    36,    37,    38,    39,    40,    -1,
    -1,    -1,    -1,    33,    34,    35,    36,    37,    38,    39,
    40,    15,    16,    43,    -1,    19,    20,    21,    22,    15,
    -1,    -1,    -1,    19,    20,    21,    22,    -1,    -1,    33,
    34,    35,    36,    37,    38,    39,    40,    33,    34,    35,
    36,    37,    38,    39,    40,    23,    24,    25,    26,    27,
    28,    29,    -1,    -1,    32
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

#if YY_ShaderYacc_USE_GOTO != 0
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
int __alloca_free_ptr(char *ptr,char *ref)
{if(ptr!=ref) free(ptr);
 return 0;}

#define __ALLOCA_alloca(size) malloc(size)
#define __ALLOCA_free(ptr,ref) __alloca_free_ptr((char *)ptr,(char *)ref)

#ifdef YY_ShaderYacc_LSP_NEEDED
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
#define yyclearin       (YY_ShaderYacc_CHAR = YYEMPTY)
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
  if (YY_ShaderYacc_CHAR == YYEMPTY && yylen == 1)                               \
    { YY_ShaderYacc_CHAR = (token), YY_ShaderYacc_LVAL = (value);                 \
      yychar1 = YYTRANSLATE (YY_ShaderYacc_CHAR);                                \
      YYPOPSTACK;                                               \
      YYGOTO(yybackup);                                            \
    }                                                           \
  else                                                          \
    { YY_ShaderYacc_ERROR ("syntax error: cannot back up"); YYERROR; }   \
while (0)

#define YYTERROR        1
#define YYERRCODE       256

#ifndef YY_ShaderYacc_PURE
/* UNPURE */
#define YYLEX           YY_ShaderYacc_LEX()
#ifndef YY_USE_CLASS
/* If nonreentrant, and not class , generate the variables here */
int     YY_ShaderYacc_CHAR;                      /*  the lookahead symbol        */
YY_ShaderYacc_STYPE      YY_ShaderYacc_LVAL;              /*  the semantic value of the */
				/*  lookahead symbol    */
int YY_ShaderYacc_NERRS;                 /*  number of parse errors so far */
#ifdef YY_ShaderYacc_LSP_NEEDED
YY_ShaderYacc_LTYPE YY_ShaderYacc_LLOC;   /*  location data for the lookahead     */
			/*  symbol                              */
#endif
#endif


#else
/* PURE */
#ifdef YY_ShaderYacc_LSP_NEEDED
#define YYLEX           YY_ShaderYacc_LEX(&YY_ShaderYacc_LVAL, &YY_ShaderYacc_LLOC)
#else
#define YYLEX           YY_ShaderYacc_LEX(&YY_ShaderYacc_LVAL)
#endif
#endif
#ifndef YY_USE_CLASS
#if YY_ShaderYacc_DEBUG != 0
int YY_ShaderYacc_DEBUG_FLAG;                    /*  nonzero means print parse trace     */
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
 YY_ShaderYacc_CLASS::
#endif
     YY_ShaderYacc_PARSE(YY_ShaderYacc_PARSE_PARAM)
#ifndef __STDC__
#ifndef __cplusplus
#ifndef YY_USE_CLASS
/* parameter definition without protypes */
YY_ShaderYacc_PARSE_PARAM_DEF
#endif
#endif
#endif
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YY_ShaderYacc_STYPE *yyvsp;
  int yyerrstatus;      /*  number of tokens to shift before error messages enabled */
  int yychar1=0;          /*  lookahead token as an internal (translated) token number */

  short yyssa[YYINITDEPTH];     /*  the state stack                     */
  YY_ShaderYacc_STYPE yyvsa[YYINITDEPTH];        /*  the semantic value stack            */

  short *yyss = yyssa;          /*  refer to the stacks thru separate pointers */
  YY_ShaderYacc_STYPE *yyvs = yyvsa;     /*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YY_ShaderYacc_LSP_NEEDED
  YY_ShaderYacc_LTYPE yylsa[YYINITDEPTH];        /*  the location stack                  */
  YY_ShaderYacc_LTYPE *yyls = yylsa;
  YY_ShaderYacc_LTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YY_ShaderYacc_PURE
  int YY_ShaderYacc_CHAR;
  YY_ShaderYacc_STYPE YY_ShaderYacc_LVAL;
  int YY_ShaderYacc_NERRS;
#ifdef YY_ShaderYacc_LSP_NEEDED
  YY_ShaderYacc_LTYPE YY_ShaderYacc_LLOC;
#endif
#endif

  YY_ShaderYacc_STYPE yyval;             /*  the variable used to return         */
				/*  semantic values from the action     */
				/*  routines                            */

  int yylen;
/* start loop, in which YYGOTO may be used. */
YYBEGINGOTO

#if YY_ShaderYacc_DEBUG != 0
  if (YY_ShaderYacc_DEBUG_FLAG)
    fprintf(stderr, "Starting parse\n");
#endif
  yystate = 0;
  yyerrstatus = 0;
  YY_ShaderYacc_NERRS = 0;
  YY_ShaderYacc_CHAR = YYEMPTY;          /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YY_ShaderYacc_LSP_NEEDED
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
      YY_ShaderYacc_STYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YY_ShaderYacc_LSP_NEEDED
      YY_ShaderYacc_LTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YY_ShaderYacc_LSP_NEEDED
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
#ifdef YY_ShaderYacc_LSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  YY_ShaderYacc_ERROR("parser stack overflow");
	  __ALLOCA_return(2);
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) __ALLOCA_alloca (yystacksize * sizeof (*yyssp));
      __yy_bcopy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      __ALLOCA_free(yyss1,yyssa);
      yyvs = (YY_ShaderYacc_STYPE *) __ALLOCA_alloca (yystacksize * sizeof (*yyvsp));
      __yy_bcopy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
      __ALLOCA_free(yyvs1,yyvsa);
#ifdef YY_ShaderYacc_LSP_NEEDED
      yyls = (YY_ShaderYacc_LTYPE *) __ALLOCA_alloca (yystacksize * sizeof (*yylsp));
      __yy_bcopy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
      __ALLOCA_free(yyls1,yylsa);
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YY_ShaderYacc_LSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YY_ShaderYacc_DEBUG != 0
      if (YY_ShaderYacc_DEBUG_FLAG)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YY_ShaderYacc_DEBUG != 0
  if (YY_ShaderYacc_DEBUG_FLAG)
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

  if (YY_ShaderYacc_CHAR == YYEMPTY)
    {
#if YY_ShaderYacc_DEBUG != 0
      if (YY_ShaderYacc_DEBUG_FLAG)
	fprintf(stderr, "Reading a token: ");
#endif
      YY_ShaderYacc_CHAR = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (YY_ShaderYacc_CHAR <= 0)           /* This means end of input. */
    {
      yychar1 = 0;
      YY_ShaderYacc_CHAR = YYEOF;                /* Don't call YYLEX any more */

#if YY_ShaderYacc_DEBUG != 0
      if (YY_ShaderYacc_DEBUG_FLAG)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(YY_ShaderYacc_CHAR);

#if YY_ShaderYacc_DEBUG != 0
      if (YY_ShaderYacc_DEBUG_FLAG)
	{
	  fprintf (stderr, "Next token is %d (%s", YY_ShaderYacc_CHAR, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, YY_ShaderYacc_CHAR, YY_ShaderYacc_LVAL);
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

#if YY_ShaderYacc_DEBUG != 0
  if (YY_ShaderYacc_DEBUG_FLAG)
    fprintf(stderr, "Shifting token %d (%s), ", YY_ShaderYacc_CHAR, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (YY_ShaderYacc_CHAR != YYEOF)
    YY_ShaderYacc_CHAR = YYEMPTY;

  *++yyvsp = YY_ShaderYacc_LVAL;
#ifdef YY_ShaderYacc_LSP_NEEDED
  *++yylsp = YY_ShaderYacc_LLOC;
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

#if YY_ShaderYacc_DEBUG != 0
  if (YY_ShaderYacc_DEBUG_FLAG)
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
#line 1308 "ShaderYacc.C"

  switch (yyn) {

case 1:
#line 150 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  ShaderNode::enterBlock();
                ;
    break;}
case 2:
#line 155 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
		  yyval.node = new ShaderProgNode(yyvsp[-1].node, yyvsp[0].node);
		  myParseTree = (ShaderProgNode*)yyval.node;
                  ShaderNode::leaveBlock();
		;
    break;}
case 3:
#line 163 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.node = new ShaderHeadNode(yyvsp[-4].id, yyvsp[-3].id, yyvsp[-1].nodelist);
                ;
    break;}
case 4:
#line 169 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.id = new RCString("surface");
                ;
    break;}
case 5:
#line 175 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.nodelist = NULL;
                ;
    break;}
case 6:
#line 180 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                   yyval.nodelist = new List<ShaderNode*>(1);
                   yyval.nodelist->append(yyvsp[0].node);
                ;
    break;}
case 7:
#line 186 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.nodelist = yyvsp[-2].nodelist;
                  yyval.nodelist->append(yyvsp[0].node);
                ;
    break;}
case 8:
#line 193 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
		  RCString* tempstring = new RCString("real");
                  List<NVPair*>* templist;
                  NVPair* newPair = new NVPair(yyvsp[-1].id, yyvsp[0].expnode);
                  templist = new List<NVPair*>(1);
                  templist->append(newPair);
                  RCString warnMsg;
                  yyval.node = new ShaderDeclNode(warnMsg, tempstring, templist);
                  if(!warnMsg.isEmpty())
                    warning(warnMsg);
                ;
    break;}
case 9:
#line 206 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  List<NVPair*>* temp;
                  NVPair* newPair = new NVPair(yyvsp[-1].id, yyvsp[0].expnode);
                  temp = new List<NVPair*>(1);
                  temp->append(newPair);
                  RCString warnMsg;
                  yyval.node = new ShaderDeclNode(warnMsg, yyvsp[-2].id, temp);
                  if (!warnMsg.isEmpty())
                    warning(warnMsg);
                ;
    break;}
case 10:
#line 219 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  ShaderNode::enterBlock();
                ;
    break;}
case 11:
#line 224 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{  
		  yyval.node = new ShaderCmpStmtNode(yyvsp[-2].nodelist, yyvsp[-1].nodelist);
                  ShaderNode::leaveBlock();		
                ;
    break;}
case 12:
#line 231 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
		  yyval.nodelist = NULL;
		;
    break;}
case 13:
#line 236 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
		  if (yyvsp[-1].nodelist) {
		    yyval.nodelist = yyvsp[-1].nodelist;
		    if (yyvsp[0].node)
		      yyval.nodelist->append(yyvsp[0].node);
		  }     
		  else
		    if (yyvsp[0].node) {
		      yyval.nodelist = new List<ShaderNode*>(1);
		      yyval.nodelist->append(yyvsp[0].node);
		  }
		  
		  yyerrok;
		;
    break;}
case 15:
#line 255 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  RCString warnMsg;
                  yyval.node = new ShaderDeclNode(warnMsg, yyvsp[-2].id, yyvsp[-1].nvlist);
                  if (!warnMsg.isEmpty())
                    warning(warnMsg);
		;
    break;}
case 16:
#line 264 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
		  yyval.id = new RCString("real");
		;
    break;}
case 17:
#line 269 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
		  yyval.id = new RCString("color");
		;
    break;}
case 18:
#line 274 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
		  yyval.id = new RCString("vector");
		;
    break;}
case 19:
#line 279 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
		  yyval.id = new RCString("string");
		;
    break;}
case 20:
#line 285 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  NVPair* newPair = new NVPair(yyvsp[-1].id, yyvsp[0].expnode);
                  yyval.nvlist = new List<NVPair*>(1);
                  yyval.nvlist->append(newPair);
		;
    break;}
case 21:
#line 292 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.nvlist = yyvsp[-3].nvlist;
                  NVPair* newPair = new NVPair(yyvsp[-1].id, yyvsp[0].expnode);
                  yyval.nvlist->append(newPair);
		;
    break;}
case 22:
#line 300 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = NULL;
                ;
    break;}
case 23:
#line 305 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = yyvsp[0].expnode;
                ;
    break;}
case 24:
#line 311 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
		  yyval.nodelist = NULL;
		;
    break;}
case 25:
#line 316 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
		  if (yyvsp[-1].nodelist) {
		    yyval.nodelist = yyvsp[-1].nodelist;
		    if (yyvsp[0].node)
		      yyval.nodelist->append(yyvsp[0].node);
		  }     
		  else
		    if (yyvsp[0].node) {
		      yyval.nodelist = new List<ShaderNode*>(1);
		      yyval.nodelist->append(yyvsp[0].node);
		    }
		    
                  yyerrok;
		;
    break;}
case 27:
#line 335 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
		  yyval.node = new ShaderStmtNode(yyvsp[-1].expnode);
		;
    break;}
case 28:
#line 340 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
		  yyval.node = NULL;
		;
    break;}
case 29:
#line 345 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.node = new ShaderCmpStmtNode((const ShaderCmpStmtNode&) *yyvsp[0].node);
                ;
    break;}
case 30:
#line 350 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.node = new ShaderIfNode(yyvsp[-2].expnode, yyvsp[0].node);
                ;
    break;}
case 31:
#line 355 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.node = new ShaderIfThenElseNode(yyvsp[-4].expnode, yyvsp[-2].node, yyvsp[0].node);
                ;
    break;}
case 32:
#line 360 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.node = new ShaderForNode(yyvsp[-6].expnode, yyvsp[-4].expnode, yyvsp[-2].expnode, yyvsp[0].node);
                ;
    break;}
case 33:
#line 365 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.node = new ShaderWhileNode(yyvsp[-2].expnode, yyvsp[0].node);
                ;
    break;}
case 34:
#line 370 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.node = new ShaderShaderNode(yyvsp[-2].expnodelist);
                ;
    break;}
case 35:
#line 376 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = yyvsp[0].expnode;
                ;
    break;}
case 36:
#line 382 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = yyvsp[0].expnode;
                ;
    break;}
case 37:
#line 387 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  ShaderExpNode* temp = new ShaderRealValueNode(-1.0);
                  yyval.expnode = new ShaderArithExpNode('*', temp, yyvsp[0].expnode);
                ;
    break;}
case 38:
#line 393 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  RCString errMsg;
                  yyval.expnode = new ShaderFuncNode(errMsg, yyvsp[-3].id, yyvsp[-1].expnodelist);
                  if (!errMsg.isEmpty())
                    recoverableError(errMsg);
                ;
    break;}
case 39:
#line 401 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  RCString errMsg;
                  ShaderExpNode* temp1 = new ShaderRealValueNode(-1.0);
                  ShaderFuncNode* temp2 = new ShaderFuncNode(errMsg, yyvsp[-3].id, yyvsp[-1].expnodelist);
                  if (!errMsg.isEmpty())
                    recoverableError(errMsg);
                  yyval.expnode = new ShaderArithExpNode('*', temp1, temp2);
                ;
    break;}
case 40:
#line 412 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = yyvsp[0].idexpnode;
                ;
    break;}
case 41:
#line 417 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  ShaderExpNode* temp = new ShaderRealValueNode(-1.0);
                  yyval.expnode = new ShaderArithExpNode('*', temp, yyvsp[0].idexpnode);
                ;
    break;}
case 42:
#line 423 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  ShaderExpNode* temp1 = new ShaderRealValueNode(1.0);
                  ShaderExpNode* temp2 = new ShaderArithExpNode('+', yyvsp[-1].idexpnode, temp1);
                  yyval.expnode = new ShaderAssExpNode(yyvsp[-1].idexpnode, temp2);
                ;
    break;}
case 43:
#line 430 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  ShaderExpNode* temp1 = new ShaderRealValueNode(1.0);
                  ShaderExpNode* temp2 = new ShaderArithExpNode('-', yyvsp[-1].idexpnode, temp1);
                  yyval.expnode = new ShaderAssExpNode(yyvsp[-1].idexpnode, temp2);
                ;
    break;}
case 44:
#line 437 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = yyvsp[0].expnode;
                ;
    break;}
case 45:
#line 442 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  ShaderExpNode* temp = new ShaderRealValueNode(-1.0);
                  yyval.expnode = new ShaderArithExpNode('*', temp, yyvsp[0].expnode);
                ;
    break;}
case 46:
#line 448 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = new ShaderArithExpNode('+', yyvsp[-2].expnode, yyvsp[0].expnode)
                ;
    break;}
case 47:
#line 453 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = new ShaderArithExpNode('-', yyvsp[-2].expnode, yyvsp[0].expnode)
                ;
    break;}
case 48:
#line 458 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = new ShaderArithExpNode('*', yyvsp[-2].expnode, yyvsp[0].expnode)
                ;
    break;}
case 49:
#line 463 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = new ShaderArithExpNode('/', yyvsp[-2].expnode, yyvsp[0].expnode)
                ;
    break;}
case 50:
#line 468 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = new ShaderArithExpNode('%', yyvsp[-2].expnode, yyvsp[0].expnode)
                ;
    break;}
case 51:
#line 473 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = new ShaderArithExpNode('^', yyvsp[-2].expnode, yyvsp[0].expnode)
                ;
    break;}
case 52:
#line 478 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = new ShaderLogicExpNode("&&", yyvsp[-2].expnode, yyvsp[0].expnode)
                ;
    break;}
case 53:
#line 483 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = new ShaderLogicExpNode("||", yyvsp[-2].expnode, yyvsp[0].expnode)
                ;
    break;}
case 54:
#line 488 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = new ShaderLogicExpNode("!", yyvsp[0].expnode)
                ;
    break;}
case 55:
#line 493 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = new ShaderCompExpNode(">", yyvsp[-2].expnode, yyvsp[0].expnode)
                ;
    break;}
case 56:
#line 498 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = new ShaderCompExpNode("<", yyvsp[-2].expnode, yyvsp[0].expnode)
                ;
    break;}
case 57:
#line 503 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = new ShaderCompExpNode(">=", yyvsp[-2].expnode, yyvsp[0].expnode)
                ;
    break;}
case 58:
#line 508 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = new ShaderCompExpNode("<=", yyvsp[-2].expnode, yyvsp[0].expnode)
                ;
    break;}
case 59:
#line 513 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = new ShaderCompExpNode("==", yyvsp[-2].expnode, yyvsp[0].expnode)
                ;
    break;}
case 60:
#line 518 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = new ShaderCompExpNode("!=", yyvsp[-2].expnode, yyvsp[0].expnode)
                ;
    break;}
case 61:
#line 523 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = new ShaderAssExpNode(yyvsp[-2].idexpnode, yyvsp[0].expnode)
                ;
    break;}
case 62:
#line 528 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  ShaderIdExpNode* temp1 = new ShaderIdExpNode(yyvsp[-2].idexpnode);
                  ShaderExpNode* temp2 = new ShaderArithExpNode('/', yyvsp[-2].idexpnode, yyvsp[0].expnode);
                  yyval.expnode = new ShaderAssExpNode(temp1, temp2)
                ;
    break;}
case 63:
#line 535 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  ShaderIdExpNode* temp1 = new ShaderIdExpNode(yyvsp[-2].idexpnode);
                  ShaderExpNode* temp2 = new ShaderArithExpNode('-', yyvsp[-2].idexpnode, yyvsp[0].expnode);
                  yyval.expnode = new ShaderAssExpNode(temp1, temp2)
                ;
    break;}
case 64:
#line 542 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  ShaderIdExpNode* temp1 = new ShaderIdExpNode(yyvsp[-2].idexpnode);
                  ShaderExpNode* temp2 = new ShaderArithExpNode('+', yyvsp[-2].idexpnode,yyvsp[0].expnode);
                  yyval.expnode = new ShaderAssExpNode(temp1, temp2)
                ;
    break;}
case 65:
#line 549 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  ShaderIdExpNode* temp1 = new ShaderIdExpNode(yyvsp[-2].idexpnode);                
                  ShaderExpNode* temp2 = new ShaderArithExpNode('%', yyvsp[-2].idexpnode, yyvsp[0].expnode);
                  yyval.expnode = new ShaderAssExpNode(temp1, temp2)
                ;
    break;}
case 66:
#line 556 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  ShaderIdExpNode* temp1 = new ShaderIdExpNode(yyvsp[-2].idexpnode);
                  ShaderExpNode* temp2 = new ShaderArithExpNode('*', yyvsp[-2].idexpnode, yyvsp[0].expnode);
                  yyval.expnode = new ShaderAssExpNode(temp1, temp2)
                ;
    break;}
case 67:
#line 564 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = new ShaderRealValueNode(yyvsp[0].number);
                ;
    break;}
case 68:
#line 568 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = new ShaderRealValueNode((Real)M_PI);
                ;
    break;}
case 69:
#line 573 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = new ShaderVecValueNode(yyvsp[-5].expnode, yyvsp[-3].expnode, yyvsp[-1].expnode);
                ;
    break;}
case 70:
#line 578 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                   yyval.expnode = new ShaderStringValueNode(yyvsp[0].id);
                ;
    break;}
case 71:
#line 584 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnodelist = NULL;
                ;
    break;}
case 72:
#line 589 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
		  yyval.expnodelist = new List<ShaderExpNode*>(1);
                  yyval.expnodelist->append(yyvsp[0].expnode);		  
        	;
    break;}
case 73:
#line 595 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnodelist = yyvsp[-2].expnodelist;
                  yyval.expnodelist->append(yyvsp[0].expnode);
		;
    break;}
case 74:
#line 602 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                   RCString errMsg;
                   yyval.idexpnode = new ShaderIdExpNode(errMsg, yyvsp[0].id);
                  if (!errMsg.isEmpty())
                    recoverableError(errMsg);                   
                 ;
    break;}
case 75:
#line 611 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
{
                  yyval.expnode = new ShaderParExpNode(yyvsp[-1].expnode);
                ;
    break;}
}

#line 811 "/usr/local/lib/bison.cc"
   /* the action file gets copied in in place of this dollarsign  */
  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YY_ShaderYacc_LSP_NEEDED
  yylsp -= yylen;
#endif

#if YY_ShaderYacc_DEBUG != 0
  if (YY_ShaderYacc_DEBUG_FLAG)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YY_ShaderYacc_LSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = YY_ShaderYacc_LLOC.first_line;
      yylsp->first_column = YY_ShaderYacc_LLOC.first_column;
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
      ++YY_ShaderYacc_NERRS;

#ifdef YY_ShaderYacc_ERROR_VERBOSE
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
	      YY_ShaderYacc_ERROR(msg);
	      free(msg);
	    }
	  else
	    YY_ShaderYacc_ERROR ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YY_ShaderYacc_ERROR_VERBOSE */
	YY_ShaderYacc_ERROR("parse error");
    }

  YYGOTO(yyerrlab1);
YYLABEL(yyerrlab1)   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (YY_ShaderYacc_CHAR == YYEOF)
	YYABORT;

#if YY_ShaderYacc_DEBUG != 0
      if (YY_ShaderYacc_DEBUG_FLAG)
	fprintf(stderr, "Discarding token %d (%s).\n", YY_ShaderYacc_CHAR, yytname[yychar1]);
#endif

      YY_ShaderYacc_CHAR = YYEMPTY;
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
#ifdef YY_ShaderYacc_LSP_NEEDED
  yylsp--;
#endif

#if YY_ShaderYacc_DEBUG != 0
  if (YY_ShaderYacc_DEBUG_FLAG)
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

#if YY_ShaderYacc_DEBUG != 0
  if (YY_ShaderYacc_DEBUG_FLAG)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = YY_ShaderYacc_LVAL;
#ifdef YY_ShaderYacc_LSP_NEEDED
  *++yylsp = YY_ShaderYacc_LLOC;
#endif

  yystate = yyn;
  YYGOTO(yynewstate);
/* end loop, in which YYGOTO may be used. */
  YYENDGOTO
}

/* END */

/* #line 1010 "/usr/local/lib/bison.cc" */
#line 2033 "ShaderYacc.C"
#line 615 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"
