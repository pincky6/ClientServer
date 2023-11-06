#include <iostream>
#include <thread>

#include "Server.h"

bool run = true;
void acceptConnection(Server& server) 
{
	while (run)
	{
		server.accept();
	}
}

void receiveAllMessages(Server& server)
{
	while (run)
	{
		auto messages = server.receiveAll();
		for (auto& message : messages)
		{
			std::cout << message.second.getMessage() << std::endl;
			if (message.second.getMessage() == CLIENT_DISCONNECTED)
			{
				server.sendMessage(message.first, Message(SERVER_DISCONNECTED));
				server.disconnectFromClient(message.first);
			}
		}
		std::this_thread::sleep_for(std::chrono::seconds(10));
	}
}


int main()
{
	Server server(3333);
	std::thread acceptConntectionThread = std::thread(acceptConnection, std::ref(server));
	std::thread receiveAllMessageThread = std::thread(receiveAllMessages, std::ref(server));
	std::cout << "Server started" << std::endl;
	unsigned short key = 0;
	while (key != 3)
	{
		std::cout << "1. Send message to client\n" 
				  << "2. Send message to clients\n" 
				  << "3. Exit\n";
		std::cin >> key;
		switch (key)
		{
			case 1:
			{
				std::string message;
				int clientIndex;
				std::cout << "Enter message\n";
				std::cin >> clientIndex;
				std::getline(std::cin, message);
				server.sendMessage(clientIndex, Message(message));
				break;
			}
			case 2:
			{
				std::string message;
				std::cout << "Enter message\n";
				std::getline(std::cin, message);
				server.sendAll(Message(message));
				break;
			}
			case 3:
			{
				run = false;
				server.sendAll(Message(SERVER_DISCONNECTED));
				break;
			}
			default:
			{
				std::cout << "wrong input\n";
			}
		}
	}
	acceptConntectionThread.join();
	receiveAllMessageThread.join();
}