#pragma once

#include "EclipsedEngine/Components/Physics/RigidBody2D.h"
#include "EclipsedEngine/Components/Physics/CapsuleCollider2D.h"

#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"
#include "EclipsedEngine/Components/Player.h"
#include "EclipsedEngine/Components/Transform2D.h"

#include "EclipsedEngine/Components/Component.h"

namespace Eclipse
{
    class PlayerSpawner : public Component
    {
    public:
        BASE_SELECTION(PlayerSpawner, 10);

        // void HasSpawnedHere_OnRep()
        // {

        // }

        void Start() override
        {
            GameObject* gameobject = ComponentManager::CreateGameObject();

            auto transfomr = gameobject->AddComponent<Transform2D>(true);
            transfomr->SetPosition(0, 1);
            transfomr->SetScale(30, 30);

            SpriteRenderer2D* spriteRenderer = gameobject->AddComponent<SpriteRenderer2D>(true);

            RigidBody2D* rb = gameobject->AddComponent<RigidBody2D>();
            rb->SetRotationLocked(true);
            
            gameobject->AddComponent<CapsuleCollider2D>(true);
            gameobject->AddComponent<Player>();

            //HasSpawnedHere = true;
        }

        //REPLICATED_SERIALIZED_FIELD_DEFAULT(int, HasSpawnedHere, 0, PlayerSpawner);
    };
}