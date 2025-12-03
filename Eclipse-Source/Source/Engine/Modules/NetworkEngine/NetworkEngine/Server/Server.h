#pragma once

#include <thread>
#include "../AsioTestProj/Message.h"

namespace Eclipse
{
	using asio::ip::udp;
	class Server
	{
	public:

		void RecieveThread(asio::io_context* ioContext)
		{
			ioContext->run();
		}

		Server(asio::io_context& ioContext) :
			socket(ioContext, udp::endpoint(udp::v4(), asio::ip::port_type(18888))),
			recieveThread(&Server::RecieveThread, this, &ioContext)
		{
			StartRecieve();
			memset(recieveBuffer, 0, sizeof(recieveBuffer));
		}

		~Server()
		{
			recieveThread.join();
		}

		void StartRecieve()
		{
			socket.async_receive_from(asio::buffer(recieveBuffer), endpoint, std::bind(&Server::Recieve, this, asio::placeholders::error, asio::placeholders::bytes_transferred));
		}

		void Recieve(const asio::error_code& error, std::size_t bytes_transferred)
		{
			StartRecieve();
			if (error)
				return;

			Message message;
			memcpy(&message, recieveBuffer, bytes_transferred);

			hasClients = true;

			if (message.MetaData.IsGarantied)
			{
				message.MetaData.SentGarantied = false;
				message.MetaData.dataSize = 8;

				Send(message);

				return;
			}

			// AnythingElse
		}

		void Send(const void* value, size_t byteSize)
		{
			if (!hasClients)
				return;

			socket.async_send_to(asio::buffer(value, byteSize), endpoint, std::bind([]() {}));
		}

		void Send(const Message& message)
		{
			Send(&message, message.MetaData.dataSize);
		}

	private:
		udp::socket socket;

		char recieveBuffer[512]{};
		udp::endpoint endpoint;

		bool hasClients;

		std::thread recieveThread;
	};
}