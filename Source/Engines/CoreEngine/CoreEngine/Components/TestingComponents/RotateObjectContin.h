#pragma once

#include "../Component.h"
#include "../Transform2D.h"

#include "../../ECS/ComponentManager.h"

#include "Timer.h"

namespace ENGINE_NAMESPACE
{
    class RotateObjectContin : public Component
    {
    public:
        RotateObjectContin() = default;
        ~RotateObjectContin() = default;

        void Update() override
        {
            Transform2D *transform = ComponentManager::GetComponent<Transform2D>(gameObject);

            transform->SetPosition({0, 0});
        }
    };
}