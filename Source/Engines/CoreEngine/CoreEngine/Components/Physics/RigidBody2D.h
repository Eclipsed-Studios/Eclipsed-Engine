#pragma once

#include "Math/Vector/Vector2.h"

#include "../Component.h"

struct b2BodyId;

namespace ENGINE_NAMESPACE
{
    class Transform2D;
    
    class RigidBody2D : public Component
    {
    public:
        RigidBody2D() = default;
        ~RigidBody2D() = default;

        void Awake();

        void AddForce(const Math::Vector2f &aVelocity);

        void SetVelocity(const Math::Vector2f &aVelocity);
        const Math::Vector2f &GetVelocity();

        void SetAngularVelocity(float aAngularVelocity);
        const float GetAngularVelocity();

        void EarlyUpdate() override;

    private:
        Math::Vector2f myVelocity = {0.f, 0.f};
        float myAngularVelocity = 0.f;

        b2BodyId *myBodyID;

        Transform2D *myTransform;
    };
}