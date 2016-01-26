/*
 * CTYacc.y
 *
 * Copyright (C) 1994-96, Thomas Wenger <wenger@iam.unibe.ch>
 *                        Thomas von Siebenthal <siebenth@iam.unibe.ch>
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
 *  $Id: CTYacc.y,v 1.41 1996/10/30 08:30:26 siebenth Exp $
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
%}

%name CTYacc

%header{
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

%}

//
// Possible values for an LHS of a production or a tokens.
//
%union {
  RCString* string;
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


%define MEMBERS                                                  \
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


%token <string> tCLASS 
%token <string> tSTRUCT
%token <string> tUNION
%token <string> tPRIVATE 
%token <string> tPUBLIC 
%token <string> tPROTECTED 
%token <string> tVIRTUAL 
%token <string> tPUREVIRTUAL 
%token <string> tINLINE 
%token <string> tEXPRESSION 
%token <string> tCONSTEXPR 
%token <string> tOPERATOR 
%token <string> tCONST 
%token <string> tSTATIC 
%token <string> tFRIEND 
%token <string> tENUM 
%token <string> tVOLATILE 
%token <string> tGELTUNGSBEREICHOPERATOR 
%token <string> t3PUNKTE 
%token <string> tKOMMA 
%token <string> tIDENTIFIER
%token <string> tDOPPELPUNKT
%token <string> tTEMPLATE
%token <string> tANYTHINGELSE
/* I don't need the standard types but I parse them to reduce
   the conflicts. In the end they are treated as a concatenated string */
%token <string> tCHAR 
%token <string> tSHORT 
%token <string> tINT 
%token <string> tLONG 
%token <string> tSIGNED 
%token <string> tUNSIGNED 
%token <string> tFLOAT 
%token <string> tDOUBLE 
%token <string> tVOID
%token <string> tAUTO 
%token <string> tREGISTER 
%token <string> tEXTERN
%token <string> tNEW
%token <string> tDELETE

%type <string> Klassenspezifizierer Klassenkopf Klassenname Klassenschluessel QualifizierterName QualifizierterKlassenname DeklSpezifiziererliste DeklSpezlisteStandard DeklSpezifiziererStandard StandardTypname DeklSpezlisteCustom Deklarator Dname Name Speicherklassenspezifizierer QualifizierterTypname Zeigeroperator CvQualifiziererliste CvQualifizierer ArgumentDeklaration Ausdrucksliste Zuweisungsausdruck Bezeichner KonstanterAusdruck Ausdruck KlassenschluesselKlassenname Operatorfunktionsname Operator Konversionsfunktionsname Konversionstypname Typspezifizierer DeklSpezifiziererZusatz DeklSpezZusatzListe TemplateKlassenname TemplateName TemplateArgListe TemplateArg Typname TemplateArgumentListe TemplateArgument Typargument AbstrakterDeklarator AbstrakterDeklaratorOpt KonstanterAusdruckOpt FktDeklaratorName Argumentliste ArgDeklarationsliste Zugriffsspezifizierer

%start Main

%%

Main:   {
          myActualType = "";
          myActualView = "";
          myActualScope = "";
          myActualPointer = "";
          myIsTemplate = false;
          myTemplateParameters = "";
          myMemberIsTemplate = false;
          myIsVirtual = false;
        }
        Programm  
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
          } 
    ;
    
Programm:       /* empty */
        |       Programm Deklaration
        ;

Deklaration:    { 
                  myIsTemplate = false;
                }
                Klassenspezifizierer ';'
                {
                  myIsTemplate = false;
                }
           |    tTEMPLATE '<' TemplateArgumentListe '>' 
                {
                  myIsTemplate = true;
                  myTemplateParameters = "<" + *$3 + ">";
                  delete $1;
                  delete $3;
                }
                Klassenspezifizierer ';'
                {
                  myIsTemplate = false;
                }
           ;

TemplateArgumentListe:    TemplateArgument
                     |    TemplateArgumentListe tKOMMA TemplateArgument
                          { 
                            $$ = new RCString(*$1 + ", " + *$3);
                            delete $1;
                            delete $2;
                            delete $3;
                          }
                     ;
                     
TemplateArgument:    Typargument
                |    ArgumentDeklaration
                ;
                
Typargument:    tCLASS Bezeichner
                {
                  $$ = new RCString(*$1 + " " + *$2);
                  delete $1;
                  delete $2;
                }                  
           ;
                  
