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

    private:
        class RigidBody2D* myRigidBody = nullptr;
        class Transform2D* myTransform = nullptr;
    };
}