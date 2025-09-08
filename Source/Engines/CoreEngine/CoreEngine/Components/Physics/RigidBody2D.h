#pragma once

#include "Math/Vector/Vector2.h"

#include "../Component.h"

#include "box2d/id.h"

#include "../PhysicsEngine/PhysicsEngineSettings.h"

namespace ENGINE_NAMESPACE
{
    class RigidBody2D : public Component
    {
        BASE_COMPONENT(RigidBody2D, 10)

    public:
        friend class Collider2D;
        friend class BoxCollider2D;
        friend class PolygonCollider2D;

        void Awake() override;
        void EarlyUpdate() override;

        void AddForce(const Math::Vector2f& aVelocity);

        void SetVelocity(const Math::Vector2f& aVelocity);
        const Math::Vector2f& GetVelocity();

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

    protected:
        void DrawInspector() override;

    private:
        RigidBodySettings myRigidBodySettings;
        b2BodyId myBody;

        Math::Vector2f myVelocity = { 0.f, 0.f };
        float myAngularVelocity = 0.f;

    private:
        class Transform2D* myTransform;

    private:
        // Internals
        UserData myUserData;
        bool bodyHasBeenCreated = false;
    };
}