Klassenspezifizierer:   Klassenkopf '{' Elementliste '}' 
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
                        }    
                    |   Klassenkopf        /* Foreward Deklaration der Klasse */     
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
                        }
                    ;

Klassenkopf:   KlassenschluesselKlassenname
//         |   Klassenschluessel // <- does this make sense ???
//         |   Klassenschluessel Bezeichner
//         |   Klassenschluessel BasisSpez
//redund.  |   Klassenschluessel Bezeichner BasisSpez
           |   KlassenschluesselKlassenname BasisSpez
               { 
                 $$ = $1;
               }
           ;

// just a intermediate rule to reduce the number of similar code
KlassenschluesselKlassenname:   Klassenschluessel Klassenname 
                                { 
                                  aKlasse.clean();    // neue, leere Klasse beginnen
                                  aKlasse.isTemplate = myIsTemplate;
                                  aKlasse.TemplateParameters = myTemplateParameters;
                                  aKlasse.ShortName = *$2;
                                  aKlasse.LongName = myActualScope + aKlasse.ShortName;
                                  delete $1;
                                  delete $2;
                                }
                            ;

Klassenname:   Bezeichner 
           |   TemplateKlassenname
           ;

Klassenschluessel:      tCLASS      
                        { 
                          myActualView = "private";
                          $$ = $1;
                        }
                |       tSTRUCT
                        { 
                          myActualView = "public";
                          $$ = $1;
                        }
//               |       tUNION
                ;

/*
Elementliste:       Elementliste Elementdeklaration
            |       Elementdeklaration
            |       Zugriffsspezifizierer tDOPPELPUNKT Elementliste
            |       Zugriffsspezifizierer tDOPPELPUNKT
            ;
The above rule was replace by the two below. This 
reduced the number of shift/reduce conflicts by 32
and the number of reduce/reduce conflicts by 2
*/

Elementliste:   /* Element */
            |   Elementliste Element
            ;
            
Element:    Elementdeklaration
       |    Zugriffsspezifizierer tDOPPELPUNKT
            {
              delete $1;
              delete $2;
            }
       ;


Elementdeklaration:    DeklSpezifiziererliste ElementDeklaratorliste ';'
                       {
                         delete $1;
                         myActualPointer = "";
                         myActualType = "";
                         myMemberIsTemplate = false;
                       };
                  |    DeklSpezifiziererliste ';'
                       {
                         delete $1;
                         myActualType = "";
                         myActualType = "";
                         myMemberIsTemplate = false;
                       }
                  |    ';'
                  |    ElementDeklaratorliste ';'    // STRUCT mit Elementdeklaration
                       {
                         myActualType = "";
                         myActualType = "";
                         myMemberIsTemplate = false;
                       }
                  |    Funktionsdefinition
                  |    { 
                         myKlassenStack.push(aKlasse);     // aktuelle Klasse sichern
                         myScopeStack.push(myActualScope); // aktuellen Scope sichern
                         myActualScope += aKlasse.ShortName;
                         myActualScope += "::";
                       }
                       Klassenspezifizierer           // rekursive Klassendeklaration
                       { 
                         myActualType = aKlasse.ShortName;
                         aKlasse = myKlassenStack.pop();       // letzte Klasse holen
                         myActualScope = myScopeStack.pop();
                         // delete $2;
                       }            // kann von ElementDeklaratorliste gefolgt werden
                  |    tFRIEND Klassenschluessel Klassenname  // Friend wird nicht behandelt
                       { 
                         delete $1;
                         delete $2;
                         delete $3;
                       }
                  |    EnumSpezifizierer 
                  |    tUNION '{' '}'    // Unions werden ignoriert !!!
                       {
                         delete $1;
                       }
//                |    Funktionsdefinition ';'
//                |    QualifizierterName ';'
                  ;   

ElementDeklaratorliste:   ElementDeklarator 
                      |   ElementDeklaratorliste tKOMMA ElementDeklarator 
                          { 
                            delete $2;
                          }
                      ;

/* Deklarator ist nur noch fuer Member, also macht Pure Virtual keinen Sinn mehr */
ElementDeklarator:      Deklarator 
                        { 
                          aKlassenMember.clean();
                          aKlassenMember.name = *$1;
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
                          delete $1;
                        }
