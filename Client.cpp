#include "Client.h"

Client::Client(const std::string& rawIPAddress,const std::size_t port) :
	ios(), 
	endpoint(asio::ip::address::from_string(rawIPAddress), port),
	socket(ios),
	session(ios)
{}

void Client::connect() {
	socket.connect(endpoint);
	session.setSocket(socket);
}

void Client::dissconnect() {
	if (session.isOpen()) {
		session.close();
	}
}

void Client::send(const Message& message) {
	session.sendMessage(message.getMessageForSend());
}

Message Client::receive() {
	return session.receive();
}

Client::~Client() {
	dissconnect();
}
		