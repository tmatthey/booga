#
# $RCSfile: specifierAttr2C++.sh,v $
#
# Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
#                        Stephan Amann <amann@iam.unibe.ch>
#                        University of Berne, Switzerland
#
# All rights reserved.
#
# This software may be freely copied, modified, and redistributed
# provided that this copyright notice is preserved on all copies.
#
# You may not distribute this software, in whole or in part, as part of
# any commercial product without the express consent of the authors.
#
# There is no warranty or other guarantee of fitness of this software
# for any purpose.  It is provided solely "as is".
#
# -----------------------------------------------------------------------------
#  $Id: specifierAttr2C++.sh,v 1.11 1996/09/20 09:34:28 streit Exp $
# -----------------------------------------------------------------------------
#

BEGIN {
	#
	# Parse command line options.
	#
	if (ARGC != 6)
	  usage();

	if (ARGV[1] != "-type")
	  usage();
	if (ARGV[2] !~ /header|source/)
	  usage();
	fileType = ARGV[2];

	if (ARGV[3] != "-filename")
	  usage();
	fileName = ARGV[4];

	ARGV[1] = ARGV[2] = ARGV[3] = ARGV[4] = "";
	
	includeFile   ;
	headerPrinted = 0;

         libname       = "object"; # Name of the library we are working in.
	specifierName = ""; # Name of the base class to be generated
	attributeName = ""; # Name of s single attribute (concated with specifierName)
	modeFlag      = ""; # "not set", "argument", "optional"
	memberNumber  = 0;  # array and counter for attribute members
	members[-1];
	argNumber     = 0;  # array and counter for arguments in make method
	arguments[-1];
	delete arguments;
	optNumber     = 0;  # array and counter for optional arguments in make method
	optionals[-1];
	buildArgument = "";
	makeArgument  = "";
	methodName    = ""; # method name to be called for the setAttribute protocoll
      }

$1 ~ /^#/ {  # Remove comments
  next;
}

$1 ~ /^spec/ { 
	      if ($2) {
	        specifierName = $2;
	        if (NF > 2)
                   baseClass = $NF;
                 else
	          baseClass = "ObjectSpecifierAttr";

	        if (!headerPrinted) {
                   printHeader(fileName);
	          headerPrinted = 1;
	        }

                 printSpecifier();
	
                 attributeName = "";
                 modeFlag      = "not set";
                 argNumber     = 0;
                 delete arguments;
                 optNumber     = 0;
                 delete optionals;
                 memberCount    = 0;
                 delete members;
		
	        buildArgument = "";
	        makeArgument = "";
	      }
              next;
	    }

$1 ~ /^lib/  {
	      if ($2) {
                 libname = $2;
               }
	      next;
	    }

$1 ~ /^inc/  {
	      if ($2) {
                 haveIncludes = 1;
                 includeFile[FNR] = $2;
               }
	      next;
	    }

$1 ~ /^attr/ {
	      if ($2) { 
	        if (attributeName != "") 
		  printAttribute();

	        attributeName  = $2;

                 modeFlag       = "not set";
                 argNumber      = 0;
                 delete arguments;
	        optNumber      = 0;
                 delete optionals;
                 memberNumber   = 0;
                 delete members;

	        methodName     = "set" attributeName;
	        additionalCode = "";
	        buildArgument  = "";
	        makeArgument  = "";
	      }
	      next;
	    }

$1 ~ /^arg/  {
	      if ($2) { 
                 modeFlag = "argument";
                 argNumber++;
	        arguments[argNumber, "type"] = $2;	      
	        if ($3)
	          arguments[argNumber, "name"] = $3;
	        else
	          arguments[argNumber, "name"] = "value";
	      }
	      next;
	    }

$1 ~ /^constraint/ && modeFlag == "argument" {
	      if ($2 && argNumber > 0) {
                 gsub("^[ \t]*" $1 "[ \t]*", "");	
	        arguments[argNumber, "constraint"] = $0;
	      }
               next;
	    }

