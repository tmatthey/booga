/*
 * CTLex.l
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
 *  $Id: CTLex.l,v 1.33 1996/10/30 08:30:16 siebenth Exp $
 * -----------------------------------------------------------------------------
 */

%header{
#include "CTYacc.h"
%}

%{
#include <string.h>
%}

%name CTLex

%define DEBUG 1
%define DEBUG_FLAG myScannerDebugFlag
%define DEBUG_INIT 0

%define CONSTRUCTOR_PARAM void
%define CONSTRUCTOR_INIT : myCurrentLine(1)
%define CONSTRUCTOR_CODE { KlammerZu = 0;                 \
                           KlammerAuf = 0;                \
                           InArgumentListe = false;       \
                           RundeKlammern = 0;             \
                           EckigeKlammern = 0;            \
                           GeschweifteKlammern = 0;       \
                           ausdruck = "" ;                \
                           first_time = 1;                \
                           IgnoreCode = 1;                \
                           lastState = 0;                 }                    


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
     RCString myCurrentFilename;                             \
     int KlammerZu;                                          \
     int KlammerAuf;                                         \
     bool InArgumentListe;                                   \
     int RundeKlammern;                                      \
     int EckigeKlammern;                                     \
     int GeschweifteKlammern;                                \
     RCString ausdruck;                                      \
     int first_time;                                         \
     int IgnoreCode;                                         \
     int lastState;                                    


%define LEX scan
%define LEX_PARAM YY_CTYacc_STYPE& yylval

