#include "Game.h"

#include "Input/InputMapper.h"

#include <Components/Rendering/SpriteRenderer2D.h>
#include <Components/Rendering/SpriteSheetAnimator.h>
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

#include "AssetManagement/Resources/SpriteSheetAnimation.h"

namespace ENGINE_NAMESPACE
{
	void Game::Init()
	{
		// Player
		{
			int go = 1;
			SpriteRenderer2D* rend = ComponentManager::AddComponent<SpriteRenderer2D>(go);
			Transform2D* transform = ComponentManager::AddComponent<Transform2D>(go);
			transform->SetScale(60.f, 60.f);
			RigidBody2D* rb = ComponentManager::AddComponent<RigidBody2D>(go);
			rb->SetRotationLocked(true);

			ComponentManager::AddComponent<PlayerMovement>(go);

			BoxCollider2D* boxCollider = ComponentManager::AddComponent<BoxCollider2D>(go);
			boxCollider->SetScale(Math::Vector2f(1.f, 1.f));
			boxCollider->myLayer = Layer::Player;

			Material* matrial = new Material();
			matrial->SetTexture(ASSET_PATH "Sprites/Pink_Monster.png");

			matrial->color.b = 0.f;
			matrial->color.g = 0.f;


			rend->SetMaterial(matrial);

			SpriteSheetAnimator2D* animation = ComponentManager::AddComponent<SpriteSheetAnimator2D>(go);

			//ResourcePointer<SpriteSheetAnimation> anim = Resources::Get<SpriteSheetAnimation>(ASSET_PATH "Sprites/DefaultAnimation.json");


			animation->SetSpriteSheet(ASSET_PATH "Sprites/DefaultAnimation.json");
		}

		// Ground
		{
			int go = 2;
			SpriteRenderer2D* rend = ComponentManager::AddComponent<SpriteRenderer2D>(go);
			Transform2D* transform = ComponentManager::AddComponent<Transform2D>(go);
			transform->SetPosition(0, -0.9f);
			transform->SetScale(1000.f, 10.f);
			BoxCollider2D* boxCollider = ComponentManager::AddComponent<BoxCollider2D>(go);
			boxCollider->SetScale(Math::Vector2f(1.f, 1.f));
			boxCollider->myLayer = Layer::Ground;

			Material* matrial = new Material();
			//matrial->SetTexture(ASSET_PATH "Sprites/Pink_Monster_Run_6.png");

			matrial->color.r = 0.f;
			matrial->color.b = 1.f;
			matrial->color.g = 1.f;

			rend->SetMaterial(matrial);
		}
	}

	void Game::Update()
	{
		
	}
}