//               |      Bezeichner tDOPPELPUNKT KonstanterAusdruck
//               |      tDOPPELPUNKT KonstanterAusdruck
                 ;

Zugriffsspezifizierer:   tPRIVATE    
                         { 
                           myActualView = "private"; 
                           $$ = $1;
                         }
                     |   tPUBLIC     
                         { 
                           myActualView = "public"; 
                           $$ = $1;
                         }
                     |   tPROTECTED  
                         { 
                           myActualView = "protected"; 
                           $$ = $1;
                         }
                     ;

QualifizierterName:     QualifizierterKlassenname tGELTUNGSBEREICHOPERATOR Name 
                        { 
                          $$ = new RCString (*$1 + *$2 + *$3);
                          delete $1;
                          delete $2;
                          delete $3;
                        }
                  ;

/* These rules are all the same and allow to prevent RR conflicts
QualifizierterTypname:	 TypedefName 
		     |	 Klassenname tGELTUNGSBEREICHOPERATOR QualifizierterTypname
		     ;
QualifizierterKlassenname:    Klassenname 
                         |    Klassenname tGELTUNGSBEREICHOPERATOR QualifizierterKlassenname 
                         ;
VollerKlassenname:      QualifizierterKlassenname tGELTUNGSBEREICHOPERATOR QualifizierterKlassenname
                 |      QualifizierterKlassenname 
                 ;

they are replaced by an alias to QualifizierterKlassenname
VollerKlassenname is really the same as a QualifizierterKlassenname and removed
*/

QualifizierterTypname:    QualifizierterKlassenname
                     ;

QualifizierterKlassenname:    Klassenname 
                              { 
                                $$ = $1;
                              }
                         |    Klassenname tGELTUNGSBEREICHOPERATOR QualifizierterKlassenname 
                              {
                                $$ = new RCString (*$1 + *$2 + *$3);
                                delete $1;
                                delete $2;
                                delete $3;
                              }
                         ; 

BasisSpez:        tDOPPELPUNKT Basisliste
                  { 
                    delete $1;
                  }
         ;

// first empty the intermediate variable aBasisKlasse, then fill it new
Basisliste:       { 
                    aBasisKlasse.clean(); 
                  } 
                  Basisspezifizierer
                  { 
                    aKlasse.BasisKlassenListe.append(aBasisKlasse);
                  }
          |       Basisliste tKOMMA 
                  { 
                    aBasisKlasse.clean(); 
                  } 
                  Basisspezifizierer 
                  { 
                    aKlasse.BasisKlassenListe.append(aBasisKlasse);
                    delete $2;
                  }
          ;


Basisspezifizierer:     QualifizierterKlassenname 
                        { 
                          aBasisKlasse.name = *$1;
                          aBasisKlasse.view = "private"; // default derivation
                          aBasisKlasse.isVirtual = false;
                          delete $1; 
                        }
                  |     Zugriffsspezifizierer QualifizierterKlassenname
                        { 
                          aBasisKlasse.name = *$2;
                          aBasisKlasse.view = *$1;
                          aBasisKlasse.isVirtual = false;
                          delete $2;
                          delete $1;
                        }
                  |     tVIRTUAL QualifizierterKlassenname
                        { 
                          aBasisKlasse.name = *$2;
                          aBasisKlasse.view = "private"; // default derivation
                          aBasisKlasse.isVirtual = true; 
                          delete $2;
                          delete $1;
                        }
                  |     tVIRTUAL Zugriffsspezifizierer QualifizierterKlassenname
                        { 
                          aBasisKlasse.name = *$3;
                          aBasisKlasse.view = *$2;
                          aBasisKlasse.isVirtual = true; 
                          delete $1;
                          delete $2;
                          delete $3;
                        }
                  |     Zugriffsspezifizierer tVIRTUAL QualifizierterKlassenname
                        { 
                          aBasisKlasse.name = *$3;
                          aBasisKlasse.view = *$1;
                          aBasisKlasse.isVirtual = true;
                          delete $1;
                          delete $2;
                          delete $3;
                        }
                  ;

/* Problem: Mit der Definition nach Buch S. 20/21 war folgendes 
            Konstrukt erlaubt:
 
            class hello { ... };
            class tschau {
              int hello a;
              }

            Dies hat viele Konflikte und Fehlparsings zur Folge.

   Loesung: Moeglichst frueh in mehrere Parsingaeste teilen:

            Ast 1:  Standardtypen wir int, char, shart, signed, ...

            Ast 2:  FktSpezifizierer, Klassenspezifizierer, Voller
                    Klassenname etc.
*/

