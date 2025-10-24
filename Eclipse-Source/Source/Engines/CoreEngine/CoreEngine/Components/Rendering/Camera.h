#pragma once

#include "CoreEngine/Components/Base/BaseComponent.h"

#include "Utilities/Math/Math.h"
#include "CoreEngine/ECS/ComponentManager.h"

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

        static inline bool drawCameraGizmos = false;
    };
}
