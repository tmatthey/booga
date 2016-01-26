#
# Common stuff of all Makefiles for BOOGA
#
# Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
#                        Christoph Streit <streit@iam.unibe.ch>
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
#  $Id: general.mk,v 1.96 1997/01/17 10:35:28 matthey Exp $
# -----------------------------------------------------------------------------
#
# Adding a new Generator type:
# 1.) Add corresponding SNIFF variable to GEN_FILES
# 2.) Add suffix rules for new type to .h and .C
# 3.) Add new suffixes to vpath and .SUFFIXES
# 4.) Add File type to Sniff Project(s)
# 5.) Add Generator to Sniff Framework-Projectfile
#

.SUFFIXES: .specifierAttr .confHandler .dep .incl

# Libraries, that are part of the booga project
# Order of libraries is order in which they are compiled.
# -----------------------------------------------------------------------------
BOOGALIBS    = base persistence pixmapOp object nurbs animation building texture component graphicsdb glwrapper wxwrapper

# Some variables to change behaviour of make
# -----------------------------------------------------------------------------
INTERACTIVE = 0

# DEBUG options
# -----------------------------------------------------------------------------
ifdef DEBUG
  debug     := 
  separator := @echo ----------------------
else
  MAKEFLAGS += --no-print-directory
  debug     := @
  separator :=
endif

# FILE STRIPPING
# -----------------------------------------------------------------------------
ifdef STRIP
  Strip := strip
else
  Strip := true
endif

# PURIFY (after FILE STRIPPING !!)
# -----------------------------------------------------------------------------
ifdef PURIFY
  empty :=
  Purify := purify $(empty)
  Strip := true
else
  Purify :=
endif

# Include generated makefile support files
# -----------------------------------------------------------------------------
include $(SNIFF_MAKEDIR)/ofiles.incl
include $(SNIFF_MAKEDIR)/dependencies.incl

# Include platform and compiler dendent part 
# -----------------------------------------------------------------------------
include $(SNIFF_RELATIVE_ROOT_DIR)/config/$(PLATFORM).mk
include $(SNIFF_RELATIVE_ROOT_DIR)/config/$(COMPILER).mk

# Determine build type depending on system and compiler
# (Shared Libraries are only possible, if both compiler and platform
#  supports it)
# -----------------------------------------------------------------------------
ifeq ($(system_buildType),SHARED)
  ifeq ($(compiler_buildType),SHARED)
    buildType := SHARED
  else
    buildType := STATIC
  endif
else
  buildType := STATIC
endif

# Other OFILES, generated from parser stuff ...
# -----------------------------------------------------------------------------
PARSER_FILES   = $(SNIFF_Yacc_Source_FILES) \
		   $(SNIFF_Lex_Source_FILES)
PARSER_SOURCES = $(foreach file,$(PARSER_FILES),$(file:%$(suffix $(file))=%.C) \
						      $(file:%$(suffix $(file))=%.h))
PARSER_OFILES  = $(foreach file,$(PARSER_FILES),$(file:%$(suffix $(file))=%.o))					      

# Other OFILES, generated from generated sources ...
# -----------------------------------------------------------------------------
GEN_FILES   = $(SNIFF_Generator_SpecifierAttribute_FILES) \
		$(SNIFF_Generator_ConfigurationHandler_FILES)
GEN_SOURCES = $(foreach file,$(GEN_FILES),$(file:%$(suffix $(file))=src/%.C) \
					       $(file:%$(suffix $(file))=include/%.h))
GEN_OBJS    = $(foreach file,$(GEN_FILES),$(file:%$(suffix $(file))=%.o))

# Include generated dependencies
# -----------------------------------------------------------------------------
DEPENDENT = $(foreach file,\
		$(PARSER_FILES) $(GEN_OFILES),$(file:%$(suffix $(file))=%.dep)) 
# $(GEN_FILES) oder $(GEN_OFILES), letzte "Anderung war auf OFILES		
# -include $(DEPENDENT)

# List of files for distribution, wc, ...
# -----------------------------------------------------------------------------
DISTFILES = $(SNIFF_FILES)
WC_TEMP   = $(SNIFF_RELATIVE_ROOT_DIR)/wc.temp

