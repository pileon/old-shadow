// -*- coding: utf-8 -*-
/* *******************************************************************
* File: config.cpp                              Part of Shadow World *
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
#include <boost/program_options.hpp>

namespace shadow {
namespace config {

/* **************************************************************** */

namespace defaults
{
	// This function is used to set default values for the runtime
	// configuration.
	void set()
	{
		using config::set;

		// Network parameters
		set("net.telnet.enable", true);
		set("net.telnet.port"  , 5555);

		// TODO: Database configuration
		// TODO: Other configuration values
	}

	void arguments(boost::program_options::options_description &args)
	{
		args.add_options()
			("help", "show this help message and exit")
			("version", "show version information and exit")
			;
	}
}

/* **************************************************************** */

// Helper functions
namespace
{
	void get_config_file_name(int argc, char *argv[])
	{
	}
}

/* **************************************************************** */

bool init(int argc, char *argv[])
{
	namespace po = boost::program_options;

	po::options_description args("Allowed options:\n");

	defaults::set();
	defaults::arguments(args);

	po::variables_map options;
	po::store(po::parse_command_line(argc, argv, args), options);
	po::notify(options);

	get_config_file_name(argc, argv);

	// TODO: Read configuration file

	// TODO: Parse command line arguments

	return true;
}

void clean()
{
}

/* **************************************************************** */

boost::property_tree::ptree config_private::properties;

/* **************************************************************** */

} // namespace config
} // namespace shadow
