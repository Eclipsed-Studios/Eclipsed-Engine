#include "Transform2D.h"

#include "ImGui/ImGui/imgui.h"

#include <sstream>

namespace Eclipse
{
    COMPONENT_REGISTRATION(Transform2D);

    void Transform2D::DrawInspector()
    {
        auto globalPosition = GetPosition();

        ImGui::Text("Debug properties");
        ImGui::Text("gobal pos, x: %f, y: %f", globalPosition.x, globalPosition.y);
    }

    void Transform2D::OnSceneLoaded()
    {
        gameObject->transform = this;
    }
    void Transform2D::OnComponentAdded()
    {
        gameObject->transform = this;
    }

    void Transform2D::AddParentTransform(GameObject* aParent, Math::Vector2f& aPosition) const
    {
        Transform2D* parentTransform = aParent->GetComponent<Transform2D>();
        if (!parentTransform)
            return;

        aPosition += parentTransform->GetLocalPosition();

        GameObject* parent = aParent->GetParent();
        if (parent) 
            AddParentTransform(parent, aPosition);
    }

    Math::Vector2f Transform2D::GetPosition() const
    {
        Math::Vector2f newPosition = position;
        GameObject* parent = gameObject->GetParent();
        if (parent)
            AddParentTransform(parent, newPosition);

        return newPosition;
    }
    float Transform2D::GetRotation() const
    {
        return rotation;
    }
    Math::Vector2f Transform2D::GetScale() const
    {
        return scale;
    }

    const Math::Vector2f& Transform2D::GetLocalPosition() const
    {
        return position;
    }
    const float Transform2D::GetLocalRotation() const
    {
        return rotation;
    }
    const Math::Vector2f& Transform2D::GetLocalScale() const
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

        lastPosition = position;

        myIsDirty = true;
    }

    void Transform2D::SetRotation(float aRotation)
    {
        rotation = aRotation;

        lastRotation = rotation;

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

        lastScale = scale;

        myIsDirty = true;
    }

    void Transform2D::AddFunctionToRunOnDirtyUpdate(const std::function<void()>& aFunction)
    {
        myFunctionsToRunOnDirtyUpdate.push_back(aFunction);
    }

    void Transform2D::EditorUpdate()
    {
        if (position->x != lastPosition.x || position->y != lastPosition.y)
            myIsDirty = true;
        if (scale->x != lastScale.x || scale->y != lastScale.y)
            myIsDirty = true;
        if (lastRotation != rotation)
            myIsDirty = true;


        if (myIsDirty)
        {
            for (auto& func : myFunctionsToRunOnDirtyUpdate)
                func();

            myIsDirty = false;
        }
    }
}