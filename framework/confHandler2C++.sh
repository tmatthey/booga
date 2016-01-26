#
# confHandler2C++.sh
#
# Copyright (C) 1995, Stephan Amann <amann@iam.unibe.ch>
#		    Christoph Streit <streit@iam.unibe.ch>
#                     University of Berne, Switzerland
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
#  $Id: confHandler2C++.sh,v 1.8 1996/02/08 18:58:05 amann Exp $
# -----------------------------------------------------------------------------
#

BEGIN {
  SUBSEP = "@";

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
  
  "pwd" | getline path;
  close("pwd");
  nofElem = split(path,pathElem,"/");
  libName = pathElem[nofElem];
 
  ARGV[1] = ARGV[2] = ARGV[3] = ARGV[4] = "";
        
  authorName    = "nobody";
  loginName     = "";
  includeFiles  = "";

  curSection    = "";
  curConf       = "";
  curOption     = "";
  curValue      = "";

  countConf     = 0;
  countOption[-1]   ;
  countValue[-1]    ;

  nameConf[-1]     ;
  nameOption[-1]    ;
  nameValue[-1]     ;

  descConf[-1]      ;
  descOption[-1]    ;
  descValue[-1]     ;

  code[-1]          ;

  errorOccured  = 0;
}

$1 ~ /^#/ {
  next;
}

$1 ~ /^@author/ {
  if ($2) {
    gsub("^[ \t]*" $1 "[ \t]*", "");        
    author = $0;
 
    if (!loginName) 
      loginName = tolower($NF);
  }
  next;
}

$1 ~ /^@login/ {
  if ($2) 
    loginName = $2;
  next;
}

$1 ~ /^@include/ {
  if ($2) 
    includeFile[FNR] = $2;
  next;
}

$1 ~ /^@configure/ {
  if ($2) {
    if ($2 !~ /^[A-Za-z][\.A-Za-z0-9]*$/) {
      print "Error : Illegal identifier " $2 | "cat 1>&2";
      errorOccured = 1;
      exit(1);
    }

    curConf    = $2;
    curSection = "configure";

    countConf++;
    nameConf[countConf] = curConf;
    descConf[curConf] = "";

    countOpt[curConf] = 0;
  }
  next;
}

$1 ~ /^@option/ {
  if ($2) {
    if ($2 !~ /^[A-Za-z][\.A-Za-z0-9]*$/) {
      print "Error : Illegal identifier " $2 | "cat 1>&2";
      errorOccured = 1;
      exit(1);
    }

    curOption  = $2;
    curSection = "option";

    countOption[curConf]++;
    nameOption[curConf,countOption[curConf]] = curOption;
    descOption[curConf, curOption] = "";

    countValue[curConf, curOption] = 0;
  }
  next;
}

$1 ~ /^@value/ {
  if ($2) {
    if ($2 !~ /^[A-Za-z0-9]*$/ && $2 != "@string") {
      print "Error : Illegal identifier " $2 | "cat 1>&2";
      errorOccured = 1;
      exit(1);
    }

    curValue = $2;
    curSection = "value";

    countValue[curConf, curOption]++;
    nameValue[curConf, curOption, countValue[curConf, curOption]] = curValue;
    descValue[curConf, curOption, curValue] = "";
    code[curConf, curOption, curValue] = "";
  }
  next;
}

$1 ~ /^@desc/ {
  gsub("^" $1 "[ ]?", "");        

  if (curSection == "configure")
    descConf[curConf] = descConf[curConf] $0 "\n";
  else if (curSection == "option")
    descOption[curConf, curOption] = descOption[curConf, curOption] $0 "\n";
  else if (curSection == "value")
    descValue[curConf, curOption, curValue] = descValue[curConf, curOption, curValue] $0 "\n";
  else {
    print "Internal Error : Illegal current Section" | "cat 1>&2";
    errorOccured = 1;
    exit(1);
  }

  next;
}

$1 ~ /^@code/ {
  gsub("^" $1 "[ ]?", "");        

  if (curSection == "value")
    code[curConf, curOption, curValue] = code[curConf, curOption, curValue] $0 "\n";
  else {
    print "Error : @code allowed only for value section" | "cat 1>&2";
    errorOccured = 1;
    exit(1);
  }
}

END {
  if (!errorOccured && fileName != "")
    generate();
}

function usage()
{
  print "usage: genConfHandler -type header|source";
  print "                      -filename name specfile";
  errorOccured = 1;
  exit(1);
}

function generate()
{
  printHeader();

  if (fileType == "header")
    printClassHeader();
  else if (fileType == "source")
    printClassSource();

  printTrailer();
}

function printHeader()
{
  print "/*";
 
  if (fileType == "header")
    print " * " fileName ".h";
  else if (filetype == "source")
    print " * " fileName ".C";
 
  if (fileType == "header" || fileType == "source") {
    print " *";
    print " * Copyright (C) 1995, " author " <" loginName "@iam.unibe.ch>";
    print " *                     University of Berne, Switzerland";
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
  }

  if (fileType == "header") {
    print "#ifndef _" fileName "_H";
    print "#define _" fileName "_H\n";
  
    for (i in includeFile)
      print "#include " includeFile[i];

    print "#include \"booga/base/ConfigurationHandler.h\"";
    print "#include \"booga/base/StaticInit.h\"";
    printf "\n";
  }
  else if (fileType == "source")
    print "#include \"booga/" libName "/" fileName ".h\"\n";
}

function printTrailer()
{
  if (fileType == "header")
    print "#endif // _" fileName "_H";
}

