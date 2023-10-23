#pragma once
#include "Session.h"

#include <vector>
#include <map>

class Server
{
	Server(const std::size_t port);

	std::vector<const Message> receive(const std::size_t);
	void sendMessage(const std::size_t, const Message&);

	std::map<int, Message> receiveAll();
	void sendAll(const Message&);

	~Server();
private:
	asio::io_service ios;
	asio::ip::tcp::endpoint endpoint;
	asio::ip::tcp::acceptor acceptor;
	std::vector<Session> sessions;
};

