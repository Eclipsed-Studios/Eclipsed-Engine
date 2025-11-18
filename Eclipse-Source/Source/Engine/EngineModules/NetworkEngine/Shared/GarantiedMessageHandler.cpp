#include "GarantiedMessageHandler.h"

#include "Client.h"

namespace Eclipse
{
	void GarantiedMessageHandler::Update()
	{
		for (auto& [networkID, message] : GarantiedMsgs)
		{
			float& TryAgainTimer = message.TryAgainTimer;

			TryAgainTimer -= DeltaTime;

			if (TryAgainTimer > 0.f)
				continue;

			ClientReference->SendDirectly_NoChecks(message.message);

			TryAgainTimer = TimeBetweenTryAgains;
		}
	}

	void GarantiedMessageHandler::Enqueue(const Message& message)
	{
		Message cpyMessage;
		std::memcpy(&cpyMessage, &message, message.MetaData.dataSize);

		mapChangeMutex.lock();
		GarantiedMsgs.emplace(message.MetaData.messageID, GarantiedMessage(message));
		mapChangeMutex.unlock();
	}

	void GarantiedMessageHandler::RecievedGarantied(const Message& aMessage)
	{
		if (aMessage.MetaData.SentGarantied)
			return;
		if (GarantiedMsgs.empty())
			return;


		mapChangeMutex.lock();
		GarantiedMsgs.erase(aMessage.MetaData.messageID);
		mapChangeMutex.unlock();

		static int amount = -1;

		amount++;
		std::cout << amount << std::endl;
	}
}