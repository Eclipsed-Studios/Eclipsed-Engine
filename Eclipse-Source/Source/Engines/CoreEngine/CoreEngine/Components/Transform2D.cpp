#include "Transform2D.h"

#include "ImGui/ImGui/imgui.h"
#include "TemporarySettingsSingleton.h"

#include <sstream>

namespace Eclipse
{
    void Transform2D::OnComponentAdded()
    {
        gameObject->transform = this;
    }

    const Math::Vector2f& Transform2D::GetPosition() const
    {
        return position;
    }
    const float Transform2D::GetRotation() const
    {
        return rotation;
    }
    const Math::Vector2f& Transform2D::GetScale() const
    {
        return scale;
    }

    Math::Vector2f* Transform2D::GetPositionPtr()
    {
        return &position.Get();
    }
    float* Transform2D::GetRotationPtr()
    {
        return &rotation.Get();
    }
    Math::Vector2f* Transform2D::GetScalePtr()
    {
        return &scale.Get();
    }

    void Transform2D::SetPosition(const Math::Vector2f& aPosition)
    {
        SetPosition(aPosition.x, aPosition.y);
    }
    void Transform2D::SetPosition(float aX, float aY)
    {
        position->x = aX;
        position->y = aY;

        myIsDirty = true;
    }

    void Transform2D::SetRotation(float aRotation)
    {
        rotation = aRotation;

        myIsDirty = true;
    }

    void Transform2D::SetScale(const Math::Vector2i& aScale)
    {
        SetScale(static_cast<float>(aScale.x), static_cast<float>(aScale.y));
    }
    void Transform2D::SetScale(const Math::Vector2f& aScale)
    {
        SetScale(aScale.x, aScale.y);
    }
    void Transform2D::SetScale(float aX, float aY)
    {
        scale->x = aX;
        scale->y = aY;

        myIsDirty = true;
    }

    void Transform2D::AddFunctionToRunOnDirtyUpdate(const std::function<void()>& aFunction)
    {
        myFunctionsToRunOnDirtyUpdate.push_back(aFunction);
    }

    void Transform2D::EditorUpdate()
    {
        if (myIsDirty)
        {
            for (auto& func : myFunctionsToRunOnDirtyUpdate)
                func();

            myIsDirty = false;
        }
    }
}