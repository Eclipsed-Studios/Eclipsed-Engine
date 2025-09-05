#pragma once

#include "components/Component.h"

namespace ENGINE_NAMESPACE
{
    class PlayerMovement : public Component
    {
    public:
        PlayerMovement() = default;
        ~PlayerMovement() = default;

        void Update() override;
        void Awake() override;

        float myMoveSpeed = 0.4f;
        float myJumpStrength = 2.5f;

    private:
        bool myIsJumping = false;

        class RigidBody2D* myRigidBody = nullptr;
        class Transform2D* myTransform = nullptr;
        class SpriteRenderer2D* mySpriteRenderer = nullptr;
        class SpriteSheetAnimator2D* myAnimation = nullptr;
    };
}