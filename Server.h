#pragma once
#include "Session.h"
#include "Message.h"
#include <vector>
#include <map>
#include <memory>

class Server
{
	Server(const std::size_t port);

	std::vector<const std::string> receive(const std::size_t);
	void sendMessage(const std::size_t, const Message&);

	std::map<int, const std::string> receiveAll();
	void sendAll(const Message&);

	~Server();
private:
	asio::ip::tcp::endpoint endpoint;
	asio::ip::tcp::acceptor acceptor;
	std::vector<std::unique_ptr<Session>> sessions;
};