identifier        [a-zA-Z_][0-9a-zA-Z_]*
white             [ \t]
CLEAN             [ \t\n]
word              [^ \t\n\;\,\(\)\{\}\[\]\<\>\:\=\*\&\~\.!%\^\-\+\|\[\]\/]+
special           [:;\,<>=\*&~\.!%\^\-\+\|\[\]\/]
TEMPLATEOK        {CLEAN}*\<.*\>{CLEAN}*class
CLASSOK1          [ \n\t\};]
CLASSOK2          [ \n\t\{;:]
PUREVIRTOK        [ \n\t;]

DIGIT            [0-9]
FILENAME         \"([^\n\"])*\"

%s sEATCODE 
%s sCLASS 
%s sCLASSCODE 
%s sENUMERATION 
%s sENUMCODE 
%s sEXPRESSION
%s sCONSTEXPR
%s sEATTEMPLATE

// these 2 states were used to handle C++ comments
// the cpp of Solaris 2.0 is able to handle both
// sorts of comments; /* comment */  and // comment
// When I invoke the cpp with the option -B I won't
// have to treat comments myself. 
//%s sCOMMENT 
//%s sCLASSCOMMENT 

// I use these 2 states to ignore the crap of the CPP
%x CPP_OUTPUT EAT_END_OF_LINE

%%


                       { if(first_time) {
                           first_time = 0;
                           BEGIN sEATCODE;
                           Report::debug("[CTLex] First time started with EATCODE");
                           }
                       }

<sEATCODE>"//".*\n     { /* comment ignored */ }
<sEATCODE>{CLASSOK1}class/{CLASSOK2} { KlammerAuf = 0;
                                       KlammerZu = 0;
                                       IgnoreCode = 0; /* Inhalt der naechsten { } nicht ignorieren */
                                       BEGIN sCLASS;
                                       Report::debug("[CTLex] entered CLASS from EATCODE");
                                       Report::debug("[CTLex] KEYWORD: class");
                                       yylval.string = new RCString ("CLASS");
                                       return CTYacc::tCLASS; }
<sEATCODE>^class/{CLASSOK2} { KlammerAuf = 0;
                              KlammerZu = 0;
                              IgnoreCode = 0; /* Inhalt der naechsten { } nicht ignorieren */
                              BEGIN sCLASS;
                              Report::debug("[CTLex] entered CLASS from EATCODE");
                              Report::debug("[CTLex] KEYWORD: class");
                              yylval.string = new RCString ("CLASS");
                              return CTYacc::tCLASS; }
<sEATCODE>template/{TEMPLATEOK}    { /* ich will nur folgendes erkennen:
                                     template < ... > class ...
                                     
                                     daher akzeptiere ich template nur, wenn dieses von
                                     < ... > class gefolgt wird. Ansonsten verwerfe ich
                                     alles in den < ... > da hier class stehen koennte!    */
                                     
                                     KlammerAuf = 0;
                                     KlammerZu = 0;
                                     IgnoreCode = 0; /* Inhalt der naechsten { } nicht ignorieren */
                                     BEGIN sCLASS;
                                     Report::debug("[CTLex] entered CLASS from EATCODE");
                                     Report::debug("[CTLex] KEYWORD: template");
                                     yylval.string = new RCString ("TEMPLATE");
                                     return CTYacc::tTEMPLATE; }
<sEATCODE>template     { Report::debug("[CTLex] WRONG TEMPLATE !!!");
                         Report::debug("[CTLex] left EATCODE to EATTEMPLATE");
                         BEGIN sEATTEMPLATE; }
<sEATCODE>class        { Report::debug("[CTLex] WRONG CLASS !!!"); }
<sEATTEMPLATE>\>       { Report::debug("[CTLex] left EATTEMPLATE to EATCODE");
                         BEGIN sEATCODE; }


<sCLASSCODE>"{"        { GeschweifteKlammern++;      /* irgendeine Klammer im Code */
                         /* return yytext[0]; */ }
<sCLASSCODE>"}"        { GeschweifteKlammern--;
                         if (GeschweifteKlammern == 0) { 
                           KlammerZu++;
                           BEGIN sCLASS;    /* letzte Klammer im Code */
                           Report::debug("[CTLex] left CLASSCODE to CLASS");
                           return yytext[0];
                           } 
                       }
<sCLASSCODE>.          { /* ignore C++ code inside a class definition */ }



<sEXPRESSION>"("       { RundeKlammern++;
                         ausdruck += "("; 
                       }
<sEXPRESSION>","       { /* - if I parse a ',' I close the expression
                            - this is not correct, but when there is
                              a not matching () - paranthesis count
                              it's still a parsed expression
                            - I assume that a wrong ',' inside an expression
                              is more rare than a wrong paranthesis
                         */
                         BEGIN sCLASS;
                         Report::debug("[CTLex] left to CLASS from EXPRESSION by ,");
                         yylval.string = new RCString (",");
                         return CTYacc::tKOMMA;
                       }

<sEXPRESSION>")"       { if (RundeKlammern == 0) {
                           BEGIN sCLASS;
                           InArgumentListe = false;
                           Report::debug("[CTLex] ArgumentListe in CLASS geschlossen");
                           Report::debug("[CTLex] left to CLASS from EXPRESSION by )");;
                           return yytext[0];
                           }
                         else {
                           /* If there isn't the same amount of opening
                              paranthesis as closing paranthesis I'm 
                              still parsing the expression
                           */
                           RundeKlammern--;
                           ausdruck += ")";
                           }
                       }

<sEXPRESSION>")"/")"   { // Die naechste Runde Klammer schliesst den Ausdruck
                         // Daher wir hier tEXPRESSION zurueckgegeben
                         // ansonsten waere folgendes nicht OK:
                         // test(... , vec = Vector2D()), denn Vector2D() ist hier
                         // der Ausdruck zur Initialisierung
                         RundeKlammern--;
                         ausdruck += ")";
                         if (RundeKlammern == 0) {
                           Report::debug("[CTLex] EXPRESSION will be closed by next )");;
                           ostrstream os;
                           os << "[CTLex] EXPRESSION: " << ausdruck;
                           Report::debug(os);
                           yylval.string = new RCString(ausdruck);  
                           /* keep the whole expression */
                           return CTYacc::tEXPRESSION;
                           }
                       }
<sEXPRESSION>[^,)(]/[)]     { ausdruck += yytext;
                              /* The next token is a closing paranthesis
                                 and will end the expression if there 
                                 were no opening paranthesis left        */
                              if (RundeKlammern == 0) {
                                ostrstream os;
                                os << "[CTLex] EXPRESSION: " << ausdruck;
                                Report::debug(os);
                                yylval.string = new RCString(ausdruck);  
                                /* keep the whole expression */
                                return CTYacc::tEXPRESSION;
                                }
                            }
<sEXPRESSION>[^,)(]/[,]     { ausdruck += yytext;
                              /* The next token is a ',' and will end
                                 the expression in any case            */
                              ostrstream os;
                              os << "[CTLex] EXPRESSION: " << ausdruck;
                              Report::debug(os);
                              yylval.string = new RCString(ausdruck);  
                              /* keep the whole expression */
                              return CTYacc::tEXPRESSION;
                            }
<sEXPRESSION>[^,)(]         { ausdruck += yytext; }



<sCONSTEXPR>"["             { EckigeKlammern++;
                              ausdruck += "[";
                            }
