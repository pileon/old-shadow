dnl ######################################################################
dnl # File: configure.ac                            Part of Shadow World #
dnl #                                                                    #
dnl # Copyright (C) 2012, Joachim Pileborg and individual contributors.  #
dnl # All rights reserved.                                               #
dnl #                                                                    #
dnl # Redistribution and use in source and binary forms, with or without #
dnl # modification, are permitted provided that the following conditions #
dnl # are met:                                                           #
dnl #                                                                    #
dnl #   o Redistributions of source code must retain the above copyright #
dnl #     notice, this list of conditions and the following disclaimer.  #
dnl #   o Redistributions in binary form must reproduce the above        #
dnl #     copyright notice, this list of conditions and the following    #
dnl #     disclaimer in the documentation and/or other materials         #
dnl #     provided with the distribution.                                #
dnl #   o Neither the name of Shadow World nor the names of its          #
dnl #     contributors may be used to endorse or promote products        #
dnl #     derived from this software without specific prior written      # 
dnl #     permission.                                                    #
dnl #                                                                    #
dnl # THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             #
dnl # CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        #
dnl # INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           #
dnl # MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           #
dnl # DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS  #
dnl # BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,#
dnl # OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,           #
dnl # PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR #
dnl # PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY       #
dnl # THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR     #
dnl # TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF #
dnl # THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF    #
dnl # SUCH DAMAGE.                                                       #
dnl #                                                                    #
dnl ######################################################################

AC_INIT(shadow, [0.1.0], [shadow@pileborg.se], , [https://github.com/pileon/shadow])
dnl AC_CONFIG_AUX_DIR([scripts])
dnl AC_CONFIG_MACRO_DIR([scripts])
AM_INIT_AUTOMAKE
AC_COPYRIGHT([Parts of the configure script is copyright (C) 2012, Joachim Pileborg and individual contributors.])
AC_CONFIG_SRCDIR([src/shadow.h])
AC_CONFIG_HEADERS([src/host/autoconf.h])
dnl AC_CONFIG_LIBOBJ_DIR([src/libobj])
AC_CONFIG_FILES([Makefile])

dnl ######################################################################
dnl # Checks for programs

dnl # First check which GCC version is wanted
AC_ARG_WITH(gcc,
  [  --with-gcc=<version>    Use GCC (gcc and g++) of the specified version],
  [if test "$withval" != yes; then
     AC_PROG_CXX([g++-$withval g++ c++q])
   else
     AC_PROG_CXX
   fi],
  [AC_PROG_CXX])

dnl ######################################################################

dnl ######################################################################

dnl ######################################################################

dnl ######################################################################

dnl ######################################################################

dnl ######################################################################

AC_OUTPUT

dnl ######################################################################
