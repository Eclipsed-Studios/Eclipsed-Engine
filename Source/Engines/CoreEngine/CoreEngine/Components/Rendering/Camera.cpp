#include "Camera.h"

#include "OpenGL/OpenGLGraphicsAPI.h"

#include "ECS/ComponentManager.h"

#include "Components/Transform2D.h"

#include "Timer.h"

#include "Input/InputMapper.h"
#include "Input/Input.h"

namespace ENGINE_NAMESPACE
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

    void Camera::Update()
    {
        myTransform->SetPosition(GetComp(Transform2D, 1)->GetPosition());

        float back = -Time::GetDeltaTime() * static_cast<float>(Input::GetKey(Keycode::S));
        float forward = Time::GetDeltaTime() * static_cast<float>(Input::GetKey(Keycode::W));

        myTransform->SetScale(myTransform->GetScale() + Math::Vector2f(forward + back, forward + back));

        float backRot = -Time::GetDeltaTime() * static_cast<float>(Input::GetKey(Keycode::Q));
        float forwardRot = Time::GetDeltaTime() * static_cast<float>(Input::GetKey(Keycode::E));

        myTransform->SetRotation(myTransform->GetRotation() + forwardRot + backRot);
    }
}