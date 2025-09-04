#pragma once

#include <vector>
#include "Math/Vector/Vector2.h"

namespace ENGINE_NAMESPACE
{
    class Collider2D;

    enum Box2DBodyType
    {
        StaticBody = 0,
        KinematicBody = 1,
        DynamicBody = 2
    };

    struct RigidBodySettings
    {
        Box2DBodyType BodyType = StaticBody;

        bool LockRotation = false;
        bool LockXPos = false;
        bool LockYPos = false;
    };

    struct UserData
    {
        unsigned gameobject = 0;
    };

    struct HitResult
    {
        Math::Vector2f point;
        Math::Vector2f normal;
        float fraction;
        unsigned gameobject;
    };

    struct HitResults
    {
        std::vector<HitResult> results;
    };

    struct Ray
    {
        Math::Vector2f position;
        Math::Vector2f direction;
    };

    enum class Layer : uint32_t
    {
        Default = 1 << 1,
        Player = 1 << 2,
        Enemy = 1 << 3,
        Projectile = 1 << 4,
        Ground = 1 << 5,
        Trigger = 1 << 6,
        IgnoreRaycast = 1 << 7,
        UI = 1 << 8,

        All = (1 << 8) - 1
    };

    inline Layer operator|(Layer a, Layer b)
    {
        return static_cast<Layer>(static_cast<unsigned>(a) | static_cast<unsigned>(b));
    }

}
