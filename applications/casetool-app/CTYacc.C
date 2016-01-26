#define YY_CTYacc_h_included

/*  A Bison parser, made from CTYacc.y  */


#line 1 "/Home/origin/matthey/lib/bison.cc"
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
#ifndef _MSDOS
#ifdef MSDOS
#define _MSDOS
#endif
#endif
/* turboc */
#ifdef __MSDOS__
#ifndef _MSDOS
#define _MSDOS
#endif
#endif

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc)
#include <alloca.h>
#else /* not sparc */
#if defined (_MSDOS)
#include <malloc.h>
#ifndef __TURBOC__
/* MS C runtime lib */
#define alloca _alloca
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
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

/* #line 70 "/Home/origin/matthey/lib/bison.cc" */
#line 24 "CTYacc.y"

#include <string.h>
#include <stdlib.h>
//						                         
// Semantic errors have to be handled the same way as syntatic errors  
// recognized by the parser. That's why calling the error reporting    
// function parseError isn't enough. Use the macro raiseError instead. 
//						                         
#define raiseError(msg) 		        \
  myErrorCount++; parseError(msg); YYERROR;	

#define generateError(parseObjectName, identifier)                        \
  if (!errMsg.isEmpty())			                          \
    recoverableError(parseObjectName " "                                  \
		     + RCString(identifier->getIdentifier())              \
		     + ": " + errMsg);                                    \
  else						                          \
    recoverableError("unknown " parseObjectName " "                       \
		     + RCString(identifier->getIdentifier())              \
                       + " in namespaces "                                \
		     + RCString(identifier->getNamespace()) + "::, ::")
#line 49 "CTYacc.y"

#include "booga/base/List.h"
#include "booga/base/ListUtilities.h"
#include "booga/base/Stack.h"
#include "booga/base/RCString.h"
#include "booga/base/PrimitiveTypes.h"
#include "booga/base/Report.h"
#include "booga/object/World2D.h"
#include "booga/object/Object2D.h"
#include "booga/object/Shared2D.h"
#include "CTClassDescription2D.h"
#include "CTParserUtils.h"


#line 67 "CTYacc.y"
typedef union {
  RCString* string;
} yy_CTYacc_stype;
#define YY_CTYacc_STYPE yy_CTYacc_stype
#define YY_CTYacc_DEBUG  1
#define YY_CTYacc_DEBUG_FLAG  myParserDebugFlag
#define YY_CTYacc_ERROR_VERBOSE 
#define YY_CTYacc_ERROR_BODY  =0
#define YY_CTYacc_ERROR  fatalError
#define YY_CTYacc_NERRS  myErrorCount
#define YY_CTYacc_LEX_BODY  =0
#define YY_CTYacc_LEX   scan
#define YY_CTYacc_LVAL  myTokenValue
#define YY_CTYacc_PARSE  parse
#define YY_CTYacc_PARSE_PARAM 
#define YY_CTYacc_CONSTRUCTOR_PARAM  
#define YY_CTYacc_CONSTRUCTOR_INIT  : myParserDebugFlag(0), myWorld(NULL)
#define YY_CTYacc_CONSTRUCTOR_CODE 
#define YY_CTYacc_MEMBERS                                                   \
public:                                                          \
  void setWorldObject(World2D* world) { myWorld = world; }       \
  World2D* getWorldObject() const { return myWorld; }            \
  void setVerboseFlag(const bool enable) { myParserVerboseFlag = enable; } \
private:                                                         \
  World2D* myWorld;                                              \
private:                                                         \
  virtual void recoverableError(const RCString& errorMsg) = 0;   \
  tProgramm aProgramm;                                           \
  tKlasse aKlasse;                                               \
  tKlassenMember aKlassenMember;                                 \
  tKlassenOperation aKlassenOperation;                           \
  tOperationsParameter aOperationsParameter;                     \
  tBasisKlasse aBasisKlasse;                                     \
  RCString myActualType;                                         \
  RCString myActualView;                                         \
  RCString myActualScope;                                        \
  RCString myActualPointer;                                      \
  bool myIsTemplate;                                             \
  bool myMemberIsTemplate;                                       \
  RCString myTemplateParameters;                                 \
  bool myIsVirtual;                                              \
  bool myParserVerboseFlag;                                      \
  Stack<tKlasse> myKlassenStack;                                 \
  Stack<RCString> myScopeStack;

#line 70 "/Home/origin/matthey/lib/bison.cc"
/* %{ and %header{ and %union, during decl */
#define YY_CTYacc_BISON 1
#ifndef YY_CTYacc_COMPATIBILITY
#ifndef YY_USE_CLASS
#define  YY_CTYacc_COMPATIBILITY 1
#else
#define  YY_CTYacc_COMPATIBILITY 0
#endif
#endif

#if YY_CTYacc_COMPATIBILITY != 0
/* backward compatibility */
#ifdef YYLTYPE
#ifndef YY_CTYacc_LTYPE
#define YY_CTYacc_LTYPE YYLTYPE
#endif
#endif
#ifdef YYSTYPE
#ifndef YY_CTYacc_STYPE 
#define YY_CTYacc_STYPE YYSTYPE
#endif
#endif
#ifdef YYDEBUG
#ifndef YY_CTYacc_DEBUG
#define  YY_CTYacc_DEBUG YYDEBUG
#endif
#endif
#ifdef YY_CTYacc_STYPE
#ifndef yystype
#define yystype YY_CTYacc_STYPE
#endif
#endif
#endif

#ifndef YY_CTYacc_PURE

/* #line 105 "/Home/origin/matthey/lib/bison.cc" */

#line 105 "/Home/origin/matthey/lib/bison.cc"
/*  YY_CTYacc_PURE */
#endif

/* section apres lecture def, avant lecture grammaire S2 */

/* #line 109 "/Home/origin/matthey/lib/bison.cc" */

#line 109 "/Home/origin/matthey/lib/bison.cc"
/* prefix */
#ifndef YY_CTYacc_DEBUG

/* #line 111 "/Home/origin/matthey/lib/bison.cc" */

#line 111 "/Home/origin/matthey/lib/bison.cc"
/* YY_CTYacc_DEBUG */
#endif


#ifndef YY_CTYacc_LSP_NEEDED

/* #line 116 "/Home/origin/matthey/lib/bison.cc" */

#line 116 "/Home/origin/matthey/lib/bison.cc"
 /* YY_CTYacc_LSP_NEEDED*/
#endif



/* DEFAULT LTYPE*/
#ifdef YY_CTYacc_LSP_NEEDED
#ifndef YY_CTYacc_LTYPE
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

#define YY_CTYacc_LTYPE yyltype
#endif
#endif
/* DEFAULT STYPE*/
      /* We used to use `unsigned long' as YY_CTYacc_STYPE on MSDOS,
	 but it seems better to be consistent.
	 Most programs should declare their own type anyway.  */

#ifndef YY_CTYacc_STYPE
#define YY_CTYacc_STYPE int
#endif
/* DEFAULT MISCELANEOUS */
#ifndef YY_CTYacc_PARSE
#define YY_CTYacc_PARSE yyparse
#endif
#ifndef YY_CTYacc_LEX
#define YY_CTYacc_LEX yylex
#endif
#ifndef YY_CTYacc_LVAL
#define YY_CTYacc_LVAL yylval
#endif
#ifndef YY_CTYacc_LLOC
#define YY_CTYacc_LLOC yylloc
#endif
#ifndef YY_CTYacc_CHAR
#define YY_CTYacc_CHAR yychar
#endif
#ifndef YY_CTYacc_NERRS
#define YY_CTYacc_NERRS yynerrs
#endif
#ifndef YY_CTYacc_DEBUG_FLAG
#define YY_CTYacc_DEBUG_FLAG yydebug
#endif
#ifndef YY_CTYacc_ERROR
#define YY_CTYacc_ERROR yyerror
#endif
#ifndef YY_CTYacc_PARSE_PARAM
#ifndef __STDC__
#ifndef __cplusplus
#ifndef YY_USE_CLASS
#define YY_CTYacc_PARSE_PARAM
#ifndef YY_CTYacc_PARSE_PARAM_DEF
#define YY_CTYacc_PARSE_PARAM_DEF
#endif
#endif
#endif
#endif
#ifndef YY_CTYacc_PARSE_PARAM
#define YY_CTYacc_PARSE_PARAM void
#endif
#endif
/* TOKEN C */
#if YY_CTYacc_COMPATIBILITY != 0
/* backward compatibility */
#ifdef YY_CTYacc_LTYPE
#ifndef YYLTYPE
#define YYLTYPE YY_CTYacc_LTYPE
#else
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
#endif
#endif
#ifndef YYSTYPE
#define YYSTYPE YY_CTYacc_STYPE
#else
/* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
#endif
#ifdef YY_CTYacc_PURE
#ifndef YYPURE
#define YYPURE YY_CTYacc_PURE
#endif
#endif
#ifdef YY_CTYacc_DEBUG
#ifndef YYDEBUG
#define YYDEBUG YY_CTYacc_DEBUG 
#endif
#endif
#ifndef YY_CTYacc_ERROR_VERBOSE
#ifdef YYERROR_VERBOSE
#define YY_CTYacc_ERROR_VERBOSE YYERROR_VERBOSE
#endif
#endif
#ifndef YY_CTYacc_LSP_NEEDED
#ifdef YYLSP_NEEDED
#define YY_CTYacc_LSP_NEEDED YYLSP_NEEDED
#endif
#endif


/* #line 223 "/Home/origin/matthey/lib/bison.cc" */
#define	tCLASS	258
#define	tSTRUCT	259
#define	tUNION	260
#define	tPRIVATE	261
#define	tPUBLIC	262
#define	tPROTECTED	263
#define	tVIRTUAL	264
#define	tPUREVIRTUAL	265
#define	tINLINE	266
#define	tEXPRESSION	267
#define	tCONSTEXPR	268
#define	tOPERATOR	269
#define	tCONST	270
#define	tSTATIC	271
#define	tFRIEND	272
#define	tENUM	273
#define	tVOLATILE	274
#define	tGELTUNGSBEREICHOPERATOR	275
#define	t3PUNKTE	276
#define	tKOMMA	277
#define	tIDENTIFIER	278
#define	tDOPPELPUNKT	279
#define	tTEMPLATE	280
#define	tANYTHINGELSE	281
#define	tCHAR	282
#define	tSHORT	283
#define	tINT	284
#define	tLONG	285
#define	tSIGNED	286
#define	tUNSIGNED	287
#define	tFLOAT	288
#define	tDOUBLE	289
#define	tVOID	290
#define	tAUTO	291
#define	tREGISTER	292
#define	tEXTERN	293
#define	tNEW	294
#define	tDELETE	295


#line 223 "/Home/origin/matthey/lib/bison.cc"
 /* #defines tokens */
#else
/* CLASS */
#ifndef YY_CTYacc_CLASS
#define YY_CTYacc_CLASS CTYacc
#endif
#ifndef YY_CTYacc_INHERIT
#define YY_CTYacc_INHERIT
#endif
#ifndef YY_CTYacc_MEMBERS
#define YY_CTYacc_MEMBERS 
#endif
#ifndef YY_CTYacc_LEX_BODY
#define YY_CTYacc_LEX_BODY  
#endif
#ifndef YY_CTYacc_ERROR_BODY
#define YY_CTYacc_ERROR_BODY  
#endif
#ifndef YY_CTYacc_CONSTRUCTOR_PARAM
#define YY_CTYacc_CONSTRUCTOR_PARAM
#endif
#ifndef YY_CTYacc_CONSTRUCTOR_CODE
#define YY_CTYacc_CONSTRUCTOR_CODE
#endif
#ifndef YY_CTYacc_CONSTRUCTOR_INIT
#define YY_CTYacc_CONSTRUCTOR_INIT
#endif

