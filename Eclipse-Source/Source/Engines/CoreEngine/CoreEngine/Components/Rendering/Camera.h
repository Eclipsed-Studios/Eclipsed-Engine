#pragma once

#include "Components/Base/BaseComponent.h"

#include "Math/Math.h"
#include "ECS/ComponentManager.h"

namespace Eclipse
{
    class Camera : public Component
    {
        BASE_SELECTION(Camera, 100)

    public:
        void OnDestroy() override;

        void OnComponentAdded() override;
        void OnSceneLoaded() override;
        void Render() override;

        static inline class Camera* main;

        bool created;
    };
}
