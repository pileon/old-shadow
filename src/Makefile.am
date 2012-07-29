######################################################################
# File: src/Makefile.am                         Part of Shadow World #
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

AUTOMAKE_OPTIONS = subdir-objects

SUBDIRS = host

LDFLAGS_BOOST = \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_LOG_LDFLAGS) \
	$(BOOST_PROGRAM_OPTIONS_LDFLAGS) \
	$(BOOST_THREAD_LDFLAGS)

LIBS_BOOST = \
	$(BOOST_SYSTEM_LIBS) \
	$(BOOST_LOG_LIBS) \
	$(BOOST_PROGRAM_OPTIONS_LIBS) \
	$(BOOST_THREAD_LIBS) \
	$(BOOST_FILESYSTEM_LIBS)

AM_CPPFLAGS = $(BOOST_CPPFLAGS)
AM_LDFLAGS  = $(LDFLAGS_BOOST)
LIBS       += $(LIBS_BOOST)
LIBS       += host/libhost.a

######################################################################

noinst_PROGRAMS = shadow

noinst_HEADERS  = shadow.h logging.h config.h

shadow_SOURCES  = host/posix/main.cpp shadow.cpp logging.cpp config.cpp

shadow_LDADD    = $(LIBOBJS)

shadow_DEPENDENCIES = host/libhost.a

######################################################################

.PHONY: count
count:
	wc $(HEADERS) $(SOURCES) | sort -g

.PHONY: count16k
count16k:
	$(top_builddir)/scripts/16k.py -c -b -l -s -q $(HEADERS) $(SOURCES) | wc

.PHONY: sloccount
sloccount:
	sloccount -- .

.PHONY: sloccount-all
sloccount-all:
	sloccount --multiproject -- . $(SUBDIRS)

.PHONY: count-all
count-all:
	(files=""; for d in $(SUBDIRS); do \
	   files="$$files `$(MAKE) -s -C $$d get-files`"; \
	 done; \
	wc $(HEADERS) $(SOURCES) $$files | sort -g)

.PHONY: count16k-all
count16k-all:
	(files=""; for d in $(SUBDIRS); do \
	   files="$$files `$(MAKE) -s -C $$d get-files`"; \
	 done; \
	$(top_builddir)/scripts/16k.py -c -b -l -s -q $(HEADERS) $(SOURCES) $$files | wc)

######################################################################