class YY_CTYacc_CLASS YY_CTYacc_INHERIT
{
public: /* static const int token ... */

/* #line 254 "/Home/origin/matthey/lib/bison.cc" */
static const int tCLASS;
static const int tSTRUCT;
static const int tUNION;
static const int tPRIVATE;
static const int tPUBLIC;
static const int tPROTECTED;
static const int tVIRTUAL;
static const int tPUREVIRTUAL;
static const int tINLINE;
static const int tEXPRESSION;
static const int tCONSTEXPR;
static const int tOPERATOR;
static const int tCONST;
static const int tSTATIC;
static const int tFRIEND;
static const int tENUM;
static const int tVOLATILE;
static const int tGELTUNGSBEREICHOPERATOR;
static const int t3PUNKTE;
static const int tKOMMA;
static const int tIDENTIFIER;
static const int tDOPPELPUNKT;
static const int tTEMPLATE;
static const int tANYTHINGELSE;
static const int tCHAR;
static const int tSHORT;
static const int tINT;
static const int tLONG;
static const int tSIGNED;
static const int tUNSIGNED;
static const int tFLOAT;
static const int tDOUBLE;
static const int tVOID;
static const int tAUTO;
static const int tREGISTER;
static const int tEXTERN;
static const int tNEW;
static const int tDELETE;


#line 254 "/Home/origin/matthey/lib/bison.cc"
 /* decl const */
public:
 int YY_CTYacc_PARSE (YY_CTYacc_PARSE_PARAM);
 virtual void YY_CTYacc_ERROR(char *msg) YY_CTYacc_ERROR_BODY;
#ifdef YY_CTYacc_PURE
#ifdef YY_CTYacc_LSP_NEEDED
 virtual int  YY_CTYacc_LEX (YY_CTYacc_STYPE *YY_CTYacc_LVAL,YY_CTYacc_LTYPE *YY_CTYacc_LLOC) YY_CTYacc_LEX_BODY;
#else
 virtual int  YY_CTYacc_LEX (YY_CTYacc_STYPE *YY_CTYacc_LVAL) YY_CTYacc_LEX_BODY;
#endif
#else
 virtual int YY_CTYacc_LEX() YY_CTYacc_LEX_BODY;
 YY_CTYacc_STYPE YY_CTYacc_LVAL;
#ifdef YY_CTYacc_LSP_NEEDED
 YY_CTYacc_LTYPE YY_CTYacc_LLOC;
#endif
 int   YY_CTYacc_NERRS;
 int    YY_CTYacc_CHAR;
#endif
#if YY_CTYacc_DEBUG != 0
 int YY_CTYacc_DEBUG_FLAG;   /*  nonzero means print parse trace     */
#endif
public:
 YY_CTYacc_CLASS(YY_CTYacc_CONSTRUCTOR_PARAM);
public:
 YY_CTYacc_MEMBERS 
};
/* other declare folow */

/* #line 282 "/Home/origin/matthey/lib/bison.cc" */
const int YY_CTYacc_CLASS::tCLASS=258;
const int YY_CTYacc_CLASS::tSTRUCT=259;
const int YY_CTYacc_CLASS::tUNION=260;
const int YY_CTYacc_CLASS::tPRIVATE=261;
const int YY_CTYacc_CLASS::tPUBLIC=262;
const int YY_CTYacc_CLASS::tPROTECTED=263;
const int YY_CTYacc_CLASS::tVIRTUAL=264;
const int YY_CTYacc_CLASS::tPUREVIRTUAL=265;
const int YY_CTYacc_CLASS::tINLINE=266;
const int YY_CTYacc_CLASS::tEXPRESSION=267;
const int YY_CTYacc_CLASS::tCONSTEXPR=268;
const int YY_CTYacc_CLASS::tOPERATOR=269;
const int YY_CTYacc_CLASS::tCONST=270;
const int YY_CTYacc_CLASS::tSTATIC=271;
const int YY_CTYacc_CLASS::tFRIEND=272;
const int YY_CTYacc_CLASS::tENUM=273;
const int YY_CTYacc_CLASS::tVOLATILE=274;
const int YY_CTYacc_CLASS::tGELTUNGSBEREICHOPERATOR=275;
const int YY_CTYacc_CLASS::t3PUNKTE=276;
const int YY_CTYacc_CLASS::tKOMMA=277;
const int YY_CTYacc_CLASS::tIDENTIFIER=278;
const int YY_CTYacc_CLASS::tDOPPELPUNKT=279;
const int YY_CTYacc_CLASS::tTEMPLATE=280;
const int YY_CTYacc_CLASS::tANYTHINGELSE=281;
const int YY_CTYacc_CLASS::tCHAR=282;
const int YY_CTYacc_CLASS::tSHORT=283;
const int YY_CTYacc_CLASS::tINT=284;
const int YY_CTYacc_CLASS::tLONG=285;
const int YY_CTYacc_CLASS::tSIGNED=286;
const int YY_CTYacc_CLASS::tUNSIGNED=287;
const int YY_CTYacc_CLASS::tFLOAT=288;
const int YY_CTYacc_CLASS::tDOUBLE=289;
const int YY_CTYacc_CLASS::tVOID=290;
const int YY_CTYacc_CLASS::tAUTO=291;
const int YY_CTYacc_CLASS::tREGISTER=292;
const int YY_CTYacc_CLASS::tEXTERN=293;
const int YY_CTYacc_CLASS::tNEW=294;
const int YY_CTYacc_CLASS::tDELETE=295;


#line 282 "/Home/origin/matthey/lib/bison.cc"
 /* const YY_CTYacc_CLASS::token */
/*apres const  */
YY_CTYacc_CLASS::YY_CTYacc_CLASS(YY_CTYacc_CONSTRUCTOR_PARAM) YY_CTYacc_CONSTRUCTOR_INIT
{
#if YY_CTYacc_DEBUG != 0
YY_CTYacc_DEBUG_FLAG=0;
#endif
YY_CTYacc_CONSTRUCTOR_CODE;
};
#endif

/* #line 292 "/Home/origin/matthey/lib/bison.cc" */


#define	YYFINAL		296
#define	YYFLAG		-32768
#define	YYNTBASE	62

#define YYTRANSLATE(x) ((unsigned)(x) <= 295 ? yytranslate[x] : 143)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    54,     2,     2,     2,    55,    49,     2,    52,
    53,    48,    58,    61,    57,     2,    60,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,    41,    42,
    50,    43,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    46,     2,    47,    56,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    44,    59,    45,    51,     2,     2,     2,     2,
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
    36,    37,    38,    39,    40
};

#if YY_CTYacc_DEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     5,     8,     9,    13,    14,    22,    24,
    28,    30,    32,    35,    40,    42,    44,    47,    50,    52,
    54,    56,    58,    59,    62,    64,    67,    71,    74,    76,
    79,    81,    82,    85,    89,    91,    95,    97,   101,   103,
   105,   107,   109,   113,   115,   117,   121,   124,   125,   128,
   129,   134,   136,   139,   142,   146,   150,   152,   155,   157,
   160,   162,   165,   168,   170,   172,   175,   177,   179,   181,
   183,   185,   187,   189,   191,   193,   195,   197,   199,   201,
   204,   206,   208,   211,   216,   220,   222,   224,   226,   228,
   230,   232,   234,   236,   238,   240,   243,   246,   247,   250,
   252,   254,   255,   257,   258,   261,   262,   267,   270,   275,
   279,   281,   284,   289,   293,   295,   298,   300,   303,   304,
   306,   308,   310,   311,   320,   321,   323,   324,   326,   329,
   330,   337,   339,   342,   346,   351,   353,   357,   362,   366,
   368,   372,   376,   378,   380,   383,   385,   387,   389,   391,
   393,   395,   397,   399,   402,   404,   406,   408,   410,   412,
   415,   417,   419,   421,   423,   426,   429,   432,   436,   439,
   442,   445,   448,   451,   454,   457,   460,   463,   466,   469,
   472,   475,   479,   483,   486,   489,   492,   495,   497,   500,
   502,   504,   509,   511,   513,   517,   519,   522,   526,   529,
   535,   540,   544,   545,   547,   548,   550,   555,   559,   561,
   563
};

#endif

static const short yyrhs[] = {    -1,
    63,    64,     0,     0,    64,    65,     0,     0,    66,    71,
    41,     0,     0,    25,    42,    68,    43,    67,    71,    41,
     0,    69,     0,    68,    22,    69,     0,    70,     0,   109,
     0,     3,   140,     0,    72,    44,    76,    45,     0,    72,
     0,    73,     0,    73,    86,     0,    75,    74,     0,   140,
     0,   131,     0,     3,     0,     4,     0,     0,    76,    77,
     0,    78,     0,    82,    24,     0,    91,    80,    41,     0,
    91,    41,     0,    41,     0,    80,    41,     0,   110,     0,
     0,    79,    71,     0,    17,    75,    74,     0,   139,     0,
     5,    44,    45,     0,    81,     0,    80,    22,    81,     0,
    98,     0,     6,     0,     7,     0,     8,     0,    85,    20,
   100,     0,    85,     0,    74,     0,    74,    20,    85,     0,
    24,    87,     0,     0,    88,    90,     0,     0,    87,    22,
    89,    90,     0,    85,     0,    82,    85,     0,     9,    85,
     0,     9,    82,    85,     0,    82,     9,    85,     0,    92,
     0,    94,    92,     0,    97,     0,    94,    97,     0,    93,
     0,    92,    93,     0,    96,    94,     0,    96,     0,    95,
     0,    94,    95,     0,   101,     0,   113,     0,   104,     0,
    17,     0,    27,     0,    28,     0,    29,     0,    30,     0,
    31,     0,    32,     0,    33,     0,    34,     0,    35,     0,
    85,    94,     0,    85,     0,    99,     0,   102,    98,     0,
    98,    46,   141,    47,     0,    98,    46,    47,     0,   100,
     0,    84,     0,   140,     0,   126,     0,   128,     0,    83,
     0,    36,     0,    37,     0,    16,     0,    38,     0,    48,
   103,     0,    49,   103,     0,     0,   103,   104,     0,    15,
     0,    19,     0,     0,   106,     0,     0,   107,   109,     0,
     0,   106,    22,   108,   109,     0,    91,    98,     0,    91,
    98,    50,   142,     0,    91,    50,   142,     0,    91,     0,
    91,   102,     0,    91,   119,   117,   111,     0,   119,   117,
   111,     0,   114,     0,    44,    45,     0,    41,     0,    10,
    41,     0,     0,   113,     0,    11,     0,     9,     0,     0,
   112,    51,   140,   115,    52,   116,    53,   111,     0,     0,
    35,     0,     0,   118,     0,    24,   122,     0,     0,   121,
   120,    52,   105,    53,   103,     0,    99,     0,   102,   121,
     0,    52,    99,    53,     0,    52,   102,   121,    53,     0,
   123,     0,   122,    22,   123,     0,    85,    52,   124,    53,
     0,    85,    52,    53,     0,   125,     0,   124,    22,   125,
     0,   140,    50,    12,     0,   140,     0,    26,     0,    14,
   127,     0,    39,     0,    40,     0,    22,     0,    54,     0,
    55,     0,    56,     0,    49,     0,    48,     0,    52,    53,
     0,    57,     0,    58,     0,    50,     0,    59,     0,    51,
     0,    46,    47,     0,    42,     0,    43,     0,    60,     0,
    61,     0,    57,    43,     0,    58,    58,     0,    57,    57,
     0,    57,    43,    48,     0,    42,    42,     0,    43,    43,
     0,    42,    50,     0,    43,    50,     0,    50,    50,     0,
    54,    50,     0,    49,    49,     0,    59,    59,     0,    48,
    50,     0,    60,    50,     0,    55,    50,     0,    58,    50,
     0,    57,    50,     0,    42,    42,    50,     0,    43,    43,
    50,     0,    49,    50,     0,    56,    50,     0,    59,    50,
     0,    14,   129,     0,   130,     0,   130,   102,     0,    92,
     0,    97,     0,   132,    42,   133,    43,     0,   140,     0,
   134,     0,   133,    22,   134,     0,   135,     0,   130,   137,
     0,    94,   130,   137,     0,   102,   137,     0,   137,    52,
   105,    53,   103,     0,   137,    46,   138,    47,     0,    52,
   136,    53,     0,     0,   136,     0,     0,   141,     0,    18,
   140,    44,    45,     0,    18,    44,    45,     0,    23,     0,
    13,     0,    12,     0
};