<sCONSTEXPR>"]"             { if (EckigeKlammern == 0) {
                                BEGIN sCLASS;
                                Report::debug("[CTLex] left to CLASS from CONSTEXPR by ]");
                                return yytext[0];
                                }
                              else {
                                /* If there isn't the same amount of opening
                                   paranthesis as closing paranthesis I'm 
                                   still parsing the expression
                                */
                                EckigeKlammern--;
                                ausdruck += "]";
                                }
                            }

<sCONSTEXPR>[^\]]/[\]]      { /* Ausdruckteil gefolgt von ] */
                              ausdruck += yytext;
                              /* The next token is a closing ]
                                 and will end the expression if 
                                 there were no opening [ left      */
                              if (EckigeKlammern == 0) {
                                ostrstream os;
                                os << "[CTLex] CONSTEXPR: " << ausdruck;
                                Report::debug(os);
                                yylval.string = new RCString (ausdruck);  
                                /* keep the whole expression */
                                return CTYacc::tCONSTEXPR;
                                }
                            }
<sCONSTEXPR>[^\]]           { ausdruck += yytext; }



<sCLASS>"("            { InArgumentListe = true;
                         Report::debug("[CTLex] CLASS: ArgumentListe gestartet");
                         return yytext[0]; }
<sCLASS>")"            { if (InArgumentListe) { 
                           InArgumentListe = false;
                           Report::debug("[CTLex] CLASS: ArgumentListe geschlossen");
                           return yytext[0];
                           }
                         else {
                           Report::debug("[CTLex] CLASS: unexpected )");
                           return yytext[0];
                           }
                       }
<sCLASS>"="            { if (InArgumentListe) {
                           BEGIN sEXPRESSION;
                           RundeKlammern = 0;
                           ausdruck = "";
                           Report::debug("[CTLex] entered EXPRESSION from CLASS");
                           }
                         return yytext[0];
                       }
<sCLASS>"="{white}*"0"/{PUREVIRTOK}  { Report::debug("[CTLex] KEYWORD: = 0");
                                       yylval.string = new RCString (yytext);
                                       return CTYacc::tPUREVIRTUAL; }
<sCLASS>"["            { BEGIN sCONSTEXPR;
                         EckigeKlammern = 0;
                         ausdruck = "";
                         Report::debug("[CTLex] entered CONSTEXPR from CLASS");
                         return yytext[0];
                       }
<sCLASS>"{"           { KlammerAuf++;
                        /* if (KlammerAuf > 1) { */
                        if (IgnoreCode == 1) {
                          GeschweifteKlammern = 1;  /* Klammerbilanz {} ist +1 } */
                          BEGIN sCLASSCODE;
                          Report::debug("[CTLex] entered CLASSCODE from CLASS");
                          }
                        IgnoreCode = 1; /* naechste { } ignorieren */
                        return yytext[0]; }
<sCLASS>"}"{white}*/";"     { KlammerZu++;
                              if (KlammerAuf == KlammerZu) { 
                                /* BEGIN sEATCODE; */
                                Report::debug("[CTLex] Next Token is ; and will leave CLASS to EATCODE"); 
                                }
                              IgnoreCode = 1; /* class fertig -> Code in { } ignorieren */
                              return yytext[0];
                            }                        
<sCLASS>"}"           { KlammerZu++;
                        if (KlammerAuf == KlammerZu) { 
                          BEGIN sEATCODE;
                          Report::debug("[CTLex] left CLASS to EATCODE"); 
                          }
                        IgnoreCode = 1; /* class fertig -> Code in { } ignorieren */
                        return yytext[0];
                      }
<sCLASS>";"           { if ((KlammerAuf == 0) || (KlammerAuf == KlammerZu)) {
                          Report::debug("[CTLex] CLASS: Strichpunkt nach Klassendeklaration");
                          BEGIN sEATCODE;
                          Report::debug("[CTLex] left CLASS to EATCODE");
                          return yytext[0];
                          }
                        else {
                          /* REJECT; */
                          Report::debug("[CTLex] SPECIAL CHAR: ;");
                          return yytext[0];
                          }
                      }
<sCLASS>"//".*\n      { /* comment ignored */ }
<sCLASS>class         { Report::debug("[CTLex] KEYWORD: class");
                        IgnoreCode = 0;   /* Inhalt der naechsten { } nicht ignorieren */
                        yylval.string = new RCString (yytext);
                        return CTYacc::tCLASS; }
<sCLASS>struct        { Report::debug("[CTLex] KEYWORD: struct");
                        IgnoreCode = 0;   /* Inhalt der naechsten { } nicht ignorieren */
                        yylval.string = new RCString (yytext);
                        return CTYacc::tSTRUCT; }
