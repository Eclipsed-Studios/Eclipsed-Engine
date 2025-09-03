#include "Transform2D.h"

#include "TemporarySettingsSingleton.h"

namespace ENGINE_NAMESPACE
{
    const Math::Vector2f &Transform2D::GetPosition() const
    {
        return position;
    }
    const float Transform2D::GetRotation() const
    {
        return rotation;
    }
    const Math::Vector2f &Transform2D::GetScale() const
    {
        return scale;
    }

    void Transform2D::SetPosition(const Math::Vector2f &aPosition)
    {
        SetPosition(aPosition.x, aPosition.y);
    }
    void Transform2D::SetPosition(float aX, float aY)
    {
        position.x = aX;
        position.y = aY;
    }

    void Transform2D::SetRotation(float aRotation)
    {
        rotation = aRotation;
    }

    void Transform2D::SetScale(const Math::Vector2f &aScale)
    {
        SetScale(aScale.x, aScale.y);
    }
    void Transform2D::SetScale(float aX, float aY)
    {
        scale.x = aX;
        scale.y = aY;
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