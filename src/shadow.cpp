// -*- coding: utf-8 -*-
/* *******************************************************************
* File: shadow.cpp                              Part of Shadow World *
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

#include <thread>
#include <chrono>

namespace shadow {

/* **************************************************************** */

namespace
{
	void init(int argc, char *argv[])
	{
		// TODO: Load configuration file
		// TODO: Parse arguments
		// TODO: Setup logging
		// TODO: Other misc. setup (like signals)
		// TODO: Network setup
	}

	void boot()
	{
		// TODO: Database setup
		// TODO: Load world
	}

	void clean()
	{
		// TODO: Network cleanup
		// TODO: Save unsave data
		// TODO: Database cleanup
		// TODO: Other misc. cleanup
		// TODO: Logging cleanup
	}

	/* ************************************************************ */

	bool keep_mainloop_running = true;

	void mainloop()
	{
		while (keep_mainloop_running)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
}

/* **************************************************************** */

int main(int argc, char *argv[])
{
	init(argc, argv);

	boot();

	mainloop();

	clean();

	return 0;
}

void shutdown()
{
	keep_mainloop_running = false;
}

/* **************************************************************** */

} // namespace shadow
