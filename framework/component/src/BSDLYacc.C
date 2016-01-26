#define YY_BSDLYacc_h_included

/*  A Bison++ parser, made from /home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y  */

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
#line 85 "BSDLYacc.C"
#line 27 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"

#include <string.h>
#include <stdlib.h>
//						                         
// Semantic errors have to be handled the same way as syntatic errors  
// recognized by the parser. That's why calling the error reporting    
// function parseError isn't enough. Use the macro raiseError instead. 
//						                         
#define raiseError(msg) 		        \
  myErrorCount++; parseError(msg); YYERROR;	

#define generateError(parseObjectName, identifier)                              \
  if (!errMsg.isEmpty())			                                   \
    recoverableError(parseObjectName " "                                        \
		     + RCString(identifier->getIdentifier()) \
		     + ": " + errMsg);                                        \
  else						                          \
    recoverableError("unknown " parseObjectName " "                             \
		     + RCString(identifier->getIdentifier()) \
                       + " in namespaces "                                      \
		     + RCString(identifier->getNamespace()) + "::, ::")
#line 52 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"

#include "booga/base/List.h"
#include "booga/base/ListUtilities.h"
#include "booga/base/Stack.h"
#include "booga/base/Value.h"
#include "booga/base/RCString.h"
#include "booga/base/Name.h"
#include "booga/base/ScopedName.h"
#include "booga/object/Makeable.h"
#include "booga/object/ValueMakeable.h"
#include "booga/object/World.h"
#include "booga/object/Object2D.h"
#include "booga/object/Shared2D.h"
#include "booga/object/Object3D.h"
#include "booga/object/Shared3D.h"

struct StackFrame {
  StackFrame();
  StackFrame(const ScopedName& scopedName, const Name& theNamespace);
  int isGlobalFrame() const;
  ScopedName mySpecifier;
  Name myNamespace;
};

inline StackFrame::StackFrame()
: mySpecifier(Name()), myNamespace(Name()) 
{}

inline StackFrame::StackFrame(const ScopedName& scopedName, const Name& theNamespace)
: mySpecifier(scopedName), myNamespace(theNamespace) 
{}

inline int StackFrame::isGlobalFrame() const
{ 
  return ((RCString) mySpecifier.getIdentifier()).isEmpty(); 
}


#line 94 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
typedef union {
        Name*            id;
        ScopedName*      scopedName;
        Real             number;
        RCString*        string;
        Value*           value;
        List<Value*>*    valueList;
        Makeable*        makeable;
        List<Makeable*>* makeableList;
       } yy_BSDLYacc_stype;
#define YY_BSDLYacc_STYPE yy_BSDLYacc_stype
#define YY_BSDLYacc_DEBUG  1
#define YY_BSDLYacc_DEBUG_FLAG  myParserDebugFlag
#define YY_BSDLYacc_ERROR_VERBOSE 
#define YY_BSDLYacc_ERROR_BODY  =0
#define YY_BSDLYacc_ERROR  fatalError
#define YY_BSDLYacc_NERRS  myErrorCount
#define YY_BSDLYacc_LEX_BODY  =0
#define YY_BSDLYacc_LEX   scan
#define YY_BSDLYacc_LVAL  myTokenValue
#define YY_BSDLYacc_PARSE  parse
#define YY_BSDLYacc_PARSE_PARAM 
#define YY_BSDLYacc_CONSTRUCTOR_PARAM  
#define YY_BSDLYacc_CONSTRUCTOR_INIT  : myParserDebugFlag(0), myWorld(NULL)
#define YY_BSDLYacc_CONSTRUCTOR_CODE 
#define YY_BSDLYacc_MEMBERS  \
public:                                                          \
  void setWorldObject(World* world) { myWorld = world; }         \
  World* getWorldObject() const { return myWorld; }              \
private:                                                         \
  World* myWorld;                                                \
  Stack<StackFrame> myStackedFrames;                             \
private:                                                         \
  const Name& getCurrentIdentifier()                             \
  { return myStackedFrames.top().mySpecifier.getIdentifier(); }  \
  const ScopedName& getCurrentScopeName()                        \
  { return myStackedFrames.top().mySpecifier; }                  \
  const Name& getCurrentNamespace()                              \
  { return myStackedFrames.top().myNamespace; }                  \
  void setCurrentNamespace(const Name& theNamespace)             \
  { myStackedFrames.top().myNamespace = theNamespace; }          \
  virtual void recoverableError(const RCString& errorMsg) = 0;

#line 73 "/usr/local/lib/bison.cc"
/* %{ and %header{ and %union, during decl */
#define YY_BSDLYacc_BISON 1
#ifndef YY_BSDLYacc_COMPATIBILITY
#ifndef YY_USE_CLASS
#define  YY_BSDLYacc_COMPATIBILITY 1
#else
#define  YY_BSDLYacc_COMPATIBILITY 0
#endif
#endif

#if YY_BSDLYacc_COMPATIBILITY != 0
/* backward compatibility */
#ifdef YYLTYPE
#ifndef YY_BSDLYacc_LTYPE
#define YY_BSDLYacc_LTYPE YYLTYPE
#endif
#endif
#ifdef YYSTYPE
#ifndef YY_BSDLYacc_STYPE 
#define YY_BSDLYacc_STYPE YYSTYPE
#endif
#endif
#ifdef YYDEBUG
#ifndef YY_BSDLYacc_DEBUG
#define  YY_BSDLYacc_DEBUG YYDEBUG
#endif
#endif
#ifdef YY_BSDLYacc_STYPE
#ifndef yystype
#define yystype YY_BSDLYacc_STYPE
#endif
#endif
/* use goto to be compatible */
#ifndef YY_BSDLYacc_USE_GOTO
#define YY_BSDLYacc_USE_GOTO 1
#endif
#endif

/* use no goto to be clean in C++ */
#ifndef YY_BSDLYacc_USE_GOTO
#define YY_BSDLYacc_USE_GOTO 0
#endif

