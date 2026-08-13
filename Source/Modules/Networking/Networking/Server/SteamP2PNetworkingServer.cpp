#include "Server/SteamP2PNetworkingServer.h"

#include "steamsdk/isteamnetworkingsockets.h"
#include "steamsdk/isteamgameserver.h"
#include "steamsdk/isteamnetworkingutils.h"

#include <iostream>

namespace Eclipse
{
	SteamP2PNetworkingServer::SteamP2PNetworkingServer(const std::function<void(const NetMessage& aNetMessage)>& aHandleRecieve)
		: myConnection(0), myListenSocket(0), HandleRecieve(aHandleRecieve)
	{
	}

	void SteamP2PNetworkingServer::CloseConnection(const char* aReason)
	{
		SteamNetworkingSockets()->CloseConnection(myConnection, 1, aReason, true);
		SteamNetworkingSockets()->CloseListenSocket(myListenSocket);
	}

	void SteamP2PNetworkingServer::Send(NetMessage& message)
	{
		EMessageType messageType;
		if (message.MetaData.IsGarantied)
			messageType = EMessageType::Garantied;
		else
			messageType = EMessageType::NotGarantied;

		int64 messageCount;
		EResult result = SteamNetworkingSockets()->SendMessageToConnection(myConnection, &message, message.MetaData.dataSize, messageType, &messageCount);

		SteamNetworkingSockets()->FlushMessagesOnConnection(myConnection);
	}

	void SteamP2PNetworkingServer::Start()
	{
		SteamNetworkingUtils()->InitRelayNetworkAccess();

		myListenSocket = SteamNetworkingSockets()->CreateListenSocketP2P(0, 0, nullptr);
	}

	void SteamP2PNetworkingServer::Update()
	{
		if (!myConnection)
			return;

		SteamNetworkingMessage_t* receivedMessages[256];
		int messageCount = SteamNetworkingSockets()->ReceiveMessagesOnConnection(myConnection, receivedMessages, 256);

		if (messageCount < 0)
			return;

		for (int i = 0; i < messageCount; ++i)
		{
			SteamNetworkingMessage_t* msg = receivedMessages[i];

			NetMessage message;
			memcpy(&message, msg->GetData(), msg->m_cbSize);

			msg->Release();

			HandleRecieve(message);
		}
	}

	void SteamP2PNetworkingServer::OnSteamConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t* info)
	{
		switch (info->m_info.m_eState)
		{
		case k_ESteamNetworkingConnectionState_Connecting:
			SteamNetworkingSockets()->AcceptConnection(info->m_hConn);
			break;

		case k_ESteamNetworkingConnectionState_Connected: // Fix replication
			//Replication::ReplicationManager::SteamNetorkingReady();
			break;

		case k_ESteamNetworkingConnectionState_ProblemDetectedLocally:
			// Log the reason code for debugging
			printf("Connection failed with reason: %d - %s\n",
				info->m_info.m_eEndReason,
				info->m_info.m_szEndDebug);
			break;
		}

		myConnection = info->m_hConn;
	}

}