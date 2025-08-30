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

            auto position = transform->GetPosition();
            Math::Vector2f pos = {xVelocity * Time::GetDeltaTime(), yVelocity * Time::GetDeltaTime()};
            transform->SetPosition(position + pos);

            // if (pos.x)
            // {
            //     pos.x >= 1820;
            // }
        }

        float xVelocity = 0.1f;
        float yVelocity = 0.1f;
    };
}