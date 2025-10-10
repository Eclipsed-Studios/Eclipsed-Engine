#include "Camera.h"

#include "OpenGL/OpenGLGraphicsAPI.h"

#include "ECS/ComponentManager.h"

#include "Components/Transform2D.h"

#include "Input/InputMapper.h"
#include "Input/Input.h"

#include "OpenGL/DebugDrawers/DebugDrawer.h"

namespace Eclipse
{
    void Camera::OnDestroy()
    {
        if (main == this)
            main = nullptr;
    }

    void Camera::OnSceneLoaded()
    {
        main = this;

        gameObject->transform->AddFunctionToRunOnDirtyUpdate([&]() {
            if (Camera::main != this)
                return;

            GraphicsEngine::UpdateGlobalUniform(UniformType::Vector2f, "cameraPosition", gameObject->transform->GetPositionPtr());
            GraphicsEngine::UpdateGlobalUniform(UniformType::Float, "cameraRotation", gameObject->transform->GetRotationPtr());
            GraphicsEngine::UpdateGlobalUniform(UniformType::Vector2f, "cameraScale", gameObject->transform->GetScalePtr());
            });
    }

    void Camera::Render()
    {
        float size = TemporarySettingsSingleton::Get().resolutionRatioGameView;

        DebugDrawer::DrawSquare(gameObject->transform->GetPosition() * 0.5f + Math::Vector2f(0.5f, 0.5f), gameObject->transform->GetRotation(), Math::Vector2f(0.5f * size + 0.001f, 0.5f + 0.001f), Math::Color(0.9f, 0.9f, 0.9f, 1.f));
    }
}