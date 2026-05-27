#pragma once

#ifdef ECLIPSED_NETWORKING

namespace Eclipse
{
    namespace Reflection
    {
        class AbstractSerializedVariable;
    }

    class Component;
    namespace Replication
    {
        class BaseReplicatedVariable
        {
        public:
            void* Data;
            int DataCount;
            bool ManualVariableSending;
            unsigned IterationID;

            Component* OnComponent;

            BaseReplicatedVariable(void* aData, int aDataCount, Component* aComponent, bool anAutomatic) : Data(aData), DataCount(aDataCount), OnComponent(aComponent), ManualVariableSending(!anAutomatic)
            {

            }

            void ReplicateThis(unsigned aID, bool aIsGarantied = false, bool aAlwaysSend = false);
        };

        template<typename T>
        class ReplicatedVariable : public BaseReplicatedVariable
        {
        public:
            inline ReplicatedVariable(void* aData, int aDataCount, Component* aComponent, bool anAutomatic, void(T::* aOnRepFunction)());

        public:
            void(T::* OnRepFunction)();
        };
    }

}

#include "ReplicatedVariable.inl"

#endif