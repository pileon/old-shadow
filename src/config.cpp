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
#include <boost/filesystem.hpp>
#include <boost/property_tree/info_parser.hpp>

namespace po = boost::program_options;
namespace pt = boost::property_tree;

namespace shadow {
namespace config {

/* **************************************************************** */

namespace defaults
{
	// This function is used to set default values for the runtime
	// configuration.
	void set()
	{
		// Network parameters
		config::set("net.telnet.enable", true);
		config::set("net.telnet.port"  , 5555);

		// TODO: Database configuration
		// TODO: Other configuration values
	}

	void add_arguments(po::options_description &args)
	{
		args.add_options()
			("help,h", "show this help message and exit")
			("version,v", "show version information and exit")
			("config,c", po::value<std::string>(), "path to configuration file")

			// Network options
			("telnet-port,t",
				po::value<int>()->default_value(get<int>("net.telnet.port")),
				"telnet network port")

			// Add more command line parameters here
			;
	}

	void set_arguments(const po::variables_map &options)
	{
		if (options.count("telnet-port"))
			config::set("net.telnet.port", options["telnet-port"].as<int>());
	}
}

/* **************************************************************** */
/* The code below this line should not need to be modified.         */
/* Please leave it alone.                                           */
/* **************************************************************** */

// Helper functions
namespace
{
	bool fetch_config_file_path(const std::string &argv0,
		const po::variables_map &options)
	{
		namespace fs = boost::filesystem;

		fs::path file;

		// Configuration file specified on the command line?
		if (options.count("config"))
			file = options["config"].as<std::string>();

		if (!fs::exists(file))
			file = fs::path(argv0).replace_extension(".rc");

		if (!fs::exists(file))
			file = fs::path("shadow.rc");

		if (!fs::exists(file))
			file = fs::path(".shadowrc");

		if (!fs::exists(file))
			file = fs::path("~/.shadowrc");

		if (!fs::exists(file))
			file = fs::path("/etc/shadow.rc");

		if (fs::exists(file))
		{
			config::set("config.path", file);
			return true;
		}
		else
			return false;
	}

	void read_config_file()
	{
		if (!config::exists("config.path"))
			return;

		pt::info_parser::read_info(config::get<std::string>("config.path"),
					  			   config_private::properties);
	}
}

/* **************************************************************** */

bool init(int argc, char *argv[])
{
	po::options_description args("Allowed options");

	defaults::set();

	defaults::add_arguments(args);

	po::variables_map options;
	po::store(po::parse_command_line(argc, argv, args), options);
	po::notify(options);

	if (options.count("help"))
	{
		std::cout << args;
		return false;
	}

	if (options.count("version"))
	{
		std::cout << "Shadow World version 0\n";
		return false;
	}

	if (fetch_config_file_path(argv[0], options))
		read_config_file();

	defaults::set_arguments(options);

	return true;
}

void clean()
{
}

/* **************************************************************** */

pt::ptree config_private::properties;

/* **************************************************************** */

} // namespace config
} // namespace shadow
