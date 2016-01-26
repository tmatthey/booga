/*
 * $RCSfile: BSDLLex.l,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
 *                        University of Berne, Switzerland
 *
 * All rights reserved.
 *
 * This software may be freely copied, modified and redistributed
 * provided that this copyright note be preserved on all copies.
 * 
 * You may not distribute this software, in whole or in part, as part
 * of any commercial product without the express consent of the author.
 *
 * There is no warranty or other guarantee of fitness of this software
 * for any purpose. It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: BSDLLex.l,v 1.4 1996/08/01 11:59:02 streit Exp $
 * -----------------------------------------------------------------------------
 */

%header{
#include "BSDLYacc.h"
%}

%{
#include <string.h>
%}

%name BSDLLex

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
%define LEX_PARAM YY_BSDLYacc_STYPE& yylval

DIGIT            [0-9]
E                [Ee][+-]?{DIGIT}+
LETTER           [a-zA-Z_]
SPECIAL          [\.:]
STRING           {LETTER}({LETTER}|{DIGIT}|{SPECIAL})*
FILENAME         \"([^\n\"])*\"

%x CPP_OUTPUT EAT_END_OF_LINE

%%

^#                      { // Handle output from C preprocessor.
			  BEGIN(CPP_OUTPUT);
			}
<CPP_OUTPUT>{DIGIT}+    { myCurrentLine = atoi(yytext); }
<CPP_OUTPUT>{FILENAME}  { myCurrentFilename = yytext;   
			  BEGIN(EAT_END_OF_LINE); // Skip rest of the current line.
			}
<CPP_OUTPUT>.           ;
<CPP_OUTPUT>\n          BEGIN 0;
 
"//"                    { // Allow C++ comments.
			  BEGIN(EAT_END_OF_LINE); // Skip rest of the current line.
			}

","        { return *yytext; }  
";"        { return *yytext; }  
"("        { return *yytext; }  
")"        { return *yytext; }  
"{"        { return *yytext; }  
"}"        { return *yytext; }  
"["        { return *yytext; }  
"]"        { return *yytext; }  
"+"        { return *yytext; }
"-"        { return *yytext; }
"*"        { return *yytext; }
"/"        { return *yytext; }

"define"    { return BSDLYacc::tDefine;    }
"const"     { return BSDLYacc::tConstant;  }
"namespace" { return BSDLYacc::tNamespace; }
"verbatim"  { return BSDLYacc::tVerbatim;  }
"using"     { return BSDLYacc::tUsing;     }

({SPECIAL}?{DIGIT}*{LETTER}({SPECIAL}?({LETTER}|{DIGIT})+)*{SPECIAL}?)?"::" { 
  //
  // Rule for Scope
  // 
  yytext[strlen(yytext)-2] = '\0'; // Remove trailing ::
  yylval.id = new Name(yytext);
  return BSDLYacc::SCOPE; 
}

{SPECIAL}?{DIGIT}*{LETTER}({SPECIAL}?({LETTER}|{DIGIT})+)*{SPECIAL}? { 
  //
  // Rule for Identifiers
  // 
  yylval.id = new Name(yytext);
  return BSDLYacc::IDENTIFIER; 
}

{DIGIT}*"."{DIGIT}+({E})? |
{DIGIT}+"."{DIGIT}*({E})? |
{DIGIT}+({E})? {
  //
  // Rule for Realnumbers:
  //
  //  Numbers of the form  1.2  .2  1e3  1.2e-4  .2e5
  //  are recognized.
  //
  yylval.number = atof(yytext);
  return BSDLYacc::NUMBER;
}


\"([^\n\"])*\" { 
  //
  // Rule for String values:
  //
  //   "any Text ..."
  //
  yytext[strlen(yytext)-1] = '\0'; // remove trailing "
  yylval.string = new RCString(yytext+1);

  return BSDLYacc::STRING;
}

[ \t]+  ;
\n      { myCurrentLine++; }
.       ;

<<EOF>> { yyterminate();   }

<EAT_END_OF_LINE>\n       { // myCurrentLine++;
			    BEGIN(0);
			  }
<EAT_END_OF_LINE>.        ;

%%

