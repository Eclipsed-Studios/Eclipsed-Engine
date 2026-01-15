#pragma once

#include "EclipsedEngine/Components/Component.h"
#include "EclipsedEngine/Components/Physics/RigidBody2D.h"
#include "EclipsedEngine/Components/Rendering/SpriteSheetAnimator2D.h"

#include "CoreEngine/Input/Input.h"
#include "CoreEngine/Timer.h"

namespace Eclipse
{
    class ECLIPSED_API Player : public Component
    {
    public:
        BASE_SELECTION(Player, 10);

        RigidBody2D* rb;
        SpriteSheetAnimator2D* ssa;

        void Awake() override
        {
            rb = gameObject->GetComponent<RigidBody2D>();
            ssa = gameObject->GetComponent<SpriteSheetAnimator2D>();

            ssa->SetIsLooping(false);
        }

        void Update() override
        {
            if (!rb)
                return;

            int leftRight = Input::GetKey(Keycode::D) - Input::GetKey(Keycode::A);
            if (leftRight)
                rb->SetVelocity(Math::Vector2f(leftRight * Time::GetDeltaTime() * 1000, rb->GetVelocity().Y));

            if (Input::GetKeyDown(Keycode::SPACE))
                rb->SetVelocity(Math::Vector2f(0, 6));
                
            if (Input::GetMouseDown(0))
                ssa->Play();
        }


    };
}