#ifndef YY_BSDLYacc_PURE

/* #line 117 "/usr/local/lib/bison.cc" */
#line 238 "BSDLYacc.C"

#line 117 "/usr/local/lib/bison.cc"
/*  YY_BSDLYacc_PURE */
#endif

/* section apres lecture def, avant lecture grammaire S2 */

/* #line 121 "/usr/local/lib/bison.cc" */
#line 247 "BSDLYacc.C"

#line 121 "/usr/local/lib/bison.cc"
/* prefix */
#ifndef YY_BSDLYacc_DEBUG

/* #line 123 "/usr/local/lib/bison.cc" */
#line 254 "BSDLYacc.C"

#line 123 "/usr/local/lib/bison.cc"
/* YY_BSDLYacc_DEBUG */
#endif


#ifndef YY_BSDLYacc_LSP_NEEDED

/* #line 128 "/usr/local/lib/bison.cc" */
#line 264 "BSDLYacc.C"

#line 128 "/usr/local/lib/bison.cc"
 /* YY_BSDLYacc_LSP_NEEDED*/
#endif



/* DEFAULT LTYPE*/
#ifdef YY_BSDLYacc_LSP_NEEDED
#ifndef YY_BSDLYacc_LTYPE
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

#define YY_BSDLYacc_LTYPE yyltype
#endif
#endif
/* DEFAULT STYPE*/
      /* We used to use `unsigned long' as YY_BSDLYacc_STYPE on MSDOS,
	 but it seems better to be consistent.
	 Most programs should declare their own type anyway.  */

#ifndef YY_BSDLYacc_STYPE
#define YY_BSDLYacc_STYPE int
#endif
/* DEFAULT MISCELANEOUS */
#ifndef YY_BSDLYacc_PARSE
#define YY_BSDLYacc_PARSE yyparse
#endif
#ifndef YY_BSDLYacc_LEX
#define YY_BSDLYacc_LEX yylex
#endif
#ifndef YY_BSDLYacc_LVAL
#define YY_BSDLYacc_LVAL yylval
#endif
#ifndef YY_BSDLYacc_LLOC
#define YY_BSDLYacc_LLOC yylloc
#endif
#ifndef YY_BSDLYacc_CHAR
#define YY_BSDLYacc_CHAR yychar
#endif
#ifndef YY_BSDLYacc_NERRS
#define YY_BSDLYacc_NERRS yynerrs
#endif
#ifndef YY_BSDLYacc_DEBUG_FLAG
#define YY_BSDLYacc_DEBUG_FLAG yydebug
#endif
#ifndef YY_BSDLYacc_ERROR
#define YY_BSDLYacc_ERROR yyerror
#endif
#ifndef YY_BSDLYacc_PARSE_PARAM
#ifndef __STDC__
#ifndef __cplusplus
#ifndef YY_USE_CLASS
#define YY_BSDLYacc_PARSE_PARAM
#ifndef YY_BSDLYacc_PARSE_PARAM_DEF
#define YY_BSDLYacc_PARSE_PARAM_DEF
#endif
#endif
#endif
#endif
#ifndef YY_BSDLYacc_PARSE_PARAM
#define YY_BSDLYacc_PARSE_PARAM void
#endif
#endif
#if YY_BSDLYacc_COMPATIBILITY != 0
/* backward compatibility */
#ifdef YY_BSDLYacc_LTYPE
#ifndef YYLTYPE
#define YYLTYPE YY_BSDLYacc_LTYPE
#else
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
#endif
#endif
#ifndef YYSTYPE
#define YYSTYPE YY_BSDLYacc_STYPE
#else
/* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
#endif
#ifdef YY_BSDLYacc_PURE
#ifndef YYPURE
#define YYPURE YY_BSDLYacc_PURE
#endif
#endif
#ifdef YY_BSDLYacc_DEBUG
#ifndef YYDEBUG
#define YYDEBUG YY_BSDLYacc_DEBUG 
#endif
#endif
#ifndef YY_BSDLYacc_ERROR_VERBOSE
#ifdef YYERROR_VERBOSE
#define YY_BSDLYacc_ERROR_VERBOSE YYERROR_VERBOSE
#endif
#endif
#ifndef YY_BSDLYacc_LSP_NEEDED
#ifdef YYLSP_NEEDED
#define YY_BSDLYacc_LSP_NEEDED YYLSP_NEEDED
#endif
#endif
#endif
#ifndef YY_USE_CLASS
/* TOKEN C */

/* #line 236 "/usr/local/lib/bison.cc" */
#line 377 "BSDLYacc.C"
#define	IDENTIFIER	258
#define	SCOPE	259
#define	NUMBER	260
#define	STRING	261
#define	tDefine	262
#define	tConstant	263
#define	tVerbatim	264
#define	tUsing	265
#define	tNamespace	266
#define	tUMINUS	267


#line 236 "/usr/local/lib/bison.cc"
 /* #defines tokens */
#else
/* CLASS */
#ifndef YY_BSDLYacc_CLASS
#define YY_BSDLYacc_CLASS BSDLYacc
#endif
#ifndef YY_BSDLYacc_INHERIT
#define YY_BSDLYacc_INHERIT
#endif
#ifndef YY_BSDLYacc_MEMBERS
#define YY_BSDLYacc_MEMBERS 
#endif
#ifndef YY_BSDLYacc_LEX_BODY
#define YY_BSDLYacc_LEX_BODY  
#endif
#ifndef YY_BSDLYacc_ERROR_BODY
#define YY_BSDLYacc_ERROR_BODY  
#endif
#ifndef YY_BSDLYacc_CONSTRUCTOR_PARAM
#define YY_BSDLYacc_CONSTRUCTOR_PARAM
#endif
#ifndef YY_BSDLYacc_CONSTRUCTOR_CODE
#define YY_BSDLYacc_CONSTRUCTOR_CODE
#endif
#ifndef YY_BSDLYacc_CONSTRUCTOR_INIT
#define YY_BSDLYacc_CONSTRUCTOR_INIT
#endif
/* choose between enum and const */
#ifndef YY_BSDLYacc_USE_CONST_TOKEN
#define YY_BSDLYacc_USE_CONST_TOKEN 0
/* yes enum is more compatible with flex,  */
/* so by default we use it */ 
#endif
#if YY_BSDLYacc_USE_CONST_TOKEN != 0
#ifndef YY_BSDLYacc_ENUM_TOKEN
#define YY_BSDLYacc_ENUM_TOKEN yy_BSDLYacc_enum_token
#endif
#endif

