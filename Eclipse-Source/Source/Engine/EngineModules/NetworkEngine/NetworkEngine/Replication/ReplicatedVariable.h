#pragma once

#include <string>

namespace Eclipse
{
    class Component;
    namespace Replication
    {
        class ReplicatedVariable
        {
        public:
            inline ReplicatedVariable(std::string aName, Component* aComponent, bool anAutomatic, unsigned ID, void(Component::* anOnRepFunction)());
            inline void ReplicateThis(unsigned aID);

        public:
            Component* ConnectedComponent;

            void* myVariableAddress;
            bool ManualVariableSending;
            int dataAmount;
        
            void(Component::* OnRepFunction)();
        };
    }

}

#include "ReplicatedVariable.inl"