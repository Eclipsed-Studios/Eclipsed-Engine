#pragma once

#include <string>

#include "EclipsedEngine/Components/Component.h"
#include "EntityEngine/GameObject.h"

namespace Eclipse
{
    class ReplicatedVariable
    {
    public:
        ReplicatedVariable(std::string aName, class Component* aComponent)
        {
                GameObjectReplicationID = aComponent->myInstanceComponentID;
                ReplicationComponentID = aComponent->gameObject->GetID();
                VariableName = aComponent->GetComponentName();
        }

        void REPComponent()
        {

        }

    public:
        int GameObjectReplicationID = 0;
        int ReplicationComponentID = 0;
        std::string VariableName;

        bool ManualVariableSending;
    };
}