class YY_BSDLYacc_CLASS YY_BSDLYacc_INHERIT
{
public: 
#if YY_BSDLYacc_USE_CONST_TOKEN != 0
/* static const int token ... */

/* #line 280 "/usr/local/lib/bison.cc" */
#line 437 "BSDLYacc.C"
static const int IDENTIFIER;
static const int SCOPE;
static const int NUMBER;
static const int STRING;
static const int tDefine;
static const int tConstant;
static const int tVerbatim;
static const int tUsing;
static const int tNamespace;
static const int tUMINUS;


#line 280 "/usr/local/lib/bison.cc"
 /* decl const */
#else
enum YY_BSDLYacc_ENUM_TOKEN { YY_BSDLYacc_NULL_TOKEN=0

/* #line 283 "/usr/local/lib/bison.cc" */
#line 456 "BSDLYacc.C"
	,IDENTIFIER=258
	,SCOPE=259
	,NUMBER=260
	,STRING=261
	,tDefine=262
	,tConstant=263
	,tVerbatim=264
	,tUsing=265
	,tNamespace=266
	,tUMINUS=267


#line 283 "/usr/local/lib/bison.cc"
 /* enum token */
     }; /* end of enum declaration */
#endif
public:
 int YY_BSDLYacc_PARSE (YY_BSDLYacc_PARSE_PARAM);
 virtual void YY_BSDLYacc_ERROR(char *msg) YY_BSDLYacc_ERROR_BODY;
#ifdef YY_BSDLYacc_PURE
#ifdef YY_BSDLYacc_LSP_NEEDED
 virtual int  YY_BSDLYacc_LEX (YY_BSDLYacc_STYPE *YY_BSDLYacc_LVAL,YY_BSDLYacc_LTYPE *YY_BSDLYacc_LLOC) YY_BSDLYacc_LEX_BODY;
#else
 virtual int  YY_BSDLYacc_LEX (YY_BSDLYacc_STYPE *YY_BSDLYacc_LVAL) YY_BSDLYacc_LEX_BODY;
#endif
#else
 virtual int YY_BSDLYacc_LEX() YY_BSDLYacc_LEX_BODY;
 YY_BSDLYacc_STYPE YY_BSDLYacc_LVAL;
#ifdef YY_BSDLYacc_LSP_NEEDED
 YY_BSDLYacc_LTYPE YY_BSDLYacc_LLOC;
#endif
 int   YY_BSDLYacc_NERRS;
 int    YY_BSDLYacc_CHAR;
#endif
#if YY_BSDLYacc_DEBUG != 0
 int YY_BSDLYacc_DEBUG_FLAG;   /*  nonzero means print parse trace     */
#endif
public:
 YY_BSDLYacc_CLASS(YY_BSDLYacc_CONSTRUCTOR_PARAM);
public:
 YY_BSDLYacc_MEMBERS 
};
/* other declare folow */
#if YY_BSDLYacc_USE_CONST_TOKEN != 0

/* #line 314 "/usr/local/lib/bison.cc" */
#line 503 "BSDLYacc.C"
const int YY_BSDLYacc_CLASS::IDENTIFIER=258;
const int YY_BSDLYacc_CLASS::SCOPE=259;
const int YY_BSDLYacc_CLASS::NUMBER=260;
const int YY_BSDLYacc_CLASS::STRING=261;
const int YY_BSDLYacc_CLASS::tDefine=262;
const int YY_BSDLYacc_CLASS::tConstant=263;
const int YY_BSDLYacc_CLASS::tVerbatim=264;
const int YY_BSDLYacc_CLASS::tUsing=265;
const int YY_BSDLYacc_CLASS::tNamespace=266;
const int YY_BSDLYacc_CLASS::tUMINUS=267;


#line 314 "/usr/local/lib/bison.cc"
 /* const YY_BSDLYacc_CLASS::token */
#endif
/*apres const  */
YY_BSDLYacc_CLASS::YY_BSDLYacc_CLASS(YY_BSDLYacc_CONSTRUCTOR_PARAM) YY_BSDLYacc_CONSTRUCTOR_INIT
{
#if YY_BSDLYacc_DEBUG != 0
YY_BSDLYacc_DEBUG_FLAG=0;
#endif
YY_BSDLYacc_CONSTRUCTOR_CODE;
};
#endif

/* #line 325 "/usr/local/lib/bison.cc" */
#line 530 "BSDLYacc.C"


#define	YYFINAL		76
#define	YYFLAG		-32768
#define	YYNTBASE	25

#define YYTRANSLATE(x) ((unsigned)(x) <= 267 ? yytranslate[x] : 43)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    21,
    22,    14,    12,    20,    13,     2,    15,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,    17,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    23,     2,    24,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    18,     2,    19,     2,     2,     2,     2,     2,
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
     6,     7,     8,     9,    10,    11,    16
};

#if YY_BSDLYacc_DEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     5,     8,    11,    13,    15,    19,    24,
    29,    31,    34,    36,    40,    45,    46,    51,    56,    60,
    62,    66,    67,    69,    70,    72,    78,    80,    82,    84,
    86,    88,    90,    94,    96,    98,   101,   105,   109,   113,
   117,   121,   126
};

