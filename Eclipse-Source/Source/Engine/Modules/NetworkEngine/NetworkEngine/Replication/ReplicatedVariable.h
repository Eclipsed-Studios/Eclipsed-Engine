//#pragma once
//
//#include <string>
//
//namespace Eclipse
//{
//    class Component;
//    namespace Replication
//    {
//
//        class BaseReplicatedVariable
//        {
//        public:
//            void* myVariableAddress;
//            bool ManualVariableSending;
//            int dataAmount;
//
//            inline void ReplicateThis(unsigned aID);
//
//            Component* ConnectedComponent;
//        };
//
//        template<typename T>
//        class ReplicatedVariable : public BaseReplicatedVariable
//        {
//        public:
//            inline ReplicatedVariable(std::string aName, Component* aComponent, bool anAutomatic, unsigned ID, void(T::* OnRepFunctionPtr)());
//            
//
//        public:
//            void(T::* OnRepFunction)();
//        };
//    }
//
//}
//
//#include "ReplicatedVariable.inl"