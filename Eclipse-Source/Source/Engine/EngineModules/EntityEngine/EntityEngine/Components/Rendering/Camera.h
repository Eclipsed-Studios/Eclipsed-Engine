#pragma once

#include "EntityEngine/Components/Base/BaseComponent.h"

#include "Utilities/Math/Math.h"
#include "EntityEngine/ComponentManager.h"

namespace Eclipse
{
    class Camera : public Component
    {
        COMPONENT_BASE_2(Camera, 100)

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