function printClassHeader()
{
  for (i=1; i<=countConf; i++) {
    curConf = nameConf[i];
    className = curConf; 
    gsub(/\./, "", className);
    className = className "ConfigurationHandler";
    printTheLine(className);
    print "";
    print "class " className " : public ConfigurationHandler {";
    print "public:";
    print "  virtual Option* handleOption(const Name& name, const Name& option);";
    if (descConf[curConf]) {
      desc = descConf[curConf];
      count = split(desc, descLines, "\n");
      for (j=1; j<count; j++)
	print "  // " descLines[j];
    }
    print "";
    print "protected:";
    for (j=1; j<=countOption[curConf]; j++) {
      curOption = nameOption[curConf, j];
      optionName = curOption;
      gsub(/\./, "", optionName); 
      print "  virtual Option* handleOption" optionName "(const Name& option);";
      if (descOption[curConf, curOption]) {
        desc = descOption[curConf, curOption];
        count = split(desc, descLines, "\n");
        for (k=1; k<count; k++)
	  print "  // " descLines[k];
      }
    }
    print "";
    print "private:";
    for (j=1; j<=countOption[curConf]; j++) {
      curOption = nameOption[curConf, j];
      optionName = curOption;
      gsub(/\./, "", optionName);
      print "  static const Name OPTION" optionName "_;";
      for (k=1; k<=countValue[curConf, curOption]; k++) {
        curValue = nameValue[curConf, curOption, k];
	if (curValue != "@string")
          print "  static const Name VALUE" optionName "_" curValue "_;";
      }
    }
    print "";
    print "public:";
    print "  static void initClass();";
    print "  // enable initialization of static members";

    print "};";
    print "";
    printTheLine("ensure initialization of class " className);
    print "";
    print "declareInitStatics(" className ");";
    print "";
  }
}

function printClassSource()
{
  for (i=1; i<=countConf; i++) {
    curConf = nameConf[i];
    className = curConf; 
    gsub(/\./, "", className);
    className = className "ConfigurationHandler";
    printTheLine(className);
    print "";
    print "implementInitStatics(" className ");"
    print "";
    for (j=1; j<=countOption[curConf]; j++) {
      curOption = nameOption[curConf, j];
      optionName = curOption;
      gsub(/\./, "", optionName);
      print "const Name " className "::OPTION" optionName "_(\"" curConf "." curOption "\");";
      for (k=1; k<=countValue[curConf, curOption]; k++) {
        curValue = nameValue[curConf, curOption, k];
	if (curValue != "@string")
          print "const Name " className "::VALUE" optionName "_" curValue "_(\"" curValue "\");";
      }
    }
    print "";
    if (descConf[curConf]) {
      desc = descConf[curConf];
      count = split(desc, descLines, "\n");
      print "/*";
      for (j=1; j<count; j++)
	print " * " descLines[j];
      print " */";
    }
    print "Option* " className "::handleOption(const Name& name, const Name& option)";
    print "{";
    printf " ";
    for (j=1; j<=countOption[curConf]; j++) {
      curOption = nameOption[curConf, j];
      optionName = curOption;
      gsub(/\./, "", optionName);
      print " if (name == OPTION" optionName "_)";
      print "    return handleOption" optionName "(option);";
      printf "  else"; 
    }
    print "";
    print "    return NULL;";
    print "}";
    print "";

    for (j=1; j<=countOption[curConf]; j++) {
      curOption = nameOption[curConf, j];
      optionName = curOption;
      gsub(/\./, "", optionName); 
      if (descOption[curConf, curOption]) {
        desc = descOption[curConf, curOption];
        count = split(desc, descLines, "\n");
        print "/*";
        for (k=1; k<count; k++)
	  print " * " descLines[k];
        print " */";
      }
      print "Option* " className "::handleOption" optionName "(const Name& option)";
      print "{";
      if (countValue[curConf, curOption]==1 && nameValue[curConf, curOption, 1] == "@string") {
        curValue = nameValue[curConf, curOption, 1];
        if (code[curConf, curOption, curValue]) {
          curCode = code[curConf, curOption, curValue];
	  gsub(/@string/, "((const RCString\\&)option)", curCode);
          count = split(curCode, codeLines, "\n");
        } else {
          print "Error : No code specified for [" curConf ", "curOption ", " curValue "]" | "cat 1>&2";
          errorOccured = 1;
          exit(1);
        }

        for (c=1; c<count; c++)
	  print "  " codeLines[c];

        print "}";
      } else {
        printf " ";
        for (k=1; k<=countValue[curConf, curOption]; k++) {
          curValue = nameValue[curConf, curOption, k];
          if (code[curConf, curOption, curValue]) {
            curCode = code[curConf, curOption, curValue];
            count = split(curCode, codeLines, "\n");
          } else {
            print "Error : No code specified for [" curConf ", "curOption ", " curValue "]" | "cat 1>&2";
            errorOccured = 1;
            exit(1);
          }

          print " if (option == VALUE" optionName "_" curValue "_) {";
            for (c=1; c<count; c++) 
	      print "    " codeLines[c];
          printf "  } else";
        } 
        print "";
        print "    return NULL;";
        print "}";
        print "";
      }
    }
    print "";
    print "void " className "::initClass()";
    print "{";
    print "  Configuration::addHandler(new " className ");";
    print "}";
  }
}

function printTheLine(name)
{
  printf "//";
  for (ii=0; ii < 77 - length(name); ii++)
    printf "_";
  print  " " name;
}

function tolower1stChar(s)
{
  return tolower(substr(s, 1, 1)) substr(s, 2);
}
