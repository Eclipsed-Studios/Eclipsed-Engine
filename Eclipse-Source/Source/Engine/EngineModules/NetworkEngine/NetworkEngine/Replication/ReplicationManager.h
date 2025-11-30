#pragma once

#include <unordered_map>

#include "asio/asio/asio.hpp"

namespace Eclipse
{
    class Client;
    class Server;
}

namespace Eclipse::Replication
{
    class ReplicatedVariable;

    class ReplicationManager
    {
    public:
        friend class ReplicatedVariable;

        ReplicationManager() = default;
        ~ReplicationManager() = default;

        static void ReplicateVariable(unsigned aID);

        static void CreateServer();
        static void CreateClient();

        static void Start();
        static void Update();


        static void CreateNetworkObject(unsigned aID);

        // void ReplicatedVariable::SendCreateObjectCommand(unsigned aObjectID)
        // {
        //     char* data = new char[sizeof(aObjectID) + sizeof(int)];



        //     size_t offset = 0;
        //     memcpy(data + offset, &aObjectID, sizeof(aObjectID));
        //     offset += sizeof(aObjectID);

        //     memcpy(data + offset, &aID, sizeof(aID));
        //     offset += sizeof(aID);

        //     NetMessage message = NetMessage::BuildGameObjectMessage(0, MessageType::Msg_Variable, data, offset, false);

        //     Server& server = Utilities::MainSingleton::GetInstance<Server>();
        //     server.Send(message);
        // }


    public:
        static inline std::unordered_map<unsigned, ReplicatedVariable*> ReplicatedVariableList;

        static inline Client* client = nullptr;
        static inline Server* server = nullptr;

        static inline bool startServer = false;
        static inline bool startClient = true;

        static inline bool startedGame = false;

        static inline asio::io_context ioContext;
    private:
    };
}