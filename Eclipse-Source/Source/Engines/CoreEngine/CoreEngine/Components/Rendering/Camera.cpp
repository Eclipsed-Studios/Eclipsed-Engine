#include "Camera.h"

#include "GraphicsEngine/OpenGL/OpenGLGraphicsAPI.h"

#include "ECS/ComponentManager.h"

#include "Components/Transform2D.h"

#include "Input/InputMapper.h"
#include "Input/Input.h"

#include "GraphicsEngine/OpenGL/DebugDrawers/DebugDrawer.h"

namespace Eclipse
{
    COMPONENT_REGISTRATION(Camera);

    void Camera::OnDestroy()
    {
        if (main == this)
            main = nullptr;
    }

    void Camera::OnComponentAdded()
    {
        OnSceneLoaded();
    }

    void Camera::OnSceneLoaded()
    {
        if (!created)
        {
            main = this;

            gameObject->transform->AddFunctionToRunOnDirtyUpdate([&]() {
                if (Camera::main != this)
                    return;

                GraphicsEngine::UpdateGlobalUniform(UniformType::Vector2f, "cameraPosition", gameObject->transform->GetPositionPtr());
                GraphicsEngine::UpdateGlobalUniform(UniformType::Float, "cameraRotation", gameObject->transform->GetRotationPtr());
                GraphicsEngine::UpdateGlobalUniform(UniformType::Vector2f, "cameraScale", gameObject->transform->GetScalePtr());
                });

            created = true;
        }
    }

    void Camera::Render()
    {
        if (drawCameraGizmos)
        {
            float size = TemporarySettingsSingleton::Get().resolutionRatioGameView;

            Math::Vector2f sqrPosition = gameObject->transform->GetPosition() * 0.5f + Math::Vector2f(0.5f, 0.5f);
            float sqrRotation = gameObject->transform->GetRotation();
            Math::Vector2f sqrSize = Math::Vector2f(0.5f * size + 0.001f, 0.5f + 0.001f);

            DebugDrawer::DrawSquare(sqrPosition, sqrRotation, sqrSize, Math::Color(0.9f, 0.9f, 0.9f, 1.f));
        }
    }
}