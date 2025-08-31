#pragma once

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

    struct RigidBodyUserData
    {
        unsigned gameobject = 0;
    };

    struct ColliderUserData
    {
        unsigned gameobject = 0;
    };

    struct HitResult
    {
        ColliderUserData data;
    };

    struct HitResults
    {
        std::vector<HitResult> results;
        Math::Vector2f position;
    };

    struct Ray
    {
        Math::Vector2f position;
        Math::Vector2f direction;
    };
    

}
