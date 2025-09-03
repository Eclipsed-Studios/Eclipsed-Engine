#include "Game.h"

#include "Input/InputMapper.h"

#include <Components/Rendering/SpriteRendrer2D.h>
#include <Components/Rendering/Animation2D.h>
#include <Components/Transform2D.h>
#include <Components/Physics/RigidBody2D.h>
#include <Components/Physics/BoxCollider2D.h>

#include "Components/PlayerMovement.h"

#include <ECS/ComponentManager.h>
#include <MainSingleton.h>

#include "Timer.h"
#include "Input/Input.h"
#include "Input/Keycodes.h"

#include "PhysicsEngine.h"

#include "Components/Rendering/SpriteSheet.h"

namespace ENGINE_NAMESPACE
{
	void Game::Init()
	{
		Material* matrial = new Material();
		matrial->SetTexture(ASSET_PATH "Sprites/spritesheet.png");

		// Player
		{
			int go = 1;
			SpriteRendrer2D* rend = ComponentManager::AddComponent<SpriteRendrer2D>(go);
			Transform2D* transform = ComponentManager::AddComponent<Transform2D>(go);
			transform->SetScale(30.f, 30.f);
			RigidBody2D* rb = ComponentManager::AddComponent<RigidBody2D>(go);
			rb->SetRotationLocked(true);

			ComponentManager::AddComponent<PlayerMovement>(go);

			BoxCollider2D* boxCollider = ComponentManager::AddComponent<BoxCollider2D>(go);
			boxCollider->SetHalfExtents(Math::Vector2f(15.f, 15.f));
			boxCollider->myLayer = Layer::Player;

			rend->SetMaterial(matrial);

			Animation2D* animation = ComponentManager::AddComponent<Animation2D>(go);
			animation->SetSpriteSheet(ASSET_PATH "Sprites/spritesheet.json");
		}

		// Ground
		{
			int go = 2;
			SpriteRendrer2D* rend = ComponentManager::AddComponent<SpriteRendrer2D>(go);
			Transform2D* transform = ComponentManager::AddComponent<Transform2D>(go);
			transform->SetPosition(0, -1.f);
			transform->SetScale(1000.f, 10.f);
			BoxCollider2D* boxCollider = ComponentManager::AddComponent<BoxCollider2D>(go);
			boxCollider->SetHalfExtents(Math::Vector2f(500.f, 5.f));
			boxCollider->myLayer = Layer::Ground;

			rend->SetMaterial(matrial);
		}
	}

	void Game::Update()
	{
		
	}
}