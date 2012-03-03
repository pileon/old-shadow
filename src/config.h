// -*- mode: C++; coding: utf-8 -*-
#ifndef __CONFIG_H__
#define __CONFIG_H__ 1
/* *******************************************************************
* File: config.h                                Part of Shadow World *
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

#include <unordered_map>
#include <sstream>

namespace shadow {
namespace config {

namespace defaults
{
	const int telnet_port_number = 4000;
}

/* **************************************************************** */

void init(int argc, char *argv[]);
void clean();

/* **************************************************************** */

extern std::unordered_map<std::string, std::string> config_values;

template<typename T>
void set(const std::string &name, const T &value)
{
	std::ostringstream os;
	os << value;

	config_values.insert(std::pair<std::string, std::string>(name, os.str()));
}

template<typename T>
const T get(const std::string &name)
{
	auto value_iter = config_values.find(name);
	if (value_iter  == config_values.end())
	{
		set(name, T{});
		value_iter = config_values.find(name);
	}

	std::istringstream is(value_iter->second);
	T value;

	is >> value;

	return value;
}

/* **************************************************************** */

} // namespace config
} // namespace shadow

#endif // __CONFIG_H__
