/*
 * $RCSfile: BSDLYacc.y,v $
 *
 * Parser definition file. Class BSDLYacc is generated using 
 * bison++.
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: BSDLYacc.y,v 1.11 1996/08/01 11:59:10 streit Exp $
 * -----------------------------------------------------------------------------
 */

%{
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
%}

%name BSDLYacc

%header{
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

%}

//
// Possible values for an LHS of a production or a tokens.
//
%union {
        Name*            id;
        ScopedName*      scopedName;
        Real             number;
        RCString*        string;
        Value*           value;
        List<Value*>*    valueList;
        Makeable*        makeable;
        List<Makeable*>* makeableList;
       }

//
// enable all error handling code available
//
%define DEBUG 1
%define DEBUG_FLAG myParserDebugFlag
%define ERROR_VERBOSE

%define ERROR_BODY =0
%define ERROR fatalError
%define NERRS myErrorCount

%define LEX_BODY =0
%define LEX  scan
%define LVAL myTokenValue

%define PARSE parse
%define PARSE_PARAM
%define CONSTRUCTOR_PARAM 
%define CONSTRUCTOR_INIT : myParserDebugFlag(0), myWorld(NULL)
%define CONSTRUCTOR_CODE


%define MEMBERS \
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


%start Entry

%type <scopedName>   Identifier
%type <value>        Value RealValue VectorValue 
%type <value>        StringValue Expression
%type <valueList>    Values OptValues OptValueList 
%type <makeable>     Specifier 
%type <makeableList> Specifiers OptSpecifiers

%token <id>     IDENTIFIER SCOPE
%token <number> NUMBER
%token <string> STRING
%token tDefine tConstant tVerbatim tUsing tNamespace

%left '+' '-'
%left '*' '/' 
%left tUMINUS

%%

//________________________________________________________________________ World

Entry        : { 
                 myStackedFrames.push(StackFrame()); 
               } 
               World
             ; 

World        : /* empty */
             | World WorldElement
               {
                 yyerrok;
               }
             | World error
             ;

WorldElement : Specifier
               {
		RCString errMsg;
		if ($1)
		  if (!myWorld->setSpecifier(errMsg, $1)) {
		    recoverableError(errMsg);
		    delete $1;
		  }
	      }
             | Definition
             ;

//___________________________________________________________________ Definition

Definition : tDefine Identifier Specifier
             {
	       if ($3) {
		 Makeable* newMakeable = $3;

		 Object3D* object3D = dynamic_cast<Object3D*>($3);
		 if (object3D != NULL) 
		   newMakeable = new Shared3D(object3D, (RCString)$2->getIdentifier()); // !!! bisher *$2
		 else {
		   Object2D* object2D = dynamic_cast<Object2D*>($3);
		   if (object2D != NULL)
		     newMakeable = new Shared2D(object2D, (RCString)$2->getIdentifier());
		 }
		 
		 RCString errMsg;
		 if (!Makeable::registerExemplar(errMsg, *$2, newMakeable)) {
		   recoverableError("definition failed: " + errMsg);
		   delete newMakeable;
		 }
	       }
	       delete $2;
	     }
           | tDefine IDENTIFIER tNamespace ';'
             {
	       if (!Makeable::createNamespace(*$2))
		 recoverableError("namespace " + RCString(*$2) + 
				  " already exists");

	       delete $2;
	     }
           | tConstant Identifier Value ';'
             {
	       Makeable* newConstant = new ValueMakeable(*$3);
	       RCString errMsg;
	       if (!Makeable::registerExemplar(errMsg, *$2, newConstant)) {
		 recoverableError("const definition failed: " + errMsg);
		 delete newConstant;
	       }

	       delete $2;
	       delete $3;
	     }
           ;

//____________________________________________________________________ Specifier

Specifiers : Specifier
             {
	       if ($1 != NULL) {
		 $$ = new List<Makeable*>(1);
		 $$->append($1);
	       }
	       else
		 $$ = NULL;
	    }
           | Specifiers Specifier
             {
	       if ($1 != NULL)
		 $$ = $1;
	       else if ($2 != NULL)
		 $$ = new List<Makeable*>(1);
	       else
		 $$ = NULL;

	       if ($2 != NULL)
		 $$->append($2);
	     }
           ;

