// -*- coding: utf-8 -*-
/* *******************************************************************
* File: net/net.cpp                             Part of Shadow World *
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
#include "net.h"

#include <boost/asio.hpp>
#include <thread>
#include <memory>
#include <functional>

namespace asio = boost::asio;
using asio::ip::tcp;

namespace shadow {
namespace net {

/* **************************************************************** */

namespace
{
	asio::io_service io_service_;
	std::thread io_thread_;

	class telnet_server
	{
	public:
		telnet_server()
			: endpoint_(tcp::v4(),
						config::get<unsigned short>("net.telnet.port")),
			  acceptor_(io_service_, endpoint_),
			  socket_(io_service_),
			  accepted_(io_service_)
			{ }

		void start()
			{
				acceptor_.async_accept(accepted_,
					boost::bind(&telnet_server::accept, this,
						boost::asio::placeholders::error));
			}

	private:
		tcp::endpoint endpoint_;
		tcp::acceptor acceptor_;
		tcp::socket   socket_;
		tcp::socket   accepted_;

		void accept(const boost::system::error_code &error)
			{
				if (!error)
				{
					LOG(debug, "New connection");
					accepted_.close();
				}

				start();
			}
	};

	std::shared_ptr<telnet_server> telnet_server_;

	/* ************************************************************ */

	void create_server()
	{
		telnet_server_.reset(new telnet_server);

		telnet_server_->start();
	}
}

/* **************************************************************** */

bool init()
{
	// TODO: Create the listening socket(s)
	create_server();

	// To not block the main thread we have to create a new thread
	// that will handle the ASIO event loop
	io_thread_ = std::thread([]{
		LOG(debug, "Starting network event loop");
		io_service_.run();
		LOG(debug, "Network event loop stopped");
	});

	return true;
}

void clean()
{
	LOG(debug, "net::clean");
	io_service_.stop();
	io_thread_.join();
}

/* **************************************************************** */

} // namespace net
} // namespace shadow
