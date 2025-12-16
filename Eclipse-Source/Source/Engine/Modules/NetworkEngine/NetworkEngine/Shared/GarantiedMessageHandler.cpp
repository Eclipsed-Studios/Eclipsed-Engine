//#include "GarantiedMessageHandler.h"
//
//#include "NetworkEngine/Client/Client.h"
//
//#include "Utilities/Common/MainSingleton.h"
//
//#include <iostream>
//
//namespace Eclipse
//{
//	template <class T>
//	void GarantiedMessageHandler<T>::Update()
//	{
//		for (std::pair<unsigned, GarantiedMessage> garantiedMessage : GarantiedMsgs)
//		{
//			GarantiedMessage message = garantiedMessage.second;
//
//			float& TryAgainTimer = message.TryAgainTimer;
//
//			TryAgainTimer -= DeltaTime;
//
//			if (TryAgainTimer > 0.f)
//				continue;
//			
//			if (message.message.MetaData.Type == Msg_AddComponent)
//			{
//				std::cout << "componeb"  << std::endl;
//			}
//			
//
//			(FunctionOwner->*SendDirectlyFunc)(message.message, message.endpoint);
//
//			TryAgainTimer = TimeBetweenTryAgains;
//		}
//	}
//
//	template <class T>
//	void GarantiedMessageHandler<T>::Enqueue(const NetMessage& message, const udp::endpoint& anEndpoint)
//	{
//		NetMessage cpyMessage;
//		std::memcpy(&cpyMessage, &message, message.MetaData.dataSize);
//
//		GarantiedMessage grntMessage(message, anEndpoint);
//
//		grntMessage.TimeAtFirstSend = Time::GetTotalTime();
//		
//		mapChangeMutex.lock();
//		GarantiedMsgs.emplace(message.MetaData.messageID, grntMessage);
//		mapChangeMutex.unlock();
//	}
//
//	template <class T>
//	void GarantiedMessageHandler<T>::Enqueue(const NetMessage& message, const udp::endpoint& anEndpoint, const std::function<void()>& aLambdaFunctionToRunOnRecieve)
//	{
//		NetMessage cpyMessage;
//		std::memcpy(&cpyMessage, &message, message.MetaData.dataSize);
//
//		GarantiedMessage grntMessage(message, anEndpoint, aLambdaFunctionToRunOnRecieve);
//
//		grntMessage.TimeAtFirstSend = Time::GetTotalTime();
//		
//		mapChangeMutex.lock();
//		GarantiedMsgs.emplace(message.MetaData.messageID, grntMessage);
//		mapChangeMutex.unlock();
//	}
//
//	template <class T>
//	void GarantiedMessageHandler<T>::RecievedGarantied(const NetMessage& aMessage)
//	{
//		if (aMessage.MetaData.SentGarantied)
//			return;
//		if (GarantiedMsgs.empty())
//			return;
//		if (GarantiedMsgs.find(aMessage.MetaData.messageID) == GarantiedMsgs.end())
//			return;
//		
//		auto& garantiedMessage = GarantiedMsgs.at(aMessage.MetaData.messageID);
//
//		float currenttime = Time::GetTotalTime();
//		float secondsPing = currenttime - garantiedMessage.TimeAtFirstSend;
//
//		TemporarySettingsSingleton::Get().ping = (int)(secondsPing * 1000.f);
//		
//		if (garantiedMessage.HasLambda)
//		{
//			garantiedMessage.LambdaToRunOnRecieve();
//		}
//		
//
//		mapChangeMutex.lock();
//		GarantiedMsgs.erase(aMessage.MetaData.messageID);
//		mapChangeMutex.unlock();
//	}
//}