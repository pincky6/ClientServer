#pragma once
#include <asio.hpp>
#include "Message.h"

class Session
{
public:
	Session(asio::ip::tcp::socket&& socket);

	Message readMessage();
	void sendMessage();

	void disconnect();

	~Session();
private:
	asio::ip::tcp::socket socket;
};

