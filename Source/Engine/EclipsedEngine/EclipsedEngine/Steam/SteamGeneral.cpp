#include "SteamGeneral.h"

#include "Replication/ReplicationManager.h"

#include <iostream>
#include <cassert>

namespace Eclipse
{
    
    void SteamGeneral::RelayNetworkInitilized(SteamRelayNetworkStatus_t* aCallback)
    {
        std::cout << "Steam networking Ready" << std::endl;
    }
    
    void SteamGeneral::FriendClickedJoinedGame(GameRichPresenceJoinRequested_t* aCallback)
    {
        OthersteamID = aCallback->m_steamIDFriend;
#ifdef ECLIPSED_NETWORKING
        Replication::ReplicationManager::Start(true);
#endif 

        //SceneManager::LoadScene(1);
    }

    bool SteamGeneral::SetRichPresence( const char *pchKey, const char *pchValue)
    {
        return SteamFriends()->SetRichPresence(pchKey, pchValue);
    }

    void SteamGeneral::Update() 
    {        
        SteamAPI_RunCallbacks();
    }
    
    void SteamGeneral::Init()
    {
        SteamErrMsg error;
        if (SteamAPI_InitEx(&error) != k_ESteamAPIInitResult_OK)
        {
            printf("SteamAPI Init failed: %s\n", error);
            assert(false && "Steam initialization failed");
            return;
        }
    }

    void SteamGeneral::ShutDown()
    {
        SteamFriends()->ClearRichPresence();
        SteamAPI_Shutdown();
    }
}
