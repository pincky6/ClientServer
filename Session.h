#pragma once
#include "asio.hpp"
#include "Message.h"

class Session
{
public:
	Session(asio::io_service& ios);
	Session(asio::ip::tcp::socket&& socket);
	Session(Session&&) noexcept;

	void sendMessage(const Message&);
	Message receive();

	bool isOpen() const;
	void close();

	void setSocket(asio::ip::tcp::socket&);
	const asio::ip::tcp::socket& getSocket() const;

	~Session();
private:
	std::size_t getMessageSize();
	Message readMessage(const std::size_t);
private:
	asio::ip::tcp::socket socket;
};

