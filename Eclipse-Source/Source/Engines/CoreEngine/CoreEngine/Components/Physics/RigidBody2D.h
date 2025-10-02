#pragma once

#include "Components/Base/BaseComponent.h"

#include "Math/Vector/Vector2.h"

#include "ECS/ComponentManager.h"

#include "box2d/id.h"

#include "../PhysicsEngine/PhysicsEngineSettings.h"

namespace Eclipse
{
    class RigidBody2D : public Component
    {
        BASE_SELECTION(RigidBody2D, 10)

    public:
        friend class Collider2D;
        
        friend class BoxCollider2D;
        friend class CircleCollider2D;
        friend class CapsuleCollider2D;

        friend class PolygonCollider2D;

        void OnSceneLoaded() override;
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

    private:
        RigidBodySettings myRigidBodySettings;
        b2BodyId myBody;

        Box2DBodyType BodyType = DynamicBody;

        SERIALIZED_FIELD_DEFAULT(bool, LockRotation, false);
        SERIALIZED_FIELD_DEFAULT(bool, LockXPos, false);
        SERIALIZED_FIELD_DEFAULT(bool, LockYPos, false);

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