#if YY_CTYacc_DEBUG != 0
static const short yyrline[] = { 0,
   168,   179,   479,   480,   483,   486,   490,   497,   503,   504,
   513,   514,   517,   525,   557,   585,   590,   597,   609,   610,
   613,   618,   637,   638,   641,   642,   650,   657,   664,   665,
   671,   672,   679,   685,   691,   692,   700,   701,   708,   728,
   733,   738,   745,   769,   772,   776,   785,   792,   796,   799,
   804,   811,   818,   826,   834,   843,   872,   880,   896,   904,
   924,   928,   936,   948,   954,   958,   972,   973,   974,   975,
   979,   980,   981,   982,   983,   984,   985,   986,   987,  1017,
  1022,  1046,  1050,  1056,  1062,  1070,  1074,  1077,  1078,  1079,
  1081,  1084,  1085,  1086,  1087,  1090,  1096,  1107,  1111,  1119,
  1120,  1123,  1127,  1133,  1137,  1143,  1148,  1159,  1170,  1183,
  1192,  1198,  1210,  1214,  1217,  1223,  1224,  1225,  1233,  1234,
  1237,  1241,  1248,  1257,  1272,  1273,  1279,  1280,  1283,  1291,
  1306,  1318,  1322,  1331,  1336,  1344,  1345,  1351,  1356,  1364,
  1365,  1374,  1380,  1381,  1388,  1396,  1397,  1398,  1399,  1400,
  1401,  1402,  1403,  1404,  1405,  1406,  1407,  1408,  1409,  1410,
  1411,  1412,  1413,  1414,  1415,  1416,  1417,  1418,  1419,  1420,
  1421,  1422,  1423,  1424,  1425,  1426,  1427,  1428,  1429,  1430,
  1431,  1432,  1433,  1434,  1435,  1436,  1439,  1447,  1451,  1459,
  1460,  1463,  1472,  1475,  1476,  1485,  1489,  1495,  1504,  1510,
  1517,  1523,  1530,  1534,  1537,  1541,  1544,  1549,  1558,  1562,
  1566
};

static const char * const yytname[] = {   "$","error","$illegal.","tCLASS","tSTRUCT",
"tUNION","tPRIVATE","tPUBLIC","tPROTECTED","tVIRTUAL","tPUREVIRTUAL","tINLINE",
"tEXPRESSION","tCONSTEXPR","tOPERATOR","tCONST","tSTATIC","tFRIEND","tENUM",
"tVOLATILE","tGELTUNGSBEREICHOPERATOR","t3PUNKTE","tKOMMA","tIDENTIFIER","tDOPPELPUNKT",
"tTEMPLATE","tANYTHINGELSE","tCHAR","tSHORT","tINT","tLONG","tSIGNED","tUNSIGNED",
"tFLOAT","tDOUBLE","tVOID","tAUTO","tREGISTER","tEXTERN","tNEW","tDELETE","';'",
"'<'","'>'","'{'","'}'","'['","']'","'*'","'&'","'='","'~'","'('","')'","'!'",
"'%'","'^'","'-'","'+'","'|'","'/'","','","Main","@1","Programm","Deklaration",
"@2","@3","TemplateArgumentListe","TemplateArgument","Typargument","Klassenspezifizierer",
"Klassenkopf","KlassenschluesselKlassenname","Klassenname","Klassenschluessel",
"Elementliste","Element","Elementdeklaration","@4","ElementDeklaratorliste",
"ElementDeklarator","Zugriffsspezifizierer","QualifizierterName","QualifizierterTypname",
"QualifizierterKlassenname","BasisSpez","Basisliste","@5","@6","Basisspezifizierer",
"DeklSpezifiziererliste","DeklSpezlisteStandard","DeklSpezifiziererStandard",
"DeklSpezZusatzListe","DeklSpezifiziererZusatz","StandardTypname","DeklSpezlisteCustom",
"Deklarator","Dname","Name","Speicherklassenspezifizierer","Zeigeroperator",
"CvQualifiziererliste","CvQualifizierer","Argumentliste","ArgDeklarationsliste",
"@7","@8","ArgumentDeklaration","Funktionsdefinition","FktRumpf","FktSpezifiziererOpt",
"FktSpezifizierer","Destruktor","@9","VoidOpt","KtorInitialisiererOpt","KtorInitialisierer",
"FktDeklarator","@10","FktDeklaratorName","ElementInitialisiererliste","ElementInitialisierer",
"Ausdrucksliste","Zuweisungsausdruck","Operatorfunktionsname","Operator","Konversionsfunktionsname",
"Konversionstypname","Typspezifizierer","TemplateKlassenname","TemplateName",
"TemplateArgListe","TemplateArg","Typname","AbstrakterDeklarator","AbstrakterDeklaratorOpt",
"KonstanterAusdruckOpt","EnumSpezifizierer","Bezeichner","KonstanterAusdruck",
"Ausdruck",""
};
#endif

static const short yyr1[] = {     0,
    63,    62,    64,    64,    66,    65,    67,    65,    68,    68,
    69,    69,    70,    71,    71,    72,    72,    73,    74,    74,
    75,    75,    76,    76,    77,    77,    78,    78,    78,    78,
    78,    79,    78,    78,    78,    78,    80,    80,    81,    82,
    82,    82,    83,    84,    85,    85,    86,    88,    87,    89,
    87,    90,    90,    90,    90,    90,    91,    91,    91,    91,
    92,    92,    93,    93,    94,    94,    95,    95,    95,    95,
    96,    96,    96,    96,    96,    96,    96,    96,    96,    97,
    97,    98,    98,    98,    98,    99,    99,   100,   100,   100,
   100,   101,   101,   101,   101,   102,   102,   103,   103,   104,
   104,   105,   105,   107,   106,   108,   106,   109,   109,   109,
   109,   109,   110,   110,   110,   111,   111,   111,   112,   112,
   113,   113,   115,   114,   116,   116,   117,   117,   118,   120,
   119,   121,   121,   121,   121,   122,   122,   123,   123,   124,
   124,   125,   125,   125,   126,   127,   127,   127,   127,   127,
   127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
   127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
   127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
   127,   127,   127,   127,   127,   127,   128,   129,   129,   130,
   130,   131,   132,   133,   133,   134,   135,   135,   136,   136,
   136,   136,   137,   137,   138,   138,   139,   139,   140,   141,
   142
};

static const short yyr2[] = {     0,
     0,     2,     0,     2,     0,     3,     0,     7,     1,     3,
     1,     1,     2,     4,     1,     1,     2,     2,     1,     1,
     1,     1,     0,     2,     1,     2,     3,     2,     1,     2,
     1,     0,     2,     3,     1,     3,     1,     3,     1,     1,
     1,     1,     3,     1,     1,     3,     2,     0,     2,     0,
     4,     1,     2,     2,     3,     3,     1,     2,     1,     2,
     1,     2,     2,     1,     1,     2,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
     1,     1,     2,     4,     3,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     2,     2,     0,     2,     1,
     1,     0,     1,     0,     2,     0,     4,     2,     4,     3,
     1,     2,     4,     3,     1,     2,     1,     2,     0,     1,
     1,     1,     0,     8,     0,     1,     0,     1,     2,     0,
     6,     1,     2,     3,     4,     1,     3,     4,     3,     1,
     3,     3,     1,     1,     2,     1,     1,     1,     1,     1,
     1,     1,     1,     2,     1,     1,     1,     1,     1,     2,
     1,     1,     1,     1,     2,     2,     2,     3,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     3,     3,     2,     2,     2,     2,     1,     2,     1,
     1,     4,     1,     1,     3,     1,     2,     3,     2,     5,
     4,     3,     0,     1,     0,     1,     4,     3,     1,     1,
     1
};

static const short yydefact[] = {     1,
     3,     5,     0,     4,     0,     0,    21,    22,     0,    15,
    16,     0,     0,   122,   121,   100,    94,    70,   101,   209,
    71,    72,    73,    74,    75,    76,    77,    78,    79,    92,
    93,    95,     0,     9,    11,    45,    81,   111,    57,    61,
     0,    65,    64,    59,    67,    69,    12,    68,    20,     0,
    19,     6,    23,    48,    17,    18,    13,     0,     7,     0,
    80,     0,    98,    98,     0,    91,    87,    44,   108,    82,
    86,   112,    89,    90,    19,    62,    58,    66,    60,    63,
     0,    32,    47,     0,    10,     0,    46,   148,   146,   147,
   161,   162,     0,   153,   152,   157,   159,     0,   149,   150,
   151,   155,   156,   158,   163,   164,   190,   191,   145,   187,
   188,    96,    97,   211,   110,     0,     0,     0,    83,     0,
     0,   203,     0,   194,   196,     0,    40,    41,    42,    70,
     0,    29,    14,     0,    24,    25,     0,     0,    37,     0,
    44,     0,    39,    82,     0,    31,     0,    68,   115,   127,
   130,    35,    50,     0,     0,    52,    49,     0,   169,   171,
   170,   172,   160,   177,   175,   184,   173,   154,   174,   179,
   185,   165,   181,   167,   180,   166,   186,   176,   178,   189,
    99,     0,    43,   210,    85,     0,   109,   203,   203,   203,
   204,   197,     0,   192,     0,     0,     0,     0,     0,     0,
    33,     0,    30,    26,    28,     0,   127,   133,     0,     0,
     0,   128,     0,     0,     0,    54,     0,    53,     8,   182,
   183,   168,    84,   198,   204,     0,   199,   205,   104,   195,
    36,    34,   208,     0,   134,   132,     0,     0,    38,    27,
     0,   123,     0,   129,   136,     0,   117,     0,   114,   104,
    51,    55,    56,   202,     0,   206,     0,   103,     0,   207,
   135,   113,     0,     0,     0,   118,   116,     0,   201,    98,
   106,   105,   125,   144,   139,     0,   140,   143,   137,    98,
   200,     0,   126,     0,     0,   138,     0,   131,   107,     0,
   141,   142,   124,     0,     0,     0
};

static const short yydefgoto[] = {   294,
     1,     2,     4,     5,    86,    33,    34,    35,     9,    10,
    11,    36,    12,    82,   135,   136,   137,   138,   139,   155,
    66,    67,    37,    55,    83,    84,   214,   157,    38,    39,
    40,    41,    42,    43,    44,   119,    70,    71,    45,   190,
   112,    46,   257,   258,   259,   282,    47,   146,   249,   147,
    48,   149,   263,   284,   211,   212,   150,   213,   151,   244,
   245,   276,   277,    73,   109,    74,   110,   122,    49,    50,
   123,   124,   125,   191,   192,   255,   152,    51,   186,   115
};

static const short yypact[] = {-32768,
-32768,    19,   -11,-32768,   177,   319,-32768,-32768,    -8,    72,
    18,    54,    54,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,    -7,-32768,-32768,   139,   137,    92,   181,-32768,
   349,-32768,   137,-32768,-32768,-32768,-32768,-32768,-32768,   115,
   122,-32768,-32768,-32768,-32768,-32768,-32768,   319,-32768,    54,
   137,   260,-32768,-32768,   172,-32768,-32768,   168,    93,-32768,
-32768,    82,-32768,-32768,   122,-32768,   181,-32768,-32768,   137,
   349,   229,   171,   127,-32768,   177,-32768,-32768,-32768,-32768,
   -20,    77,   148,   151,   141,   178,-32768,   165,   179,   180,
   189,    94,    50,    33,   191,-32768,   181,-32768,-32768,-32768,
   174,   130,   130,-32768,-32768,   124,     8,   172,   196,    82,
   349,    46,    -2,-32768,-32768,   205,-32768,-32768,-32768,   177,
    35,-32768,-32768,    82,-32768,-32768,   177,     7,-32768,   226,
   183,    76,   196,   201,    24,-32768,   203,   204,-32768,   244,
-32768,-32768,-32768,   154,    66,-32768,-32768,   228,   221,-32768,
   223,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   227,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   168,-32768,-32768,-32768,   232,-32768,    46,    46,    46,
-32768,    28,   349,-32768,   231,    54,   239,   241,   233,    24,
-32768,    82,-32768,-32768,-32768,    44,   244,-32768,    54,    54,
     2,-32768,   245,   127,    54,-32768,    54,-32768,-32768,-32768,
-32768,-32768,-32768,    28,   243,    28,    28,   285,   248,-32768,
-32768,-32768,-32768,   259,-32768,-32768,    24,   252,-32768,-32768,
     2,-32768,   255,   291,-32768,   282,-32768,   279,-32768,   248,
-32768,-32768,-32768,-32768,   278,-32768,   273,   305,   349,-32768,
-32768,-32768,   277,     9,    54,-32768,-32768,   280,-32768,-32768,
-32768,-32768,   296,-32768,-32768,     4,-32768,   287,-32768,-32768,
   130,   349,-32768,   286,   132,-32768,   320,   130,-32768,     2,
-32768,-32768,-32768,   340,   341,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,-32768,   301,-32768,   -72,-32768,
-32768,   -10,   213,-32768,-32768,-32768,-32768,   202,   143,   -73,
-32768,-32768,   -32,-32768,-32768,-32768,-32768,   147,   281,   -28,
   -16,   -27,   -24,-32768,   -17,   -31,   -74,   246,-32768,   -33,
   -63,  -109,   117,-32768,-32768,-32768,  -196,-32768,  -223,-32768,
   288,-32768,-32768,-32768,   162,-32768,   247,-32768,  -118,-32768,
   106,-32768,    88,-32768,-32768,-32768,-32768,   -51,-32768,-32768,
-32768,   182,-32768,   185,    37,-32768,-32768,   -13,   160,   272
};


