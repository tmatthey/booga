#ifndef YY_CTYacc_h_included
#define YY_CTYacc_h_included

#line 1 "/Home/origin/matthey/lib/bison.h"
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
#include <stdio.h>

/* #line 14 "/Home/origin/matthey/lib/bison.h" */
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

#line 14 "/Home/origin/matthey/lib/bison.h"
 /* %{ and %header{ and %union, during decl */
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
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
/* use %define LTYPE */
#endif
#endif
#ifdef YYSTYPE
#ifndef YY_CTYacc_STYPE 
#define YY_CTYacc_STYPE YYSTYPE
/* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
/* use %define STYPE */
#endif
#endif
#ifdef YYDEBUG
#ifndef YY_CTYacc_DEBUG
#define  YY_CTYacc_DEBUG YYDEBUG
/* WARNING obsolete !!! user defined YYDEBUG not reported into generated header */
/* use %define DEBUG */
#endif
#endif
#ifdef YY_CTYacc_STYPE
#ifndef yystype
#define yystype YY_CTYacc_STYPE
#endif
#endif
#endif

#ifndef YY_CTYacc_PURE

/* #line 54 "/Home/origin/matthey/lib/bison.h" */

#line 54 "/Home/origin/matthey/lib/bison.h"
/* YY_CTYacc_PURE */
#endif

/* #line 56 "/Home/origin/matthey/lib/bison.h" */

#line 56 "/Home/origin/matthey/lib/bison.h"
/* prefix */
#ifndef YY_CTYacc_DEBUG

/* #line 58 "/Home/origin/matthey/lib/bison.h" */

#line 58 "/Home/origin/matthey/lib/bison.h"
/* YY_CTYacc_DEBUG */
#endif
#ifndef YY_CTYacc_LSP_NEEDED

/* #line 61 "/Home/origin/matthey/lib/bison.h" */

#line 61 "/Home/origin/matthey/lib/bison.h"
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
#ifndef YY_USE_CLASS

#ifndef YY_CTYacc_PURE
extern YY_CTYacc_STYPE YY_CTYacc_LVAL;
#endif


/* #line 134 "/Home/origin/matthey/lib/bison.h" */
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


#line 134 "/Home/origin/matthey/lib/bison.h"
 /* #defines token */
/* after #define tokens, before const tokens S5*/
#else
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

class YY_CTYacc_CLASS YY_CTYacc_INHERIT
{
public: /* static const int token ... */

/* #line 160 "/Home/origin/matthey/lib/bison.h" */
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


#line 160 "/Home/origin/matthey/lib/bison.h"
 /* decl const */
public:
 int YY_CTYacc_PARSE(YY_CTYacc_PARSE_PARAM);
 virtual void YY_CTYacc_ERROR(char *) YY_CTYacc_ERROR_BODY;
#ifdef YY_CTYacc_PURE
#ifdef YY_CTYacc_LSP_NEEDED
 virtual int  YY_CTYacc_LEX(YY_CTYacc_STYPE *YY_CTYacc_LVAL,YY_CTYacc_LTYPE *YY_CTYacc_LLOC) YY_CTYacc_LEX_BODY;
#else
 virtual int  YY_CTYacc_LEX(YY_CTYacc_STYPE *YY_CTYacc_LVAL) YY_CTYacc_LEX_BODY;
#endif
#else
 virtual int YY_CTYacc_LEX() YY_CTYacc_LEX_BODY;
 YY_CTYacc_STYPE YY_CTYacc_LVAL;
#ifdef YY_CTYacc_LSP_NEEDED
 YY_CTYacc_LTYPE YY_CTYacc_LLOC;
#endif
 int YY_CTYacc_NERRS;
 int YY_CTYacc_CHAR;
#endif
#if YY_CTYacc_DEBUG != 0
public:
 int YY_CTYacc_DEBUG_FLAG;	/*  nonzero means print parse trace	*/
#endif
public:
 YY_CTYacc_CLASS(YY_CTYacc_CONSTRUCTOR_PARAM);
public:
 YY_CTYacc_MEMBERS 
};
/* other declare folow */
#endif


#if YY_CTYacc_COMPATIBILITY != 0
/* backward compatibility */
#ifndef YYSTYPE
#define YYSTYPE YY_CTYacc_STYPE
#endif

#ifndef YYLTYPE
#define YYLTYPE YY_CTYacc_LTYPE
#endif
#ifndef YYDEBUG
#ifdef YY_CTYacc_DEBUG 
#define YYDEBUG YY_CTYacc_DEBUG
#endif
#endif

#endif
/* END */

/* #line 209 "/Home/origin/matthey/lib/bison.h" */
#endif