$1 ~ /^error/  && modeFlag == "argument" {
	      if ($2 && argNumber > 0) {
                 gsub("^[ \t]*" $1 "[ \t]*", "");	
	        arguments[argNumber, "error"] = $0;
	      }
               next;
	    }
	    
$1 ~ /^warning/  && modeFlag == "argument" {
	      if ($2 && argNumber > 0) {
                 gsub("^[ \t]*" $1 "[ \t]*", "");	
	        arguments[argNumber, "warning"] = $0;
	      }
               next;
	    }

$1 ~ /^member/ {
  	      if ($2) {
                 memberNumber++;
                 members[memberNumber, "type"] = $2;
                 if ($3)
	          members[memberNumber, "name"] = $3;
	        else
	          members[memberNumber, "name"] = attributeName;
	      }
	      next;
	    }

$1 ~ /^opt/ {
	      if ($2) {
		modeFlag = "optional";
               optNumber++;
	      optionals[optNumber, "type"] = $2;	      
	      if ($3)
	        optionals[optNumber, "name"] = $3;
	      else
	        optionals[optNumber, "name"] = "optValue";
              }
	      next;
	    }

$1 ~ /^default/ && modeFlag == "optional" {
	      if ($2 != "" && optNumber > 0) {
                 gsub("^[ \t]*" $1 "[ \t]*", "");	
	        optionals[optNumber, "default"] = $0;
	      }
	      next;
	    }

$1 ~ /^constraint/ && modeFlag == "optional" {
	      if ($2 && optNumber > 0) {
                 gsub("^[ \t]*" $1 "[ \t]*", "");	
	        optionals[optNumber, "constraint"] = $0;
	      }
              next;
	    }

$1 ~ /^error/ && modeFlag == "optional" {
	      if ($2 && optNumber > 0) {
                 gsub("^[ \t]*" $1 "[ \t]*", "");
	        optionals[optNumber, "error"] = $0;
	      }
              next;
	    }

$1 ~ /^set/ {
	      if ($2) {
                 gsub("^[ \t]*" $1 "[ \t]*", "");
                 methodName = $0;
	      }
	      next;
	    }

$1 ~ /^code/ {
	      if ($2) {
                 gsub("^[ \t]*" $1 "[ \t]", "");	
	        if (additionalCode) 
 	          additionalCode = additionalCode "\n  " $0;
	        else
                  additionalCode = "  " $0;
	      }
               next;
	    }

$1 ~ /^build/ {
                if ($2) {
                  gsub("^[ \t]*" $1 "[ \t]*", "");	
                  buildArgument = $0;
                }
                next;
              }
	    
$1 ~ /^make/ {
               if ($2) {
                 gsub("^[ \t]*" $1 "[ \t]*", "");	
	        makeArgument = $0;
               }
               next;
	    }
	    
END {
      if (fileName != "") {
        if (attributeName != "") 
	  printAttribute();
        printTrailer(fileName);
      }
    }


function printHeader(fileName)
{
  print "/*";

  if (fileType == "header")
    print " * " fileName ".h";
  else
    print " * " fileName ".C";

  print " *";
  print " * Copyright (C) 1994-96, University of Berne, Switzerland";
  print " *";
  print " * All rights reserved.";
  print " *";
  print " * This software may be freely copied, modified, and redistributed";
  print " * provided that this copyright notice is preserved on all copies.";
  print " *";
  print " * You may not distribute this software, in whole or in part, as part of";
  print " * any commercial product without the express consent of the authors.";
  print " *";
  print " * There is no warranty or other guarantee of fitness of this software";
  print " * for any purpose.  It is provided solely \"as is\".";
  print " *";
  print " */\n";

  if (fileType == "header") {
    print "#ifndef _" fileName "_H";
    print "#define _" fileName "_H\n";
  
    print "#include \"booga/base/Value.h\"";
    
    for (i in includeFile)
      print "#include " includeFile[i];
    
    printf "\n";

    print "class " specifierName ";"
    print "class RCString;"
    
    printf "\n";
  }
  else {
    print "#include \"booga/base/Value.h\"";
    print "#include \"booga/base/Report.h\"";
    print "#include \"booga/" libname "/" fileName ".h\"";
    print "#include \"booga/" libname "/" specifierName ".h\"";
    printf "\n";
  }
}