# Some temporary variables for paths
# -----------------------------------------------------------------------------
RelLib   := $(SNIFF_RELATIVE_ROOT_DIR)/framework/lib
RelIncl  := $(SNIFF_RELATIVE_ROOT_DIR)/framework/include
SrcIncl  := $(SNIFF_ShSWS) $(subst $(SNIFF_PROJECT_DIR),,$(SNIFF_ShSWS))framework/include
ObjIncl  := $(SNIFF_ShOWS) $(subst $(SNIFF_PROJECT_DIR),,$(SNIFF_ShOWS))framework/include
AllIncl  := $(RelIncl) $(ObjIncl) $(SrcIncl) 

# Set build-type dependent and other derived flags 
# -----------------------------------------------------------------------------
LIB_EXT     = $($(buildType)_LIB_EXT)
CXXFLAGS   += $($(buildType)_CXXFLAGS) $(SYSTYPE)
LDFLAGS    += $($(buildType)_LDFLAGS) \
	       -L$(SNIFF_RELATIVE_ROOT_DIR)/framework/lib
CPPFLAGS   += -I. $(patsubst %,-I%,$(AllIncl))
OFILES     += $(PARSER_OFILES) $(GEN_OFILES)
OTHER_LIBS += $($(buildType)_LIBS) $(FW_OTHER_LIBS)

# What has to be removed ?
# -----------------------------------------------------------------------------
mostlyclean := $(MOSTLYCLEAN) \
		 $(wildcard *~) $(wildcard *%) $(wildcard core) \
		 $(wildcard *.dep) $(wildcard *.output) 
clean       := $(CLEAN) $(mostlyclean) \
		 $(wildcard $(OFILES)) $(wildcard $(PARSER_SOURCES)) \
		 $(wildcard $(GEN_SOURCES))
realclean   := $(REALCLEAN) $(clean) \
		 $(wildcard $(LIB_TARGET:%=%.$(LIB_EXT)))
distclean   := $(DISTCLEAN) $(realclean) \
		 $(wildcard $(SNIFF_GENERATE_DIR))

# Set vpath for different types
# -----------------------------------------------------------------------------
vpath %.h  $(AllIncl) 
vpath %.C  $(SNIFF_ShOWS) $(SNIFF_ShSWS) $(AllIncl)
vpath %.o  $(SNIFF_ShOWS)
vpath %.l  $(SNIFF_ShSWS)
vpath %.y  $(SNIFF_ShSWS)
vpath %.$(LIB_EXT)    $(RelLib) $(SNIFF_ShOWS)
vpath %.specifierAttr $(SNIFF_ShSWS)
vpath %.confHandler   $(SNIFF_ShSWS)

# Canned Commands
# -----------------------------------------------------------------------------
ifeq "$(strip $(SUBDIRS))" ""
define enter-subdirs
  # no subdirs to enter
endef
else
define enter-subdirs
  for i in $(SUBDIRS) ; do \
    echo; \
    echo Entering directory $(SNIFF_PROJECT_DIR)/$$i; \
    $(MAKE) $@ -C $$i ; \
  done ; 
endef
endif

define rm-link-to-file
  if [ "$(strip $(SNIFF_ShOWS))" != "" ]; then \
    if [ "$(shell ls -l $@ | $(CUT) -b1)" = "l" ]; then \
      echo Removing link $@ to $(SNIFF_ShOWS)/$@; \
      rm $@; \
    fi; \
  fi;
endef

define rm-link-to-file-and-copy
  if [ "$(strip $(SNIFF_ShOWS))" != "" ]; then \
    if [ "$(shell ls -l $@ | $(CUT) -b1)" = "l" ]; then \
      echo Removing link $@ to $(SNIFF_ShOWS)/$@; \
      rm $@; \
      cp $(SNIFF_ShOWS)/$@ $@; \
    fi; \
  fi;
endef

# Primary rules
# -----------------------------------------------------------------------------

.PHONY: all
all: Message SymbolicLinksToTarget \
     $(GEN_SOURCES) $(filter %.C,$(PARSER_SOURCES)) \
     $(LIB_TARGET) $(EXEC_TARGET)
	$(debug)$(enter-subdirs)

.PHONY: mostlyclean clean realclean distclean
mostlyclean clean realclean distclean: Makefiles
	$(debug){ \
	  if [ ! "$(strip $($@))" = "" ] ; then \
	    echo Removing $($@); \
	    rm -rf $($@); \
	  fi; \
	}
	$(debug)$(enter-subdirs)