static const short yyrhs[] = {    -1,
    26,    27,     0,     0,    27,    28,     0,    27,     1,     0,
    32,     0,    29,     0,     7,    41,    32,     0,     7,     3,
    11,    17,     0,     8,    41,    37,    17,     0,    32,     0,
    30,    32,     0,    17,     0,    18,    30,    19,     0,    18,
    30,    19,    17,     0,     0,    41,    36,    33,    31,     0,
    41,     9,    40,    31,     0,    10,     3,    17,     0,    37,
     0,    34,    20,    37,     0,     0,    34,     0,     0,    37,
     0,    21,    34,    20,    37,    22,     0,    38,     0,    39,
     0,    40,     0,    41,     0,    42,     0,     5,     0,    23,
    34,    24,     0,     6,     0,     3,     0,     4,     3,     0,
    21,    37,    22,     0,    37,    12,    37,     0,    37,    13,
    37,     0,    37,    14,    37,     0,    37,    15,    37,     0,
    41,    21,    35,    22,     0,    13,    37,     0
};

#endif

#if YY_BSDLYacc_DEBUG != 0
static const short yyrline[] = { 0,
   168,   172,   174,   175,   179,   182,   191,   196,   218,   226,
   242,   251,   265,   269,   273,   279,   284,   338,   343,   353,
   358,   365,   369,   375,   379,   384,   391,   395,   399,   403,
   426,   432,   438,   520,   527,   532,   544,   548,   554,   560,
   566,   572,   595
};

static const char * const yytname[] = {   "$","error","$illegal.","IDENTIFIER",
"SCOPE","NUMBER","STRING","tDefine","tConstant","tVerbatim","tUsing","tNamespace",
"'+'","'-'","'*'","'/'","tUMINUS","';'","'{'","'}'","','","'('","')'","'['",
"']'","Entry","@1","World","WorldElement","Definition","Specifiers","OptSpecifiers",
"Specifier","@2","Values","OptValues","OptValueList","Value","RealValue","VectorValue",
"StringValue","Identifier","Expression",""
};
#endif

static const short yyr1[] = {     0,
    26,    25,    27,    27,    27,    28,    28,    29,    29,    29,
    30,    30,    31,    31,    31,    33,    32,    32,    32,    34,
    34,    35,    35,    36,    36,    36,    37,    37,    37,    37,
    37,    38,    39,    40,    41,    41,    42,    42,    42,    42,
    42,    42,    42
};

static const short yyr2[] = {     0,
     0,     2,     0,     2,     2,     1,     1,     3,     4,     4,
     1,     2,     1,     3,     4,     0,     4,     4,     3,     1,
     3,     0,     1,     0,     1,     5,     1,     1,     1,     1,
     1,     1,     3,     1,     1,     2,     3,     3,     3,     3,
     3,     4,     2
};

static const short yydefact[] = {     1,
     3,     0,     5,    35,     0,     0,     0,     0,     4,     7,
     6,    24,    36,    35,     0,     0,     0,    32,    34,     0,
     0,     0,     0,    16,    25,    27,    28,    29,    30,    31,
     0,     8,     0,     0,    19,     0,    43,     0,    20,     0,
    20,     0,     0,     0,     0,     0,    22,     9,     0,    10,
    13,     0,    18,     0,    37,     0,    33,    17,    38,    39,
    40,    41,    23,     0,     0,    11,    21,    21,    42,    14,
    12,    26,    15,     0,     0,     0
};

static const short yydefgoto[] = {    74,
     1,     2,     9,    10,    65,    53,    11,    42,    38,    64,
    24,    41,    26,    27,    28,    29,    30
};

static const short yypact[] = {-32768,
-32768,    57,-32768,-32768,     4,    13,    27,     7,-32768,-32768,
-32768,    16,-32768,    15,    37,    49,    11,-32768,-32768,    26,
    49,    49,    49,-32768,    82,-32768,-32768,-32768,    24,-32768,
    39,-32768,    49,    76,-32768,    25,-32768,    46,    61,    -6,
    82,    25,    49,    49,    49,    49,    49,-32768,    61,-32768,
-32768,    37,-32768,    49,-32768,    49,-32768,-32768,    34,    34,
-32768,-32768,    48,    47,     5,-32768,    65,    82,-32768,    42,
-32768,-32768,-32768,    71,    81,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,    40,   -14,-32768,   -20,-32768,
-32768,   -10,-32768,-32768,    64,    -2,-32768
};


#define	YYLAST		97


static const short yytable[] = {    12,
    32,    25,    40,    15,    16,    34,    13,     4,     5,    17,
    37,    39,    12,    56,     8,    14,     5,    57,     4,     5,
    18,    19,    49,    70,    20,    31,    63,    35,    21,     4,
     5,    19,    59,    60,    61,    62,    22,    66,    23,     4,
     5,    51,    52,    67,    47,    68,     8,    45,    46,    12,
    71,     4,     5,    18,    19,    48,    -2,     3,    73,     4,
     5,    21,    12,     6,     7,    54,     8,    56,    69,    33,
    75,    23,    43,    44,    45,    46,    43,    44,    45,    46,
    76,    58,    55,    36,     0,     0,    72,    43,    44,    45,
    46,     0,    50,    43,    44,    45,    46
};