function printTrailer(fileName)
{
  if (fileType == "header")
    print "#endif // _" fileName "_H";
}

function printSpecifier()
{
  if (fileType == "header")
    printSpecifierHeader();
  else
    printSpecifierSource();
}

function printSpecifierHeader()
{
  className = specifierName "Attr";
  printTheLine(className);
 
  printf "\nclass " className;
  print  " : public " baseClass " {";

  print  "declareRTTI(" className ");";
  print  "// enable RTTI support\n";

  print  "public:"
  print  "  virtual void setAttribute(" specifierName "* " tolower(specifierName) ") const = 0;";
  print  "  // Interface to class " specifierName ". Whenever setSpecifier(specifier)";
  print  "  // is called for an instance of class " specifierName ",";
  print  "  // specifier->setAttribute(" tolower(specifierName) "Object) will be called. Method";
  print  "  // setAttribute has to alter the appropriate member of the " specifierName;
  print  "  // object by executing the right method. The corresponding call graph:";
  print  "  //";
  print  "  //   " tolower(specifierName) "Object->setSpecifier(specifier)";
  print  "  //       specifier->setAttribute(" tolower(specifierName) "Object)";
  print  "  //           " tolower(specifierName) "Object->setTheAttribute(newValue)";
  print  "  //";
  print  "  // This technique allows a method dispatch without case analysis.";

  print "};\n";
}

function printSpecifierSource()
{
  className = specifierName "Attr";
  printTheLine(className);
  print  "\nimplementRTTI(" className ", " baseClass ");\n";
}

function printAttribute()
{
  if (fileType == "header")
    printAttributeHeader();
  else
    printAttributeSource();
}

function printAttributeHeader()
{
  className = specifierName "Attr" attributeName;
  printTheLine(className);  
  printf "\nclass " className;
  print  " : public " specifierName "Attr {";

  print  "declareRTTI(" className ");";
  print  "// enable RTTI support\n";

  print  "public:"
  print  "  " className "(Exemplar) {}";

  print  "  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;"; 
  print  "  virtual void setAttribute(" specifierName "* " tolower(specifierName) ") const;";

  if (memberNumber > 0) {

    printf  "  " className "(";
    for (i=1; i<=memberNumber; i++) {
      printf "const " members[i, "type"] "& " tolower1stChar(members[i,"name"]);
      if (i < memberNumber)
        printf ", ";
    }
    print ");";

    print  "\nprivate:";
    for (i=1; i<=memberNumber; i++)
      print  "  " members[i, "type"] " my" members[i, "name"] ";";
  }
  print  "};\n";
}

