#include "Camera.h"

#include "OpenGL/OpenGLGraphicsAPI.h"

#include "ECS/ComponentManager.h"

#include "Components/Transform2D.h"

#include "Timer.h"

#include "Input/InputMapper.h"
#include "Input/Input.h"

namespace Eclipse
{
    void Camera::Awake()
    {
        myTransform = GetComp(Transform2D, gameObject);

        myTransform->AddFunctionToRunOnDirtyUpdate([&]() {
            GraphicsEngine::UpdateGlobalUniform(UniformType::Vector2f, "cameraPosition", myTransform->GetPositionPtr());
            GraphicsEngine::UpdateGlobalUniform(UniformType::Float, "cameraRotation", myTransform->GetRotationPtr());
            GraphicsEngine::UpdateGlobalUniform(UniformType::Vector2f, "cameraScale", myTransform->GetScalePtr());
            });
    }

    void Camera::DrawInspector()
    {
    }
}