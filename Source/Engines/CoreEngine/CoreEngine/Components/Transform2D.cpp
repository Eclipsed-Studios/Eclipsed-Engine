#include "Transform2D.h"

#include "../TemporarySettingsSingleton.h"

namespace ENGINE_NAMESPACE
{
    const Math::Vector2f &Transform2D::GetPosition()
    {
        return position;
    }
    const float Transform2D::GetRotation()
    {
        return rotation;
    }
    const Math::Vector2f &Transform2D::GetScale()
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
        scale = aScale;
    }
}