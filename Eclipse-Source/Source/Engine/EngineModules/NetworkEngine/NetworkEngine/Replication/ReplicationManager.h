#pragma once

#include <unordered_map>

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

        static inline std::unordered_map<unsigned, ReplicatedVariable*> ReplicatedVariableList;

        static inline Client* client = nullptr;
        static inline Server* server = nullptr;

        static inline bool startServer = false;
        static inline bool startClient = true;

        static inline bool startedGame = false;
    private:
    };
}