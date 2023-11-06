#include "Session.h"

Session::Session(asio::io_service& ios) : socket(ios)
{}
Session::Session(asio::ip::tcp::socket&& socket_): socket(std::move(socket_))
{}
Session::Session(Session&& session) noexcept  : socket(std::move(session.socket))
{}

void Session::sendMessage(const Message& message) {
	asio::write(socket, asio::buffer(message.getMessage()));
}
Message Session::receive() {
	return readMessage(getMessageSize());
}

bool Session::isOpen() const
{
	return socket.is_open();
}

void Session::close() {
	if(socket.is_open())
		socket.close();
}

void Session::setSocket(asio::ip::tcp::socket& otherSocket) {
	socket = std::move(otherSocket);
}
const asio::ip::tcp::socket& Session::getSocket() const {
	return socket;
}

std::size_t Session::getMessageSize() {
	std::size_t sizeOfMessage = 65, totalyRead = 0;;
	std::string sizeString;
	sizeString.resize(sizeOfMessage);
	while (totalyRead < sizeOfMessage)
	{
		totalyRead += asio::read(socket, asio::buffer(sizeString, sizeOfMessage));
	}
	std::size_t messageSize = Message::messageSizeFromBinaryString(
		std::string(sizeString.begin(), sizeString.begin() + sizeOfMessage - 1)
	);
	return messageSize;
}

Message Session::readMessage(const std::size_t messageSize) {
	std::string buffer;
	buffer.resize(messageSize);
	std::size_t totalyRead = 0;
	while (totalyRead < messageSize)
	{
		totalyRead += asio::read(socket, asio::buffer(buffer ,messageSize - totalyRead));
	}
	return Message(buffer);
}

Session::~Session() {
	close();
}