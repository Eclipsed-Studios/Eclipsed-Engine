#pragma once

#include <thread>

#include "Utilities/Common/MainSingleton.h"

#include "NetworkEngine/Shared/Message.h"
#include "NetworkEngine/Shared/GarantiedMessageHandler.h"

#include "asio/asio/asio.hpp"

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
			recieveThread(&Server::RecieveThread, this, &ioContext),
			garantiedMessageHandler(&Server::SendDirectly_NoChecks, this)
		{
			StartRecieve();
			memset(recieveBuffer, 0, sizeof(recieveBuffer));
		}

		~Server()
		{
			recieveThread.join();
		}

		void Update()
		{
			garantiedMessageHandler.Update();
		}

		void StartRecieve()
		{
			socket.async_receive_from(asio::buffer(recieveBuffer), recieveEndpoint, std::bind(&Server::Recieve, this, asio::placeholders::error, asio::placeholders::bytes_transferred));
		}

		void Recieve(const asio::error_code& error, std::size_t bytes_transferred)
		{
			StartRecieve();
			if (error)
				return;

			bool endpointFound = false;

			for (auto& endpoint : endpoints)
				if (endpoint.port() == recieveEndpoint.port())
					endpointFound = true;

			if (!endpointFound)
				endpoints.emplace_back(recieveEndpoint);


			NetMessage message;
			memcpy(&message, recieveBuffer, bytes_transferred);

			hasClients = true;

			if (message.MetaData.IsGarantied)
			{
				message.MetaData.SentGarantied = false;
				message.MetaData.dataSize = 8;

				Send(message);
			}

			for (auto& endpoint : endpoints)
			{
				if (recieveEndpoint.port() == endpoint.port())
					continue;

				Send(&message, message.MetaData.dataSize, endpoint);
			}
		}

		void SendManager()
		{

		}

		void Send(const void* value, size_t byteSize, const udp::endpoint& endpoint)
		{
			if (!hasClients)
				return;

			socket.async_send_to(asio::buffer(value, byteSize), endpoint, std::bind(&Server::SendManager, this));
		}

		void Send(const NetMessage& message)
		{
			for (auto& endpoint : endpoints)
				Send(&message, message.MetaData.dataSize, endpoint);
		}

	private:
		template <class T>
		friend class GarantiedMessageHandler;

		// Does check for garantied messages do not use this function
		void SendDirectly_NoChecks(NetMessage& message, const udp::endpoint& endpoint)
		{
			socket.async_send_to(asio::buffer(&message, message.MetaData.dataSize), endpoint, std::bind(&Server::SendManager, this));
		}

	private:
		udp::socket socket;

		char recieveBuffer[512]{};
		udp::endpoint recieveEndpoint;

		std::vector<udp::endpoint> endpoints;

		bool hasClients;

		std::thread recieveThread;

		GarantiedMessageHandler<Server> garantiedMessageHandler;
	};
}