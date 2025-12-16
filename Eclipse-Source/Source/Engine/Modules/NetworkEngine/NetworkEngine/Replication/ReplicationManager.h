//#pragma once
//
//#include <unordered_map>
//
//#include "asio/asio/asio.hpp"
//
//#include "../shared/Message.h"
//
//namespace Eclipse
//{
//    class Client;
//    class Server;
//    class GameObject;
//}
//
//namespace Eclipse::Replication
//{
//    class BaseReplicatedVariable;
//
//    class ReplicationManager
//    {
//    public:
//        friend class BaseReplicatedVariable;
//
//        ReplicationManager() = default;
//        ~ReplicationManager() = default;
//
//        static void ReplicatedOnPlay();
//
//        static void ReplicateVariable(unsigned aID);
//
//        static void CreateServer();
//        static void CreateClient();
//
//        static void Start();
//        static void Update();
//
//        static void CreateComponentMessage(Eclipse::Component* aComponent, NetMessage& outMessage);
//
//        static void EmplaceReplicatedVariable(unsigned ID, BaseReplicatedVariable* ReplicatedVariable) { ReplicatedVariabpePtr->emplace(ID, ReplicatedVariable); }
//
//    public:
//        static inline std::unordered_map<unsigned, BaseReplicatedVariable*> PossibleReplicatedVariableList;
//        static inline std::unordered_map<unsigned, BaseReplicatedVariable*> RealReplicatedVariableList;
//
//        static inline std::unordered_map<unsigned, BaseReplicatedVariable*>* ReplicatedVariabpePtr = &PossibleReplicatedVariableList;
//
//        static inline Client* client = nullptr;
//        static inline Server* server = nullptr;
//
//        static inline bool startServer = false;
//        static inline bool startClient = true;
//
//        static inline bool startedGame = false;
//
//        static inline asio::io_context ioContext;
//    private:
//    };
//}