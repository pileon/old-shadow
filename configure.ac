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
AC_CONFIG_AUX_DIR([scripts])
AC_CONFIG_MACRO_DIR([scripts])
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

AC_PROG_CXX_C_O
AC_PROG_CXXCPP

dnl # Set default language to C++
AC_LANG([C++])

dnl # General programs, and their arguments
dnl AC_PROG_RANLIB
AC_PROG_LIBTOOL

AC_REQUIRE_CPP

dnl ######################################################################
dnl # Checks for libraries

dnl ######################################################################
dnl # Checks for header files

dnl ######################################################################
dnl # Checks for types

AC_TYPE_MBSTATE_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_SIGNAL

dnl ######################################################################
dnl # Checks for structures

dnl ######################################################################
dnl # Checks for compiler characteristics

AC_C_BACKSLASH_A
AC_C_BACKSLASH_E

AC_ARG_ENABLE([gdb3],
  [  --enable-gdb3           enable higher debug level option to the compiler],
  [if test $enableval = yes; then
     AC_CHECK_CXX_ARGUMENT(-ggdb3, [cxx_have_ggdb3=yes], [cxx_have_ggdb3=no])
   fi])
if test $cxx_have_ggdb3 = yes; then
  CXXFLAGS=`echo $CXXFLAGS | sed 's/\-g//'`
fi

AC_CHECK_CXX_ARGUMENT([-std=c++11], [], [AC_CHECK_CXX_ARGUMENT([-std=c++0x])])

AC_CHECK_CXX_ARGUMENT(-pipe)

AC_ARG_ENABLE([warnings],
  [  --enable-warnings       enable extra warnings from the compiler],
  [if test $enableval = yes; then
     AC_CHECK_CXX_ARGUMENT(-Wall)
     AC_CHECK_CXX_ARGUMENT(-Wextra)
     AC_CHECK_CXX_ARGUMENT(-Weffc++)
     AC_CHECK_CXX_ARGUMENT(-Wconversion)
     AC_CHECK_CXX_ARGUMENT(-Wsign-conversion)
     AC_CHECK_CXX_ARGUMENT(-Woverloaded-virtual)
     AC_CHECK_CXX_ARGUMENT(-pedantic)
   fi])

AC_ARG_ENABLE([opt],
  [  --disable-opt           disable compiler optimizations],
  [if test $enableval = no; then
     CXXFLAGS=`echo "$CXXFLAGS" | sed 's/-O2//'`
   fi])

AC_ARG_ENABLE([profiling],
  [  --enable-profiling      enable compiler profiling of code],
  [if test $enableval = yes; then
     :
   fi])

AC_MSG_CHECKING([if ${CXX-g++} supports __PRETTY_FUNCTION__])
AC_LINK_IFELSE(
  [AC_LANG_PROGRAM(
    [
#include <iostream>
    ],
    [[
      std::cout << __PRETTY_FUNCTION__;
    ]])],
  [AC_MSG_RESULT(yes)
   AC_DEFINE(HAVE___PRETTY_FUNCTION__, 1,
     [Define to 1 if the compiler supports the __FUNCTION__ literal])],
  [AC_MSG_RESULT(no)])

AC_MSG_CHECKING([if ${CXX-g++} supports __FUNCTION__])
AC_LINK_IFELSE(
  [AC_LANG_PROGRAM(
    [
#include <iostream>
    ],
    [[
      std::cout << __FUNCTION__;
    ]])],
  [AC_MSG_RESULT(yes)
   AC_DEFINE(HAVE___FUNCTION__, 1,
     [Define to 1 if the compiler supports the __func__ variable])],
  [AC_MSG_RESULT(no)])

AC_MSG_CHECKING([if ${CXX-g++} supports __func__])
AC_LINK_IFELSE(
  [AC_LANG_PROGRAM(
    [
#include <iostream>
    ],
    [[
      std::cout << __func__;
    ]])],
  [AC_MSG_RESULT(yes)
   AC_DEFINE(HAVE___FUNC__, 1,
     [Define to 1 if the compiler supports the __func__ variable])],
  [AC_MSG_RESULT(no)])

AC_MSG_CHECKING([if ${CXX-g++} supports nullptr])
old_CXXFLAGS=$CXXFLAGS
CXXFLAGS=$EXTRA_CXXFLAGS
AC_LINK_IFELSE(
  [AC_LANG_PROGRAM(
    [],
    [[
      char *char_null = nullptr;
    ]])],
  [AC_MSG_RESULT(yes)
   AC_DEFINE(HAVE_NULLPTR, 1,
     [Define to 1 if the compiler supports the nullptr C++0x constant])],
  [AC_MSG_RESULT(no)])
CXXFLAGS=$old_CXXFLAGS

AC_MSG_CHECKING([if ${CXX-g++} supports computed gotos])
AC_COMPILE_IFELSE(
  [AC_LANG_PROGRAM(
    [],
    [[
      void *my_label_ptr = &&my_label;  /* GCC syntax */
      goto *my_label_ptr;
      return 1;
      my_label:
      return 0;
    ]])],
  [AC_MSG_RESULT(yes)
   AC_DEFINE(HAVE_COMPUTED_GOTOS, 1,
     [Define to 1 if the compilers supports computed gotos])],
  [AC_MSG_RESULT(no)])

dnl TODO: Check for: Unicode string/character support (C++11 u8"\u2018", u"\u2018" and U"\u2018")
dnl TODO: Check for: Raw strings (C++11 R"delim(string)delim")

dnl ######################################################################

dnl ######################################################################

dnl ######################################################################

dnl ######################################################################

dnl ######################################################################

AC_OUTPUT

dnl ######################################################################
