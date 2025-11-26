#include "GarantiedMessageHandler.h"

#include "NetworkEngine/Client/Client.h"

namespace Eclipse
{
	template <class T>
	void GarantiedMessageHandler<T>::Update()
	{
		for (std::pair<unsigned, GarantiedMessage> garantiedMessage : GarantiedMsgs)
		{
			GarantiedMessage message = garantiedMessage.second;

			float& TryAgainTimer = message.TryAgainTimer;

			TryAgainTimer -= DeltaTime;

			if (TryAgainTimer > 0.f)
				continue;

			(FunctionOwner->*SendDirectlyFunc)(message.message, message.endpoint);

			TryAgainTimer = TimeBetweenTryAgains;
		}
	}

	template <class T>
	void GarantiedMessageHandler<T>::Enqueue(const NetMessage& message, const udp::endpoint& anEndpoint)
	{
		NetMessage cpyMessage;
		std::memcpy(&cpyMessage, &message, message.MetaData.dataSize);

		mapChangeMutex.lock();
		GarantiedMsgs.emplace(message.MetaData.messageID, GarantiedMessage(message, anEndpoint));
		mapChangeMutex.unlock();
	}

	template <class T>
	void GarantiedMessageHandler<T>::RecievedGarantied(const NetMessage& aMessage)
	{
		if (aMessage.MetaData.SentGarantied)
			return;
		if (GarantiedMsgs.empty())
			return;


		mapChangeMutex.lock();
		GarantiedMsgs.erase(aMessage.MetaData.messageID);
		mapChangeMutex.unlock();
	}
}