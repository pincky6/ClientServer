#include "Server.h"

Server::Server(std::size_t port) :
	ios(),
	endpoint(asio::ip::address_v4::any(), port),
	acceptor(ios, endpoint)
{
}

void Server::accept() 
{
	asio::ip::tcp::socket socket(ios);
	acceptor.accept(socket);
	sessions.emplace_back(std::move(socket));
}

void Server::disconnectFromClient(std::size_t pos)
{
	auto it = sessions.begin();
	for (int i = 0; i < pos; ++it, ++pos);
	it->sendMessage(Message(SERVER_DISCONNECTED));
	it->close();
	sessions.erase(it);
}

Message Server::receive(std::size_t pos) {
	auto it = sessions.begin();
	for (int i = 0; i < pos; ++it);
	return it->receive();
}

void Server::sendMessage(const std::size_t pos, const Message& message) 
{
	auto it = sessions.begin();
	for (int i = 0; i < pos; ++it);
	it->sendMessage(message.getMessageForSend());
}


std::map<int, Message> Server::receiveAll() {

	std::map<int, Message> messages;
	int i = 0;
	for (auto it = sessions.begin(); it != sessions.end(); ++it, ++i) {
		messages[i] = it->receive();
	}
	return messages;
}
void Server::sendAll(const Message& message) {
	for (auto it = sessions.begin(); it != sessions.end(); ++it) {
		it->sendMessage(message);
	}
}

Server::~Server()
{
	for (auto it = sessions.begin(); it != sessions.end(); it++) {
		if (!it->isOpen()) continue;
		it->sendMessage(Message(SERVER_DISCONNECTED));
		while (it->receive().getMessage() == CLIENT_DISCONNECTED);
	}
}
