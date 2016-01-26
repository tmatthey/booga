/*
 * ShaderYacc.y
 *
 * Copyright (C) 1995-96, Thomas Teuscher <teuscher@iam.unibe.ch>
 *                        University of Berne, Switzerland
 *
 * All rights reserved.
 *
 * This software may be freely copied, modified, and redistributed
 * provided that this copyright notice is preserved on all copies.
 *
 * You may not distribute this software, in whole or in part, as part of
 * any commercial product without the express consent of the authors.
 *
 * There is no warranty or other guarantee of fitness of this software
 * for any purpose. It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: ShaderYacc.y,v 1.4 1996/06/06 11:49:53 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
 
%name ShaderYacc

%header{

#include <iostream>
#include <cstring>

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

%}

%union {
        Real                    number;
	RCString*		id;
	List<NVPair*>*	        nvlist;
	ShaderNode*            	node;
        ShaderExpNode*          expnode;
        List<ShaderExpNode*>*   expnodelist;
        ShaderIdExpNode*        idexpnode;
	List<ShaderNode*>*      nodelist;
	}

%define DEBUG 1
%define DEBUG_FLAG myParserDebugFlag
%define ERROR_VERBOSE

%define ERROR_BODY =0
%define ERROR fatalError
%define NERRS myErrorCount

%define LEX_BODY =0
%define LEX scan
%define LVAL myTokenValue

%define PARSE parse
%define PARSE_PARAM
%define CONSTRUCTOR_PARAM 
%define CONSTRUCTOR_INIT : myParserDebugFlag(0)
%define CONSTRUCTOR_CODE

%define MEMBERS                                \
public:                                        \
  ShaderProgNode* getParseTree() {return myParseTree;}    \
private:                                        \
  virtual void recoverableError(const RCString& errorMsg) = 0; \
  virtual void warning(const RCString& warnMsg) = 0; \
private:                                       \
  ShaderProgNode* myParseTree;


%token <id>	IDENTIFIER
%token <number> NUMBER
%token		SURFACE
%token 		COLOR
%token 		VECTOR
%token 		REAL
%token          STRING    // reserved keyword for string declarations
%token <id>     ANYSTRING // contents of an arbitrary string value.
%token		IF
%token		ELSE
%token		FOR
%token          WHILE
%token          AND
%token          OR
%token          NOT
%token          SHADER
%token		GE
%token		LE
%token		EQ
%token		NE
%token		PE
%token		ME
%token		TE
%token		DE
%token		RE
%token		PP
%token		MM
%token          UMINUS
%token          PI

%right '=' PE ME TE DE RE
%left OR
%left AND
%left EQ NE
%left '<' '>' GE LE
%left '+' '-'
%left '*' '/' '%'
%left '^'
%left NOT UMINUS
%right PP MM

%start program
%type <node>        program head parameter declaration compound_statement statement
%type <expnode>     expression parexp binary value optional_init
%type <expnodelist> arguments
%type <idexpnode>   Identifier
%type <nodelist>    parameters declarations statements
%type <nvlist>      declarator_list
%type <id>          valid_type shader_type

%%

program              
       :
                {
                  ShaderNode::enterBlock();
                }
                
          head compound_statement
                {
		  $$ = new ShaderProgNode($2, $3);
		  myParseTree = (ShaderProgNode*)$$;
                  ShaderNode::leaveBlock();
		}

head
        : shader_type IDENTIFIER '(' parameters ')'
                {
                  $$ = new ShaderHeadNode($1, $2, $4);
                }

shader_type
        : SURFACE
                {
                  $$ = new RCString("surface");
                }

parameters
        :
                {
                  $$ = NULL;
                }

        | parameter
                {
                   $$ = new List<ShaderNode*>(1);
                   $$->append($1);
                }
        
        | parameters ',' parameter
		{
                  $$ = $1;
                  $$->append($3);
                }
			  
parameter
        : IDENTIFIER optional_init
		{
		  RCString* tempstring = new RCString("real");
                  List<NVPair*>* templist;
                  NVPair* newPair = new NVPair($1, $2);
                  templist = new List<NVPair*>(1);
                  templist->append(newPair);
                  RCString warnMsg;
                  $$ = new ShaderDeclNode(warnMsg, tempstring, templist);
                  if(!warnMsg.isEmpty())
                    warning(warnMsg);
                }

        | valid_type IDENTIFIER optional_init
		{
                  List<NVPair*>* temp;
                  NVPair* newPair = new NVPair($2, $3);
                  temp = new List<NVPair*>(1);
                  temp->append(newPair);
                  RCString warnMsg;
                  $$ = new ShaderDeclNode(warnMsg, $1, temp);
                  if (!warnMsg.isEmpty())
                    warning(warnMsg);
                }

compound_statement
	:
                {
                  ShaderNode::enterBlock();
                }
                
           '{' declarations statements '}'
                {  
		  $$ = new ShaderCmpStmtNode($3, $4);
                  ShaderNode::leaveBlock();		
                }
		
declarations
	: 
		{
		  $$ = NULL;
		}
	
	| declarations declaration
		{
		  if ($1) {
		    $$ = $1;
		    if ($2)
		      $$->append($2);
		  }     
		  else
		    if ($2) {
		      $$ = new List<ShaderNode*>(1);
		      $$->append($2);
		  }
		  
		  yyerrok;
		}
		
        | declarations error        
			  
declaration	
	: valid_type declarator_list ';'
		{
                  RCString warnMsg;
                  $$ = new ShaderDeclNode(warnMsg, $1, $2);
                  if (!warnMsg.isEmpty())
                    warning(warnMsg);
		}
	
valid_type
	: REAL
		{
		  $$ = new RCString("real");
		}
		
	| COLOR
		{
		  $$ = new RCString("color");
		}
		
	| VECTOR
		{
		  $$ = new RCString("vector");
		}

	| STRING
		{
		  $$ = new RCString("string");
		}
		
declarator_list
	: IDENTIFIER optional_init
		{
                  NVPair* newPair = new NVPair($1, $2);
                  $$ = new List<NVPair*>(1);
                  $$->append(newPair);
		}
		
	| declarator_list ',' IDENTIFIER optional_init
		{
                  $$ = $1;
                  NVPair* newPair = new NVPair($3, $4);
                  $$->append(newPair);
		}
        
optional_init
        :
                {
                  $$ = NULL;
                }
                
        | '=' expression
                {
                  $$ = $2;
                }
                 		
statements
	:	
		{
		  $$ = NULL;
		}

	| statements statement
		{
		  if ($1) {
		    $$ = $1;
		    if ($2)
		      $$->append($2);
		  }     
		  else
		    if ($2) {
		      $$ = new List<ShaderNode*>(1);
		      $$->append($2);
		    }
		    
                  yyerrok;
		}
        
        | statements error
	
statement
	: expression ';'
		{
		  $$ = new ShaderStmtNode($1);
		}
	
	| ';' 
		{
		  $$ = NULL;
		}
        
        | compound_statement
                {
                  $$ = new ShaderCmpStmtNode((const ShaderCmpStmtNode&) *$1);
                }

        | IF '(' expression ')' statement 
                {
                  $$ = new ShaderIfNode($3, $5);
                }
                        
        | IF '(' expression ')' statement ELSE statement
                {
                  $$ = new ShaderIfThenElseNode($3, $5, $7);
                }

        | FOR '(' expression ';' expression ';' expression ')' statement
                {
                  $$ = new ShaderForNode($3, $5, $7, $9);
                }

        | WHILE '(' expression ')' statement
                {
                  $$ = new ShaderWhileNode($3, $5);
                }
                
        | SHADER '(' arguments ')' ';'
                {
                  $$ = new ShaderShaderNode($3);
                }
        
expression       
        : binary
                {
                  $$ = $1;
                } 

binary 
        : value
                {
                  $$ = $1;
                }

        | '-' value %prec UMINUS
                {
                  ShaderExpNode* temp = new ShaderRealValueNode(-1.0);
                  $$ = new ShaderArithExpNode('*', temp, $2);
                }
                
        | IDENTIFIER '(' arguments ')'
                {
                  RCString errMsg;
                  $$ = new ShaderFuncNode(errMsg, $1, $3);
                  if (!errMsg.isEmpty())
                    recoverableError(errMsg);
                }

        | '-' IDENTIFIER '(' arguments ')' %prec UMINUS
                {
                  RCString errMsg;
                  ShaderExpNode* temp1 = new ShaderRealValueNode(-1.0);
                  ShaderFuncNode* temp2 = new ShaderFuncNode(errMsg, $2, $4);
                  if (!errMsg.isEmpty())
                    recoverableError(errMsg);
                  $$ = new ShaderArithExpNode('*', temp1, temp2);
                }

        | Identifier

                {
                  $$ = $1;
                }

        | '-' Identifier %prec UMINUS
                {
                  ShaderExpNode* temp = new ShaderRealValueNode(-1.0);
                  $$ = new ShaderArithExpNode('*', temp, $2);
                }
                
        | Identifier PP
                {
                  ShaderExpNode* temp1 = new ShaderRealValueNode(1.0);
                  ShaderExpNode* temp2 = new ShaderArithExpNode('+', $1, temp1);
                  $$ = new ShaderAssExpNode($1, temp2);
                }
                
        | Identifier MM
                {
                  ShaderExpNode* temp1 = new ShaderRealValueNode(1.0);
                  ShaderExpNode* temp2 = new ShaderArithExpNode('-', $1, temp1);
                  $$ = new ShaderAssExpNode($1, temp2);
                }
                
        | parexp
                {
                  $$ = $1;
                }
                
        | '-' parexp %prec UMINUS
                {
                  ShaderExpNode* temp = new ShaderRealValueNode(-1.0);
                  $$ = new ShaderArithExpNode('*', temp, $2);
                }
                
        | binary '+' binary
                {
                  $$ = new ShaderArithExpNode('+', $1, $3)
                }

        | binary '-' binary
                {
                  $$ = new ShaderArithExpNode('-', $1, $3)
                }

        | binary '*' binary
                {
                  $$ = new ShaderArithExpNode('*', $1, $3)
                }

        | binary '/' binary
                {
                  $$ = new ShaderArithExpNode('/', $1, $3)
                }

        | binary '%' binary
                {
                  $$ = new ShaderArithExpNode('%', $1, $3)
                }
        
        | binary '^' binary
                {
                  $$ = new ShaderArithExpNode('^', $1, $3)
                }
       
        | binary AND binary
                {
                  $$ = new ShaderLogicExpNode((char*)"&&", $1, $3)
                }
       
        | binary OR binary
                {
                  $$ = new ShaderLogicExpNode((char*)"||", $1, $3)
                }
       
        | NOT binary
                {
                  $$ = new ShaderLogicExpNode((char*)"!", $2)
                }
       
        | binary '>' binary
                {
                  $$ = new ShaderCompExpNode((char*)">", $1, $3)
                }
        
        | binary '<' binary
                {
                  $$ = new ShaderCompExpNode((char*)"<", $1, $3)
                }
        
        | binary GE binary
                {
                  $$ = new ShaderCompExpNode((char*)">=", $1, $3)
                }
        
        | binary LE binary
                {
                  $$ = new ShaderCompExpNode((char*)"<=", $1, $3)
                }
        
        | binary EQ binary
                {
                  $$ = new ShaderCompExpNode((char*)"==", $1, $3)
                }
        
        | binary NE binary
                {
                  $$ = new ShaderCompExpNode((char*)"!=", $1, $3)
                }
                
        | Identifier '=' binary
                {
                  $$ = new ShaderAssExpNode($1, $3)
                }
 
        | Identifier DE binary
                {
                  ShaderIdExpNode* temp1 = new ShaderIdExpNode($1);
                  ShaderExpNode* temp2 = new ShaderArithExpNode('/', $1, $3);
                  $$ = new ShaderAssExpNode(temp1, temp2)
                }

        | Identifier ME binary
                {
                  ShaderIdExpNode* temp1 = new ShaderIdExpNode($1);
                  ShaderExpNode* temp2 = new ShaderArithExpNode('-', $1, $3);
                  $$ = new ShaderAssExpNode(temp1, temp2)
                }

        | Identifier PE binary
                {
                  ShaderIdExpNode* temp1 = new ShaderIdExpNode($1);
                  ShaderExpNode* temp2 = new ShaderArithExpNode('+', $1,$3);
                  $$ = new ShaderAssExpNode(temp1, temp2)
                }

        | Identifier RE binary
                {
                  ShaderIdExpNode* temp1 = new ShaderIdExpNode($1);                
                  ShaderExpNode* temp2 = new ShaderArithExpNode('%', $1, $3);
                  $$ = new ShaderAssExpNode(temp1, temp2)
                }

        | Identifier TE binary
                {
                  ShaderIdExpNode* temp1 = new ShaderIdExpNode($1);
                  ShaderExpNode* temp2 = new ShaderArithExpNode('*', $1, $3);
                  $$ = new ShaderAssExpNode(temp1, temp2)
                }

value
        : NUMBER
                {
                  $$ = new ShaderRealValueNode($1);
                }
        | PI
                {
                  $$ = new ShaderRealValueNode((Real)M_PI);
                } 

        | '[' binary ',' binary ',' binary ']'
                {
                  $$ = new ShaderVecValueNode($2, $4, $6);
                }

        | ANYSTRING 
                {
                   $$ = new ShaderStringValueNode($1);
                }       

arguments
        :
                {
                  $$ = NULL;
                }
                                
	| binary
		{
		  $$ = new List<ShaderExpNode*>(1);
                  $$->append($1);		  
        	}

	| arguments ',' binary
		{
                  $$ = $1;
                  $$->append($3);
		}
		      
Identifier
        : IDENTIFIER
                 {
                   RCString errMsg;
                   $$ = new ShaderIdExpNode(errMsg, $1);
                  if (!errMsg.isEmpty())
                    recoverableError(errMsg);                   
                 }

parexp
        : '(' expression ')'
                {
                  $$ = new ShaderParExpNode($2);
                }

