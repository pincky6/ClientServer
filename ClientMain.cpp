#include <iostream>
#include <thread>
#include "Client.h"

//bool run = true;
//void receiveMessageFromServer(Client& client)
//{
//	while (run)
//	{
//		Message message = client.receive();
//		if (message.getMessage() == SERVER_DISCONNECTED)
//		{
//			client.dissconnect();
//			break;
//		}
//		std::cout << message.getMessage() << std::endl;
//		std::this_thread::sleep_for(std::chrono::seconds(10));
//	}
//}
//
//int main()
//{
//	Client client("127.0.0.1", 3333);
//	unsigned short key = 0;
//	client.connect();
//	std::cout << "CONNECTED\nIf you wont to leave enter EXIT\n";
//	std::thread receiveMessage = std::thread(receiveMessageFromServer, std::ref(client));
//	while (key != 2)
//	{
//		std::cout << "1. Send message to server\n" << "2. Exit\n";
//		std::cin >> key;
//		switch (key)
//		{
//			case 1:
//			{
//				std::string message;
//				std::cout << "Enter message: ";
//				std::getline(std::cin, message);
//				client.send(Message(message));
//				break;
//			}
//			case 2:
//			{
//				run = false;
//				client.send(Message(CLIENT_DISCONNECTED));
//				break;
//
//			}
//			default:
//			{
//				std::cout << "wrong input\n";
//			}
//		}
//	}
//	receiveMessage.join();
//}