static const short yycheck[] = {     2,
    15,    12,    23,     6,     7,    16,     3,     3,     4,     3,
    21,    22,    15,    20,    10,     3,     4,    24,     3,     4,
     5,     6,    33,    19,     9,    11,    47,    17,    13,     3,
     4,     6,    43,    44,    45,    46,    21,    52,    23,     3,
     4,    17,    18,    54,    21,    56,    10,    14,    15,    52,
    65,     3,     4,     5,     6,    17,     0,     1,    17,     3,
     4,    13,    65,     7,     8,    20,    10,    20,    22,    21,
     0,    23,    12,    13,    14,    15,    12,    13,    14,    15,
     0,    42,    22,    20,    -1,    -1,    22,    12,    13,    14,
    15,    -1,    17,    12,    13,    14,    15
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

#if YY_BSDLYacc_USE_GOTO != 0
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

#ifdef YY_BSDLYacc_LSP_NEEDED
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
#define yyclearin       (YY_BSDLYacc_CHAR = YYEMPTY)
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
  if (YY_BSDLYacc_CHAR == YYEMPTY && yylen == 1)                               \
    { YY_BSDLYacc_CHAR = (token), YY_BSDLYacc_LVAL = (value);                 \
      yychar1 = YYTRANSLATE (YY_BSDLYacc_CHAR);                                \
      YYPOPSTACK;                                               \
      YYGOTO(yybackup);                                            \
    }                                                           \
  else                                                          \
    { YY_BSDLYacc_ERROR ("syntax error: cannot back up"); YYERROR; }   \
while (0)

#define YYTERROR        1
#define YYERRCODE       256

#ifndef YY_BSDLYacc_PURE
/* UNPURE */
#define YYLEX           YY_BSDLYacc_LEX()
#ifndef YY_USE_CLASS
/* If nonreentrant, and not class , generate the variables here */
int     YY_BSDLYacc_CHAR;                      /*  the lookahead symbol        */
YY_BSDLYacc_STYPE      YY_BSDLYacc_LVAL;              /*  the semantic value of the */
				/*  lookahead symbol    */
int YY_BSDLYacc_NERRS;                 /*  number of parse errors so far */
#ifdef YY_BSDLYacc_LSP_NEEDED
YY_BSDLYacc_LTYPE YY_BSDLYacc_LLOC;   /*  location data for the lookahead     */
			/*  symbol                              */
#endif
#endif


#else
/* PURE */
#ifdef YY_BSDLYacc_LSP_NEEDED
#define YYLEX           YY_BSDLYacc_LEX(&YY_BSDLYacc_LVAL, &YY_BSDLYacc_LLOC)
#else
#define YYLEX           YY_BSDLYacc_LEX(&YY_BSDLYacc_LVAL)
#endif
#endif
#ifndef YY_USE_CLASS
#if YY_BSDLYacc_DEBUG != 0
int YY_BSDLYacc_DEBUG_FLAG;                    /*  nonzero means print parse trace     */
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
 YY_BSDLYacc_CLASS::
#endif
     YY_BSDLYacc_PARSE(YY_BSDLYacc_PARSE_PARAM)
#ifndef __STDC__
#ifndef __cplusplus
#ifndef YY_USE_CLASS
/* parameter definition without protypes */
YY_BSDLYacc_PARSE_PARAM_DEF
#endif
#endif
#endif
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YY_BSDLYacc_STYPE *yyvsp;
  int yyerrstatus;      /*  number of tokens to shift before error messages enabled */
  int yychar1=0;          /*  lookahead token as an internal (translated) token number */

  short yyssa[YYINITDEPTH];     /*  the state stack                     */
  YY_BSDLYacc_STYPE yyvsa[YYINITDEPTH];        /*  the semantic value stack            */

  short *yyss = yyssa;          /*  refer to the stacks thru separate pointers */
  YY_BSDLYacc_STYPE *yyvs = yyvsa;     /*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YY_BSDLYacc_LSP_NEEDED
  YY_BSDLYacc_LTYPE yylsa[YYINITDEPTH];        /*  the location stack                  */
  YY_BSDLYacc_LTYPE *yyls = yylsa;
  YY_BSDLYacc_LTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YY_BSDLYacc_PURE
  int YY_BSDLYacc_CHAR;
  YY_BSDLYacc_STYPE YY_BSDLYacc_LVAL;
  int YY_BSDLYacc_NERRS;
#ifdef YY_BSDLYacc_LSP_NEEDED
  YY_BSDLYacc_LTYPE YY_BSDLYacc_LLOC;
#endif
#endif

  YY_BSDLYacc_STYPE yyval;             /*  the variable used to return         */
				/*  semantic values from the action     */
				/*  routines                            */

  int yylen;
/* start loop, in which YYGOTO may be used. */
YYBEGINGOTO

#if YY_BSDLYacc_DEBUG != 0
  if (YY_BSDLYacc_DEBUG_FLAG)
    fprintf(stderr, "Starting parse\n");
#endif
  yystate = 0;
  yyerrstatus = 0;
  YY_BSDLYacc_NERRS = 0;
  YY_BSDLYacc_CHAR = YYEMPTY;          /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YY_BSDLYacc_LSP_NEEDED
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
      YY_BSDLYacc_STYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YY_BSDLYacc_LSP_NEEDED
      YY_BSDLYacc_LTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YY_BSDLYacc_LSP_NEEDED
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
#ifdef YY_BSDLYacc_LSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  YY_BSDLYacc_ERROR("parser stack overflow");
	  __ALLOCA_return(2);
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) __ALLOCA_alloca (yystacksize * sizeof (*yyssp));
      __yy_bcopy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      __ALLOCA_free(yyss1,yyssa);
      yyvs = (YY_BSDLYacc_STYPE *) __ALLOCA_alloca (yystacksize * sizeof (*yyvsp));
      __yy_bcopy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
      __ALLOCA_free(yyvs1,yyvsa);
