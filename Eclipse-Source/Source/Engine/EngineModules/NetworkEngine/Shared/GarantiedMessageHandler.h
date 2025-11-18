#pragma once

#include <thread>
#include <mutex>

#include "Message.h"
//#include "MessageQueue.h"

#include <unordered_map>

namespace Eclipse
{
	class Client;
	class GarantiedMessageHandler
	{
	public:
		GarantiedMessageHandler(Client* aClientReference) : ClientReference(aClientReference)
		{

		}

		~GarantiedMessageHandler()
		{

		}

		void Update();
		void Enqueue(const Message& message);
		void RecievedGarantied(const Message& aMessage);

		void UpdateDeltaTime(float deltaTime)
		{
			DeltaTime = deltaTime;
		}

	private:

		std::mutex mapChangeMutex;

		float TimeBetweenTryAgains = 0.1f;

		Client* ClientReference;

		//Temporary
		float DeltaTime = 0.f;

	public:
		struct GarantiedMessage
		{
			GarantiedMessage(const Message& aMessage)
			{
				memcpy(&message, &aMessage, 512);
			}

			float TryAgainTimer = 0;
			Message message;
		};

		//MessageQueue GarantiedMsgs;
		std::unordered_map<unsigned, GarantiedMessage> GarantiedMsgs;

		int toatlFailed;
	};
}