DeklSpezifiziererliste:	  DeklSpezlisteStandard  
                          { 
                            $$ = $1; 
                            ostrstream os;
                            os << "[CTYacc] STANDARD TYPE: " << *$$;
                            Report::debug(os);
                            myActualType = *$$;
                          }
                      |   DeklSpezZusatzListe DeklSpezlisteStandard
                          {
                            if (*$1 == "") {
                              $$ = $2;
                              delete $1;
                              }
                            else {
                              $$ = new RCString(*$1 + " " + *$2);
                              delete $1;
                              delete $2;
                              };
                            ostrstream os;
                            os << "[CTYacc] STANDARD TYPE: " << *$$;
                            Report::debug(os);
                            myActualType = *$$;
                          }                            
                      |   DeklSpezlisteCustom    
                          {
                            $$ = $1;    
                            ostrstream os;
                            os << "[CTYacc] CUSTOM TYPE: " << *$$;
                            Report::debug(os);
                            myActualType = *$1;
                          }
                      |   DeklSpezZusatzListe DeklSpezlisteCustom
                          {
                            if (*$1 == "") {
                              $$ = $2;
                              delete $1;
                              }
                            else {
                              $$ = new RCString(*$1 + " " + *$2);
                              delete $1;
                              delete $2;
                              };
                            ostrstream os;
                            os << "[CTYacc] CUSTOM TYPE: " << *$$;
                            Report::debug(os);
                            myActualType = *$$;
                          }                            
                      ;

/* Die Standardliste laesst _nur_ gueltige Listen fuer die C++
   Standardtypen (int, float, signed, ...) zu                  */
DeklSpezlisteStandard:   DeklSpezifiziererStandard  
                         { 
                           $$ = $1;
                         }
                     |   DeklSpezlisteStandard DeklSpezifiziererStandard 
                         { 
                           $$ = new RCString (*$1 + " " + *$2);
                           delete $1;
                           delete $2;
                         }
		     ; 

DeklSpezifiziererStandard:    StandardTypname DeklSpezZusatzListe
                              {
                                if (*$2 == "") {
                                  $$ = $1;
                                  delete $2;
                                  }
                                else {
                                  $$ = new RCString(*$1 + " " + *$2);
                                  delete $1;
                                  delete $2;
                                  };
                              }
                         |    StandardTypname
                              {
                                $$ = $1;
                              }
                         ;

DeklSpezZusatzListe:    DeklSpezifiziererZusatz
                        {
                          $$ = $1;
                        }
                   |    DeklSpezZusatzListe DeklSpezifiziererZusatz
                        {
                          if (*$2 == "") {
                            $$ = $1;
                            delete $2;
                            }
                          else {
                            $$ = new RCString(*$1 + " " + *$2);
                            delete $1;
                            delete $2;
                            };
                        }
                   ;
                            
DeklSpezifiziererZusatz:    Speicherklassenspezifizierer   { $$ = $1; }
                       |    FktSpezifizierer               { $$ = new RCString(""); }
                       |    CvQualifizierer                { $$ = $1; }
                       |    tFRIEND                        { $$ = $1; }
//                     |    tTYPEDEF
                       ;  

StandardTypname:   tCHAR        { $$ = $1; }
	       |   tSHORT       { $$ = $1; }
               |   tINT         { $$ = $1; }
	       |   tLONG        { $$ = $1; }
	       |   tSIGNED      { $$ = $1; }
	       |   tUNSIGNED    { $$ = $1; }
	       |   tFLOAT       { $$ = $1; }
	       |   tDOUBLE      { $$ = $1; }
	       |   tVOID        { $$ = $1; }
	       ;

/* Die Customliste laesst _keine_ Listen fuer die C++
   Standardtypen (int, float, signed, ...) zu          */