#ifdef YY_BSDLYacc_LSP_NEEDED
      yyls = (YY_BSDLYacc_LTYPE *) __ALLOCA_alloca (yystacksize * sizeof (*yylsp));
      __yy_bcopy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
      __ALLOCA_free(yyls1,yylsa);
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YY_BSDLYacc_LSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YY_BSDLYacc_DEBUG != 0
      if (YY_BSDLYacc_DEBUG_FLAG)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YY_BSDLYacc_DEBUG != 0
  if (YY_BSDLYacc_DEBUG_FLAG)
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

  if (YY_BSDLYacc_CHAR == YYEMPTY)
    {
#if YY_BSDLYacc_DEBUG != 0
      if (YY_BSDLYacc_DEBUG_FLAG)
	fprintf(stderr, "Reading a token: ");
#endif
      YY_BSDLYacc_CHAR = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (YY_BSDLYacc_CHAR <= 0)           /* This means end of input. */
    {
      yychar1 = 0;
      YY_BSDLYacc_CHAR = YYEOF;                /* Don't call YYLEX any more */

#if YY_BSDLYacc_DEBUG != 0
      if (YY_BSDLYacc_DEBUG_FLAG)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(YY_BSDLYacc_CHAR);

#if YY_BSDLYacc_DEBUG != 0
      if (YY_BSDLYacc_DEBUG_FLAG)
	{
	  fprintf (stderr, "Next token is %d (%s", YY_BSDLYacc_CHAR, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, YY_BSDLYacc_CHAR, YY_BSDLYacc_LVAL);
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

#if YY_BSDLYacc_DEBUG != 0
  if (YY_BSDLYacc_DEBUG_FLAG)
    fprintf(stderr, "Shifting token %d (%s), ", YY_BSDLYacc_CHAR, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (YY_BSDLYacc_CHAR != YYEOF)
    YY_BSDLYacc_CHAR = YYEMPTY;

  *++yyvsp = YY_BSDLYacc_LVAL;
#ifdef YY_BSDLYacc_LSP_NEEDED
  *++yylsp = YY_BSDLYacc_LLOC;
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

#if YY_BSDLYacc_DEBUG != 0
  if (YY_BSDLYacc_DEBUG_FLAG)
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
#line 1181 "BSDLYacc.C"

  switch (yyn) {

case 1:
#line 168 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{ 
                 myStackedFrames.push(StackFrame()); 
               ;
    break;}
case 4:
#line 176 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
                 yyerrok;
               ;
    break;}
case 6:
#line 183 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
		RCString errMsg;
		if (yyvsp[0].makeable)
		  if (!myWorld->setSpecifier(errMsg, yyvsp[0].makeable)) {
		    recoverableError(errMsg);
		    delete yyvsp[0].makeable;
		  }
	      ;
    break;}
case 8:
#line 197 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
	       if (yyvsp[0].makeable) {
		 Makeable* newMakeable = yyvsp[0].makeable;

		 Object3D* object3D = dynamic_cast(Object3D, yyvsp[0].makeable);
		 if (object3D != NULL) 
		   newMakeable = new Shared3D(object3D, (RCString)yyvsp[-1].scopedName->getIdentifier()); // !!! bisher *$2
		 else {
		   Object2D* object2D = dynamic_cast(Object2D, yyvsp[0].makeable);
		   if (object2D != NULL)
		     newMakeable = new Shared2D(object2D, (RCString)yyvsp[-1].scopedName->getIdentifier());
		 }
		 
		 RCString errMsg;
		 if (!Makeable::registerExemplar(errMsg, *yyvsp[-1].scopedName, newMakeable)) {
		   recoverableError("definition failed: " + errMsg);
		   delete newMakeable;
		 }
	       }
	       delete yyvsp[-1].scopedName;
	     ;
    break;}
case 9:
#line 219 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
	       if (!Makeable::createNamespace(*yyvsp[-2].id))
		 recoverableError("namespace " + RCString(*yyvsp[-2].id) + 
				  " already exists");

	       delete yyvsp[-2].id;
	     ;
    break;}
case 10:
#line 227 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
	       Makeable* newConstant = new ValueMakeable(*yyvsp[-1].value);
	       RCString errMsg;
	       if (!Makeable::registerExemplar(errMsg, *yyvsp[-2].scopedName, newConstant)) {
		 recoverableError("const definition failed: " + errMsg);
		 delete newConstant;
	       }

	       delete yyvsp[-2].scopedName;
	       delete yyvsp[-1].value;
	     ;
    break;}
case 11:
#line 243 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
	       if (yyvsp[0].makeable != NULL) {
		 yyval.makeableList = new List<Makeable*>(1);
		 yyval.makeableList->append(yyvsp[0].makeable);
	       }
	       else
		 yyval.makeableList = NULL;
	    ;
    break;}
case 12:
#line 252 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
	       if (yyvsp[-1].makeableList != NULL)
		 yyval.makeableList = yyvsp[-1].makeableList;
	       else if (yyvsp[0].makeable != NULL)
		 yyval.makeableList = new List<Makeable*>(1);
	       else
		 yyval.makeableList = NULL;

	       if (yyvsp[0].makeable != NULL)
		 yyval.makeableList->append(yyvsp[0].makeable);
	     ;
    break;}
case 13:
#line 266 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
		  yyval.makeableList = NULL;
                ;
    break;}
case 14:
#line 270 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
		  yyval.makeableList = yyvsp[-1].makeableList;
                ;
    break;}
case 15:
#line 274 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
 		  yyval.makeableList = yyvsp[-2].makeableList;
                ;
    break;}
case 16:
#line 280 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
	     myStackedFrames.push(StackFrame(*yyvsp[-1].scopedName, yyvsp[-1].scopedName->getNamespace()));
	   ;
    break;}
case 17:
#line 284 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{	
              myStackedFrames.pop();
	     RCString errMsg;

	     yyval.makeable = Makeable::make(errMsg, *yyvsp[-3].scopedName, yyvsp[-2].valueList);
	     if (yyval.makeable == NULL) {
                if (!errMsg.isEmpty()) {
		recoverableError("specifier " + 
                                   RCString((RCString)yyvsp[-3].scopedName->getIdentifier()) +
				  ": " + errMsg);
                }
                else {
		if (!myStackedFrames.top().isGlobalFrame()) {
		  //
		  // We didn't find the identifier neither in the current,
		  // nor in the global namespace. Now let's look, if it
		  // is an attribute of a specifier. (Each specifier has
                    // its own scope !)
		  //
		  yyval.makeable = Makeable::make(
                           errMsg, 
                           ScopedName(RCString((RCString)
                                      yyvsp[-3].scopedName->getNamespace()) + "::"  +
                                      getCurrentIdentifier(),
                                      RCString(yyvsp[-3].scopedName->getIdentifier())), 
                           yyvsp[-2].valueList);
                   }
                             
                   if (yyval.makeable == NULL)
		    generateError("specifier", yyvsp[-3].scopedName);
                 }
	      }
	      
               //
	      // Set additional specifiers
	      //
	      if (yyval.makeable != NULL && yyvsp[0].makeableList != NULL) {
		for (long i=0; i<yyvsp[0].makeableList->count(); i++)
		  if (!yyval.makeable->setSpecifier(errMsg, yyvsp[0].makeableList->item(i))) {
		    recoverableError(errMsg);
		    delete yyvsp[0].makeableList->item(i);
		  }
                  delete yyvsp[0].makeableList;
	      }
	      else if (yyvsp[0].makeableList != NULL)
                 deleteList(yyvsp[0].makeableList);
               //
	      // clean up
	      //
	      delete yyvsp[-3].scopedName; 
	      if (yyvsp[-2].valueList != NULL)
                 deleteList(yyvsp[-2].valueList);
	      // $4 is alreay deleted!
	   ;
    break;}
