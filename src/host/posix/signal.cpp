// -*- coding: utf-8 -*-
/* *******************************************************************
* File: hosts/posix/signal.cpp                  Part of Shadow World *
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

#include "shadow.h"
#if HAVE_SIGNAL_H
# include <signal.h>
#endif

namespace shadow {
namespace host {
namespace signals {

/* **************************************************************** */

namespace handlers
{
	void sighup(int)
	{
		LOG(info, "HUP received");
		shadow::exit();
	}
}

namespace
{
	typedef RETSIGTYPE sigfunc(int);

	/* ************************************************************ */

#if HAVE_SIGACTION
	# define signal my_signal

	/*
	 * New implementation of signal(2), using sigaction(2).
	 * Taken from the book ``Advanced Programmin in the UNIX Environment''
	 * by W. Richard Stevens.
	 */
	sigfunc *signal(int signo, sigfunc *func)
	{
		struct sigaction nact, oact;

		nact.sa_handler = func;
		nact.sa_flags   = 0;
# ifdef SA_INTERRUPT
		nact.sa_flags  |= SA_INTERRUPT;
# endif
		sigemptyset(&nact.sa_mask);

		if (sigaction(signo, &nact, &oact) < 0)
			return SIG_ERR;

		return oact.sa_handler;
	}
#endif  // HAVE_SIGACTION

	/* ************************************************************ */

	// Signal handlers

}

/* **************************************************************** */

bool setup()
{
	signal(SIGHUP , handlers::sighup);
	signal(SIGINT , handlers::sighup);
	signal(SIGTERM, handlers::sighup);

	return true;
}

/* **************************************************************** */

} // namespace signals
} // namespace host
} // namespace shadow
