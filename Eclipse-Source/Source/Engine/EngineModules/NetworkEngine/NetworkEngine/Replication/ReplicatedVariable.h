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
            inline ReplicatedVariable(std::string aName, Component* aComponent, bool anAutomatic, unsigned ID);
            inline void ReplicateThis(unsigned aID);

        public:
            Component* ConnectedComponent;

            void* myVariableAddress;
            bool ManualVariableSending;
            int dataAmount;
        };
    }

}

#include "ReplicatedVariable.inl"