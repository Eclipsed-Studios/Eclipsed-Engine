#pragma once

#include <vector>

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

        static void Init();
        static void Update();

        static inline std::vector<ReplicatedVariable*> ReplicatedVariableList;

        static inline Client* client = nullptr;
        static inline Server* server = nullptr;
    private:
    };
}