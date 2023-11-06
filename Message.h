#pragma once
#include <string>

class Message
{
public:
	Message();
	Message(const std::string&);
	Message(const Message&);
	Message(Message&&);

	Message& operator=(const Message&);
	Message& operator=(Message&&);

	const std::string& getMessage() const;
	std::string getMessageForSend() const;

	static std::string messageSizeToBinaryString(const std::string&);
	static std::size_t messageSizeFromBinaryString(const std::string&);
private:
	std::string message_;
};
