#pragma once

#include <thread>

#include "Message.h"

#include "GarantiedMessageHandler.h"

namespace Eclipse
{
	using asio::ip::udp;
	class Client
	{
	public:
		~Client()
		{
			recieveThread.join();
		}
		void RecieveThread(asio::io_context* ioContext)
		{
			while (true)
			{
				ioContext->run();
			}
		}

		Client(asio::io_context& ioContext, const char* ip) :
			socket(ioContext),
			serverEndpoint(*(udp::resolver(ioContext)).resolve(udp::v4(), ip, "18888").begin()),
			recieveThread(&Client::RecieveThread, this, &ioContext),
			garantiedMessageHandler(this)
		{
			memset(recieveBuffer, 0, sizeof(recieveBuffer));
			socket.open(udp::v4());
			StartRecieve();
		}

		void Update()
		{
			garantiedMessageHandler.Update();
		}

		void Recieve(const asio::error_code& error, std::size_t bytes_transferred)
		{
			StartRecieve();
			if (error)
				return;

			NetMessage message;
			memcpy(&message, recieveBuffer, bytes_transferred);

			isConnected = true;

			if (message.MetaData.IsGarantied)
			{
				if (!message.MetaData.SentGarantied)
					garantiedMessageHandler.RecievedGarantied(message);
			}
			// else
			// {
			// 	size_t realMessageSize = message.MetaData.dataSize - sizeof(message.MetaData);
			// 	char Zero = '\0';
			// 	memcpy(message.data + realMessageSize, &Zero, 1);
			// 	std::cout << message.data << std::endl;
			// }
		}

		void StartRecieve()
		{
			socket.async_receive_from(asio::buffer(recieveBuffer), recieveEndpoint, std::bind(&Client::Recieve, this, asio::placeholders::error, asio::placeholders::bytes_transferred));
		}

		void SendManager()
		{

		}

		void Send(NetMessage& message, bool SendAnyway = false)
		{
			if (message.MetaData.IsGarantied)
				garantiedMessageHandler.Enqueue(message);
			else
				socket.async_send_to(asio::buffer(&message, message.MetaData.dataSize), serverEndpoint, std::bind(&Client::SendManager, this));
		}

		void SetDeltaTime(float aDeltaTime)
		{
			garantiedMessageHandler.UpdateDeltaTime(aDeltaTime);
		}

	private:
		friend class GarantiedMessageHandler;

		// Does check for garantied messages do not use this function
		void SendDirectly_NoChecks(NetMessage& message)
		{
			socket.async_send_to(asio::buffer(&message, message.MetaData.dataSize), serverEndpoint, std::bind(&Client::SendManager, this));
		}

	private:
		udp::endpoint serverEndpoint;
		udp::socket socket;

		char recieveBuffer[512]{};
		udp::endpoint recieveEndpoint;

		bool isConnected;

		std::thread recieveThread;

		GarantiedMessageHandler garantiedMessageHandler;
	};
}