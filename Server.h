#pragma once
#include "Session.h"
#include "constants.h"

#include <list>
#include <map>

class Server
{
public:
	Server(const std::size_t port);

	void accept();

	Message receive(std::size_t);
	void sendMessage(const std::size_t, const Message&);

	void disconnectFromClient(std::size_t);

	std::map<int, Message> receiveAll();
	void sendAll(const Message&);

	~Server();
private:
	asio::io_service ios;
	asio::ip::tcp::endpoint endpoint;
	asio::ip::tcp::acceptor acceptor;
	std::list<Session> sessions;
};