<sCLASS>union         { Report::debug("[CTLex] KEYWORD: union");
                        IgnoreCode = 1;   /* Inhalt der naechsten { } ignorieren */
                        yylval.string = new RCString (yytext);
                        return CTYacc::tUNION; }
<sCLASS>private       { Report::debug("[CTLex] KEYWORD: private");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tPRIVATE; }
<sCLASS>public        { Report::debug("[CTLex] KEYWORD: public");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tPUBLIC; }
<sCLASS>protected     { Report::debug("[CTLex] KEYWORD: protected");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tPROTECTED; }
<sCLASS>operator      { Report::debug("[CTLex] KEYWORD: operator");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tOPERATOR; }
<sCLASS>virtual       { Report::debug("[CTLex] KEYWORD: virtual");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tVIRTUAL; }
<sCLASS>inline        { Report::debug("[CTLex] KEYWORD: inline");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tINLINE; }
<sCLASS>template      { Report::debug("[CTLex] KEYWORD: template");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tTEMPLATE; }       
<sCLASS>const         { Report::debug("[CTLex] KEYWORD: const");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tCONST; }
<sCLASS>static        { Report::debug("[CTLex] KEYWORD: static");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tSTATIC; }
<sCLASS>auto          { Report::debug("[CTLex] KEYWORD: auto");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tAUTO; } 
<sCLASS>register      { Report::debug("[CTLex] KEYWORD: register");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tREGISTER; } 
<sCLASS>extern        { Report::debug("[CTLex] KEYWORD: extern");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tEXTERN; }
<sCLASS>friend        { Report::debug("[CTLex] KEYWORD: friend");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tFRIEND; }
<sCLASS>char          { Report::debug("[CTLex] KEYWORD: char");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tCHAR; }
<sCLASS>short         { Report::debug("[CTLex] KEYWORD: short");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tSHORT; }
<sCLASS>int           { Report::debug("[CTLex] KEYWORD: int");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tINT; }
<sCLASS>long          { Report::debug("[CTLex] KEYWORD: long");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tLONG; }
<sCLASS>signed        { Report::debug("[CTLex] KEYWORD: signed");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tSIGNED; }
<sCLASS>unsigned      { Report::debug("[CTLex] KEYWORD: unsigned");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tUNSIGNED; }
<sCLASS>float         { Report::debug("[CTLex] KEYWORD: float");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tFLOAT; }
<sCLASS>double        { Report::debug("[CTLex] KEYWORD: double");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tDOUBLE; }
<sCLASS>void          { Report::debug("[CTLex] KEYWORD: void");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tVOID; }
<sCLASS>new           { Report::debug("[CTLex] KEYWORD: new");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tNEW; }
<sCLASS>delete        { Report::debug("[CTLex] KEYWORD: delete");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tDELETE; }
<sCLASS>enum          { Report::debug("[CTLex] KEYWORD: enum");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tENUM; 
                        Report::debug("[CTLex] left CLASS to ENUMERATION");
                        BEGIN sENUMERATION; }
<sCLASS>volatile      { Report::debug("[CTLex] KEYWORD: volatile");
                        yylval.string = new RCString (yytext);
                        return CTYacc::tVOLATILE; }

<sCLASS>operator


<sCLASS>{identifier}  { yylval.string = new RCString (yytext);
                        ostrstream os;
                        os << "[CTLex] BEZEICHNER: " << yytext;
                        Report::debug(os);
                        return CTYacc::tIDENTIFIER; }
<sCLASS>{white}+      { /* ignore whitespace */ }
<sCLASS>"::"          { Report::debug("[CTLex] SPECIAL CHAR: Geltungsbereichoperator");
                        yylval.string = new RCString ("::");
                        return CTYacc::tGELTUNGSBEREICHOPERATOR; }
<sCLASS>"..."         { Report::debug("[CTLex] SPECIAL CHAR: Drei Punkte");
                        yylval.string = new RCString ("...");
                        return CTYacc::t3PUNKTE; }
<sCLASS>","           { Report::debug("[CTLex] SPECIAL CHAR: Komma");
                        yylval.string = new RCString (",");
                        return CTYacc::tKOMMA; }
<sCLASS>":"           { Report::debug("[CTLex] SPECIAL CHAR: Doppelpunkt");
                        yylval.string = new RCString (":");
                        return CTYacc::tDOPPELPUNKT; }
<sCLASS>{special}     { ostrstream os;
                        os << "[CTLex] SPECIAL CHAR: " << yytext;
                        Report::debug(os);
                        return yytext[0];  }
