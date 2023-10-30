#pragma once
#include "Session.h"
#include "Message.h"

class Client
{
public:
	Client(const std::string&, std::size_t);

	void connect();
	void dissconnect();

	void send(const std::string&);
	Message receive();

	~Client();

private:
	asio::io_service ios;
	asio::ip::tcp::endpoint endpoint;
	asio::ip::tcp::socket socket;
	Session session;
};

