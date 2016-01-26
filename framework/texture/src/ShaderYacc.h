#ifndef YY_ShaderYacc_h_included
#define YY_ShaderYacc_h_included

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
#include <stdio.h>

/* #line 14 "/usr/local/lib/bison.h" */
#line 21 "ShaderYacc.h"
#line 26 "/home/fcg/BOOGA/workspaces/core-dev/shared_src/framework/texture/src/ShaderYacc.y"


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

#line 14 "/usr/local/lib/bison.h"
 /* %{ and %header{ and %union, during decl */
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
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
/* use %define LTYPE */
#endif
#endif
#ifdef YYSTYPE
#ifndef YY_ShaderYacc_STYPE 
#define YY_ShaderYacc_STYPE YYSTYPE
/* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
/* use %define STYPE */
#endif
#endif
#ifdef YYDEBUG
#ifndef YY_ShaderYacc_DEBUG
#define  YY_ShaderYacc_DEBUG YYDEBUG
/* WARNING obsolete !!! user defined YYDEBUG not reported into generated header */
/* use %define DEBUG */
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

/* #line 63 "/usr/local/lib/bison.h" */
#line 141 "ShaderYacc.h"

#line 63 "/usr/local/lib/bison.h"
/* YY_ShaderYacc_PURE */
#endif

/* #line 65 "/usr/local/lib/bison.h" */
#line 148 "ShaderYacc.h"

#line 65 "/usr/local/lib/bison.h"
/* prefix */
#ifndef YY_ShaderYacc_DEBUG

/* #line 67 "/usr/local/lib/bison.h" */
#line 155 "ShaderYacc.h"

#line 67 "/usr/local/lib/bison.h"
/* YY_ShaderYacc_DEBUG */
#endif
#ifndef YY_ShaderYacc_LSP_NEEDED

/* #line 70 "/usr/local/lib/bison.h" */
#line 163 "ShaderYacc.h"

#line 70 "/usr/local/lib/bison.h"
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

/* TOKEN C */
#ifndef YY_USE_CLASS

#ifndef YY_ShaderYacc_PURE
extern YY_ShaderYacc_STYPE YY_ShaderYacc_LVAL;
#endif


/* #line 143 "/usr/local/lib/bison.h" */
#line 241 "ShaderYacc.h"
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


#line 143 "/usr/local/lib/bison.h"
 /* #defines token */
/* after #define tokens, before const tokens S5*/
#else
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

/* #line 182 "/usr/local/lib/bison.h" */
#line 315 "ShaderYacc.h"
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


#line 182 "/usr/local/lib/bison.h"
 /* decl const */
#else
enum YY_ShaderYacc_ENUM_TOKEN { YY_ShaderYacc_NULL_TOKEN=0

/* #line 185 "/usr/local/lib/bison.h" */
#line 353 "ShaderYacc.h"
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


#line 185 "/usr/local/lib/bison.h"
 /* enum token */
     }; /* end of enum declaration */
#endif
public:
 int YY_ShaderYacc_PARSE(YY_ShaderYacc_PARSE_PARAM);
 virtual void YY_ShaderYacc_ERROR(char *msg) YY_ShaderYacc_ERROR_BODY;
#ifdef YY_ShaderYacc_PURE
#ifdef YY_ShaderYacc_LSP_NEEDED
 virtual int  YY_ShaderYacc_LEX(YY_ShaderYacc_STYPE *YY_ShaderYacc_LVAL,YY_ShaderYacc_LTYPE *YY_ShaderYacc_LLOC) YY_ShaderYacc_LEX_BODY;
#else
 virtual int  YY_ShaderYacc_LEX(YY_ShaderYacc_STYPE *YY_ShaderYacc_LVAL) YY_ShaderYacc_LEX_BODY;
#endif
#else
 virtual int YY_ShaderYacc_LEX() YY_ShaderYacc_LEX_BODY;
 YY_ShaderYacc_STYPE YY_ShaderYacc_LVAL;
#ifdef YY_ShaderYacc_LSP_NEEDED
 YY_ShaderYacc_LTYPE YY_ShaderYacc_LLOC;
#endif
 int YY_ShaderYacc_NERRS;
 int YY_ShaderYacc_CHAR;
#endif
#if YY_ShaderYacc_DEBUG != 0
public:
 int YY_ShaderYacc_DEBUG_FLAG;	/*  nonzero means print parse trace	*/
#endif
public:
 YY_ShaderYacc_CLASS(YY_ShaderYacc_CONSTRUCTOR_PARAM);
public:
 YY_ShaderYacc_MEMBERS 
};
/* other declare folow */
#endif


#if YY_ShaderYacc_COMPATIBILITY != 0
/* backward compatibility */
#ifndef YYSTYPE
#define YYSTYPE YY_ShaderYacc_STYPE
#endif

#ifndef YYLTYPE
#define YYLTYPE YY_ShaderYacc_LTYPE
#endif
#ifndef YYDEBUG
#ifdef YY_ShaderYacc_DEBUG 
#define YYDEBUG YY_ShaderYacc_DEBUG
#endif
#endif

#endif
/* END */

/* #line 236 "/usr/local/lib/bison.h" */
#line 439 "ShaderYacc.h"
#endif
