
/*
 * CTParserUtils.h
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
 *  $Id: CTParserUtils.h,v 1.14 1996/09/13 13:32:56 siebenth Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _CTParserUtils_H
# define _CTParserUtils_H

#include "CTClassDescription2D.h"

    // my internal Structures to represent the
    // parsed classes in a fast and easy way
    // this is the source to produce the needed
    // Casetool-Classes in a postprocessing
    // 
    // Description of a class Member
    struct tKlassenMember {
      RCString type;   // Typ des Attributes
      RCString ptr;    // Zeigerteil des Typs
      RCString view;   // Protected, Private or Public
      RCString name;   // Name des Attributes
      int hasa;        // Assoziation -> has-a Relation
      bool isTemplate; // Has-a Instanciation of a Template
      void clean() { 
        name = "";
        view = "";
        type = "";
        ptr = "";
        hasa = -1;
        isTemplate = false;
        };
      tKlassenMember() { clean(); };
      };
    //
    // Description of a Operations Attribute
    struct tOperationsParameter {
      RCString type;   // Typ des Attributes
      RCString ptr;    // Zeigerteil des Typs
      RCString view;   // Protected, Private or Public
      RCString name;   // Name des Attributes
      RCString init;   // Initialisierungswert
      void clean() {
        type = "";
        ptr = "";
        view = "";
        name = "";
        init = "";
        };
      tOperationsParameter() { clean(); };
      };
    //
    // Descreption of a class operation (method)
    struct tKlassenOperation {
      RCString name;   // Name der Funktion
      RCString type;   // Typ des Rueckgabewertes
      RCString ptr;    // Zeigerteil des Typs
      RCString view;   // Zugriffsrecht der Funktion
      bool isAbstract;  // virtuelle Funktion
      List<tOperationsParameter> OperationsParameterListe;   
                       // Liste der Parameter
      void clean() {
        name = "";
        type = "";
        ptr = "";
        view = "";
        isAbstract = false;
        OperationsParameterListe.removeAll();
        };
      tKlassenOperation() { clean(); };
      };
    //
    // Description of a Baseclass
    struct tBasisKlasse {
      RCString name;
      RCString view;
      bool isVirtual;
      int isa;        // Vererbung -> is-a Relation
      void clean() { 
        name = "";
        view = "";
        isVirtual = false;
        isa = -1;      
        };
      tBasisKlasse() { clean(); };
      };
    //
    // Description of a class
    struct tKlasse {
      RCString ShortName;
      RCString LongName;
      List<tKlassenMember> KlassenMemberListe;
      List<tBasisKlasse> BasisKlassenListe;            
      List<tKlassenOperation> KlassenOperationenListe;
      CTClassDescription2D* hasBecomeThisClass;
      bool isAbstract;
      bool isTemplate;
      RCString TemplateParameters;
      void clean() {
        ShortName = "";
        LongName = "";
        KlassenMemberListe.removeAll();
        KlassenOperationenListe.removeAll();
        BasisKlassenListe.removeAll();
        hasBecomeThisClass = NULL;
        isTemplate = false;
        TemplateParameters = "";
        isAbstract = false;
        };
      tKlasse() { clean(); };
      };
    //
    // Programm = List of classes
    struct tProgramm {
      List<tKlasse> KlassenListe;
      };




#endif // _CTParserUtils_H
