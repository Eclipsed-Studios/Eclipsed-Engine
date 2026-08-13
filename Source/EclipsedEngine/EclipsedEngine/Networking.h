#pragma once

#ifdef ECLIPSED_NETWORKING
	#define SHUT_DOWN_NETWORK_ENGINE() \
		Replication::ReplicationManager::CloseConnection("Disconnect : Quit Game");
#else
	#define SHUT_DOWN_NETWORK_ENGINE() 
#endif