#define	YYLAST		390


static const short yytable[] = {    57,
   113,    56,   181,   181,    72,    68,    69,   144,   140,    61,
   111,   246,    77,   158,    58,    80,    78,   262,    -2,   193,
   184,   159,    76,    79,    75,   285,   208,    87,   202,   160,
     6,    20,    52,   107,   274,    59,    78,    62,   120,    68,
   194,    54,   247,     3,   108,   248,    20,   203,   145,   141,
   143,   156,   107,   121,   185,    78,   286,    20,    75,   199,
    76,   275,   272,   108,   201,   202,   293,   144,    75,   188,
   144,    63,    64,   228,   217,   134,    20,   180,   197,   229,
   215,   238,   177,   182,   240,   289,   120,    68,    20,    62,
    76,   178,   107,    63,    64,    62,    78,   189,    20,   175,
   200,    68,    75,   108,    20,    62,    75,   176,   145,    68,
   143,   145,    68,    61,    20,    53,   205,   198,   208,   161,
    75,   216,   218,    63,    64,   236,   162,   134,    75,    63,
    64,    75,   127,   128,   129,   154,   172,    62,   117,    63,
    64,    65,   118,   173,    16,    14,    20,    15,    19,    20,
   174,    16,    17,    18,    20,    19,    81,   274,    60,   127,
   128,   129,   236,  -193,   107,   121,   237,    68,   120,    68,
   143,   181,    30,    31,    32,   108,    20,   243,   181,     7,
     8,   156,   252,   114,   253,   232,    75,   116,    75,   165,
   166,    14,   153,    15,   163,   242,   -81,    16,    17,    18,
   164,    19,   116,   237,    68,   -81,   281,    21,    22,    23,
    24,    25,    26,    27,    28,    29,   288,   168,    30,    31,
    32,    63,    64,    75,   224,   226,   227,   167,   169,   170,
   -81,   -81,   243,   126,   127,   128,   129,    14,   171,    15,
   179,   117,    62,    16,    17,   130,   131,    19,   195,   204,
   278,    20,  -132,   209,  -120,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,   210,   219,   132,
   220,   278,   221,   133,   222,   231,    63,    64,   223,  -119,
   134,    88,    20,   233,   234,   235,    21,    22,    23,    24,
    25,    26,    27,    28,    29,   254,   250,   184,    89,    90,
  -102,    91,    92,   260,   261,    93,   264,    94,    95,    96,
    97,    98,   265,    99,   100,   101,   102,   103,   104,   105,
   106,    13,   266,   267,   269,   270,   271,    14,   273,    15,
   283,   292,   280,    16,    17,    18,   287,    19,   290,   295,
   296,    20,   196,   206,   239,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    14,    85,    15,
   251,   183,   142,    16,    17,    18,   268,    19,   241,   148,
   279,    20,   291,   225,   230,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,   256,   207,   187
};

static const short yycheck[] = {    13,
    64,    12,   112,   113,    38,    38,    38,    82,    82,    37,
    62,    10,    41,    86,    22,    43,    41,   241,     0,    22,
    13,    42,    39,    41,    38,    22,   145,    60,    22,    50,
    42,    23,    41,    62,    26,    43,    61,    14,    72,    72,
    43,    24,    41,    25,    62,    44,    23,    41,    82,    82,
    82,    84,    81,    81,    47,    80,    53,    23,    72,   134,
    77,    53,   259,    81,   137,    22,   290,   142,    82,   121,
   145,    48,    49,    46,     9,    52,    23,   111,    44,    52,
   154,   200,    50,   116,    41,   282,   120,   120,    23,    14,
   107,    59,   121,    48,    49,    14,   121,    52,    23,    50,
   134,   134,   116,   121,    23,    14,   120,    58,   142,   142,
   142,   145,   145,   141,    23,    44,    41,   131,   237,    43,
   134,   154,   155,    48,    49,   200,    50,    52,   142,    48,
    49,   145,     6,     7,     8,     9,    43,    14,    46,    48,
    49,    50,    50,    50,    15,     9,    23,    11,    19,    23,
    57,    15,    16,    17,    23,    19,    42,    26,    20,     6,
     7,     8,   237,    42,   193,   193,   200,   200,   202,   202,
   202,   281,    36,    37,    38,   193,    23,   210,   288,     3,
     4,   214,   215,    12,   217,   196,   200,    20,   202,    49,
    50,     9,    22,    11,    47,   209,    14,    15,    16,    17,
    50,    19,    20,   237,   237,    23,   270,    27,    28,    29,
    30,    31,    32,    33,    34,    35,   280,    53,    36,    37,
    38,    48,    49,   237,   188,   189,   190,    50,    50,    50,
    48,    49,   265,     5,     6,     7,     8,     9,    50,    11,
    50,    46,    14,    15,    16,    17,    18,    19,    44,    24,
   264,    23,    52,    51,    51,    27,    28,    29,    30,    31,
    32,    33,    34,    35,    36,    37,    38,    24,    41,    41,
    50,   285,    50,    45,    48,    45,    48,    49,    47,    51,
    52,    22,    23,    45,    44,    53,    27,    28,    29,    30,
    31,    32,    33,    34,    35,    53,    52,    13,    39,    40,
    53,    42,    43,    45,    53,    46,    52,    48,    49,    50,
    51,    52,    22,    54,    55,    56,    57,    58,    59,    60,
    61,     3,    41,    45,    47,    53,    22,     9,    52,    11,
    35,    12,    53,    15,    16,    17,    50,    19,    53,     0,
     0,    23,   130,   142,   202,    27,    28,    29,    30,    31,
    32,    33,    34,    35,    36,    37,    38,     9,    58,    11,
   214,   116,    82,    15,    16,    17,   250,    19,   207,    82,
   265,    23,   285,   189,   193,    27,    28,    29,    30,    31,
    32,    33,    34,    35,    36,    37,    38,   228,   142,   118
};

#line 292 "/Home/origin/matthey/lib/bison.cc"
 /* fattrs + tables */

/* parser code folow  */


/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: dollar marks section change
   the next  is replaced by the list of actions, each action
   as one case of the switch.  */ 

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (YY_CTYacc_CHAR = YYEMPTY)
#define YYEMPTY         -2
#define YYEOF           0
#define YYACCEPT        return(0)
#define YYABORT         return(1)
#define YYERROR         goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL          goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do                                                              \
  if (YY_CTYacc_CHAR == YYEMPTY && yylen == 1)                               \
    { YY_CTYacc_CHAR = (token), YY_CTYacc_LVAL = (value);                 \
      yychar1 = YYTRANSLATE (YY_CTYacc_CHAR);                                \
      YYPOPSTACK;                                               \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    { YY_CTYacc_ERROR ("syntax error: cannot back up"); YYERROR; }   \
while (0)

#define YYTERROR        1
#define YYERRCODE       256

#ifndef YY_CTYacc_PURE
/* UNPURE */
#define YYLEX           YY_CTYacc_LEX()
#ifndef YY_USE_CLASS
/* If nonreentrant, and not class , generate the variables here */
int     YY_CTYacc_CHAR;                      /*  the lookahead symbol        */
YY_CTYacc_STYPE      YY_CTYacc_LVAL;              /*  the semantic value of the */
				/*  lookahead symbol    */
int YY_CTYacc_NERRS;                 /*  number of parse errors so far */
#ifdef YY_CTYacc_LSP_NEEDED
YY_CTYacc_LTYPE YY_CTYacc_LLOC;   /*  location data for the lookahead     */
			/*  symbol                              */
#endif
#endif


#else
/* PURE */
#ifdef YY_CTYacc_LSP_NEEDED
#define YYLEX           YY_CTYacc_LEX(&YY_CTYacc_LVAL, &YY_CTYacc_LLOC)
#else
#define YYLEX           YY_CTYacc_LEX(&YY_CTYacc_LVAL)
#endif
#endif
#ifndef YY_USE_CLASS
#if YY_CTYacc_DEBUG != 0
int YY_CTYacc_DEBUG_FLAG;                    /*  nonzero means print parse trace     */
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
 YY_CTYacc_CLASS::
#endif
     YY_CTYacc_PARSE(YY_CTYacc_PARSE_PARAM)
#ifndef __STDC__
#ifndef __cplusplus
#ifndef YY_USE_CLASS
/* parameter definition without protypes */
YY_CTYacc_PARSE_PARAM_DEF
#endif
#endif
#endif
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YY_CTYacc_STYPE *yyvsp;
  int yyerrstatus;      /*  number of tokens to shift before error messages enabled */
  int yychar1;          /*  lookahead token as an internal (translated) token number */

  short yyssa[YYINITDEPTH];     /*  the state stack                     */
  YY_CTYacc_STYPE yyvsa[YYINITDEPTH];        /*  the semantic value stack            */

  short *yyss = yyssa;          /*  refer to the stacks thru separate pointers */
  YY_CTYacc_STYPE *yyvs = yyvsa;     /*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YY_CTYacc_LSP_NEEDED
  YY_CTYacc_LTYPE yylsa[YYINITDEPTH];        /*  the location stack                  */
  YY_CTYacc_LTYPE *yyls = yylsa;
  YY_CTYacc_LTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YY_CTYacc_PURE
  int YY_CTYacc_CHAR;
  YY_CTYacc_STYPE YY_CTYacc_LVAL;
  int YY_CTYacc_NERRS;
#ifdef YY_CTYacc_LSP_NEEDED
  YY_CTYacc_LTYPE YY_CTYacc_LLOC;
#endif
#endif

  YY_CTYacc_STYPE yyval;             /*  the variable used to return         */
				/*  semantic values from the action     */
				/*  routines                            */

  int yylen;

#if YY_CTYacc_DEBUG != 0
  if (YY_CTYacc_DEBUG_FLAG)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  YY_CTYacc_NERRS = 0;
  YY_CTYacc_CHAR = YYEMPTY;          /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YY_CTYacc_LSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YY_CTYacc_STYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YY_CTYacc_LSP_NEEDED
      YY_CTYacc_LTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
#ifdef YY_CTYacc_LSP_NEEDED
		 &yyls1, size * sizeof (*yylsp),
#endif
		 &yystacksize);

      yyss = yyss1; yyvs = yyvs1;
