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
            inline ReplicatedVariable(std::string aName, Component* aComponent, bool anAutomatic);
            inline void ReplicateThis();

        public:
            void* myVariableAddress;
            bool ManualVariableSending;
            int dataAmount;

            size_t vectorIndex;
        };
    }

}

#include "ReplicatedVariable.inl"