/*
DeklSpezlisteCustom:    DeklSpezifiziererCustom  
                        { 
                          $$ = $1;
                        }
                   |    DeklSpezlisteCustom DeklSpezifiziererCustom 
                        { 
                          $$ = new RCString (*$1 + " " + *$2);
                          delete $1;
                          delete $2;
                        }
                   ; 

DeklSpezifiziererCustom:    QualifizierterKlassenname DeklSpezZusatzListe
                            {
                              $$ = new RCString(*$1 + " " + *$2);
                              delete $1; delete $2;
                            }
                       |    QualifizierterKlassenname
                            {
                              $$ = $1;
                            }
                       ;
*/
/* DeklSpezlisteCustom darf maximal _einen_ Bezeichner enthalten !!! */
DeklSpezlisteCustom:    QualifizierterKlassenname DeklSpezZusatzListe
                        {
                           $$ = new RCString(*$1 + " " + *$2);
                           delete $1; delete $2;
                        }
                   |    QualifizierterKlassenname
                        {
                          $$ = $1;
                        }
                   ;



/*
   QualifizierterTypname  is a Subset of  QualifizierterKlassenname
   QualifizierterTypname  is  Bezeicher(::Bezeichern)*
   QualifizierterKlassenname  is  (Bezeichner|Template)(::(Bezeichner|Template))*
   
	       |   QualifizierterTypname          { $$ = $1; }
	       |   tFRIEND QualifizierterTypname 
                   {
                     $$ = new RCString(*$1 + " " + *$2);
                     delete $1;
                     delete $2;
                   }
*/

/* Deklarator itself cannot be a function. A function can only
   be represented by FktDeklarator and nothing else               */
Deklarator:   Dname 
              { 
                $$ = $1;
              }
	  |   Zeigeroperator Deklarator 
              { 
                myActualPointer += *$1;
                $$ = $2;
                delete $1; 
              }
	  |   Deklarator '[' KonstanterAusdruck ']'
              { 
                $$ = new RCString (*$1 + "[" + *$3 + "]");
                delete $1;
                delete $3;
              }
	  |   Deklarator '[' ']' 
              { 
                $$ = new RCString (*$1 + "[]");
                delete $1;
              }
// sinnlos |   '(' Deklarator ')' { $$ = new RCString ("(" + *$2 + ")"); delete $2; }
	  ;

Dname:			Name                               { $$ = $1; }
// redundant???	|	Klassenname                        { $$ = $1; }
// redundant:   |	'~' Klassenname              
// redundant:	|	TypedefName                        { $$ = $1; }
		|	QualifizierterTypname              { $$ = $1; }
		;

Name:			Bezeichner                         { $$ = $1; }
                |	Operatorfunktionsname              { $$ = $1; }
        	|	Konversionsfunktionsname           { $$ = $1; }
// redundant	|	'~' Klassenname                    { $$ = $2; }
		|	QualifizierterName                 { $$ = $1; }
		;

Speicherklassenspezifizierer:	tAUTO        { $$ = $1; }
		            |	tREGISTER    { $$ = $1; }
		            |	tSTATIC      { $$ = $1; }
		            |	tEXTERN      { $$ = $1; }
		            ; 

Zeigeroperator:   '*' CvQualifiziererliste 
                  { 
                    $$ = new RCString ("*" + *$2);
                    delete $2;
                  }
                  
	      |	  '&' CvQualifiziererliste 
                  { 
                    $$ = new RCString ("&" + *$2);
                    delete $2;
                  }
// redundant  |   '*'          CvQualifiziererliste can be empty            
// redundant  |	  '&'                      
// ???	      |	  QualifizierterKlassenname tGELTUNGSBEREICHOPERATOR '*' CvQualifiziererliste
// ???	      |	  QualifizierterKlassenname tGELTUNGSBEREICHOPERATOR '*'
	      ;

CvQualifiziererliste:	/*   empty   */
                        {
                          $$ = new RCString("");
                        }
		    |	CvQualifiziererliste CvQualifizierer 
                        { 
                          $$ = new RCString (*$1 + " " + *$2);
                          delete $1;
                          delete $2;
                        }
		    ;

CvQualifizierer:	tCONST     { $$ = $1; }
               |	tVOLATILE  { $$ = $1; }
	       ;

Argumentliste:	 /* empty */
                 {
                   $$ = new RCString("");
                 }
             |   ArgDeklarationsliste
//	     |   ArgDeklarationsliste tKOMMA t3PUNKTE
//	     |	 ArgDeklarationsliste t3PUNKTE
// Sinn ???  |	 t3PUNKTE
	     ;

