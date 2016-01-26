/*
 * ShaderLex.l
 *
 * Copyright (C) 1995-96, Thomas Teuscher <teuscher@iam.unibe.ch>
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
 *  $Id: ShaderLex.l,v 1.4 1996/06/06 11:49:46 streit Exp $
 * -----------------------------------------------------------------------------
 */

%name ShaderLex

%header{
#include "ShaderYacc.h"
#include "booga/texture/ShaderNode.h"
%}

%define MEMBERS                                                  \
  public:                                                        \
    void setParseFile(FILE* parseFile) {yyin = parseFile;}       \
    const char* getToken() { return yytext;}                     \
    int getLineNo() {return myLineNo;}                           \
  private:                                                       \
    int myLineNo;                                                \

%define LEX scan
%define LEX_PARAM YY_ShaderYacc_STYPE& yylval
%define CONSTRUCTOR_INIT : myLineNo(1)

LETTER			[a-zA-Z_]
DIGIT			[0-9]
E                       [Ee][+-]?{DIGIT}+
OTHER			.

%x SKIP_REST_OF_LINE

%%

"+"		return *yytext;
"-"		return *yytext;
"*"		return *yytext;
"/"		return *yytext;
"%"               return *yytext;
"^"               return *yytext;
";"		return *yytext;
"."		return *yytext;
","		return *yytext;
":"		return *yytext;
"("		return *yytext;
")"		return *yytext;
"["		return *yytext;
"]"		return *yytext;
"{"		return *yytext;
"}"		return *yytext;
"="		return *yytext;
">"		return *yytext;
"<"		return *yytext;
"&&"              return ShaderYacc::AND;
"||"              return ShaderYacc::OR;
">="		return ShaderYacc::GE;
"<="		return ShaderYacc::LE;
"=="		return ShaderYacc::EQ;
"!="		return ShaderYacc::NE;
"+="		return ShaderYacc::PE;
"-="		return ShaderYacc::ME;
"*="		return ShaderYacc::TE;
"/="		return ShaderYacc::DE;
"%="		return ShaderYacc::RE;
"++"		return ShaderYacc::PP;
"--"		return ShaderYacc::MM;

"vector"	         return ShaderYacc::VECTOR;
"color"		return ShaderYacc::COLOR;
"else"		return ShaderYacc::ELSE;
"for"		return ShaderYacc::FOR;
"if"		return ShaderYacc::IF;
"real"		return ShaderYacc::REAL;
"string"          return ShaderYacc::STRING;
"while"           return ShaderYacc::WHILE;
"surface"         return ShaderYacc::SURFACE;
"PI"              return ShaderYacc::PI;
"shader"          return ShaderYacc::SHADER;

"//"                            {
                                  BEGIN(SKIP_REST_OF_LINE);
                                }        

{DIGIT}*"."{DIGIT}+({E})? |
{DIGIT}+"."{DIGIT}*({E})? |
{DIGIT}+({E})?  		{
                                  yylval.number = atof(yytext);
                                  return ShaderYacc::NUMBER;
                                }

{LETTER}*({LETTER}|{DIGIT})*    {
                                  yylval.id = new RCString(yytext);
                                  return ShaderYacc::IDENTIFIER;
				}
				
\"{LETTER}*({LETTER}|{DIGIT}|".")*\"    {
                                  yylval.id = new RCString(yytext);
                                  return ShaderYacc::ANYSTRING;
				}

\n          			{ 
                                  myLineNo++;
                                }
                                
<SKIP_REST_OF_LINE>.            ;

<SKIP_REST_OF_LINE>\n           {
                                  myLineNo++;
                                  BEGIN(0);
                                 }

{OTHER}                         ;
                                   
%%