function printAttributeSource()
{
  className = specifierName "Attr" attributeName;
 
  printTheLine(className);  

  print  "\nimplementRTTI(" className ", " specifierName "Attr);\n";
  
  #------------------------------------------------------------ Constructor

  if (memberNumber > 0) {

    printf className "::" className "(";
    for (i=1; i<=memberNumber; i++) {
      printf "const " members[i, "type"] "& " tolower1stChar(members[i,"name"]);
      if (i < memberNumber)
        printf ", ";
    }
    print ")";

    printf ": "
    for (i=1; i<=memberNumber; i++) {
      printf "my" members[i, "name"] "(" tolower1stChar(members[i,"name"]) ")";
      if (i < memberNumber)
        printf ", ";
    }
    print  "\n{}\n";
  }

  #------------------------------------------------------------ make method

  print "Makeable* " className "::make(RCString& errMsg,";
  printf("%" length(className)+17 "s%s\n", 
         " ", "const List<Value*>* parameters) const"); 
  print  "{";

  #
  # Getting and checking the parameters ...
  #
  
  if (optNumber > 0) {
    print  "  long provided_ = (!parameters ? 0 : parameters->count());";
    print  "  if (provided_ < " argNumber " || provided_ > " argNumber+optNumber ") {";
    print  "    std::stringstream str; str \<\< provided_;";
    printf "    errMsg = RCString(\"between " argNumber " and " argNumber+optNumber;
    print  " parameter(s) required, \")"
    print  "             + str.str().c_str();";
    print  "    return NULL;";
    print  "  }\n";
  }
  else
    print "  checkParameterNumber(" argNumber ");";

  for (i=1; i <= argNumber; i++) {
    print "  getParameter(" i ", " arguments[i, "type"] ", " arguments[i, "name"] ");";
    if (arguments[i, "constraint"]) {
       print "  if (!(" arguments[i, "constraint"] ")) {";
       if (arguments[i, "error"]) {
         print "    errMsg = "  arguments[i, "error"] ";";        
         print "    return NULL;";
       }
       else if (arguments[i, "warning"]) {
         print "    Report::warning(" arguments[i, "warning"] ");";        
       }
       else {
         printf "    errMsg = \"failed constraint \\\"" arguments[i, "constraint"] 
         print  "\\\" for " i ". argument\";";
         print  "    return NULL;";
       }
       print "  }";
    }
    printf "\n";
  }

  if (optNumber > 0) {
    for (i=1; i <= optNumber; i++) {
      printf  "  " optionals[i, "type"] " " optionals[i, "name"];
      if (optionals[i, "default"] != "")
	printf " = " optionals[i, "default"];
      print ";"
      print  "  if (provided_ > " argNumber+i-1 ") {";
      print  "    getParameter(" argNumber+i ", " optionals[i, "type"] ", tmpVal);";
      print  "    " optionals[i, "name"] " = tmpVal;";
      if (optionals[i, "constraint"]) {
        print  "    if (!(" optionals[i, "constraint"] ")) {";
        if (optionals[i, "error"]) {
          print "      errMsg = "  optionals[i, "error"] ";";        
          print "      return NULL;";
        }
        else {
          printf "    errMsg = \"failed constraint \\\"" optionals[i, "constraint"] 
          print  "\\\" for " i ". argument\";";
          print  "    return NULL;";
        }
        print "    }";
      }
      print  "  }\n";
    }
  }

  #
  # Add the additional source code statements ...
  #
  if (additionalCode)
    print additionalCode "\n";

  #
  # Generating the return value...
  #
  if (makeArgument) {
    print "  return " makeArgument ";"
  }
  else if (buildArgument)
    print "  return new " className "(" buildArgument ");";
  else if (argNumber == 0)
    print "  return new " className "(anExemplar);";
  else
    print "  return new " className "(value);";

  print  "}";

  #------------------------------------------------------------ setAttribute method

  printf "\nvoid " className "::setAttribute(" specifierName;
  print  "* " tolower(specifierName) ") const";
  print  "{";

  if (index(methodName, "("))
    print  "  " tolower(specifierName) "->" methodName ";";
  else {
    printf  "  " tolower(specifierName) "->" methodName "(" 
    for (i=1; i<=memberNumber; i++) {
      printf "my" members[i,"name"];
      if (i < memberNumber)
        printf ", ";
    }
    print ");";
  }
  print  "}\n";
}

function printTheLine(name)
{
  printf "//";
  for (i = 0; i < 77 - length(name); i++)
    printf "_";
  print  " " name;
}

function usage()
{
  print "usage: genObjSpecifier -type header|source";
  print "                       -filename name specfile";
  exit(1);
}

function tolower1stChar(s)
{
  return tolower(substr(s, 1, 1)) substr(s, 2);
}
