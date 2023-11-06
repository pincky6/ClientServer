#include "Message.h"

Message::Message(): message_("")
{}
Message::Message(const std::string& message) : message_(message)
{}
Message::Message(const Message& message): message_(message.getMessage())
{}
Message::Message(Message&& message): message_(std::move(message.message_))
{}

Message& Message::operator=(const Message& message)
{
    if(this == std::addressof(message))
        return *this;
    message_ = message.message_;
    return *this;
}
Message& Message::operator=(Message&& message)
{
    if (this == std::addressof(message))
        return *this;
    message_ = std::move(message.message_);
    return *this;
}

const std::string& Message::getMessage() const
{
    return message_;
}
std::string Message::getMessageForSend() const
{
    return messageSizeToBinaryString(message_) + "\n" + message_;
}

std::string Message::messageSizeToBinaryString(const std::string& message)
{
    std::string sizeString;
    sizeString.resize(sizeof(std::string::size_type) * 8);
    std::size_t size = message.size();
    for (auto it = sizeString.rbegin(), end = sizeString.rend(); it != end; it++)
    {
        *it = '0' + (size & 1);
        size >>= 1;
    }
    return sizeString;
}

std::size_t Message::messageSizeFromBinaryString(const std::string& binaryString)
{
    std::size_t size = 0, i = 0;
    for (auto it = binaryString.rbegin(), end = binaryString.rend(); it != end; ++it)
    {
        size += (*it - '0') << (i++);
    }
    return size;
}