#include "Transform2D.h"

#include "ImGui/ImGui/imgui.h"
#include "TemporarySettingsSingleton.h"

#include <sstream>

namespace ENGINE_NAMESPACE
{
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
        return &position;
    }
    float* Transform2D::GetRotationPtr()
    {
        return &rotation;
    }
    Math::Vector2f* Transform2D::GetScalePtr()
    {
        return &scale;
    }

    void Transform2D::SetPosition(const Math::Vector2f& aPosition)
    {
        SetPosition(aPosition.x, aPosition.y);
    }
    void Transform2D::SetPosition(float aX, float aY)
    {
        position.x = aX;
        position.y = aY;

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
        scale.x = aX;
        scale.y = aY;

        myIsDirty = true;
    }

    void Transform2D::AddFunctionToRunOnDirtyUpdate(const std::function<void()>& aFunction)
    {
        myFunctionsToRunOnDirtyUpdate.push_back(aFunction);
    }

    void Transform2D::DrawInspector()
    {
        std::stringstream ss;
        ss << "##" << this;

        { // Position
            ImGui::Text("Position");
            ImGui::SameLine();
            if (ImGui::DragFloat2(("##Position" + ss.str()).c_str(), &position.x, 0.001f))
            {
                myIsDirty = true;
            }
        }

        { // Scale
            ImGui::Text("Scale");
            ImGui::SameLine();
            if (ImGui::DragFloat2(("##Scale" + ss.str()).c_str(), &scale.x, 0.1f))
            {
                myIsDirty = true;
            }
        }

        { // Rotation
            float rot = rotation * (180.f / 3.1415f);
            ImGui::Text("Rotation");
            ImGui::SameLine();
            if (ImGui::DragFloat(("##Rotation" + ss.str()).c_str(), &rot, 0.01f))
            {
                myIsDirty = true;
                rotation = rot * (3.1415f / 180.f);
            }
        }
    }

    void Transform2D::Update()
    {
        if (myIsDirty)
        {
            for (auto& func : myFunctionsToRunOnDirtyUpdate)
                func();

            myIsDirty = false;
        }
    }

    rapidjson::Value Transform2D::Save(rapidjson::Document::AllocatorType& allocator) const
    {
        rapidjson::Value obj = Component::Save(allocator);

        obj.AddMember("position", GetPosition().Save(allocator), allocator);
        obj.AddMember("rotation", GetRotation(), allocator);
        obj.AddMember("scale", GetScale().Save(allocator), allocator);

        return obj;
    }

    void Transform2D::Load(const rapidjson::Value& aValue)
    {
    }
}