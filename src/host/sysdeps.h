/* -*- mode: c++; coding: utf-8 -*- */
#ifndef __HOST_SYSDEPS_H__
#define __HOST_SYSDEPS_H__ 1
/* *******************************************************************
* File: host/sysdeps.h                          Part of Shadow World *
*                                                                    *
* Copyright (C) 2012, Joachim Pileborg and individual contributors.  *
* All rights reserved.                                               *
*                                                                    *
* Redistribution and use in source and binary forms, with or without *
* modification, are permitted provided that the following conditions *
* are met:                                                           *
*                                                                    *
*   o Redistributions of source code must retain the above copyright *
*     notice, this list of conditions and the following disclaimer.  *
*   o Redistributions in binary form must reproduce the above        *
*     copyright notice, this list of conditions and the following    *
*     disclaimer in the documentation and/or other materials         *
*     provided with the distribution.                                *
*   o Neither the name of Shadow World nor the names of its          *
*     contributors may be used to endorse or promote products        *
*     derived from this software without specific prior written      *
*     permission.                                                    *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS  *
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,*
* OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,           *
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR *
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY       *
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR     *
* TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF *
* THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF    *
* SUCH DAMAGE.                                                       *
*                                                                    *
******************************************************************* */

#if HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif

#if STDC_HEADERS
# include <stdlib.h>
# include <stddef.h>
#else
# if HAVE_STDLIB_H
#  include <stdlib.h>
# endif
# if HAVE_STDDEF_H
#  include <stddef.h>
# endif
#endif

#if HAVE_STRING_H
# if !STDC_HEADERS && HAVE_MEMORY_H
#  include <memory.h>
# endif
# include <string.h>
#endif

#if HAVE_STRINGS_H
# include <strings.h>
#endif

#if HAVE_INTTYPES_H
# include <inttypes.h>
#endif
#if HAVE_STDINT_H
# include <stdint.h>
#endif

#if HAVE_UNISTD_H
# include <unistd.h>
#endif

#if HAVE_ERRNO_H
# include <errno.h>
#endif

/* **************************************************************** */

// If we have __PRETTY_FUNCTION__ then use that, else __func__ and
// __FUNCTION__ if nothing else.
#if HAVE___PRETTY_FUNCTION__
# if HAVE___FUNC__
#  undef __func__
# endif
# define __func__ __PRETTY_FUNCTION__
#elif HAVE___FUNC__
// Do nothing
#elif HAVE___FUNCTION__
# if HAVE___FUNC__
#  undef __func__
# endif
# define __func__ __FUNCTION__
#else
# if HAVE___FUNC__
#  undef __func__
# endif
# define __func__ "<unknown>"
#endif

#if !HAVE_NULLPTR
// `nullptr´ is a new keyword from the C++11 standard.
// This implementation is taken from the official suggestion document
// SC22/WG21/N2431 = J16/07-0301 (2 October 2007), A name for the null pointer: nullptr
const class
{
public:
	template<class T>            // convertible to any type
    operator T*() const          // of null non-member
		{ return 0; }            // pointer...
	template<class C, class T>   // or any type of null
    operator T C::*() const      // member pointer...
		{ return 0; }
private:
	void operator&() const;      // whose address can't be taken
} nullptr = {};                  // and whose name is nullptr
#endif

#if !defined(PATH_MAX)
# if defined(MAX_PATH)
#  define PATH_MAX MAX_PATH
# else
#  define PATH_MAX 255
# endif
#endif

/* **************************************************************** */

#endif /* __HOST_SYSDEPS_H__ */
