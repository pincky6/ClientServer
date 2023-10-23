#pragma once
#include <asio.hpp>
#include <queue>

class Session
{
public:
	Session(asio::ip::tcp::socket&& socket);

	void readMessage();
	void sendMessage();
	~Session();
private:
	asio::ip::tcp::socket socket;
};

