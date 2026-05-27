#pragma once

#ifdef ECLIPSED_NETWORKING
	#define SHUT_DOWN_NETWORK_ENGINE() \
		if (MainSingleton::Exists<SteamP2PNetworkingServer>()) \
		{ \
			auto& server = MainSingleton::GetInstance<SteamP2PNetworkingServer>(); \
			server.ShutDown(); \
		} \
		if (MainSingleton::Exists<SteamP2PNetworkingClient>()) \
		{ \
			auto& client = MainSingleton::GetInstance<SteamP2PNetworkingClient>(); \
			client.ShutDown(); \
		}
#else
	#define SHUT_DOWN_NETWORK_ENGINE() 
#endif