case 18:
#line 339 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
	      yyval.makeable = NULL;
	      recoverableError("verbatim not yet implemented");
	   ;
    break;}
case 19:
#line 344 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
	      yyval.makeable = NULL;
	      setCurrentNamespace(*yyvsp[-1].id);
	      if (yyvsp[-1].id) delete yyvsp[-1].id;
	   ;
    break;}
case 20:
#line 354 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
	  yyval.valueList = new List<Value*>(1);
	  yyval.valueList->append(yyvsp[0].value);
	;
    break;}
case 21:
#line 359 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
	  yyval.valueList = yyvsp[-2].valueList;
	  yyval.valueList->append(yyvsp[0].value);
	;
    break;}
case 22:
#line 366 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
	      yyval.valueList = NULL;
	   ;
    break;}
case 23:
#line 370 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
	      yyval.valueList = yyvsp[0].valueList;
	   ;
    break;}
case 24:
#line 376 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
		yyval.valueList = NULL;
	      ;
    break;}
case 25:
#line 380 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
		yyval.valueList = new List<Value*>(1);
		yyval.valueList->append(yyvsp[0].value);
	      ;
    break;}
case 26:
#line 385 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
		yyval.valueList = yyvsp[-3].valueList;
		yyval.valueList->append(yyvsp[-1].value);
	      ;
    break;}
case 27:
#line 392 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{ 
	 yyval.value = yyvsp[0].value; 
        ;
    break;}
case 28:
#line 396 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{ 
	 yyval.value = yyvsp[0].value; 
        ;
    break;}
case 29:
#line 400 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{ 
	 yyval.value = yyvsp[0].value; 
        ;
    break;}
case 30:
#line 404 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{ 
	  RCString errMsg;
	  yyval.value = NULL;

	  Makeable* theValue = Makeable::make(errMsg, *yyvsp[0].scopedName, NULL);
	  if (theValue == NULL)
	    generateError("constant", yyvsp[0].scopedName);
	  else {
	    ValueMakeable* constValue = dynamic_cast(ValueMakeable, theValue);
	    if (constValue == NULL)
	      recoverableError(RCString((RCString)yyvsp[0].scopedName->getIdentifier()) + 
			       " not a value");
	    else
	      yyval.value = new Value(constValue->getValue());
	  }

	  if (yyval.value == NULL) 
             yyval.value = new Value();
	  if (theValue != NULL) 
             delete theValue;
	  delete yyvsp[0].scopedName;
        ;
    break;}
case 31:
#line 427 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{ 
	 yyval.value = yyvsp[0].value; 
        ;
    break;}
case 32:
#line 433 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
	     yyval.value = new Value(yyvsp[0].number);
	   ;
    break;}
case 33:
#line 439 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
		int valueNumbers = (yyvsp[-1].valueList ? yyvsp[-1].valueList->count() : 0);

		yyval.value = NULL;

		switch (valueNumbers) {
  		  case 2: {
		    Real r0, r1;
		    //
		    // First try to build a Vector2D out of 2 Reals :
		    //
		    if (!yyvsp[-1].valueList->item(0)->toReal(r0) || !yyvsp[-1].valueList->item(1)->toReal(r1)) {
		      //
		      // Nope ! Now try to build a Matrix2D out of 2 Vector2D :
		      //
		      Vector2D v0, v1;
		      if (!yyvsp[-1].valueList->item(0)->toVector2D(v0) || 
			  !yyvsp[-1].valueList->item(1)->toVector2D(v1))
			recoverableError("type/number mismatch in vector/matrix");
		      else // build a matrix2D
			yyval.value = new Value(TransMatrix2D(v0,v1));
		    } else // build a vector2D
		      yyval.value = new Value(r0, r1);
		    break;
		  }
		    
		    break;
		  case 3: {
		    Real r0, r1, r2;
		    //
		    // First try to build a Vector3D out of 3 Reals :
		    //
		    if (!yyvsp[-1].valueList->item(0)->toReal(r0) || !yyvsp[-1].valueList->item(1)->toReal(r1) ||
			!yyvsp[-1].valueList->item(2)->toReal(r2)) {
		      //
		      // Nope ! Now try to build a Matrix3D out of 3 Vector3D :
		      //
		      Vector3D v0, v1, v2;
		      if (!yyvsp[-1].valueList->item(0)->toVector3D(v0) || 
			  !yyvsp[-1].valueList->item(1)->toVector3D(v1) ||
			  !yyvsp[-1].valueList->item(2)->toVector3D(v2)) {
			//
			// Last try: Build a Matrix2D out of 3 Vectors2D
			//
		        Vector2D v0, v1, v2;
			if (!yyvsp[-1].valueList->item(0)->toVector2D(v0) || 
			    !yyvsp[-1].valueList->item(1)->toVector2D(v1) ||
			    !yyvsp[-1].valueList->item(2)->toVector2D(v2))
			  recoverableError("type/number mismatch in vector/matrix");
			else // build a matrix2D
			  yyval.value = new Value(TransMatrix2D(v0, v1, v2));
		      } else // build a matrix3D
			yyval.value = new Value(TransMatrix3D(v0, v1, v2));
		    } else // build a vector3D
		      yyval.value = new Value(r0, r1, r2);
		    break;
		  }
		  case 4: {
		    Vector3D v0, v1, v2, v3;
		    if (!yyvsp[-1].valueList->item(0)->toVector3D(v0) || !yyvsp[-1].valueList->item(1)->toVector3D(v1) ||
			!yyvsp[-1].valueList->item(2)->toVector3D(v2) || !yyvsp[-1].valueList->item(3)->toVector3D(v3)) 
		      recoverableError("type/number mismatch in vector/matrix");
		    else 
		      yyval.value = new Value(TransMatrix3D(v0,v1, v2, v3));
		    break;
		  }
		  default:
		    recoverableError("invalid number of elements in vector");
		    break;
		}

		if (!yyval.value) yyval.value = new Value(0,0,0);

		// 
                  // clean up ...
                  //
		if (yyvsp[-1].valueList)
                    deleteList(yyvsp[-1].valueList);
	      ;
    break;}