ArgDeklarationsliste:   { 
                          aOperationsParameter.clean(); 
                        }
                        ArgumentDeklaration 
                        { 
                          $$ = $2;
                          aKlassenOperation.OperationsParameterListe.append(aOperationsParameter);
                          myActualPointer = "";
                          myActualType = "";
                        }
		    |	ArgDeklarationsliste tKOMMA 
                        { 
                          aOperationsParameter.clean();
                        } 
                        ArgumentDeklaration 
                        { 
                          $$ = new RCString(*$1 + *$2 + " " + *$4);
                          delete $1;
                          delete $2;
                          delete $4;
                          aKlassenOperation.OperationsParameterListe.append(aOperationsParameter);
                          myActualPointer = "";
                          myActualType = "";
                        }
		    ;

ArgumentDeklaration:	DeklSpezifiziererliste Deklarator
                        { 
                          aOperationsParameter.name = *$2;
                          aOperationsParameter.type = *$1;
                          aOperationsParameter.ptr = myActualPointer;
                          myActualPointer = "";
                          aOperationsParameter.view = myActualView;
                          $$ = new RCString(*$1 + " " + *$2);
                          delete $1;
                          delete $2;
                        } 
   		   |	DeklSpezifiziererliste Deklarator '=' Ausdruck
                        { 
                          aOperationsParameter.name = *$2;
                          aOperationsParameter.type = *$1;
                          aOperationsParameter.ptr = myActualPointer;
                          myActualPointer = "";
                          aOperationsParameter.init = *$4;
                          aOperationsParameter.view = myActualView;
                          $$ = new RCString(*$1 + " " + *$2 + " = " + *$4);
                          delete $1;
                          delete $2;
                          delete $4;                          
                        }
		   |	DeklSpezifiziererliste '=' Ausdruck
                        { 
                          aOperationsParameter.type = *$1;
                          aOperationsParameter.init = *$3;
                          aOperationsParameter.view = myActualView; 
                          $$ = new RCString(*$1 + " = " + *$3);
                          delete $1;
                          delete $3;
                        } 
		   |	DeklSpezifiziererliste
                        { 
                          aOperationsParameter.type = *$1;
                          aOperationsParameter.view = myActualView;
                          $$ = $1;
                        } 
		   |	DeklSpezifiziererliste Zeigeroperator
                        { 
                          aOperationsParameter.type = (*$1 + *$2);
                          aOperationsParameter.view = myActualView;
                          $$ = new RCString(*$1 + *$2);
                          delete $1;
                          delete $2;
                        } 
//		   |	DeklSpezifiziererliste AbstrakterDeklarator
//		   |	DeklSpezifiziererliste AbstrakterDeklarator '=' Ausdruck
		   ;

Funktionsdefinition:    DeklSpezifiziererliste FktDeklarator KtorInitialisiererOpt FktRumpf
                        {
                          delete $1;
                        }
                   |    FktDeklarator KtorInitialisiererOpt FktRumpf
                        {
                        }
                   |    Destruktor
                        {
                        }
// strange:        |    Konstruktor
                   ;

FktRumpf:    '{' '}'        
        |    ';' /* empty   oder   ;  */
        |    tPUREVIRTUAL ';'   /* '=' '0'  <->  RvSpezifizierer */ 
             { 
               myIsVirtual = true;
               delete $1;
               // aKlassenOperation.isVirtual = true; 
             }
        ;

FktSpezifiziererOpt:    /* empty */
                   |    FktSpezifizierer
                   ;

FktSpezifizierer:   tINLINE   
                    {
                      delete $1;
                    }
                |   tVIRTUAL  
                    { 
                      delete $1;
                      myIsVirtual = true; 
                    }
                ;

Destruktor:    FktSpezifiziererOpt '~' Bezeichner
               { 
                 aKlassenOperation.clean();
                 aKlassenOperation.name = "~" + *$3;
                 // aKlassenOperation.type = myActualType;
                 aKlassenOperation.type = "";
                 myActualType = "";
                 aKlassenOperation.view = myActualView;
                }
               '(' VoidOpt ')' FktRumpf
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
                 delete $3;
               }
          ;

VoidOpt:   /*  empty  */
       |   tVOID
           {
             delete $1;
           }                        
       ;
                  
KtorInitialisiererOpt:    /* empty */
                     |    KtorInitialisierer
                     ;

KtorInitialisierer:     tDOPPELPUNKT ElementInitialisiererliste
                        {
                          delete $1;
                        }
                  ;