<sCLASS>{word}        { ostrstream os;
                        os << "[CTLex] ANYTHING ELSE: " << yytext;
                        Report::debug(os);
                        return CTYacc::tANYTHINGELSE; }


<sENUMERATION>{identifier}  { ostrstream os;
                              os << "[CTLex] ENUM: BEZEICHNER: " << yytext;
                              Report::debug(os);
                              yylval.string = new RCString (yytext);
                              return CTYacc::tIDENTIFIER; }
<sENUMERATION>{white}+      { /* ignore whitespace */ }
<sENUMERATION>"{"           { BEGIN sENUMCODE;
                              Report::debug("[CTLex] left ENUMERATION to ENUMCODE");
                              return yytext[0]; }
<sENUMERATION>{word}        { ostrstream os;
                              os << "[CTLex] ENUM: ANYTHINGELSE: " << yytext;
                              Report::debug(os);
                              return CTYacc::tANYTHINGELSE; }
<sENUMCODE>"}"              { BEGIN sCLASS;
                              Report::debug("[CTLex] left ENUMCODE to CLASS"); 
                              return yytext[0];
                            }


\n      { myCurrentLine++; }

<<EOF>> { yyterminate();   }

<EAT_END_OF_LINE>\n       { // myCurrentLine++;
			    // BEGIN(0);
			    ostrstream os;
			    os << "[CTLex] left EAT_END_OF_LINE to " << lastState;
                            Report::debug(os);
                            BEGIN(lastState);
			  }
<EAT_END_OF_LINE>.        ;

<sEATCODE>^#            { // Handle output from C preprocessor.
                          lastState = sEATCODE;
                          ostrstream os;
                          os << "[CTLex] left " << lastState << " to CPP_OUTPUT";
                          Report::debug(os);
			  BEGIN(CPP_OUTPUT);
			}
<sCLASS>^#              { // Handle output from C preprocessor.
                          lastState = sCLASS ;
                          ostrstream os;
                          os << "[CTLex] left " << lastState << " to CPP_OUTPUT";
                          Report::debug(os);
			  BEGIN(CPP_OUTPUT);
			}
<sCLASSCODE>^#          { // Handle output from C preprocessor.
                          lastState = sCLASSCODE ;
                          ostrstream os;
                          os << "[CTLex] left " << lastState << " to CPP_OUTPUT";
                          Report::debug(os);
			  BEGIN(CPP_OUTPUT);
			}
<sENUMERATION>^#        { // Handle output from C preprocessor.
                          lastState = sENUMERATION ;
                          ostrstream os;
                          os << "[CTLex] left " << lastState << " to CPP_OUTPUT";
                          Report::debug(os);
			  BEGIN(CPP_OUTPUT);
			}
<sENUMCODE>^#           { // Handle output from C preprocessor.
                          lastState = sENUMCODE ;
                          ostrstream os;
                          os << "[CTLex] left " << lastState << " to CPP_OUTPUT";
                          Report::debug(os);
			  BEGIN(CPP_OUTPUT);
			}
<sEXPRESSION>^#         { // Handle output from C preprocessor.
                          lastState = sEXPRESSION ;
                          ostrstream os;
                          os << "[CTLex] left " << lastState << " to CPP_OUTPUT";
                          Report::debug(os);
			  BEGIN(CPP_OUTPUT);
			}
<sCONSTEXPR>^#          { // Handle output from C preprocessor.
                          lastState = sCONSTEXPR ;
                          ostrstream os;
                          os << "[CTLex] left " << lastState << " to CPP_OUTPUT";
                          Report::debug(os);
			  BEGIN(CPP_OUTPUT);
			}

<CPP_OUTPUT>{DIGIT}+    { myCurrentLine = atoi(yytext); }
<CPP_OUTPUT>{FILENAME}  { myCurrentFilename = yytext;   
			  BEGIN(EAT_END_OF_LINE); // Skip rest of the current line.
			}
<CPP_OUTPUT>.           ;
<CPP_OUTPUT>\n          { // go back to the last state before CPP crap
                          // BEGIN 0;
                          ostrstream os;
                          os << "[CTLex] left CPP_OUTPUT to " << lastState;
                          Report::debug(os);
                          BEGIN(lastState);
                        }
 
"//"                    { // Allow C++ comments.
                          lastState = yy_current_state;
                          ostrstream os;
                          os << "[CTLex] left " << lastState << " to EAT_END_OF_LINE";
                          Report::debug(os);
			  BEGIN(EAT_END_OF_LINE); // Skip rest of the current line.
			}


.                     { /* any not recognized token */ }


%%

