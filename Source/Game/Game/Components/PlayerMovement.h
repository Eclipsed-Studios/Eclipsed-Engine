#pragma once

#include "Components/Base/Component.h"

namespace ENGINE_NAMESPACE
{
    class PlayerMovement : public Component
    {
    public:
        void Awake() override;
        void Update() override;

    private:
        class RigidBody2D* myRigidBody = nullptr;
        class Transform2D* myTransform = nullptr;
        class Player* myPlayer = nullptr;

        const float Run_Multiplier = 1.4f;
        float myMovementSpeed = 0.4f;
        float myJumpStrength = 2.0f;
    };
}