case 34:
#line 521 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
                yyval.value = new Value(*yyvsp[0].string);
                delete yyvsp[0].string;
	     ;
    break;}
case 35:
#line 528 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
	       yyval.scopedName = new ScopedName(getCurrentNamespace(), *yyvsp[0].id);
	       delete yyvsp[0].id;
	    ;
    break;}
case 36:
#line 533 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
	       if (((RCString)*yyvsp[-1].id).isEmpty()) 
		 yyval.scopedName = new ScopedName(*yyvsp[0].id); // global namespace
	       else
		 yyval.scopedName = new ScopedName(*yyvsp[-1].id, *yyvsp[0].id);

	       delete yyvsp[-1].id;
	       delete yyvsp[0].id;
	    ;
    break;}
case 37:
#line 545 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{ 
                yyval.value = yyvsp[-1].value; 
              ;
    break;}
case 38:
#line 549 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
                yyval.value = new Value(*yyvsp[-2].value + *yyvsp[0].value);
                delete yyvsp[-2].value; 
                delete yyvsp[0].value;
	     ;
    break;}
case 39:
#line 555 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
                yyval.value = new Value(*yyvsp[-2].value - *yyvsp[0].value);
                delete yyvsp[-2].value; 
                delete yyvsp[0].value;
              ;
    break;}
case 40:
#line 561 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
                yyval.value = new Value(*yyvsp[-2].value * *yyvsp[0].value);
                delete yyvsp[-2].value; 
                delete yyvsp[0].value;
              ;
    break;}
case 41:
#line 567 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
                yyval.value = new Value(*yyvsp[-2].value / *yyvsp[0].value);
                delete yyvsp[-2].value; 
                delete yyvsp[0].value;
              ;
    break;}
case 42:
#line 573 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
                RCString errMsg;
                yyval.value = NULL;

                Makeable* func = Makeable::make(errMsg, *yyvsp[-3].scopedName, yyvsp[-1].valueList);
                if (func == NULL) 
                  generateError("function", yyvsp[-3].scopedName);
                else {
                  ValueMakeable* funcValue = dynamic_cast(ValueMakeable, func);
                  if (funcValue == NULL) 
                    recoverableError(RCString(yyvsp[-3].scopedName->getIdentifier())
                		     + " not a function name");
                  else
                    yyval.value = new Value(funcValue->getValue());
                }

                if (yyval.value == NULL) 
                  yyval.value = new Value();
                if (func != NULL) delete func;
                if (yyvsp[-3].scopedName != NULL)   delete yyvsp[-3].scopedName;
                if (yyvsp[-1].valueList != NULL)   deleteList(yyvsp[-1].valueList);
              ;
    break;}
case 43:
#line 596 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
{
                yyval.value = new Value(- *yyvsp[0].value);
                delete yyvsp[0].value; 
	     ;
    break;}
}

#line 811 "/usr/local/lib/bison.cc"
   /* the action file gets copied in in place of this dollarsign  */
  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YY_BSDLYacc_LSP_NEEDED
  yylsp -= yylen;
#endif

#if YY_BSDLYacc_DEBUG != 0
  if (YY_BSDLYacc_DEBUG_FLAG)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YY_BSDLYacc_LSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = YY_BSDLYacc_LLOC.first_line;
      yylsp->first_column = YY_BSDLYacc_LLOC.first_column;
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
      ++YY_BSDLYacc_NERRS;

#ifdef YY_BSDLYacc_ERROR_VERBOSE
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
	      YY_BSDLYacc_ERROR(msg);
	      free(msg);
	    }
	  else
	    YY_BSDLYacc_ERROR ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YY_BSDLYacc_ERROR_VERBOSE */
	YY_BSDLYacc_ERROR("parse error");
    }

  YYGOTO(yyerrlab1);
YYLABEL(yyerrlab1)   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (YY_BSDLYacc_CHAR == YYEOF)
	YYABORT;

#if YY_BSDLYacc_DEBUG != 0
      if (YY_BSDLYacc_DEBUG_FLAG)
	fprintf(stderr, "Discarding token %d (%s).\n", YY_BSDLYacc_CHAR, yytname[yychar1]);
#endif

      YY_BSDLYacc_CHAR = YYEMPTY;
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
#ifdef YY_BSDLYacc_LSP_NEEDED
  yylsp--;
#endif

#if YY_BSDLYacc_DEBUG != 0
  if (YY_BSDLYacc_DEBUG_FLAG)
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

#if YY_BSDLYacc_DEBUG != 0
  if (YY_BSDLYacc_DEBUG_FLAG)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = YY_BSDLYacc_LVAL;
#ifdef YY_BSDLYacc_LSP_NEEDED
  *++yylsp = YY_BSDLYacc_LLOC;
#endif

  yystate = yyn;
  YYGOTO(yynewstate);
/* end loop, in which YYGOTO may be used. */
  YYENDGOTO
}

/* END */

/* #line 1010 "/usr/local/lib/bison.cc" */
#line 1860 "BSDLYacc.C"
#line 601 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/component/src/BSDLYacc.y"
