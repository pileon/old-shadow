dnl ######################################################################
dnl # File: acinclude.m4                               Part of The Raven #
dnl #                                                                    #
dnl # Copyright (C) 2011, Joachim Pileborg and individual contributors.  #
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
dnl #   o Neither the name of The Raven nor the names of its contributors#
dnl #     may be used to endorse or promote products derived from this   #
dnl #     software without specific prior written permission.            #
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

AC_DEFUN([AC_CHECK_PROTO],
  [name_lcase=translit($1, 'A-Z', 'a-z')

   AS_VAR_PUSHDEF([ac_Proto], [ac_cv_proto_$name_lcase])

   AC_CACHE_CHECK([if $1 is prototyped], ac_Proto,
     [AC_COMPILE_IFELSE(
       [AC_LANG_PROGRAM(
         [
AC_INCLUDES_DEFAULT([$2])
#include "src/sysdep.h"
#if defined($1)
  error - already defined
#endif
void $1(int a, char b, int c, char d, int e, char f, int g, char h);
         ],
         [])],
         [AS_VAR_SET(ac_Proto, no)],
         [AS_VAR_SET(ac_Proto, yes)])])

   if test AS_VAR_GET(ac_Proto) = no; then
     AC_DEFINE(
       builtin(format, NEED_%s_PROTO, translit($1, 'a-z', 'A-Z')), 1,
       [Define if the prototype for $1 is not defined.])
   fi

   AS_VAR_POPDEF([ac_Proto])
])

dnl ######################################################################

AC_DEFUN([AC_UNSAFE_CRYPT], [
  AC_CACHE_CHECK([whether crypt needs over 10 characters], ac_cv_unsafe_crypt, [
    if test ${ac_cv_header_crypt_h-no} = yes; then
      use_crypt_header="#include <crypt.h>"
    fi
    if test ${ac_cv_lib_crypt_crypt-no} = yes; then
      ORIGLIBS=$LIBS
      LIBS="-lcrypt $LIBS"
    fi
    AC_TRY_RUN(
changequote(<<, >>)dnl
<<
#define _XOPEN_SOURCE
#include <string.h>
#include <unistd.h>
$use_crypt_header

int main(void)
{
  char pwd[11], pwd2[11];

  strncpy(pwd, (char *)crypt("FooBar", "BazQux"), 10);
  pwd[10] = '\0';
  strncpy(pwd2, (char *)crypt("xyzzy", "BazQux"), 10);
  pwd2[10] = '\0';
  if (strcmp(pwd, pwd2) == 0)
    exit(0);
  exit(1);
}
>>
changequote([, ])dnl
, ac_cv_unsafe_crypt=yes, ac_cv_unsafe_crypt=no, ac_cv_unsafe_crypt=no)])
if test $ac_cv_unsafe_crypt = yes; then
  AC_DEFINE(HAVE_UNSAFE_CRYPT, [],
    [Define if we don't have proper support for the system's crypt().])
fi
if test ${ac_cv_lib_crypt_crypt-no} = yes; then
  LIBS=$ORIGLIBS
fi
])

dnl ######################################################################

AC_DEFUN([AC_CHECK_CXX_ARGUMENT], [
  AC_MSG_CHECKING([if ${CXX-g++} supports argument $1])
  OLD_CXX_FLAGS=$CXXFLAGS
  CXXFLAGS="$1 $CXXFLAGS"
  AC_COMPILE_IFELSE(
    [AC_LANG_PROGRAM([], [])],
    [AC_MSG_RESULT(yes)
     if test "x$EXTRA_CXXFLAGS" = x; then
       EXTRA_CXXFLAGS="$1"
       AC_SUBST([EXTRA_CXXFLAGS])
     else
       EXTRA_CXXFLAGS="$1 $EXTRA_CXXFLAGS"
     fi
     ifelse([$2], , :, [$2])],
    [AC_MSG_RESULT(no)
     ifelse([$3], , :, [$3])])
  CXXFLAGS=$OLD_CXX_FLAGS])

dnl ######################################################################