.PHONY: wc
wc: Makefiles Directories LinksToTarget WC
	$(debug)$(enter-subdirs)
ifeq ($(MAKELEVEL),0)
	$(debug)cat $(WC_TEMP) | \
	  $(GAWK) '{size+=$$1} \
		    END{print "Project BOOGA containing " size " LOC";}'
	$(debug)rm $(WC_TEMP)
endif

.PHONY: WC
WC: $(filter-out %.shared %.d,$(DISTFILES)) 
ifeq ($(MAKELEVEL),0)
	$(debug)rm -f $(WC_TEMP)
endif
	$(debug)$(WC) $^ /dev/null | \
	  $(GAWK) '$$0!~/total/ {size+=$$1;} \
	  END{print size; \
	      print stderr," Directory $(SNIFF_PROJECT_DIR) containing " \
			     size " LOC" > "/dev/stderr";}' >> $(WC_TEMP)

.PHONY: dist
dist: Makefiles
	@echo Not yet implemented ...

.PHONY: install
install: Makefiles
	@echo Not yet implemented ...

.PHONY: uninstall
uninstall: Makefiles
	@echo Not yet implemented ...

.PHONY: check_obsolete_files
check_obsolete_files: Makefiles Directories LinksToTarget 
	$(debug){ \
	  if [ "$(strip $(SNIFF_PROJECT))" != "" ]; then \
	    echo Checking $(SNIFF_PROJECT_DIR); \
	    for f in *; do \
	      if [ -f $$f ]; then \
		 found=0; \
		 for pf in _dummy_ $(SNIFF_FILES) $(OFILES) $(OTHER_FILES) \
			    $(LINK_TARGET) $(EXEC_TARGET); do \
		   if [ $$pf = $$f ]; then \
		     found=1; \
		     break; \
		   fi; \
		 done; \
		 if [ $$found = 0 ]; then \
		   if [ $(INTERACTIVE) = 1 ]; then \
		     echo "----> Potentially obsolete file: $$f"; \
		     $(RM_INTACT) $$f; \
		   else \
		     echo "----> Potentially obsolete file: $$f. Please remove it."; \
		   fi; \
		 fi; \
	      fi; \
	    done; \
	  fi; \
	}
	$(debug)$(enter-subdirs)

.PHONY: symbolic_links
symbolic_links: SymbolicLinksToTarget SymbolicLinksToMakefiles \
		  SymbolicLinksToProjectFiles	
	$(debug)$(enter-subdirs)

.PHONY: update_pws_to_sws
update_pws_to_sws: UpdateFilesToSharedWs \
		 SymbolicLinksToTarget SymbolicLinksToMakefiles \
		 SymbolicLinksToProjectFiles TouchStatusFile
	$(debug)$(enter-subdirs)

.PHONY: SymbolicLinksToTarget
SymbolicLinksToTarget: Makefiles Directories LinksToTarget
	$(debug){ \
	  if [ "$(strip $(OFILES)$(LIB_TARGET)$(EXEC_TARGET))" != "" -a \
	       "$(strip $(SNIFF_ShOWS))" != "" ]; then \
	    for o in $(OFILES) $(LIB_TARGET).$(LIB_EXT) $(EXEC_TARGET); do \
	      if [ "$$o" != "." -a ! -r $$o ]; then \
		if [ -r $(SNIFF_ShOWS)/$$o ]; then \
		  echo Creating symbolic link $$o to shared target file. ; \
		  ln -s $(SNIFF_ShOWS)/$$o $$o; \
		fi; \
	      fi; \
	    done; \
	  fi; \
	}

.PHONY: SymbolicLinksToProjectFiles
SymbolicLinksToProjectFiles: Makefiles Directories LinksToTarget
	$(debug){ \
	  if [ "$(strip $(SNIFF_PROJECT))" != "" -a "$(strip $(SNIFF_ShOWS))" != "" ]; then \
	    if [ ! -r $(SNIFF_PROJECT) ]; then \
	      if [ -r $(SNIFF_ShOWS)/$(SNIFF_PROJECT) ]; then \
		 echo Creating symbolic link $(SNIFF_PROJECT) to shared project file. ; \
		 ln -s $(SNIFF_ShOWS)/$(SNIFF_PROJECT) $(SNIFF_PROJECT); \
	      fi; \
	    fi; \
	  fi; \
	}

