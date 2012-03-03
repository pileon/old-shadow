// -*- coding: utf-8 -*-
/* *******************************************************************
* File: config.cpp                            Part of Shadow World *
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

#include <fstream>
#include <cstring>
#include <cctype>

#include <unistd.h>
#include <getopt.h>

namespace shadow {

std::unordered_map<std::string, std::string> config::config_values;

/* **************************************************************** */

namespace config
{
	namespace
	{
		void set_defaults()
		{
			set("telnet-port-number", defaults::telnet_port_number);
		}

		/* ******************************************************** */

		static const option long_options[] = {
			{ "config", required_argument, nullptr, 'c' },
			{ nullptr, 0, nullptr, 0 }
		};

		static const char short_options[] = "c:hv";

		void get_config_file_name(int argc, char *argv[])
		{
			int c;

			while ((c = getopt_long(argc, argv, short_options, long_options, nullptr)))
			{
				if (c == 'c')
				{
					set("config-file-name", optarg);
					optind = 0;
					return;
				}
			}

			set("config-file-name", std::string(argv[0]) + ".cfg");
		}

		std::string trim(const std::string &str)
		{
			std::string::const_iterator b, e;

			for (b = str.begin(); b != str.end(); ++b)
			{
				if (!std::isspace(*b))
					break;
			}

			for (e = str.end() - 1; e > b; --e)
			{
				if (!std::isspace(*e))
					break;
			}

			return std::string(b, e + 1);
		}

		void parse_config_line(std::string config_line)
		{
			auto comment_pos = config_line.find('#');
			if (comment_pos != std::string::npos)
				config_line = config_line.substr(0, comment_pos - 1);

			config_line = trim(config_line);

			if (config_line.length() == 0)
				return;
		}

		void load_config_file(int argc, char *argv[])
		{
			get_config_file_name(argc, argv);

			std::ifstream config_file{get<std::string>("config-file-name")};
			if (!config_file)
			{
				// TODO: Check if file exists, or for a "real" error
				std::cerr << "Error opening configuration file: "
						  << std::strerror(errno) << '\n';
				return;
			}

			std::string config_line;
			while (std::getline(config_file, config_line))
				parse_config_line(config_line);

			if (!config_file.eof())
			{
				std::cerr << "Error reading configuration file: "
						  << std::strerror(errno) << '\n';
			}
		}
	}
}

/* **************************************************************** */

void config::init(int argc, char *argv[])
{
	set_defaults();

	load_config_file(argc, argv);

	// TODO: Parse arguments
}

void config::clean()
{
}

/* **************************************************************** */

} // namespace shadow
