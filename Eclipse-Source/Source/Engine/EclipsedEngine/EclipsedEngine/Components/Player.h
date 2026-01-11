#pragma once

#include "EclipsedEngine/Components/Component.h"
#include "EclipsedEngine/Components/Physics/RigidBody2D.h"

#include "CoreEngine/Input/Input.h"

namespace Eclipse
{
    class ECLIPSED_API Player : public Component
    {
    public:
        BASE_SELECTION(Player, 10);

        RigidBody2D* rb;

        void Awake() override
        {
            rb = gameObject->GetComponent<RigidBody2D>();
        }

        void Update() override
        {
            if (!rb)
                return;
            
            int leftRight = Input::GetKey(Keycode::D) - Input::GetKey(Keycode::A);

            if (leftRight)
                rb->SetVelocity(Math::Vector2f(leftRight, rb->GetVelocity().Y));
        }


    };
}