OptSpecifiers : ';'
                {
		  $$ = NULL;
                }
              | '{' Specifiers '}'
                {
		  $$ = $2;
                }
               | '{' Specifiers '}' ';'
                {
 		  $$ = $2;
                }
              ;

Specifier : Identifier OptValueList 
	   {
	     myStackedFrames.push(StackFrame(*$1, $1->getNamespace()));
	   }
            OptSpecifiers
            {	
              myStackedFrames.pop();
	     RCString errMsg;

	     $$ = Makeable::make(errMsg, *$1, $2);
	     if ($$ == NULL) {
                if (!errMsg.isEmpty()) {
		recoverableError("specifier " + 
                                   RCString((RCString)$1->getIdentifier()) +
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
		  $$ = Makeable::make(
                           errMsg, 
                           ScopedName(RCString((RCString)
                                      $1->getNamespace()) + "::"  +
                                      getCurrentIdentifier(),
                                      RCString($1->getIdentifier())), 
                           $2);
                   }
                             
                   if ($$ == NULL)
		    generateError("specifier", $1);
                 }
	      }
	      
               //
	      // Set additional specifiers
	      //
	      if ($$ != NULL && $4 != NULL) {
		for (long i=0; i<$4->count(); i++)
		  if (!$$->setSpecifier(errMsg, $4->item(i))) {
		    recoverableError(errMsg);
		    delete $4->item(i);
		  }
                  delete $4;
	      }
	      else if ($4 != NULL)
                 deleteList($4);
               //
	      // clean up
	      //
	      delete $1; 
	      if ($2 != NULL)
                 deleteList($2);
	      // $4 is alreay deleted!
	   }
          | Identifier tVerbatim StringValue OptSpecifiers
            {
	      $$ = NULL;
	      recoverableError("verbatim not yet implemented");
	   }
          | tUsing IDENTIFIER ';'
            {
	      $$ = NULL;
	      setCurrentNamespace(*$2);
	      if ($2) delete $2;
	   }
          ;

//________________________________________________________________ General Stuff

Values : Value
         {
	  $$ = new List<Value*>(1);
	  $$->append($1);
	}
       | Values ',' Value
         {
	  $$ = $1;
	  $$->append($3);
	}
       ;

OptValues : /* empty */
            {
	      $$ = NULL;
	   }
          | Values
            {
	      $$ = $1;
	   }
          ;

OptValueList : /* empty */
               {
		$$ = NULL;
	      }
             | Value
               {
		$$ = new List<Value*>(1);
		$$->append($1);
	      }
             | '(' Values ',' Value ')'
               {
		$$ = $2;
		$$->append($4);
	      }
             ;

Value : RealValue
        { 
	 $$ = $1; 
        }
      | VectorValue 
        { 
	 $$ = $1; 
        }
      | StringValue
        { 
	 $$ = $1; 
        }
      | Identifier
        { 
	  RCString errMsg;
	  $$ = NULL;

	  Makeable* theValue = Makeable::make(errMsg, *$1, NULL);
	  if (theValue == NULL)
	    generateError("constant", $1);
	  else {
	    ValueMakeable* constValue = dynamic_cast<ValueMakeable*>(theValue);
	    if (constValue == NULL)
	      recoverableError(RCString((RCString)$1->getIdentifier()) + 
			       " not a value");
	    else
	      $$ = new Value(constValue->getValue());
	  }

	  if ($$ == NULL) 
             $$ = new Value();
	  if (theValue != NULL) 
             delete theValue;
	  delete $1;
        }
      | Expression
        { 
	 $$ = $1; 
        }
      ;
	   	    
RealValue : NUMBER
            {
	     $$ = new Value($1);
	   }
          ;

