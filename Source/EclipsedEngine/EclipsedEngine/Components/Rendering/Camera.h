#pragma once

#include "EclipsedEngine/Components/Component.h"

#include "EclipsedEngine/Graphics/Buffers/CameraBuffer.h"

namespace Eclipse
{
    class Camera : public Component
    {
        COMPONENT_BASE_2(Camera, 100)

    public:
        void OnDestroy() override;

        void OnComponentAdded() override;
        void EditorUpdate() override;
        void OnDrawGizmos() override;

        void UpdateCameraTransform();

        SERIALIZED_FIELD_DEFAULT(float, CameraZoom, 1.f);

        static inline class Camera* main;
        bool created;

        static inline bool drawCameraGizmos = false;

        CameraBuffer myCameraBuffer;
    };
}