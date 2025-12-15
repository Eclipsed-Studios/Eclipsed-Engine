#pragma once

#include <thread>

#include "Utilities/Common/MainSingleton.h"

#include "NetworkEngine/Shared/Message.h"
#include "NetworkEngine/Shared/GarantiedMessageHandler.h"

#include "asio/asio/asio.hpp"



#include "NetworkEngine/Replication/ReplicationManager.h"
#include <unordered_set>
#include "NetworkEngine/Replication/ReplicatedVariable.h"

#include "EntityEngine/ComponentManager.h"

namespace Eclipse
{
	using asio::ip::udp;
	class Server
	{
	public:
		~Server()
		{
			recieveThread.join();
		}
		void RecieveThread()
		{
			asio::executor_work_guard<asio::io_context::executor_type> work = asio::make_work_guard(myIOContext);

			myIOContext.run();
		}

		void ShutDown()
		{
			myIOContext.stop();
			recieveThread.join();
		}

		Server(asio::io_context& ioContext) :
			myIOContext(ioContext),
			socket(ioContext, udp::endpoint(udp::v4(), asio::ip::port_type(18888))),
			recieveThread(&Server::RecieveThread, this),
			garantiedMessageHandler(&Server::SendDirectly_NoChecks, this)
		{
			StartRecieve();
			memset(recieveBuffer, 0, sizeof(recieveBuffer));
		}

		void Update()
		{
			garantiedMessageHandler.Update();
		}

		void StartRecieve()
		{
			socket.async_receive_from(asio::buffer(recieveBuffer), recieveEndpoint, std::bind(&Server::Recieve, this, asio::placeholders::error, asio::placeholders::bytes_transferred));
		}

		void SendComponentScene()
		{
			std::unordered_set<unsigned> ReplicatedGameObjects;

			const auto& variableManager = Replication::ReplicationManager::RealReplicatedVariableList;
			for (auto& Variable : variableManager)
				ReplicatedGameObjects.emplace(Variable.second->ConnectedComponent->gameObject->GetID());

			for (const auto& gameobject : ReplicatedGameObjects)
			{
				std::vector<Component*> components = ComponentManager::GetComponents(gameobject);

				for (const auto& component : components)
				{
					if (!component->IsReplicated)
						continue;
					NetMessage message;
					Replication::ReplicationManager::CreateComponentMessage(component, message);

					Server& server = Utilities::MainSingleton::GetInstance<Server>();
					server.Send(message, recieveEndpoint);
				}
			}
		}

		int TotalRecievedGO = 0;

		void HandleRequestedScene(const NetMessage& aMessage)
		{
			std::unordered_set<unsigned> ReplicatedGameObjects;

			const auto& variableManager = Replication::ReplicationManager::RealReplicatedVariableList;
			for (auto& Variable : variableManager)
				if (Variable.second->ConnectedComponent->IsReplicated)
					ReplicatedGameObjects.emplace(Variable.second->ConnectedComponent->gameObject->GetID());

			int Replgameobjectsize = ReplicatedGameObjects.size() - 1;

			for (const auto& gameobject : ReplicatedGameObjects)
			{
				NetMessage message;
				message = NetMessage::BuildGameObjectMessage(gameobject, MessageType::Msg_CreateObject, &message, 0, true);

				Server& server = Utilities::MainSingleton::GetInstance<Server>();
				server.Send(message, recieveEndpoint, [Replgameobjectsize, this]() {

					if (TotalRecievedGO++ >= Replgameobjectsize)
					{
						TotalRecievedGO = 0;
						SendComponentScene();
					}

					});
			}
		}

		void HandleRecieve(const NetMessage& aMessage)
		{
			switch (aMessage.MetaData.Type)
			{
			case MessageType::Msg_RequestSceneInfo:
				HandleRequestedScene(aMessage);
				break;

			default:
				break;
			}
		}

		void Recieve(const asio::error_code& error, std::size_t bytes_transferred)
		{
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

			HandleRecieve(message);

			hasClients = true;

			if (message.MetaData.IsGarantied)
			{
				if (!message.MetaData.SentGarantied)
					garantiedMessageHandler.RecievedGarantied(message);

				if (message.MetaData.SentGarantied)
				{
					message.MetaData.SentGarantied = false;

					Send(&message, 8, recieveEndpoint);
				}

				message.MetaData.IsGarantied = false;
			}

			for (auto& endpoint : endpoints)
			{
				if (recieveEndpoint.port() == endpoint.port())
					continue;

				Send(&message, message.MetaData.dataSize, endpoint);
			}

			StartRecieve();
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

		void Send(const NetMessage& message, const udp::endpoint& endpoint)
		{
			Send(&message, message.MetaData.dataSize, endpoint);
		}

		void Send(const NetMessage& message, const udp::endpoint& endpoint, const std::function<void()>& aLambdaToRunAfterRecieve)
		{
			garantiedMessageHandler.Enqueue(message, endpoint, aLambdaToRunAfterRecieve);
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

		asio::io_context& myIOContext;
	};
}