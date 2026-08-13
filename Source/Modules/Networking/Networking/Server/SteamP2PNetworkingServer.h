#pragma once

#include <functional>

#include "Networking/Shared/Message.h"

#include "steamsdk/isteamnetworkingsockets.h"
#include "steamsdk/isteamgameserver.h"
#include "steamsdk/isteamnetworkingutils.h"

//#include "EclipsedEngine/Replication/ReplicationManager.h"
// Add repliocation here

#include "Networking.Core.hpp"

namespace Eclipse
{
    class NETWORKING_API SteamP2PNetworkingServer
    {
    public:
        SteamP2PNetworkingServer(const std::function<void(const NetMessage& aNetMessage)>& aHandleRecieve);

        void CloseConnection(const char* aReason);

        void Send(NetMessage& message);

        void Start();

        void Update();

    public:
        std::function<void(const NetMessage& aNetMessage)> HandleRecieve;

        HSteamListenSocket myListenSocket;
        HSteamNetConnection myConnection;

        STEAM_CALLBACK(SteamP2PNetworkingServer, OnSteamConnectionStatusChanged, SteamNetConnectionStatusChangedCallback_t);
    };
}
