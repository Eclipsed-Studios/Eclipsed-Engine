#pragma once

#include "Math/Vector/Vector2.h"

#include "../Component.h"

#include "box2d/id.h"

#include "../PhysicsEngine/PhysicsEngineSettings.h"

namespace ENGINE_NAMESPACE
{
    class Transform2D;
    class RigidBody2D : public Component
    {
    public:
        friend class Collider2D;
        friend class BoxCollider2D;

        RigidBody2D() = default;
        ~RigidBody2D() override;

        void Awake() override;
        void EarlyUpdate() override;

        void AddForce(const Math::Vector2f &aVelocity);

        void SetVelocity(const Math::Vector2f &aVelocity);
        const Math::Vector2f &GetVelocity();

        void SetAngularVelocity(float aAngularVelocity);
        const float GetAngularVelocity();

        void SetBodyType(Box2DBodyType aBodytype);
        void GetBodyType();

        void SetRotationLocked(bool aValue);
        bool GetRotationLocked();

        void SetXPosLocked(bool aValue);
        bool GetXPosLocked();

        void SetYPosLocked(bool aValue);
        bool GetYPosLocked();

    private:
        bool bodyHasBeenCreated = false;

        Math::Vector2f myVelocity = {0.f, 0.f};
        float myAngularVelocity = 0.f;

        Transform2D *myTransform;

        RigidBodySettings myRigidBodySettings;

        b2BodyId myBody;

    private:
        // Internals
        RigidBodyUserData mySavedDataForUserData;
    };
}