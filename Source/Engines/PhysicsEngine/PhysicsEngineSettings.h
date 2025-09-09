#pragma once

#include <vector>
#include "Math/Vector/Vector2.h"

#include <string>

#include "defines.h"

#define MAX_LAYERS 16

namespace ENGINE_NAMESPACE
{
    constexpr int layerCount = 7;
    enum class Layer : uint64_t
    {
        Default = 1 << 0,
        Player = 1 << 1,
        Enemy = 1 << 2,
        Projectile = 1 << 3,
        Ground = 1 << 4,
        Trigger = 1 << 5,
        IgnoreRaycast = 1 << 6,
        UI = 1 << 7,

        All = (1 << (layerCount + 1)) - 1
    };

    inline std::string GetCollisionLayerAsName(Layer aLayer)
    {
        switch (aLayer)
        {
        case Layer::Default:
            return stringify(Default);
        case Layer::Player:
            return stringify(Player);
        case Layer::Enemy:
            return stringify(Enemy);
        case Layer::Projectile:
            return stringify(Projectile);
        case Layer::Ground:
            return stringify(Ground);
        case Layer::Trigger:
            return stringify(Trigger);
        case Layer::IgnoreRaycast:
            return stringify(IgnoreRaycast);
        case Layer::UI:
            return stringify(UI);
        }

        return stringify(None);
    }

    inline Layer operator|(Layer a, Layer b)
    {
        return static_cast<Layer>(static_cast<unsigned>(a) | static_cast<unsigned>(b));
    }

    enum DebugDrawTypes
    {
        drawShapes,
        drawJoints,
        drawJointExtras,
        drawBounds,
        drawMass,
        drawBodyNames,
        drawContacts,
        drawGraphColors,
        drawContactNormals,
        drawContactImpulses,
        drawContactFeatures,
        drawFrictionImpulses,
        drawIslands,

        drawQueries,
    };

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
}
