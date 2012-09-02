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
#include "telnet.h"

#include <boost/asio.hpp>
#include <thread>
#include <memory>
#include <functional>
#include <list>

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
			  socket_(io_service_)
			{ }

		void start()
			{
				auto sock = new tcp::socket(io_service_);

				// TODO: Why cant async_accept handle std::bind instead?
				acceptor_.async_accept(*sock,
					boost::bind(&telnet_server::accept, this,
						sock, boost::asio::placeholders::error));
				// acceptor_.async_accept(*sock,
				// 	std::bind(&telnet_server::accept, this,
				// 		sock, boost::asio::placeholders::error));
			}

	private:
		tcp::endpoint endpoint_;
		tcp::acceptor acceptor_;
		tcp::socket   socket_;

		void accept(tcp::socket *sock, const boost::system::error_code &error)
			{
				if (!error)
				{
					LOG(debug, "New connection");

					if (sock != nullptr)
					{
						LOG(debug, "    from " << sock->remote_endpoint());
						boost::asio::write(*sock,
							boost::asio::buffer("Hello world!\r\n", 14));
					}
					else
						LOG(debug, "    from unknown host");
				}

				if (sock != nullptr)
					delete sock;

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

	using server_ptr_t = std::shared_ptr<server::Server>;
	std::list<server_ptr_t> server_list_;

	template<class S>
	void add_server(const unsigned short port)
	{
		server_list_.push_back(std::make_shared<S>(io_service_, port));
	}
}

/* **************************************************************** */

bool init()
{
	// TODO: Create the listening socket(s)
	// create_server();

	if (config::get<bool>("net.telnet.enabled"))
	{
		add_server<server::Telnet>(
			config::get<unsigned short>("net.telnet.port"));
	}

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
	io_service_.stop();
	io_thread_.join();
}

asio::io_service& get_io_service()
{
	return io_service_;
}

/* **************************************************************** */

} // namespace net
} // namespace shadow
