#pragma once

#include <thread>
#include <mutex>

#include "Message.h"
//#include "MessageQueue.h"

#include <unordered_map>

	#include "asio/asio/asio.hpp"


namespace Eclipse
{
	using asio::ip::udp;

	class Client;

	template <class T>
	class GarantiedMessageHandler
	{
	public:
		GarantiedMessageHandler(void (T::*aSendDirectlyFunc)(NetMessage&, const udp::endpoint&), T* owner) : FunctionOwner(owner), SendDirectlyFunc(aSendDirectlyFunc)
		{
			
		}

		~GarantiedMessageHandler()
		{

		}

		void Update();
		void Enqueue(const NetMessage& message);
		void RecievedGarantied(const NetMessage& aMessage);

		void UpdateDeltaTime(float deltaTime)
		{
			DeltaTime = deltaTime;
		}

	private:

		std::mutex mapChangeMutex;

		float TimeBetweenTryAgains = 0.1f;

		T* FunctionOwner;
		void (T::*SendDirectlyFunc)(NetMessage&, const udp::endpoint&);

		//Temporary
		float DeltaTime = 0.f;

	public:
		struct GarantiedMessage
		{
			GarantiedMessage(const NetMessage& aMessage)
			{
				memcpy(&message, &aMessage, 512);
			}

			float TryAgainTimer = 0;
			NetMessage message;
		};

		//MessageQueue GarantiedMsgs;
		std::unordered_map<unsigned, GarantiedMessage> GarantiedMsgs;

		int toatlFailed;
	};
}