.PHONY: SymbolicLinksToMakefiles
SymbolicLinksToMakefiles: Makefiles Directories LinksToTarget
	$(debug){ \
	  if [ "$(strip $(SNIFF_Make_FILES))" != "" -a "$(strip $(SNIFF_ShSWS))" != "" ]; then \
	    for f in _dummy_ $(SNIFF_Make_FILES); do \
	      if [ ! -f $$f ]; then \
		if [ -r $(SNIFF_ShSWS)/$$f ]; then \
		  echo Creating symbolic link $$f to shared makefile. ; \
		  ln -s $(SNIFF_ShSWS)/$$f $$f; \
		fi; \
	      fi; \
	    done; \
	  fi; \
	}

.PHONY: UpdateFilesToSharedWs
UpdateFilesToSharedWs: Makefiles Directories LinksToTarget
	$(debug){ \
	  if [ "$(strip $(SNIFF_ShSWS))" != "" ]; then \
	    echo Updating files compared to shared workspace $(SNIFF_ShSWS); \
	    for s in _dummy_ $(SNIFF_FILES); do \
	      if [ "$$s" = "_dummy_" ]; then \
		continue; \
	      fi; \
	      if [ -f $$s -a ! -h $$s ]; then \
		if [ ! -w $$s ]; then \
		  if [ -r $(SNIFF_ShSWS)/$$s ]; then \
		    echo Removing $$s: private read-only file; \
		    rm -f $$s; \
                    fi; \
                  else \
		  echo Touching $$s: private writable file; \
		  touch $$s; \
		fi; \
	      fi; \
	    done; \
	  fi; \
	}

.PHONY: TouchStatusFile
TouchStatusFile: Makefiles Directories LinksToTarget
	$(debug){ \
	  if [ "$(strip $(SNIFF_STATUSFILE))" != "" ]; then \
	    echo Touching status file; \
	    touch $(SNIFF_STATUSFILE); \
	  fi; \
	}

.PHONY: Message
Message:
ifeq ($(MAKELEVEL),0)
	@echo Compiling and Linking in $(buildType) mode.
endif

$(LIB_TARGET): $(LIB_TARGET).$(LIB_EXT)
	-$(debug){ \
	  if [ ! -r ../../lib/$(notdir $^) ] ; then \
	    if [ -r $(notdir $^) ] ; then \
	      echo Generating link ../../lib/$(notdir $^); \
	      ln -s ../$(subst _src.shared,,$(SNIFF_PROJECT))/src/$(notdir $^) ../../lib/$(notdir $^); \
	    fi; \
	  fi; \
	}

ifeq ($(buildType),STATIC)
$(LIB_TARGET).$(STATIC_LIB_EXT): $(OFILES)
	@echo
	-$(debug)$(rm-link-to-file-and-copy)
	@echo Building STATIC Library $(notdir $@)
	$(debug)$(AR) $(ARFLAGS) $(notdir $@) $?
	$(debug)$(RANLIB) $(notdir $@)
	@echo ----------------------
endif
ifeq ($(buildType),SHARED)
$(LIB_TARGET).$(SHARED_LIB_EXT): $(OFILES)
	@echo
	-$(debug)$(rm-link-to-file-and-copy)
	@echo Building SHARED Library $(notdir $@)
	$(build-shared-lib)
	@echo ----------------------
endif

$(EXEC_TARGET): SymbolicLinksToTarget $(OFILES) $(DEP_LIBS:-l%=lib%.$(LIB_EXT))
	@echo
	-$(debug)$(rm-link-to-file)
	@echo Linking $(notdir $@) 
	$(debug)$(Purify)$(CXX) $(LDFLAGS) -o $(notdir $@) $(OFILES) $(DEP_LIBS) $(OTHER_LIBS)
	$(debug)$(Strip) $(notdir $@)
	-$(debug){ \
	  if [ ! -r ../bin/$(notdir $@) ] ; then \
	    if [ -r $(notdir $@) ] ; then \
	      echo Generating link ../bin/$(notdir $@); \
	      ln -s ../$(notdir $@)-app/$(notdir $@)../bin/$(notdir $@); \
	    fi; \
	  fi; \
	}
	@echo ----------------------

# Suffix Rules
# -----------------------------------------------------------------------------

%.o: %.C
	@echo
	@echo Compiling $(SNIFF_PROJECT_DIR)/$(notdir $<)
	$(debug)rm -f $(notdir $@)
	$(debug)$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $(notdir $@)
	$(separator)

