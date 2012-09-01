// -*- mode: C++; coding: utf-8 -*-
#ifndef NET_TCP_H_
#define NET_TCP_H_ 1
/* *******************************************************************
* File: net/tcp.h                               Part of Shadow World *
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

#include "server.h"
#include <boost/asio.hpp>

namespace shadow {
namespace net {

using boost::asio::ip::tcp;

/* **************************************************************** */

namespace server {

class TCP : public Server
{
public:
	// Must use the overloaded constructor
	TCP() = delete;

	// Disable copying, movement and assignment
	TCP(const TCP &) = delete;
	TCP(const TCP &&) = delete;
	TCP &operator=(const TCP &) = delete;

	TCP(boost::asio::io_service &service, const unsigned short port)
		: Server(service),
		  local_(tcp::v4(), port),
		  socket_(service),
		  acceptor_(service, local_)
		{ }

	TCP(boost::asio::io_service &service,
		const boost::asio::ip::address &address,
		const unsigned short port)
		: Server(service),
		  local_(address, port),
		  socket_(service),
		  acceptor_(service, local_)
		{ }

	virtual ~TCP()
		{ }

	virtual void start_accept()
		{ }

private:
	tcp::endpoint local_;    // The local address we listen to
	tcp::socket   socket_;   // The socket we're listening for connections on
	tcp::acceptor acceptor_; //
};

} // namespace server

/* **************************************************************** */

} // namespace net
} // namespace shadow

#endif // NET_TCP_H_