# The check for this was "borrowed" from the AC_C_BACKSLASH_A test
AC_DEFUN([AC_C_BACKSLASH_E],[
  AC_MSG_CHECKING([[whether backslash-e works in strings]])
  AC_COMPILE_IFELSE(
    [AC_LANG_PROGRAM(
      [],
      [[
#if '\e' == 'e'
        syntax error;
#endif
        char buf['\e' == 'e' ? -1 : 1];
        buf[0] = '\e';
        return buf[0] != "\e"[0];
      ]])],
    [AC_MSG_RESULT(yes)
     AC_DEFINE(HAVE_C_BACKSLASH_E, 1,
       [Define if backslash-e works in C strings.])],
    [AC_MSG_RESULT(no)])])

dnl ######################################################################
dnl # The code below was made by Douglas Gregor, and found on:
dnl # http://aspn.activestate.com/ASPN/Mail/Message/boost/1391132

dnl AC_PATH_BOOST([MINIMUM-VERSION], [ACTION-IF-FOUND], [ACTION-IF-NOT-FOUND])
dnl Test for the Boost C++ libraries of a particular version (or newer)
dnl Defines:
dnl   BOOST_CXXFLAGS to the set of flags required to compiled Boost
AC_DEFUN([AC_PATH_BOOST], 
[
  BOOST_CXXFLAGS=""
  path_given="no"

dnl Extract the path name from a --with-boost=PATH argument
  AC_ARG_WITH(boost,
    [  --with-boost=PATH absolute path name where the Boost C++ libraries
    reside. Alternatively, the BOOST_ROOT environment variable will be used],
    if test "$withval" = no ; then
	path_given="no"
	BOOST_CXXFLAGS=""
    else
      if test "$withval" != yes ; then
        path_given="yes"
        BOOST_CXXFLAGS="-I$withval"
        BOOST_ROOT="$withval"
      fi
    fi    
  )

dnl If no path with given and there is a BOOST_ROOT environment variable,
dnl use it
  if test "$path_given" = "no"; then
    if test "x$BOOST_ROOT" = "x"; then
      BOOST_CXXFLAGS=""
    else
      BOOST_CXXFLAGS="-I$BOOST_ROOT"
    fi
  fi

  boost_min_version=ifelse([$1], ,1.20.0,$1)

  AC_LANG_SAVE
  AC_LANG_CPLUSPLUS
  OLD_CXX_FLAGS=$CXXFLAGS
  CXXFLAGS="$CXXFLAGS $BOOST_CXXFLAGS"
  AC_MSG_CHECKING([for the Boost C++ libraries, version $boost_min_version or newer])
  AC_TRY_COMPILE(
    [
#include <boost/version.hpp>
],
    [],
    [
      have_boost="yes"
    ],
    [
      AC_MSG_RESULT(no)
      have_boost="no"
      ifelse([$3], , :, [$3])
    ])

  if test "$have_boost" = "yes"; then
    WANT_BOOST_MAJOR=`expr $boost_min_version : '\([[0-9]]\+\)'`
    WANT_BOOST_MINOR=`expr $boost_min_version : '[[0-9]]\+\.\([[0-9]]\+\)'`
    WANT_BOOST_SUB_MINOR=`expr $boost_min_version : '[[0-9]]\+\.[[0-9]]\+\.\([[0-9]]\+\)'`
    WANT_BOOST_VERSION=`expr $WANT_BOOST_MAJOR \* 100000 \+ $WANT_BOOST_MINOR \* 100 \+ $WANT_BOOST_SUB_MINOR`

    AC_TRY_COMPILE(
      [
#include <boost/version.hpp>
],
      [
#if BOOST_VERSION >= $WANT_BOOST_VERSION
// Everything is okay
#else
#  error Boost version is too old
#endif

],
      [
        AC_MSG_RESULT(yes)
        ifelse([$2], , :, [$2])
      ],
      [
        AC_MSG_RESULT([no, version of installed Boost libraries is too old])
        ifelse([$3], , :, [$3])
      ])
  fi
  CXXFLAGS=$OLD_CXXFLAGS
  AC_LANG_RESTORE
])

dnl ######################################################################
