#pragma once
#include <string>

class Message
{
public:
	Message(const std::string&);
	const std::string& getMessage() const;

	void reserve(const std::size_t);
	const std::size_t size() const;

	static std::string messageSizeToBinaryString(const std::string&);
	static std::size_t messageSizeFromBinaryString(const std::string&);
private:
	std::string message_;
};