VectorValue : '[' Values ']'
              {
		int valueNumbers = ($2 ? $2->count() : 0);

		$$ = NULL;

		switch (valueNumbers) {
  		  case 2: {
		    Real r0, r1;
		    //
		    // First try to build a Vector2D out of 2 Reals :
		    //
		    if (!$2->item(0)->toReal(r0) || !$2->item(1)->toReal(r1)) {
		      //
		      // Nope ! Now try to build a Matrix2D out of 2 Vector2D :
		      //
		      Vector2D v0, v1;
		      if (!$2->item(0)->toVector2D(v0) || 
			  !$2->item(1)->toVector2D(v1))
			recoverableError("type/number mismatch in vector/matrix");
		      else // build a matrix2D
			$$ = new Value(TransMatrix2D(v0,v1));
		    } else // build a vector2D
		      $$ = new Value(r0, r1);
		    break;
		  }
		    
		    break;
		  case 3: {
		    Real r0, r1, r2;
		    //
		    // First try to build a Vector3D out of 3 Reals :
		    //
		    if (!$2->item(0)->toReal(r0) || !$2->item(1)->toReal(r1) ||
			!$2->item(2)->toReal(r2)) {
		      //
		      // Nope ! Now try to build a Matrix3D out of 3 Vector3D :
		      //
		      Vector3D v0, v1, v2;
		      if (!$2->item(0)->toVector3D(v0) || 
			  !$2->item(1)->toVector3D(v1) ||
			  !$2->item(2)->toVector3D(v2)) {
			//
			// Last try: Build a Matrix2D out of 3 Vectors2D
			//
		        Vector2D v0, v1, v2;
			if (!$2->item(0)->toVector2D(v0) || 
			    !$2->item(1)->toVector2D(v1) ||
			    !$2->item(2)->toVector2D(v2))
			  recoverableError("type/number mismatch in vector/matrix");
			else // build a matrix2D
			  $$ = new Value(TransMatrix2D(v0, v1, v2));
		      } else // build a matrix3D
			$$ = new Value(TransMatrix3D(v0, v1, v2));
		    } else // build a vector3D
		      $$ = new Value(r0, r1, r2);
		    break;
		  }
		  case 4: {
		    Vector3D v0, v1, v2, v3;
		    if (!$2->item(0)->toVector3D(v0) || !$2->item(1)->toVector3D(v1) ||
			!$2->item(2)->toVector3D(v2) || !$2->item(3)->toVector3D(v3)) 
		      recoverableError("type/number mismatch in vector/matrix");
		    else 
		      $$ = new Value(TransMatrix3D(v0,v1, v2, v3));
		    break;
		  }
		  default:
		    recoverableError("invalid number of elements in vector");
		    break;
		}

		if (!$$) $$ = new Value(0,0,0);

		// 
                  // clean up ...
                  //
		if ($2)
                    deleteList($2);
	      }
              ;
	    
StringValue : STRING
              {
                $$ = new Value(*$1);
                delete $1;
	     }
            ;

Identifier : IDENTIFIER
             {
	       $$ = new ScopedName(getCurrentNamespace(), *$1);
	       delete $1;
	    }
           | SCOPE IDENTIFIER
             {
	       if (((RCString)*$1).isEmpty()) 
		 $$ = new ScopedName(*$2); // global namespace
	       else
		 $$ = new ScopedName(*$1, *$2);

	       delete $1;
	       delete $2;
	    }
           ;

Expression  : '(' Value ')' 
              { 
                $$ = $2; 
              }
            | Value '+' Value
              {
                $$ = new Value(*$1 + *$3);
                delete $1; 
                delete $3;
	     }
            | Value '-' Value
              {
                $$ = new Value(*$1 - *$3);
                delete $1; 
                delete $3;
              }
            | Value '*' Value
              {
                $$ = new Value(*$1 * *$3);
                delete $1; 
                delete $3;
              }
            | Value '/' Value
              {
                $$ = new Value(*$1 / *$3);
                delete $1; 
                delete $3;
              }
            | Identifier '(' OptValues ')'    // Function
              {
                RCString errMsg;
                $$ = NULL;

                Makeable* func = Makeable::make(errMsg, *$1, $3);
                if (func == NULL) 
                  generateError("function", $1);
                else {
                  ValueMakeable* funcValue = dynamic_cast<ValueMakeable*>(func);
                  if (funcValue == NULL) 
                    recoverableError(RCString($1->getIdentifier())
                		     + " not a function name");
                  else
                    $$ = new Value(funcValue->getValue());
                }

                if ($$ == NULL) 
                  $$ = new Value();
                if (func != NULL) delete func;
                if ($1 != NULL)   delete $1;
                if ($3 != NULL)   deleteList($3);
              }
            | '-' Value %prec tUMINUS 
              {
                $$ = new Value(- *$2);
                delete $2; 
	     }
            ;