/* The FktDeklarator is only valid as a function name
   so it has to be followed by a ( ... ) to be parsed   */
FktDeklarator:    FktDeklaratorName 
                  { 
                    aKlassenOperation.clean();
                    aKlassenOperation.name = *$1;
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
                  }
                  '(' Argumentliste ')' CvQualifiziererliste
                  { 
                    ostrstream os;
                    os << "[CTYacc] OPERATION ADDED: " << aKlassenOperation.name;
                    Report::debug(os);
                    aKlasse.KlassenOperationenListe.append(aKlassenOperation);
                    delete $1;
                    delete $4;
                    delete $6;
                  }
             ;            

FktDeklaratorName:    Dname
                      { 
                        $$ = $1;
                      }
                 |    Zeigeroperator FktDeklaratorName
                      /* I store the pointer part of a declaration in a special
                         variable. Because the pointer is displayed with the type
                         but is parsed together with the name ...                */
                      { 
                        myActualPointer += *$1;
                        $$ = $2;
                        delete $1; 
                      }
                 |    '(' Dname ')'
                      { 
                        $$ = new RCString ("(" + *$2 + ")");
                        delete $2; 
                      }
                 |    '(' Zeigeroperator FktDeklaratorName ')'
                      { 
                        $$ = new RCString ("(" + *$2 + *$3 + ")");
                        delete $2;
                        delete $3; 
                      }
                 ;
                 
ElementInitialisiererliste:     ElementInitialisierer
                          |     ElementInitialisiererliste tKOMMA ElementInitialisierer
                                {
                                  delete $2;
                                }
                          ;

ElementInitialisierer:  QualifizierterKlassenname '(' Ausdrucksliste ')'
                        {
                          delete $1;
                          delete $3;
                        }
                     |  QualifizierterKlassenname '(' ')'
                        {
                          delete $1;
                        }
// redundant:        |  Bezeichner '(' Ausdrucksliste ')'
// redundant:        |  Bezeichner '(' ')'
                     ;

Ausdrucksliste:         Zuweisungsausdruck
              |         Ausdrucksliste tKOMMA Zuweisungsausdruck
                        {
                          $$ = new RCString(*$1 + ", " + *$3);
                          delete $1;
                          delete $2;
                          delete $3;
                        }
              ;

Zuweisungsausdruck:     Bezeichner '=' tEXPRESSION
                        {
                          $$ = new RCString(*$1 + " = " + *$3);
                          delete $1;
                          delete $3;
                        }
                  |     Bezeichner
                  |     tANYTHINGELSE
                  ;
/*                      BedingterAusdruck
                |       EinstelligerAusdruck Zuweisungsoperator Zuweisungsausdruck
                ;       */


Operatorfunktionsname:    tOPERATOR Operator
                          {
                            $$ = new RCString(*$1 + *$2);
                            delete $1;
                            delete $2;
                          }
                     ;
                  
Operator:    tNEW
        |    tDELETE
        |    tKOMMA
        |    '!'                { $$ = new RCString("!"); }
        |    '%'                { $$ = new RCString("%"); }
        |    '^'                { $$ = new RCString("^"); }
        |    '&'                { $$ = new RCString("&"); }
        |    '*'                { $$ = new RCString("*"); }
        |    '(' ')'            { $$ = new RCString("()"); }
        |    '-'                { $$ = new RCString("-"); }
        |    '+'                { $$ = new RCString("+"); }
        |    '='                { $$ = new RCString("="); }
        |    '|'                { $$ = new RCString("|"); }
        |    '~'                { $$ = new RCString("~"); }
        |    '[' ']'            { $$ = new RCString("[]"); }
        |    '<'                { $$ = new RCString("<"); }
        |    '>'                { $$ = new RCString(">"); }
        |    '/'                { $$ = new RCString("/"); }
        |    ','                { $$ = new RCString(","); }
        |    '-' '>'            { $$ = new RCString("->"); }
        |    '+' '+'            { $$ = new RCString("++"); }
        |    '-' '-'            { $$ = new RCString("--"); }
        |    '-' '>' '*'        { $$ = new RCString("->*"); }
        |    '<' '<'            { $$ = new RCString("<<"); }
        |    '>' '>'            { $$ = new RCString(">>"); }
        |    '<' '='            { $$ = new RCString("<="); }
        |    '>' '='            { $$ = new RCString(">="); }
        |    '=' '='            { $$ = new RCString("=="); }
        |    '!' '='            { $$ = new RCString("!="); }
        |    '&' '&'            { $$ = new RCString("&&"); }
        |    '|' '|'            { $$ = new RCString("||"); }
        |    '*' '='            { $$ = new RCString("*="); }
        |    '/' '='            { $$ = new RCString("/="); }
        |    '%' '='            { $$ = new RCString("%="); }
        |    '+' '='            { $$ = new RCString("+="); }
        |    '-' '='            { $$ = new RCString("-="); }
        |    '<' '<' '='        { $$ = new RCString("<<="); }
        |    '>' '>' '='        { $$ = new RCString(">>="); }
        |    '&' '='            { $$ = new RCString("&="); }
        |    '^' '='            { $$ = new RCString("^="); }
        |    '|' '='            { $$ = new RCString("|="); }
        ; 
        