#ifdef YY_CTYacc_LSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  YY_CTYacc_ERROR("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_bcopy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YY_CTYacc_STYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_bcopy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YY_CTYacc_LSP_NEEDED
      yyls = (YY_CTYacc_LTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_bcopy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YY_CTYacc_LSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YY_CTYacc_DEBUG != 0
      if (YY_CTYacc_DEBUG_FLAG)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YY_CTYacc_DEBUG != 0
  if (YY_CTYacc_DEBUG_FLAG)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (YY_CTYacc_CHAR == YYEMPTY)
    {
#if YY_CTYacc_DEBUG != 0
      if (YY_CTYacc_DEBUG_FLAG)
	fprintf(stderr, "Reading a token: ");
#endif
      YY_CTYacc_CHAR = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (YY_CTYacc_CHAR <= 0)           /* This means end of input. */
    {
      yychar1 = 0;
      YY_CTYacc_CHAR = YYEOF;                /* Don't call YYLEX any more */

#if YY_CTYacc_DEBUG != 0
      if (YY_CTYacc_DEBUG_FLAG)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(YY_CTYacc_CHAR);

#if YY_CTYacc_DEBUG != 0
      if (YY_CTYacc_DEBUG_FLAG)
	{
	  fprintf (stderr, "Next token is %d (%s", YY_CTYacc_CHAR, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, YY_CTYacc_CHAR, YY_CTYacc_LVAL);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

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
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YY_CTYacc_DEBUG != 0
  if (YY_CTYacc_DEBUG_FLAG)
    fprintf(stderr, "Shifting token %d (%s), ", YY_CTYacc_CHAR, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (YY_CTYacc_CHAR != YYEOF)
    YY_CTYacc_CHAR = YYEMPTY;

  *++yyvsp = YY_CTYacc_LVAL;
#ifdef YY_CTYacc_LSP_NEEDED
  *++yylsp = YY_CTYacc_LLOC;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YY_CTYacc_DEBUG != 0
  if (YY_CTYacc_DEBUG_FLAG)
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


/* #line 697 "/Home/origin/matthey/lib/bison.cc" */

  switch (yyn) {

case 1:
#line 168 "CTYacc.y"
{
          myActualType = "";
          myActualView = "";
          myActualScope = "";
          myActualPointer = "";
          myIsTemplate = false;
          myTemplateParameters = "";
          myMemberIsTemplate = false;
          myIsVirtual = false;
        ;
    break;}
case 2:
#line 179 "CTYacc.y"
{
          // look for has-a and is-a Relations and set them
          for(int i = 0; i < aProgramm.KlassenListe.count(); i++) {

            // look for has-a Relations
            tKlassenMember * tmpMember;
            for(int j = 0; j < aProgramm.KlassenListe.item(i).KlassenMemberListe.count(); j++) {
              tmpMember = &aProgramm.KlassenListe.item(i).KlassenMemberListe.item(j);
              RCString myCheckScopes = "";
              myCheckScopes = aProgramm.KlassenListe.item(i).LongName;
              bool stayIn = true;
              while (stayIn) {
                // if the scope is empty terminate after this step
                if (myCheckScopes.length() <= 0) {
                  stayIn = false;
                  };
               
                for(int k = 0; k < aProgramm.KlassenListe.count(); k++) {
                  RCString myCheck = ""; 
                  if (myCheckScopes == "") {
                    myCheck = tmpMember->type;
                    }
                  else {
                    myCheck = myCheckScopes + "::" + tmpMember->type;
                    };
                  // cout << myCheck << " == " << aProgramm.KlassenListe.item(k).LongName << "?\n";
                  if (aProgramm.KlassenListe.item(k).LongName == myCheck) {
                    aProgramm.KlassenListe.item(i).KlassenMemberListe.item(j).hasa = k;
                    myCheckScopes = "";
                    break;
                    }; // end if
                  }; // end for

                // cut the classname in the scope away at the tail        
                // cout << ">>> " << myCheckScopes << " <<<\n\n";
                int myScopeEnd = 0;
                for (int k = myCheckScopes.length() - 1; k >= 1; k--) {
                  if (myCheckScopes(k-1,k) == "::") {
                    myScopeEnd = k-2;
                    break;
                    }; // end if
                  }; // end for
                if (myScopeEnd == 0) {
                  myCheckScopes = "";
                  }
                else {
                  myCheckScopes = myCheckScopes(0,myScopeEnd);
                  };
                // cout << "Resulting Scope: [_" << myCheckScopes << "_]\n";
                  
                }; // end while
              }; // for j (has-a)

            // look for is-a Relations
            tBasisKlasse * tmpBasis;
            for(int j = 0; j < aProgramm.KlassenListe.item(i).BasisKlassenListe.count(); j++) {
              tmpBasis = &aProgramm.KlassenListe.item(i).BasisKlassenListe.item(j);
              for(int k = 0; k < aProgramm.KlassenListe.count(); k++) {
                if (aProgramm.KlassenListe.item(k).ShortName == tmpBasis->name) {
                  aProgramm.KlassenListe.item(i).BasisKlassenListe.item(j).isa = k;
                  break;
                  } // if
                }; // for k
              if (aProgramm.KlassenListe.item(i).BasisKlassenListe.item(j).isa < 0) {
                // is-a detected, but not parsed -> let's create the empty baseclass
                Report::warning("[CTYacc::postprocess] '" + aProgramm.KlassenListe.item(i).LongName + "' is-a '" + tmpBasis->name + "' but this class hasn't been parsed");
                aKlasse.clean();
                aKlasse.ShortName = tmpBasis->name;
                aKlasse.LongName = tmpBasis->name;
                aProgramm.KlassenListe.append(aKlasse);
                aProgramm.KlassenListe.item(i).BasisKlassenListe.item(j).isa = aProgramm.KlassenListe.count()-1;
                Report::warning("[CTYacc::postprocess] '" + aProgramm.KlassenListe.item(aProgramm.KlassenListe.count()-1).LongName + "' has been added without beeing parsed");
                };
              };  // for j (is-a)
            }; // for i 

          
          
          // display the results Results (only in verbose mode)
          if (myParserVerboseFlag) {
            cout << "\n";
            for(int i = 0; i < aProgramm.KlassenListe.count(); i++) {
              cout << i << ": " << aProgramm.KlassenListe.item(i).ShortName;
              cout << " - " << aProgramm.KlassenListe.item(i).LongName;
              cout << " - " << aProgramm.KlassenListe.item(i).KlassenMemberListe.count() << " members";
              cout << " - Template: " << aProgramm.KlassenListe.item(i).isTemplate << " " << aProgramm.KlassenListe.item(i).TemplateParameters;
              cout << " - Virtual: " << aProgramm.KlassenListe.item(i).isAbstract;
              cout << "\n";

              tBasisKlasse * tmpBasis;
              cout << "   Basisklassen:\n";
              for(int j = 0; j < aProgramm.KlassenListe.item(i).BasisKlassenListe.count(); j++) {
                tmpBasis = &aProgramm.KlassenListe.item(i).BasisKlassenListe.item(j);
                cout << "     Name: " << tmpBasis->name;
                cout << "   View: " << tmpBasis->view;
                cout << "   Virtual: " << tmpBasis->isVirtual;
                cout << "   Is-a: " << tmpBasis->isa;
                cout << "\n";
                }

              tKlassenMember * tmpMember;
              cout << "   Klassenmember:\n"; 
              for(int j = 0; j < aProgramm.KlassenListe.item(i).KlassenMemberListe.count(); j++) {
                tmpMember = &aProgramm.KlassenListe.item(i).KlassenMemberListe.item(j);
                cout << "     Name: " << tmpMember->name;
                cout << "   Type: " << tmpMember->type << tmpMember->ptr;
                cout << "   View: " << tmpMember->view;
                cout << "   Hasa: " << tmpMember->hasa;
                // cout << "   Init: " << tmpMember->init;   // ANSI C++ forbids this
                cout << "   Template: " << tmpMember->isTemplate;
                cout << "\n\n";
                }

              tKlassenOperation tmpOp;
              cout << "   Operationen:\n";
              for(int j = 0; j < aProgramm.KlassenListe.item(i).KlassenOperationenListe.count(); j++) {
                tmpOp = aProgramm.KlassenListe.item(i).KlassenOperationenListe.item(j);
                cout << "     Name: " << tmpOp.name;
                cout << "   Type: " << tmpOp.type << tmpOp.ptr;
                cout << "   View: " << tmpOp.view;
                cout << "   Virtual: " << tmpOp.isAbstract;
                cout << "\n";
                cout << "       Parameter:\n";
                tOperationsParameter tmpParm;
                for(int k = 0; k < tmpOp.OperationsParameterListe.count(); k++) {
                  tmpParm = tmpOp.OperationsParameterListe.item(k);
                  cout << "       Name: " << tmpParm.name;
                  cout << "   Type: " << tmpParm.type << tmpParm.ptr;
                  cout << "   View: " << tmpParm.view;
                  cout << "   Init: " << tmpParm.init;
                  cout << "\n";
                  }
                }

              cout << "\n";      
              }
            };


          // generateResults in a World2D of CTClassDescription2D          
          //
          // go through all the classes the first time
          // and just generate the class body itself
          //
          // in this step I don't treat the pointers to
          // BaseClasses and has-a Relations because the
          // targets of the pointers couldn't yet been created
          // when I would like to make the pointer
          //
          for(int i = 0; i < aProgramm.KlassenListe.count(); i++) {
            CTClassDescription2D* aClass = new CTClassDescription2D; 
            aClass->setName(aProgramm.KlassenListe.item(i).LongName);
            if (aProgramm.KlassenListe.item(i).isTemplate) {
              aClass->setIsTemplate(true);
              aClass->setTemplateParameters(aProgramm.KlassenListe.item(i).TemplateParameters);
              };
            aClass->setIsAbstract(aProgramm.KlassenListe.item(i).isAbstract); 
            aProgramm.KlassenListe.item(i).hasBecomeThisClass = aClass;

            myWorld->getObjects()->adoptObject(aClass);
            };
          // now all the CTClassDescriptions2D needed exist


          // Second loop
          // now I have created all classes and can create the pointers
          // and all the other details

          CTClassDescription2D* aClass;
          CTAttributeDescription * aAttribute;
          tKlassenMember * tmpMember; 
          CTBaseclassDescription * aBaseclass;
          tBasisKlasse * tmpBasis;
          CTOperationDescription * aOperation;
          tKlassenOperation * tmpOp;
          CTVariableDescription * aVariable;
          tOperationsParameter * tmpParm;
          ostrstream *os;

          for(int i = 0; i < aProgramm.KlassenListe.count(); i++) {
            aClass = aProgramm.KlassenListe.item(i).hasBecomeThisClass;

            // Attributes
            for(int j = 0; j < aProgramm.KlassenListe.item(i).KlassenMemberListe.count(); j++) {
              tmpMember = &aProgramm.KlassenListe.item(i).KlassenMemberListe.item(j);

              aAttribute = new CTAttributeDescription;

              aAttribute->setName(tmpMember->name);
              aAttribute->setType(tmpMember->type + tmpMember->ptr);
              if (tmpMember->view == "public") {
                aAttribute->setView(CTAttributeDescription::Public);
                }
              else if (tmpMember->view == "protected") {
                aAttribute->setView(CTAttributeDescription::Protected);
                }
              else if (tmpMember->view == "private") {
                aAttribute->setView(CTAttributeDescription::Private);
                }
              else {
                aAttribute->setView(CTAttributeDescription::Unspecified);
                };
              if (tmpMember->isTemplate) {
                aAttribute->setIsTemplate(true);
                };

              // look for has-a Relations
              if (tmpMember->hasa >= 0) {
                aAttribute->setAssociation(aProgramm.KlassenListe.item(tmpMember->hasa).hasBecomeThisClass);
                }; 

              aClass->addAttribute(*aAttribute);
              delete aAttribute;
              }

            // Baseclasses
            for(int j = 0; j < aProgramm.KlassenListe.item(i).BasisKlassenListe.count(); j++) {
              tmpBasis = &aProgramm.KlassenListe.item(i).BasisKlassenListe.item(j);

              // look for is-a Relations          
              if (tmpBasis->isa >= 0) {
                aBaseclass = new CTBaseclassDescription;

                if (tmpBasis->view == "public") {
                  aBaseclass->setView(CTBaseclassDescription::Public);
                  }
                else if (tmpBasis->view == "protected") {
                  aBaseclass->setView(CTBaseclassDescription::Protected);
                  }
                else if (tmpBasis->view == "private") {
                  aBaseclass->setView(CTBaseclassDescription::Private);
                  }
                else {
                  aBaseclass->setView(CTBaseclassDescription::Unspecified);
                  };

                aBaseclass->setBaseclass(aProgramm.KlassenListe.item(tmpBasis->isa).hasBecomeThisClass);

                aClass->addBaseclass(*aBaseclass);
                delete aBaseclass;
                }
              else {
                Report::warning("[CTYacc::postprocess] '" + aProgramm.KlassenListe.item(i).LongName + "' is-a '" + tmpBasis->name + "' but this class hasn't been parsed and not produced");
                };

             }



            // Operations
            for(int j = 0; j < aProgramm.KlassenListe.item(i).KlassenOperationenListe.count(); j++) { 
              tmpOp = &aProgramm.KlassenListe.item(i).KlassenOperationenListe.item(j);

              aOperation = new CTOperationDescription;

              aOperation->setName(tmpOp->name);
              aOperation->setReturnType(tmpOp->type + tmpOp->ptr);
              aOperation->setIsAbstract(tmpOp->isAbstract);        

              for(int k = 0; k < tmpOp->OperationsParameterListe.count(); k++) {
                tmpParm = &tmpOp->OperationsParameterListe.item(k);

                aVariable = new CTVariableDescription;

                aVariable->setName(tmpParm->name);
                aVariable->setType(tmpParm->type + tmpParm->ptr);
                aVariable->setInitValue(tmpParm->init);

                aOperation->addParameter(*aVariable);        
                delete aVariable;
                }

              if (tmpOp->view == "public") {
                aOperation->setView(CTOperationDescription::Public);
                }
              else if (tmpOp->view == "protected") {
                aOperation->setView(CTOperationDescription::Protected);
                }
              else if (tmpOp->view == "private") {
                aOperation->setView(CTOperationDescription::Private);
                }
              else {
                aOperation->setView(CTOperationDescription::Unspecified);
                };

              aClass->addOperation(*aOperation);
              delete aOperation;
              }

            os = new ostrstream;
            *os << "[CTYacc] Postprocess - CLASS " << i;
            Report::debug(*os);
            delete os;

            }; // for all classes          

            Report::debug("[CTYacc] Postprocess - END");
          ;
    break;}
case 5:
#line 483 "CTYacc.y"
{ 
                  myIsTemplate = false;
                ;
    break;}
case 6:
#line 487 "CTYacc.y"
{
                  myIsTemplate = false;
                ;
    break;}
case 7:
#line 491 "CTYacc.y"
{
                  myIsTemplate = true;
                  myTemplateParameters = "<" + *yyvsp[-1].string + ">";
                  delete yyvsp[-3].string;
                  delete yyvsp[-1].string;
                ;
    break;}
case 8:
#line 498 "CTYacc.y"
{
                  myIsTemplate = false;
                ;
    break;}
case 10:
#line 505 "CTYacc.y"
{ 
                            yyval.string = new RCString(*yyvsp[-2].string + ", " + *yyvsp[0].string);
                            delete yyvsp[-2].string;
                            delete yyvsp[-1].string;
                            delete yyvsp[0].string;
                          ;
    break;}
case 13:
#line 518 "CTYacc.y"
{
                  yyval.string = new RCString(*yyvsp[-1].string + " " + *yyvsp[0].string);
                  delete yyvsp[-1].string;
                  delete yyvsp[0].string;
                ;
    break;}
case 14:
#line 526 "CTYacc.y"
{ 
                          bool myAlreadyDeclared = false;
                          int myAlreadyDeclaredClass = -1;                          
                          for(int i = 0; i < aProgramm.KlassenListe.count(); i++) {
                            ostrstream os;
                            os << "[CTYacc] " << aKlasse.LongName << " ==??== " << aProgramm.KlassenListe.item(i).LongName;
                            Report::debug(os);
                            if (aKlasse.LongName == aProgramm.KlassenListe.item(i).LongName) {
                              ostrstream os;
                              os << "[CTYacc] DOPPELTE KLASSE : " << aKlasse.LongName << " !!!";
                              Report::debug(os);
                              myAlreadyDeclared = true;
                              myAlreadyDeclaredClass = i;
                              };
                            };
                          if (myAlreadyDeclared == true) {
                            // The Foreward Declaration is will be replaced
                            ostrstream os;
                            os << "[CTYacc] Die Klasse Nr. " << myAlreadyDeclaredClass << " wird ersetzt!";
                            Report::debug(os);
                            aProgramm.KlassenListe.remove(myAlreadyDeclaredClass);
                            aProgramm.KlassenListe.insert(myAlreadyDeclaredClass, aKlasse);
                            }
                          else {
                            // the new class will be appended
                            aProgramm.KlassenListe.append(aKlasse);
                            ostrstream os;
                            os << "[CTYacc] Klasse zugefuegt: " << aKlasse.LongName;
                            Report::debug(os);
                            };
                        ;
    break;}
case 15:
#line 558 "CTYacc.y"
{ 
                          bool myAlreadyDeclared = false;
                          for(int i = 0; i < aProgramm.KlassenListe.count(); i++) {
                            ostrstream os;
                            os << "[CTYacc] " << aKlasse.LongName << " ==??== " << aProgramm.KlassenListe.item(i).LongName;
                            Report::debug(os);
                            if (aKlasse.LongName == aProgramm.KlassenListe.item(i).LongName) {
                              ostrstream os;
                              os << "[CTYacc] DOPPELTE KLASSE : " << aKlasse.LongName << " !!!";
                              Report::debug(os);
                              myAlreadyDeclared = true;
                              };
                            };
                          // The Foreward Declaration is only inserted, when
                          // no class with the same name exisits
                          if (myAlreadyDeclared == false) {
                            aProgramm.KlassenListe.append(aKlasse);
                            ostrstream os;
                            os << "[CTYacc] Klasse zugefuegt: " << aKlasse.LongName;
                            Report::debug(os);
                            }
                          else {
                            Report::debug("[CTYacc] keine Klassenforewarddeklaration zugefuegt"); 
                            };
                        ;
    break;}
case 17:
#line 591 "CTYacc.y"
{ 
                 yyval.string = yyvsp[-1].string;
               ;
    break;}
case 18:
#line 598 "CTYacc.y"
{ 
                                  aKlasse.clean();    // neue, leere Klasse beginnen
                                  aKlasse.isTemplate = myIsTemplate;
                                  aKlasse.TemplateParameters = myTemplateParameters;
                                  aKlasse.ShortName = *yyvsp[0].string;
                                  aKlasse.LongName = myActualScope + aKlasse.ShortName;
                                  delete yyvsp[-1].string;
                                  delete yyvsp[0].string;
                                ;
    break;}
case 21:
#line 614 "CTYacc.y"
{ 
                          myActualView = "private";
                          yyval.string = yyvsp[0].string;
                        ;
    break;}
case 22:
#line 619 "CTYacc.y"
{ 
                          myActualView = "public";
                          yyval.string = yyvsp[0].string;
                        ;
    break;}
case 26:
#line 643 "CTYacc.y"
{
              delete yyvsp[-1].string;
              delete yyvsp[0].string;
            ;
    break;}
case 27:
#line 651 "CTYacc.y"
{
                         delete yyvsp[-2].string;
                         myActualPointer = "";
                         myActualType = "";
                         myMemberIsTemplate = false;
                       ;
    break;}
case 28:
#line 658 "CTYacc.y"
{
                         delete yyvsp[-1].string;
                         myActualType = "";
                         myActualType = "";
                         myMemberIsTemplate = false;
                       ;
    break;}
case 30:
#line 666 "CTYacc.y"
{
                         myActualType = "";
                         myActualType = "";
                         myMemberIsTemplate = false;
                       ;
    break;}
case 32:
#line 672 "CTYacc.y"
{ 
                         myKlassenStack.push(aKlasse);     // aktuelle Klasse sichern
                         myScopeStack.push(myActualScope); // aktuellen Scope sichern
                         myActualScope += aKlasse.ShortName;
                         myActualScope += "::";
                       ;
    break;}
case 33:
#line 679 "CTYacc.y"
{ 
                         myActualType = aKlasse.ShortName;
                         aKlasse = myKlassenStack.pop();       // letzte Klasse holen
                         myActualScope = myScopeStack.pop();
                         // delete $2;
                       ;
    break;}
case 34:
#line 686 "CTYacc.y"
{ 
                         delete yyvsp[-2].string;
                         delete yyvsp[-1].string;
                         delete yyvsp[0].string;
                       ;
    break;}
case 36:
#line 693 "CTYacc.y"
{
                         delete yyvsp[-2].string;
                       ;
    break;}
case 38:
#line 702 "CTYacc.y"
{ 
                            delete yyvsp[-1].string;
                          ;
    break;}
case 39:
#line 709 "CTYacc.y"
{ 
                          aKlassenMember.clean();
                          aKlassenMember.name = *yyvsp[0].string;
                          aKlassenMember.type = myActualType;
                          aKlassenMember.ptr = myActualPointer;
                          // myActualType = "";
                          myActualPointer = "";
                          aKlassenMember.view = myActualView;
                          aKlassenMember.isTemplate = myMemberIsTemplate;
                          aKlasse.KlassenMemberListe.append(aKlassenMember);
                          ostrstream os;
                          os << "[CTYacc] MEMBER ADDED: " << aKlassenMember.name << " with type: " << aKlassenMember.type;
                          Report::debug(os);
                          delete yyvsp[0].string;
                        ;
    break;}
case 40:
#line 729 "CTYacc.y"
{ 
                           myActualView = "private"; 
                           yyval.string = yyvsp[0].string;
                         ;
    break;}
case 41:
#line 734 "CTYacc.y"
{ 
                           myActualView = "public"; 
                           yyval.string = yyvsp[0].string;
                         ;
    break;}
case 42:
#line 739 "CTYacc.y"
{ 
                           myActualView = "protected"; 
                           yyval.string = yyvsp[0].string;
                         ;
    break;}
case 43:
#line 746 "CTYacc.y"
{ 
                          yyval.string = new RCString (*yyvsp[-2].string + *yyvsp[-1].string + *yyvsp[0].string);
                          delete yyvsp[-2].string;
                          delete yyvsp[-1].string;
                          delete yyvsp[0].string;
                        ;
    break;}
case 45:
#line 773 "CTYacc.y"
{ 
                                yyval.string = yyvsp[0].string;
                              ;
    break;}
case 46:
#line 777 "CTYacc.y"
{
                                yyval.string = new RCString (*yyvsp[-2].string + *yyvsp[-1].string + *yyvsp[0].string);
                                delete yyvsp[-2].string;
                                delete yyvsp[-1].string;
                                delete yyvsp[0].string;
                              ;
    break;}
case 47:
#line 786 "CTYacc.y"
{ 
                    delete yyvsp[-1].string;
                  ;
    break;}
case 48:
#line 792 "CTYacc.y"
{ 
                    aBasisKlasse.clean(); 
                  ;
    break;}
case 49:
#line 796 "CTYacc.y"
{ 
                    aKlasse.BasisKlassenListe.append(aBasisKlasse);
                  ;
    break;}
case 50:
#line 800 "CTYacc.y"
{ 
                    aBasisKlasse.clean(); 
                  ;
    break;}
case 51:
#line 804 "CTYacc.y"
{ 
                    aKlasse.BasisKlassenListe.append(aBasisKlasse);
                    delete yyvsp[-2].string;
                  ;
    break;}
case 52:
#line 812 "CTYacc.y"
{ 
                          aBasisKlasse.name = *yyvsp[0].string;
                          aBasisKlasse.view = "private"; // default derivation
                          aBasisKlasse.isVirtual = false;
                          delete yyvsp[0].string; 
                        ;
    break;}
case 53:
#line 819 "CTYacc.y"
{ 
                          aBasisKlasse.name = *yyvsp[0].string;
                          aBasisKlasse.view = *yyvsp[-1].string;
                          aBasisKlasse.isVirtual = false;
                          delete yyvsp[0].string;
                          delete yyvsp[-1].string;
                        ;
    break;}
case 54:
#line 827 "CTYacc.y"
{ 
                          aBasisKlasse.name = *yyvsp[0].string;
                          aBasisKlasse.view = "private"; // default derivation
                          aBasisKlasse.isVirtual = true; 
                          delete yyvsp[0].string;
                          delete yyvsp[-1].string;
                        ;
    break;}
case 55:
#line 835 "CTYacc.y"
{ 
                          aBasisKlasse.name = *yyvsp[0].string;
                          aBasisKlasse.view = *yyvsp[-1].string;
                          aBasisKlasse.isVirtual = true; 
                          delete yyvsp[-2].string;
                          delete yyvsp[-1].string;
                          delete yyvsp[0].string;
                        ;
    break;}
case 56:
#line 844 "CTYacc.y"
{ 
                          aBasisKlasse.name = *yyvsp[0].string;
                          aBasisKlasse.view = *yyvsp[-2].string;
                          aBasisKlasse.isVirtual = true;
                          delete yyvsp[-2].string;
                          delete yyvsp[-1].string;
                          delete yyvsp[0].string;
                        ;
    break;}
case 57:
#line 873 "CTYacc.y"
{ 
                            yyval.string = yyvsp[0].string; 
                            ostrstream os;
                            os << "[CTYacc] STANDARD TYPE: " << *yyval.string;
                            Report::debug(os);
                            myActualType = *yyval.string;
                          ;
    break;}
case 58:
#line 881 "CTYacc.y"
{
                            if (*yyvsp[-1].string == "") {
                              yyval.string = yyvsp[0].string;
                              delete yyvsp[-1].string;
                              }
                            else {
                              yyval.string = new RCString(*yyvsp[-1].string + " " + *yyvsp[0].string);
                              delete yyvsp[-1].string;
                              delete yyvsp[0].string;
                              };
                            ostrstream os;
                            os << "[CTYacc] STANDARD TYPE: " << *yyval.string;
                            Report::debug(os);
                            myActualType = *yyval.string;
                          ;
    break;}
case 59:
#line 897 "CTYacc.y"
{
                            yyval.string = yyvsp[0].string;    
                            ostrstream os;
                            os << "[CTYacc] CUSTOM TYPE: " << *yyval.string;
                            Report::debug(os);
                            myActualType = *yyvsp[0].string;
                          ;
    break;}
case 60:
#line 905 "CTYacc.y"
{
                            if (*yyvsp[-1].string == "") {
                              yyval.string = yyvsp[0].string;
                              delete yyvsp[-1].string;
                              }
                            else {
                              yyval.string = new RCString(*yyvsp[-1].string + " " + *yyvsp[0].string);
                              delete yyvsp[-1].string;
                              delete yyvsp[0].string;
                              };
                            ostrstream os;
                            os << "[CTYacc] CUSTOM TYPE: " << *yyval.string;
                            Report::debug(os);
                            myActualType = *yyval.string;
                          ;
    break;}
case 61:
#line 925 "CTYacc.y"
{ 
                           yyval.string = yyvsp[0].string;
                         ;
    break;}
case 62:
#line 929 "CTYacc.y"
{ 
                           yyval.string = new RCString (*yyvsp[-1].string + " " + *yyvsp[0].string);
                           delete yyvsp[-1].string;
                           delete yyvsp[0].string;
                         ;
    break;}
case 63:
#line 937 "CTYacc.y"
{
                                if (*yyvsp[0].string == "") {
                                  yyval.string = yyvsp[-1].string;
                                  delete yyvsp[0].string;
                                  }
                                else {
                                  yyval.string = new RCString(*yyvsp[-1].string + " " + *yyvsp[0].string);
                                  delete yyvsp[-1].string;
                                  delete yyvsp[0].string;
                                  };
                              ;
    break;}
case 64:
#line 949 "CTYacc.y"
{
                                yyval.string = yyvsp[0].string;
                              ;
    break;}
case 65:
#line 955 "CTYacc.y"
{
                          yyval.string = yyvsp[0].string;
                        ;
    break;}
case 66:
#line 959 "CTYacc.y"
{
                          if (*yyvsp[0].string == "") {
                            yyval.string = yyvsp[-1].string;
                            delete yyvsp[0].string;
                            }
                          else {
                            yyval.string = new RCString(*yyvsp[-1].string + " " + *yyvsp[0].string);
                            delete yyvsp[-1].string;
                            delete yyvsp[0].string;
                            };
                        ;
    break;}
case 67:
#line 972 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 68:
#line 973 "CTYacc.y"
{ yyval.string = new RCString(""); ;
    break;}
case 69:
#line 974 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 70:
#line 975 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 71:
#line 979 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 72:
#line 980 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 73:
#line 981 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 74:
#line 982 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 75:
#line 983 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 76:
#line 984 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 77:
#line 985 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 78:
#line 986 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 79:
#line 987 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 80:
#line 1018 "CTYacc.y"
{
                           yyval.string = new RCString(*yyvsp[-1].string + " " + *yyvsp[0].string);
                           delete yyvsp[-1].string; delete yyvsp[0].string;
                        ;
    break;}
case 81:
#line 1023 "CTYacc.y"
{
                          yyval.string = yyvsp[0].string;
                        ;
    break;}
case 82:
#line 1047 "CTYacc.y"
{ 
                yyval.string = yyvsp[0].string;
              ;
    break;}
case 83:
#line 1051 "CTYacc.y"
{ 
                myActualPointer += *yyvsp[-1].string;
                yyval.string = yyvsp[0].string;
                delete yyvsp[-1].string; 
              ;
    break;}
case 84:
#line 1057 "CTYacc.y"
{ 
                yyval.string = new RCString (*yyvsp[-3].string + "[" + *yyvsp[-1].string + "]");
                delete yyvsp[-3].string;
                delete yyvsp[-1].string;
              ;
    break;}
case 85:
#line 1063 "CTYacc.y"
{ 
                yyval.string = new RCString (*yyvsp[-2].string + "[]");
                delete yyvsp[-2].string;
              ;
    break;}
case 86:
#line 1070 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 87:
#line 1074 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 88:
#line 1077 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 89:
#line 1078 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 90:
#line 1079 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 91:
#line 1081 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 92:
#line 1084 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 93:
#line 1085 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 94:
#line 1086 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 95:
#line 1087 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 96:
#line 1091 "CTYacc.y"
{ 
                    yyval.string = new RCString ("*" + *yyvsp[0].string);
                    delete yyvsp[0].string;
                  ;
    break;}
case 97:
#line 1097 "CTYacc.y"
{ 
                    yyval.string = new RCString ("&" + *yyvsp[0].string);
                    delete yyvsp[0].string;
                  ;
    break;}
case 98:
#line 1108 "CTYacc.y"
{
                          yyval.string = new RCString("");
                        ;
    break;}
case 99:
#line 1112 "CTYacc.y"
{ 
                          yyval.string = new RCString (*yyvsp[-1].string + " " + *yyvsp[0].string);
                          delete yyvsp[-1].string;
                          delete yyvsp[0].string;
                        ;
    break;}
case 100:
#line 1119 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 101:
#line 1120 "CTYacc.y"
{ yyval.string = yyvsp[0].string; ;
    break;}
case 102:
#line 1124 "CTYacc.y"
{
                   yyval.string = new RCString("");
                 ;
    break;}
case 104:
#line 1133 "CTYacc.y"
{ 
                          aOperationsParameter.clean(); 
                        ;
    break;}
case 105:
#line 1137 "CTYacc.y"
{ 
                          yyval.string = yyvsp[0].string;
                          aKlassenOperation.OperationsParameterListe.append(aOperationsParameter);
                          myActualPointer = "";
                          myActualType = "";
                        ;
    break;}
case 106:
#line 1144 "CTYacc.y"
{ 
                          aOperationsParameter.clean();
                        ;
    break;}
case 107:
#line 1148 "CTYacc.y"
{ 
                          yyval.string = new RCString(*yyvsp[-3].string + *yyvsp[-2].string + " " + *yyvsp[0].string);
                          delete yyvsp[-3].string;
                          delete yyvsp[-2].string;
                          delete yyvsp[0].string;
                          aKlassenOperation.OperationsParameterListe.append(aOperationsParameter);
                          myActualPointer = "";
                          myActualType = "";
                        ;
    break;}
case 108:
#line 1160 "CTYacc.y"
{ 
                          aOperationsParameter.name = *yyvsp[0].string;
                          aOperationsParameter.type = *yyvsp[-1].string;
                          aOperationsParameter.ptr = myActualPointer;
                          myActualPointer = "";
                          aOperationsParameter.view = myActualView;
                          yyval.string = new RCString(*yyvsp[-1].string + " " + *yyvsp[0].string);
                          delete yyvsp[-1].string;
                          delete yyvsp[0].string;
                        ;
    break;}
case 109:
#line 1171 "CTYacc.y"
{ 
                          aOperationsParameter.name = *yyvsp[-2].string;
                          aOperationsParameter.type = *yyvsp[-3].string;
                          aOperationsParameter.ptr = myActualPointer;
                          myActualPointer = "";
                          aOperationsParameter.init = *yyvsp[0].string;
                          aOperationsParameter.view = myActualView;
                          yyval.string = new RCString(*yyvsp[-3].string + " " + *yyvsp[-2].string + " = " + *yyvsp[0].string);
                          delete yyvsp[-3].string;
                          delete yyvsp[-2].string;
                          delete yyvsp[0].string;                          
                        ;
    break;}
case 110:
#line 1184 "CTYacc.y"
{ 
                          aOperationsParameter.type = *yyvsp[-2].string;
                          aOperationsParameter.init = *yyvsp[0].string;
                          aOperationsParameter.view = myActualView; 
                          yyval.string = new RCString(*yyvsp[-2].string + " = " + *yyvsp[0].string);
                          delete yyvsp[-2].string;
                          delete yyvsp[0].string;
                        ;
    break;}
case 111:
#line 1193 "CTYacc.y"
{ 
                          aOperationsParameter.type = *yyvsp[0].string;
                          aOperationsParameter.view = myActualView;
                          yyval.string = yyvsp[0].string;
                        ;
    break;}
case 112:
#line 1199 "CTYacc.y"
{ 
                          aOperationsParameter.type = (*yyvsp[-1].string + *yyvsp[0].string);
                          aOperationsParameter.view = myActualView;
                          yyval.string = new RCString(*yyvsp[-1].string + *yyvsp[0].string);
                          delete yyvsp[-1].string;
                          delete yyvsp[0].string;
                        ;
    break;}
case 113:
#line 1211 "CTYacc.y"
{
                          delete yyvsp[-3].string;
                        ;
    break;}
case 114:
#line 1215 "CTYacc.y"
{
                        ;
    break;}
case 115:
#line 1218 "CTYacc.y"
{
                        ;
    break;}
case 118:
#line 1226 "CTYacc.y"
{ 
               myIsVirtual = true;
               delete yyvsp[-1].string;
               // aKlassenOperation.isVirtual = true; 
             ;
    break;}
case 121:
#line 1238 "CTYacc.y"
{
                      delete yyvsp[0].string;
                    ;
    break;}
case 122:
#line 1242 "CTYacc.y"
{ 
                      delete yyvsp[0].string;
                      myIsVirtual = true; 
                    ;
    break;}
case 123:
#line 1249 "CTYacc.y"
{ 
                 aKlassenOperation.clean();
                 aKlassenOperation.name = "~" + *yyvsp[0].string;
                 // aKlassenOperation.type = myActualType;
                 aKlassenOperation.type = "";
                 myActualType = "";
                 aKlassenOperation.view = myActualView;
                ;
    break;}
case 124:
#line 1258 "CTYacc.y"
{ 
                 aKlassenOperation.isAbstract = myIsVirtual;
                 if (myIsVirtual) {
                   aKlasse.isAbstract = true;
                   };
                 myIsVirtual = false;
                 ostrstream os;
                 os << "[CTYacc] DESTRUCTOR OPERATION ADDED: " << aKlassenOperation.name;
                 Report::debug(os);
                 aKlasse.KlassenOperationenListe.append(aKlassenOperation);
                 delete yyvsp[-5].string;
               ;
    break;}
case 126:
#line 1274 "CTYacc.y"
{
             delete yyvsp[0].string;
           ;
    break;}
case 129:
#line 1284 "CTYacc.y"
{
                          delete yyvsp[-1].string;
                        ;
    break;}
case 130:
#line 1292 "CTYacc.y"
{ 
                    aKlassenOperation.clean();
                    aKlassenOperation.name = *yyvsp[0].string;
                    aKlassenOperation.type = myActualType;
                    aKlassenOperation.ptr = myActualPointer;
                    myActualType = "";
                    myActualPointer = "";
                    aKlassenOperation.view = myActualView;
                    aKlassenOperation.isAbstract = myIsVirtual;
                    if (myIsVirtual) {
                      aKlasse.isAbstract = true;
                      };
                    myIsVirtual = false;
                  ;
    break;}
case 131:
#line 1307 "CTYacc.y"
{ 
                    ostrstream os;
                    os << "[CTYacc] OPERATION ADDED: " << aKlassenOperation.name;
                    Report::debug(os);
                    aKlasse.KlassenOperationenListe.append(aKlassenOperation);
                    delete yyvsp[-5].string;
                    delete yyvsp[-2].string;
                    delete yyvsp[0].string;
                  ;
    break;}
case 132:
#line 1319 "CTYacc.y"
{ 
                        yyval.string = yyvsp[0].string;
                      ;
    break;}
case 133:
#line 1326 "CTYacc.y"
{ 
                        myActualPointer += *yyvsp[-1].string;
                        yyval.string = yyvsp[0].string;
                        delete yyvsp[-1].string; 
                      ;
    break;}
case 134:
#line 1332 "CTYacc.y"
{ 
                        yyval.string = new RCString ("(" + *yyvsp[-1].string + ")");
                        delete yyvsp[-1].string; 
                      ;
    break;}
case 135:
#line 1337 "CTYacc.y"
{ 
                        yyval.string = new RCString ("(" + *yyvsp[-2].string + *yyvsp[-1].string + ")");
                        delete yyvsp[-2].string;
                        delete yyvsp[-1].string; 
                      ;
    break;}
case 137:
#line 1346 "CTYacc.y"
{
                                  delete yyvsp[-1].string;
                                ;
    break;}
case 138:
#line 1352 "CTYacc.y"
{
                          delete yyvsp[-3].string;
                          delete yyvsp[-1].string;
                        ;
    break;}
case 139:
#line 1357 "CTYacc.y"
{
                          delete yyvsp[-2].string;
                        ;
    break;}
case 141:
#line 1366 "CTYacc.y"
{
                          yyval.string = new RCString(*yyvsp[-2].string + ", " + *yyvsp[0].string);
                          delete yyvsp[-2].string;
                          delete yyvsp[-1].string;
                          delete yyvsp[0].string;
                        ;
    break;}
case 142:
#line 1375 "CTYacc.y"
{
                          yyval.string = new RCString(*yyvsp[-2].string + " = " + *yyvsp[0].string);
                          delete yyvsp[-2].string;
                          delete yyvsp[0].string;
                        ;
    break;}
case 145:
#line 1389 "CTYacc.y"
{
                            yyval.string = new RCString(*yyvsp[-1].string + *yyvsp[0].string);
                            delete yyvsp[-1].string;
                            delete yyvsp[0].string;
                          ;
    break;}
case 149:
#line 1399 "CTYacc.y"
{ yyval.string = new RCString("!"); ;
    break;}
case 150:
#line 1400 "CTYacc.y"
{ yyval.string = new RCString("%"); ;
    break;}
case 151:
#line 1401 "CTYacc.y"
{ yyval.string = new RCString("^"); ;
    break;}
case 152:
#line 1402 "CTYacc.y"
{ yyval.string = new RCString("&"); ;
    break;}
case 153:
#line 1403 "CTYacc.y"
{ yyval.string = new RCString("*"); ;
    break;}
case 154:
#line 1404 "CTYacc.y"
{ yyval.string = new RCString("()"); ;
    break;}
case 155:
#line 1405 "CTYacc.y"
{ yyval.string = new RCString("-"); ;
    break;}
case 156:
#line 1406 "CTYacc.y"
{ yyval.string = new RCString("+"); ;
    break;}
case 157:
#line 1407 "CTYacc.y"
{ yyval.string = new RCString("="); ;
    break;}
case 158:
#line 1408 "CTYacc.y"
{ yyval.string = new RCString("|"); ;
    break;}
case 159:
#line 1409 "CTYacc.y"
{ yyval.string = new RCString("~"); ;
    break;}
case 160:
#line 1410 "CTYacc.y"
{ yyval.string = new RCString("[]"); ;
    break;}
case 161:
#line 1411 "CTYacc.y"
{ yyval.string = new RCString("<"); ;
    break;}
case 162:
#line 1412 "CTYacc.y"
{ yyval.string = new RCString(">"); ;
    break;}
case 163:
#line 1413 "CTYacc.y"
{ yyval.string = new RCString("/"); ;
    break;}
case 164:
#line 1414 "CTYacc.y"
{ yyval.string = new RCString(","); ;
    break;}
case 165:
#line 1415 "CTYacc.y"
{ yyval.string = new RCString("->"); ;
    break;}
case 166:
#line 1416 "CTYacc.y"
{ yyval.string = new RCString("++"); ;
    break;}
case 167:
#line 1417 "CTYacc.y"
{ yyval.string = new RCString("--"); ;
    break;}
case 168:
#line 1418 "CTYacc.y"
{ yyval.string = new RCString("->*"); ;
    break;}
case 169:
#line 1419 "CTYacc.y"
{ yyval.string = new RCString("<<"); ;
    break;}
case 170:
#line 1420 "CTYacc.y"
{ yyval.string = new RCString(">>"); ;
    break;}
case 171:
#line 1421 "CTYacc.y"
{ yyval.string = new RCString("<="); ;
    break;}
case 172:
#line 1422 "CTYacc.y"
{ yyval.string = new RCString(">="); ;
    break;}
case 173:
#line 1423 "CTYacc.y"
{ yyval.string = new RCString("=="); ;
    break;}
case 174:
#line 1424 "CTYacc.y"
{ yyval.string = new RCString("!="); ;
    break;}
case 175:
#line 1425 "CTYacc.y"
{ yyval.string = new RCString("&&"); ;
    break;}
case 176:
#line 1426 "CTYacc.y"
{ yyval.string = new RCString("||"); ;
    break;}
case 177:
#line 1427 "CTYacc.y"
{ yyval.string = new RCString("*="); ;
    break;}
case 178:
#line 1428 "CTYacc.y"
{ yyval.string = new RCString("/="); ;
    break;}
case 179:
#line 1429 "CTYacc.y"
{ yyval.string = new RCString("%="); ;
    break;}
case 180:
#line 1430 "CTYacc.y"
{ yyval.string = new RCString("+="); ;
    break;}
case 181:
#line 1431 "CTYacc.y"
{ yyval.string = new RCString("-="); ;
    break;}
case 182:
#line 1432 "CTYacc.y"
{ yyval.string = new RCString("<<="); ;
    break;}
case 183:
#line 1433 "CTYacc.y"
{ yyval.string = new RCString(">>="); ;
    break;}
case 184:
#line 1434 "CTYacc.y"
{ yyval.string = new RCString("&="); ;
    break;}
case 185:
#line 1435 "CTYacc.y"
{ yyval.string = new RCString("^="); ;
    break;}
case 186:
#line 1436 "CTYacc.y"
{ yyval.string = new RCString("|="); ;
    break;}
case 187:
#line 1440 "CTYacc.y"
{
                               yyval.string = new RCString(*yyvsp[-1].string + *yyvsp[0].string);
                               delete yyvsp[-1].string;
                               delete yyvsp[0].string;
                             ;
    break;}
case 188:
#line 1448 "CTYacc.y"
{
                         yyval.string = yyvsp[0].string;
                       ;
    break;}
case 189:
#line 1452 "CTYacc.y"
{
                         yyval.string = new RCString(*yyvsp[-1].string + " " + *yyvsp[0].string);
                         delete yyvsp[-1].string;
                         delete yyvsp[0].string;
                       ;
    break;}
case 192:
#line 1464 "CTYacc.y"
{
                          yyval.string = new RCString(*yyvsp[-3].string + "<" + *yyvsp[-1].string + ">");
                          delete yyvsp[-3].string;
                          delete yyvsp[-1].string;
                          myMemberIsTemplate = true;
                        ;
    break;}
case 195:
#line 1477 "CTYacc.y"
{
                       yyval.string = new RCString(*yyvsp[-2].string + ", " + *yyvsp[0].string);
                       delete yyvsp[-2].string;
                       delete yyvsp[-1].string;
                       delete yyvsp[0].string;
                     ;
    break;}
case 197:
#line 1490 "CTYacc.y"
{
              yyval.string = new RCString(*yyvsp[-1].string + " " + *yyvsp[0].string);
              delete yyvsp[-1].string;
              delete yyvsp[0].string;
            ;
    break;}
case 198:
#line 1496 "CTYacc.y"
{
              yyval.string = new RCString(*yyvsp[-2].string + " " + *yyvsp[-1].string + " " + *yyvsp[0].string);
              delete yyvsp[-2].string;
              delete yyvsp[-1].string;
              delete yyvsp[0].string;
            ;
    break;}
case 199:
#line 1505 "CTYacc.y"
{
                           yyval.string = new RCString(*yyvsp[-1].string + *yyvsp[0].string);
                           delete yyvsp[-1].string;
                           delete yyvsp[0].string;
                         ;
    break;}
case 200:
#line 1511 "CTYacc.y"
{
                           yyval.string = new RCString(*yyvsp[-4].string + "(" + *yyvsp[-2].string + ")" + *yyvsp[0].string);
                           delete yyvsp[-4].string;
                           delete yyvsp[-2].string;
                           delete yyvsp[0].string;
                         ;
    break;}
case 201:
#line 1518 "CTYacc.y"
{
                           yyval.string = new RCString(*yyvsp[-3].string + "[" + *yyvsp[-1].string + "]");
                           delete yyvsp[-3].string;
                           delete yyvsp[-1].string;
                         ;
    break;}
case 202:
#line 1524 "CTYacc.y"
{
                           yyval.string = new RCString("(" + *yyvsp[-1].string + ")");
                           delete yyvsp[-1].string;
                         ;
    break;}
case 203:
#line 1531 "CTYacc.y"
{
                              yyval.string = new RCString("");
                            ;
    break;}
case 205:
#line 1538 "CTYacc.y"
{
                            yyval.string = new RCString("");
                          ;
    break;}
case 207:
#line 1545 "CTYacc.y"
{
                        delete yyvsp[-3].string;
                        delete yyvsp[-2].string;
                      ;
    break;}
case 208:
#line 1550 "CTYacc.y"
{
                        delete yyvsp[-2].string;
                      ;
    break;}
}

#line 697 "/Home/origin/matthey/lib/bison.cc"
   /* the action file gets copied in in place of this dollarsign  */
  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YY_CTYacc_LSP_NEEDED
  yylsp -= yylen;
#endif

#if YY_CTYacc_DEBUG != 0
  if (YY_CTYacc_DEBUG_FLAG)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YY_CTYacc_LSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = YY_CTYacc_LLOC.first_line;
      yylsp->first_column = YY_CTYacc_LLOC.first_column;
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

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++YY_CTYacc_NERRS;

#ifdef YY_CTYacc_ERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  for (x = 0; x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = 0; x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      YY_CTYacc_ERROR(msg);
	      free(msg);
	    }
	  else
	    YY_CTYacc_ERROR ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YY_CTYacc_ERROR_VERBOSE */
	YY_CTYacc_ERROR("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (YY_CTYacc_CHAR == YYEOF)
	YYABORT;

#if YY_CTYacc_DEBUG != 0
      if (YY_CTYacc_DEBUG_FLAG)
	fprintf(stderr, "Discarding token %d (%s).\n", YY_CTYacc_CHAR, yytname[yychar1]);
#endif

      YY_CTYacc_CHAR = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;              /* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YY_CTYacc_LSP_NEEDED
  yylsp--;
#endif

#if YY_CTYacc_DEBUG != 0
  if (YY_CTYacc_DEBUG_FLAG)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YY_CTYacc_DEBUG != 0
  if (YY_CTYacc_DEBUG_FLAG)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = YY_CTYacc_LVAL;
#ifdef YY_CTYacc_LSP_NEEDED
  *++yylsp = YY_CTYacc_LLOC;
#endif

  yystate = yyn;
  goto yynewstate;
}

/* END */

/* #line 891 "/Home/origin/matthey/lib/bison.cc" */
#line 1568 "CTYacc.y"
