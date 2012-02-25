######################################################################
# File: mk/build.mk                             Part of Shadow World #
#                                                                    #
# Copyright (C) 2012, Joachim Pileborg and individual contributors.  #
# All rights reserved.                                               #
#                                                                    #
# Redistribution and use in source and binary forms, with or without #
# modification, are permitted provided that the following conditions #
# are met:                                                           #
#                                                                    #
#   o Redistributions of source code must retain the above copyright #
#     notice, this list of conditions and the following disclaimer.  #
#   o Redistributions in binary form must reproduce the above        #
#     copyright notice, this list of conditions and the following    #
#     disclaimer in the documentation and/or other materials         #
#     provided with the distribution.                                #
#   o Neither the name of Shadow World nor the names of its          #
#     contributors may be used to endorse or promote products        #
#     derived from this software without specific prior written      # 
#     permission.                                                    #
#                                                                    #
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             #
# CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        #
# INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           #
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           #
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS  #
# BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,#
# OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,           #
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR #
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY       #
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR     #
# TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF #
# THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF    #
# SUCH DAMAGE.                                                       #
#                                                                    #
######################################################################

TOBJS    = $(patsubst %.c,%.o,$(filter %.c,$(SOURCES)))
TOBJS   += $(patsubst %.cpp,%.o,$(filter %.cpp,$(SOURCES)))
# TODO: Add other source file types as well?

OBJECTS  = $(TOBJS:%.o=.obj/%.o)

include $(topdir)/mk/tools.mk

######################################################################

ifeq ($(VERBOSE),y)
VERBOSE = Y
endif
ifeq ($(VERBOSE),true)
VERBOSE = Y
endif
ifeq ($(VERBOSE),TRUE)
VERBOSE = Y
endif

ifeq ($(VERBOSE),Y)
silent  = 
else
silent  = @
VERBOSE = N
endif

ifeq ($(QUIET),y)
QUIET = Y
endif
ifeq ($(QUIET),true)
QUIET = Y
endif
ifeq ($(QUIET),TRUE)
QUIET = Y
endif

ifeq ($(QUIET),Y)
silent  = @
VERBOSE =
endif

######################################################################

.PHONY: build_all
build_all: pre_build build_targets post_build

.PHONY: pre_build
pre_build: .dep .obj

.PHONY: post_build
post_build:

.PHONY: build_targets
build_targets: build_static_libs build_dynamic_libs build_exes

.PHONY: build_static_libs
build_static_libs:

.PHONY: build_dynamic_libs
build_dynamic_libs:

.PHONY: build_exes
build_exes: $(filter-out %.a %.so,$(TARGETS))

$(filter-out %.a %.so,$(TARGETS)): $(OBJECTS)
ifeq ($(VERBOSE),N)
	@echo "LINK $@"
endif
	$(silent)$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)

######################################################################

# Folders

.dep .obj:
	$(silent)-mkdir $@

######################################################################

.obj/%.o: %.c
ifeq ($(VERBOSE),N)
	@echo "COMP $<"
endif
	$(silent)$(CC) $(CFLAGS) -c -o $@ $^

.obj/%.o: %.cpp
ifeq ($(VERBOSE),N)
	@echo "COMP $<"
endif
	$(silent)$(CXX) $(CXXFLAGS) -MMD -MF "`echo $@ | sed 's#.obj/\(.*\)\.o$$#.dep/\1.d#'`" -MT $@ -c "$<" -o "$@"

######################################################################

# Include dependency files

-include $(foreach dep,$(filter %.c,$(SOURCES)),$(dep:%.c=.dep/%.d))
-include $(foreach dep,$(filter %.cpp,$(SOURCES)),$(dep:%.cpp=.dep/%.d))

######################################################################