Konversionsfunktionsname:    tOPERATOR Konversionstypname
                             {
                               $$ = new RCString(*$1 + *$2);
                               delete $1;
                               delete $2;
                             }
                        ;
                        
Konversionstypname:    Typspezifizierer
                       {
                         $$ = $1;
                       } 
                  |    Typspezifizierer Zeigeroperator
                       {
                         $$ = new RCString(*$1 + " " + *$2);
                         delete $1;
                         delete $2;
                       }
                  ;

Typspezifizierer:    DeklSpezlisteStandard
                |    DeklSpezlisteCustom
                ;                

TemplateKlassenname:    TemplateName '<' TemplateArgListe '>'
                        {
                          $$ = new RCString(*$1 + "<" + *$3 + ">");
                          delete $1;
                          delete $3;
                          myMemberIsTemplate = true;
                        }
                   ;
                   
TemplateName:    Bezeichner
            ;
            
TemplateArgListe:    TemplateArg
                |    TemplateArgListe tKOMMA TemplateArg
                     {
                       $$ = new RCString(*$1 + ", " + *$3);
                       delete $1;
                       delete $2;
                       delete $3;
                     }
                ;
                
TemplateArg:    Typname
// ???     |    Ausdruck
           ;   

Typname:    Typspezifizierer AbstrakterDeklaratorOpt
            {
              $$ = new RCString(*$1 + " " + *$2);
              delete $1;
              delete $2;
            }
       |    DeklSpezZusatzListe Typspezifizierer AbstrakterDeklaratorOpt
            {
              $$ = new RCString(*$1 + " " + *$2 + " " + *$3);
              delete $1;
              delete $2;
              delete $3;
            }            
       ;

AbstrakterDeklarator:    Zeigeroperator AbstrakterDeklaratorOpt
                         {
                           $$ = new RCString(*$1 + *$2);
                           delete $1;
                           delete $2;
                         }
                    |    AbstrakterDeklaratorOpt '(' Argumentliste ')' CvQualifiziererliste
                         {
                           $$ = new RCString(*$1 + "(" + *$3 + ")" + *$5);
                           delete $1;
                           delete $3;
                           delete $5;
                         }
                    |    AbstrakterDeklaratorOpt '[' KonstanterAusdruckOpt ']'
                         {
                           $$ = new RCString(*$1 + "[" + *$3 + "]");
                           delete $1;
                           delete $3;
                         }
                    |    '(' AbstrakterDeklarator ')'
                         {
                           $$ = new RCString("(" + *$2 + ")");
                           delete $2;
                         }
                    ;

AbstrakterDeklaratorOpt:    /* empty */
                            {
                              $$ = new RCString("");
                            }
                       |    AbstrakterDeklarator
                       ;

KonstanterAusdruckOpt:    /* empty */
                          {
                            $$ = new RCString("");
                          }
                     |    KonstanterAusdruck
                     ;

EnumSpezifizierer:    tENUM Bezeichner '{' /* EnumListe */ '}'
                      {
                        delete $1;
                        delete $2;
                      }
                 |    tENUM '{' /* EnumListe */ '}'
                      {
                        delete $1;
                      }
                 ;      


/* below are my own rules */

Bezeichner:   tIDENTIFIER 
          ;

// tritt vorerst nur auf nach einem [ auf
KonstanterAusdruck:    tCONSTEXPR  
                  ;

// tritt hier nur auf nach einem =
Ausdruck:    tEXPRESSION 
        ;
