#ifndef YY_BSDLYacc_h_included
#define YY_BSDLYacc_h_included

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
#line 21 "BSDLYacc.h"
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

#line 14 "/usr/local/lib/bison.h"
 /* %{ and %header{ and %union, during decl */
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
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
/* use %define LTYPE */
#endif
#endif
#ifdef YYSTYPE
#ifndef YY_BSDLYacc_STYPE 
#define YY_BSDLYacc_STYPE YYSTYPE
/* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
/* use %define STYPE */
#endif
#endif
#ifdef YYDEBUG
#ifndef YY_BSDLYacc_DEBUG
#define  YY_BSDLYacc_DEBUG YYDEBUG
/* WARNING obsolete !!! user defined YYDEBUG not reported into generated header */
/* use %define DEBUG */
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

/* #line 63 "/usr/local/lib/bison.h" */
#line 157 "BSDLYacc.h"

#line 63 "/usr/local/lib/bison.h"
/* YY_BSDLYacc_PURE */
#endif

/* #line 65 "/usr/local/lib/bison.h" */
#line 164 "BSDLYacc.h"

#line 65 "/usr/local/lib/bison.h"
/* prefix */
#ifndef YY_BSDLYacc_DEBUG

/* #line 67 "/usr/local/lib/bison.h" */
#line 171 "BSDLYacc.h"

#line 67 "/usr/local/lib/bison.h"
/* YY_BSDLYacc_DEBUG */
#endif
#ifndef YY_BSDLYacc_LSP_NEEDED

/* #line 70 "/usr/local/lib/bison.h" */
#line 179 "BSDLYacc.h"

#line 70 "/usr/local/lib/bison.h"
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

/* TOKEN C */
#ifndef YY_USE_CLASS

#ifndef YY_BSDLYacc_PURE
extern YY_BSDLYacc_STYPE YY_BSDLYacc_LVAL;
#endif


/* #line 143 "/usr/local/lib/bison.h" */
#line 257 "BSDLYacc.h"
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


#line 143 "/usr/local/lib/bison.h"
 /* #defines token */
/* after #define tokens, before const tokens S5*/
#else
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

/* #line 182 "/usr/local/lib/bison.h" */
#line 312 "BSDLYacc.h"
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


#line 182 "/usr/local/lib/bison.h"
 /* decl const */
#else
enum YY_BSDLYacc_ENUM_TOKEN { YY_BSDLYacc_NULL_TOKEN=0

/* #line 185 "/usr/local/lib/bison.h" */
#line 331 "BSDLYacc.h"
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


#line 185 "/usr/local/lib/bison.h"
 /* enum token */
     }; /* end of enum declaration */
#endif
public:
 int YY_BSDLYacc_PARSE(YY_BSDLYacc_PARSE_PARAM);
 virtual void YY_BSDLYacc_ERROR(char *msg) YY_BSDLYacc_ERROR_BODY;
#ifdef YY_BSDLYacc_PURE
#ifdef YY_BSDLYacc_LSP_NEEDED
 virtual int  YY_BSDLYacc_LEX(YY_BSDLYacc_STYPE *YY_BSDLYacc_LVAL,YY_BSDLYacc_LTYPE *YY_BSDLYacc_LLOC) YY_BSDLYacc_LEX_BODY;
#else
 virtual int  YY_BSDLYacc_LEX(YY_BSDLYacc_STYPE *YY_BSDLYacc_LVAL) YY_BSDLYacc_LEX_BODY;
#endif
#else
 virtual int YY_BSDLYacc_LEX() YY_BSDLYacc_LEX_BODY;
 YY_BSDLYacc_STYPE YY_BSDLYacc_LVAL;
#ifdef YY_BSDLYacc_LSP_NEEDED
 YY_BSDLYacc_LTYPE YY_BSDLYacc_LLOC;
#endif
 int YY_BSDLYacc_NERRS;
 int YY_BSDLYacc_CHAR;
#endif
#if YY_BSDLYacc_DEBUG != 0
public:
 int YY_BSDLYacc_DEBUG_FLAG;	/*  nonzero means print parse trace	*/
#endif
public:
 YY_BSDLYacc_CLASS(YY_BSDLYacc_CONSTRUCTOR_PARAM);
public:
 YY_BSDLYacc_MEMBERS 
};
/* other declare folow */
#endif


#if YY_BSDLYacc_COMPATIBILITY != 0
/* backward compatibility */
#ifndef YYSTYPE
#define YYSTYPE YY_BSDLYacc_STYPE
#endif

#ifndef YYLTYPE
#define YYLTYPE YY_BSDLYacc_LTYPE
#endif
#ifndef YYDEBUG
#ifdef YY_BSDLYacc_DEBUG 
#define YYDEBUG YY_BSDLYacc_DEBUG
#endif
#endif

#endif
/* END */

/* #line 236 "/usr/local/lib/bison.h" */
#line 398 "BSDLYacc.h"
#endif
