#include "Camera.h"

#include "OpenGL/OpenGLGraphicsAPI.h"

#include "ECS/ComponentManager.h"

#include "Components/Transform2D.h"

#include "Timer.h"

#include "Input/InputMapper.h"
#include "Input/Input.h"

#include "OpenGL/DebugDrawers/DebugDrawer.h"

namespace Eclipse
{
    void Camera::OnDestroy()
    {
        if (main == this)
        {
            main = nullptr;
        }
    }

    void Camera::Awake()
    {
        main = this;
        myTransform = gameObject->GetComponent<Transform2D>();

        myTransform->AddFunctionToRunOnDirtyUpdate([&]() {
            if (main == this)
            {
                GraphicsEngine::UpdateGlobalUniform(UniformType::Vector2f, "cameraPosition", myTransform->GetPositionPtr());
                GraphicsEngine::UpdateGlobalUniform(UniformType::Float, "cameraRotation", myTransform->GetRotationPtr());
                GraphicsEngine::UpdateGlobalUniform(UniformType::Vector2f, "cameraScale", myTransform->GetScalePtr());
            }
            });
    }

    void Camera::Render()
    {
        float size = TemporarySettingsSingleton::Get().resolutionRatioGameView;

        DebugDrawer::DrawSquare(myTransform->GetPosition() * 0.5f + Math::Vector2f(0.5f, 0.5f), Math::Vector2f(0.5f * size, 0.5f));
    }
}