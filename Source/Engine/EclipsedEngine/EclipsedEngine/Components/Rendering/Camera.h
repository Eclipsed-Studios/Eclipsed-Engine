#pragma once

#include "EclipsedEngine/Components/Component.h"

#include "CoreEngine/GraphicsBuffers/CameraBuffer.h"

#include "CoreEngine/UtilityMacros.h"

ECLIPSED_CLASS;

namespace Eclipse
{
    class Camera : public Component
    {
        COMPONENT_BASE_2(Camera, 100)

    public:
        FRIEND_REFLECTION(Camera);

    public:
        void OnDestroy() override;

        void OnComponentAdded() override;
        void EditorUpdate() override;
        void OnDrawGizmos() override;

        void UpdateCameraTransform();

        float CameraZoom = 1.f;

        static inline class Camera* main;
        bool created;

        static inline bool drawCameraGizmos = false;

        CameraBuffer myCameraBuffer;

    };
}