%.C %.h: %.y
	@echo
	@echo Generating $(SNIFF_PROJECT_DIR)/$(notdir $*".{h,C}")
	$(debug)$(BISON++) $(B++FLAGS) -o $(notdir $*).C -h $(notdir $*).h $<
	$(separator)

%.C %.h: %.l
	@echo
	@echo Generating $(SNIFF_PROJECT_DIR)/$(notdir $*".{h,C}")
#	$(debug)$(FLEX++) $(F++FLAGS) -o$(notdir $*).C -h$(notdir $*).h $<
	$(separator)

src/%.C: %.specifierAttr $(SNIFF_RELATIVE_ROOT_DIR)/framework/specifierAttr2C++.sh
	@echo
	@echo Generating $(SNIFF_PROJECT_DIR)/$@
	$(debug)$(GAWK) -f $(SNIFF_RELATIVE_ROOT_DIR)/framework/specifierAttr2C++.sh \
	 		-type source -filename $* $< > $@
	$(separator)

include/%.h: %.specifierAttr $(SNIFF_RELATIVE_ROOT_DIR)/framework/specifierAttr2C++.sh
	@echo
	@echo Generating $(SNIFF_PROJECT_DIR)/$@
	$(debug)$(GAWK) -f $(SNIFF_RELATIVE_ROOT_DIR)/framework/specifierAttr2C++.sh \
			-type header -filename $* $< > $@
	$(separator)

src/%.C: %.confHandler $(SNIFF_RELATIVE_ROOT_DIR)/framework/confHandler2C++.sh
	@echo
	@echo Generating $(SNIFF_PROJECT_DIR)/$@
	$(debug)$(GAWK) -f $(SNIFF_RELATIVE_ROOT_DIR)/framework/confHandler2C++.sh \
	 		-type source -filename $* $< > $@
	$(separator)

include/%.h: %.confHandler $(SNIFF_RELATIVE_ROOT_DIR)/framework/confHandler2C++.sh
	@echo
	@echo Generating $(SNIFF_PROJECT_DIR)/$@
	$(debug)$(GAWK) -f $(SNIFF_RELATIVE_ROOT_DIR)/framework/confHandler2C++.sh \
			-type header -filename $* $< > $@
	$(separator)

%.dep: %.y 
	@echo
	@echo Generating depedencies $(notdir $@)
	$(debug){ \
		if [ ! -d $(tmpdir)/$(USER) ]; then \
		  mkdir -p $(tmpdir)/$(USER); \
		fi; \
	}
	$(debug)$(BISON++) $(B++FLAGS) -o $(tmpdir)/$(USER)/$(notdir $*).C -h $(tmpdir)/$(USER)/$(notdir $*).h $<
	$(debug)$(SHELL) -ec '$(BUILD_DEPEND) $(CPPFLAGS) $(tmpdir)/$(USER)/$(notdir $*).C \
		| sed '\''s/$*\.o[ :]*/$(notdir $@) &/g'\'' \
		| sed '\''s/\$(tmpdir)\/$(USER)\///g'\'' > $(notdir $@)'
	$(separator)

%.dep: %.l 
	@echo 
	@echo Generating depedencies $(notdir $@)
	$(debug){ \
		if [ ! -d $(tmpdir)/$(USER) ]; then \
		  mkdir -p $(tmpdir)/$(USER); \
		fi; \
	}
	$(debug)$(FLEX++) $(F++FLAGS) -o$(tmpdir)/$(USER)/$(notdir $*).C -h$(tmpdir)/$(USER)/$(notdir $*).h $<
	$(debug)$(SHELL) -ec '$(BUILD_DEPEND) $(CPPFLAGS) $(tmpdir)/$(USER)/$(notdir $*).C \
		| sed '\''s/$*\.o[ :]*/$(notdir $@) &/g'\'' \
		| sed '\''s/\$(tmpdir)\/$(USER)\///g'\'' > $(notdir $@)'
	$(separator)

%.dep: %.C 
	@echo 
	@echo Generating Depedencies for $*.C
	$(debug)$(SHELL) -ec '$(BUILD_DEPEND) $(CPPFLAGS) $< \
		| sed '\''s/$*\.o[ :]*/$@ &/g'\'' > $@'
	$(separator)


